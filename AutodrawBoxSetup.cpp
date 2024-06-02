#include "sierrachart.h"
SCDLLName("AdrianCodes- Update box details based on box length")

    /*
        Written by AdrianCodes
    */

    SCSFExport scsf_BoxSetup(SCStudyInterfaceRef sc)
{
    SCString msg;

    s_UseTool ChartDrawing;
    ChartDrawing.AddMethod = UTAM_ADD_OR_ADJUST;

    if (sc.GetUserDrawnChartDrawing(0, DRAWING_RECTANGLEHIGHLIGHT, ChartDrawing, -1))
    {
        // msg.Format("Box High: '%f'", ChartDrawing.EndValue);
        // sc.AddMessageToLog(msg, 1);
        // msg.Format("Box Low: '%f'", ChartDrawing.BeginValue);
        // sc.AddMessageToLog(msg, 1);
        // msg.Format("Begin: '%i'", ChartDrawing.BeginIndex);
        // sc.AddMessageToLog(msg, 1);
        // msg.Format("End: '%i'", ChartDrawing.EndIndex);
        // sc.AddMessageToLog(msg, 1);
        int BoxLength = (ChartDrawing.EndIndex - ChartDrawing.BeginIndex);
        sc.AddMessageToLog(msg, 1);
        if (BoxLength > 3 & BoxLength < 8)
        {
            ChartDrawing.Color = RGB(255, 255, 0);
            msg.Format("Box %i", BoxLength);
            ChartDrawing.Text = msg;
            sc.UseTool(ChartDrawing);
        }
        if (BoxLength > 8)
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
    }
}
