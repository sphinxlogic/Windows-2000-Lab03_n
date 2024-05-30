VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 1  'NoTransaction
END
Attribute VB_Name = "Search"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit
Option Compare Text

'--- Error messages and codes
Private Const NERR_INVALIDAREA = &H800C0101
Private Const SERR_INVALIDAREA = "An invalid SearchAreaOption was passed."

Private Const NERR_NOCRITERIA = &H800C0102
Private Const SERR_NOCRITERIA = "You must specify keywords for Title and/or Author."

Private Const STR_QUOTE = """"
Private Const MAX_COLL = 5 ' Maximum number of document types

Public Enum SearchTypeOptions
    ftsContains = 1
    ftsFreeText = 2
    ftsInflection = 3
    ftsSubstring = 4
    ftsOrIsDefault = 5
End Enum

Public Enum SearchAreaOptions
    ftsTitle = 1
    ftsAuthor = 2
    ftsSubject = 3
End Enum

'--- PUBLIC properties (no restrictions)
Public SearchType As SearchTypeOptions
Public SearchArea As SearchAreaOptions
Public ConnectionString As String
Public ConnectionTimeout As Long

'--- PRIVATE data members
Private m_aWords() As String

'--- Create MTS Object context
Private MTS As New MTSEnvironment

'--- Initialize the class defaults
Private Sub Class_Initialize()
   SearchType = ftsContains
   SearchArea = ftsTitle
   ConnectionString = "DSN=FmLib;UID=sa;PWD=;DATABASE=FmLib"
   ConnectionTimeout = 30
End Sub

Public Sub CreateTable(ByVal TableName As String, Optional ByRef WhereClause As Variant, Optional ByVal SearchArea As SearchAreaOptions, Optional ByVal SearchType As SearchTypeOptions)
   Dim cmd As ADODB.Command
   Dim params As ADODB.Parameters
   Dim cn As ADODB.Connection
   Dim strWhere As String
   
   On Error GoTo ErrHandler
   
   ' Set optional search type
   If SearchType <> 0 Then
      Me.SearchType = SearchType
   End If
   
   ' Create optional WHERE clause
   If Not IsMissing(WhereClause) Then
      strWhere = TypesFromArray(WhereClause)
      If strWhere <> "" Then strWhere = " AND " & strWhere
   End If
   
   Set cn = MTS.CreateInstance("ADODB.Connection")
   cn.ConnectionString = ConnectionString
   cn.ConnectionTimeout = ConnectionTimeout
   cn.Open
   
   Set cmd = MTS.CreateInstance("ADODB.Command")
   With cmd
      .ActiveConnection = cn
      .CommandTimeout = 90
      .CommandType = adCmdStoredProc
      
      Select Case SearchArea
      Case ftsTitle
         .CommandText = "fm_fts_optTitle_contains"
      Case ftsAuthor
         .CommandText = "fm_fts_optAuthor_contains"
      Case ftsSubject
        .CommandText = "fm_fts_optSubject_contains"
      Case Else
          Err.Raise NERR_INVALIDAREA, "Search.CreateTable", SERR_INVALIDAREA
      End Select
  
      ' Pass arguments to stored procedure
      Set params = .Parameters
      params.Append .CreateParameter("@search", adVarChar, adParamInput, 255, SearchString)
      params.Append .CreateParameter("@tblname", adVarChar, adParamInput, 64, TableName)
      params.Append .CreateParameter("@where", adVarChar, adParamInput, 255, strWhere)
      ' Execute the command
      .Execute
   End With
   Exit Sub
   
ErrHandler:
   Err.Raise Err.Number, Err.Source, Err.Description
End Sub

Public Function AdvancedSearch(ByVal TitleKeywords As String, ByVal AuthorKeywords As String, _
                                          ByVal MediaTypes As Variant, Optional ByVal Logon As String, _
                                          Optional ByVal ConnectionString As String) As ADODB.Recordset
   Dim cn As ADODB.Connection
   Dim rs As ADODB.Recordset
   Dim rsFlat As ADODB.Recordset
   Dim fldAuthors As ADODB.Field
   Dim fldCritique As ADODB.Field
   Dim df As RDSServer.DataFactory
   ' ColumnDefs contains 7 columns, but is 0-based
   Dim vColumnDefs(6) As Variant
   Dim vColumn1(3) As Variant
   Dim vColumn2(3) As Variant
   Dim vColumn3(3) As Variant
   Dim vColumn4(3) As Variant
   Dim vColumn5(3) As Variant
   Dim vColumn6(3) As Variant
   Dim vColumn7(3) As Variant
   Dim oUser As CML.User
   Dim nBorrower As Integer
   Dim strSQL As String
   Dim strOR As String
   Dim strWhere As String
   
   ' Must specify at least one keyword criteria
   If TitleKeywords = "" And AuthorKeywords = "" Then
      Err.Raise NERR_NOCRITERIA, "Search.AdvancedSearch", SERR_NOCRITERIA
   End If
   
   ' Set OLE DB connection string from optional param
   If ConnectionString <> "" Then
      Me.ConnectionString = ConnectionString
   End If
   
   SearchType = ftsOrIsDefault
   
   On Error GoTo ErrHandler
   
   strSQL = "SHAPE {SELECT DISTINCT t.bib#,t.title,CONVERT(char(4),t.pubdate,112) AS pubdate,t.coll FROM title AS t WHERE "
   
   ' Restrict by media type
   strWhere = TypesFromArray(MediaTypes)
   If strWhere <> "" Then strSQL = strSQL & strWhere & " AND ("
   
   ' Select based on TITLE keywords
   If TitleKeywords <> "" Then
      SearchString = TitleKeywords
      strSQL = strSQL & "CONTAINS(t.*,'" & SearchString & "')"
      strOR = " OR "
   End If
   
   ' Select based on AUTHOR keywords
   If AuthorKeywords <> "" Then
      SearchString = AuthorKeywords
      strSQL = strSQL & strOR & "t.bib# IN (SELECT DISTINCT ta.bib# FROM titleauth AS ta JOIN author AS a ON ta.auth#=a.auth# AND CONTAINS(a.*,'" & SearchString & "')) "
   End If
   
   ' Sort by title
   If strWhere <> "" Then strSQL = strSQL & ") "
   strSQL = strSQL & " ORDER BY t.title} "
   
   ' Get borrower# if logon is specified
   If Logon <> "" Then
      Set oUser = New CML.User
      nBorrower = oUser.GetInfoFromTable(Logon)
      Set oUser = Nothing
   End If
   
   ' Include borrower's critiques
   strSQL = strSQL & " APPEND ({SELECT objectid,isapproved FROM critique WHERE borrower#=" & nBorrower & " AND bib#=?} AS critique RELATE 'bib#' TO PARAMETER 0)"
   
   ' Fill in datashape for author lists
   strSQL = strSQL & ", ({SELECT a.fname,a.lname FROM author AS a JOIN titleauth AS ta ON ta.auth#=a.auth# WHERE ta.bib#=?} AS authors RELATE 'bib#' TO PARAMETER 0)"
   
   ' Open the connection
   Set cn = MTS.CreateInstance("ADODB.Connection")
   cn.Provider = "MSDataShape"
   cn.ConnectionTimeout = ConnectionTimeout
   cn.Open "Data Provider=MSDASQL;" & Me.ConnectionString
   
   Set rs = MTS.CreateInstance("ADODB.Recordset")
   rs.StayInSync = True
   rs.Open strSQL, cn, adOpenForwardOnly, adLockReadOnly
   
   ' Create the flat recordset for returning through RDS
   vColumn1(0) = "bib#"
   vColumn1(1) = CInt(adInteger)
   vColumn1(2) = CInt(-1) ' Fixed length
   vColumn1(3) = False ' NOT NULL
   vColumn2(0) = "title"
   vColumn2(1) = CInt(adVarChar)
   vColumn2(2) = CInt(255)
   vColumn2(3) = False
   vColumn3(0) = "pubdate"
   vColumn3(1) = CInt(adChar)
   vColumn3(2) = CInt(4)
   vColumn3(3) = False
   vColumn4(0) = "coll"
   vColumn4(1) = CInt(adChar)
   vColumn4(2) = CInt(5)
   vColumn4(3) = False
   vColumn5(0) = "authors"
   vColumn5(1) = CInt(adVarChar)
   vColumn5(2) = CInt(255)
   vColumn5(3) = True ' NULL
   vColumn6(0) = "objectid"
   vColumn6(1) = CInt(adChar)
   vColumn6(2) = CInt(255)
   vColumn6(3) = True
   vColumn7(0) = "isapproved"
   vColumn7(1) = CInt(adTinyInt)
   vColumn7(2) = CInt(-1)
   vColumn7(3) = True
   vColumnDefs(0) = vColumn1
   vColumnDefs(1) = vColumn2
   vColumnDefs(2) = vColumn3
   vColumnDefs(3) = vColumn4
   vColumnDefs(4) = vColumn5
   vColumnDefs(5) = vColumn6
   vColumnDefs(6) = vColumn7
   
   Set df = MTS.CreateInstance("RDSServer.DataFactory")
   Set rsFlat = df.CreateRecordSet(vColumnDefs)
   
    ' Copy all rows to flat recordset
    Set fldAuthors = rs("authors")
    Set fldCritique = rs("critique")
    Do Until rs.EOF
       rsFlat.AddNew
       rsFlat("bib#") = rs("bib#")
       rsFlat("title") = rs("title")
       rsFlat("pubdate") = rs("pubdate")
       rsFlat("coll") = rs("coll")
       rsFlat("authors") = AuthorsToString(fldAuthors.Value)
       
       If Not fldCritique.Value.EOF Then
          rsFlat("objectid") = fldCritique.Value("objectid")
          rsFlat("isapproved") = fldCritique.Value("isapproved")
       Else
          rsFlat("objectid") = vbNullString
          rsFlat("isapproved") = Null
       End If
       
       rsFlat.Update
       rs.MoveNext
    Loop
   
   Set rs = Nothing
   Set cn = Nothing
   
   Set AdvancedSearch = rsFlat
   Exit Function
    
ErrHandler:
    Err.Raise Err.Number, Err.Source, Err.Description
End Function

Private Function AuthorsToString(ByRef rs As ADODB.Recordset) As String
    Dim sAuthors As String
    Dim sSep As String
    
    Do Until rs.EOF
        sAuthors = sAuthors & sSep & rs("fname")
        If rs("lname") <> "" Then
            sAuthors = sAuthors & " " & rs("lname")
        End If
        sSep = "; "
        rs.MoveNext
    Loop
    
    AuthorsToString = sAuthors
End Function

Public Property Let SearchString(ByVal RHS As String)
  ' Replace special case "NEAR()" with tilde
  RHS = Replace(LCase(Trim(RHS)), "near() ", "~ ")
  ' Split the string into words (tokens)
  m_aWords = Tokenize(RHS, " ")
End Property

Public Property Get SearchString() As String
    Dim count As Integer
    Dim strncat As String
    Dim bTerm As Boolean
    Dim strAnd As String
    
    If SearchType = ftsOrIsDefault Then
       strAnd = "or "
    Else
       strAnd = "and "
    End If
    
    Select Case SearchType
    ' Combine the word list into a single phrase
    Case ftsFreeText
        strncat = STR_QUOTE
        For count = 1 To UBound(m_aWords)
            ' Remove double quotes from all tokens
            strncat = strncat & Replace(m_aWords(count), STR_QUOTE, "")
        Next count
        strncat = strncat & STR_QUOTE
        
    ' Combine the words as a boolean search
    Case Else
        bTerm = True ' First pass, don't add terms
        For count = 1 To UBound(m_aWords)
            Select Case m_aWords(count)
            ' Append these, but treat them as special terms
            Case "~ ", "or ", "and "
                If Not bTerm Then
                    bTerm = True
                    strncat = strncat & m_aWords(count)
                End If
            
            ' Handle NEAR as a term, but not after another term
            Case "near "
                If Not bTerm Then
                    bTerm = True
                    strncat = strncat & "~ "
                End If
            
            ' Non-term word found
            Case Else
                Dim x
                If Not bTerm Then strncat = strncat & strAnd
                bTerm = False
                x = InStr(m_aWords(count), "*")
                If x > 0 Then
                    ' Wrap "word*" form in double quotes
                    strncat = strncat & """" & Left(m_aWords(count), x) & """ "
                ElseIf SearchType <> ftsSubstring Or _
                       InStr(m_aWords(count), STR_QUOTE) > 0 Then
                    ' Just add this word as-is
                    strncat = strncat & m_aWords(count)
                Else
                    ' Create "word*" form if using sub-string search option
                    strncat = strncat & """" & m_aWords(count) & "*"" "
                End If
            End Select
        Next
    End Select
    
    If SearchType = ftsInflection And _
       UBound(m_aWords) = 1 And _
       InStr(strncat, "*") = 0 Then
       strncat = "FORMSOF (INFLECTIONAL,""" & strncat & """)"
    End If
     
    SearchString = RTrim(strncat)
End Property

'===================================================================
' TOKEN PARSING FUNCTIONS
'===================================================================

' Returns the current position in the string
' NOTE: This function ignores delimiters inside of quotes and adds an extra space to tokens
Private Function GetToken(ByRef strText As String, ByRef strDelim As String, ByRef strToken As String) As String
   Dim x As Integer, c As String, bInQ As Boolean

   bInQ = False
   strToken = ""
   For x = 1 To Len(strText)
      c = Mid(strText, x, 1)
      '--- skip delimiters inside quoted strings
      If c = STR_QUOTE Then bInQ = Not bInQ
      If Not bInQ And c = strDelim Then
         If strToken <> "" Then
           strToken = strToken & " "
           GetToken = x + 1  ' skip delimiter
           Exit Function
         End If
      Else
         strToken = strToken & c
      End If
   Next
   
   ' Append a space, just like all the other tokens
   If strToken <> "" Then strToken = strToken & " "
   
   ' Last token
   GetToken = 0
End Function

' Returns an array of values split at delimiters
Private Function Tokenize(ByRef strText As String, ByVal strDelim As String) As String()
   Dim aTokens() As String, cTokens As Integer
   Dim x As Integer, strToken As String

   cTokens = 0
   
   '--- Parse string into array of tokens
   x = GetToken(strText, strDelim, strToken)
   Do While x > 0
      cTokens = cTokens + 1
      ReDim Preserve aTokens(cTokens)
      aTokens(cTokens) = strToken
      '--- Chop string and iterate
      strText = Mid(strText, x)
      x = GetToken(strText, strDelim, strToken)
   Loop
   
   '--- Last token in string
   cTokens = cTokens + 1
   ReDim Preserve aTokens(cTokens)
   aTokens(cTokens) = strToken
   
   '--- Return array of tokens
   Tokenize = aTokens
End Function
   
'--- Build WHERE clause only if SUBSET of document types selected
'--- Also, ignore it if there are NO document types selected
Private Function TypesFromArray(ByRef WhereClause As Variant) As String
   Dim strOR As String
   Dim item As Variant
   Dim count As Integer
   
   On Error GoTo ErrHandler
   
   TypesFromArray = ""
   count = 0
   If VarType(WhereClause) = vbArray + vbString Then
      If UBound(WhereClause) > 0 And UBound(WhereClause) < MAX_COLL - 1 Then
        strOR = "("
        For Each item In WhereClause
          If item <> "" Then
            TypesFromArray = TypesFromArray & strOR & "t.coll='" & CStr(item) & "'"
            count = count + 1
            strOR = " OR "
          End If
        Next
        If count > 0 Then TypesFromArray = TypesFromArray & ")"
      End If
   End If
   Exit Function
   
ErrHandler:
   Err.Raise Err.Number, "Search.TypesFromArray", "Failed to parse WHERE clause from array: " & Err.Description
End Function
