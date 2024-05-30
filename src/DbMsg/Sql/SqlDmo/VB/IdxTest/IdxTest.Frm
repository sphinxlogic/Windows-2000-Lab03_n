VERSION 5.00
Object = "{5E9E78A0-531B-11CF-91F6-C2863C385E30}#1.0#0"; "MSFLXGRD.OCX"
Begin VB.Form frmIdxTest 
   Caption         =   "Index Test"
   ClientHeight    =   5550
   ClientLeft      =   645
   ClientTop       =   945
   ClientWidth     =   9405
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   5550
   ScaleWidth      =   9405
   Begin VB.Frame frameTestSProcs 
      Caption         =   "Test selected stored procedures with new index on table"
      Enabled         =   0   'False
      Height          =   1395
      Left            =   180
      TabIndex        =   23
      Top             =   4020
      Width           =   9015
      Begin MSFlexGridLib.MSFlexGrid gridResults 
         Height          =   1035
         Left            =   180
         TabIndex        =   26
         Top             =   240
         Width           =   6735
         _ExtentX        =   11880
         _ExtentY        =   1826
         _Version        =   65541
         Rows            =   20
         Cols            =   3
         FixedCols       =   2
      End
      Begin VB.CommandButton cmdTest 
         Caption         =   "&Test stored proc(s)"
         Enabled         =   0   'False
         Height          =   375
         Left            =   7080
         TabIndex        =   24
         Top             =   240
         Width           =   1695
      End
   End
   Begin VB.Frame frameCreateIdx 
      Caption         =   "Create new index"
      Enabled         =   0   'False
      Height          =   1695
      Left            =   180
      TabIndex        =   15
      Top             =   2160
      Width           =   9015
      Begin VB.CommandButton cmdCreateIdx 
         Caption         =   "C&reate index for test"
         Enabled         =   0   'False
         Height          =   375
         Left            =   7080
         TabIndex        =   22
         Top             =   300
         Width           =   1695
      End
      Begin VB.ListBox listColsNewIdx 
         Enabled         =   0   'False
         Height          =   1230
         Left            =   4500
         MultiSelect     =   1  'Simple
         TabIndex        =   21
         Top             =   300
         Width           =   1995
      End
      Begin VB.CommandButton cmdRmvColFromIdx 
         Caption         =   "<< Remove"
         Enabled         =   0   'False
         Height          =   375
         Left            =   3120
         TabIndex        =   19
         Top             =   1200
         Width           =   1215
      End
      Begin VB.CommandButton cmdAddColToIdx 
         Caption         =   "Add >>"
         Enabled         =   0   'False
         Height          =   375
         Left            =   3120
         TabIndex        =   18
         Top             =   780
         Width           =   1215
      End
      Begin VB.ListBox listColsTable 
         Enabled         =   0   'False
         Height          =   1230
         Left            =   960
         MultiSelect     =   1  'Simple
         Sorted          =   -1  'True
         TabIndex        =   17
         Top             =   300
         Width           =   1995
      End
      Begin VB.Label lblIndexName 
         Caption         =   "Index:"
         Height          =   555
         Left            =   6600
         TabIndex        =   25
         Top             =   960
         Width           =   2175
      End
      Begin VB.Label lblColsInIdx 
         Caption         =   "Colu&mns in index"
         Enabled         =   0   'False
         Height          =   495
         Left            =   3660
         TabIndex        =   20
         Top             =   300
         Width           =   675
      End
      Begin VB.Label lblColsInTbl 
         Caption         =   "&Columns in table"
         Enabled         =   0   'False
         Height          =   495
         Left            =   180
         TabIndex        =   16
         Top             =   300
         Width           =   675
      End
   End
   Begin VB.Frame frameDatabases 
      Caption         =   "Database/Table/Stored Procedure"
      Enabled         =   0   'False
      Height          =   1455
      Left            =   180
      TabIndex        =   8
      Top             =   540
      Width           =   9015
      Begin VB.ListBox listDatabases 
         Enabled         =   0   'False
         Height          =   1035
         Left            =   960
         Sorted          =   -1  'True
         TabIndex        =   10
         Top             =   300
         Width           =   1995
      End
      Begin VB.ListBox listSProcs 
         Enabled         =   0   'False
         Height          =   1035
         Left            =   6540
         MultiSelect     =   1  'Simple
         Sorted          =   -1  'True
         TabIndex        =   14
         Top             =   300
         Width           =   2235
      End
      Begin VB.ListBox listTables 
         Enabled         =   0   'False
         Height          =   1035
         Left            =   3540
         Sorted          =   -1  'True
         TabIndex        =   12
         Top             =   300
         Width           =   1995
      End
      Begin VB.Label lblSProc 
         Caption         =   "St&ored procs and/or views to test"
         Enabled         =   0   'False
         Height          =   975
         Left            =   5700
         TabIndex        =   13
         Top             =   300
         Width           =   795
      End
      Begin VB.Label lblTable 
         Caption         =   "Ta&ble"
         Enabled         =   0   'False
         Height          =   255
         Left            =   3060
         TabIndex        =   11
         Top             =   300
         Width           =   495
      End
      Begin VB.Label lblDatabase 
         Caption         =   "&Database"
         Enabled         =   0   'False
         Height          =   255
         Left            =   180
         TabIndex        =   9
         Top             =   300
         Width           =   855
      End
   End
   Begin VB.TextBox txtServer 
      Height          =   285
      Left            =   1020
      TabIndex        =   1
      Top             =   120
      Width           =   1455
   End
   Begin VB.TextBox txtLogin 
      Height          =   285
      Left            =   3180
      TabIndex        =   3
      Top             =   120
      Width           =   1455
   End
   Begin VB.TextBox txtPassword 
      Height          =   285
      IMEMode         =   3  'DISABLE
      Left            =   5700
      PasswordChar    =   "*"
      TabIndex        =   5
      Top             =   120
      Width           =   1455
   End
   Begin VB.CommandButton cmdConnect 
      Caption         =   "&Connect"
      Default         =   -1  'True
      Height          =   375
      Left            =   7260
      TabIndex        =   6
      Top             =   120
      Width           =   1215
   End
   Begin VB.CommandButton cmdExit 
      Caption         =   "E&xit"
      Height          =   375
      Left            =   8580
      TabIndex        =   7
      Top             =   120
      Width           =   615
   End
   Begin VB.Label lblServer 
      Caption         =   "&Server"
      Height          =   255
      Left            =   180
      TabIndex        =   0
      Top             =   150
      Width           =   735
   End
   Begin VB.Label lblLogin 
      Caption         =   "&Login"
      Height          =   255
      Left            =   2580
      TabIndex        =   2
      Top             =   150
      Width           =   615
   End
   Begin VB.Label lblPassword 
      Caption         =   "&Password"
      Height          =   255
      Left            =   4740
      TabIndex        =   4
      Top             =   150
      Width           =   855
   End
End
Attribute VB_Name = "frmIdxTest"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim oSQLServer As SQLDMO.SQLServer
Dim oCurrentDB As SQLDMO.Database
Dim oCurrentTable As SQLDMO.Table
Dim oTestIdx As SQLDMO.Index
Dim bConnected As Boolean
Private Sub cmdAddColToIdx_Click()
    'If nothing selected, return.
    If listColsTable.SelCount = 0 Then
        Exit Sub
    End If
    
    'Add the selected columns to the list of columns for
    'a new test index.
    Dim nColToAdd As Integer
    Dim idxAddAt As Integer
    idxAddAt = listColsNewIdx.ListCount
    For nColToAdd = listColsTable.ListCount - 1 To 0 Step -1
        If listColsTable.Selected(nColToAdd) = True Then
            listColsNewIdx.AddItem listColsTable.List(nColToAdd), idxAddAt
            listColsTable.RemoveItem nColToAdd
        End If
    Next nColToAdd
    cmdCreateIdx.Enabled = True
End Sub
Private Sub cmdConnect_Click()
    On Error GoTo HandleError
        
    'If we're connected, then disconnect and clear lists.
    If bConnected = True Then
        oSQLServer.DisConnect
        bConnected = False

        cmdConnect.Caption = "&Connect"
        EnableLoginPrompts (True)
        
        'Empty all lists and disable prompts.
        FillEmptyDatabaseList (False)
        EnableDatabasePrompts (False)
        Exit Sub
    End If
    
    'Set mouse pointer to "Wait" cursor.
    frmIdxTest.MousePointer = 11
    
    'Attempt a connection, then fill the properties stuff.
    oSQLServer.ApplicationName = "SQL-DMO Index Test"
    
    'If no login name, use NT Integrated security in an attempt.
    'to connect.
    If Not (Len(txtLogin.Text)) Then
        oSQLServer.LoginSecure = True
    End If
    
    oSQLServer.Connect txtServer.Text, txtLogin.Text, txtPassword.Text
    bConnected = True
    
    cmdConnect.Caption = "&Disconnect"
    EnableLoginPrompts (False)
    
    'Enable and fill database prompts from collections in SQLServer
    'object.
    EnableDatabasePrompts (True)
    
    'Fill databases list. If any databases found, select first and
    'fill tables collection.
    FillEmptyDatabaseList (True)
    If listDatabases.ListCount > 0 Then
        listDatabases.ListIndex = 0
        listDatabases_Click
    End If
    
    frmIdxTest.MousePointer = 1
    Exit Sub
        
HandleError:
    frmIdxTest.MousePointer = 1
    PrintError
    Exit Sub
End Sub
Private Sub cmdCreateIdx_Click()
    CreateTestIndex (True)
End Sub
Private Sub cmdExit_Click()
    Form_Unload (0)
    End
End Sub
Private Sub cmdRmvColFromIdx_Click()
    'If nothing in the list, test for index remove, then exit.
    If listColsNewIdx.ListCount = 0 Then
        Exit Sub
    End If
    
    Dim nColToRemove As Integer
    For nColToRemove = listColsNewIdx.ListCount - 1 To 0 Step -1
        If listColsNewIdx.Selected(nColToRemove) = True Then
            listColsTable.AddItem listColsNewIdx.List(nColToRemove)
            listColsNewIdx.RemoveItem (nColToRemove)
        End If
    Next nColToRemove
    
    If listColsNewIdx.ListCount = 0 Then
        CreateTestIndex (False)
        cmdCreateIdx.Enabled = False
    End If
End Sub
Private Sub CreateTestIndex(bCreate As Boolean)
    On Error GoTo HandleError
    If oTestIdx Is Nothing Then
        'Nothing to do
    Else
        oTestIdx.Remove
        Set oTestIdx = Nothing
    End If
    
    If bCreate = False Then
        lblIndexName.Caption = "Index:"
        Exit Sub
    End If

    frmIdxTest.MousePointer = 11
    
    Dim ncol As Integer
    Dim strColumns As String
    
    Dim oNewIdx As New SQLDMO.Index
    oNewIdx.Name = "idx_IdxTest"
    oNewIdx.Type = SQLDMOIndex_Default
    
    For ncol = 0 To listColsNewIdx.ListCount - 1
        If Len(strColumns) Then
            strColumns = strColumns + ","
        End If
        strColumns = strColumns + "[" + listColsNewIdx.List(ncol) + "]"
    Next ncol
    
    oNewIdx.IndexedColumns = strColumns
    oCurrentTable.Indexes.Add oNewIdx
    
    Set oTestIdx = oNewIdx
    lblIndexName.Caption = "Index:" + Chr(10) + Chr(13) + oTestIdx.Name
    EnableTestPrompts (True)
    
    frmIdxTest.MousePointer = 1
    Exit Sub
    
HandleError:
    frmIdxTest.MousePointer = 1
    PrintError
    Exit Sub
End Sub
Private Sub cmdTest_Click()
    On Error GoTo ErrorHandler
    
    Dim oQR As SQLDMO.QueryResults
    Dim strExec As String
    Dim strMessage As String
    Dim nProc As Integer
    Dim strSProc As String
    Dim strSProcs As String
    Dim strParams As String
    Dim oDBObj As SQLDMO.DBObject
    
    'Create and initialize statistics counters.
    Dim CPUTime As Integer
            
    Dim TotalCPUTime As Integer
    TotalCPUTime = 0
    
    'Execute the chosen stored procedures and extract statistics.
    For nProc = 0 To listSProcs.ListCount - 1
        If listSProcs.Selected(nProc) = True Then
            CPUTime = 0
            
            'Build the SQL stored procedure or view execution string.
            strSProc = listSProcs.List(nProc)
            Set oDBObj = oCurrentDB.GetObjectByName(strSProc)
            If oDBObj.Type = SQLDMOObj_StoredProcedure Then
                If GetSProcParams(oCurrentDB.StoredProcedures(strSProc), strParams) = True Then
                    strExec = "exec " + strSProc + " " + strParams
                Else
                    strExec = ""
                End If
            Else
                strExec = "select * from " + strSProc
            End If
            
            If Len(strExec) Then
                ' Enable the SQL Server statistics timing option.
                Set oQR = oCurrentDB.ExecuteWithResults("set statistics time on")
                
                ' Execute SQL execution string, retrieve results and messages.
                Set oQR = oCurrentDB.ExecuteWithResultsAndMessages(strExec, , strMessage)
                
                ' Parse statistics results from the strMessage string.
                Do While InStr(1, strMessage, "CPU time = ") > 0
                    strMessage = Right(strMessage, _
                        Len(strMessage) - InStr(1, strMessage, "CPU time = ") - (Len("CPU time = ") - 1))
                    Comma = InStr(1, strMessage, ",")
                    CPUTime = CPUTime + Val(Left(strMessage, Comma - 1))
                Loop
                
                If Len(strSProcs) Then
                    strSProcs = strSProcs + ","
                End If
                strSProcs = strSProcs + strSProc
                
                ' Disable SQL Server's statistics option
                Set oQR = oCurrentDB.ExecuteWithResults("set statistics time off")
                
                ' Keep running total of statistics for every stored procedure
                TotalCPUTime = TotalCPUTime + CPUTime
            End If
        End If
    Next nProc

    'Check to see if we did anything
    If TotalCPUTime > 0 Then
        Dim ncol As Integer
        Dim strIdxCols As String
        For ncol = 0 To listColsNewIdx.ListCount - 1
            If Len(strIdxCols) Then
                strIdxCols = strIdxCols + "::"
            End If
            strIdxCols = strIdxCols + listColsNewIdx.List(ncol)
        Next ncol
        
        'Display the results in the grid control
        gridResults.Rows = gridResults.Rows + 1
        gridResults.Row = gridResults.Rows - 1
        gridResults.Col = 0
        gridResults.Text = strIdxCols
        gridResults.Col = 1
        gridResults.Text = strSProcs
        gridResults.Col = 2
        gridResults.Text = TotalCPUTime
    End If
    
    frmIdxTest.MousePointer = 1
    Exit Sub

ErrorHandler:
    frmIdxTest.MousePointer = 1
    PrintError
    Exit Sub
End Sub
Private Sub EmptyColsInIndex()
    listColsNewIdx.Clear
End Sub
Private Sub EnableDatabasePrompts(bEnable As Boolean)
    frameDatabases.Enabled = bEnable
    lblDatabase.Enabled = bEnable
    listDatabases.Enabled = bEnable
    lblTable.Enabled = bEnable
    listTables.Enabled = bEnable
    lblSProc.Enabled = bEnable
    listSProcs.Enabled = bEnable
End Sub
Private Sub EnableIndexPrompts(bEnable As Boolean)
    frameCreateIdx.Enabled = bEnable
    lblColsInTbl.Enabled = bEnable
    listColsTable.Enabled = bEnable
    cmdAddColToIdx.Enabled = bEnable
    cmdRmvColFromIdx.Enabled = bEnable
    lblColsInIdx.Enabled = bEnable
    listColsNewIdx.Enabled = bEnable
End Sub
Private Sub EnableLoginPrompts(bEnable As Boolean)
    lblServer.Enabled = bEnable
    txtServer.Enabled = bEnable
    lblLogin.Enabled = bEnable
    txtLogin.Enabled = bEnable
    lblPassword.Enabled = bEnable
    txtPassword.Enabled = bEnable
End Sub
Private Sub EnableTestPrompts(bEnable As Boolean)
    frameTestSProcs.Enabled = bEnable
    gridResults.Enabled = bEnable
    cmdTest.Enabled = bEnable
End Sub
Private Sub FillEmptyColsToIndex(bFill As Boolean)
    listColsTable.Clear
    If bFill = True Then
        Dim oCol As SQLDMO.Column
        For Each oCol In oCurrentTable.Columns
            listColsTable.AddItem oCol.Name
        Next oCol
    End If
End Sub
Private Sub FillEmptyDatabaseList(bFill As Boolean)
    listDatabases.Clear
    If bFill = True Then
        Dim oDB As SQLDMO.Database
        For Each oDB In oSQLServer.Databases
            If oDB.SystemObject = False Then
                listDatabases.AddItem oDB.Name
            End If
        Next oDB
    End If
End Sub
Private Sub FillEmptyTableList(bFill As Boolean)
    listTables.Clear
    If bFill = True Then
        Dim oTable As SQLDMO.Table
        For Each oTable In oCurrentDB.Tables
            If oTable.SystemObject = False Then
                listTables.AddItem oTable.Name
            End If
        Next oTable
    End If
End Sub
Private Sub FillEmptySProcList(bFill As Boolean)
    listSProcs.Clear
    If bFill = True Then
        Dim oQR As SQLDMO.QueryResults
        Set oQR = oCurrentTable.EnumDependencies(SQLDMODep_Children)
        
        'If the object type is stored procedure or view, add it to
        'the list of testable objects.
        Dim nRow As Integer
        Dim oType As SQLDMO.SQLDMO_OBJECT_TYPE
        For nRow = 1 To oQR.Rows
            oType = oQR.GetColumnLong(nRow, 1)
            If oType = SQLDMOObj_StoredProcedure Or oType = SQLDMOObj_View Then
                listSProcs.AddItem oQR.GetColumnString(nRow, 2)
            End If
        Next nRow
    End If
    
    'Clean up dependent objects.
    CreateTestIndex (False)
    EmptyColsInIndex
    FillEmptyColsToIndex (False)
    EnableIndexPrompts (False)
    cmdCreateIdx.Enabled = False
End Sub
Private Sub Form_Load()
    bConnected = False
    
    Set oSQLServer = New SQLDMO.SQLServer
    oSQLServer.LoginTimeout = 15
    oSQLServer.ODBCPrefix = False
    
    'Initialize grid control's columns, widths, and headings.
    gridResults.Rows = 1
    gridResults.Cols = 3
    
    gridResults.ColWidth(0) = 2500
    gridResults.ColWidth(1) = 2400
    gridResults.ColWidth(2) = 1300
    gridResults.ColAlignment(2) = 1
    
    gridResults.Col = 0
    gridResults.Text = "Index Columns"
    gridResults.Col = 1
    gridResults.Text = "Stored Procs/Views"
    gridResults.Col = 2
    gridResults.Text = "CPU Time"
End Sub
Private Sub Form_Unload(Cancel As Integer)
    On Error Resume Next
    
    If bConnected = True Then
        CreateTestIndex (False)
        oSQLServer.DisConnect
    End If
    
    oSQLServer.Close
    Set oSQLServer = Nothing
End Sub
Private Function GetSProcParams(oSP As SQLDMO.StoredProcedure, strParams As String) As Boolean
    Dim oQR As SQLDMO.QueryResults
    Set oQR = oSP.EnumParameters
    
    'If there are no parameters, then we're fine, just continue
    If oQR.Rows = 0 Then
        GetSProcParams = True
    Else
        'Fill out the parameter dialog and display it. Return True if the
        'user indicates continue.
        Dim nParam As Integer
        Dim strDType As String
        Dim bIllegalParamFound As Boolean
        bIllegalParamFound = False
        
        'Set for failure.
        GetSProcParams = False
        
        frmIdxTestGetParams.bOK = False
        
        frmIdxTestGetParams.lblSProcName = oSP.Name
        
        frmIdxTestGetParams.gridParameters.Rows = oQR.Rows + 1
        For nParam = 1 To oQR.Rows
            If oQR.GetColumnBool(nParam, 5) = True Then
                bIllegalParamFound = True
            Else
                frmIdxTestGetParams.gridParameters.Row = nParam
                
                frmIdxTestGetParams.gridParameters.Col = 0
                frmIdxTestGetParams.gridParameters.Text = _
                    oQR.GetColumnString(nParam, 1)
                
                strDType = oQR.GetColumnString(nParam, 2)
                If InStr(1, strDType, "char") Or InStr(1, strDType, "binary") Then
                    strDType = strDType + "(" + _
                        oQR.GetColumnString(nParam, 3) + ")"
                End If
                frmIdxTestGetParams.gridParameters.Col = 1
                frmIdxTestGetParams.gridParameters.Text = strDType
                
                frmIdxTestGetParams.gridParameters.Col = 2
                frmIdxTestGetParams.gridParameters.Text = ""
            End If
        Next nParam
        
        If bIllegalParamFound = False Then
            frmIdxTestGetParams.Show vbModal, Me
            If frmIdxTestGetParams.bOK = True Then
                Dim strParam As String
                Dim strValue As String
                
                frmIdxTestGetParams.gridParameters.Col = 2
                For nParam = 1 To frmIdxTestGetParams.gridParameters.Rows - 1
                    strParam = oQR.GetColumnString(nParam, 1)

                    frmIdxTestGetParams.gridParameters.Row = nParam
                    strValue = frmIdxTestGetParams.gridParameters.Text
                    
                    If Len(strValue) Then
                        strDType = oQR.GetColumnString(nParam, 2)
                        If InStr(1, strDType, "char") Or InStr(1, strDType, "text") Or InStr(1, strDType, "date") Then
                            strValue = "'" + strValue + "'"
                        End If
                    Else
                        strValue = "NULL"
                    End If
                    
                    If Len(strParams) Then
                        strParams = strParams + ","
                    End If
                    strParams = strParams + strParam + " = " + strValue
                Next nParam
                
                GetSProcParams = True
            End If
        End If
    End If
End Function
Private Sub listDatabases_Click()
    'If no item selected, simply return.
    If listDatabases.ListIndex = -1 Or listDatabases.ListCount = 0 Then
        Set oCurrentDB = Nothing
        Set oCurrentTable = Nothing
        FillEmptyTableList (False)
        
        Exit Sub
    End If
    
    'Set to "Wait" pointer.
    frmIdxTest.MousePointer = 11
    
    'Get the selected database.
    Dim oDB As SQLDMO.Database
    Set oDB = oSQLServer.Databases(listDatabases.List(listDatabases.ListIndex))
    
    'If the database selected references the current one, return. Otherwise
    'get the list of tables from the newly selected database.
    If oCurrentDB Is Nothing Then
        Set oCurrentDB = oDB
    Else
        If oCurrentDB.Name = oDB.Name Then
            Exit Sub
        End If
        Set oCurrentDB = Nothing
        Set oCurrentDB = oDB
    End If
    
    'Get the list of tables and select the first one.
    FillEmptyTableList (True)
    If listTables.ListCount > 0 Then
        listTables.ListIndex = 0
    End If
    
    'Reset pointer.
    frmIdxTest.MousePointer = 1
End Sub
Private Sub listSProcs_Click()
    'If nothing selected, clear objects, reset prompts and return.
    If listSProcs.SelCount = 0 Then
        CreateTestIndex (False)
        EmptyColsInIndex
        FillEmptyColsToIndex (False)
        EnableIndexPrompts (False)
        cmdCreateIdx.Enabled = False
        Exit Sub
    End If
    
    EnableIndexPrompts (True)
    EnableTestPrompts (True)
    
    'If any object is selected, then fill in columns list as required.
    If listColsTable.ListCount = 0 Then
        'Set to "Wait" pointer.
        frmIdxTest.MousePointer = 11
        
        FillEmptyColsToIndex (True)
        
        'Reset pointer.
        frmIdxTest.MousePointer = 1
    End If
End Sub
Private Sub listTables_Click()
    'If no database or no tables, clear stored proc/view list and return.
    If oCurrentDB Is Nothing Or listTables.ListIndex = -1 Or listTables.ListCount = 0 Then
        Set oCurrentTable = Nothing
        FillEmptySProcList (False)
    End If
    
    'Set to "Wait" pointer.
    frmIdxTest.MousePointer = 11
    
    'Get the selected table.
    Dim oTable As SQLDMO.Table
    Set oTable = oCurrentDB.Tables(listTables.List(listTables.ListIndex))
    
    'If the table selected references the current one, return. Otherwise
    'get the list of dependent stored procedures and views.
    If oCurrentTable Is Nothing Then
        Set oCurrentTable = oTable
    Else
        If oCurrentTable.Name = oTable.Name Then
            Exit Sub
        End If
        Set oCurrentTable = Nothing
        Set oCurrentTable = oTable
    End If
    
    'Get the list of dependent stored procedures and views.
    FillEmptySProcList (True)
    listSProcs_Click
    
    'Reset pointer.
    frmIdxTest.MousePointer = 1
End Sub
Private Sub PrintError()
    Dim errString As String
    
    If Err.Number <> 0 Then
        errString$ = Err.Source & " Error " & Err.Number & ": " & Err.Description
        MsgBox errString$
    End If
End Sub

