#include "sierrachart.h"
SCDLLName("AdrianCodes - Update box details based on box length")

    /*
        Written by AdrianCodes
    */

    SCSFExport scsf_BoxSetup(SCStudyInterfaceRef sc)
{
    SCString msg;

    if (sc.SetDefaults)
    {
        sc.GraphName = "Auto Box Setup";
        sc.GraphRegion = 1;
        return;
    }
    s_UseTool ChartDrawing;
    ChartDrawing.AddMethod = UTAM_ADD_OR_ADJUST;
    int &r_LineNumber = sc.GetPersistentInt(1);
    float BoxHigh;
    float BoxLow;

    if (sc.GetUserDrawnChartDrawing(0, DRAWING_RECTANGLEHIGHLIGHT, ChartDrawing, -1))
    {
        if (ChartDrawing.BeginValue > ChartDrawing.EndValue)
        {
            BoxHigh = ChartDrawing.BeginValue;
            BoxLow = ChartDrawing.EndValue;
        }
        else
        {
            BoxHigh = ChartDrawing.EndValue;
            BoxLow = ChartDrawing.BeginValue;
        }

        // msg.Format("Box High: %f", BoxHigh);
        // sc.AddMessageToLog(msg, 1);
        // msg.Format("Box Low: '%f'", BoxLow);
        // sc.AddMessageToLog(msg, 1);
        // msg.Format("Begin: '%i'", ChartDrawing.BeginIndex);
        // sc.AddMessageToLog(msg, 1);
        // msg.Format("End: '%i'", ChartDrawing.EndIndex);
        // sc.AddMessageToLog(msg, 1);

        int BoxLength = (ChartDrawing.EndIndex - ChartDrawing.BeginIndex);
        // if current price is withng high and low and current index is < EndIndex move EndIndex over 1
        // to avoid having to keep moving box end boundary
        if (sc.BaseData[SC_LAST][sc.Index] < ChartDrawing.EndValue && sc.BaseData[SC_LAST][sc.Index] > ChartDrawing.BeginValue)
        {
            ChartDrawing.EndDateTime.Clear();
            ChartDrawing.EndIndex = sc.Index;
            sc.UseTool(ChartDrawing);
        }

        if (BoxLength > 3 & BoxLength < 8)
        {
            ChartDrawing.Color = RGB(255, 255, 0);
            msg.Format("Box %i", BoxLength);
            ChartDrawing.Text = msg;
            sc.UseTool(ChartDrawing);
        }
        if (BoxLength > 7)
        {
            ChartDrawing.Color = RGB(0, 255, 0);
            msg.Format("NTIT %i", BoxLength);
            ChartDrawing.Text = msg;
            sc.UseTool(ChartDrawing);
        }
        if (BoxLength > 12)
        {
            ChartDrawing.Color = RGB(255, 0, 255);
            msg.Format("Base %i", BoxLength);
            ChartDrawing.Text = msg;
            sc.UseTool(ChartDrawing);
        }

        sc.Subgraph[0].Name = "Box Triggers Up";
        sc.Subgraph[0].DrawStyle = DRAWSTYLE_ARROW_UP;
        sc.Subgraph[0].PrimaryColor = COLOR_GREEN;
        sc.Subgraph[1].Name = "Box Triggers Down";
        sc.Subgraph[1].DrawStyle = DRAWSTYLE_ARROW_DOWN;
        sc.Subgraph[1].PrimaryColor = COLOR_RED;

        // if price is higher then BoxHigh boundary and length of box is >= 8 and within the box plot the marker
        if (sc.BaseData[SC_LAST][sc.Index] > BoxHigh && BoxLength >= 8 && sc.Index <= ChartDrawing.EndIndex)
        {
            s_UseTool MarkerDrawingUp;
            MarkerDrawingUp.Clear();
            MarkerDrawingUp.BeginDateTime.Clear();
            MarkerDrawingUp.AddMethod = UTAM_ADD_OR_ADJUST;
            MarkerDrawingUp.Region = 0;
            MarkerDrawingUp.DrawingType = DRAWING_MARKER;
            MarkerDrawingUp.MarkerType = MARKER_TRIANGLEUP;
            MarkerDrawingUp.Color = COLOR_GREEN;
            MarkerDrawingUp.AddMethod = UTAM_ADD_OR_ADJUST;
            MarkerDrawingUp.MarkerSize = 20;
            MarkerDrawingUp.BeginIndex = sc.Index;
            MarkerDrawingUp.BeginValue = ChartDrawing.EndValue;
            sc.UseTool(MarkerDrawingUp);
            // add markers to subgraph
            sc.Subgraph[0][sc.Index] = sc.BaseData[SC_LAST][sc.Index];
        }
        // if price is higher then BoxLow boundary and length of box is >= 8 and within the box plot the marker
        if (sc.BaseData[SC_LAST][sc.Index] < BoxLow && BoxLength >= 8 && sc.Index <= ChartDrawing.EndIndex)
        {
            s_UseTool MarkerDrawingDown;
            MarkerDrawingDown.Clear();
            MarkerDrawingDown.BeginDateTime.Clear();
            MarkerDrawingDown.AddMethod = UTAM_ADD_OR_ADJUST;
            MarkerDrawingDown.Region = 0;
            MarkerDrawingDown.DrawingType = DRAWING_MARKER;
            MarkerDrawingDown.MarkerType = MARKER_TRIANGLEDOWN;
            MarkerDrawingDown.Color = COLOR_RED;
            MarkerDrawingDown.AddMethod = UTAM_ADD_OR_ADJUST;
            MarkerDrawingDown.MarkerSize = 20;
            MarkerDrawingDown.BeginIndex = sc.Index;
            MarkerDrawingDown.BeginValue = ChartDrawing.BeginValue;
            sc.UseTool(MarkerDrawingDown);
            // add markers to subgraph
            sc.Subgraph[1][sc.Index] = sc.BaseData[SC_LAST][sc.Index];
        }
    }
}
