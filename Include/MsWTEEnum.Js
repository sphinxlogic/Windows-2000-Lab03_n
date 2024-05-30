/*****************************************************************************
 *                                                                           *
 *  Copyright (c) 1991-1999, Microsoft Corp. All rights reserved.            *
 *                                                                           *
 * This is prerelease software and is provided as is and Microsoft makes no  *
 * warranties,  either express or implied. The entire risk of the use or the *
 * results of the use of this prerelease software remains with the user.     *
 *****************************************************************************/

wteConsNone = 0;
wteConsTerminator = 1;
wteConsLegalDigits = 2;
wteConsBoundaries = 4;
wteConsAny = 8;
wteConsMax = 2147483647;

wteServicePauseSoft = 128;
wteServiceStopSoft = 129;
wteServiceFlushLog = 130;
wteServiceRefreshStorage = 131;
wteServiceMax = 255;

wteLogFullPath = 0;
wteLogRelativePath = 1;

wteLineError = 0;
wteLineIdle = 1;
wteLineInbound = 2;
wteLineOutbound = 4;

wteLogInvalidType = -1;
wteLogNone = 0;
wteLogToFile = 1;
wteLogToSql = 2;
wteDisabledLogToFile = 3;
wteDisabledLogToSql = 4;

wteLogInvalidPeriod = -1;
wteLogNoPeriod = 0;
wteLogDaily = 1;
wteLogWeekly = 2;
wteLogMonthly = 3;
wteLogYearly = 4;

wteEndReasonScopeEnd = 0;
wteEndReasonCutThroughChanged = 1;
wteEndReasonIntrinsicControl = 2;
wteEndReasonTable = 3;
wteEndReasonIncompatibleMenuItemType = 4;
wteEndReasonForm = 5;
wteEndReasonPageEnd = 6;
wteEndReasonSelectionTimeout = 7;
wteEndReasonSelectionError = 8;
wteEndReasonMax = 2147483647;

wteDispidApplicationEventOnOffering = 1;
wteDispidApplicationEventOnConnected = 2;
wteDispidApplicationEventOnDisconnected = 3;
wteDispidApplicationEventOnDigit = 4;
wteDispidApplicationEventOnDigitsUsed = 5;
wteDispidApplicationEventOnBeforeNavigate = 6;
wteDispidApplicationEventOnNavigateComplete = 7;
wteDispidApplicationEventOnDocumentComplete = 8;
wteDispidApplicationEventOnTagBegin = 9;
wteDispidApplicationEventOnTagEnd = 10;
wteDispidApplicationEventOnSessionValue = 11;
wteDispidApplicationEventOnTelephonyStepEnd = 12;
wteDispidApplicationEventOnSessionEnd = 13;

wteAuthoringError = 0x1;
wteCallAvailable = 0x2;
wteApplicationConnect = 0x4;
wteNavigate = 0x8;
wteCallForward = 0x10;
wteCallDisconnect = 0x20;
wteApplicationTermination = 0x40;
wteInputTimeout = 0x80;
wteCallInfoChanged = 0x100;
wteCallAnswer = 0x200;
wteDtmfInputError = 0x400;
wteCustomLog = 0x800;
wteDtmfReceived = 0x1000;
wteSpeechInputData = 0x2000;
wteSpeechInputFailed = 0x4000;
wteRecordData = 0x8000;
wteRecordFailed = 0x10000;
wteAudioFailure = 0x20000;

wteSessionID = 0x1;
wteLogTime = 0x2;
wteEventClass = 0x4;
wteMachineName = 0x8;
wtePortGroupID = 0x10;
wtePortID = 0x20;
wteCallerID = 0x40;
wteCalledID = 0x80;
wteReason = 0x100;
wteApplicationName = 0x200;
wteMedia = 0x400;
wtePage = 0x800;
wteHTMLID = 0x1000;
wteDTMFValue = 0x2000;
wteDestAddress = 0x4000;
wteHangReason = 0x8000;
wteTransferType = 0x10000;
wteErrorType = 0x20000;
wteInputRecordFile = 0x40000;
wteCustom = 0x80000;

