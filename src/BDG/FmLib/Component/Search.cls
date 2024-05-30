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

Private Const STR_QUOTE = """"
Private Const MAX_COLL = 5 ' Maximum number of document types

Public Enum SearchTypeOptions
    ftsContains = 1
    ftsFreeText = 2
    ftsInflection = 3
    ftsSubstring = 4
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
    ConnectionString = "DSN=FmLib"
    ConnectionTimeout = 30
End Sub

Public Sub CreateTable(ByVal TableName As String, Optional ByRef WhereClause As Variant, Optional ByVal SearchArea As SearchAreaOptions, Optional ByVal SearchType As SearchTypeOptions)
    Dim cmd As ADODB.Command
    Dim params As ADODB.Parameters
    Dim cn As ADODB.Connection
    Dim strWhere As String
    Dim strOR As String
    Dim item As Variant
    
    On Error GoTo ErrHandler
    
    '--- Build WHERE clause only if SUBSET of document types selected
    '--- Also, ignore it if there are NO document types selected
    If Not IsMissing(WhereClause) Then
      If UBound(WhereClause) < MAX_COLL - 1 Then
        strOR = "AND ("
        For Each item In WhereClause
          strWhere = strWhere & strOR & "t.coll='" & item & "'"
          strOR = " OR "
        Next
        strWhere = strWhere & ")"
      End If
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
    
        ' BUG : SearchType is ignored
    
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
            
            ' Valid word found
            Case Else
                Dim x
                If Not bTerm Then strncat = strncat & "and "
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
   
