VERSION 5.00
Object = "{5E9E78A0-531B-11CF-91F6-C2863C385E30}#1.0#0"; "Msflxgrd.ocx"
Begin VB.UserControl ResultsPane 
   BorderStyle     =   1  'Fixed Single
   ClientHeight    =   5505
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   10200
   ClipControls    =   0   'False
   ForeColor       =   &H80000011&
   ScaleHeight     =   5505
   ScaleWidth      =   10200
   Begin MSFlexGridLib.MSFlexGrid grdResults 
      Height          =   5505
      Left            =   0
      TabIndex        =   0
      TabStop         =   0   'False
      Top             =   0
      Width           =   10215
      _ExtentX        =   18018
      _ExtentY        =   9710
      _Version        =   65541
      Rows            =   0
      Cols            =   0
      FixedRows       =   0
      FixedCols       =   0
      BackColorBkg    =   -2147483633
      AllowBigSelection=   0   'False
      ScrollTrack     =   -1  'True
      FocusRect       =   0
      MergeCells      =   4
      AllowUserResizing=   3
      BorderStyle     =   0
   End
End
Attribute VB_Name = "ResultsPane"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
'*******************************************************************************
'* CONTROL: ResultsPane
'*    The ResultsPane provides display of the results of an MDX Query.
'*
'* PUBLIC PROPERTIES:
'*    ActiveCellset  Cellset currently being displayed (R/W)
'*    Current        Determines if the currently displayed results are current
'*                   (R/W)
'*    Pivoted        Determines if the results have been pivoted (R/W)
'*
'* PUBLIC METHODS:
'*
'* PUBLIC EVENTS:
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

Private Const m_sNullCellValue = "<Null>"
Private Const m_iCurrentForecolor = &H80000012
Private Const m_iNotCurrentForecolor = &H80000011

Private m_csActiveCellset As Cellset
Private m_fCurrent As Boolean
Private m_fPivoted As Boolean



'******************
'*** PROPERTIES ***
'******************

'*******************************************************************************
'* PROPERTY:  ActiveCellset
'*    Contains the cellset currently being displayed (R/W)
'*******************************************************************************
Public Property Get ActiveCellset() As Cellset
   Set ActiveCellset = m_csActiveCellset
End Property

Public Property Set ActiveCellset(NewActiveCellset As Cellset)
   Set m_csActiveCellset = NewActiveCellset
   Current = True
   DisplayCellset
End Property

'*******************************************************************************
'* PROPERTY:  Current
'*    Determines if the currently displayed results are current (R/W)
'*******************************************************************************
Public Property Get Current() As Boolean
   Current = m_fCurrent
End Property

Public Property Let Current(NewCurrent As Boolean)
   If Not m_fCurrent = NewCurrent Then
      m_fCurrent = NewCurrent
      If m_fCurrent Then
         grdResults.ForeColor = m_iCurrentForecolor
         grdResults.ForeColorFixed = m_iCurrentForecolor
      Else
         grdResults.ForeColor = m_iNotCurrentForecolor
         grdResults.ForeColorFixed = m_iNotCurrentForecolor
      End If
   End If
End Property

'*******************************************************************************
'* PROPERTY:  Pivoted
'*    Determines if the results have been pivoted (R/W)
'*******************************************************************************
Public Property Get Pivoted() As Boolean
   Pivoted = m_fPivoted
End Property

Public Property Let Pivoted(NewPivoted As Boolean)
   If Not m_fPivoted = NewPivoted Then
      m_fPivoted = NewPivoted
      DisplayCellset
   End If
End Property



'***************
'*** METHODS ***
'***************

'* Displays a cellset
Private Sub DisplayCellset()
    Dim axCur As Axis
    Dim psCur As Position
    Dim mbCur As Member
    Dim clCur As Cell
    Dim iCellRowCnt As Long, iCellColCnt As Long
    Dim iHeaderRowCnt As Long, iHeaderColCnt As Long
    Dim iCellRow As Long, iCellCol As Long, iCell As Long
    Dim iGrdRow As Long, iGrdCol As Long
    Dim iAxis As Long, iTuple As Long, iPos As Long
     
    '*** ADOMD Example ***
    
    ' Determine fixed area of the grid
    iHeaderRowCnt = m_csActiveCellset.Axes(0).DimensionCount
    If m_csActiveCellset.Axes.Count > 1 Then
        For iAxis = 1 To m_csActiveCellset.Axes.Count - 1
            iHeaderColCnt = iHeaderColCnt + m_csActiveCellset.Axes(iAxis).DimensionCount
        Next iAxis
    Else
        iHeaderColCnt = 0
    End If
   
    ' Determine value area of grid
    iCellColCnt = m_csActiveCellset.Axes(0).Positions.Count
    iCellRowCnt = 1
    If m_csActiveCellset.Axes.Count > 1 Then
        For iAxis = 1 To m_csActiveCellset.Axes.Count - 1
            iCellRowCnt = iCellRowCnt * m_csActiveCellset.Axes(iAxis).Positions.Count
        Next iAxis
    End If
   
    With grdResults
        .Redraw = False   '* for performance
    
        '* Prepare the grid to contain the results
        If m_fPivoted Then
            PrepareGrid iCellColCnt, iHeaderColCnt, iCellRowCnt, iHeaderRowCnt
        Else
            PrepareGrid iCellRowCnt, iHeaderRowCnt, iCellColCnt, iHeaderColCnt
        End If
    
        '* Display column headers
        Set axCur = m_csActiveCellset.Axes(0)
        If iHeaderRowCnt <> 0 Then
            iGrdCol = iHeaderColCnt
            For Each psCur In axCur.Positions
                iGrdRow = 0
                For Each mbCur In psCur.Members
                    If m_fPivoted Then
                        grdResults.TextMatrix(iGrdCol, iGrdRow) = mbCur.Caption
                    Else
                        grdResults.TextMatrix(iGrdRow, iGrdCol) = mbCur.Caption
                    End If
                    iGrdRow = iGrdRow + 1
                Next mbCur
                iGrdCol = iGrdCol + 1
            Next psCur
        End If
      
        '* Display row headers
        If m_csActiveCellset.Axes.Count > 1 Then
            'for all rows
            For iGrdRow = 0 To iCellRowCnt - 1
                iTuple = iGrdRow
                iGrdCol = iHeaderColCnt - 1
                For iAxis = 1 To m_csActiveCellset.Axes.Count - 1
                    Set axCur = m_csActiveCellset.Axes(iAxis)
                    iPos = iTuple Mod axCur.Positions.Count
                    Set psCur = axCur.Positions(iPos)
                    For Each mbCur In psCur.Members
                        If m_fPivoted Then
                            grdResults.TextMatrix(iGrdCol, iGrdRow + iHeaderRowCnt) = mbCur.Caption
                        Else
                            grdResults.TextMatrix(iGrdRow + iHeaderRowCnt, iGrdCol) = mbCur.Caption
                        End If
                        iGrdCol = iGrdCol - 1
                    Next mbCur
                    iTuple = iTuple \ axCur.Positions.Count
                Next iAxis
            Next iGrdRow
        End If
            
        '* Let grid display the axes headers we have added
        .Redraw = True
        .Refresh
        .Redraw = False
      
        '* Display cells
        iGrdRow = iHeaderRowCnt
        iCell = 0
        For iCellRow = 0 To iCellRowCnt - 1
            iGrdCol = iHeaderColCnt
            For iCellCol = 0 To iCellColCnt - 1
                Set clCur = m_csActiveCellset(iCell)
                iCell = iCell + 1
                If IsNull(clCur.Value) Then
                    If m_fPivoted Then
                        .TextMatrix(iGrdCol, iGrdRow) = m_sNullCellValue
                    Else
                        .TextMatrix(iGrdRow, iGrdCol) = m_sNullCellValue
                    End If
                Else
                    If m_fPivoted Then
                        .TextMatrix(iGrdCol, iGrdRow) = clCur.FormattedValue
                    Else
                        .TextMatrix(iGrdRow, iGrdCol) = clCur.FormattedValue
                    End If
                End If
                iGrdCol = iGrdCol + 1
            Next iCellCol
            iGrdRow = iGrdRow + 1
        Next iCellRow

        .Redraw = True
        .Refresh
    
    End With
   
    '*** End Example ***

End Sub

'* Prepares the grid to display a cellset by clearing and resizing as
'* appropriate
Private Sub PrepareGrid(iCellRowCnt As Long, _
                       iHeaderRowCnt As Long, _
                       iCellColCnt As Long, _
                       iHeaderColCnt As Long)
   Dim iGrdRow As Long, iGrdCol As Long
   
   With grdResults
      .Clear
      
      .Rows = 0
      .Cols = 0
      .Cols = iCellColCnt + iHeaderColCnt
      .Rows = iCellRowCnt + iHeaderRowCnt
      If Not iHeaderRowCnt < .Rows Then  '* MSFlexGrid requires FixedRows < Rows
         .Rows = iHeaderRowCnt + 1
         .RowHeight(iHeaderRowCnt) = 0
      End If
      .FixedRows = iHeaderRowCnt
      If Not iHeaderColCnt < .Cols Then  '* MSFlexGrid requires FixedCos < Cols
         .Cols = iHeaderColCnt + 1
         .ColWidth(iHeaderColCnt) = 0
      End If
      .FixedCols = iHeaderColCnt
    
      '* Set alignment for cells
      For iGrdCol = 0 To .Cols - 1
         .FixedAlignment(iGrdCol) = flexAlignLeftCenter
      Next iGrdCol
      
      '* Turn merge on for headers, off for cellset contents
      For iGrdCol = 0 To iHeaderColCnt - 1
         .MergeCol(iGrdCol) = True
         .ColAlignment(iGrdCol) = flexAlignLeftCenter
      Next iGrdCol
      For iGrdCol = iHeaderColCnt To .Cols - 1
         .MergeCol(iGrdCol) = False
      Next iGrdCol
      For iGrdRow = 0 To iHeaderRowCnt - 1
         .MergeRow(iGrdRow) = True
      Next iGrdRow
      For iGrdRow = iHeaderRowCnt To .Rows - 1
         .MergeRow(iGrdRow) = False
      Next iGrdRow
   End With
End Sub


'**********************
'*** EVENT HANDLERS ***
'**********************

Private Sub UserControl_Resize()
   #If Not DebugVersion Then
      On Error Resume Next
   #End If
         
   grdResults.Width = UserControl.ScaleWidth
   grdResults.Height = UserControl.ScaleHeight
End Sub
