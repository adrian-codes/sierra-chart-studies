#include "sierrachart.h"
SCDLLName("AdrianCodes- Study Text Display")

    /*============================================================================*/

    SCSFExport scsf_LargeTextDisplayForStudyFromChart(SCStudyInterfaceRef sc)

{

    SCSubgraphRef TextDisplay = sc.Subgraph[0];

    SCInputRef HorizontalPosition = sc.Input[0];

    SCInputRef VerticalPosition = sc.Input[1];

    SCInputRef DisplayInFillSpace = sc.Input[2];

    SCInputRef StudySubgraphReference = sc.Input[3];

    SCInputRef DisplaySubgraphName = sc.Input[4];

    SCInputRef SubgraphOffset = sc.Input[5];

    if (sc.SetDefaults)

    {

        // Set the configuration and defaults

        sc.GraphName = "Text Display For Study from Chart";

        sc.AutoLoop = 0;

        sc.GraphRegion = 0;

        TextDisplay.Name = "Text Display";

        TextDisplay.LineWidth = 20;

        TextDisplay.DrawStyle = DRAWSTYLE_CUSTOM_TEXT;

        TextDisplay.PrimaryColor = RGB(0, 0, 0); // black

        TextDisplay.SecondaryColor = RGB(128, 255, 255);

        TextDisplay.SecondaryColorUsed = true;

        TextDisplay.DisplayNameValueInWindowsFlags = 0;

        HorizontalPosition.Name = "Horizontal Position From Left (1-150)";

        HorizontalPosition.SetInt(20);

        HorizontalPosition.SetIntLimits(1, 150);

        VerticalPosition.Name = "Vertical Position From Bottom (1-100)";

        VerticalPosition.SetInt(90);

        VerticalPosition.SetIntLimits(1, 100);

        DisplayInFillSpace.Name = "Display in Fill Space";

        DisplayInFillSpace.SetYesNo(false);

        StudySubgraphReference.Name = "Study And Subgraph To Display";

        StudySubgraphReference.SetChartStudySubgraphValues(1, 1, 0);

        DisplaySubgraphName.Name = "Display Subgraph Name";

        DisplaySubgraphName.SetYesNo(false);

        SubgraphOffset.Name = "Subgraph Columns Back";

        SubgraphOffset.SetInt(0);

        sc.TextInputName = "Prefix Text for Display Value";

        // During development set this flag to 1, so the DLL can be modified. When development is completed, set it to 0 to improve performance.

        sc.FreeDLL = false;

        return;
    }

    // Do data processing

    if (sc.HideStudy) // do nothing if study is hidden

        return;

    SCFloatArray StudyReference;

    // sc.GetStudyArrayFromChartUsingID(StudySubgraphReference.GetChartStudySubgraphValues(), StudyReference);

    //   sc.GetStudyArrayFromChartUsingID(StudySubgraphReference.GetChartNumber(), StudySubgraphReference.GetStudyID(), StudySubgraphReference.GetSubgraphIndex(), StudyReference);
    sc.GetStudyArrayFromChartUsingID(11, 4, StudySubgraphReference.GetSubgraphIndex(), StudyReference);

    s_UseTool Tool;

    Tool.Clear(); // Reset tool structure for our next use. Unnecessary in this case, but good practice.

    Tool.ChartNumber = sc.ChartNumber;

    Tool.DrawingType = DRAWING_TEXT;

    Tool.LineNumber = 79212343 + (sc.StudyGraphInstanceID);

    if (!DisplayInFillSpace.GetYesNo() && !sc.Input[8].GetYesNo())

        Tool.BeginDateTime = HorizontalPosition.GetInt();

    else

        Tool.BeginDateTime = -3;

    Tool.Region = sc.GraphRegion;

    Tool.BeginValue = (float)VerticalPosition.GetInt();

    Tool.UseRelativeVerticalValues = true;

    Tool.Color = TextDisplay.PrimaryColor;

    Tool.FontBackColor = TextDisplay.SecondaryColor;

    Tool.FontBold = true;

    SCString ValueText;

    if (sc.TextInput.GetLength() > 0)

    {

        ValueText += sc.TextInput;

        ValueText += " ";
    }

    int ColumnsBack = SubgraphOffset.GetInt();

    float StudyValue = StudyReference[StudyReference.GetArraySize() - 1 - ColumnsBack];

    if (StudyValue == -FLT_MAX) // Patch for when referencing data from the Numbers Bars Calculated Values study. This value could be used.

        StudyValue = 0;

    ValueText += sc.FormatGraphValue(StudyValue, sc.GetValueFormat());

    Tool.Text = ValueText;

    Tool.FontSize = TextDisplay.LineWidth;

    Tool.AddMethod = UTAM_ADD_OR_ADJUST;

    Tool.ReverseTextColor = false;

    sc.UseTool(Tool);
}
