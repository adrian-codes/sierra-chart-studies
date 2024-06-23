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
    float BoxHigh;
    float BoxLow;

    if (sc.GetUserDrawnChartDrawing(0, DRAWING_RECTANGLEHIGHLIGHT, ChartDrawing, -1))
    {
        // msg.Format("Box High: %f", BoxHigh);
        // sc.AddMessageToLog(msg, 1);
        // msg.Format("Box Low: '%f'", BoxLow);
        // sc.AddMessageToLog(msg, 1);
        // msg.Format("Begin: '%i'", ChartDrawing.BeginIndex);
        // sc.AddMessageToLog(msg, 1);
        // msg.Format("End: '%i'", ChartDrawing.EndIndex);
        // sc.AddMessageToLog(msg, 1);
        // msg.Format("Current: '%i'", sc.Index);
        // sc.AddMessageToLog(msg, 1);

        ChartDrawing.AddMethod = UTAM_ADD_OR_ADJUST;
        // int r_LineNumber = sc.GetPersistentInt(1);
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

        // If ChartDrawing is drawn past the current bar, snap back to current bar Index
        // if (ChartDrawing.EndIndex > sc.Index)
        // {
        //     msg.Format("End: '%i'", ChartDrawing.EndIndex);
        //     sc.AddMessageToLog(msg, 1);
        //     msg.Format("Current: '%i'", sc.Index);
        //     sc.AddMessageToLog(msg, 1);
        //     msg.Format("Setting %i, to %i", ChartDrawing.EndIndex, sc.Index);
        //     sc.AddMessageToLog(msg, 1);
        //     ChartDrawing.EndDateTime.Clear();
        //     ChartDrawing.EndIndex = sc.Index;
        //     sc.UseTool(ChartDrawing);
        //     msg.Format("Updated: '%i'", ChartDrawing.BeginIndex);
        //     sc.AddMessageToLog(msg, 1);
        //     msg.Format("Updated: '%i'", ChartDrawing.EndIndex);
        //     sc.AddMessageToLog(msg, 1);
        // }

        bool BoxExtendable = false;
        // if current price is withn high and low
        // and previous candle didn't have a low close above BoxHigh or a high close below BoxLow (meaning box broke out already)
        // and current index is < EndIndex move EndIndex over 1 to avoid having to keep moving box end boundary
        // trying to use current end index of box plus 1 for the next bar to keep the current last price from within the box and not many
        // bars past the box to prevent extending way past when trading back into the original box

        // maybe check if the current index is +1 of the endindex before making it extendable
        if (sc.Index == ChartDrawing.EndIndex + 1)
        {
            // update this to use the midline logic
            if (sc.BaseData[SC_LAST][sc.Index] < BoxHigh && sc.BaseData[SC_LOW][ChartDrawing.EndIndex - 1] < BoxHigh)
            {
                BoxExtendable = true;
            }
            if (sc.BaseData[SC_LAST][sc.Index] > BoxLow && sc.BaseData[SC_HIGH][ChartDrawing.EndIndex - 1] > BoxLow)
            {
                BoxExtendable = true;
            }
        }
        int BoxLength = (ChartDrawing.EndIndex - ChartDrawing.BeginIndex) + 1;
        // ChartDrawing.LineNumber = r_LineNumber;
        if (BoxExtendable && ChartDrawing.EndIndex != sc.Index && BoxLength < 14)
        {
            ChartDrawing.EndDateTime.Clear();
            ChartDrawing.EndIndex = ChartDrawing.EndIndex + 1;
            sc.UseTool(ChartDrawing);
        }

        BoxLength = (ChartDrawing.EndIndex - ChartDrawing.BeginIndex) + 1;
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
        // r_LineNumber = ChartDrawing.LineNumber;

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
            MarkerDrawingUp.MarkerSize = 15;
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
            MarkerDrawingDown.MarkerSize = 15;
            MarkerDrawingDown.BeginIndex = sc.Index;
            MarkerDrawingDown.BeginValue = ChartDrawing.BeginValue;
            sc.UseTool(MarkerDrawingDown);
            // add markers to subgraph
            sc.Subgraph[1][sc.Index] = sc.BaseData[SC_LAST][sc.Index];
        }
    }
}
