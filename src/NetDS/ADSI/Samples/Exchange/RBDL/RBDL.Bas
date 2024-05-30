Attribute VB_Name = "modRBDL"
'
' Author: Greg Visscher
' Microsoft Corporation
'
' Rules Based Distribution Lists
'
' RBDL.EXE will automatically populate and update Microsoft Exchange "rules based
' distribution lists". The membership in a "rules based distribution list" is
' determined by criteria based upon Exchange directory attributes. RBDL.EXE determines
' which distribution lists to modify and the precise membership of the distribution
' list based upon a criteria string that is stored within the DL itself.  This
' functionality allows RBDL.EXE to populate and keep up to date DLs like
'     "All mailboxes in California" or
'     "All mailboxes on ServerX" or
'     "All people in the Sales Department that are not Temporary Employees".
'
' Since RBDL.EXE uses LDAP v3 to update the directory, at least one Exchange 5.5
' server per organization is required.

' run with the following command line parameter
' /container:"LDAP://server/o=organization/ou=site/cn=Recipients"

Option Explicit

Const RBDL_PREFIX = "RBDL"
Const E_SERVER_DOWN = &H8007003A
Const E_CONTAINER_DOES_NOT_EXIST = &H80070002
Const E_INVALID_SYNTAX = &H80004005

Declare Sub Sleep Lib "kernel32" (ByVal dwMilliseconds As Long)

Declare Function RegisterEventSource Lib "advapi32.dll" Alias "RegisterEventSourceA" (ByVal lpUNCServerName As String, ByVal lpSourceName As String) As Long
Declare Function DeregisterEventSource Lib "advapi32.dll" (ByVal hEventLog As Long) As Long
Declare Function ReportEvent Lib "advapi32.dll" Alias "ReportEventA" (ByVal hEventLog As Long, ByVal wType As Integer, ByVal wCategory As Integer, ByVal dwEventID As Long, ByVal lpUserSid As Any, ByVal wNumStrings As Integer, ByVal dwDataSize As Long, plpStrings As Long, lpRawData As Any) As Boolean
Declare Function GetLastError Lib "kernel32" () As Long
Declare Sub CopyMemory Lib "kernel32" Alias "RtlMoveMemory" (hpvDest As Any, hpvSource As Any, ByVal cbCopy As Long)
Declare Function GlobalAlloc Lib "kernel32" (ByVal wFlags As Long, ByVal dwBytes As Long) As Long
Declare Function GlobalFree Lib "kernel32" (ByVal hMem As Long) As Long
Public Const EVENTLOG_SUCCESS = 0
Public Const EVENTLOG_ERROR_TYPE = 1
Public Const EVENTLOG_WARNING_TYPE = 2
Public Const EVENTLOG_INFORMATION_TYPE = 4
Public Const EVENTLOG_AUDIT_SUCCESS = 8
Public Const EVENTLOG_AUDIT_FAILURE = 10

Sub Main()
    On Error Resume Next
    Const EVENTLOGMSG_STARTING = "Starting Distribution List Auto-Generation"
    Const EVENTLOGMSG_MISSING_RBDL_DL = "No Distribution Lists are setup " _
        & "for Auto-Generation.  Please see setup instructions.  " _
        & "The Admin property on the Distribution List must contain " _
        & "the ADODB search string.  The DLs must also reside in the " _
        & "container tree provided on the command line"
    Const REGKEY_THRESHOLD_SETTINGS = "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\RBDL"
    Const REGVALUE_MAX_THRESHOLD = "EntriesPerDistributionListMaximumThreshold"
    Const REGVALUE_WARNING_THRESHOLD = "EntriesPerDistributionListWarningThreshold"
    
    Dim strADOQueryDLs As String
    Dim strADOQueryRecips As String
    Dim objDLrs As New ADODB.RecordSet
    Dim objDLConn As New ADODB.Connection
    Dim objRecipRs As New ADODB.RecordSet
    Dim objRecipConn As New ADODB.Connection
    Dim objTempTableRs As New ADODB.RecordSet
    Dim objTempTableConn As New ADODB.Connection
        
    Dim Member As IADs
    Dim iadsDL As IADsGroup
    
    Dim strDLADsPath As String ' the ads path for the Dist List being updated
    Dim strDLContainer As String  ' the ads path to search for DLs.  passed via command line
    Dim strTempDatabasePath As String
    Dim strDLAdminDescription As String  ' The string in the Admin Note in the the Dist List being updated
    
    Dim intStartPos As Integer
    Dim lngLoopDelayMinutes As Long
    Dim dlngLoopDelayMilliSec As Double
    Dim lngMemberCount As Long, lngRecipCount As Long
    Dim strErrorMsg As String
    Dim StartTime As String, StopTime As String
    Dim lngMaxEntriesPerDL As Long, lngWarningEntriesPerDL As Long
    ' todo  replace the following two hardcoded entries with reg values
    lngMaxEntriesPerDL = 5000
    lngWarningEntriesPerDL = 3000
    
    ParseCommandLine strDLContainer, lngLoopDelayMinutes
    If strDLContainer = "" Then
        Call LogNTEvent("The LDAP path to the container that contains the distribution lists to be rebuilt must be passed via the command line using the /container: parameter.", EVENTLOG_ERROR_TYPE, 0)
        End
    End If
' todo  - make sure we can open container before proceeding
    
    If lngLoopDelayMinutes > 0 Then
        dlngLoopDelayMilliSec = lngLoopDelayMinutes * 1000 * 60
    Else
        dlngLoopDelayMilliSec = 0
    End If
    
    Do
        StartTime = Now()
        Call LogNTEvent(EVENTLOGMSG_STARTING, EVENTLOG_INFORMATION_TYPE, 0)
        
        ' Setup the ADO Connection and the record set object
        '   for the RBDL Distribution List query
        InitializeRSConnection objDLConn, objDLrs
                        
        'Setup the ADO Connection and the record set object
        '   for the matching Recipient queries
        InitializeRSConnection objRecipConn, objRecipRs

        ' Create a Record set that contains the Distribution Lists that
        '    have a Admin Note field that starts with "RBDL"
        strADOQueryDLs = "<" & strDLContainer & _
            ">;(&(objectClass=groupOfNames)(Admin-Description=" _
            & RBDL_PREFIX & "*));cn,adspath,Admin-Description;subtree"
            
        objDLrs.Source = strADOQueryDLs
        objDLrs.Open
        
        If Err.Number = 0 Then
        
            If objDLrs.EOF Then
'todo rephrase error message
                Call LogNTEvent(EVENTLOGMSG_MISSING_RBDL_DL, EVENTLOG_WARNING_TYPE, 1001)
            Else
                ' Create a Temporary Database
                strTempDatabasePath = CreateTemporaryDatabase
                
                ' Open a Connection to it
                objTempTableConn.Open "DRIVER=Microsoft Access Driver (*.mdb);DBQ=" & strTempDatabasePath
                
                While Not objDLrs.EOF
                    ' Get the ADSpath and the Admin Note from the current DL being generated
                    strDLADsPath = objDLrs.Fields("adspath")
                    strDLAdminDescription = objDLrs.Fields("Admin-Description")
                    ' Find the = after the RBDL prefix
                    intStartPos = InStr(strDLAdminDescription, "=")
                    If intStartPos > 0 Then
                        Err.Clear
                        strADOQueryRecips = Trim(Mid(strDLAdminDescription, intStartPos + 1))
                        ' look for "adspath" in attribute field of the Connection text (after 2nd ";")
                        ' if it doesn't exist, raise error and don't rebuild DL
                        If InStr(InStr(InStr(strADOQueryRecips, ";"), strADOQueryRecips, ";"), LCase(strADOQueryRecips), "adspath") > 0 Then
                            'Find the Recipients that are supposed to be in the DL
                            objRecipRs.Source = strADOQueryRecips
                            objRecipRs.Open
                        Else
                            Err.Raise E_INVALID_SYNTAX, "RBDL", "Adspath must be included in attributes field"
                        End If
                        
                        'Update the DL if the Recipient Query suceeded
                        If Err.Number = 0 Then
                           ' Clear old temp table
                            objTempTableConn.Execute ("Drop table temptable1")  ' error 80040e14 means table doesn't exist
                            Err.Clear '     Clear the error if the table didn't exist (i.e. new database)
                            objTempTableConn.Execute ("create table temptable1 (ADsPath TEXT (255) CONSTRAINT PrimaryKey PRIMARY KEY)")
                            
                            ' Create an ADSI object pointing to the Distribution List
                            Set iadsDL = GetObject(strDLADsPath)
                            
                            lngRecipCount = 0
                            ' Add the Recipients that match the criteria to the DL
                            While Not objRecipRs.EOF _
                                And (iadsDL.Members.Count < lngMaxEntriesPerDL) _
                                And (lngRecipCount < lngMaxEntriesPerDL)
                            
                                ' Check to make sure that we are not adding the DL to itself.
                                If objRecipRs.Fields("adspath") <> strDLADsPath Then
                                    iadsDL.Add (objRecipRs.Fields("adspath"))
                                    lngRecipCount = lngRecipCount + 1
                                    ' adding the recipient is quicker and more efficient than checking ISMEMBER
                                    ' Additionally, USN is not increased if recip already eists in DLx
                                    objTempTableConn.Execute "INSERT INTO temptable1 (ADsPath) VALUES ('" & objRecipRs.Fields("adspath") & "')"
                                    objRecipRs.MoveNext
                                End If
                            Wend
                            
                            lngMemberCount = iadsDL.Members.Count
                                                        
                            ' Check to see if Maximum threshold has been reached.
                            If lngMemberCount >= lngMaxEntriesPerDL Then
                                strErrorMsg = iadsDL.ADsPath & "has exceeded the maximum threshold for entries per Distribution List (" & CStr(lngMaxEntriesPerDL) & ").  No more object will be added to this Distribution List."
                                Call LogNTEvent(strErrorMsg, EVENTLOG_ERROR_TYPE, 1001)
                                
                            'Check whether the WARNING Threshold for max objects per DL has been crossed
                            ElseIf lngMemberCount >= lngWarningEntriesPerDL Then
                                strErrorMsg = iadsDL.ADsPath & "is approaching the maximum number of objects allowed per DL. (" & CStr(lngMaxEntriesPerDL) & ").  Objects will be added to this Distribution List until the maximum threshold is reached."
                                Call LogNTEvent(strErrorMsg, EVENTLOG_WARNING_TYPE, 1001)
                            End If
                            
                            If lngMemberCount > lngRecipCount Then
                                ' only need to execute this section if there are members to remove from the list
        
                                For Each Member In iadsDL.Members
                                    ' Clear the Distribution List of members that aren't in
                                    ' the temporary table and hence aren't in Query result set
                                    ' TODO test that large DLs don't exceed LDAP max settings
                                    objTempTableRs.ActiveConnection = objTempTableConn
                                    objTempTableRs.Source = "Select ADsPath From temptable1 WHERE ADsPath='" & Member.ADsPath & "'"
                                    objTempTableRs.Open
                                    If objTempTableRs.EOF Then
                                        iadsDL.Remove (Member.ADsPath)
                                        lngMemberCount = lngMemberCount - 1
                                        If lngMemberCount <= lngRecipCount Then
                                            Exit For
                                            ' We only need to continue removing members until all members that
                                            ' should be removed are removed.  Since we added all appropriate members
                                            ' before executing this portion, the number of members on the list
                                            ' should be equal to the number of people we added to the list.
                                            ' ** If it isn't we still have people to remove from the list.  **
                                        End If
                                    End If
                                    objTempTableRs.Close
                                Next
                            End If
                        ElseIf Err.Number = E_INVALID_SYNTAX Then
'todo rephrase error message
                            strErrorMsg = "Please correct the RBDL Syntax for " & strDLADsPath
                            Call LogNTEvent(strErrorMsg, EVENTLOG_ERROR_TYPE, 1001)
                        End If ' Err.Number = 0
                        
                        ' Close the Recipient Recordset
                        objRecipRs.Close
                    
                    End If ' intStartPos > 0
                        
                    'move to the next Distribution List
                    objDLrs.MoveNext
                
                Wend ' Not objDLrs.EOF
                
                ' Delete the Temporary database
                objTempTableConn.Close
                Kill strTempDatabasePath
                
            End If ' Else (not objDLrs.EOF)
        ElseIf Err.Number = E_SERVER_DOWN Then
'todo rephrase error message
            strErrorMsg = "Server is Down.  Please check network connection.  " & vbLf & "Unable to contact " & strDLContainer
            Call LogNTEvent(strErrorMsg, EVENTLOG_ERROR_TYPE, 1001)
            
        ElseIf Err.Number = E_CONTAINER_DOES_NOT_EXIST Then
'todo rephrase error message
            strErrorMsg = "Container " & strDLContainer & " does not exist.  Please correct the /container parameter."
            Call LogNTEvent(strErrorMsg, EVENTLOG_ERROR_TYPE, 1001)
            
        Else ' Err.Number <> 0
'todo rephrase error message
            strErrorMsg = "Error = " & Str(Err.Number) & " (" & Hex(Err.Number) & ") " & Err.Description
            Call LogNTEvent(strErrorMsg, EVENTLOG_ERROR_TYPE, 1001)
        End If ' Else (Err.Number)
        
        objDLConn.Close
        objDLrs.Close
        objRecipConn.Close
        Err.Clear
        StopTime = Now()
'todo rephrase error message
        strErrorMsg = "Distribution List Auto-Generation is complete.  Start Time = " & StartTime & vbLf & "Stop Time  = " & StopTime
        Call LogNTEvent(strErrorMsg, EVENTLOG_INFORMATION_TYPE, 1001)
        Sleep (dlngLoopDelayMilliSec)
    Loop Until lngLoopDelayMinutes < 0
End Sub

Private Function CreateTemporaryDatabase(Optional Directory As String)
    ' This function will create a temporary database.
    ' If no directory is supplied the database will be created in the
    ' temp directory (as specified in the TEMP environment variable).
    ' The File will use the constant TEMPFILE_PREFIX as the
    ' filename followed by a random number to ensure uniqueness.
    
    On Local Error Resume Next
    
    Const TEMPFILE_PREFIX = "RBDL"
    Dim db1 As DAO.Database
    Dim iRandomPrefix As Integer
    Dim sRandomPrefix As String
    Dim sTempFilePath As String
    
    Randomize
    iRandomPrefix = Int((99999 * Rnd) + 1)
    sRandomPrefix = "00000000" & Trim(Str(iRandomPrefix))
    
    sTempFilePath = Directory
    
    ' Build the FilePath String
    If sTempFilePath = "" Then sTempFilePath = Environ("TEMP")
    If Right(sTempFilePath, 1) <> "\" Then sTempFilePath = sTempFilePath & "\"
    sTempFilePath = sTempFilePath & TEMPFILE_PREFIX
    sTempFilePath = sTempFilePath & Right(sRandomPrefix, 4)
    sTempFilePath = sTempFilePath & ".mdb"
    
    ' Check to see if the file exists if not create it
    If Len(Dir(sTempFilePath)) = 0 Then
        Set db1 = CreateDatabase(sTempFilePath, dbLangGeneral)
        Set db1 = Nothing
    End If
    CreateTemporaryDatabase = sTempFilePath
End Function

Private Sub InitializeRSConnection(Connection As ADODB.Connection, RecordSet As ADODB.RecordSet)
    Connection.Provider = "ADSDSOObject"
    Connection.ConnectionString = "ADs Provider"
    Connection.Open
    
    Set RecordSet = New ADODB.RecordSet
    RecordSet.ActiveConnection = Connection
    RecordSet.Properties.Item("page size").Value = 100
End Sub
Private Sub ParseCommandLine(DLSearchContainer As String, LoopDelay As Long)
    ' /pause:nnnn
    ' /container:"LDAP://gregv2/o=Acme Corporation/ou=Foster City/cn=Distribution Lists"
    
    Dim sCommandLine As String
    Dim sLowercaseCommandLine As String
    Dim iContainerPos As Integer
    Dim iDelayPos As Integer
    Dim iLength As Integer
    Dim sLoopDelay As String
    
    sCommandLine = Command()
    sLowercaseCommandLine = LCase(sCommandLine)
      
    iLength = Len(sCommandLine)
    iContainerPos = InStr(sLowercaseCommandLine, "/container:")
    iDelayPos = InStr(sLowercaseCommandLine, "/pause:")
    
    If iContainerPos < 1 Then iContainerPos = iLength
    If iDelayPos < 1 Then iDelayPos = iLength
    
    If iContainerPos > iDelayPos Then
        sLoopDelay = Mid(sCommandLine, iDelayPos, iContainerPos - iDelayPos)
        DLSearchContainer = Mid(sCommandLine, iContainerPos, iLength - iContainerPos + 1)
    Else
        DLSearchContainer = Mid(sCommandLine, iContainerPos, iDelayPos - iContainerPos)
        sLoopDelay = Mid(sCommandLine, iDelayPos, iLength - iDelayPos + 1)
    End If
    
    'Cleanup the variables and return
    DLSearchContainer = Trim(DLSearchContainer)
    sLoopDelay = Trim(sLoopDelay)
    If Left(LCase(DLSearchContainer), 11) = "/container:" Then DLSearchContainer = Mid(DLSearchContainer, 12)
    If Left(LCase(DLSearchContainer), 1) = """" Then DLSearchContainer = Mid(DLSearchContainer, 2)
    If Right(LCase(DLSearchContainer), 1) = """" Then DLSearchContainer = Left(DLSearchContainer, Len(DLSearchContainer) - 1)
    If Left(LCase(DLSearchContainer), 1) = "'" Then DLSearchContainer = Mid(DLSearchContainer, 2)
    If Right(LCase(DLSearchContainer), 1) = "'" Then DLSearchContainer = Left(DLSearchContainer, Len(DLSearchContainer) - 1)
    If Left(LCase(sLoopDelay), 7) = "/pause:" Then sLoopDelay = Mid(sLoopDelay, 8)
    If IsNumeric(sLoopDelay) Then
        LoopDelay = Int(Val(sLoopDelay))
    Else
        LoopDelay = -1
    End If
End Sub


Private Sub LogNTEvent(sString As String, iLogType As Integer, iEventID As Long)
    Dim bRC As Boolean
    Dim iNumStrings As Integer
    Dim hEventLog As Long
    Dim hMsgs As Long
    Dim cbStringSize As Long
    hEventLog = RegisterEventSource("", App.Title)
    cbStringSize = Len(sString) + 1
    hMsgs = GlobalAlloc(&H40, cbStringSize)
    CopyMemory ByVal hMsgs, ByVal sString, cbStringSize
    iNumStrings = 1
    If ReportEvent(hEventLog, iLogType, 0, iEventID, 0&, iNumStrings, cbStringSize, hMsgs, hMsgs) = 0 Then
       MsgBox GetLastError()
    End If
    Call GlobalFree(hMsgs)
    DeregisterEventSource (hEventLog)
End Sub
