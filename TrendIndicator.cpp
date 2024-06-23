#include "sierrachart.h"
#include "scstudyfunctions.h"

SCSFExport scsf_ReferenceDataFromAnotherChart(SCStudyInterfaceRef sc)
{
    SCInputRef Input_ChartStudyInput = sc.Input[0];

    if (sc.SetDefaults)
    {

        sc.GraphName = "Reference Data";
        sc.StudyDescription = "This is an example of referencing data from another chart.";

        sc.AutoLoop = 1;

        Input_ChartStudyInput.Name = "Study Reference";
        Input_ChartStudyInput.SetChartStudyValues(1, 1);

        return;
    }

    // The following code is for getting a study subgraph array
    // and corresponding index from another chart.
    // For example, this could be a moving average study subgraph.

    // Define a graph data object to get all of the study data
    SCGraphData StudyData;

    // Get the study data from the specified chart
    // sc.GetStudyArraysFromChartUsingID(Input_ChartStudyInput.GetChartNumber(), Input_ChartStudyInput.GetStudyID(), StudyData);
    sc.GetStudyArraysFromChartUsingID(11, 4, StudyData);

    // Check if the study has been found.  If it has, GetArraySize() will return the number of Subgraphs in the study.
    if (StudyData.GetArraySize() == 0)
        return;

    // Define a reference to the first subgraph array. Note the type must be 'SCFloatArrayRef' and not 'SCFloatArray'.
    SCFloatArrayRef SubgraphArray = StudyData[0];

    // Array is empty. Nothing to do.
    if (SubgraphArray.GetArraySize() == 0)
        return;

    // Get the index in the specified chart that is nearest
    // to current index.
    RefChartIndex = sc.GetNearestMatchForDateTimeIndex(Input_ChartStudyInput.GetChartNumber(), sc.Index);
    float NearestSubgraphValue = SubgraphArray[RefChartIndex];

    // Get the index in the specified chart that contains
    // the DateTime of the bar at the current index.
    RefChartIndex = sc.GetContainingIndexForDateTimeIndex(Input_ChartStudyInput.GetChartNumber(), sc.Index);
    float ContainingSubgraphValue = SubgraphArray[RefChartIndex];

    // Get the index in the specified chart that exactly
    // matches the DateTime of the current index.
    RefChartIndex = sc.GetExactMatchForSCDateTime(Input_ChartStudyInput.GetChartNumber(), sc.BaseDateTimeIn[sc.Index]);
    if (RefChartIndex != -1) //-1 means that there was not an exact match and therefore we do not have a valid index to work with
    {
        float ExactMatchSubgraphValue = SubgraphArray[RefChartIndex];
    }
}