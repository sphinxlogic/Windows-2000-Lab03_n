#ifndef _filtdata_h_
#define _filtdata_h_

// MSSample_DiagnosticSetting - MSSample_DiagnosticSetting
#define MSSample_DiagnosticSettingGuid \
    { 0x887dab33,0x5a16,0x4321, { 0xa0,0xbe,0xec,0x0d,0x01,0xb1,0x2e,0x1d } }

DEFINE_GUID(MSSample_DiagnosticSetting_GUID, \
            0x887dab33,0x5a16,0x4321,0xa0,0xbe,0xec,0x0d,0x01,0xb1,0x2e,0x1d);


typedef struct _MSSample_DiagnosticSetting
{
    // Sets the level of warning messages to be logged. If for example no warning information is required, the level would be set to "No Warnings" (value=0). Using "Missing Resources" (value=1) will cause warnings to be generated when required resources or hardware are not found. Setting the value to 2, "Testing Impacts", results in both missing resources and 'test impact' warnings (for example, multiple retries required) to be reported.
    USHORT TestWarningLevel;
    #define MSSample_DiagnosticSetting_TestWarningLevel_SIZE sizeof(USHORT)
    #define MSSample_DiagnosticSetting_TestWarningLevel_ID 1

    // When this flag is true, the diagnostic test will report 'soft errors'. In this context, a soft error is a message from the diagnostic reporting a known defect in the hardware or driver configuration, or execution environment.  Examples are: "Not enough memory", "Driver IOCTL not implemented", "Video RAM compare failed during polygon fill test (A known defect in the video chipset)", etc.
    BOOLEAN ReportSoftErrors;
    #define MSSample_DiagnosticSetting_ReportSoftErrors_SIZE sizeof(BOOLEAN)
    #define MSSample_DiagnosticSetting_ReportSoftErrors_ID 2

    // When this flag is true, the diagnostic test will report 'status messages'. In this context, a status message indicates that the diagnostic code is at a checkpoint. Examples are: "Completion of phase 1", "Complex pattern", etc.
    BOOLEAN ReportStatusMessages;
    #define MSSample_DiagnosticSetting_ReportStatusMessages_SIZE sizeof(BOOLEAN)
    #define MSSample_DiagnosticSetting_ReportStatusMessages_ID 3

    // When this flag is true, the test will halt after finding the first error.
    BOOLEAN HaltOnError;
    #define MSSample_DiagnosticSetting_HaltOnError_SIZE sizeof(BOOLEAN)
    #define MSSample_DiagnosticSetting_HaltOnError_ID 4

    // When this flag is true, the test software should attempt to run in an accelerated fashion either by reducing the coverage or number of tests performed.
    BOOLEAN QuickMode;
    #define MSSample_DiagnosticSetting_QuickMode_SIZE sizeof(BOOLEAN)
    #define MSSample_DiagnosticSetting_QuickMode_ID 5

    // Requests the diagnostic software to reduce test coverage to the specified percentage.  For example, a hard drive scan test could be asked to run at 50%. The most effective way to accomplish this is for the test software to scan every other track, as opposed to only scanning the first half of a drive. It is assumed that the effectiveness of the test is impacted proportional to the percentage of testing requested. Permissible values for this property range from 0 to 100. This property may not be applicable to all tests.  If it can be set for a test, the value 7 ("Supports PercentOfTestCoverage") should be entered into the DiagnosticTest's Characteristics array.
    UCHAR PercentOfTestCoverage;
    #define MSSample_DiagnosticSetting_PercentOfTestCoverage_SIZE sizeof(UCHAR)
    #define MSSample_DiagnosticSetting_PercentOfTestCoverage_ID 6

    // 
    UCHAR Reserved;
    #define MSSample_DiagnosticSetting_Reserved_SIZE sizeof(UCHAR)
    #define MSSample_DiagnosticSetting_Reserved_ID 7

} MSSample_DiagnosticSetting, *PMSSample_DiagnosticSetting;

// MSSample_DiagnosticSettingList - MSSample_DiagnosticSettingList
// Sample Diagnostic Test Settings List
#define MSSample_DiagnosticSettingListGuid \
    { 0x0f48a81f,0x8f26,0x404d, { 0xaa,0x87,0x0d,0x62,0xdd,0xe0,0x5d,0xa8 } }

DEFINE_GUID(MSSample_DiagnosticSettingList_GUID, \
            0x0f48a81f,0x8f26,0x404d,0xaa,0x87,0x0d,0x62,0xdd,0xe0,0x5d,0xa8);


typedef struct _MSSample_DiagnosticSettingList
{
    // 
    ULONG SettingCount;
    #define MSSample_DiagnosticSettingList_SettingCount_SIZE sizeof(ULONG)
    #define MSSample_DiagnosticSettingList_SettingCount_ID 1

    // 
    MSSample_DiagnosticSetting SettingList[1];
    #define MSSample_DiagnosticSettingList_SettingList_ID 2

} MSSample_DiagnosticSettingList, *PMSSample_DiagnosticSettingList;

// MSSample_DiagnosticResult - MSSample_DiagnosticResult
#define MSSample_DiagnosticResultGuid \
    { 0x91843bea,0x5562,0x4315, { 0xab,0x73,0x0c,0xb0,0x68,0x8d,0x02,0xe5 } }

DEFINE_GUID(MSSample_DiagnosticResult_GUID, \
            0x91843bea,0x5562,0x4315,0xab,0x73,0x0c,0xb0,0x68,0x8d,0x02,0xe5);


typedef struct _MSSample_DiagnosticResult
{
    // Estimated number of seconds to perform the DiagnosticTest indicated by the DiagnosticCreationClassName and DiagnosticName properties.  After the test has completed, the actual elapsed time can be determined by subtracting the TestStartTime from the TestCompletionTime. A similar property is defined in the association, DiagnosticTestForMSE. The difference between the two properties is that the value stored in the association is a generic test execution time for the Element and the Test. But, the value here (in DiagnosticResult) is the estimated time that this instance of testing would run.
    ULONG EstimatedTimeOfPerforming;
    #define MSSample_DiagnosticResult_EstimatedTimeOfPerforming_SIZE sizeof(ULONG)
    #define MSSample_DiagnosticResult_EstimatedTimeOfPerforming_ID 1


// Unknown
#define TestStateUnknown 0
// Other
#define TestStateOther 1
// Passed
#define TestStatePassed 2
// Failed
#define TestsStateFailed 3
// In Progress
#define TestStatInProgress 4
// Stopped
#define TestStateStopped 5

    // Describes how the test is progressing. For example, if the test was discontinued, the TestState will be "Stopped" (value=5), or if testing is currently executing, TestState will be "In Progress" (4).
    USHORT TestState;
    #define MSSample_DiagnosticResult_TestState_SIZE sizeof(USHORT)
    #define MSSample_DiagnosticResult_TestState_ID 2


// Hardware Paused
#define OtherTestStateHardwarePaused 0
// Device Power Up
#define OtherTestStateDevicePowerUp 1
// Pass With Flying Colors
#define OtherTestStatePassWithFlyingColors 2
// Offline Pending Execution
#define OfflinePendingExecution 3

    // When "Other" (value=1) is entered in the TestState property, OtherState has a value that is indexed into the value map to get the text representation.
    USHORT OtherStateDescription;
    #define MSSample_DiagnosticResult_OtherStateDescription_SIZE sizeof(USHORT)
    #define MSSample_DiagnosticResult_OtherStateDescription_ID 3

    // The percentage of the test that has executed thus far, if the TestState property is set to "In Progress" or the percentage of the complete test that was executed if the TestState property is set to any of the completed states ("Passed", "Failed" or "Stopped"). Final results may be based on less than 100% coverage due to the parameters defined in DiagnosticSetting (such as QuickMode, PercentOfTestCoverage or HaltOnError).
    UCHAR PercentComplete;
    #define MSSample_DiagnosticResult_PercentComplete_SIZE sizeof(UCHAR)
    #define MSSample_DiagnosticResult_PercentComplete_ID 4

    // 
    UCHAR Reserved1;
    #define MSSample_DiagnosticResult_Reserved1_SIZE sizeof(UCHAR)
    #define MSSample_DiagnosticResult_Reserved1_ID 5

    // 
    UCHAR Reserved2;
    #define MSSample_DiagnosticResult_Reserved2_SIZE sizeof(UCHAR)
    #define MSSample_DiagnosticResult_Reserved2_ID 6

    // 
    UCHAR Reserved3;
    #define MSSample_DiagnosticResult_Reserved3_SIZE sizeof(UCHAR)
    #define MSSample_DiagnosticResult_Reserved3_ID 7

    // 
    ULONG TestResultsCount;
    #define MSSample_DiagnosticResult_TestResultsCount_SIZE sizeof(ULONG)
    #define MSSample_DiagnosticResult_TestResultsCount_ID 8


// Passes and is happy
#define TestResultPassHappy 0
// Passes but is sad
#define TestResultPassSad 1
// Failed and is happy
#define TestResultFailHappy 2
// Failed but is sad
#define TestResultFailSad 3

    // This is an array of values that get mapped via the value map into strings by the provider
    ULONG TestResults[1];
    #define MSSample_DiagnosticResult_TestResults_ID 9

} MSSample_DiagnosticResult, *PMSSample_DiagnosticResult;

// MSSample_RunTestIn - MSSample_RunTestIn
#define MSSample_RunTestInGuid \
    { 0x3db46efb,0x34c3,0x4509, { 0xae,0x00,0x98,0x72,0x58,0x71,0xcb,0x59 } }

DEFINE_GUID(MSSample_RunTestIn_GUID, \
            0x3db46efb,0x34c3,0x4509,0xae,0x00,0x98,0x72,0x58,0x71,0xcb,0x59);


// Warning: Header for class MSSample_RunTestIn cannot be created
typedef struct _MSSample_RunTestIn
{
    char VariableData[1];

} MSSample_RunTestIn, *PMSSample_RunTestIn;

// MSSample_RunTestOut - MSSample_RunTestOut
#define MSSample_RunTestOutGuid \
    { 0x23dcd086,0x2111,0x4bda, { 0x9e,0x1c,0xe3,0x3c,0x29,0xa4,0xaa,0xd6 } }

DEFINE_GUID(MSSample_RunTestOut_GUID, \
            0x23dcd086,0x2111,0x4bda,0x9e,0x1c,0xe3,0x3c,0x29,0xa4,0xaa,0xd6);


typedef struct _MSSample_RunTestOut
{
    // 
    ULONG Result;
    #define MSSample_RunTestOut_Result_SIZE sizeof(ULONG)
    #define MSSample_RunTestOut_Result_ID 1

    // 
    MSSample_DiagnosticResult DiagResult;
    #define MSSample_RunTestOut_DiagResult_SIZE sizeof(MSSample_DiagnosticResult)
    #define MSSample_RunTestOut_DiagResult_ID 2

} MSSample_RunTestOut, *PMSSample_RunTestOut;

// MSSample_DiagnosticTest - MSSample_DiagnosticTest
// Sample Diagnostic Test
#define MSSample_DiagnosticTestGuid \
    { 0xb5c68c9e,0x39ad,0x4ad5, { 0xa8,0x44,0xaf,0x15,0x32,0xf4,0xbb,0x9f } }

DEFINE_GUID(MSSample_DiagnosticTest_GUID, \
            0xb5c68c9e,0x39ad,0x4ad5,0xa8,0x44,0xaf,0x15,0x32,0xf4,0xbb,0x9f);

//
// Method id definitions for MSSample_DiagnosticTest
#define RunTest     1
#define DiscontinueTest     2

// Warning: Header for class MSSample_DiagnosticTest cannot be created
typedef struct _MSSample_DiagnosticTest
{
    char VariableData[1];

} MSSample_DiagnosticTest, *PMSSample_DiagnosticTest;

// MSSample_OfflineDiagnosticTest - MSSample_OfflineDiagnosticTest
// Sample Offline Diagnostic Test
#define MSSample_OfflineDiagnosticTestGuid \
    { 0xc440ac3c,0xc739,0x424e, { 0x99,0xf4,0x6d,0x02,0xda,0x8b,0x83,0x13 } }

DEFINE_GUID(MSSample_OfflineDiagnosticTest_GUID, \
            0xc440ac3c,0xc739,0x424e,0x99,0xf4,0x6d,0x02,0xda,0x8b,0x83,0x13);

//
// Method id definitions for MSSample_OfflineDiagnosticTest
#define RunTest     1
#define DiscontinueTest     2

// Warning: Header for class MSSample_OfflineDiagnosticTest cannot be created
typedef struct _MSSample_OfflineDiagnosticTest
{
    char VariableData[1];

} MSSample_OfflineDiagnosticTest, *PMSSample_OfflineDiagnosticTest;

// MSSample_OfflineResult - MSSample_OfflineResult
// Sample Diagnostic Test Settings List
#define MSSample_OfflineResultGuid \
    { 0xd4a4ab8e,0x84db,0x4049, { 0x88,0x65,0x28,0xc3,0xe0,0xf1,0xa0,0x6f } }

DEFINE_GUID(MSSample_OfflineResult_GUID, \
            0xd4a4ab8e,0x84db,0x4049,0x88,0x65,0x28,0xc3,0xe0,0xf1,0xa0,0x6f);


// Warning: Header for class MSSample_OfflineResult cannot be created
typedef struct _MSSample_OfflineResult
{
    char VariableData[1];

} MSSample_OfflineResult, *PMSSample_OfflineResult;

#endif
