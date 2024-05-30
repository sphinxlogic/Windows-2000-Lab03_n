VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 2  'RequiresTransaction
END
Attribute VB_Name = "Admin"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

'--- Error messages and codes
Const N_MISSINGINFO = &H800C0100
Const S_MISSINGINFO = "Invalid BibNo or BorrowerNo specified."

Const N_INVALIDBARCODE = &H800C0101
Const S_INVALIDBARCODE = "Invalid Barcode specified."

Const N_INVALIDDUEDATE = &H800C0102
Const S_INVALIDDUEDATE = "DueDate doesn't allow for much reading time..."

Const N_INVALIDITEMCODE = &H800C0103
Const S_INVALIDITEMCODE = "Invalid Item Number specified."

Const N_NOTABLEQUEUE = &H800C0104
Const S_NOTABLEQUEUE = "Failed to create TableQueue object."

Public ConnectionString As String   ' OLE DB Connection String
Public ConnectionTimeout As Long    ' Length of connection attempt

'--- Create MTS Object context
Private MTS As New MTSEnvironment

Private Sub Class_Initialize()
  ConnectionString = "DSN=FmLib"
  ConnectionTimeout = 30
End Sub

'--- Assign materials to new request in queue.
'--- Returns borrower# to whom the materials are checked out
Public Function CheckOut(ByVal Barcode As String, ByVal DueDate As Date) As Long
    Dim cn As ADODB.Connection
    Dim cmd As ADODB.Command
    Dim params As ADODB.Parameters
    
    On Error GoTo ErrHandler
    
    '--- Check that we have valid parameters
    If IsEmpty(Barcode) Or Barcode = "" Then
        Err.Raise N_INVALIDBARCODE, "Admin.CheckOut", S_INVALIDBARCODE
    End If
    If DueDate <= DateAdd("d", 1, Date) Then
        Err.Raise N_INVALIDDUEDATE, "Admin.CheckOut", S_INVALIDDUEDATE
    End If
       
    Set cn = MTS.CreateInstance("ADODB.Connection")
    cn.ConnectionString = ConnectionString
    cn.ConnectionTimeout = ConnectionTimeout
    cn.Open
    
    Set cmd = MTS.CreateInstance("ADODB.Command")
    With cmd
        .ActiveConnection = cn
        .CommandTimeout = 90
        
        .CommandText = "fm_admin_checkout"
        .CommandType = adCmdStoredProc
        
        'Pass Arguments to stored procedure
        Set params = .Parameters
        params.Append .CreateParameter("retval", adInteger, adParamReturnValue)
        params.Append .CreateParameter("@barcode", adVarChar, adParamInput, 15, Barcode)
        params.Append .CreateParameter("@dueDate", adChar, adParamInput, 10, CStr(DueDate))
        
        'Execute the command
        .Execute
    End With
    
    'Return value (borrower#)
    CheckOut = cmd(0)
    
    Set params = Nothing
    Set cmd = Nothing
    
    cn.Close
    Set cn = Nothing
    
    Exit Function

ErrHandler:
    Err.Raise Err.Number, Err.Source, Err.Description
End Function

'--- Check in material by barcode
'--- Returns the bib# if the item was successfully checked in, otherwise 0
Public Function CheckIn(ByVal Barcode As String, ByVal Location As String) As Long
   Dim cn As ADODB.Connection
   Dim cmd As ADODB.Command
   Dim params As ADODB.Parameters
   
   On Error GoTo ErrHandler
   
   '--- Check that we have valid parameters
   If IsEmpty(Barcode) Or Barcode = "" Then
       Err.Raise N_INVALIDBARCODE, "Admin.Checkin", S_INVALIDBARCODE
   End If
   
   Set cn = MTS.CreateInstance("ADODB.Connection")
   cn.ConnectionString = ConnectionString
   cn.ConnectionTimeout = ConnectionTimeout
   cn.Open
   
   Set cmd = MTS.CreateInstance("ADODB.Command")
   With cmd
      .ActiveConnection = cn
      .CommandTimeout = 90
      
      .CommandText = "fm_admin_checkin"
      .CommandType = adCmdStoredProc
      
      'Pass Arguments to stored procedure
      Set params = .Parameters
      params.Append .CreateParameter("retval", adInteger, adParamReturnValue, 8)
      params.Append .CreateParameter("@barcode", adVarChar, adParamInput, 15, Barcode)
      params.Append .CreateParameter("@location", adVarChar, adParamInput, 64, Location)
      
      'Execute the command
      .Execute
   End With
   
   CheckIn = cmd(0)
   
   Set params = Nothing
   Set cmd = Nothing
   cn.Close
   Set cn = Nothing
   Exit Function

ErrHandler:
   Err.Raise Err.Number, Err.Source, Err.Description
End Function

'--- Return recordset of current requests
Public Function Requests(Optional ByVal BibNo As Long) As ADODB.Recordset
   Dim rs As ADODB.Recordset
   Dim strSQL As String
   
   On Error GoTo ErrHandler
   
   strSQL = "SELECT t.bib# as BibNo,t.Title,t.Call,t.Coll," & _
            " r.request#,r.borrower# As BorrowerNo,r.Pickup_Location As Location,r.Comment" & _
            " FROM Title AS t JOIN Request AS r ON t.bib#=r.bib# WHERE r.req_queue_ord=1"
   If BibNo > 0 Then strSQL = strSQL & " AND t.bib#=" & BibNo
            strSQL = strSQL & " ORDER BY t.Call"
   
   Set rs = MTS.CreateInstance("ADODB.Recordset")
   rs.Open strSQL, ConnectionString
   
   'Return value
   Set Requests = rs
   Exit Function
   
ErrHandler:
   Err.Raise Err.Number, Err.Source, Err.Description
End Function

'--- Return recordset of library items that are available for checkout
Public Function Available(ByVal BibNo As Long) As ADODB.Recordset
   Dim rs As ADODB.Recordset
   Dim strSQL As String
   
   On Error GoTo ErrHandler
   
   '--- Check that we have valid parameters
   If BibNo = 0 Then Err.Raise N_MISSINGINFO, "Admin.Available", S_MISSINGINFO

   strSQL = "SELECT item#,barcode,location FROM Item WHERE bib#=" & BibNo & _
            " AND staff_only=0 AND item_status IN" & _
            " (SELECT item_status FROM item_status WHERE available_for_request=1)"
   
   Set rs = MTS.CreateInstance("ADODB.Recordset")
   rs.Open strSQL, ConnectionString
   
   'Return value
   Set Available = rs
   Exit Function
   
ErrHandler:
   Err.Raise Err.Number, Err.Source, Err.Description
End Function

'--- Lookup barcode and return bib#
Public Function LookupBarcode(ByVal Barcode As String) As ADODB.Recordset
   Dim rs As ADODB.Recordset
   Dim strSQL As String
   
   '--- Check that we have valid parameters
   If IsEmpty(Barcode) Or Barcode = "" Then
      Err.Raise N_INVALIDBARCODE, "Admin.CheckOut", S_INVALIDBARCODE
   End If

   On Error GoTo ErrHandler
   
   strSQL = "SELECT t.bib# as BibNo,t.Title,t.Call,t.Coll" & _
            " FROM Title AS t JOIN Item AS i ON t.bib#=i.bib#" & _
            " WHERE i.barcode='" & Barcode & "'"
   
   Set rs = MTS.CreateInstance("ADODB.Recordset")
   rs.Open strSQL, ConnectionString
   
   Set LookupBarcode = rs
   Exit Function

ErrHandler:
   Err.Raise Err.Number, Err.Source, Err.Description
End Function

'--- Renew library materials
Public Function Renew(ByVal Barcode As String, ByVal DueDate As Date) As Long
   Dim cn As ADODB.Connection
   Dim cmd As ADODB.Command
   Dim params As ADODB.Parameters
   
   On Error GoTo ErrHandler
    
   '--- Check that we have valid parameters
   If IsEmpty(Barcode) Or Barcode = "" Then
      Err.Raise N_INVALIDBARCODE, "Admin.Renew", S_INVALIDBARCODE
   End If
   If DueDate <= DateAdd("d", 1, Date) Then
      Err.Raise N_INVALIDDUEDATE, "Admin.Renew", S_INVALIDDUEDATE
   End If
   
   Set cn = MTS.CreateInstance("ADODB.Connection")
   cn.ConnectionString = ConnectionString
   cn.ConnectionTimeout = ConnectionTimeout
   cn.Open
   
   Set cmd = MTS.CreateInstance("ADODB.Command")
   With cmd
      .ActiveConnection = cn
      .CommandTimeout = 90
      
      .CommandText = "fm_admin_renew"
      .CommandType = adCmdStoredProc
      
      'Pass Arguments to stored procedure
      Set params = .Parameters
      params.Append .CreateParameter("retval", adInteger, adParamReturnValue, 8)
      params.Append .CreateParameter("@barcode", adVarChar, adParamInput, 15, Barcode)
      params.Append .CreateParameter("@dueDate", adChar, adParamInput, 10, CStr(DueDate))
      
      'Execute the command
      .Execute
   End With
   
   'Return value
   Renew = cmd(0)
   
   Set params = Nothing
   Set cmd = Nothing
   Exit Function
   
ErrHandler:
   Err.Raise Err.Number, Err.Source, Err.Description
End Function
   
'--- Returns queue length for this title.
Public Function QueueLength(ByVal BibNo As Long) As Long
   Dim tq As New TableQueue
   
   If BibNo <= 0 Then Err.Raise N_MISSINGINFO, "Admin.QueueLength", S_MISSINGINFO
   If tq Is Nothing Then Err.Raise N_NOTABLEQUEUE, "Admin.QueueLength", S_NOTABLEQUEUE
   
   On Error GoTo ErrHandler
   
   ' Find position, and optionally, length of queue
   tq.ConnectionString = ConnectionString
   QueueLength = tq.Length(BibNo)
   Exit Function
   
ErrHandler:
   Err.Raise Err.Number, Err.Source, Err.Description
End Function

'--- Update title information
Public Function UpdateTitle(ByVal BibNo As Long, ByVal Title As String, ByVal CallNo As String, ByVal Coll As String, ByVal ISBN As String, _
                            ByVal Publisher As String, ByVal PubDate As Date, ByVal Description As String, ByVal Notes As String) As Long
   Dim cn As ADODB.Connection
   Dim cmd As ADODB.Command
   Dim params As ADODB.Parameters
   
   On Error GoTo ErrHandler
    
   Set cn = MTS.CreateInstance("ADODB.Connection")
   cn.ConnectionString = ConnectionString
   cn.ConnectionTimeout = ConnectionTimeout
   cn.Open
   
   Set cmd = MTS.CreateInstance("ADODB.Command")
   With cmd
      .ActiveConnection = cn
      .CommandTimeout = 90
      
      .CommandText = "fm_admin_update_title"
      .CommandType = adCmdStoredProc
      
      'Pass Arguments to stored procedure
      Set params = .Parameters
      params.Append .CreateParameter("retval", adInteger, adParamReturnValue, 8)
      params.Append .CreateParameter("@bibNo", adInteger, adParamInput, , BibNo)
      params.Append .CreateParameter("@title", adVarChar, adParamInput, 255, Title)
      params.Append .CreateParameter("@call", adVarChar, adParamInput, 50, CallNo)
      params.Append .CreateParameter("@coll", adVarChar, adParamInput, 24, Coll)
      params.Append .CreateParameter("@ISBN", adVarChar, adParamInput, 64, ISBN)
      params.Append .CreateParameter("@publisher", adVarChar, adParamInput, 255, Publisher)
      params.Append .CreateParameter("@pubdate", adChar, adParamInput, 10, CStr(PubDate))
      params.Append .CreateParameter("@description", adVarChar, adParamInput, 255, Description)
      params.Append .CreateParameter("@notes", adBSTR, adParamInput, , Notes)
      
      'Execute the command
      .Execute
   End With
   
   'Return value
   UpdateTitle = cmd(0)
   
   Set params = Nothing
   Set cmd = Nothing
   Exit Function
   
ErrHandler:
   Err.Raise Err.Number, Err.Source, Err.Description
End Function

'--- Update item information
Public Function UpdateItem(ByVal ItemNo As Long, ByVal Barcode As String, ByVal BibNo As Long, ByVal Location As String, ByVal Source As String, _
                            ByVal Price As Double, ByVal Notes As String, ByVal StaffOnly As Boolean, ByVal ItemStatus As String) As Long
   Dim cn As ADODB.Connection
   Dim cmd As ADODB.Command
   Dim params As ADODB.Parameters
   
   '--- Check that we have valid parameters
   If IsEmpty(Barcode) Or Barcode = "" Then
       Err.Raise N_INVALIDBARCODE, "Admin.UpdateItem", S_INVALIDBARCODE
   End If
   If BibNo = 0 Then Err.Raise N_MISSINGINFO, "Admin.UpdateItem", S_MISSINGINFO

   On Error GoTo ErrHandler
    
   Set cn = MTS.CreateInstance("ADODB.Connection")
   cn.ConnectionString = ConnectionString
   cn.ConnectionTimeout = ConnectionTimeout
   cn.Open
   
   Set cmd = MTS.CreateInstance("ADODB.Command")
   With cmd
      .ActiveConnection = cn
      .CommandTimeout = 90
      
      .CommandText = "fm_admin_update_item"
      .CommandType = adCmdStoredProc
      
      'Pass Arguments to stored procedure
      Set params = .Parameters
      params.Append .CreateParameter("retval", adInteger, adParamReturnValue, 8)
      params.Append .CreateParameter("@itemNo", adInteger, adParamInput, , ItemNo)
      params.Append .CreateParameter("@barcode", adVarChar, adParamInput, 16, Barcode)
      params.Append .CreateParameter("@bibNo", adInteger, adParamInput, , BibNo)
      params.Append .CreateParameter("@location", adVarChar, adParamInput, 64, Location)
      params.Append .CreateParameter("@source", adVarChar, adParamInput, 64, Source)
      params.Append .CreateParameter("@price", adCurrency, adParamInput, , Price)
      params.Append .CreateParameter("@notes", adVarChar, adParamInput, 255, Notes)
      params.Append .CreateParameter("@staff_only", adTinyInt, adParamInput, , IIf(StaffOnly, 1, 0))
      params.Append .CreateParameter("@item_status", adVarChar, adParamInput, 7, ItemStatus)
      
      'Execute the command
      .Execute
   End With
   
   'Return value
   UpdateItem = cmd(0)
   
   Set params = Nothing
   Set cmd = Nothing
   Exit Function
   
ErrHandler:
   Err.Raise Err.Number, Err.Source, Err.Description
End Function
