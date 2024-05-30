VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 1  'NoTransaction
END
Attribute VB_Name = "Critique"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

Public ConnectionString As String
Private MTS As New MTSEnvironment

Private Const NERR_NOUPDATE = &H800C0159
Private Const SERR_NOUPDATE = "Critique not approved. Use DeleteRecordByCritiqueNo instead."

Private Sub Class_Initialize()
   ConnectionString = "DSN=Fmlib;UID=sa;PWD="
End Sub

Public Function AddRecord(ByVal BibNo As Long, ByVal BorrowerNo As Long, _
                          ByVal CritiqueTitle As String, ByVal MessageID As String, _
                          ByVal Rating As Integer, ByVal DateOfCritique As Date, _
                          ByVal IsApproved As Boolean, Optional ByVal ConnectionString As String) As Long
   Dim oRs As ADODB.Recordset
   Dim varFields, varValues
   
   On Error GoTo ErrHandler
   
   If ConnectionString <> "" Then
      Me.ConnectionString = ConnectionString
   End If
   
   varFields = Array("bib#", "borrower#", "title", "objectID", "rating", "dateOfCritique", "isApproved")
   varValues = Array(BibNo, BorrowerNo, CritiqueTitle, MessageID, Rating, CStr(DateOfCritique), IIf(IsApproved, 1, 0))
   
   Set oRs = MTS.CreateInstance("ADODB.Recordset")
   
   oRs.Open "Critique", Me.ConnectionString, adOpenKeyset, adLockOptimistic, adCmdTableDirect
   
   oRs.AddNew varFields, varValues
   oRs.Resync
   AddRecord = oRs("Critique#").Value
   
   oRs.Close
   Set oRs = Nothing
   MTS.SetComplete
   Exit Function
   
ErrHandler:
   MTS.SetAbort
   Err.Raise Err.Number, Err.Source, Err.Description
End Function

' If called in response to an approval message, only
' CritiqueNo, MessageID and IsApproved are required
' Do not pass optional params for review if this is an approver message!

Public Sub UpdateRecord(ByVal CritiqueNo As Long, ByVal MessageID As String, _
                        ByVal IsApproved As Boolean, Optional ByVal OverAllRating As Integer, _
                        Optional ByVal CritiqueTitle As String, Optional ByVal CritiqueDate As Date, _
                        Optional ByVal ConnectionString As String)
   On Error GoTo ErrHandler
   Dim oRs As ADODB.Recordset
   
   If ConnectionString <> "" Then
      Me.ConnectionString = ConnectionString
   End If
   
   Set oRs = MTS.CreateInstance("ADODB.Recordset")
   
   oRs.Filter = "Critique#=" & CritiqueNo
   oRs.Open "Critique", Me.ConnectionString, adOpenStatic, adLockOptimistic, adCmdTable
   
   If Not oRs.EOF Then
      ' It is update from reviewer
      If CritiqueTitle <> "" Then
         oRs("objectId") = MessageID
         oRs("Title") = CritiqueTitle
         oRs("Rating") = OverAllRating
         oRs("dateOfCritique") = CStr(CritiqueDate)
         oRs("isApproved") = IIf(IsApproved, 1, 0)
      ' It is update from approver
      ElseIf IsApproved Then
         oRs("objectID") = MessageID
         oRs("isApproved") = 1
      Else
         ' Not approved, should use DeleteRecord instead
         Err.Raise NERR_NOUPDATE, "UpdateRecord", SERR_NOUPDATE
      End If
      oRs.Update
   End If
   
   oRs.Close
   Set oRs = Nothing
   MTS.SetComplete
   Exit Sub

ErrHandler:
   MTS.SetAbort
   Err.Raise Err.Number, Err.Source, Err.Description
End Sub

' Called from OnMessageDeleted event
Public Sub DeleteRecordByObjectID(ByVal objectID As String, Optional ByVal ConnectionString As String)
   If ConnectionString <> "" Then
      Me.ConnectionString = ConnectionString
   End If
   
   DeleteRecord "ObjectID Like '%" & objectID & "0000'", False
End Sub

' Called when approver rejected the critique
Public Sub DeleteRecordByCritiqueNo(ByVal CritiqueNo As Long, Optional ByVal ConnectionString As String)
   If ConnectionString <> "" Then
      Me.ConnectionString = ConnectionString
   End If
   
   DeleteRecord "Critique#=" & CritiqueNo, True
End Sub

Private Sub DeleteRecord(ByVal Filter As String, ByVal IsApprover As Boolean)
   Dim oRs As ADODB.Recordset
   Const Approved = 1
   Const Rejected = 0
   
   On Error GoTo ErrHandler
   
   Set oRs = MTS.CreateInstance("ADODB.Recordset")
   
   oRs.Filter = Filter
   oRs.Open "Critique", Me.ConnectionString, adOpenStatic, adLockOptimistic, adCmdTableDirect
   
   If Not oRs.EOF Then
      ' Only delete if critique has been approved
      If IsApprover Or Approved = oRs("isApproved") Then
         oRs.Delete
      End If
   End If
   
   oRs.Close
   Set oRs = Nothing
   MTS.SetComplete
   Exit Sub

ErrHandler:
   MTS.SetAbort
   Err.Raise Err.Number, Err.Source, Err.Description
End Sub

Public Function BorrowerInfo(ByVal LDAPString As String, ByVal Server As String) As Long
   Dim varValues() As String
   Dim oUser As CML.User
   Dim BorrowerNo As Long
   
   On Error GoTo ErrHandler
   
   ParseString LDAPString, varValues
   
   Set oUser = MTS.CreateInstance("CML.User")
   BorrowerNo = oUser.GetInfoFromTable(varValues(4)) 'varvalues(4) = alias
   
   If BorrowerNo = 0 Then
      BorrowerNo = oUser.UpdateInfoFromExchange(Server, varValues(1), varValues(2), varValues(4))
   End If
   
   BorrowerInfo = BorrowerNo
   Set oUser = Nothing
   Exit Function

ErrHandler:
   Err.Raise Err.Number, Err.Source, Err.Description
End Function

Private Sub ParseString(ByVal LDAPString As String, ByRef varValues() As String)
   Dim Count As Integer
   Dim FromPos, ToPos As Integer
   
     'To break LDAPString into Organisation, OrgUnit and Alias
     'LDAPString = "/o=org/ou=site/cn=recipients/cn=alias"
     Count = 1
     LDAPString = Mid(LCase(LDAPString), 2)
     FromPos = InStr(LDAPString, "=")
     
     Do While FromPos > 0
         ToPos = InStr(LDAPString, "/")
         ReDim Preserve varValues(Count)
         If ToPos > 0 Then
            varValues(Count) = Mid(LDAPString, FromPos + 1, ToPos - FromPos - 1)
         Else
            varValues(Count) = Mid(LDAPString, FromPos + 1)
            LDAPString = ""
         End If
         Count = Count + 1
         LDAPString = Mid(LDAPString, ToPos + 1)
         FromPos = InStr(LDAPString, "=")
     Loop
End Sub




