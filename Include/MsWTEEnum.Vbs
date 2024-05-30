''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'   Copyright (c) 1991-1999, Microsoft Corp. All rights reserved.              '
'                                                                              '
' This is prerelease software and is provided as is and Microsoft makes no     '
' warranties,  either express or implied. The entire risk of the use or the    '
' results of the use of this prerelease software remains with the user.        '
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

const wteConsNone = 0
const wteConsTerminator = 1
const wteConsLegalDigits = 2
const wteConsBoundaries = 4
const wteConsAny = 8
const wteConsMax = 2147483647

const wteServicePauseSoft = 128
const wteServiceStopSoft = 129
const wteServiceFlushLog = 130
const wteServiceRefreshStorage = 131
const wteServiceMax = 255

const wteLogFullPath = 0
const wteLogRelativePath = 1

const wteLineError = 0
const wteLineIdle = 1
const wteLineInbound = 2
const wteLineOutbound = 4

const wteLogInvalidType = -1
const wteLogNone = 0
const wteLogToFile = 1
const wteLogToSql = 2
const wteDisabledLogToFile = 3
const wteDisabledLogToSql = 4

const wteLogInvalidPeriod = -1
const wteLogNoPeriod = 0
const wteLogDaily = 1
const wteLogWeekly = 2
const wteLogMonthly = 3
const wteLogYearly = 4

const wteEndReasonScopeEnd = 0
const wteEndReasonCutThroughChanged = 1
const wteEndReasonIntrinsicControl = 2
const wteEndReasonTable = 3
const wteEndReasonIncompatibleMenuItemType = 4
const wteEndReasonForm = 5
const wteEndReasonPageEnd = 6
const wteEndReasonSelectionTimeout = 7
const wteEndReasonSelectionError = 8
const wteEndReasonMax = 2147483647

const wteDispidApplicationEventOnOffering = 1
const wteDispidApplicationEventOnConnected = 2
const wteDispidApplicationEventOnDisconnected = 3
const wteDispidApplicationEventOnDigit = 4
const wteDispidApplicationEventOnDigitsUsed = 5
const wteDispidApplicationEventOnBeforeNavigate = 6
const wteDispidApplicationEventOnNavigateComplete = 7
const wteDispidApplicationEventOnDocumentComplete = 8
const wteDispidApplicationEventOnTagBegin = 9
const wteDispidApplicationEventOnTagEnd = 10
const wteDispidApplicationEventOnSessionValue = 11
const wteDispidApplicationEventOnTelephonyStepEnd = 12
const wteDispidApplicationEventOnSessionEnd = 13

const wteAuthoringError = &H1&
const wteCallAvailable = &H2&
const wteApplicationConnect = &H4&
const wteNavigate = &H8&
const wteCallForward = &H10&
const wteCallDisconnect = &H20&
const wteApplicationTermination = &H40&
const wteInputTimeout = &H80&
const wteCallInfoChanged = &H100&
const wteCallAnswer = &H200&
const wteDtmfInputError = &H400&
const wteCustomLog = &H800&
const wteDtmfReceived = &H1000&
const wteSpeechInputData = &H2000&
const wteSpeechInputFailed = &H4000&
const wteRecordData = &H8000&
const wteRecordFailed = &H10000&
const wteAudioFailure = &H20000&

const wteSessionID = &H1&
const wteLogTime = &H2&
const wteEventClass = &H4&
const wteMachineName = &H8&
const wtePortGroupID = &H10&
const wtePortID = &H20&
const wteCallerID = &H40&
const wteCalledID = &H80&
const wteReason = &H100&
const wteApplicationName = &H200&
const wteMedia = &H400&
const wtePage = &H800&
const wteHTMLID = &H1000&
const wteDTMFValue = &H2000&
const wteDestAddress = &H4000&
const wteHangReason = &H8000&
const wteTransferType = &H10000&
const wteErrorType = &H20000&
const wteInputRecordFile = &H40000&
const wteCustom = &H80000&

