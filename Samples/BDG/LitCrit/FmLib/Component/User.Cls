VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 3  'UsesTransaction
END
Attribute VB_Name = "User"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

'--- Error messages and codes
Const N_MISSINGALIAS = &H800C0001
Const S_MISSINGALIAS = "Must specify a user alias (logon name)."

Const N_MISSINGBNO = &H800C0002
Const S_MISSINGBNO = "Missing or invalid borrower number."

Const N_INVALIDADMIN = &H800C0003
Const S_INVALIDADMIN = "AdminAccount parameter must use valid ADSI (cn=account,dc=domain) or NTLM account format."

Const N_NOTABLEQUEUE = &H800C0004
Const S_NOTABLEQUEUE = "Failed to create TableQueue object."

Const N_MISSINGPROVIDER = &H800C0005
Const S_MISSINGPROVIDER = "LDAP provider not installed, or unavailable."

'--- PUBLIC properties
Public ConnectionString As String        ' OLE DB Connection String
Attribute ConnectionString.VB_VarDescription = "The ODBC data source name (default ""DSN=FMLib"")."

'--- PRIVATE properties
Private m_bno As Long         ' Library borrower number
Private m_alias As String     ' User properties (from ADSI)
Private m_fname As String
Private m_lname As String
Private m_displayName As String
Private m_location As String
Private m_dept As String
Private m_title As String
Private m_phone As String
Private m_staff As Boolean

'--- Create MTS Object context
Private MTS As New MTSEnvironment

Private Sub Class_Initialize()
  ConnectionString = "DSN=FmLib"
End Sub

'--- Default property
Public Property Let Alias(ByVal RHS As String)
    m_alias = Trim(RHS)
End Property

Public Property Get Alias() As String
Attribute Alias.VB_Description = "User's logon."
Attribute Alias.VB_UserMemId = 0
    Alias = m_alias
End Property

'--- Read/only properties
Public Property Get FirstName() As String
Attribute FirstName.VB_Description = "User's given name (from Exchange)."
    FirstName = m_fname
End Property

Public Property Get LastName() As String
Attribute LastName.VB_Description = "User's surname (from Exchange)."
    LastName = m_lname
End Property

Public Property Get FullName() As String
    FullName = m_displayName
End Property

Public Property Get Location() As String
Attribute Location.VB_Description = "User's office location (from Exchange)."
    Location = m_location
End Property

Public Property Get Department() As String
Attribute Department.VB_Description = "User's department (from Exchange)."
    Department = m_dept
End Property

Public Property Get Title() As String
Attribute Title.VB_Description = "User's business title (from Exchange)."
    Title = m_title
End Property

Public Property Get TelephoneNumber() As String
Attribute TelephoneNumber.VB_Description = "User's office phone number (from Exchange)."
    TelephoneNumber = m_phone
End Property

Public Property Get BorrowerNo() As Long
Attribute BorrowerNo.VB_Description = "User's borrower ID."
    BorrowerNo = m_bno
End Property

Public Property Get Requests(Optional ByVal BorrowerNo As Long) As ADODB.Recordset
Attribute Requests.VB_Description = "Returns a list of items requested by this user."
    Dim bno As Long
    Dim strSQL As String
    Dim rs As ADODB.Recordset
    
    '--- Check optional values
    bno = IIf(BorrowerNo = 0, m_bno, BorrowerNo)
    If bno <= 0 Then Err.Raise N_MISSINGBNO, "User.Requests", S_MISSINGBNO
    
    On Error GoTo ErrHandler
    
    strSQL = "SELECT DISTINCT r.bib#,date_requested AS 'Date Requested'," & _
             "t.title FROM Request r LEFT JOIN Title t ON r.bib#=t.bib# " & _
             "WHERE r.borrower#=" & bno & " ORDER BY t.Title"
             
    Set rs = MTS.CreateInstance("ADODB.Recordset")
    rs.Open strSQL, ConnectionString
    
    Set Requests = rs
    Exit Property
    
ErrHandler:
    Err.Raise Err.Number, Err.Source, Err.Description
End Property

Public Property Get Checkouts(Optional ByVal BorrowerNo As Long) As ADODB.Recordset
Attribute Checkouts.VB_Description = "Returns a list of items currently checked out to this user."
    Dim bno As Long
    Dim strSQL As String
    Dim rs As ADODB.Recordset
    
    '--- Check optional values
    bno = IIf(BorrowerNo = 0, m_bno, BorrowerNo)
    If bno <= 0 Then Err.Raise N_MISSINGBNO, "User.Checkouts", S_MISSINGBNO
    
    On Error GoTo ErrHandler
    
    strSQL = "SELECT DISTINCT i.bib#,i.barcode,i.last_cko_date AS 'Checkout Date'," & _
            "i.due_date AS 'Due Date',t.title FROM Item i LEFT JOIN Title t ON " & _
            "i.bib#=t.bib# WHERE i.borrower#=" & bno & " ORDER BY i.due_date,t.Title"
    
    Set rs = MTS.CreateInstance("ADODB.Recordset")
    rs.Open strSQL, ConnectionString
    
    Set Checkouts = rs
    Exit Property
    
ErrHandler:
    Err.Raise Err.Number, Err.Source, Err.Description
End Property

'=== Functions and subroutines ===

'--- Load information from the borrower table (not all properties will be refreshed).
'--- If no user record exists, this function will return a BorrowerID of 0.
Public Function GetInfoFromTable(ByVal Logon As Variant) As Long
Attribute GetInfoFromTable.VB_Description = "Populate user properties from FmLib Borrower table."
    Dim rs As New ADODB.Recordset
    
    Select Case VarType(Logon)
    Case vbString:
      rs.Filter = "alias='" & Trim(CStr(Logon)) & "'"
    Case vbLong:
      rs.Filter = "borrower#=" & CInt(Logon)
    Case Else:
      Err.Raise N_MISSINGALIAS, "User.GetInfoFromTable", S_MISSINGALIAS
    End Select
    
    On Error GoTo ErrHandler
    
    rs.Open "Borrower", ConnectionString, adOpenForwardOnly, adLockReadOnly, adCmdTable
    If Not rs.EOF Then
        m_bno = rs("borrower#")
        m_alias = rs("alias")
        m_fname = rs("fname")
        m_lname = rs("lname")
        m_displayName = m_fname & " " & m_lname
        
        '--- Concatenate "" to convert null fields to string
        m_location = rs("location") & ""
        m_phone = rs("phone") & ""
        m_dept = rs("dept") & ""
        m_title = rs("title") & ""
        m_staff = IIf(rs("is_staff") = 0, False, True)
    Else
        '--- Reset properties
        m_bno = 0
        m_fname = ""
        m_lname = ""
        m_location = ""
        m_phone = ""
        m_dept = ""
        m_title = ""
        m_staff = False
    End If
    rs.Close
    
    '--- Return value
    GetInfoFromTable = m_bno
    
    Exit Function

ErrHandler:
    Err.Raise Err.Number, Err.Source, Err.Description
End Function

'--- Get information from Exchange and update our borrower table
Public Function UpdateInfoFromExchange(ByVal ExchangeServer As String, ByVal Organization As String, ByVal Site As String, Optional ByVal Logon As String, Optional ByVal AdminAccount As String, Optional ByVal AdminPassword As String) As Long
Attribute UpdateInfoFromExchange.VB_Description = "Copy data from Exchange directory to FmLib borrower table."
    Dim prov As ActiveDs.IADs
    Dim Admin As String
    Dim container As String
    Dim oUser As ActiveDs.IADs ' organizationalPersons doesn't map to IADsUser in ADSI 2.5
    Dim cmd As ADODB.Command
    Dim params As ADODB.Parameters
    
    On Error GoTo ErrHandler
    
    '--- Before going much further, we need to know if LDAP provider is installed
    For Each prov In GetObject("ADs:")
        If prov.Name = "LDAP:" Then GoTo Continue
    Next prov
    Err.Raise N_MISSINGPROVIDER, "User.UpdateInfoFromExchange", S_MISSINGPROVIDER
    
Continue:
    '--- Check that we have a user alias defined
    Logon = Trim(Logon)
    If Logon <> "" Then m_alias = Logon
    If m_alias = "" Then Err.Raise N_MISSINGALIAS, "User.UpdateInfoFromExchange", S_MISSINGALIAS
    
    '--- Get user object using ADSI
    ' container = "LDAP://" & ExchangeServer & "/o=" & Organization & "/ou=" & Site & "/cn=Recipients/cn=" & m_alias
    container = "LDAP://" & ExchangeServer & "/cn=" & m_alias & ",cn=Recipients,ou=" & Site & ",o=" & Organization
    
    '--- WARNING: Missing account properties cause automation errors
    On Error Resume Next
    
    '--- Access LDAP anonymously, or with authentication, depending on the presence of admin account
    AdminAccount = Trim(AdminAccount)
    If AdminAccount <> "" Then
        Dim x As Integer
        '--- Change from admin account from NTLM format, if required
        x = InStr(AdminAccount, "\")
        If x > 0 Then
            Admin = "cn=" & Mid(AdminAccount, x + 1) & ",dc=" & Left(AdminAccount, x - 1)
        Else
            Admin = AdminAccount
            '--- Verify format of admin account is "cn=account,dc=domain".
            If InStr(Admin, "cn=") <= InStr(Admin, "dc=") Then
                Err.Raise N_INVALIDADMIN, "User.UpdateInfoFromExchange", S_INVALIDADMIN
            End If
        End If
        
        Set prov = GetObject("LDAP:")
        Set oUser = prov.OpenDSObject(container, Admin, AdminPassword, 1) ' ADS_SECURE_AUTHENTICATION)
    Else
        Set oUser = GetObject(container)
    End If
    
    '--- Error indicates that either Exchange is unavailable, or
    '--- the username is unrecognized by Exchange. In either case we
    '--- can't continue, but let's try getting the requested information
    '--- from our records first.
    
    If Err.Number <> 0 Then
        UpdateInfoFromExchange = GetInfoFromTable(m_alias)
        Exit Function
    End If
    
    '--- Cache user properties
    oUser.GetInfoEx Array("givenName", "sn", "cn", "physicalDeliveryOfficeName", "department", "title", "telephoneNumber"), 0
    
    '--- Set user properties
    m_fname = oUser.Get("givenName")
    If Err.Number <> 0 Then m_fname = "": Err.Clear
    m_lname = oUser.Get("sn")
    If Err.Number <> 0 Then m_lname = "": Err.Clear
    m_displayName = oUser.Get("cn")
    If Err.Number <> 0 Then m_displayName = "": Err.Clear
    m_location = oUser.Get("physicalDeliveryOfficeName")
    If Err.Number <> 0 Then m_location = "": Err.Clear
    m_dept = oUser.Get("department")
    If Err.Number <> 0 Then m_dept = "": Err.Clear
    m_title = oUser.Get("title")
    If Err.Number <> 0 Then m_title = "": Err.Clear
    m_phone = oUser.Get("telephoneNumber")
    If Err.Number <> 0 Then m_phone = "": Err.Clear
    
    '--- Let our default handler take care of any other errors
    On Error GoTo ErrHandler
    
    '--- Update borrower record in the database
    Set cmd = MTS.CreateInstance("ADODB.Command")
    With cmd
        .ActiveConnection = ConnectionString
        .CommandTimeout = 90
        
        .CommandText = "fm_user_update"
        .CommandType = adCmdStoredProc
        
        Set params = .Parameters
        
        params.Append .CreateParameter("retval", adInteger, adParamReturnValue, 8)
        params.Append .CreateParameter("@alias", adVarChar, adParamInput, 50, m_alias)
        params.Append .CreateParameter("@fname", adVarChar, adParamInput, 64, m_fname)
        params.Append .CreateParameter("@lname", adVarChar, adParamInput, 64, m_lname)
        params.Append .CreateParameter("@location", adVarChar, adParamInput, 50, IIf(m_location = "", Null, m_location))
        params.Append .CreateParameter("@title", adVarChar, adParamInput, 50, IIf(m_title = "", Null, m_title))
        params.Append .CreateParameter("@phone", adVarChar, adParamInput, 50, IIf(m_phone = "", Null, m_phone))
        params.Append .CreateParameter("@dept", adVarChar, adParamInput, 50, IIf(m_dept = "", Null, m_dept))
        
        .Execute
    End With
    
    '--- Return value is assigned borrower number
    m_bno = cmd(0)
    UpdateInfoFromExchange = m_bno
    
    '--- Release  objects
    Set cmd = Nothing
    Set oUser = Nothing
    MTS.SetComplete
    Exit Function
    
ErrHandler:
    MTS.SetAbort
    Err.Raise Err.Number, Err.Source, Err.Description
End Function

'--- Enters a request for this user. Returns queue position.
Public Function MakeRequest(ByVal BibNo As Long, ByVal Location As String, ByVal comment As String, Optional ByVal BorrowerNo As Long) As Long
Attribute MakeRequest.VB_Description = "Enters a request for a title by Bib#."
    Dim bno As Long
    Dim tq As New TableQueue
    
    '--- Check optional values
    bno = IIf(BorrowerNo = 0, m_bno, BorrowerNo)
    If bno <= 0 Then Err.Raise N_MISSINGBNO, "User.MakeRequest", S_MISSINGBNO
    If tq Is Nothing Then Error.Raise N_NOTABLEQUEUE, "User.MakeRequest", S_NOTABLEQUEUE
    
    On Error GoTo ErrHandler
    
    ' Add user request
    tq.ConnectionString = ConnectionString
    MakeRequest = tq.Enqueue(BibNo, bno, Location, comment)
    MTS.SetComplete
    Exit Function
    
ErrHandler:
    MTS.SetAbort
    Err.Raise Err.Number, Err.Source, Err.Description
End Function

'--- Deletes the request from the queue for this user.
Public Sub CancelRequest(ByVal BibNo As Long, Optional ByVal BorrowerNo As Long)
Attribute CancelRequest.VB_Description = "Deletes request from queue."
    Dim bno As Long
    Dim tq As New TableQueue
    
    '--- Check optional values
    bno = IIf(BorrowerNo = 0, m_bno, BorrowerNo)
    If bno <= 0 Then Err.Raise N_MISSINGBNO, "User.CancelRequest", S_MISSINGBNO
    If tq Is Nothing Then Error.Raise N_NOTABLEQUEUE, "User.Position", S_NOTABLEQUEUE
    
    On Error GoTo ErrHandler
    
    ' Cancel user request
    tq.ConnectionString = ConnectionString
    tq.Cancel BibNo, bno
    MTS.SetComplete
    Exit Sub
    
ErrHandler:
    MTS.SetAbort
    Err.Raise Err.Number, Err.Source, Err.Description
End Sub

'--- Returns queue position for this user. Optionally returns length of queue.
Public Function Position(ByVal BibNo As Long, Optional ByRef Length As Variant, Optional ByVal BorrowerNo As Long) As Long
Attribute Position.VB_Description = "Position of user's request in queue."
    Dim bno As Long
    Dim tq As New TableQueue
    
    '--- Check optional values
    bno = IIf(BorrowerNo = 0, m_bno, BorrowerNo)
    If bno <= 0 Then Err.Raise N_MISSINGBNO, "User.Position", S_MISSINGBNO
    If tq Is Nothing Then Error.Raise N_NOTABLEQUEUE, "User.Position", S_NOTABLEQUEUE
    
    On Error GoTo ErrHandler
    
    ' Find position, and optionally, length of queue
    tq.ConnectionString = ConnectionString
    Position = tq.Position(BibNo, bno)
    If Not IsMissing(Length) Then Length = tq.Length(BibNo)
    Exit Function

ErrHandler:
    Err.Raise Err.Number, Err.Source, Err.Description
End Function

