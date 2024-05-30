VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "QueryFile"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
'*******************************************************************************
'* CLASS: QueryFile
'*    The QueryFile class represents a file containing a collection of MDX
'*    queries.
'*
'* PUBLIC PROPERTIES:
'*    Name        Name of the query file (R/O)
'*    File        Path and name of the query file (R/W)
'*    Queries     Array of queries in the query file (R/W)
'*    Dirty       Indicates if query file needs to be saved (R/W)
'*    QueryCount  Count of queries in the file (R/O)
'*
'* PUBLIC METHODS:
'*    OpenFile    Opens a query file
'*    Save        Saves the query file
'*    SaveAs      Saves the query file under a new name supplied by the user
'*    AddNew      Adds a new query to the file
'*    Remove      Removes the specified query from the file
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

'* API Declarations
Private Type OPENFILENAME
   lStructSize As Long
   hwndOwner As Long
   hInstance As Long
   lpstrFilter As String
   lpstrCustomFilter As String
   nMaxCustFilter As Long
   nFilterIndex As Long
   lpstrFile As String
   nMaxFile As Long
   lpstrFileTitle As String
   nMaxFileTitle As Long
   lpstrInitialDir As String
   lpstrTitle As String
   flags As Long
   nFileOffset As Integer
   nFileExtension As Integer
   lpstrDefExt As String
   lCustData As Long
   lpfnHook As Long
   lpTemplateName As String
End Type
Private Const OFN_FILEMUSTEXIST = &H1000
Private Const OFN_OVERWRITEPROMPT = &H2
Private Const OFN_HIDEREADONLY = &H4
Private Declare Function GetOpenFileName Lib "comdlg32.dll" Alias _
                     "GetOpenFileNameA" (pOpenfilename As OPENFILENAME) As Long
Private Declare Function GetSaveFileName Lib "comdlg32.dll" Alias _
                     "GetSaveFileNameA" (pOpenfilename As OPENFILENAME) As Long


'* Private constants
Private Const m_iArraySizeIncrement = 20
Private Const m_iErrSubscriptOutOfBounds = 9
Private Const m_sQueryFileExt = "MDX"
Private Const m_sFileFilter = _
      "MDX Query Files (*." & m_sQueryFileExt & ")" & vbNullChar & _
      "*." & m_sQueryFileExt & vbNullChar & _
      "All Files" & vbNullChar & _
      "*.*" & vbNullChar


'* Private data
Private m_sFile As String
Private m_sQueries() As String
Private m_fDirty As Boolean
Private m_iQueryCount As Long
Private m_fNewFile As Boolean



'******************
'*** PROPERTIES ***
'******************

'*******************************************************************************
'* PROPERTY:  Name
'*    Contains the name of the query file (R/O)
'*******************************************************************************
Public Property Get Name() As String
   Name = sGetFileName(m_sFile)
End Property

'*******************************************************************************
'* PROPERTY:  File
'*    Contains the path and name of the query file (R/W)
'*******************************************************************************
Public Property Get File() As String
   File = m_sFile
End Property

Public Property Let File(NewFile As String)
   If Not m_sFile = NewFile Then
      m_sFile = NewFile
      m_fDirty = True
   End If
End Property

'*******************************************************************************
'* PROPERTY:  Queries
'*    Contains the array of queries in the query file (R/W)
'*******************************************************************************
Public Property Get Queries(Index As Long) As String
   If Index > m_iQueryCount Then
      Err.Raise m_iErrSubscriptOutOfBounds
   End If
   
   Queries = m_sQueries(Index)
End Property

Public Property Let Queries(Index As Long, NewQuery As String)
   If Index > m_iQueryCount Then
      Err.Raise m_iErrSubscriptOutOfBounds
   End If
   
   If Not StrComp(m_sQueries(Index), NewQuery, vbBinaryCompare) = 0 Then
      m_sQueries(Index) = NewQuery
      m_fDirty = True
   End If
End Property

'*******************************************************************************
'* PROPERTY:  Dirty
'*    Contains the indicates if query file needs to be saved (R/W)
'*******************************************************************************
Public Property Get Dirty() As Boolean
   Dirty = m_fDirty
End Property

Public Property Let Dirty(NewDirty As Boolean)
   m_fDirty = NewDirty
End Property

'*******************************************************************************
'* PROPERTY:  QueryCount
'*    Contains the count of queries in the file (R/O)
'*******************************************************************************
Public Property Get QueryCount() As Long
   QueryCount = m_iQueryCount
End Property



'***************
'*** METHODS ***
'***************

'*******************************************************************************
'* METHOD:  OpenFile
'*    Opens a query file specified either by File or by the user.  If the
'*    current file needs saving the user will be prompted to save it prior to
'*    opening the next file.
'*
'* PARAMETERS:
'*    File  Specifies the path and name of the file to open.  If no file is
'*          specified or the file specified can not be opened, then the user
'*          will be prompted for the name of a file to open. (Optional)
'*
'* RETURNS:
'*    True if the file was successfully opened, False if canceled by the user.
'*******************************************************************************
Public Function OpenFile(Optional File As String = vbNullString) As Boolean
   Dim iFile As Long, sFile As String
   Dim sBuffer As String
   
   On Error GoTo OpenFileErr
   
   '* Get file name to open
   sFile = File
   If Not fFileExists(File) Then
      If Not fGetOpenFileName(sFile, OFN_FILEMUSTEXIST Or OFN_HIDEREADONLY) Then
         OpenFile = False
         Exit Function
      End If
   End If
       
   '* Open and read file
   iFile = FreeFile
   Open sFile For Input Access Read As #iFile
   Dim tmpStr As String

   m_iQueryCount = 0    '* Effectively removes all queries
      
   While Not EOF(iFile)
      Input #iFile, sBuffer
      sBuffer = Trim(sBuffer)
      If Len(sBuffer) Then
         AddNew
         m_sQueries(m_iQueryCount) = sBuffer
      End If
   Wend

   Close #iFile
   
   m_sFile = sFile
   m_fNewFile = False
   m_fDirty = False
   OpenFile = True

   Exit Function
OpenFileErr:
   DisplayError "Unable to open file '" & sFile & "'."
   OpenFile = False
End Function

'*******************************************************************************
'* METHOD:  Save
'*    Saves the query file
'*
'* RETURNS:
'*    True if the file was successfully saved, false if unable to save the file.
'*******************************************************************************
Public Function Save() As Boolean
   On Error GoTo SaveErr
   
   If m_fDirty Then
      
      '* if File empty or new use save as
      If Len(m_sFile) = 0 Or m_fNewFile Then
         If Not SaveAs() Then
            Save = False
         End If
         Exit Function
      End If
      
      '* Save file
      WriteQueriesToFile
   
      m_fNewFile = False
      m_fDirty = False
      Save = True
      
   End If
   
   Exit Function
SaveErr:
   DisplayError "Unable to save file '" & m_sFile & "'"
   Save = False
End Function

'*******************************************************************************
'* METHOD:  SaveAs
'*    Saves the query file under a new name supplied by the user
'*
'* RETURNS:
'*    True if the file was successfully saved, false if unable to save the file.
'*******************************************************************************
Public Function SaveAs() As Boolean
   Dim sFileNew As String, fCanceled As Boolean
   
   On Error GoTo SaveAsErr
   
   sFileNew = m_sFile
   
   '* Get new file name
   fCanceled = Not fGetSaveFileName(sFileNew, OFN_OVERWRITEPROMPT Or OFN_HIDEREADONLY)
   
   '* Save file if not canceled by user
   If fCanceled Then
      SaveAs = False
   Else
      '* Save file
      m_sFile = sFileNew
      WriteQueriesToFile
      SaveAs = True
      m_fNewFile = False
   End If
      
   Exit Function
SaveAsErr:
   DisplayError "Unable to save file '" & m_sFile & "'"
   SaveAs = False
End Function

'*******************************************************************************
'* METHOD:  AddNew
'*    Adds a new query to the file
'*******************************************************************************
Public Sub AddNew()
   Dim iUbound As Long
   
   m_iQueryCount = m_iQueryCount + 1
   iUbound = UBound(m_sQueries)
   If m_iQueryCount > iUbound Then
      iUbound = iUbound + m_iArraySizeIncrement
      ReDim Preserve m_sQueries(1 To iUbound)
   End If
   m_sQueries(m_iQueryCount) = vbNullString
End Sub

'*******************************************************************************
'* METHOD:  Remove
'*    Removes the specified query from the file
'*
'* PARAMETERS:
'*    Index    Position of the query to be removed from the file
'*******************************************************************************
Public Sub Remove(Index As Long)
   Dim i As Long
   
   Debug.Assert Index > 0
   
   If Index > m_iQueryCount Then
      Err.Raise m_iErrSubscriptOutOfBounds
   End If
   
   m_iQueryCount = m_iQueryCount - 1
   For i = Index To m_iQueryCount
      m_sQueries(i) = m_sQueries(i + 1)
   Next i
      
End Sub

'* Writes the queries to the currently specified file
'* Assumption:  m_sFile has been set to a valid file path
Private Sub WriteQueriesToFile()
   Dim iFile As Long, i As Long
   
   Debug.Assert Len(m_sFile) > 0
   
   iFile = FreeFile
   Open m_sFile For Output Access Write As #iFile
   For i = 1 To QueryCount
      Write #iFile, Queries(i)
   Next i
   
   Close #iFile
End Sub

'* Returns the file name from a file path
Private Function sGetFileName(sFile As String) As String
   Dim iPos As Long
   
   iPos = Len(sFile)
   Do Until iPos = 0
      Select Case Mid(sFile, iPos, 1)
         Case ":", "/", "\"
            Exit Do
      End Select
      iPos = iPos - 1
   Loop
   sGetFileName = Mid(sFile, iPos + 1)
End Function

'* Prompts the user for a file to open (GetuOpenFileInfoName wrapper)
Private Function fGetOpenFileName(sFile As String, _
                                  Optional iFlags As Long = 0) As Boolean
   Dim uOpenFileInfo As OPENFILENAME
   Dim iReturn As Long

   With uOpenFileInfo
      .lStructSize = Len(uOpenFileInfo)
      If Not Screen.ActiveForm Is Nothing Then
         .hwndOwner = Screen.ActiveForm.hwnd
      End If
      .hInstance = App.hInstance
      .lpstrFilter = sQueryFileFilter
      .nFilterIndex = 1
      .lpstrFile = sFile & String(257 - Len(sFile), 0)
      .nMaxFile = Len(.lpstrFile) - 1
      .lpstrFileTitle = .lpstrFile
      .nMaxFileTitle = .nMaxFile
      .flags = iFlags
   End With
   iReturn = GetOpenFileName(uOpenFileInfo)
   If iReturn = 0 Then
      fGetOpenFileName = False
   Else
      fGetOpenFileName = True
      sFile = sTrimSZ(uOpenFileInfo.lpstrFile)
   End If
End Function

'* Prompts the user for a file to save (GetSaveFileName wrapper)
'* Returns true if successful, false if canceled by the user
Private Function fGetSaveFileName(sFile As String, _
                                  Optional iFlags As Long = 0) As Boolean
   Dim uOpenFileInfo As OPENFILENAME
   Dim iReturn As Long, iLen As Long

   With uOpenFileInfo
      .lStructSize = Len(uOpenFileInfo)
      If Not Screen.ActiveForm Is Nothing Then
         .hwndOwner = Screen.ActiveForm.hwnd
      End If
      .hInstance = App.hInstance
      .lpstrFilter = sQueryFileFilter
      .nFilterIndex = 1
      .lpstrFile = sFile & String(257 - Len(sFile), 0)
      .nMaxFile = Len(.lpstrFile) - 1
      .lpstrFileTitle = .lpstrFile
      .nMaxFileTitle = .nMaxFile
      .lpstrDefExt = m_sQueryFileExt
      .flags = iFlags
   End With
   iReturn = GetSaveFileName(uOpenFileInfo)
   If iReturn = 0 Then
      fGetSaveFileName = False
   Else
      fGetSaveFileName = True
      sFile = sTrimSZ(uOpenFileInfo.lpstrFile)
   End If
End Function

'* Returns the file filter for query files
Private Function sQueryFileFilter() As String
   '* Not implemented as a constant because vb truncates constants at first
   '*   occurance of vbNullChar
   sQueryFileFilter = _
         "MDX Query Files (*." & m_sQueryFileExt & ")" & vbNullChar & _
               "*." & m_sQueryFileExt & vbNullChar & _
         "All Files" & vbNullChar & "*.*" & vbNullChar
End Function

'* Trims a C-style string at the first \0
Private Function sTrimSZ(lpstr As String) As String
   Dim iLen As Long
   
   iLen = InStr(lpstr, vbNullChar) - 1
   If iLen < 0 Then
      sTrimSZ = lpstr
   Else
      sTrimSZ = Left(lpstr, iLen)
   End If

End Function

'* Test to see if a file exists
Private Function fFileExists(sFile As String) As Boolean
   Dim iFile As Long
   
   On Error Resume Next
   
   iFile = FreeFile
   Open sFile For Input Access Read As #iFile
   
   fFileExists = (Err.Number = 0)
   
   Close #iFile
   Err.Clear
End Function



'**********************
'*** EVENT HANDLERS ***
'**********************

Private Sub Class_Initialize()
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
         
   ReDim m_sQueries(1 To m_iArraySizeIncrement)
   m_iQueryCount = 0
   m_fNewFile = True
End Sub
