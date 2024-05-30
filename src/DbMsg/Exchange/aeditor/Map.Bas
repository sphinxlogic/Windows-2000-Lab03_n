Attribute VB_Name = "MapTool"
Option Explicit

'***********************************************************************
'  Copyright (c) by Microsoft 1998
'***********************************************************************
'
'                MAP TOOL MODULE
'
'-----------------------------------------------------------------------
'
'  Overview: The map tool module handles the export and import of maps
'  from/to the MSFlex Grid in AEditUI form.
'
'  Note: The map is a simple comma separated file that has a special
'  character "/r" and quotes inserted for string parms that contain
'  Returns or commas. This is referred to in the code comments as an
'  embedded tokens or characters.
'
'  Note2: This map can be created with Microsoft Excell with the stipulation
'  that if you want embedded returns you must use the /n in the cell and
'  after you save the parms with the embedded returns need to have
'  quotes put around them.
'-----------------------------------------------------------------------

'Local Constants
Const SWITCH = True
Const NO_SWITCH = False

Const TOKEN_COMMA = ","
Const TOKEN_COMMA_QUOTE = ","""
Const TOKEN_QUOTE_COMMA = ""","

Const DIALOG_CANCEL_ERROR = 32755

'----------------------------------------------
'   Public Sub: Import Map
'
'   Action: Pops up a file dialog for selecting
'   the Map to Import
'
'----------------------------------------------
Public Sub ImportMap(ByRef Grid As Control)

   
    On Error GoTo ImportMapErr
    
    Dim sTempStr As String    'Temporary String
    Dim ilocate As Integer    'Locate of token in string
    Dim sFilename As String   'Filename as string
    Dim sSPN As String        'PathName and Filename
    Dim errinfo As String
    
    With AEditorUI
      
      Call SetUpDialog(.CommonDialog1, "Import Map")
      ' Set CancelError is True
    
      ' Set filters
      .CommonDialog1.Filter = "Map Files (*.map)|*.map|CSV Files" & _
           "(*.csv)|*.csv|All Files (*.*)|*.*|"
      
      ' Display the Open dialog box
      .CommonDialog1.ShowOpen
         
      ' Display name of selected file
      AEClass.MapPathName = .CommonDialog1.filename
    
      'Figure out initial directory and save
      sSPN = .CommonDialog1.filename
      sFilename = .CommonDialog1.FileTitle
        
      'Locate the last "\"
      ilocate = InStr(1, sSPN, sFilename)
      AEClass.MapInitDir = Left(sSPN, ilocate - 1)
    
      'Load Map
      Call FileToMap(.CommonDialog1.filename, errinfo, Grid)
      
    End With
    
Exit Sub

'-------------------
ImportMapErr:
    If Err.Number = CdoE_CANCEL Or Err.Number = DIALOG_CANCEL_ERROR Then
       'User pressed the Cancel button
    Else
       AgentMap.CdoErrorHandler ("Import Map")
    End If
End Sub

'-------------------------------------------------------
'
'  Name: SET UP DIALOG
'
'  Action: Sets up default parms for the open and save
'  map dialogs.
'
'-------------------------------------------------------
Private Sub SetUpDialog(ByRef cDialog As Control, sTitle)

   ' Enable Cancelling
   cDialog.CancelError = True
    
   'Set Title
   cDialog.DialogTitle = sTitle

   ' Clear Filename
   cDialog.filename = ""
   
   ' Set flags
   cDialog.Flags = cdlOFNHideReadOnly
   
   cDialog.InitDir = AEClass.MapInitDir
    
   ' Specify default filter to be first one
   cDialog.FilterIndex = 1
     
End Sub

'----------------------------------------------
'
'   Public Sub: Export Map
'
'   Action: Exports map from the grid to a comma
'   delimited file.
'
'----------------------------------------------
Public Sub ExportMap(ByRef Grid As Control)

    On Error GoTo ExportMapErr
    
    Dim errstring As String
    
    Dim sTempStr As String    'Temporary String
    Dim ilocate As Integer    'Locate of token in string
    Dim sFilename As String   'Filename as string
    Dim sSPN As String        'PathName and Filename
    
    With AEditorUI
      
      Call SetUpDialog(.CommonDialog1, "Export Map")
      
      ' Set filters
      .CommonDialog1.Filter = "Map Files (*.map)|*.map|CSV Files" & _
           "(*.csv)|*.csv|All Files (*.*)|*.*|"
      
      ' Display the Open dialog box
      .CommonDialog1.ShowSave
         
      ' Display name of selected file
      AEClass.MapPathName = .CommonDialog1.filename
    
      'Figure out initial directory and save
      sSPN = .CommonDialog1.filename
      sFilename = .CommonDialog1.FileTitle
        
      'Locate the last "\"
      ilocate = InStr(1, sSPN, sFilename)
      AEClass.MapInitDir = Left(sSPN, ilocate - 1)
    
      Call MapToFile(.CommonDialog1.filename, errstring, Grid)
      
    End With
    
    Exit Sub

   
'-------------------
ExportMapErr:
    If Err.Number = CdoE_CANCEL Or Err.Number = DIALOG_CANCEL_ERROR Then
       'User pressed the Cancel button
    Else
       AgentMap.CdoErrorHandler ("Export Map")
    End If
    
End Sub

'-------------------------------------------------------
'
'  Name: MAP TO FILE
'
'  Action: This function opens the specified map and
'  and writes it to a file, line by line.
'
'-------------------------------------------------------
'  Note: Must perform a Get Msg and Get Map before this
'  function.
'-------------------------------------------------------

Private Function MapToFile(ByVal sMapPath As String, ByRef errstring As String, ByRef Grid As Control) As Integer
  
  Dim b_OK As Boolean             'Boolean Success
  
  Dim lCol As Long                'Long Column Number
  Dim lRow As Long                'Long Row Number
  Dim lParamCols As Long          'Long Number of Columns
  Dim lCurParamCol As Long        '
  
  Dim iVal As Integer             'Return integer err value (>0 is error)
  Dim iFileNum As Integer         'File Number
  Dim vntField As Variant         'Variant Field Array
  Dim vData As Variant            'Variant Data
  
  Dim sRow As String              'Comma delimited row string
  Dim sCell As String             'Cell String
  
  Dim vTempDouble As Double       'Allocate a double to check for double data type
  
  Dim bMapError As Boolean        'Map Error
  
  Dim bBlank As Boolean           'Blank Column Flag
  
  'Get Free File Number
  iFileNum = FreeFile
  
  bMapError = False
  
  'Open Map file
  Open sMapPath For Output As #iFileNum
  
  On Error GoTo MapToFileError
  
  If Grid.TextMatrix(1, 0) = "" And Grid.Rows = 2 Or Grid.Enabled = False Then
      'Nothing To Save
      MsgBox "Nothing to export.", vbInformation, App.Title
      bMapError = True
      GoTo Cleanup
  End If
   
   'Check for accurate entry
  For lRow = 1 To Grid.Rows - 1
      If Len(Grid.TextMatrix(lRow, 0)) > 0 And Grid.TextMatrix(lRow, 0) <> " " Then
          
         vData = Grid.TextMatrix(lRow, 0)
         
         'Filter out errors with activity ID Being to a double, a string, or negative
         If IsNumeric(vData) = False Then
            MsgBox "Activity ID must be a number in row " & lRow & ". Map not exported."
            bMapError = True
            GoTo Cleanup
         End If
         vTempDouble = 2147483648#
         If CDbl(vData) >= vTempDouble Then
            MsgBox "Activity ID must be smaller than 2147483648 in row " & lRow & ". Map not exported."
            bMapError = True
            GoTo Cleanup
         ElseIf CDbl(vData) < 1 Then
            MsgBox "Activity ID must a number greater than zero in row " & lRow & ". Map not exported."
            bMapError = True
            GoTo Cleanup
         End If
                
         vData = Grid.TextMatrix(lRow, 2)
         'Filter out nonnumeric and neg or > 2 for parameter 2
         If IsNumeric(vData) = False Then
            MsgBox "Flag must be a number in row " & lRow & ". Map not exported."
            bMapError = True
            GoTo Cleanup
         End If
         vTempDouble = 2#
         If CDbl(vData) > vTempDouble Then
            MsgBox "Flag must be smaller than 3 in row " & lRow & ". Map not exported."
            bMapError = True
            GoTo Cleanup
         ElseIf CDbl(vData) < 0 Then
            MsgBox "Flag must be a positive number in row " & lRow & ". Map not exported."
            bMapError = True
            GoTo Cleanup
         End If
         
         'Trap embedded numerics or blank in function name
         vData = Grid.TextMatrix(lRow, 1)
         If IsNumeric(vData) = True Then
            MsgBox "Cannot use numbers only in function name in row " & lRow & ". Map not exported."
            bMapError = True
            GoTo Cleanup
         End If
         If Len(vData) = 0 Then
            MsgBox "Activity cannot be zero length in row " & lRow & ". Map not exported."
            bMapError = True
            GoTo Cleanup
         End If
         If Len(LTrim(vData)) = 0 Then
            MsgBox "Activity doesn't contain any characters in row " & lRow & ". Map not exported."
            bMapError = True
            GoTo Cleanup
         End If
                  
         
         With Grid 'Use the msflexgrid
            lParamCols = 0
            bBlank = False
            For lCol = 3 To Grid.Cols - 1
               If Len(Grid.TextMatrix(lRow, lCol)) <> 0 And Len(LTrim(Grid.TextMatrix(lRow, lCol))) <> 0 Then
                  lParamCols = lParamCols + 1
                  'If there was a blank in a column and another value is detected then
                  'post error.
                  If bBlank = True Then
                     MsgBox "Empty column in row " & lRow & ". Map not exported."
                     bMapError = True
                     GoTo Cleanup
                  End If
               Else
                  bBlank = True
               End If
            Next
            
            'if flag = 1 - must supply a parameter
            If lParamCols = 0 Then
               If .TextMatrix(lRow, 2) = "2" Then
                  MsgBox "All activity items with a Flag set to '2' must supply a parameter." & vbCrLf & vbCrLf & "Map not exported.", vbOKOnly + vbInformation, App.Title
                  bMapError = True
                  GoTo Cleanup
               End If
            End If
        End With
      Else
        'Trap Blank rows as error except for last one.
        If Grid.Rows - 1 = lRow Then
            'Ignore since this is the last row
        Else
            MsgBox "A column is empty in Row " & lRow & ". Map not exported.", vbExclamation, App.Title
            bMapError = True
            GoTo Cleanup
        End If
      End If
   Next lRow

   
   'Now write the map to a file iterating through all the rows one at a time
   For lRow = 1 To Grid.Rows - 2
   
      '--------
      With Grid
         'Clear Row
         sRow = ""
         
         'Fill first 3 parms
         sRow = sRow & CStr(.TextMatrix(lRow, 0)) & "," & CStr(.TextMatrix(lRow, 1)) _
                     & "," & CStr(.TextMatrix(lRow, 2))
         
         'Iterate through the extra parameters skipping the
         'first 3 and trapping for embedded commas and returns
         For lCol = 3 To Grid.Cols - 1
             sCell = CStr(Grid.TextMatrix(lRow, lCol))
             If sCell <> "" And Len(LTrim(sCell)) <> 0 Then
               If InStr(sCell, ",") = 0 And Not bTokenizeRet(sCell) Then
                  sRow = sRow & "," & sCell
               Else
                  'Place string with embedded characters in quotes
                  sRow = sRow & "," & """" & sCell & """"
               End If
             End If
         Next
      End With
    
      'Print to file a row at a time.
      Print #iFileNum, CStr(sRow)
   
   Next lRow

   'It's been saved.
   MsgBox "Map exported successfully."
  
'---------------
Cleanup:
  
  Close #iFileNum
    
  On Error Resume Next
  If bMapError Then
      Kill sMapPath
      Err.Clear
  End If
  
  Exit Function
  
'---------------
MapToFileError:

  
  Call AgentMap.CdoErrorHandler("MapToFile")
  
  GoTo Cleanup
  

End Function

'------------------------------------------------------
'
'   Function: bTokenizeRet
'
'   Action: If asc(13)Asc(10) are embedded in the string
'   replace all instances otherwise simply return false.
'------------------------------------------------------
Private Function bTokenizeRet(ByRef sCell As String)

bTokenizeRet = False

Do While InStr(sCell, Chr(13))
   bTokenizeRet = True
   sCell = InsertRet(sCell)
Loop

End Function

'------------------------------------------------------
'
'   Function: Insert Ret
'
'   Action: Inserts "\n" in the place of ASC(13)ASC(10)
'------------------------------------------------------
Private Function InsertRet(ByVal sCell As String)
   Dim ilocate As Integer
   Dim sFirst As String
   Dim sLast As String
   
   ilocate = InStr(sCell, Chr(13))
   sFirst = Mid(sCell, 1, ilocate - 1)
   sLast = Mid(sCell, ilocate + 2)
   InsertRet = sFirst & "\n" & sLast
   
End Function

'-------------------------------------------------------
'
'  Name: FILE TO MAP
'
'  Action: This function opens the specified map file and
'  reads it in line by line, inserts the rows
'  into the grid.
'
'-------------------------------------------------------

Private Function FileToMap(ByVal sMapPath As String, ByRef errstring As String, ByRef cGrid As Control) As Integer

  On Error GoTo FileToMapErr
  
  
  Dim iFileNum As Integer          'Free File Number integer
  Dim iParms As Integer            'Number of Parms in String
  Dim iX As Integer                'Loop integer
  Dim iVal As Integer
  
  Dim sLine As String              'String Read in from file
  Dim sFailRow As String           'Row Failure Occured
  
  Dim ocParms As New Collection    'Parameter collection
  
  Dim oRow As Variant              'IRow Variant
  
  Dim b_OK As Boolean              'Boolean Success
  
  '--------- Grid Variables
  Dim lRowCnt As Long
  Dim lLoopCnt As Long
  
  'Set default as no error
  FileToMap = NO_ERROR
    
  
  '--------- Setup Grid
  Call ClearGrid
  
  'Number of Rows to start (header and first row)
  lRowCnt = 2
  cGrid.Rows = lRowCnt
  lLoopCnt = 0
  
  '--------- Setup Input File
  
  'Get Free File Number
  iFileNum = FreeFile
  
  'Open Map file
  Open sMapPath For Input As #iFileNum
  
  'Loop through lines on map file and insert them
  'into the Grid
  Do While Not EOF(iFileNum)
     If Not EOF(iFileNum) Then
        Line Input #iFileNum, sLine
        If sLine = "" Then  'Exit on first blank line
            If lLoopCnt <> 0 Then
               Call DirtyStatusUpdate(DIRTY_MAP, DIRTY_ADD)
            End If
            Call FormatGridHeaders
            GoTo FileToMapErr
        End If
               
        lLoopCnt = lLoopCnt + 1
        lRowCnt = lRowCnt + 1
        cGrid.Rows = lRowCnt
        sFailRow = lRowCnt - 2
        
        'Get the number of parms and the parms
        'in a collection
        iParms = ProcessMapLine(sLine, ocParms)
        
        'make sure there are at least 4
        If iParms < 3 Then
           MsgBox "To Few Parameters on row " & sFailRow & ". Map couldn't be completely imported."
           GoTo FileToMapErr
        End If
        
        
        'Set Column Size (if it's bigger than last size, expand it)
        If iParms > cGrid.Cols Then
            cGrid.Cols = iParms
        End If
     
        'Validate first 3 parms then
        'write them to the row object
        If Not IsNumeric(ocParms.item(1)) Then
          MsgBox "ActivityID not numeric in row " & sFailRow & ". Map couldn't be completely imported."
          GoTo FileToMapErr
        End If
        If Not IsNumeric(ocParms.item(3)) Then
          MsgBox "Flag column is not numeric in row " & sFailRow & ". Map couldn't be completely imported."
          GoTo FileToMapErr
        Else
          If Val(ocParms.item(3)) > 2 Or Val(ocParms.item(3)) < 0 Then
            MsgBox "Flag out of range in row " & sFailRow & ". Map couldn't be completely imported."
            GoTo FileToMapErr
          End If
        End If
        If IsNumeric(ocParms.item(2)) Then
          MsgBox "Activity is not a string in row " & sFailRow & ". Map couldn't be completely imported."
          GoTo FileToMapErr
        End If
        
        'Write the parms
        For iX = 0 To ocParms.Count - 1
           If IsNumeric(ocParms.item(iX + 1)) Then
               cGrid.TextMatrix(lLoopCnt, iX) = CStr(ocParms.item(iX + 1))
           Else
               cGrid.TextMatrix(lLoopCnt, iX) = ocParms.item(iX + 1)
           End If
        Next
        
     End If
  Loop

'--------------
FileToMapErr:

    If Err.Number = 0 Then
           'Map was read in properly, this is a EOF notification
           Call DirtyStatusUpdate(DIRTY_MAP, DIRTY_ADD)
           Call FormatGridHeaders
           Call MapEditingToggle(True)
    Else
        MsgBox GetSpecialErrorString(FileToMap) & vbCrLf & vbCrLf & "Error Number: " & FileToMap
        Err.Clear
    End If
    
    Close #iFileNum
    Set ocParms = Nothing
    
End Function

'-------------------------------------------------
'
'  Name: PROCESS MAP LINE
'
'  Action: This function retrieves the number of
'  parms that are in a line of a comma delimited
'  map file.
'
'--------------------------------------------------
Private Function ProcessMapLine(ByVal sLine As String, ByRef ocParms As Collection) As Integer

Dim bFinished As Boolean
Dim icount As Integer
Dim ilocate As Integer
Dim iLocateStart As Integer
Dim iLocateEnd As Integer
Dim iLocateTemp As Integer

Dim bQuoted As Boolean
Dim bActiveQuote As Boolean

Dim sTempEmbedded As String

bFinished = False
icount = 0
ilocate = 0
iLocateStart = 0
iLocateEnd = 0

'Clear Collection
Set ocParms = New Collection

'Set return default to zero
ProcessMapLine = 0

'Put individual arguments from the line
Do While Not bFinished
    If bQuoted Then
      'We are processing a quoted string so find the next
      'quote command token and if it doesn't exist take
      'all to end of line, otherwise, also check for
      'another embedded strings following it.
      iLocateEnd = InStr(ilocate, sLine, TOKEN_QUOTE_COMMA)
      bActiveQuote = True
      If iLocateEnd > 0 Then
         If Mid(sLine, iLocateEnd + 1, 2) = TOKEN_COMMA_QUOTE Then
            bQuoted = True
         Else
            bQuoted = False
         End If
         ilocate = iLocateEnd
      Else
         ilocate = 0
      End If
      
    Else
      'On first pass and others that aren't quoted then
      'find the next parm if one exists. If it is a
      'comma quote then set the comma quote flag for the next pass
      'so we can skip embedded commas in quotes.
      bActiveQuote = False
      ilocate = InStr(ilocate + 1, sLine, TOKEN_COMMA)
      If ilocate > 0 Then
         If Mid(sLine, ilocate, 2) = TOKEN_COMMA_QUOTE Then
            bQuoted = True
         Else
            bQuoted = False
         End If
      End If
    End If
    
    'If this is the last parm then iLocate = 0
    If ilocate > 0 Then
       If bActiveQuote Then
         sTempEmbedded = CStr(Mid(sLine, iLocateStart + 2, ilocate - iLocateStart - 2))
         Call bUnTokenizeRet(sTempEmbedded)
         ocParms.Add sTempEmbedded
         ilocate = ilocate + 1
       Else
         ocParms.Add CStr(Mid(sLine, iLocateStart + 1, ilocate - iLocateStart - 1))
       End If
    Else
       If bActiveQuote Then
         sTempEmbedded = CStr(Mid(Left(sLine, Len(sLine) - 1), iLocateStart + 2))
         Call bUnTokenizeRet(sTempEmbedded)
         ocParms.Add sTempEmbedded
       Else
         ocParms.Add CStr(Mid(sLine, iLocateStart + 1))
       End If
    End If
    
    iLocateStart = ilocate
    icount = icount + 1
    If ilocate = 0 Then
       bFinished = True
       ProcessMapLine = icount
    End If
Loop

End Function

'------------------------------------------------------
'
'   Function: bUnTokenizeRet
'
'   Action: If \n is in an embedded string then
'   search and replace all instances otherwise simply
'   return false.
'------------------------------------------------------
Private Function bUnTokenizeRet(ByRef sCell As String)

bUnTokenizeRet = False

Do While InStr(sCell, "\n")
   bUnTokenizeRet = True
   sCell = RemoveRet(sCell)
Loop

End Function

'------------------------------------------------------
'
'   Function: Remove Ret
'
'   Action: Inserts ASC(13)ASCI(10) in the place of "\n"
'------------------------------------------------------
Private Function RemoveRet(ByVal sCell As String)
   Dim ilocate As Integer
   Dim sFirst As String
   Dim sLast As String
   
   ilocate = InStr(sCell, "\n")
   sFirst = Mid(sCell, 1, ilocate - 1)
   sLast = Mid(sCell, ilocate + 2)
   RemoveRet = sFirst & Chr(13) & Chr(10) & sLast
   
End Function


