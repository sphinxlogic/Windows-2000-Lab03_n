Attribute VB_Name = "Utils"
'*******************************************************************************
'* MODULE:  Utils
'*    Contains utility routines used by the project.
'*
'* VERSIONS:
'*    1.00  9/9/97   Matthew Carroll
'*
'* Copyright © 1997 Microsoft Corp.  All rights reserved.
'*******************************************************************************
Option Explicit
Option Compare Text



'********************
'*** DECLARATIONS ***
'********************

Public Declare Function WinHelp Lib "user32" Alias "WinHelpA" _
      (ByVal hwnd As Long, ByVal lpHelpFile As String, _
      ByVal wCommand As Long, ByVal dwData As Long) As Long
Public Const HELP_FINDER = &HB&



'***************
'*** METHODS ***
'***************

'*******************************************************************************
'* SUB: DisplayError
'*    Displays an error message to the user.
'*
'* PARAMETERS:
'*    sEffectOfErr   String containing the effect of the error on the user.
'*    cnActive       ADOMD Connection on which error occurred if applicable
'*******************************************************************************
Public Sub DisplayError(sEffectOfErr As String, _
                        Optional cnActive As Connection = Nothing)
   Dim sMsg As String, erCur As Error
   Dim sVBErrDesc As String, sADOMDErrs As String, fUseVBErrDesc As Boolean
   
   '* Keep VB error description -- On Error Resume Next will clear
   sVBErrDesc = Err.Description
   
   On Error Resume Next
   
   '* Get ADOMD errors if available
   If cnActive Is Nothing Then
      fUseVBErrDesc = True
   ElseIf cnActive.Errors.Count = 0 Then
      fUseVBErrDesc = True
   Else
      For Each erCur In cnActive.Errors
         sADOMDErrs = sADOMDErrs & erCur.Description & vbCrLf
      Next erCur
   End If
   
   '* Check for error in retrieving ADOMD errors
   If Err.Number > 0 Then
      fUseVBErrDesc = True
   End If
   
   '* Use appropriate error descriptions(s)
   If fUseVBErrDesc Then
      sMsg = sVBErrDesc
   Else
      sMsg = sADOMDErrs
   End If
   
   '* Display error to user
   sMsg = sEffectOfErr & vbCrLf & sMsg
   MsgBox sMsg, vbOKOnly + vbExclamation, App.Title
   
End Sub

'*******************************************************************************
'* SUB: SetHourglass
'*    Provides a safer way to turn on and off the hourglass mouse pointer.
'*
'* PARAMETERS:
'*    fOn   If true the mouse cursor will be set to the hourglass cursor,
'*          if false the previous mouse cursor will be restored
'*******************************************************************************
Public Sub SetHourglass(fOn As Boolean)
   Static iOnCnt As Integer
   Static iOldMousePtr As Integer
      
   If fOn Then
      iOnCnt = iOnCnt + 1
      If iOnCnt = 1 Then
         iOldMousePtr = frmMain.MousePointer
         frmMain.MousePointer = vbHourglass
      End If
   Else
      iOnCnt = iOnCnt - 1
      If iOnCnt < 1 Then
         iOnCnt = 0
         frmMain.MousePointer = iOldMousePtr
      End If
   End If
      
End Sub

'*******************************************************************************
'* SUB: SetStatus
'*    Sets the status bar text of the applications main form.
'*
'* PARAMETERS:
'*    sStatus     Text to be displayed in the status bar.  If not specified
'*                the status bar text is cleared.  (Optional)
'*******************************************************************************
Public Sub SetStatus(Optional sStatus As String = "")
   With frmMain.stbMain
      .Panels("CurrentActivity").Text = sStatus
      .Refresh
   End With
End Sub

'*******************************************************************************
'* FUNCTION:  fIsLegalName
'*    Takes a name and returns true if it is an unqualified legal name.
'*
'* PARAMETERS:
'*    sName    Name to convert test
'*
'* RETURNS:
'*    Returns true if sName is a valid legal name, false otherwise
'*******************************************************************************
Public Function fIsLegalName(ByVal sName As String) As Boolean
   Dim sChar As String, iPos As Long, fUnmatchedEndDelimiter As Boolean
   Dim iEndPos As Long
   
   Const sAlpha = "abcdefghijklmnopqrstuvwxyz"
   Const sDigitsEtc = "1234567890_"
   
   '* Assume it's not legal
   fIsLegalName = False
      
   '* Delimited identifier?
   sChar = Left(sName, g_iStartDelimiterLen)
   If sChar = g_sStartDelimiter Then
      '* Length of delimited identifier excluding delimiters must be > 0
      If Len(sName) < g_iStartDelimiterLen + 1 + g_iEndDelimiterLen Then
         Exit Function
      End If
      
      '* Last character must be an end delimiter
      If Not Right(sName, g_iEndDelimiterLen) = g_sEndDelimiter Then
         Exit Function
      End If
      
      '* Any end delimiters within the identifier must be doubled up
      iPos = 1 + g_iStartDelimiterLen
      iEndPos = Len(sName) - g_iEndDelimiterLen
      Do Until iPos > iEndPos
         If fUnmatchedEndDelimiter Then
            If Mid(sName, iPos, g_iEndDelimiterLen) = g_sEndDelimiter Then
               fUnmatchedEndDelimiter = False
               iPos = iPos + g_iEndDelimiterLen
            Else
               Exit Do
            End If
         Else
            If Mid(sName, iPos, g_iEndDelimiterLen) = g_sEndDelimiter Then
               fUnmatchedEndDelimiter = True
               iPos = iPos + g_iEndDelimiterLen
            Else
               iPos = iPos + 1
            End If
         End If
      Loop
      If fUnmatchedEndDelimiter Then
         Exit Function
      End If
   
   Else
      '* Check length
      If Len(sName) = 0 Then Exit Function
      
      '* Check first char
      If InStr(sAlpha, sChar) = 0 Then Exit Function
      
      '* Check remaining char's
      For iPos = 2 To Len(sName)
         If InStr(sAlpha & sDigitsEtc, Mid(sName, iPos, 1)) = 0 Then
            Exit Function
         End If
      Next iPos
   End If
      
   
   '* If we made it this far, it's legal
   fIsLegalName = True
End Function

'*******************************************************************************
'* FUNCTION:  sGetLegalName
'*    Takes a name as input and returns a legal name.  (Delimits it if
'*    appropriate.)
'*
'* PARAMETERS:
'*    sName    Name to convert to legal name
'*
'* RETURNS:
'*    Returns the legal name equivalent of sName
'*******************************************************************************
Public Function sGetLegalName(sName As String) As String
   Dim sResults As String, iPos As Long, iEndPos As Long
   
   If fIsLegalName(sName) Or sName = vbNullString Then
      sResults = sName
   Else
      sResults = g_sStartDelimiter
      iPos = 1
      iEndPos = Len(sName)
      Do Until iPos > iEndPos
         If Mid(sName, iPos, g_iEndDelimiterLen) = g_sEndDelimiter Then
            sResults = sResults & g_sEndDelimiter & g_sEndDelimiter
            iPos = iPos + g_iEndDelimiterLen
         Else
            sResults = sResults & Mid(sName, iPos, 1)
            iPos = iPos + 1
         End If
      Loop
      sResults = sResults & g_sEndDelimiter
   End If
   
   Debug.Assert fIsLegalName(sResults) Or sResults = vbNullString
   
   sGetLegalName = sResults
End Function

'*******************************************************************************
'* FUNCTION:  sGetConnectStrValue
'*    Gets a property value from the specified connection string
'*
'* PARAMETERS:
'*    sConnectionString    String in which to look for property value
'*    sProperty            Property value to look for
'*
'* RETURNS:
'*    Returns the value associated with the specified property in the given
'*    connection string.  If the property is not found in the connection string
'*    an empty string is returned.
'*******************************************************************************
Public Function sGetConnectStrValue(sConnectionString As String, _
                                     sProperty As String) As String
   Dim iStartPos As Long, iEndPos As Long
   
   iStartPos = InStr(sConnectionString, sProperty & g_sCnStrValuePrefix)
   If iStartPos = 0 Then
      sGetConnectStrValue = vbNullString
   Else
      iStartPos = iStartPos + Len(sProperty & g_sCnStrValuePrefix)
      iEndPos = InStr(iStartPos, sConnectionString, g_sCnStrValueSuffix)
      If iEndPos = 0 Then
         iEndPos = Len(sConnectionString) + 1
      End If
      sGetConnectStrValue = _
            Mid(sConnectionString, iStartPos, iEndPos - iStartPos)
   End If
End Function

'*******************************************************************************
'* FUNCTION:  iGetWordLow
'*    Returns the low word (integer) of the specified double word (long)
'*
'* PARAMETERS:
'*    dwLong      Double word from which retrieve low word
'*
'* RETURNS:
'*    Returns the low word (integer) of the specified double word (long)
'*******************************************************************************
Public Function iGetWordLow(dwLong As Long) As Integer
   If dwLong And &H8000& Then
      iGetWordLow = CInt(dwLong And &H7FFF) Or &H8000
   Else
      iGetWordLow = CInt(dwLong And &H7FFF)
   End If
End Function

'*******************************************************************************
'* FUNCTION:  iGetWordHi
'*    Returns the high word (integer) of the specified double word (long)
'*
'* PARAMETERS:
'*    dwLong      Double word from which retrieve high word
'*
'* RETURNS:
'*    Returns the high word (integer) of the specified double word (long)
'*******************************************************************************
Public Function iGetWordHi(dwLong As Long) As Integer
   If dwLong And &H80000000 Then
      iGetWordHi = CInt((dwLong And &H7FFFFFFF) \ &H10000) Or &H8000
   Else
      iGetWordHi = CInt(dwLong \ &H10000)
   End If
End Function

'*******************************************************************************
'* FUNCTION:  iCombineWordHiLow
'*    Combines two words (integers) into a double word (long)
'*
'* PARAMETERS:
'*    wHi      Word (integer) to place in the high (most significant) position
'*    wLow     Word (integer) to place in the low (least significant) position
'*
'* RETURNS:
'*    Returns the double word (long) that is the combination of the two given
'*    words (integers)
'*******************************************************************************
Public Function iCombineWordHiLow(wHi As Integer, wLow As Integer) As Long
   Dim iResult As Long
   If wHi And &H8000 Then
      iResult = (CLng(wHi And &H7FFF) * &H10000) Or &H80000000
   Else
      iResult = (CLng(wHi) * &H10000)
   End If
   If wLow And &H8000 Then
      iResult = iResult Or (wLow And &H7FFF) Or &H8000&
   Else
      iResult = iResult Or wLow
   End If
   iCombineWordHiLow = iResult
End Function

'*******************************************************************************
'* FUNCTION:  sprintf
'*    Gets a format string with the shape of "xxxx xxxx %s1 xxxx %s2 ...."
'*    and replaces the first %s1 with the first DataString, the %s2 with the
'*    second DataString, etc.  Very usefull for later localization.
'*
'* PARAMETERS:
'*    FormatString   String into which data strings will be insterted
'*    DataStrings()  Strings to be substitued into the FormatString
'*
'* RETURNS:
'*    Returns a vertion of the FormatString in which all string placeholders
'*    have been replaced DataStrings.
'*******************************************************************************
Public Function sprintf(ByVal FormatString As String, ParamArray DataStrings()) As String
    Dim i As Integer
    Dim pos As Integer
    Dim placeholder As String
    
    For i = 0 To UBound(DataStrings)
        placeholder = "%s" + Trim(Str(i + 1))
        pos = InStr(FormatString, placeholder)
        
        While pos > 0
            FormatString = Left(FormatString, pos - 1) + DataStrings(i) + Mid(FormatString, pos + Len(placeholder))
        
            pos = InStr(FormatString, placeholder)
        Wend
    Next
    
    sprintf = FormatString
    
End Function

