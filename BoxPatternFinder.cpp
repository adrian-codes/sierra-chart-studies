#include "sierrachart.h"
// #include "CandleStickPatternNames.h"

const char *CandleStickPatternNames[66][2] =
    {
        {"None", ""},
        {"Hammer", "HMM"},
        {"Hanging Man", "HNM"},
        {"Bullish Engulfing", "UEN"},
        {"Bearish Engulfing", "DEN"},
        {"Dark-cloud Cover", "DCC"},
        {"Piercing Line", "PEL"},
        {"Morning Star", "MST"},
        {"Evening Star", "EST"},
        {"Morning Doji Star", "MDS"},
        {"Evening Doji Star", "EDS"},
        {"Bullish Abandoned Baby", "UAB"},
        {"Bearish Abandoned Baby", "DAB"},
        {"Shooting Star", "SHS"},
        {"Inverted Hammer", "IHM"},
        {"Bearish Harami", "DHA"},
        {"Bullish Harami", "UHA"},
        {"Bearish Harami Cross", "DHC"},
        {"Bullish Harami Cross", "UHC"},
        {"Tweezer Top", "TWT"},
        {"Tweezer Bottom", "TWB"},
        {"Bearish Belt-Hold Line", "DBH"},
        {"Bullish Belt-Hold Line", "UBH"},
        {"Upside-Gap Two Crows", "TCR"},
        {"Three Black Crows", "TBC"},
        {"Bearish Counterattack Line", "DCL"},
        {"Bullish Counterattack Line", "UCL"},
        {"Three Inside Up", "TIU"},
        {"Three Outside Up", "TOU"},
        {"Three Inside Down", "TID"},
        {"Three Outside Down", "TOD"},
        {"Kicker", "UKI"},
        {"Kicking", "DKI"},
        {"Three White Soldiers", "TWS"},
        {"Advance Block", "ABL"},
        {"Deliberation", "DEL"},
        {"Bearish Tri Star", "DTS"},
        {"Bullish Tri Star", "UTS"},
        {"Unique Three River Bottom", "TRB"},
        {"Bearish Doji Star", "DDS"},
        {"Bullish Doji Star", "UDS"},
        {"Bearish Dragonfly Doji", "DDD"},
        {"Bullish Dragonfly Doji", "UDD"},
        {"Bearish Gravestone Doji", "DGD"},
        {"Bullish Gravestone Doji", "UGD"},
        {"Bearish Long Legged Doji", "DLD"},
        {"Bullish Long Legged Doji", "ULD"},
        {"Bearish Side-By-Side White Lines", "DWL"},
        {"Bullish Side-By-Side White Lines", "UWL"},
        {"Falling Three Methods", "FTM"},
        {"Rising Three Methods", "RTM"},
        {"Bearish Separating Lines", "DSL"},
        {"Bullish Separating Lines", "USL"},
        {"Downside Tasuki Gap", "DTG"},
        {"Upside Tasuki Gap", "UTG"},
        {"Bearish Three-Line Strike", "DTL"},
        {"Bullish Three-Line Strike", "UTL"},
        {"Downside Gap Three Methods", "DGM"},
        {"Upside Gap Three Methods", "UGM"},
        {"On Neck", "ONE"},
        {"In Neck", "INE"},
        {"Bearish Thrusting", "DTH"},
        {"Mat Hold", "MAT"},
        {"Doji", "DOJ"},
        {"Bullish Engulfing-Body Only", "UENB"},
        {"Box", "BOX"}};

extern const char *CandleStickPatternNames[66][2];

const int NUM_CANDLESTICK_PATTERN_NAMES = (sizeof(CandleStickPatternNames) / sizeof(char *)) / 2;
/*==========================================================================*/
/*==========================================================================*/
//  Candle Pattern Finder
/*==========================================================================*/

SCDLLName("AdrianCodes - Finds Box Pattern")

    struct s_CandleStickPatternsFinderSettings
{
    int PriceRangeNumberOfBars;
    double PriceRangeMultiplier;
    int UseTrendDetection;

    s_CandleStickPatternsFinderSettings()
    {
        // default values
        PriceRangeNumberOfBars = 100;
        PriceRangeMultiplier = 0.01;
        UseTrendDetection = true;
    }
};

// Candle dimensions

inline double CandleLength(SCBaseDataRef InData, int index);
inline double BodyLength(SCBaseDataRef InData, int index);
inline double UpperWickLength(SCBaseDataRef InData, int index);
inline double LowerWickLength(SCBaseDataRef InData, int index);

// Helper functions

int DetermineTrendForCandlestickPatterns(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &PatternsFinderSettings, int index, int num_of_candles);

inline bool IsBodyStrong(SCBaseDataRef InData, int index);
inline bool IsCandleStrength(SCBaseDataRef InData, int index);

inline bool IsDoji(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);

inline bool IsBodyStrong(SCBaseDataRef InData, int index);
inline bool IsCandleStrength(SCBaseDataRef InData, int index);

inline bool IsWhiteCandle(SCBaseDataRef InData, int index);
inline bool IsBlackCandle(SCBaseDataRef InData, int index);

inline double PercentOfCandleLength(SCBaseDataRef InData, int index, double percent);
inline double PercentOfBodyLength(SCBaseDataRef InData, int index, double percent);

inline bool IsUpperWickSmall(SCBaseDataRef InData, int index, double percent);
inline bool IsLowerWickSmall(SCBaseDataRef InData, int index, double percent);

inline bool IsNearEqual(double value1, double value2, SCBaseDataRef InData, int index, double percent);

inline bool IsInsideCandle(float currentHigh, float prevHigh, float currentLow, float prevLow, int index);

// Formations

bool IsHammer(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsHangingMan(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsBullishEngulfing(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsBearishEngulfing(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsBullishEngulfingBodyOnly(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsBearishEngulfingBodyOnly(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsDarkCloudCover(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsPiercingLine(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsMorningStar(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsEveningStar(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsMorningDojiStar(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsEveningDojiStar(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsBullishAbandonedBaby(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsBearishAbandonedBaby(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsShootingStar(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsInvertedHammer(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsBearishHarami(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsBullishHarami(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsBearishHaramiCross(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsBullishHaramiCross(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsTweezerTop(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsTweezerBottom(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsBearishBeltHoldLine(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsBullishBeltHoldLine(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsTwoCrows(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsThreeBlackCrows(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsBearishCounterattackLine(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsBullishCounterattackLine(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsThreeInsideUp(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsThreeOutsideUp(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsThreeInsideDown(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsThreeOutsideDown(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsKicker(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsKicking(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsThreeWhiteSoldiers(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsAdvanceBlock(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsDeliberation(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsBearishTriStar(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsBullishTriStar(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsUniqueThreeRiverBottom(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsBearishDojiStar(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsBullishDojiStar(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsBearishDragonflyDoji(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsBullishDragonflyDoji(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsBearishGravestoneDoji(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsBullishGravestoneDoji(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsBearishLongleggedDoji(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsBullishLongleggedDoji(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsBearishSideBySideWhiteLines(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsBullishSideBySideWhiteLines(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsFallingThreeMethods(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsRisingThreeMethods(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsBearishSeparatingLines(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsBullishSeparatingLines(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsDownsideTasukiGap(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsUpsideTasukiGap(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsBearishThreeLineStrike(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsBullishThreeLineStrike(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsDownsideGapThreeMethods(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsUpsideGapThreeMethods(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsOnNeck(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsInNeck(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsBearishThrusting(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsMatHold(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index);
bool IsBox(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index, int r_DrawingNumberForLastBar);

static const int CANDLESTICK_TREND_FLAT = 0;
static const int CANDLESTICK_TREND_UP = 1;
static const int CANDLESTICK_TREND_DOWN = -1;
static const int TREND_FOR_PATTERNS = 8;

/*==========================================================================*/
SCSFExport scsf_CandleStickPatternsFinder(SCStudyInterfaceRef sc)
{
    SCSubgraphRef Subgraph_Pattern1 = sc.Subgraph[0];
    SCSubgraphRef Subgraph_Pattern2 = sc.Subgraph[1];
    SCSubgraphRef Subgraph_Pattern3 = sc.Subgraph[2];
    SCSubgraphRef Subgraph_Pattern4 = sc.Subgraph[3];
    SCSubgraphRef Subgraph_Pattern5 = sc.Subgraph[4];
    SCSubgraphRef Subgraph_Pattern6 = sc.Subgraph[5];
    SCSubgraphRef Subgraph_TrendUp = sc.Subgraph[6];
    SCSubgraphRef Subgraph_TrendDown = sc.Subgraph[7];
    SCSubgraphRef Subgraph_TrendForPatterns = sc.Subgraph[TREND_FOR_PATTERNS];

    SCInputRef Input_InputPattern1 = sc.Input[0];
    SCInputRef Input_InputPattern2 = sc.Input[1];
    SCInputRef Input_InputPattern3 = sc.Input[2];
    SCInputRef Input_InputPattern4 = sc.Input[3];
    SCInputRef Input_InputPattern5 = sc.Input[4];
    SCInputRef Input_InputPattern6 = sc.Input[5];
    SCInputRef Input_UseNumericValue = sc.Input[6];
    SCInputRef Input_Distance = sc.Input[7];
    SCInputRef Input_PriceRangeNumberOfBars = sc.Input[8];
    SCInputRef Input_PriceRangeMultiplier = sc.Input[9];
    SCInputRef Input_TrendDetection = sc.Input[10];
    SCInputRef Input_TrendDetectionLength = sc.Input[11];
    SCInputRef Input_DisplayText = sc.Input[12];
    SCInputRef Input_DisplayAboveCandle = sc.Input[13];

    if (sc.SetDefaults)
    {
        sc.GraphName = "CandleStick Patterns Finder";
        sc.StudyDescription = "This study looks for candlestick patterns and identifies them on the chart with an abbreviation on the bar where they occur. It uses very advanced logic.";

        sc.AutoLoop = 1;
        sc.GraphRegion = 0;

        Subgraph_Pattern1.Name = "Pattern 1";
        Subgraph_Pattern1.DrawStyle = DRAWSTYLE_CUSTOM_TEXT;
        Subgraph_Pattern1.PrimaryColor = RGB(255, 255, 0);
        Subgraph_Pattern1.SecondaryColor = RGB(0, 0, 0);
        Subgraph_Pattern1.SecondaryColorUsed = TRUE;
        Subgraph_Pattern1.LineWidth = 8;
        Subgraph_Pattern1.DrawZeros = false;

        Subgraph_Pattern2.Name = "Pattern 2";
        Subgraph_Pattern2.DrawStyle = DRAWSTYLE_IGNORE;
        Subgraph_Pattern2.PrimaryColor = RGB(255, 255, 255);
        Subgraph_Pattern2.DrawZeros = false;

        Subgraph_Pattern3.Name = "Pattern 3";
        Subgraph_Pattern3.DrawStyle = DRAWSTYLE_IGNORE;
        Subgraph_Pattern3.PrimaryColor = RGB(255, 255, 255);
        Subgraph_Pattern3.DrawZeros = false;

        Subgraph_Pattern4.Name = "Pattern 4";
        Subgraph_Pattern4.DrawStyle = DRAWSTYLE_IGNORE;
        Subgraph_Pattern4.PrimaryColor = RGB(255, 255, 255);
        Subgraph_Pattern4.DrawZeros = false;

        Subgraph_Pattern5.Name = "Pattern 5";
        Subgraph_Pattern5.DrawStyle = DRAWSTYLE_IGNORE;
        Subgraph_Pattern5.PrimaryColor = RGB(255, 255, 255);
        Subgraph_Pattern5.DrawZeros = false;

        Subgraph_Pattern6.Name = "Pattern 6";
        Subgraph_Pattern6.DrawStyle = DRAWSTYLE_IGNORE;
        Subgraph_Pattern6.PrimaryColor = RGB(255, 255, 255);
        Subgraph_Pattern6.DrawZeros = false;

        Subgraph_TrendUp.Name = "Trend Up";
        Subgraph_TrendUp.DrawStyle = DRAWSTYLE_IGNORE;
        Subgraph_TrendUp.PrimaryColor = COLOR_GREEN;
        Subgraph_TrendUp.DrawZeros = false;

        Subgraph_TrendDown.Name = "Trend Down";
        Subgraph_TrendDown.DrawStyle = DRAWSTYLE_IGNORE;
        Subgraph_TrendDown.PrimaryColor = COLOR_RED;
        Subgraph_TrendDown.DrawZeros = false;

        Input_InputPattern1.Name = "Pattern 1";
        Input_InputPattern1.SetCandleStickPatternIndex(0);

        Input_InputPattern2.Name = "Pattern 2";
        Input_InputPattern2.SetCandleStickPatternIndex(0);

        Input_InputPattern3.Name = "Pattern 3";
        Input_InputPattern3.SetCandleStickPatternIndex(0);

        Input_InputPattern4.Name = "Pattern 4";
        Input_InputPattern4.SetCandleStickPatternIndex(0);

        Input_InputPattern5.Name = "Pattern 5";
        Input_InputPattern5.SetCandleStickPatternIndex(0);

        Input_InputPattern6.Name = "Pattern 6";
        Input_InputPattern6.SetCandleStickPatternIndex(0);

        Input_UseNumericValue.Name = "Use Numeric Values Instead of Letter Codes";
        Input_UseNumericValue.SetYesNo(0);

        Input_Distance.Name = "Distance Between the Codes and the Candle as a Percentage";
        Input_Distance.SetInt(5);

        Input_PriceRangeNumberOfBars.Name = "Number of Bars for Price Range Detection (Used for Trend Detection)";
        Input_PriceRangeNumberOfBars.SetInt(100);

        Input_PriceRangeMultiplier.Name = "Price Range Multiplier for Determining Value Per Point";
        Input_PriceRangeMultiplier.SetFloat(0.01f);

        Input_TrendDetection.Name = "Use Trend Detection";
        Input_TrendDetection.SetYesNo(false);

        Input_TrendDetectionLength.Name = "Number of Bars Used For Trend Detection";
        Input_TrendDetectionLength.SetInt(4);
        Input_TrendDetectionLength.SetIntLimits(1, MAX_STUDY_LENGTH);

        Input_DisplayText.Name = "Display Text";
        Input_DisplayText.SetYesNo(true);

        Input_DisplayAboveCandle.Name = "Display Above Candles";
        Input_DisplayAboveCandle.SetYesNo(false);

        return;
    }

    // This must always be custom text
    Subgraph_Pattern1.DrawStyle = DRAWSTYLE_CUSTOM_TEXT;

    // These must always be ignore
    Subgraph_Pattern2.DrawStyle = DRAWSTYLE_IGNORE;
    Subgraph_Pattern3.DrawStyle = DRAWSTYLE_IGNORE;
    Subgraph_Pattern4.DrawStyle = DRAWSTYLE_IGNORE;
    Subgraph_Pattern5.DrawStyle = DRAWSTYLE_IGNORE;
    Subgraph_Pattern6.DrawStyle = DRAWSTYLE_IGNORE;

    int &r_DrawingNumberForLastBar = sc.GetPersistentInt(1);
    if (sc.IsFullRecalculation)
        r_DrawingNumberForLastBar = 0;

    if (Subgraph_Pattern1.LineWidth <= 1)
    {
        Subgraph_Pattern1.LineWidth = 8;
    }

    const int NumberOfPatternsToDetect = 6;

    uint32_t PatternToLookFor[NumberOfPatternsToDetect];
    PatternToLookFor[0] = Input_InputPattern1.GetCandleStickPatternIndex();
    PatternToLookFor[1] = Input_InputPattern2.GetCandleStickPatternIndex();
    PatternToLookFor[2] = Input_InputPattern3.GetCandleStickPatternIndex();
    PatternToLookFor[3] = Input_InputPattern4.GetCandleStickPatternIndex();
    PatternToLookFor[4] = Input_InputPattern5.GetCandleStickPatternIndex();
    PatternToLookFor[5] = Input_InputPattern6.GetCandleStickPatternIndex();

    s_CandleStickPatternsFinderSettings PatternsFinderSettings;

    if (Input_PriceRangeNumberOfBars.GetInt() > 0)
    {
        PatternsFinderSettings.PriceRangeNumberOfBars = Input_PriceRangeNumberOfBars.GetInt();
    }

    if (Input_PriceRangeMultiplier.GetFloat() > 0)
    {
        PatternsFinderSettings.PriceRangeMultiplier = Input_PriceRangeMultiplier.GetFloat();
    }

    PatternsFinderSettings.UseTrendDetection = Input_TrendDetection.GetYesNo();

    bool DisplayNumericValue = (Input_UseNumericValue.GetYesNo() != 0);

    bool PatternDetected = false;
    bool PatternCodesToDisplay = false;

    int Direction = DetermineTrendForCandlestickPatterns(sc, PatternsFinderSettings, sc.Index - 1, Input_TrendDetectionLength.GetInt());

    Subgraph_TrendForPatterns[sc.Index] = static_cast<float>(Direction);

    if (Direction == CANDLESTICK_TREND_UP)
    {
        Subgraph_TrendUp[sc.Index] = sc.Low[sc.Index];
        Subgraph_TrendDown[sc.Index] = 0;
    }
    else if (Direction == CANDLESTICK_TREND_DOWN)
    {
        Subgraph_TrendUp[sc.Index] = 0;
        Subgraph_TrendDown[sc.Index] = sc.High[sc.Index];
    }
    else
    {
        Subgraph_TrendUp[sc.Index] = 0;
        Subgraph_TrendDown[sc.Index] = 0;
    }

    SCString DisplayTextString;

    for (int Index = 0; Index < NumberOfPatternsToDetect; Index++)
    {
        sc.Subgraph[Index][sc.Index] = 0;

        PatternDetected = false;

        switch (PatternToLookFor[Index])
        {
        case 1:
            PatternDetected = IsHammer(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 2:
            PatternDetected = IsHangingMan(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 3:
            PatternDetected = IsBullishEngulfing(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 4:
            PatternDetected = IsBearishEngulfing(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 5:
            PatternDetected = IsDarkCloudCover(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 6:
            PatternDetected = IsPiercingLine(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 7:
            PatternDetected = IsMorningStar(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 8:
            PatternDetected = IsEveningStar(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 9:
            PatternDetected = IsMorningDojiStar(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 10:
            PatternDetected = IsEveningDojiStar(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 11:
            PatternDetected = IsBullishAbandonedBaby(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 12:
            PatternDetected = IsBearishAbandonedBaby(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 13:
            PatternDetected = IsShootingStar(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 14:
            PatternDetected = IsInvertedHammer(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 15:
            PatternDetected = IsBearishHarami(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 16:
            PatternDetected = IsBullishHarami(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 17:
            PatternDetected = IsBearishHaramiCross(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 18:
            PatternDetected = IsBullishHaramiCross(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 19:
            PatternDetected = IsTweezerTop(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 20:
            PatternDetected = IsTweezerBottom(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 21:
            PatternDetected = IsBearishBeltHoldLine(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 22:
            PatternDetected = IsBullishBeltHoldLine(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 23:
            PatternDetected = IsTwoCrows(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 24:
            PatternDetected = IsThreeBlackCrows(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 25:
            PatternDetected = IsBearishCounterattackLine(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 26:
            PatternDetected = IsBullishCounterattackLine(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 27:
            PatternDetected = IsThreeInsideUp(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 28:
            PatternDetected = IsThreeOutsideUp(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 29:
            PatternDetected = IsThreeInsideDown(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 30:
            PatternDetected = IsThreeOutsideDown(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 31:
            PatternDetected = IsKicker(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 32:
            PatternDetected = IsKicking(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 33:
            PatternDetected = IsThreeWhiteSoldiers(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 34:
            PatternDetected = IsAdvanceBlock(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 35:
            PatternDetected = IsDeliberation(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 36:
            PatternDetected = IsBearishTriStar(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 37:
            PatternDetected = IsBullishTriStar(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 38:
            PatternDetected = IsUniqueThreeRiverBottom(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 39:
            PatternDetected = IsBearishDojiStar(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 40:
            PatternDetected = IsBullishDojiStar(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 41:
            PatternDetected = IsBearishDragonflyDoji(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 42:
            PatternDetected = IsBullishDragonflyDoji(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 43:
            PatternDetected = IsBearishGravestoneDoji(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 44:
            PatternDetected = IsBullishGravestoneDoji(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 45:
            PatternDetected = IsBearishLongleggedDoji(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 46:
            PatternDetected = IsBullishLongleggedDoji(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 47:
            PatternDetected = IsBearishSideBySideWhiteLines(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 48:
            PatternDetected = IsBullishSideBySideWhiteLines(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 49:
            PatternDetected = IsFallingThreeMethods(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 50:
            PatternDetected = IsRisingThreeMethods(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 51:
            PatternDetected = IsBearishSeparatingLines(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 52:
            PatternDetected = IsBullishSeparatingLines(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 53:
            PatternDetected = IsDownsideTasukiGap(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 54:
            PatternDetected = IsUpsideTasukiGap(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 55:
            PatternDetected = IsBearishThreeLineStrike(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 56:
            PatternDetected = IsBullishThreeLineStrike(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 57:
            PatternDetected = IsDownsideGapThreeMethods(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 58:
            PatternDetected = IsUpsideGapThreeMethods(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 59:
            PatternDetected = IsOnNeck(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 60:
            PatternDetected = IsInNeck(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 61:
            PatternDetected = IsBearishThrusting(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 62:
            PatternDetected = IsMatHold(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 63:
            PatternDetected = IsDoji(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 64:
            PatternDetected = IsBullishEngulfingBodyOnly(sc, PatternsFinderSettings, sc.CurrentIndex);
            break;
        case 65:
            PatternDetected = IsBox(sc, PatternsFinderSettings, sc.CurrentIndex, r_DrawingNumberForLastBar);
            break;
        }

        if (PatternDetected)
        {
            sc.Subgraph[Index][sc.CurrentIndex] = static_cast<float>(PatternToLookFor[Index]);

            if (Input_DisplayText.GetYesNo() && !sc.HideStudy)
            {
                SCString DisplayTextStringCopy = DisplayTextString;

                PatternCodesToDisplay = true;

                if (DisplayNumericValue)
                    DisplayTextString.Format("%s%.2d%s", DisplayTextStringCopy.GetChars(), PatternToLookFor[Index], "\r\n");
                else
                    DisplayTextString.Format("%s%s%s", DisplayTextStringCopy.GetChars(), CandleStickPatternNames[PatternToLookFor[Index]][1], "\r\n");
            }
        }
    }

    if (PatternCodesToDisplay && sc.Index < sc.ArraySize - 1)
    {
        s_UseTool Tool;

        Tool.ChartNumber = sc.ChartNumber;
        Tool.DrawingType = DRAWING_TEXT;
        // Tool.LineNumber;
        Tool.BeginIndex = sc.CurrentIndex;
        Tool.Region = sc.GraphRegion;

        if (Input_DisplayAboveCandle.GetYesNo())
        {
            Tool.BeginValue = sc.High[sc.Index] + ((sc.High[sc.Index] - sc.Low[sc.Index]) * Input_Distance.GetInt() * 0.01f);
            Tool.TextAlignment = DT_CENTER | DT_BOTTOM;
        }
        else
        {
            Tool.BeginValue = sc.Low[sc.Index] - ((sc.High[sc.Index] - sc.Low[sc.Index]) * Input_Distance.GetInt() * 0.01f);
            Tool.TextAlignment = DT_CENTER | DT_TOP;
        }

        Tool.Color = Subgraph_Pattern1.PrimaryColor;
        Tool.FontBackColor = Subgraph_Pattern1.SecondaryColor;
        Tool.FontSize = Subgraph_Pattern1.LineWidth;
        Tool.FontBold = TRUE;
        Tool.Text.Format("%s", DisplayTextString.GetChars());
        Tool.AddMethod = UTAM_ADD_ALWAYS;

        sc.UseTool(Tool);
    }
    else if (PatternCodesToDisplay && sc.Index == sc.ArraySize - 1) // last bar in chart
    {
        s_UseTool Tool;

        Tool.ChartNumber = sc.ChartNumber;
        Tool.DrawingType = DRAWING_TEXT;
        if (r_DrawingNumberForLastBar != 0)
            Tool.LineNumber = r_DrawingNumberForLastBar;

        Tool.BeginIndex = sc.CurrentIndex;
        Tool.Region = sc.GraphRegion;

        if (Input_DisplayAboveCandle.GetYesNo())
        {
            Tool.BeginValue = sc.High[sc.Index] + ((sc.High[sc.Index] - sc.Low[sc.Index]) * Input_Distance.GetInt() * 0.01f);
            Tool.TextAlignment = DT_CENTER | DT_BOTTOM;
        }
        else
        {
            Tool.BeginValue = sc.Low[sc.Index] - ((sc.High[sc.Index] - sc.Low[sc.Index]) * Input_Distance.GetInt() * 0.01f);
            Tool.TextAlignment = DT_CENTER | DT_TOP;
        }

        Tool.Color = Subgraph_Pattern1.PrimaryColor;
        Tool.FontBackColor = Subgraph_Pattern1.SecondaryColor;
        Tool.FontSize = Subgraph_Pattern1.LineWidth;
        Tool.FontBold = TRUE;

        if (DisplayTextString.GetLength() == 0)
            DisplayTextString = " ";

        Tool.Text.Format("%s", DisplayTextString.GetChars());

        Tool.AddMethod = UTAM_ADD_OR_ADJUST;

        sc.UseTool(Tool);

        r_DrawingNumberForLastBar = Tool.LineNumber;
    }

    if (PatternCodesToDisplay)
    {
        // draw box

        SCString msg;

        sc.AddMessageToLog(msg, 1);
        const int k_Box_NUM_OF_CANDLES = 8; // number of previous candles to calculate candle strength
        const double k_Box_SimilarityPercent = 15;
        SCBaseDataRef InData = sc.BaseData;

        double BoxHighs = 0;
        double BoxLows = 0;
        double high = 0;
        double low = 0;
        int &r_LineNumber = sc.GetPersistentInt(1);
        if (sc.IsFullRecalculation)

        {
            for (int i = 1; i < k_Box_NUM_OF_CANDLES + 1; i++)
            {

                BoxHighs = BoxHighs + InData[SC_HIGH][sc.Index - i];
                BoxLows = BoxLows + InData[SC_LOW][sc.Index - i];
                msg.Format("BoxHighs %f", BoxHighs);
                sc.AddMessageToLog(msg, 1);
                msg.Format("BoxLows %f", BoxLows);
                sc.AddMessageToLog(msg, 1);
            }

            s_UseTool ChartDrawing;
            ChartDrawing.Clear();
            ChartDrawing.AddMethod = UTAM_ADD_OR_ADJUST;
            // ChartDrawing.LineNumber = r_DrawingNumberForLastBar;
            // r_LineNumber = 0;
            if (r_LineNumber != 0)
                ChartDrawing.LineNumber = r_LineNumber;
            ChartDrawing.DrawingType = DRAWING_RECTANGLEHIGHLIGHT;
            ChartDrawing.AddAsUserDrawnDrawing = 1;
            ChartDrawing.AllowCopyToOtherCharts = 1;
            ChartDrawing.DrawOutlineOnly = 1;
            ChartDrawing.SecondaryColor = RGB(0, 255, 0);
            ChartDrawing.Color = RGB(0, 255, 0);
            // float BoxHigh = InData[SC_HIGH][index];
            // float BoxLow = InData[SC_LOW][index];
            // testing box highs here
            double BoxHigh = BoxHighs / k_Box_NUM_OF_CANDLES;
            double BoxLow = BoxLows / k_Box_NUM_OF_CANDLES;
            msg.Format("BoxHighs avg %f", BoxHigh);
            sc.AddMessageToLog(msg, 1);
            msg.Format("BoxLows avg %f", BoxLow);
            sc.AddMessageToLog(msg, 1);

            // trying to get a good box drawn below
            high = sc.GetHighest(InData[SC_OPEN], sc.CurrentIndex - 1, 7);
            low = sc.GetLowest(InData[SC_LAST], sc.CurrentIndex - 1, 7);
            // log this index pair to compare to isBox indexes of which calculations are based off of
            int BoxBeginIndex = sc.CurrentIndex - k_Box_NUM_OF_CANDLES;
            int BoxEndIndex = sc.CurrentIndex - 1;

            // ChartDrawing.BeginValue = high;
            // ChartDrawing.EndValue = low;

            ChartDrawing.BeginValue = BoxHigh;
            ChartDrawing.EndValue = BoxLow;
            ChartDrawing.BeginIndex = BoxBeginIndex;
            ChartDrawing.EndIndex = BoxEndIndex;
            bool BoxExtendable = false;
            if (sc.Index == ChartDrawing.EndIndex + 1)
            {
                msg.Format("box high %f", high);
                sc.AddMessageToLog(msg, 1);
                msg.Format("box low %f", low);
                sc.AddMessageToLog(msg, 1);
                msg.Format("next bar high %f", InData[SC_LAST][sc.Index]);
                sc.AddMessageToLog(msg, 1);
                msg.Format("next bar low %f", InData[SC_LOW][sc.Index]);
                sc.AddMessageToLog(msg, 1);

                // working on this extending logic below

                // if (IsNearEqual(InData[SC_HL][sc.Index], InData[SC_HL][ChartDrawing.EndIndex - 1], InData, sc.Index, k_Box_SimilarityPercent))
                // {
                //     BoxExtendable = true;
                // }
            }

            // if (BoxExtendable)
            // {
            //     msg.Format("extending box");
            //     sc.AddMessageToLog(msg, 1);
            //     ChartDrawing.EndDateTime.Clear();
            //     ChartDrawing.EndIndex = ChartDrawing.EndIndex + 1;
            //     sc.UseTool(ChartDrawing);
            // }
            int BoxLength = (ChartDrawing.EndIndex - ChartDrawing.BeginIndex) + 1;
            msg.Format("Box %i", BoxLength);
            ChartDrawing.Text = msg;
            sc.UseTool(ChartDrawing);
            r_LineNumber = ChartDrawing.LineNumber;
            sc.AddMessageToLog(msg, 1);

            // end box drawing

            return;
        }
    }
}

/*==========================================================================*/
inline double UpperWickLength(SCBaseDataRef InData, int index)
{
    double upperBoundary = max(InData[SC_LAST][index], InData[SC_OPEN][index]);

    double upperWickLength = InData[SC_HIGH][index] - upperBoundary;

    return upperWickLength;
}

/*==========================================================================*/
inline double LowerWickLength(SCBaseDataRef InData, int index)
{
    double lowerBoundary = min(InData[SC_LAST][index], InData[SC_OPEN][index]);

    double lowerWickLength = lowerBoundary - InData[SC_LOW][index];

    return lowerWickLength;
}

/*==========================================================================*/
inline double CandleLength(SCBaseDataRef InData, int index)
{
    return InData[SC_HIGH][index] - InData[SC_LOW][index];
}

/*==========================================================================*/
inline double BodyLength(SCBaseDataRef InData, int index)
{
    return fabs(InData[SC_OPEN][index] - InData[SC_LAST][index]);
}

/*==========================================================================*/
inline double PercentOfCandleLength(SCBaseDataRef InData, int index, double percent)
{
    return CandleLength(InData, index) * (percent / 100.0);
}

/*==========================================================================*/
inline double PercentOfBodyLength(SCBaseDataRef InData, int index, double percent)
{
    return BodyLength(InData, index) * percent / 100.0;
}

/*==========================================================================*/
const int k_Body_NUM_OF_CANDLES = 5; // number of previous candles to calculate body strength

inline bool IsBodyStrong(SCBaseDataRef InData, int index)
{
    // detecting whether candle has a strong body or not
    bool ret_flag = false;

    // calculating average length of bodies of last NUM_OF_CANDLES
    float mov_aver = 0;
    for (int i = 1; i < k_Body_NUM_OF_CANDLES + 1; i++)
    {
        mov_aver += static_cast<float>(BodyLength(InData, index - i));
    }
    mov_aver /= k_Body_NUM_OF_CANDLES;

    // compare with length of current body with average length.
    if (BodyLength(InData, index) > mov_aver)
    {
        ret_flag = true;
    }
    return ret_flag;
}

/*==========================================================================*/
const int k_Candle_NUM_OF_CANDLES = 5; // number of previous candles to calculate candle strength
const double k_CandleStrength_Multiplier = 1.0;

inline bool IsCandleStrength(SCBaseDataRef InData, int index)
{
    // detecting whether candle has a strong body or not
    bool ret_flag = false;

    // calculating average length of bodies of last NUM_OF_CANDLES
    float mov_aver = 0;
    for (int i = 1; i < k_Candle_NUM_OF_CANDLES + 1; i++)
        mov_aver += static_cast<float>(CandleLength(InData, index - i));

    mov_aver /= k_Candle_NUM_OF_CANDLES;

    // compare with length of body with average
    if (CandleLength(InData, index) > mov_aver * k_CandleStrength_Multiplier)
    {
        ret_flag = true;
    }
    return ret_flag;
}

/*==========================================================================*/

int DetermineTrendForCandlestickPatterns(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &PatternsFinderSettings, int index, int num_of_candles)
{
    // detecting trend
    // index: index of the last candle in trend
    // num_of_candles: minimum number of candles required

    const double UptrendPercent = 1.0;
    const double DowntrendPercent = -1.0;

    // Using linear regression to estimate the slope
    SCBaseDataRef InData = sc.BaseData;
    double sumx = 0.0;
    double sumy = 0.0;
    double sumxx = 0.0;
    double sumyy = 0.0;
    double sumxy = 0.0;

    for (int IndexOffset = 1; IndexOffset <= num_of_candles; IndexOffset++)
    {
        double value = InData[SC_HL_AVG][index - (IndexOffset - 1)];

        sumx += -IndexOffset;
        sumy += value;
        sumxx += IndexOffset * IndexOffset;
        sumyy += value * value;
        sumxy += -IndexOffset * value;
    }

    double n = double(num_of_candles);
    double Sxy = n * sumxy - sumx * sumy;
    double Sxx = n * sumxx - sumx * sumx;

    double Slope = Sxy / Sxx; // slope value

    // estimate the value per point:

    double high = sc.GetHighest(InData[SC_HIGH], index, PatternsFinderSettings.PriceRangeNumberOfBars);

    double low = sc.GetLowest(InData[SC_LOW], index, PatternsFinderSettings.PriceRangeNumberOfBars);

    double range = high - low;

    double valuePerPoint = range * PatternsFinderSettings.PriceRangeMultiplier;

    // detect trend

    double CorrectSlope = Slope / valuePerPoint;

    if (CorrectSlope > UptrendPercent)
    {
        return CANDLESTICK_TREND_UP;
    }
    else if (CorrectSlope < DowntrendPercent)
    {
        return CANDLESTICK_TREND_DOWN;
    }
    else
    {
        return CANDLESTICK_TREND_FLAT;
    }
}

/*==========================================================================*/

inline bool IsDoji(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    const double Doji_BodyPercent = 5.0;
    SCBaseDataRef InData = sc.BaseData;
    if (BodyLength(InData, index) <= PercentOfCandleLength(InData, index, Doji_BodyPercent))
    {
        return true;
    }

    return false;
}

/*==========================================================================*/
inline bool IsWhiteCandle(SCBaseDataRef InData, int index)
{
    return InData[SC_LAST][index] > InData[SC_OPEN][index];
}

/*==========================================================================*/
inline bool IsBlackCandle(SCBaseDataRef InData, int index)
{
    return InData[SC_LAST][index] < InData[SC_OPEN][index];
}

/*==========================================================================*/
inline bool IsNearEqual(double value1, double value2, SCBaseDataRef InData, int index, double percent)
{
    return abs(value1 - value2) < PercentOfCandleLength(InData, index, percent);
}
/*==========================================================================*/
inline bool IsInsideCandle(float prevHigh, float currentHigh, float prevLow, float currentLow, int index)
{
    return currentHigh < prevHigh && currentLow > prevLow;
}

/*==========================================================================*/
inline bool IsUpperWickSmall(SCBaseDataRef InData, int index, double percent)
{
    return UpperWickLength(InData, index) < PercentOfCandleLength(InData, index, percent);
}

/*==========================================================================*/
inline bool IsLowerWickSmall(SCBaseDataRef InData, int index, double percent)
{
    return LowerWickLength(InData, index) < PercentOfCandleLength(InData, index, percent);
}

/*==========================================================================*/

bool IsHammer(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{

    const double LowerWickPercent = 200.0;
    const double UpperWickPercent = 7.0;

    // HAMMER
    // 1. Downtrend
    // 2. Body [index] of the candle in the upper part of the candle
    // 3. Lower wick [index] of candle is 2 longer then candle body
    // 4. Upper wick [index] of candle is either absent or small
    SCBaseDataRef InData = sc.BaseData;

    bool ret_flag = false;

    if (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_DOWN) // downtrend
    {
        // check that body is in the upper part of the candle
        if (((InData[SC_HIGH][index] - InData[SC_OPEN][index]) < (InData[SC_OPEN][index] - InData[SC_LOW][index])) && ((InData[SC_HIGH][index] - InData[SC_LAST][index]) < (InData[SC_LAST][index] - InData[SC_LOW][index])) && (InData[SC_OPEN][index] != InData[SC_LAST][index]))
        {

            if ( // check of the length of the lower wick
                IsLowerWickSmall(InData, index, LowerWickPercent) &&
                // check of the length of the upper wick
                IsUpperWickSmall(InData, index, UpperWickPercent))
            {
                ret_flag = true;
            }
        }
    }
    return ret_flag;
}

/*==========================================================================*/

const double k_HangingMan_LowerWickPercent = 200.0;
const double k_HangingMan_UpperWickPercent = 7.0;

bool IsHangingMan(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // HANGING MAN
    // 1. Uptrend
    // 2. Body [index] is in the upper part of the candle
    // 3. Lower wick [index] is 2 times longer then the body
    // 4. Upper wick [index] is either absent or small
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_UP) // check uptrend
    {
        // is body in the upper part of the candle
        if (((InData[SC_HIGH][index] - InData[SC_OPEN][index]) < (InData[SC_OPEN][index] - InData[SC_LOW][index])) && ((InData[SC_HIGH][index] - InData[SC_LAST][index]) < (InData[SC_LAST][index] - InData[SC_LOW][index])) && (InData[SC_OPEN][index] != InData[SC_LAST][index]))
        {
            // check the length of lower wick
            if (IsLowerWickSmall(InData, index, k_HangingMan_LowerWickPercent))
            {
                // check the length of the upper wick
                if (IsUpperWickSmall(InData, index, k_HangingMan_UpperWickPercent))
                {
                    ret_flag = true;
                }
            }
        }
    }
    return ret_flag;
}

/*==========================================================================*/
// Reference: http://www.investopedia.com/terms/b/bullishengulfingpattern.asp
bool IsBullishEngulfing(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_DOWN) // down
    {
        if (InData[SC_LAST][index - 1] < InData[SC_OPEN][index - 1] && InData[SC_LAST][index] > InData[SC_OPEN][index])
        {
            if ((InData[SC_HIGH][index] > InData[SC_HIGH][index - 1]) &&
                (InData[SC_LOW][index] < InData[SC_LOW][index - 1]) &&
                (InData[SC_LAST][index] > InData[SC_OPEN][index - 1]) &&
                (InData[SC_OPEN][index] < InData[SC_LAST][index - 1]))
            {
                ret_flag = true;
            }
        }
    }
    return ret_flag;
}

/*==========================================================================*/
// Reference: http://www.investopedia.com/terms/b/bearishengulfingp.asp
bool IsBearishEngulfing(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_UP) // up
    {
        if (InData[SC_LAST][index - 1] > InData[SC_OPEN][index - 1] && InData[SC_LAST][index] < InData[SC_OPEN][index])
        {
            if ((InData[SC_HIGH][index] > InData[SC_HIGH][index - 1]) &&
                (InData[SC_LOW][index] < InData[SC_LOW][index - 1]) &&
                (InData[SC_OPEN][index] > InData[SC_LAST][index - 1]) &&
                (InData[SC_LAST][index] < InData[SC_OPEN][index - 1]))
            {
                ret_flag = true;
            }
        }
    }
    return ret_flag;
}
/*==========================================================================*/
bool IsBullishEngulfingBodyOnly(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_DOWN) // down
    {
        if (InData[SC_LAST][index - 1] < InData[SC_OPEN][index - 1] && InData[SC_LAST][index] > InData[SC_OPEN][index])
        {
            if ((InData[SC_LAST][index] > InData[SC_OPEN][index - 1]) &&
                (InData[SC_OPEN][index] < InData[SC_LAST][index - 1]))
            {
                ret_flag = true;
            }
        }
    }
    return ret_flag;
}
/*==========================================================================*/

bool IsBearishEngulfingBodyOnly(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_UP) // up
    {
        if (InData[SC_LAST][index - 1] > InData[SC_OPEN][index - 1] && InData[SC_LAST][index] < InData[SC_OPEN][index])
        {
            if ((InData[SC_OPEN][index] > InData[SC_LAST][index - 1]) &&
                (InData[SC_LAST][index] < InData[SC_OPEN][index - 1]))
            {
                ret_flag = true;
            }
        }
    }
    return ret_flag;
}
/*==========================================================================*/
const double k_DarkCloudCover_OverlapPercent = 50.0;

bool IsDarkCloudCover(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // DARK CLOUD COVER
    // 1. Uptrend
    // 2. Strong white body [index-1]
    // 3. Open [index] is higher then High of candle [index-1]
    // 4. Close [index] is lower then OVERLAP_PERCENT of white body of candle [index-1]

    /*1. Market is characterized by an uptrend.
    2. We see a long white candlestick in the first day.
    3. Then we see a black body characterized by an open above the high of the previous day on the second day.
    4. The second black candlestick closes within and below the midpoint of the previous white body.*/

    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (
        (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_UP)                              // uptrend
        && IsWhiteCandle(InData, index - 1)                                                                                                  // check for white body
        && IsBodyStrong(InData, index - 1) && IsBlackCandle(InData, index)                                                                   // 0 candle is black
        && (InData[SC_OPEN][index] > InData[SC_HIGH][index - 1])                                                                             // open 0 is higher then high of -1
        && (InData[SC_LAST][index] < (InData[SC_LAST][index - 1] - PercentOfBodyLength(InData, index - 1, k_DarkCloudCover_OverlapPercent))) // check for the overlap between white body and black OVERLAP_PERCENT
    )
    {
        ret_flag = true;
    }

    return ret_flag;
}

/*==========================================================================*/
const double k_PiercingLine_OverlapPercent = 50.0;

bool IsPiercingLine(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // PIERCING LINE
    // 1. Downtrend
    // 2. Strong black body [index-1]
    // 3. Open [index] less than low of candle [index-1]
    // 4. Close [index] is higher than white body of candle [index-1] by OverlapPercent
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_DOWN) // downtrend
    {
        if (IsBlackCandle(InData, index - 1)) // check for black body, -1th candle is black
        {
            if (IsWhiteCandle(InData, index) &&                       // 0th candle is white
                (InData[SC_OPEN][index] < InData[SC_LOW][index - 1])) // open of 0 the below low of -1th
            {
                // check for the overlap between black body and white by OverlapPercent
                if (InData[SC_LAST][index] > (InData[SC_OPEN][index - 1] - PercentOfBodyLength(InData, index - 1, k_PiercingLine_OverlapPercent)))
                {
                    if (IsBodyStrong(InData, index - 1)) // strong body of -1th candle
                    {
                        ret_flag = true;
                    }
                }
            }
        }
    }
    return ret_flag;
}

/*==========================================================================*/
const double k_MorningStar_OverlapPercent = 50.0;

bool IsMorningStar(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // MORNING STAR
    // 1. Downtrend
    // 2. Strong black body of candle [index-2]
    // 3. Any weak body of candle [index-1], but not Doji
    // 4. Strong white body of candle [index] overlap more then OVERLAP_PERCENT of the body of candle [index-2]

    /*1. Market is characterized by downtrend.
    2. We see a long black candlestick in the first day.
    3. Then we see a small body on the second day gapping in the direction of the previous downtrend.
    4. Finally we see a white candlestick on the third day*/
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (
        (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_DOWN) && IsBlackCandle(InData, index - 2) && IsBodyStrong(InData, index - 2) && (InData[SC_OPEN][index - 1] < InData[SC_LOW][index - 2]) // body of -1 candle below low of -2 candle
        && (InData[SC_LAST][index - 1] < InData[SC_LOW][index - 2])
        //&& !IsDoji(sc, settings, index-1) // -1 candle is not Doji
        && !IsBodyStrong(InData, index - 1)                                                                                           // body of -1 candle is weak
        && IsWhiteCandle(InData, index) && IsBodyStrong(InData, index) && (InData[SC_OPEN][index] < InData[SC_LAST][index - 2])       // body of 0 candle starts below the body of -2 candle
        && (InData[SC_LAST][index] > (InData[SC_OPEN][index - 2] - PercentOfBodyLength(InData, index, k_MorningStar_OverlapPercent))) // body of the candle 0 overlaps the body of the candle -2
    )
    {
        ret_flag = true;
    }
    return ret_flag;
}

/*==========================================================================*/
const double k_EveningStar_OverlapPercent = 50.0;

bool IsEveningStar(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // EVENING STAR
    // 1. Uptrend
    // 2. Strong white body of candle [index-2]
    // 3. Any weak body of candle [index-1], but not Doji
    // 4. Strong black body of candle [index] overlaps more then OVERLAP_PERCENT of body of candle [index-2]. -I have not found any info about overlapping
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_UP) // check for uptrend
    {
        if (IsWhiteCandle(InData, index - 2)) // body of candle -2 is white
        {
            if (IsBodyStrong(InData, index - 2)) // body of candle -2 is strong
            {
                if ((InData[SC_OPEN][index - 1] > InData[SC_HIGH][index - 2]) && // body of candle -1 higher then maximum. - This line does not correspond to what I found online it should not matter, the gap should be between the bodies.
                    (InData[SC_LAST][index - 1] > InData[SC_LOW][index - 2])
                    //&&	  !IsDoji(sc,settings,index-1)	// candle -1 is not Doji
                )
                {
                    if (!IsBodyStrong(InData, index - 1)) // body of the candle -1 is weak
                    {
                        if (IsBlackCandle(InData, index) &&                                                                                                 // body of the candle 0 is black
                            (InData[SC_OPEN][index] > InData[SC_LAST][index - 2]) &&                                                                        // body of the candle 0 starts higher then body of candle -2
                            (InData[SC_LAST][index] < (InData[SC_LAST][index - 2] - PercentOfBodyLength(InData, index - 2, k_EveningStar_OverlapPercent)))) // body of candle 0 overlaps body of candle -2. Did not find written reference to this, but all images support this.
                        {
                            if (IsBodyStrong(InData, index)) // body of candle 0 is strong
                            {
                                ret_flag = true;
                            }
                        }
                    }
                }
            }
        }
    }
    return ret_flag;
}

/*==========================================================================*/
const double k_MorningDojiStar_OverlapPercent = 50.0;

bool IsMorningDojiStar(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // MORNING DOJI STAR
    // 1. Downtrend
    // 2. Strong black body of candle [index-2]
    // 3. [index-1] candle is Doji. (2nd day is a doji which gaps below the 1st day's close.)
    // 4. Strong white body of candle [index] overlap more then OVERLAP_PERCENT of body of the candle [index-2]
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (
        (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_DOWN)                             // check for downtrend
        && IsBlackCandle(InData, index - 2)                                                                                                   // body of the candle -2 is black
        && IsBodyStrong(InData, index - 2)                                                                                                    // body of the candle -2 is strong
        && (InData[SC_HIGH][index - 1] < InData[SC_LAST][index - 2])                                                                          // the -1 candle is below the close of candle -2
        && IsDoji(sc, settings, index - 1)                                                                                                    // -1 candle is Doji
        && IsWhiteCandle(InData, index)                                                                                                       // body of the candle 0 is white
        && (InData[SC_OPEN][index] < InData[SC_LAST][index - 2])                                                                              // body of the candle 0 starts below the body of candle -2
        && (InData[SC_LAST][index] > (InData[SC_OPEN][index - 2] - PercentOfBodyLength(InData, index - 2, k_MorningDojiStar_OverlapPercent))) // body of the candle 0 overlaps body of the candle -2
        && IsBodyStrong(InData, index)                                                                                                        // body of the candle 0 is strong
    )
    {
        ret_flag = true;
    }
    return ret_flag;
}

/*==========================================================================*/
const double k_EveningDojiStar_OverlapPercent = 50.0;

bool IsEveningDojiStar(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // EVENING DOJI STAR
    // 1. Uptrend
    // 2. Strong white body of candle [index-2]
    // 3. candle [index-1]  2nd day is a doji which gaps above the  [index-2] 1st day's close.
    // 4. Strong black body of candle [index]
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (
        (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_UP) // check for uptrend
        && IsWhiteCandle(InData, index - 2)                                                                     // body of the -2 candle is white
        && IsBodyStrong(InData, index - 2)                                                                      // body of th -2 candle is strong
        && InData[SC_OPEN][index - 1] > InData[SC_HIGH][index - 2]                                              // body of the -1 candle is higher then maximum of -2 candle
        && IsDoji(sc, settings, index - 1)                                                                      // -1 candle is Doji
        && IsBlackCandle(InData, index)                                                                         // body of the 0 candle is black
        && InData[SC_OPEN][index] > InData[SC_LAST][index - 2]                                                  // body of the 0 candle starts higher then body of -2 candle
        //&&(InData[SC_LAST][index]<(InData[SC_LAST][index-2]-PercentOfBodyLength(InData, index-2, k_EveningDojiStar_OverlapPercent))))	// body of the 0 candle overlaps the body of -2 candle //This is not a requirement
        && IsBodyStrong(InData, index) // body of candle 0 is strong
    )
    {
        ret_flag = true;
    }
    return ret_flag;
}

/*==========================================================================*/
const double k_BullishAbandonedBaby_OverlapPercent = 50.0;

bool IsBullishAbandonedBaby(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // BULLISH ABANDONED BABY
    // 1. Downtrend
    // 2. Strong black body of candle [index-2]
    // 3. Candle [index-1] - Doji
    // 4. Strong white body of candle [index] overlaps more then OVERLAP_PERCENT of the body of candle [index-2]. Is not included in web descriptions but is logical.
    // 5. Gap between -1 and 0 candles, -1 and -2 candles
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_DOWN) // check for downtrend
    {
        if (IsBlackCandle(InData, index - 2)) // body of candle -2 is black
        {
            if (IsBodyStrong(InData, index - 2)) // body of the candle -2 is strong
            {
                if ((InData[SC_OPEN][index - 1] < InData[SC_LOW][index - 2]) && // body of the candle -1 is below the minimum of candle -2
                    IsDoji(sc, settings, index - 1))                            // -1 candle is Doji
                {
                    if (IsWhiteCandle(InData, index) &&                                                                                                          // body of candle 0 is white
                        (InData[SC_OPEN][index] < InData[SC_LAST][index - 2]) &&                                                                                 // body of candle 0 starts below of the body of the candle -2
                        (InData[SC_LAST][index] > (InData[SC_OPEN][index - 2] - PercentOfBodyLength(InData, index - 2, k_BullishAbandonedBaby_OverlapPercent)))) // body of candle 0 overlaps with body of candle -2
                    {
                        if (IsBodyStrong(InData, index)) // body of candle 0 is strong
                        {
                            if ((InData[SC_LOW][index - 2] > InData[SC_HIGH][index - 1]) && // gap between candle -2 and -1
                                (InData[SC_LOW][index] > InData[SC_HIGH][index - 1]))       // gap between candle -0 and -1
                            {
                                ret_flag = true;
                            }
                        }
                    }
                }
            }
        }
    }
    return ret_flag;
}

/*==========================================================================*/
const double k_BearishAbandonedBaby_OverlapPercent = 50.0;

bool IsBearishAbandonedBaby(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // BEARISH ABANDONED BABY
    // 1. Uptrend
    // 2. Strong white body of candle [index-2]
    // 3. Weak body of candle [index-1]
    // 4. Candle [index-1] is Doji
    // 5. Strong black body of candle [index] overlaps more then OVERLAP_PERCENT of body of candle [index-2]
    // 6. Gap between candle -1 and 0, -1 and 2 candles
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_UP) // check for uptrend
    {
        if (IsWhiteCandle(InData, index - 2)) // body of candle -2 is white
        {
            if (IsBodyStrong(InData, index - 2)) // body of candle -2 is strong
            {
                if ((InData[SC_OPEN][index - 1] > InData[SC_HIGH][index - 2]) && // body of candle -1 is higher than maximum of candle -2
                    IsDoji(sc, settings, index - 1))                             // candle -1 is Doji
                {
                    if (IsBlackCandle(InData, index) &&                                                                                                          // body candle 0 is black
                        (InData[SC_OPEN][index] > InData[SC_LAST][index - 2]) &&                                                                                 // body of candle 0 starts higher then body of candle -2
                        (InData[SC_LAST][index] < (InData[SC_LAST][index - 2] - PercentOfBodyLength(InData, index - 2, k_BearishAbandonedBaby_OverlapPercent)))) // body of candle 0 overlaps body of candle -2
                    {
                        if (IsBodyStrong(InData, index)) // body of candle 0 is strong
                        {
                            if ((InData[SC_HIGH][index - 2] < InData[SC_LOW][index - 1]) && // gap between -2 and -1 candle
                                (InData[SC_HIGH][index] < InData[SC_LOW][index - 1]))       // gap between -0 and -1 candle
                            {
                                ret_flag = true;
                            }
                        }
                    }
                }
            }
        }
    }
    return ret_flag;
}

/*==========================================================================*/
const double k_ShootingStar_LowerWickPercent = 7.0;
const double k_ShootingStar_UpperWickPercent = 300.0;

bool IsShootingStar(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // SHOOTING STAR
    // 1. Uptrend
    // 2. Small body of candle [index] is in the lower part of candle
    // 3. Upper wick of the candle [index] is  at least three times as long as the body
    // 4. Lower wick [index] of the candle is either absent or small
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_UP) // uptrend
    {
        if (!IsBodyStrong(InData, index)) // weak body of the candle 0
        {
            // check that the body of the candle is in the lower part of the candle
            if (((InData[SC_HIGH][index] - InData[SC_OPEN][index]) > (InData[SC_OPEN][index] - InData[SC_LOW][index])) && ((InData[SC_HIGH][index] - InData[SC_LAST][index]) > (InData[SC_LAST][index] - InData[SC_LOW][index])))
            {
                // Upper wick is 3 times longer then the body
                if (UpperWickLength(InData, index) >= PercentOfBodyLength(InData, index, k_ShootingStar_UpperWickPercent))
                {
                    // Lower wick is insignificant
                    if (IsLowerWickSmall(InData, index, k_ShootingStar_LowerWickPercent))
                    {
                        ret_flag = true;
                    }
                }
            }
        }
    }
    return ret_flag;
}

/*==========================================================================*/
const double k_InvertedHammer_LowerWickPercent = 7.0;
const double k_InvertedHammer_UpperWickPercent = 200.0;

bool IsInvertedHammer(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // INVERTED HAMMER
    // 1. Downtrend
    // 2. Small body of candle [index] is in the lower part of the candle
    // 3. The upper shadow is no more than two times as long as the body
    // 4. Lower wick [index] of the candle is either absent or small
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_DOWN) // downtrend
    {
        if (!IsBodyStrong(InData, index)) // candle 0 has weak body
        {
            // check that body is in the lower part of the candle
            if (((InData[SC_HIGH][index] - InData[SC_OPEN][index]) > (InData[SC_OPEN][index] - InData[SC_LOW][index])) && ((InData[SC_HIGH][index] - InData[SC_LAST][index]) > (InData[SC_LAST][index] - InData[SC_LOW][index])) && !IsDoji(sc, settings, index)) // candle is not Doji
            {
                // The upper shadow is no more than two times as long as the body.
                if (UpperWickLength(InData, index) <= PercentOfBodyLength(InData, index, k_InvertedHammer_UpperWickPercent))
                {
                    // lower wick is insignificant
                    if (IsLowerWickSmall(InData, index, k_InvertedHammer_LowerWickPercent))
                    {
                        ret_flag = true;
                    }
                }
            }
        }
    }
    return ret_flag;
}
/*==========================================================================*/

bool IsBearishHarami(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // BEARISH HARAMI
    // 1. Uptrend
    // 2. Strong body of candle [index-1]
    // 3. Weak body of candle [index] does not extend beyond the limits of the body of candle [index-1]
    // 4. Candle [index] is not Doji
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_UP) // Uptrend
    {
        if (IsBodyStrong(InData, index - 1)) // Strong body of candle -1
        {
            if (!IsDoji(sc, settings, index)) // candle 0 is not Doji
            {
                if (!IsBodyStrong(InData, index)) // weak body of candle 0
                {
                    if (InData[SC_OPEN][index - 1] > InData[SC_LAST][index - 1]) // part of a check that one body does not extend beyond the limits of the other body
                    {
                        if (InData[SC_OPEN][index] > InData[SC_LAST][index]) // part of a check that one body does not extend beyond the limits of the other body
                        {
                            // body of the candle 0 does not extend beyond the limits of the body of candle -1
                            if ((InData[SC_OPEN][index - 1] >= InData[SC_OPEN][index]) &&
                                (InData[SC_LAST][index - 1] <= InData[SC_LAST][index]))
                            {
                                ret_flag = true;
                            }
                        }
                        else // part of a check that one body does not extend beyond the limits of the other body
                        {
                            // body of the candle 0 does not extend beyond the limits of the body of candle -1
                            if ((InData[SC_OPEN][index - 1] >= InData[SC_LAST][index]) &&
                                (InData[SC_LAST][index - 1] <= InData[SC_OPEN][index]))
                            {
                                ret_flag = true;
                            }
                        }
                    }
                    else // part of a check that one body does not extend beyond the limits of the other body
                    {
                        if (InData[SC_OPEN][index] > InData[SC_LAST][index]) // part of a check that one body does not extend beyond the limits of the other body
                        {
                            // body of the candle 0 does not extend beyond the limits of the body of candle -1
                            if ((InData[SC_LAST][index - 1] >= InData[SC_OPEN][index]) &&
                                (InData[SC_OPEN][index - 1] <= InData[SC_LAST][index]))
                            {
                                ret_flag = true;
                            }
                        }
                        else // part of a check that one body does not extend beyond the limits of the other body
                        {
                            // body of the candle 0 does not extend beyond the limits of the body of candle -1
                            if ((InData[SC_LAST][index - 1] >= InData[SC_LAST][index]) &&
                                (InData[SC_OPEN][index - 1] <= InData[SC_OPEN][index]))
                            {
                                ret_flag = true;
                            }
                        }
                    }
                }
            }
        }
    }
    return ret_flag;
}
/*==========================================================================*/

bool IsBullishHarami(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // BULLISH HARAMI
    // 1. Downtrend
    // 2. Strong body of candle [index-1]
    // 3. Weak body of candle [index] does not extend beyond the limits of the body of candle [index-1]
    // 4. Candle [index] is not Doji
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_DOWN) // downtrend
    {
        if (IsBodyStrong(InData, index - 1)) // Strong body of candle [index-1]
        {
            if (!IsDoji(sc, settings, index)) // candle 0 is not Doji
            {
                if (!IsBodyStrong(InData, index)) // weak body of candle 0
                {
                    if (InData[SC_OPEN][index - 1] > InData[SC_LAST][index - 1]) // part of a check that one body does not extend beyond the limits of the other body
                    {
                        if (InData[SC_OPEN][index] > InData[SC_LAST][index]) // part of a check that one body does not extend beyond the limits of the other body
                        {
                            // body of the candle 0 does not extend beyond the limits of the body of candle -1
                            if ((InData[SC_OPEN][index - 1] >= InData[SC_OPEN][index]) &&
                                (InData[SC_LAST][index - 1] <= InData[SC_LAST][index]))
                            {
                                ret_flag = true;
                            }
                        }
                        else // part of a check that one body does not extend beyond the limits of the other body
                        {
                            // body of the candle 0 does not extend beyond the limits of the body of candle -1
                            if ((InData[SC_OPEN][index - 1] >= InData[SC_LAST][index]) &&
                                (InData[SC_LAST][index - 1] <= InData[SC_OPEN][index]))
                            {
                                ret_flag = true;
                            }
                        }
                    }
                    else // part of a check that one body does not extend beyond the limits of the other body
                    {
                        if (InData[SC_OPEN][index] >= InData[SC_LAST][index]) // part of a check that one body does not extend beyond the limits of the other body
                        {
                            // body of the candle 0 does not extend beyond the limits of the body of candle -1
                            if ((InData[SC_LAST][index - 1] >= InData[SC_OPEN][index]) &&
                                (InData[SC_OPEN][index - 1] <= InData[SC_LAST][index]))
                            {
                                ret_flag = true;
                            }
                        }
                        else // part of a check that one body does not extend beyond the limits of the other body
                        {
                            // body of the candle 0 does not extend beyond the limits of the body of candle -1
                            if ((InData[SC_LAST][index - 1] >= InData[SC_LAST][index]) &&
                                (InData[SC_OPEN][index - 1] <= InData[SC_OPEN][index]))
                            {
                                ret_flag = true;
                            }
                        }
                    }
                }
            }
        }
    }
    return ret_flag;
}
/*==========================================================================*/

bool IsBearishHaramiCross(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // BEARISH HARAMI CROSS
    // 1. Uptrend
    // 2. Strong body of candle [index-1]
    // 3. Candle [index] is Doji
    // 4. Body of candle [index] does not extend beyond the limits of the body of the candle [index-1]
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_UP) // uptrend
    {
        if (IsBodyStrong(InData, index - 1)) // strong body of the candle -1
        {
            if (IsDoji(sc, settings, index)) // candle 0 is Doji
            {
                if (InData[SC_OPEN][index - 1] > InData[SC_LAST][index - 1]) // part of a check that one body does not extend beyond the limits of the other body
                {
                    // body of the candle 0 does not extend beyond the limits of the body of candle -1
                    if ((InData[SC_OPEN][index - 1] > InData[SC_LAST][index]) &&
                        (InData[SC_LAST][index - 1] < InData[SC_LAST][index]))
                    {
                        ret_flag = true;
                    }
                }
                else // part of a check that one body does not extend beyond the limits of the other body
                {
                    // body of the candle 0 does not extend beyond the limits of the body of candle -1
                    if ((InData[SC_LAST][index - 1] >= InData[SC_LAST][index]) &&
                        (InData[SC_OPEN][index - 1] <= InData[SC_LAST][index]))
                    {
                        ret_flag = true;
                    }
                }
            }
        }
    }
    return ret_flag;
}
/*==========================================================================*/

bool IsBullishHaramiCross(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // BULLISH HARAMI CROSS
    // 1. Downtrend
    // 2. Strong body of the candle [index-1]
    // 3. candle [index] is Doji
    // 4. Candle [index] does not extend beyond the limits of the body of the candle [index-1]
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_DOWN) // Downtrend
    {
        if (IsBodyStrong(InData, index - 1)) // strong body of the candle -1
        {
            if (IsDoji(sc, settings, index)) // candle 0 is Doji
            {
                if (InData[SC_OPEN][index - 1] > InData[SC_LAST][index - 1]) // part of a check that one body does not extend beyond the limits of the other body
                {
                    // body of the candle 0 does not extend beyond the limits of the body of candle -1
                    if ((InData[SC_OPEN][index - 1] > InData[SC_LAST][index]) &&
                        (InData[SC_LAST][index - 1] < InData[SC_LAST][index]))
                    {
                        ret_flag = true;
                    }
                }
                else // part of a check that one body does not extend beyond the limits of the other body
                {
                    // body of the candle 0 does not extend beyond the limits of the body of candle -1
                    if ((InData[SC_LAST][index - 1] > InData[SC_LAST][index]) &&
                        (InData[SC_OPEN][index - 1] < InData[SC_LAST][index]))
                    {
                        ret_flag = true;
                    }
                }
            }
        }
    }
    return ret_flag;
}
/*==========================================================================*/
const int k_TweezerTop_PAST_INDEX = 3;
const double k_TweezerTop_SimilarityPercent = 7.0;

bool IsTweezerTop(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // TWEEZER TOP
    // 1. Maximum of the candle [index] is equal to the maximum of one of the [index-X] candles (where X is from 1 to PAST_INDEX)
    // 2. uptrend for the candle [index-X]

    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    // Iterating previous candles
    /*for (int i=1; i<k_TweezerTop_PAST_INDEX+1;i++)
    {
    // Searching for a candle with matching maximum
    if(IsNearEqual(InData[SC_HIGH][index], InData[SC_HIGH][index-i], InData, index, k_TweezerTop_SimilarityPercent))
    {
    // checking the trend
    if(settings.UseTrendDetection == false || DetectTendency(sc, settings,index-i,k_TweezerTop_TrendArea) == 1)
    {
    ret_flag = true;
    break;
    }
    }
    }*/

    //-----------------------------------------------
    // 1. 1st day consists of a long body candle.
    // 2. 2nd day consists of a short body candle that has a high equal to the prior day's high.
    // 3. The color of each candle body is not considered in the matching of this pattern.

    if (
        (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_UP) && IsNearEqual(InData[SC_HIGH][index], InData[SC_HIGH][index - 1], InData, index, k_TweezerTop_SimilarityPercent) && IsBodyStrong(InData, index - 1) && !IsBodyStrong(InData, index))
    {
        ret_flag = true;
    }

    return ret_flag;
}
/*==========================================================================*/
const int k_TweezerBottom_PAST_INDEX = 3;
const double k_TweezerBottom_SimilarityPercent = 7.0;

bool IsTweezerBottom(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // TWEEZER BOTTOM
    // 1. Minimum of the candle [index] matches the minimum of one of the candles [index-X] (where X is from 1 to PAST_INDEX)
    // 2. Downtrend for the candle [index-X]
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    // Iterating previous candles
    // for (int i=1; i<k_TweezerBottom_PAST_INDEX+1;i++)
    // {
    // Searching for a candle with matching minimum
    // if(IsNearEqual(InData[SC_LOW][index], InData[SC_LOW][index-i], InData, index, k_TweezerBottom_SimilarityPercent))
    // {
    // Checking the trend
    // if(settings.UseTrendDetection == false || DetectTendency(sc, settings,index-i,k_TweezerBottom_TrendArea) == -1)
    // {
    // ret_flag = true;
    // break;
    // }
    // }
    // }

    // 1. 1st day consists of a long body candle.
    // 2. 2nd day consists of a short body candle that has a low equal to the prior day's low.
    // 3. The color of each candle body is not considered in the matching of this pattern.

    if (
        (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_DOWN) && IsNearEqual(InData[SC_LOW][index], InData[SC_LOW][index - 1], InData, index, k_TweezerBottom_SimilarityPercent) && IsBodyStrong(InData, index - 1) && !IsBodyStrong(InData, index))
    {
        ret_flag = true;
    }
    return ret_flag;
}
/*==========================================================================*/
const double k_BearishBeltHoldLine_LowerWickPercent = 7.0;
const double k_BearishBeltHoldLine_SimilarityPercent = 7.0;

bool IsBearishBeltHoldLine(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // BEARISH BELT HOLD LINE
    // 1. Uptrend
    // 2. Long black day where the open is equal to the high.
    // 3. No upper shadow.
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (
        (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_UP)                // uptrend
        && IsBlackCandle(InData, index)                                                                                        // Black body of the candle 0
        && IsBodyStrong(InData, index)                                                                                         // Strong body of candle0
        && IsNearEqual(InData[SC_HIGH][index], InData[SC_OPEN][index], InData, index, k_BearishBeltHoldLine_SimilarityPercent) // OPEN = HIGH
    )
    {
        ret_flag = true;
    }
    return ret_flag;
}
/*==========================================================================*/
const double k_BullishBeltHoldLine_UpperWickPercent = 7.0;
const double k_BullishBeltHoldLine_SimilarityPercent = 7.0;

bool IsBullishBeltHoldLine(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // BULLISH BELT HOLD LINE
    // 1. Downtrend
    // 2. Long white day where the open is equal to the low.
    // 3. No lower shadow.
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (
        (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_DOWN)             // downtrend
        && IsWhiteCandle(InData, index)                                                                                       // white body of the candle 0
        && IsBodyStrong(InData, index)                                                                                        // Strong body of candle0
        && IsNearEqual(InData[SC_LOW][index], InData[SC_OPEN][index], InData, index, k_BullishBeltHoldLine_SimilarityPercent) // OPEN = LOW
    )
    {
        ret_flag = true;
    }

    return ret_flag;
}
/*==========================================================================*/

bool IsTwoCrows(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // UPSIDE-GAP TWO CROWS
    // 1. Uptrend
    // 2. White strong body of the candle [index-2]
    // 3. Candles [index-1] and [index] are black
    // 4. Gap between the bodies of candles  [index-2] and [index-1]
    // 5. The body of the candle [index] engulfs the body of the candle [index-1]
    // 6. 3rd day closes above the close of the 1st day.
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (
        (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_UP)        // uptrend
        && IsWhiteCandle(InData, index - 2)                                                                            // the candle -2 is white
        && IsBodyStrong(InData, index - 2)                                                                             // the body of the candle -2 is strong
        && IsBlackCandle(InData, index - 1)                                                                            // the body of the candle -1 is black
        && IsBlackCandle(InData, index)                                                                                // the body of the candle 0 is black
        && InData[SC_LAST][index - 2] < InData[SC_LAST][index - 1]                                                     // gap between the bodies of candles -2 and -1
        && InData[SC_OPEN][index - 1] <= InData[SC_OPEN][index]                                                        // the body of the candle 0 engulfs the body of the candle -1
        && InData[SC_LAST][index - 1] >= InData[SC_LAST][index] && InData[SC_LAST][index] > InData[SC_LAST][index - 2] // 3rd day closes above the close of the 1st day.
    )
    {
        ret_flag = true;
    }

    return ret_flag;
}
/*==========================================================================*/
const double k_ThreeBlackCrows_LowerWickPercent = 7.0;

bool IsThreeBlackCrows(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // THREE BLACK CROWS
    // 1. Uptrend
    // 2. Three consecutive black days with lower closes each day.
    // 3. Each day opens within the body of the previous day.
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (
        (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_UP) // uptrend
        && (IsBlackCandle(InData, index - 2) && IsBlackCandle(InData, index - 1) && IsBlackCandle(InData, index)) && InData[SC_LAST][index - 2] > InData[SC_LAST][index - 1] && InData[SC_LAST][index - 1] > InData[SC_LAST][index] && InData[SC_OPEN][index - 1] <= InData[SC_OPEN][index - 2] && InData[SC_OPEN][index - 1] >= InData[SC_LAST][index - 2] && InData[SC_OPEN][index] <= InData[SC_OPEN][index - 1] && InData[SC_OPEN][index] >= InData[SC_LAST][index - 1])
    {
        ret_flag = true;
    }

    return ret_flag;
}
/*==========================================================================*/
const double k_BearishCounterattackLine_SimilarityPercent = 7.0;

bool IsBearishCounterattackLine(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // BEARISH COUNTERATTACK LINE
    // 1. Uptrend
    // 2. The candles [index] and [index-1] are of contrast colors and their close prices are equal
    // Bearish Counterattack Line
    // In an uptrending market, a large white candlestick is following by a large black candlestick that opens on a big gap higher and then slumps back during the period to close at the same price as the previous close. The bearish black candlestick needs followup action to the downside to confirm the turn to a downtrend.
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_UP) // uptrend
    {
        // close prices are equal
        if (IsNearEqual(InData[SC_LAST][index], InData[SC_LAST][index - 1], InData, index, k_BearishCounterattackLine_SimilarityPercent))
        {
            // check for the colors contrast
            if (IsWhiteCandle(InData, index - 1) && IsBodyStrong(InData, index - 1))
            {
                if (IsBlackCandle(InData, index) && IsBodyStrong(InData, index))
                {
                    ret_flag = true;
                }
            }
            /*else if (IsBlackCandle(InData, index-1))
            {
            if(IsWhiteCandle(InData, index))
            {
            ret_flag = true;
            }
            }*/
        }
    }
    return ret_flag;
}
/*==========================================================================*/
const double k_BullishCounterattackLine_SimilarityPercent = 7.0;

bool IsBullishCounterattackLine(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // BULLISH COUNTERATTACK LINE
    // 1. Downtrend
    // 2. The candles [index] and [index-1]  are of contrast colors and their close prices are equal
    // Bullish Counterattack Line
    // In a downtrending market, a large black candlestick is following by a large white candlestick that opens on a big gap lower and then rallies during the period to close at the same price as the previous close. The bullish white candlestick needs followup action to the upside to confirm the turn to an uptrend.
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_DOWN) // downtrend
    {
        // close prices are equal
        if (IsNearEqual(InData[SC_LAST][index], InData[SC_LAST][index - 1], InData, index, k_BullishCounterattackLine_SimilarityPercent))
        {
            // check for the colors contrast
            /*if (IsWhiteCandle(InData, index-1))
            {
            if(IsBlackCandle(InData, index))
            {
            ret_flag = true;
            }
            }
            else*/
            if (IsBlackCandle(InData, index - 1) && IsBodyStrong(InData, index - 1))
            {
                if (IsWhiteCandle(InData, index) && IsBodyStrong(InData, index))
                {
                    ret_flag = true;
                }
            }
        }
    }
    return ret_flag;
}
/*==========================================================================*/

bool IsThreeInsideUp(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // THREE INSIDE UP
    // 1. Downtrend
    // 2. The candle [index] is white and the close price higher than the close price of the candle [index-1]
    // 3. The candles [index-2] and [index-3] form Bullish Harami Pattern
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_DOWN) // downtrend
    {
        if (IsWhiteCandle(InData, index) &&                        // the candle 0 is white
            (InData[SC_LAST][index] > InData[SC_LAST][index - 1])) // the close price of the candle 0 is higher than the close price of the candle -1
        {
            if (IsBullishHarami(sc, settings, index - 1))
            {
                ret_flag = true;
            }
        }
    }
    return ret_flag;
}
/*==========================================================================*/

bool IsThreeOutsideUp(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // THREE OUTSIDE UP
    // 1. Downtrend
    // 2. The candle [index] is white, and its close price is higher than the close price of the candle [index-1]
    // 3. Candles [index-2] and [index-3] form Bullish Engulfing Pattern
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_DOWN) // downtrend
    {
        if (IsWhiteCandle(InData, index) &&                        // the candle 0 is white
            (InData[SC_LAST][index] > InData[SC_LAST][index - 1])) // CLOSE of the candle 0 is higher than CLOSE of the candle -1
        {
            if (IsBullishEngulfing(sc, settings, index - 1))
            {
                ret_flag = true;
            }
        }
    }
    return ret_flag;
}
/*==========================================================================*/

bool IsThreeInsideDown(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // THREE INSIDE DOWN
    // 1. Uptrend
    // 2. The candle [index] is black, and its close price is lower than the close price of the the candle [index-1]
    // 3. The candles [index-2] and [index-3] form Bearish Harami Pattern
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_UP) // uptrend
    {
        if (IsBlackCandle(InData, index) &&                        // the candle 0 is black
            (InData[SC_LAST][index] < InData[SC_LAST][index - 1])) // CLOSE of the candle 0 is lower than CLOSE of the candle -1
        {
            if (IsBearishHarami(sc, settings, index - 1))
            {
                ret_flag = true;
            }
        }
    }
    return ret_flag;
}
/*==========================================================================*/

bool IsThreeOutsideDown(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // THREE OUTSIDE DOWN
    // 1. Uptrend
    // 2. The candle [index] is black, and its close price is lower than close price of the candle [index-1]
    // 3. The candles [index-2] and [index-3] form Bearish Engulfing Pattern
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_UP) // uptrend
    {
        if (IsBlackCandle(InData, index) &&                        // the candle 0 is black
            (InData[SC_LAST][index] < InData[SC_LAST][index - 1])) // CLOSE of the candle 0 is lower than CLOSE of the candle -1
        {
            if (IsBearishEngulfing(sc, settings, index - 1))
            {
                ret_flag = true;
            }
        }
    }
    return ret_flag;
}
/*==========================================================================*/
const double k_Kicker_UpperWickPercent = 7.0;
const double k_Kicker_LowerWickPercent = 7.0;

bool IsKicker(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // KICKER
    // 1. The candle [index-1] is black, without wicks
    // 2. The candle [index] is white, without wicks
    // 3. The bodies of the candles [index] and [index-1] are strong
    // 4. A gap between the bodies of the candles [index] and [index-1]
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    // the body of the candle -1 is black and without wicks
    if (IsBlackCandle(InData, index - 1) &&
        IsUpperWickSmall(InData, index - 1, k_Kicker_UpperWickPercent) &&
        IsLowerWickSmall(InData, index - 1, k_Kicker_LowerWickPercent))
    {
        // the body of the candle 0 is white and without wicks
        if (IsWhiteCandle(InData, index) &&
            IsUpperWickSmall(InData, index, k_Kicker_UpperWickPercent) &&
            IsLowerWickSmall(InData, index, k_Kicker_LowerWickPercent))
        {
            if (IsBodyStrong(InData, index - 1)) // the body of the candle -1 is strong
            {
                if (IsBodyStrong(InData, index)) // the body of the candle 0 is strong
                {
                    //  a gap between bodies
                    if (InData[SC_OPEN][index - 1] < InData[SC_OPEN][index])
                    {
                        ret_flag = true;
                    }
                }
            }
        }
    }
    return ret_flag;
}

/*==========================================================================*/
const double k_Kicking_UpperWickPercent = 7.0;
const double k_Kicking_LowerWickPercent = 7.0;

bool IsKicking(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // KICKING
    // 1. The candle [index-1] is white and without wicks
    // 2. The candle [index] is black and without wicks
    // 3. Bodies of the candles [index] and [index-1] are strong
    // 4. A gap between the bodies of the candles [index] and [index-1]
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    // the body of the candle -1 is white and without wicks
    if (IsWhiteCandle(InData, index - 1) &&
        IsUpperWickSmall(InData, index - 1, k_Kicking_UpperWickPercent) &&
        IsLowerWickSmall(InData, index - 1, k_Kicking_LowerWickPercent))
    {
        // the body of the candle 0 is black and without wicks
        if (IsBlackCandle(InData, index) &&
            IsUpperWickSmall(InData, index, k_Kicking_UpperWickPercent) &&
            IsLowerWickSmall(InData, index, k_Kicking_LowerWickPercent))
        {
            if (IsBodyStrong(InData, index - 1)) // the body of the candle -1 is strong
            {
                if (IsBodyStrong(InData, index)) // the body of the candle 0 is strong
                {
                    // a gap between the bodies
                    if (InData[SC_OPEN][index] < InData[SC_OPEN][index - 1])
                    {
                        ret_flag = true;
                    }
                }
            }
        }
    }
    return ret_flag;
}
/*==========================================================================*/

const double k_ThreeWhiteSoldiers_UpperWickPercent = 7.0;

bool IsThreeWhiteSoldiers(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // THREE WHITE SOLDIERS
    // 1. Downtrend till the candle 0
    // 2. The candles [index], [index-1] and [index-2] are white
    // 3. OPENs of candles [index], [index-1] are inside the bodies of the previous candles
    // 4. Upper wicks of the candles [index], [index-1] and [index-2] are insignificant
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_DOWN) // Downtrend
    {
        if (IsWhiteCandle(InData, index) &&     // the candle 0 is white
            IsWhiteCandle(InData, index - 1) && // the candle -1 is white
            IsWhiteCandle(InData, index - 2))   // the candle -2 is white
        {
            // OPEN of the candle 0 inside the body of the candle -1
            if ((InData[SC_OPEN][index] <= InData[SC_LAST][index - 1]) &&
                (InData[SC_OPEN][index] >= InData[SC_OPEN][index - 1]))
            {
                // OPEN of the candle -1 inside the body of the candle -2
                if ((InData[SC_OPEN][index - 1] <= InData[SC_LAST][index - 2]) &&
                    (InData[SC_OPEN][index - 1] >= InData[SC_OPEN][index - 2]))
                {
                    // check for upper wicks
                    if (IsUpperWickSmall(InData, index, k_ThreeWhiteSoldiers_UpperWickPercent) &&
                        IsUpperWickSmall(InData, index - 1, k_ThreeWhiteSoldiers_UpperWickPercent) &&
                        IsUpperWickSmall(InData, index - 2, k_ThreeWhiteSoldiers_UpperWickPercent))
                    {
                        ret_flag = true;
                    }
                }
            }
        }
    }
    return ret_flag;
}
/*==========================================================================*/

bool IsAdvanceBlock(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // ADVANCE BLOCK
    // 1. Uptrend till the candle 0
    // 2. The candles [index], [index-1] and [index-2] are white
    // 3. Opens of candles [index], [index-1] are inside the bodies of the previous candles
    // 4. The body of the candle [index] is smaller than the body of the candle [index-1],
    // and the body of the candle [index-1] is smaller than the body of the candle [index-2]
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_UP) // Uptrend
    {
        if (IsWhiteCandle(InData, index) &&     // the candle 0 is white
            IsWhiteCandle(InData, index - 1) && // the candle -1 is white
            IsWhiteCandle(InData, index - 2))   // the candle -2 is white
        {
            // OPEN of the candle 0 is inside the body of the candle -1
            if ((InData[SC_OPEN][index] <= InData[SC_LAST][index - 1]) &&
                (InData[SC_OPEN][index] >= InData[SC_OPEN][index - 1]))
            {
                // OPEN of the candle -1 is inside the body of the candle -2
                if ((InData[SC_OPEN][index - 1] <= InData[SC_LAST][index - 2]) &&
                    (InData[SC_OPEN][index - 1] >= InData[SC_OPEN][index - 2]))
                {
                    // check for the size of the body
                    if (BodyLength(InData, index) < BodyLength(InData, index - 1) &&
                        BodyLength(InData, index - 1) < BodyLength(InData, index - 2))
                    {
                        ret_flag = true;
                    }
                }
            }
        }
    }
    return ret_flag;
}
/*==========================================================================*/

const int k_Deliberation_UpperWickPercent = 7;

bool IsDeliberation(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // DELIBERATION
    // 1. Uptrend till the candle 0
    // 2. The candles [index], [index-1] and [index-2] are white
    // 3. OPENs of the candle [index-1] is inside the body of the previous candle
    // 4. The candle [index-1] has a strong body
    // 5. Candle [index] has a weak body
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_UP) // uptrend
    {
        if (IsWhiteCandle(InData, index) &&     // Candle 0 is white
            IsWhiteCandle(InData, index - 1) && // Candle -1 is white
            IsWhiteCandle(InData, index - 2))   // Candle -2 is white
        {
            // OPEN of the candle 0 is inside of the body of the candle -1
            /*if ((InData[SC_OPEN][index]<InData[SC_LAST][index-1])&&
            (InData[SC_OPEN][index]>InData[SC_OPEN][index-1]))*/
            {
                // OPEN of the candle -1 is inside of the body of the candle -2
                if ((InData[SC_OPEN][index - 1] <= InData[SC_LAST][index - 2]) &&
                    (InData[SC_OPEN][index - 1] >= InData[SC_OPEN][index - 2]))
                {
                    // body of the candle -1 is strong
                    if (IsBodyStrong(InData, index - 1))
                    {
                        // candle -1 does not have an upper wick
                        // if (IsUpperWickSmall(InData, index-1, k_Deliberation_UpperWickPercent))
                        {
                            // body of the candle 0 is weak
                            if (!IsBodyStrong(InData, index))
                            {
                                ret_flag = true;
                            }
                        }
                    }
                }
            }
        }
    }
    return ret_flag;
}
/*==========================================================================*/

const int k_BearishTriStar_PAST_INDEX = 3;

bool IsBearishTriStar(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // BEARISH TRI STAR
    // 1. Market is characterized by uptrend.
    // 2. We see three Dojis on three consecutive days.
    // 3. The second day Doji has a gap above the first and third.

    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    // the candle 0 is Doji
    if ((settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_UP) && IsDoji(sc, settings, index) && IsDoji(sc, settings, index - 1) && IsDoji(sc, settings, index - 2) && (InData[SC_OPEN][index - 1] > InData[SC_LAST][index]) && (InData[SC_OPEN][index - 1] > InData[SC_LAST][index - 2]))
    {
        ret_flag = true;
    }
    return ret_flag;
}
/*==========================================================================*/
const int k_BullishTriStar_PAST_INDEX = 3;

bool IsBullishTriStar(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // BULLISH TRI STAR
    // 1. Market is characterized by downtrend.
    // 2. Then we see three consecutive Doji.
    // 3. The second day Doji gaps below the first and third.
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    // the candle 0 is Doji
    if ((settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_DOWN) && IsDoji(sc, settings, index) && IsDoji(sc, settings, index - 1) && IsDoji(sc, settings, index - 2) && (InData[SC_OPEN][index - 1] < InData[SC_LAST][index]) && (InData[SC_OPEN][index - 1] < InData[SC_LAST][index - 2]))
    {
        ret_flag = true;
    }
    return ret_flag;
}
/*==========================================================================*/

bool IsUniqueThreeRiverBottom(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // UNIQUE THREE RIVER BOTTOM
    // 1. Downtrend till the candle [index-2]
    // 2. The candle [index-2] is black and with a strong body
    // 3. The candle [index-1] forms HAMMER PATERN
    // 4. The minimum of the candle [index-1] is smaller than the minimum of the candles [index-2] and [index]
    // 5. The candle [index] has a weak body that lower than the body of the candle [index-1]
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_DOWN) // Downtrend
    {
        if (InData[SC_LAST][index - 2] < InData[SC_OPEN][index - 2]) // the candle -2 is black
        {
            if (IsBodyStrong(InData, index - 2)) // the body of the candle -2 is strong
            {
                if (IsHammer(sc, settings, index - 1)) // The candle -1 is HAMMER
                {
                    // lower wick of the candle -1 forms new minimum
                    if ((InData[SC_LOW][index - 1] < InData[SC_LOW][index]) &&
                        (InData[SC_LOW][index - 1] < InData[SC_LOW][index - 2]))
                    {
                        if (IsWhiteCandle(InData, index)) // the candle 0 is white
                        {
                            if (!IsBodyStrong(InData, index)) // the body of the candle 0 is weak
                            {
                                if ((InData[SC_OPEN][index] < InData[SC_OPEN][index - 1]) &&
                                    (InData[SC_OPEN][index] < InData[SC_LAST][index - 1]))
                                // the body of the candle 0 is lower than the body of the candle -1
                                {
                                    ret_flag = true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return ret_flag;
}
/*==========================================================================*/
const double k_BearishDojiStar_UpperWickPercent = 25.0;
const double k_BearishDojiStar_LowerWickPercent = 25.0;

bool IsBearishDojiStar(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // BEARISH DOJI STAR
    // 1. Uptrend
    // 2. A strong white body of the candle [index-1]
    // 3. The candle [index] is Doji
    // 4. The body of the candle [index] is higher than the maximum of the candle [index-1]
    // 5. The wicks of the candles are "not long"
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_UP) // check for the uptrend
    {
        if (IsWhiteCandle(InData, index - 1)) // the body of the candle -1 is white
        {
            if (IsBodyStrong(InData, index - 1)) // the body of the candle -1 is strong
            {
                if (IsDoji(sc, settings, index)) // the candle 0 is Doji
                {
                    if (InData[SC_LAST][index] > InData[SC_HIGH][index - 1])
                    // the body of the candle 0 is higher than the maximum of the candle -1
                    {
                        // check for the wicks length
                        if (UpperWickLength(InData, index) <= PercentOfCandleLength(InData, index - 1, k_BearishDojiStar_UpperWickPercent) && // upper wick of Doji
                            LowerWickLength(InData, index) <= PercentOfCandleLength(InData, index - 1, k_BearishDojiStar_LowerWickPercent))
                        {
                            ret_flag = true;
                        }
                    }
                }
            }
        }
    }
    return ret_flag;
}
/*==========================================================================*/
const double k_BullishDojiStar_LowerWickPercent = 25.0;
const double k_BullishDojiStar_UpperWickPercent = 25.0;

bool IsBullishDojiStar(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // BULLISH DOJI STAR
    // 1. Downtrend
    // 2. Strong black body of the candle [index-1]
    // 3. The candle [index] is Doji
    // 4. The body of the candle [index] is lower than minimum of the candle [index-1]
    // 5. The wicks of the candle [index] are "not long"
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_DOWN) // check for the downtrend
    {
        if (IsBlackCandle(InData, index - 1)) // the body of the candle -1 is black
        {
            if (IsBodyStrong(InData, index - 1)) // the body of the candle -1 is strong
            {
                if (IsDoji(sc, settings, index)) // the candle 0 is Doji
                {
                    if (InData[SC_LAST][index] < InData[SC_LOW][index - 1])
                    // the body of the candle 0 is lower than minimum of the candle -1
                    {
                        // check for the wicks length
                        if (UpperWickLength(InData, index) <= PercentOfCandleLength(InData, index - 1, k_BearishDojiStar_UpperWickPercent) && // upper wick of Doji
                            LowerWickLength(InData, index) <= PercentOfCandleLength(InData, index - 1, k_BearishDojiStar_LowerWickPercent))   // lower wick of Doji

                        {
                            ret_flag = true;
                        }
                    }
                }
            }
        }
    }
    return ret_flag;
}
/*==========================================================================*/
const double k_BearishDragonflyDoji_UpperWickPercent = 7.0;

bool IsBearishDragonflyDoji(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // BEARISH DRAGONFLY DOJI
    // 1. Uptrend
    // 2. The candle [index] is Doji
    // 3. The candle [index] does not have an upper wick
    // 4. The lower wick of the candle [index] is very long
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_UP) // check for the uptrend
    {
        if (IsDoji(sc, settings, index)) // the candle 0 is Doji
        {
            if (IsUpperWickSmall(InData, index, k_BearishDragonflyDoji_UpperWickPercent)) // the candle 0 does not have an upper wick
            {
                // The candle 0 has a long lower wick
                //
                // Note:
                //   if body is small and upper wick is small while the candle is
                //   long => the lower wick is long
                if (IsCandleStrength(InData, index))
                {
                    ret_flag = true;
                }
            }
        }
    }
    return ret_flag;
}
/*==========================================================================*/

const double k_BullishDragonflyDoji_UpperWickPercent = 7.0;

bool IsBullishDragonflyDoji(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // BULLISH DRAGONFLY DOJI
    // 1. Downtrend
    // 2. The candle [index] is Doji
    // 3. The candle [index] does not have an upper wick
    // 4. The lower wick of the candle [index] is very long
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_DOWN) // check for the downtrend
    {
        if (IsDoji(sc, settings, index)) // the candle 0 is Doji
        {
            if (IsUpperWickSmall(InData, index, k_BullishDragonflyDoji_UpperWickPercent)) // the candle 0 does not have an upper wick
            {
                // The candle 0 has a long lower wick
                //
                // Note:
                //   if body is small and upper wick is small while the candle is
                //   long => the lower wick is long
                if (IsCandleStrength(InData, index))
                {
                    ret_flag = true;
                }
            }
        }
    }
    return ret_flag;
}
/*==========================================================================*/

const double k_BearishGravestoneDoji_LowerWickPercent = 7.0;

bool IsBearishGravestoneDoji(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // BEARISH GRAVESTONE DOJI
    // 1. Uptrend
    // 2. The candle [index-1] has a white body
    // 3. The candle [index] is Doji
    // 4. The lower wick of the candle [index] is insignificant
    // 5. Upper wick of the candle [index] is very long
    // 6. OPEN of the candle [index] is higher than the maximum of the candle [index-1]
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_UP) // check for the uptrend
    {
        if (IsWhiteCandle(InData, index - 1)) // the body of the candle -1 is white
        {
            if (IsDoji(sc, settings, index)) // the candle [index] is Doji
            {
                // lower wick of the candle 0 is insignificant
                if (IsLowerWickSmall(InData, index, k_BearishGravestoneDoji_LowerWickPercent))
                {
                    // upper wick of the candle 0 is long (please, note that it's Doji, so there is no body)
                    if (IsCandleStrength(InData, index))
                    {
                        // OPEN of the candle 0 is higher than the maximum of the candle -1
                        if (InData[SC_OPEN][index] > InData[SC_HIGH][index - 1])
                        {
                            ret_flag = true;
                        }
                    }
                }
            }
        }
    }
    return ret_flag;
}
/*==========================================================================*/

const double k_BullishGravestoneDoji_LowerWickPercent = 7;

bool IsBullishGravestoneDoji(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // BULLISH GRAVESTONE DOJI
    // 1. Downtrend
    // 2. The candle [index-1] has a black body
    // 3. The candle [index] is Doji
    // 4. The candle [index] does not have a lower wick
    // 5. The upper wick of the candle [index] is very long
    // 6. Absence of the gap between the candles [index] and [index-1] is necessary
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_DOWN) // check for the downtrend
    {
        if (IsBlackCandle(InData, index - 1)) // the body of the candle -1 is black
        {
            if (IsDoji(sc, settings, index)) // the candle 0 is Doji
            {
                // candle 0 does not have a lower wick
                if (IsLowerWickSmall(InData, index, k_BullishGravestoneDoji_LowerWickPercent))
                {
                    // candle 0 has a long upper wick
                    //
                    // Note:
                    //   if body is small and lower wick is small and the candle is
                    //   long => the lower wick is long
                    //   (please, note that it's Doji, so there is no body)
                    if (IsCandleStrength(InData, index))
                    {
                        // check for the absence of the gap
                        if (InData[SC_LOW][index - 1] < InData[SC_HIGH][index])
                        {
                            ret_flag = true;
                        }
                    }
                }
            }
        }
    }
    return ret_flag;
}
/*==========================================================================*/

const double k_BearishLongleggedDoji_SimilarityPercent = 10.0;

bool IsBearishLongleggedDoji(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // BEARISH LONGLEGGED DOJI
    // 1. Uptrend
    // 2. The candle [index] is Doji
    // 3. The candle [index] is long
    // 4. The wicks of the candle [index] are nearly the same
    // 5. The body of the candle [index] is higher than the maximum of the candle [index-1]
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_UP) // check for the uptrend
    {
        if (IsDoji(sc, settings, index)) // the candle 0 is Doji
        {
            // the candle 0 is long
            if (IsCandleStrength(InData, index))
            {
                // the body of the candle 0 is higher than the maximum of the candle -1
                if (max(InData[SC_LAST][index], InData[SC_OPEN][index]) > InData[SC_HIGH][index - 1])
                {
                    // the wicks of the candle 0 are nearly the same
                    if (abs(LowerWickLength(InData, index) - UpperWickLength(InData, index)) <
                        PercentOfCandleLength(InData, index, k_BearishLongleggedDoji_SimilarityPercent))
                    {
                        ret_flag = true;
                    }
                }
            }
        }
    }
    return ret_flag;
}
/*==========================================================================*/

const double k_BullishLongleggedDoji_SimilarityPercent = 10.0;

bool IsBullishLongleggedDoji(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // BULLISH LONGLEGGED DOJI
    // 1. Downtrend
    // 2. The candle [index] is Doji
    // 3. The candle [index] is long
    // 4. The wicks of the candle [index] are nearly the same
    // 5. The body of the candle [index] is lower than the minimum of the candle [index-1]
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_DOWN) // check for the downtrend
    {
        if (IsDoji(sc, settings, index)) // the candle 0 is Doji
        {
            // The candle 0 is long
            if (IsCandleStrength(InData, index))
            {
                // the body of the candle 0 is lower than the minimum of the candle -1
                if (max(InData[SC_LAST][index], InData[SC_OPEN][index]) < InData[SC_LOW][index - 1])
                {
                    // the wicks of the candle 0 are nearly the same
                    if (abs(LowerWickLength(InData, index) - UpperWickLength(InData, index)) <
                        PercentOfCandleLength(InData, index, k_BullishLongleggedDoji_SimilarityPercent))
                    {
                        ret_flag = true;
                    }
                }
            }
        }
    }
    return ret_flag;
}
/*==========================================================================*/
// const int    k_BearishSideBySideWhiteLines_TrendArea = 3;
const int k_BearishSideBySideWhiteLines_PAST_INDEX = 3;
const double k_BearishSideBySideWhiteLines_OpenSimilarityPercent = 14.0;
const double k_BearishSideBySideWhiteLines_CandleSimilarityPercent = 14.0;

bool IsBearishSideBySideWhiteLines(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // BEARISH SIDE-BY-SIDE WHITE LINES
    // 1. Downtrend
    // 2. The candles [index], [index-1] are white
    // 3. The candle [index-2] is black
    // 4. The maximum of the candle [index-1] is lower than the minimum of the candle [index-2]
    // 5. Open prices and the sizes of the candles [index-1] and [index] are ALMOST the same

    /*	1. 1st day is a black day.
    2. 2nd day is a white day which gaps below the 1st day's open.
    3. 3rd day is a white day about the same size as the 2nd day, opening at about the same price.*/

    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_DOWN) // check for the downtrend
    {
        if (IsWhiteCandle(InData, index) &&     // the candle 0 is white
            IsWhiteCandle(InData, index - 1) && // the candle -1 is white
            IsBlackCandle(InData, index - 2))   // the candle -2 is black
        {
            //  the candle -2 is higher than the candle -1 with a gap
            if (InData[SC_LOW][index - 2] > InData[SC_HIGH][index - 1])
            {
                // compare of the OPENS of the candles 0 and -1
                if (IsNearEqual(InData[SC_OPEN][index - 1], InData[SC_OPEN][index], InData, index, k_BearishSideBySideWhiteLines_OpenSimilarityPercent))
                {
                    // compare of the length of the candles 0 and -1
                    if (IsNearEqual(CandleLength(InData, index), CandleLength(InData, index - 1), InData, index, k_BearishSideBySideWhiteLines_CandleSimilarityPercent))
                    {
                        ret_flag = true;
                    }
                }
            }
        }
    }
    return ret_flag;
}
/*==========================================================================*/
// const int    k_BullishSideBySideWhiteLines_TrendArea = 3;
const int k_BullishSideBySideWhiteLines_PAST_INDEX = 3;
const double k_BullishSideBySideWhiteLines_OpenSimilarityPercent = 7.0;
const double k_BullishSideBySideWhiteLines_CandleSimilarityPercent = 7.0;

bool IsBullishSideBySideWhiteLines(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // BULLISH SIDE-BY-SIDE WHITE LINES
    // 1. Uptrend
    // 2. The candles [index], [index-1] and [index-2] are white
    // 3. Maximum of the candle [index-2] is lower than minimum of the candle [index-1]
    // 4. Open prices and the sizes of the candles [index-1] and [index] are ALMOST the same

    /*  1. Market is characterized by uptrend.
    2. We see a white candlestick in the first day.
    3. Then we see another white candlestick on the second day with an upward gap.
    4. Finally, we see a white candlestick on the third day characterized by the same body length and whose closing price is equal to the close of the second day and a new high is established.*/

    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (
        (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_UP) // check for the uptrend
        && IsWhiteCandle(InData, index) && IsWhiteCandle(InData, index - 1) && IsWhiteCandle(InData, index - 2) && (InData[SC_LOW][index - 1] > InData[SC_HIGH][index - 2]) && (IsNearEqual(InData[SC_LAST][index - 1], InData[SC_LAST][index], InData, index, k_BullishSideBySideWhiteLines_OpenSimilarityPercent)) && (IsNearEqual(InData[SC_OPEN][index - 1], InData[SC_OPEN][index], InData, index, k_BullishSideBySideWhiteLines_OpenSimilarityPercent)) && (InData[SC_HIGH][index] > InData[SC_HIGH][index - 1]))
    {
        ret_flag = true;
    }
    return ret_flag;
}
/*==========================================================================*/

const int k_FallingThreeMethods_PAST_INDEX = 3;
const double k_FallingThreeMethods_CandleCloseClosenessPercent = 30.0;

bool IsFallingThreeMethods(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // FALLING THREE METHODS

    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;

    // 1. Market is characterized by downtrend.
    // 2. We see a long black candlestick in the first day.
    // 3. We then see three small real bodies defining a brief uptrend on the second, third, and fourth days. However these bodies stay within the range of the first day.
    // 4. Finally we see a long black candlestick on the fifth day opening near the previous day's close and also closing below the close of the initial day to define a new low.

    if (
        (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_DOWN)

        && IsBodyStrong(InData, index - 4) && IsBlackCandle(InData, index - 4)

        //&& IsWhiteCandle(InData, index-1)
        //&& IsWhiteCandle(InData, index-2)
        //&& IsWhiteCandle(InData, index-3)
        && !IsBodyStrong(InData, index - 1) && !IsBodyStrong(InData, index - 2) && !IsBodyStrong(InData, index - 3) && (InData[SC_OHLC_AVG][index - 3] < InData[SC_OHLC_AVG][index - 2]) && (InData[SC_OHLC_AVG][index - 2] < InData[SC_OHLC_AVG][index - 1])

        && (InData[SC_HIGH][index - 3] < InData[SC_HIGH][index - 4]) && (InData[SC_HIGH][index - 2] < InData[SC_HIGH][index - 4]) && (InData[SC_HIGH][index - 1] < InData[SC_HIGH][index - 4]) && (InData[SC_LOW][index - 3] > InData[SC_LOW][index - 4]) && (InData[SC_LOW][index - 2] > InData[SC_LOW][index - 4]) && (InData[SC_LOW][index - 1] > InData[SC_LOW][index - 4])

        && IsBodyStrong(InData, index) && IsBlackCandle(InData, index) && (IsNearEqual(InData[SC_OPEN][index], InData[SC_LAST][index - 1], InData, index, k_FallingThreeMethods_CandleCloseClosenessPercent)) && (InData[SC_LAST][index] < InData[SC_LAST][index - 4]))
    {
        ret_flag = true;
    }

    return ret_flag;
}
/*==========================================================================*/

const int k_RisingThreeMethods_PAST_INDEX = 3;

bool IsRisingThreeMethods(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // RISING THREE METHODS

    //  . Market is characterized by downtrend.
    // 1. 1st day is a long white day.
    // 2. Three small body candlesticks follow the 1st day. Each trends downward and closes within the range of the 1st day.
    // 3. The last day is a long white day and closes above the 1st day's close.
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;

    if (
        (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_UP)

        && IsBodyStrong(InData, index - 4) && IsWhiteCandle(InData, index - 4)

        && !IsBodyStrong(InData, index - 1) && !IsBodyStrong(InData, index - 2) && !IsBodyStrong(InData, index - 3) && (InData[SC_OHLC_AVG][index - 3] > InData[SC_OHLC_AVG][index - 2]) && (InData[SC_OHLC_AVG][index - 2] > InData[SC_OHLC_AVG][index - 1])

        && (InData[SC_HIGH][index - 3] <= InData[SC_HIGH][index - 4]) && (InData[SC_HIGH][index - 2] <= InData[SC_HIGH][index - 4]) && (InData[SC_HIGH][index - 1] <= InData[SC_HIGH][index - 4]) && (InData[SC_LOW][index - 3] >= InData[SC_LOW][index - 4]) && (InData[SC_LOW][index - 2] >= InData[SC_LOW][index - 4]) && (InData[SC_LOW][index - 1] >= InData[SC_LOW][index - 4])

        && IsBodyStrong(InData, index) && IsWhiteCandle(InData, index) && (InData[SC_LAST][index] > InData[SC_LAST][index - 4]))
    {
        ret_flag = true;
    }

    return ret_flag;
}
/*==========================================================================*/

const double k_BearishSeparatingLines_SimilarityPercent = 5.0;

bool IsBearishSeparatingLines(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // BEARISH SEPARATING LINE
    // 1. Downtrend
    // 2. The candles [index] and [index-1] are of contrast colors and their open prices are equal
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_DOWN) // downtrend
    {
        // OPENs are equal
        if (IsNearEqual(InData[SC_OPEN][index], InData[SC_OPEN][index - 1], InData, index, k_BearishSeparatingLines_SimilarityPercent))
        {
            // check for the colors contrast
            bool colorIndex0 = IsWhiteCandle(InData, index);
            bool colorIndex1 = IsWhiteCandle(InData, index - 1);

            ret_flag = (colorIndex1 != colorIndex0);
        }
    }
    return ret_flag;
}
/*==========================================================================*/
const double k_BullishSeparatingLines_SimilarityPercent = 5.0;

bool IsBullishSeparatingLines(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // BULLISH SEPARATING LINE
    // 1. Uptrend
    // 2. The candles [index] and [index-1] are of contrast colors and their open prices are equal
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_UP) // uptrend
    {
        // OPENs are equal
        if (IsNearEqual(InData[SC_OPEN][index], InData[SC_OPEN][index - 1], InData, index, k_BullishSeparatingLines_SimilarityPercent))
        {
            // check for the colors contrast
            // check for the colors contrast
            bool colorIndex0 = IsWhiteCandle(InData, index);
            bool colorIndex1 = IsWhiteCandle(InData, index - 1);

            ret_flag = (colorIndex1 != colorIndex0);
        }
    }
    return ret_flag;
}
/*==========================================================================*/

bool IsDownsideTasukiGap(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // DOWNSIDE TASUKI GAP
    // 1. Downtrend
    // 2. The candle [index] is white and its open price is inside the body of the candle [index-1]
    // 3. The candles [index-1] and [index-2] are black with strong bodies
    // 4.  There is a gap between the candles [index-1] and [index-2]
    // 5.  CLOSE of the candle [index] is in the gap between the candles [index-1] and [index-2]
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_DOWN) // downtrend
    {
        if (IsWhiteCandle(InData, index) &&     //  the candle 0 is white
            IsBlackCandle(InData, index - 1) && // the candle -1 is black
            IsBlackCandle(InData, index - 2))   // the candle -2 is black
        {
            if (IsBodyStrong(InData, index - 1)) // the body of the candle -1 is strong
            {
                if (IsBodyStrong(InData, index - 2)) // the body of the candle -2 is strong
                {
                    if (InData[SC_LOW][index - 2] > InData[SC_HIGH][index - 1]) // a gap between the candles -1 and -2
                    {
                        // OPEN of the candle 0 is inside the body of the candle -1
                        if ((InData[SC_OPEN][index] > InData[SC_LAST][index - 1]) &&
                            (InData[SC_OPEN][index] < InData[SC_OPEN][index - 1]))
                        {
                            // CLOSE of the candle 0 is higher than maximum of the candle -1 and lower than the minimum of the candle -2
                            if ((InData[SC_LAST][index] > InData[SC_HIGH][index - 1]) &&
                                (InData[SC_LAST][index] < InData[SC_LOW][index - 2]))
                            {
                                ret_flag = true;
                            }
                        }
                    }
                }
            }
        }
    }
    return ret_flag;
}
/*==========================================================================*/

bool IsUpsideTasukiGap(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // UPSIDE TASUKI GAP
    // 1. Uptrend
    // 2. The candle [index] is black and its open price is inside the body of the candle [index-1]
    // 3. The candles [index-1] and [index-2] are white with strong bodies
    // 4. There is a gap between the candles [index-1] and [index-2]
    // 5. CLOSE of the candle [index] is in the gap between the candles [index-1] and [index-2]
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_UP) // uptrend
    {
        if (IsBlackCandle(InData, index) &&     //  the candle 0 is black
            IsWhiteCandle(InData, index - 1) && // the candle -1 is white
            IsWhiteCandle(InData, index - 2))   // the candle -2 is white
        {
            if (IsBodyStrong(InData, index - 1)) // the body of the candle -1 is strong
            {
                if (IsBodyStrong(InData, index - 2)) // the body of the candle -2 is strong
                {
                    if (InData[SC_HIGH][index - 2] < InData[SC_LOW][index - 1]) // a gap between the candles -1 and -2
                    {
                        // OPEN of the candle 0 is inside the body of the candle -1
                        if ((InData[SC_OPEN][index] > InData[SC_OPEN][index - 1]) &&
                            (InData[SC_OPEN][index] < InData[SC_LAST][index - 1]))
                        {
                            // CLOSE of the candle 0 is lower than minimum of the candle -1 and higher than the maximum of the candle -2
                            if ((InData[SC_LAST][index] > InData[SC_HIGH][index - 2]) &&
                                (InData[SC_LAST][index] < InData[SC_LOW][index - 1]))
                            {
                                ret_flag = true;
                            }
                        }
                    }
                }
            }
        }
    }
    return ret_flag;
}
/*==========================================================================*/

bool IsBearishThreeLineStrike(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // BEARISH THREE LINE STRIKE
    // 1. Downtrend
    // 2. The candle [index] is white with a strong body
    // 3. The candles [index-1], [index-2] and [index-3] are black with strong bodies
    // 4.  OPEN of the candle [index] is lower than CLOSE of the candle [index-1]
    // 5.  CLOSE of the candle [index] is higher than OPEN of the candle [index-3]
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_DOWN) // downtrend
    {
        if (IsWhiteCandle(InData, index) &&     // the candle 0 is white
            IsBlackCandle(InData, index - 1) && // the candle -1 is black
            IsBlackCandle(InData, index - 2) && // the candle -2 is black
            IsBlackCandle(InData, index - 3))   // the candle -3 is black
        {
            if (IsBodyStrong(InData, index - 1)) // the body of the candle -1 is strong
            {
                if (IsBodyStrong(InData, index - 2)) // the body of the candle -2 is strong
                {
                    if (IsBodyStrong(InData, index - 3)) // the body of the candle -1 is strong
                    {
                        // OPEN of the candle 0 is lower than CLOSE of the candle -1
                        if (InData[SC_OPEN][index] < InData[SC_LAST][index - 1])
                        {
                            // CLOSE of the candle 0 is higher than OPEN of the candle -3
                            if (InData[SC_LAST][index] > InData[SC_OPEN][index - 3])
                            {
                                ret_flag = true;
                            }
                        }
                    }
                }
            }
        }
    }
    return ret_flag;
}
/*==========================================================================*/

bool IsBullishThreeLineStrike(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // BULLISH THREE LINE STRIKE
    // 1. Uptrend
    // 2. The candle [index] is black with a strong body
    // 3. The candles [index-1], [index-2] and [index-3] are white with strong bodies
    // 4. OPEN of the candle [index] is higher than CLOSE of the candle [index-1]
    // 5. CLOSE of the candle [index] is lower than OPEN of the candle [index-3]
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_UP) // uptrend
    {
        if (IsBlackCandle(InData, index) &&     //  the candle 0 is black
            IsWhiteCandle(InData, index - 1) && // the candle -1 is white
            IsWhiteCandle(InData, index - 2) && // the candle -2 is white
            IsWhiteCandle(InData, index - 3))   // the candle -3 is white
        {
            if (IsBodyStrong(InData, index - 1)) // the body of the candle -1 is strong
            {
                if (IsBodyStrong(InData, index - 2)) // the body of the candle -2 is strong
                {
                    if (IsBodyStrong(InData, index - 3)) // the body of the candle -3 is strong
                    {
                        // OPEN of the candle 0 is higher than CLOSE of the candle -1
                        if (InData[SC_OPEN][index] > InData[SC_LAST][index - 1])
                        {
                            // CLOSE of the candle 0 is lower than OPEN of the candle -3
                            if (InData[SC_LAST][index] < InData[SC_OPEN][index - 3])
                            {
                                ret_flag = true;
                            }
                        }
                    }
                }
            }
        }
    }
    return ret_flag;
}
/*==========================================================================*/

bool IsDownsideGapThreeMethods(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // DOWNSIDE GAP THREE METHODS
    // 1. Downtrend
    // 2. The candle [index] is white and its OPEN is inside the body of the candle [index-1]
    // 3. The candles [index-1] and [index-2] are black with a strong bodies
    // 4.  There is a gap between the candles [index-1] and [index-2]
    // 5.  The body of the candle [index] closes the gap between the candles [index-1] and [index-2]
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_DOWN) // downtrend
    {
        if (IsWhiteCandle(InData, index) &&     //  the candle 0 is white
            IsBlackCandle(InData, index - 1) && // the candle -1 is black
            IsBlackCandle(InData, index - 2))   // the candle -2 is black
        {
            if (IsBodyStrong(InData, index - 1)) // the body of the candle -1 is strong
            {
                if (IsBodyStrong(InData, index - 2)) // the body of the candle -2 is strong
                {
                    if (InData[SC_LOW][index - 2] > InData[SC_HIGH][index - 1]) // a gap between the candles -1 and -2
                    {
                        // OPEN of the candle 0 is inside the body of the candle -1
                        if ((InData[SC_OPEN][index] > InData[SC_LAST][index - 1]) &&
                            (InData[SC_OPEN][index] < InData[SC_OPEN][index - 1]))
                        {
                            // CLOSE of the candle 0 is higher than minimum of the candle -2
                            if (InData[SC_LAST][index] > InData[SC_LOW][index - 2])
                            {
                                ret_flag = true;
                            }
                        }
                    }
                }
            }
        }
    }
    return ret_flag;
}
/*==========================================================================*/

bool IsUpsideGapThreeMethods(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // UPSIDE GAP THREE METHODS
    // 1. Uptrend
    // 2.  The candle [index] is black and its OPEN is inside the body of the candle [index-1]
    // 3. The candles [index-1] and [index-2] are white with a strong bodies
    // 4.  There is a gap between the candles [index-1] and [index-2]
    // 5.  The body of the candle [index] closes the gap between the candles [index-1] and [index-2]
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_UP) // uptrend
    {
        if (IsBlackCandle(InData, index) &&     // the candle 0 is black
            IsWhiteCandle(InData, index - 1) && // the candle -1 is white
            IsWhiteCandle(InData, index - 2))   // the candle -2 is white
        {
            if (IsBodyStrong(InData, index - 1)) //  the body of the candle -1 is strong
            {
                if (IsBodyStrong(InData, index - 2)) //  the body of the candle -1 is strong
                {
                    if (InData[SC_HIGH][index - 2] < InData[SC_LOW][index - 1]) // a gap between the candles -1 and -2
                    {
                        // OPEN of the candle 0 is inside the body of the candle -1
                        if ((InData[SC_OPEN][index] > InData[SC_OPEN][index - 1]) &&
                            (InData[SC_OPEN][index] < InData[SC_LAST][index - 1]))
                        {
                            // CLOSE of the candle 0 is lower than maximum of the candle -2
                            if (InData[SC_LAST][index] < InData[SC_HIGH][index - 2])
                            {
                                ret_flag = true;
                            }
                        }
                    }
                }
            }
        }
    }
    return ret_flag;
}
/*==========================================================================*/

const double k_OnNeck_SimilarityPercent = 15.0;

bool IsOnNeck(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // ON NECK
    // 1. Downtrend
    // 2.  The candle [index-1] is black and with a strong body
    // 3.  The candle [index] is white
    // 4. CLOSE of the candle [index] is ALMOST equal the minimum of the candle [index-1]
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_DOWN) // downtrend
    {
        if (IsBlackCandle(InData, index - 1)) // the candle -1 is black
        {
            if (IsBodyStrong(InData, index - 1)) // the body of the candle -1 is strong
            {
                if (IsWhiteCandle(InData, index)) // the candle 0 is white
                {
                    // CLOSE of the candle 0 is ALMOST equal the minimum of the candle -1
                    if (IsNearEqual(InData[SC_LAST][index], InData[SC_LOW][index - 1], InData, index, k_OnNeck_SimilarityPercent))
                    {
                        ret_flag = true;
                    }
                }
            }
        }
    }
    return ret_flag;
}
/*==========================================================================*/

const double k_InNeck_SimilarityPercent = 15.0;

bool IsInNeck(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // IN NECK
    // 1. Downtrend
    // 2. The candle [index-1] is black and with a strong body
    // 3. The candle [index] is white
    // 4. OPEN of the candle [index] is lower than the minimum of the candle [index-1]
    // 5. CLOSE of the candle [index] is a little bit higher or equal the CLOSE of the candle -1
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_DOWN) // downtrend
    {
        if (IsBlackCandle(InData, index - 1)) // the candle -1 is black
        {
            if (IsBodyStrong(InData, index - 1)) // the body of the candle -1 is strong
            {
                if (IsWhiteCandle(InData, index)) // the candle 0 is white
                {
                    // OPEN of the candle 0 is lower than the minimum of the candle -1,
                    // and CLOSE of the candle 0 is a higher or equal the CLOSE of the candle -1
                    if ((InData[SC_LOW][index - 1] > InData[SC_OPEN][index]) &&
                        (InData[SC_LAST][index] >= InData[SC_LAST][index - 1]))
                    {
                        // CLOSE of the candle 0 is equal the CLOSE of the candle -1
                        if (IsNearEqual(InData[SC_LAST][index], InData[SC_LAST][index - 1], InData, index, k_InNeck_SimilarityPercent))
                        {
                            ret_flag = true;
                        }
                        // CLOSE of the candle 0 is a little bit higher or equal the CLOSE of the candle -1
                        else if ((InData[SC_LAST][index] - InData[SC_LAST][index - 1]) <
                                 PercentOfCandleLength(InData, index, k_InNeck_SimilarityPercent))
                        {
                            ret_flag = true;
                        }
                    }
                }
            }
        }
    }
    return ret_flag;
}
/*==========================================================================*/

const double BearishThrusting_SignificantlyLowerPercent = 10.0;

bool IsBearishThrusting(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // Bearish Thrusting
    // 1. Downtrend
    // 2. Candle [index-1] is black
    // 3. Candle [index] is white
    // 4. OPEN of the candle [index] SIGNIFICANTLY lower the minimum of the candle [index-1]
    // 5. CLOSE of the candle [index] is higher than the CLOSE of candle [index-1], but lower than the middle of body of candle [index-1]
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_DOWN) // downtrend
    {
        if (IsBlackCandle(InData, index - 1)) // candle -1 is black
        {
            if (IsWhiteCandle(InData, index)) // candle 0 is white
            {
                // OPEN of candle 0 is SIGNIFICANTLY lower than the minimum of candle -1
                if ((InData[SC_LOW][index - 1] > InData[SC_OPEN][index]) &&
                    (InData[SC_LOW][index - 1] - InData[SC_OPEN][index]) >
                        PercentOfCandleLength(InData, index, BearishThrusting_SignificantlyLowerPercent))
                {
                    // CLOSE of candle 0 is higher than the CLOSE of -1, but lower than the middle of body of the candle -1
                    if ((InData[SC_LAST][index] > InData[SC_LAST][index - 1]) &&
                        (InData[SC_LAST][index] < (InData[SC_LAST][index - 1] + (InData[SC_OPEN][index - 1] - InData[SC_LAST][index - 1]) / 2)))
                    {
                        ret_flag = true;
                    }
                }
            }
        }
    }
    return ret_flag;
}
/*==========================================================================*/

const int k_MatHold_PAST_INDEX = 3;

bool IsMatHold(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index)
{
    // MAT HOLD
    // 1. Candle [index] is white with strong body
    // 2. OPEN of th candle [index] is higher than CLOSE of candle [index-1]
    // 3. Candles [index-1] and [index-2] has weak bodies
    // 4. CLOSE of candle [index-2] is higher than the CLOSE of candle [index-1]
    // 5. Candle [index-X] has strong white body (where X is from 3 to PAST_INDEX+1)
    // 6. CLOSE of candle [index] is higher than CLOSE of candle [index-X]
    // 7. Uptrend till candle [index-X]
    // 8. Candles [index-Y] has weak bodies (where Y is from 1 to X-1)
    // 9. CLOSE of candle [index-Y] is higher than CLOSE of [index-Y-1] (where Y is from 1 to X-1)
    // 10. Minimum of candle [index-Y+1] is higher than maximum of candle [index-Y]
    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (IsWhiteCandle(InData, index) &&                        // candle 0 is white
        (InData[SC_OPEN][index] > InData[SC_LAST][index - 1])) // OPEN of candle 0 is higher than CLOSE of -1
    {
        if (IsBodyStrong(InData, index)) // body of the candle 0 is strong
        {
            if (InData[SC_LAST][index - 2] > InData[SC_LAST][index - 1]) // CLOSE of candle -2 is higher than CLOSE of candle -1
            {
                // bodies of candles -1 and -2 are weak
                if ((!IsBodyStrong(InData, index - 1)) && (!IsBodyStrong(InData, index - 2)))
                {
                    int X = 0;
                    // searching for a strong white body
                    for (int i = 3; i < (k_MatHold_PAST_INDEX + 2); i++)
                    {
                        if (IsBodyStrong(InData, index - i) && IsWhiteCandle(InData, index - i))
                        {
                            // CLOSE of candle 0 is higher than CLOSE of candle -X
                            if (InData[SC_LAST][index] > InData[SC_LAST][index - i])
                            {
                                // found candle -X
                                X = i;
                            }
                            break;
                        }
                    }
                    if (X != 0)
                    {
                        // uptrend till candle -Õ
                        if (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_UP)
                        {
                            // Minimum of candle [index-Y+1] is higher than maximum of candle [index-Y]; candle [index-Y+1] is black
                            if ((InData[SC_LOW][index - X + 1] > InData[SC_HIGH][index - X]) &&
                                IsBlackCandle(InData, index - X + 1))
                            {
                                ret_flag = true;
                                // checking the candles between two white candles
                                if ((IsBodyStrong(InData, index - 1)) ||                         // check if body is strong
                                    (InData[SC_HIGH][index - 1] > InData[SC_HIGH][index - X]) || // check if maximum is higher than maximum of candle -Õ
                                    (InData[SC_LOW][index - 1] < InData[SC_LOW][index - X]))     // check if minimum is lower than minimum of candle -Õ
                                {
                                    ret_flag = false;
                                }
                                else
                                {
                                    for (int i = 2; i < X; i++)
                                    {
                                        // searching for a presence of a candle that does not match conditions
                                        if ((IsBodyStrong(InData, index - i)) ||                           // check whether body is strong
                                            (InData[SC_LAST][index - i] < InData[SC_LAST][index - i + 1])) //  check whether CLOSE is lower than the CLOSE of a next candle
                                        {
                                            ret_flag = false;
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return ret_flag;
}

/*==========================================================================*/
const int k_Box_NUM_OF_CANDLES = 8; // number of previous candles to calculate candle strength
const double k_Box_SimilarityPercent = 15;
// GetHighest func

inline bool IsNearEqualBars(SCBaseDataRef InData, int index, SCStudyInterfaceRef sc, int r_DrawingNumberForLastBar)
{
    bool ret_flag = false;
    bool is_inside_candle = true;
    bool is_near_equal = true;
    bool is_overlapping = false;
    float BoxHighs = 0;
    float BoxLows = 0;
    float BoxHH = InData[SC_HIGH][index];
    float BoxLL = InData[SC_LOW][index];
    double high = 0;
    double low = 0;
    int nearEqualCount = 0;
    int insideCandleCount = 0;
    SCString msg2;
    msg2.Format("begin loop");
    // sc.AddMessageToLog(msg2, 1);
    int rollingIndex = index;

    for (int i = 1; i < k_Box_NUM_OF_CANDLES + 1; i++)
    {

        is_inside_candle = IsInsideCandle(InData[SC_HIGH][rollingIndex], InData[SC_HIGH][rollingIndex - i], InData[SC_LOW][rollingIndex], InData[SC_LOW][rollingIndex - i], index);

        is_near_equal = IsNearEqual(InData[SC_HL][rollingIndex], InData[SC_HL][rollingIndex - i], InData, index, k_Box_SimilarityPercent);

        is_overlapping = (InData[SC_LAST][index] < (InData[SC_LAST][rollingIndex - 1] - PercentOfBodyLength(InData, rollingIndex - 1, 90)));

        BoxHighs += InData[SC_HIGH][rollingIndex - i];
        BoxLows += InData[SC_LOW][rollingIndex - i];

        msg2.Format("midline %f", InData[SC_HL][rollingIndex]);
        // sc.AddMessageToLog(msg2, 1);
        // msg2.Format("near equal bool %d\n", is_near_equal);
        // sc.AddMessageToLog(msg2, 1);

        // insideCandleCount = is_inside_candle && insideCandleCount + 1;
        BoxHH = InData[SC_HIGH][rollingIndex - i] > BoxHH ? InData[SC_HIGH][rollingIndex - i] : BoxHH;
        BoxLL = InData[SC_LOW][rollingIndex - i] < BoxLL ? InData[SC_LOW][rollingIndex - i] : BoxLL;
        high = sc.GetHighest(InData[SC_OPEN], sc.CurrentIndex - 1, 7);
        low = sc.GetLowest(InData[SC_LAST], sc.CurrentIndex - 1, 7);

        // msg2.Format("inside candle: '%s'", is_inside_candle);
        // sc.AddMessageToLog(msg2, 1);

        // msg2.Format("inside candle: '%s'", is_inside_candle);
        // create bar count total and if at least 6 return is box and then draw logic can extend based on bar count
        // if (is_overlapping)
        // {
        //     /* code */
        //     // msg2.Format("overlapping > 50\% %d\n", is_overlapping);
        //     // sc.AddMessageToLog(msg2, 1);
        // }

        if (is_near_equal)
        {
            nearEqualCount = nearEqualCount + 1;
            // ret_flag = false;
            msg2.Format("this is near equal: %i", nearEqualCount);
            // sc.AddMessageToLog(msg2, 1);
        }
        else
        {
            msg2.Format("this is not near equal: ");
            // sc.AddMessageToLog(msg2, 1);
        }
        rollingIndex = rollingIndex - 1;
        // msg2.Format("rolling index: %i", rollingIndex);
        // sc.AddMessageToLog(msg2, 1);
        // msg2.Format("inside candle count: '%i'", insideCandleCount);
        // sc.AddMessageToLog(msg2, 1);
    }
    msg2.Format("near equal count: %i", nearEqualCount);
    // sc.AddMessageToLog(msg2, 1);
    msg2.Format("end loop");
    // sc.AddMessageToLog(msg2, 1);

    if (nearEqualCount > 4)
    {
        ret_flag = true;
    }

    return ret_flag;
}
// /*==========================================================================*/
// inline bool IsNearEqual(double value1, double value2, SCBaseDataRef InData, int index, double percent)
// {
//     return abs(value1 - value2) < PercentOfCandleLength(InData, index, percent);
// }
/*==========================================================================*/
// const int    k_BullishSideBySideWhiteLines_TrendArea = 3;
// const int k_BullishSideBySideWhiteLines_PAST_INDEX = 3;
const double k_CandleSimilarityPercent = 7.0;

bool IsBox(SCStudyInterfaceRef sc, const s_CandleStickPatternsFinderSettings &settings, int index, int r_DrawingNumberForLastBar)
{
    // BULLISH SIDE-BY-SIDE WHITE LINES
    // 1. Uptrend
    // 2. The candles [index], [index-1] and [index-2] are white
    // 3. Maximum of the candle [index-2] is lower than minimum of the candle [index-1]
    // 4. Open prices and the sizes of the candles [index-1] and [index] are ALMOST the same

    /*  1. Market is characterized by uptrend.
    2. We see a white candlestick in the first day.
    3. Then we see another white candlestick on the second day with an upward gap.
    4. Finally, we see a white candlestick on the third day characterized by the same body length and whose closing price is equal to the close of the second day and a new high is established.*/

    // && (IsNearEqual(InData[SC_HIGH][index - 1], InData[SC_HIGH][index], InData, index, k_CandleSimilarityPercent)) && (IsNearEqual(InData[SC_LOW][index - 1], InData[SC_LOW][index], InData, index, k_CandleSimilarityPercent)

    SCBaseDataRef InData = sc.BaseData;
    bool ret_flag = false;
    if (
        (settings.UseTrendDetection == false || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_UP || sc.Subgraph[TREND_FOR_PATTERNS][index] == CANDLESTICK_TREND_DOWN) // check for the trend
        && IsNearEqualBars(InData, index, sc, r_DrawingNumberForLastBar))
    {
        ret_flag = true;
    }
    return ret_flag;
}
/*==========================================================================*/