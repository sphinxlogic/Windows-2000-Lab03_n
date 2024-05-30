VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "TitleMatch"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Private m_items As Collection

Private Sub Class_Initialize()
   ' Create internal collection object
   Set m_items = New Collection
End Sub
    
Private Sub Class_Terminate()
   ' Release memory
   Set m_items = Nothing
End Sub

Friend Sub LoadCollection(ByRef TitleKeywords As String, ByRef AuthorKeywords As String, ByRef MediaType As Variant, ByRef Logon As String, ByRef ServerName As String)
   Dim RDS As RDS.DataSpace
   Dim Search As Object
   Dim rs As ADODB.Recordset
   Dim Item As FoundTitle
   Dim MediaTypes(1) As String
   
   MediaTypes(1) = MediaType

   On Error GoTo ErrHandler
   
   Set RDS = CreateObject("RDS.DataSpace")
   RDS.InternetTimeout = 30
   Set Search = RDS.CreateObject("CML.Search", "http://" & ServerName)
   Set rs = Search.AdvancedSearch(TitleKeywords, AuthorKeywords, MediaTypes, Logon)
   
   Do Until rs.EOF
   
      ' AdvancedSearch will find reference materials, but we
      ' don't accept reviews for that type of item.  Ignore...
      
      If LCase(rs("coll")) <> "ref" Then
         Set Item = New FoundTitle
         
         ' Set item properties from current record
         Item.BibNo = rs("bib#")
         Item.Title = rs("title")
         Item.Authors = rs("authors")
         Item.MediaType = rs("coll")
         Item.Published = rs("pubdate")
         Item.ObjectID = rs("objectid")
         
         If Not IsNull(rs("isapproved")) Then
            If CInt(rs("isapproved")) = 1 Then
               Item.ReviewStatus = statusApproved
            Else
               Item.ReviewStatus = statusInProcess
            End If
         End If
         
         ' Add newly created item to the collection
         m_items.Add Item, CStr(Item.BibNo)
      End If
      
      rs.MoveNext
   Loop
   
   rs.Close
   Set rs = Nothing
   Set Search = Nothing
   Set RDS = Nothing
   Exit Sub
   
ErrHandler:
   MsgBox "Error " & Hex(Err.Number) & ": " & Err.Description, _
          vbCritical, Err.Source
End Sub

' Returns number of objects in collection
Public Property Get Count() As Long
   Count = m_items.Count
End Property

' Index can be either numeric (ordinal) or string value (key)
Public Property Get Item(ByVal Index As Variant) As FoundTitle
Attribute Item.VB_UserMemId = 0
   Set Item = m_items.Item(Index)
End Property

' NewEnum returns the collection's IEnumVARIANT interface
Public Property Get NewEnum() As IUnknown
Attribute NewEnum.VB_UserMemId = -4
Attribute NewEnum.VB_MemberFlags = "40"
   Set NewEnum = m_items.[_NewEnum]
End Property

