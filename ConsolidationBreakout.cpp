#include "sierrachart.h"

SCDLLName("Consolidation Breakout Detection");

void DrawRectangle(SCStudyInterfaceRef &sc, float startY, float endY, int startBar, int endBar);

SCSFExport scsf_ConsolidationBreakout(SCStudyInterfaceRef sc)
{
    if (sc.SetDefaults)
    {
        sc.GraphName = "Consolidation Breakout Detection";
        sc.StudyDescription = "Detects consolidation and breakout using Zig Zag Highs and Lows.";
        sc.AutoLoop = 1;

        sc.Subgraph[0].Name = "ZigZag HighLow";
        sc.Subgraph[0].DrawStyle = DRAWSTYLE_IGNORE;

        sc.Input[0].Name = "Breakout Value";
        sc.Input[0].SetFloat(250.0f);

        return;
    }

    float breakoutValue = sc.Input[0].GetFloat();

    int zigZagStudyID = sc.GetStudyIDByName(sc.ChartNumber, "Zig Zag", 1);
    if (zigZagStudyID == -1)
    {
        sc.AddMessageToLog("Could not find Zig Zag study on the chart.", 1);
        return;
    }

    SCFloatArray zigZagLabelsArray;
    if (!sc.GetStudyArrayUsingID(zigZagStudyID, 1, zigZagLabelsArray))
    {
        sc.AddMessageToLog("Could not get ZigZag label data.", 1);
        return;
    }

    static float rectStartY = 0, rectEndY = 0;
    static int rectStartBar = 0, rectEndBar = 0;
    float labelValue = zigZagLabelsArray[sc.Index];

    if (labelValue == 1)
    {
        if (rectStartY == 0 && sc.High[sc.Index] > rectEndY)
        {
            rectEndY = sc.High[sc.Index];
            rectEndBar = sc.Index;
        }
    }
    else if (labelValue == 4)
    {
        if (rectStartY == 0 && sc.Low[sc.Index] < rectStartY)
        {
            rectStartY = sc.Low[sc.Index];
            rectStartBar = sc.Index;
        }
    }

    if (rectStartY != 0 && rectEndY != 0)
        DrawRectangle(sc, rectStartY, rectEndY, rectStartBar, rectEndBar);

    if (sc.Close[sc.Index] > (rectEndY + breakoutValue) && sc.Close[sc.Index] < rectStartY - breakoutValue)
    {
        int lastBar = sc.Index;
        while (lastBar >= 0 && ((sc.Close[lastBar] <= rectEndY && sc.High[sc.Index] > rectEndY + breakoutValue) && (sc.Close[lastBar] >= rectStartY && sc.Low[sc.Index] < rectStartY - breakoutValue)))
        {
            lastBar--;
        }
        rectEndBar = lastBar;
        DrawRectangle(sc, rectStartY, rectEndY, rectStartBar, rectEndBar);
        rectStartY = 0;
        rectEndY = 0;
    }
}

void DrawRectangle(SCStudyInterfaceRef &sc, float startY, float endY, int startBar, int endBar)
{
    s_UseTool tool;
    tool.ChartNumber = sc.ChartNumber;
    tool.DrawingType = DRAWING_RECTANGLEHIGHLIGHT;
    tool.Region = 0;
    tool.Color = RGB(128, 128, 128);
    tool.LineWidth = 1;
    tool.AddAsUserDrawnDrawing = 0;
    tool.BeginDateTime = startBar;
    tool.BeginValue = startY;
    tool.EndDateTime = endBar;
    tool.EndValue = endY;
    tool.ExtendRight = 1;
    tool.TransparencyLevel = 200;

    sc.UseTool(tool);
}