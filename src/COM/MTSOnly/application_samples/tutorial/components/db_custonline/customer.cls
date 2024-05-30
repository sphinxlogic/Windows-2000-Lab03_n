VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "Customer"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit
Const modName = "db_CustOnline.Customer"

Public Function UpdateStatus(ByVal strCustomerID As String, ByVal intStatus As Integer) As String

    On Error GoTo errHandler
    
    Dim conn As New ADODB.Connection
    Dim rs As ADODB.Recordset
    Dim strSQL As String
    Dim varRecords
    
    ' if status = 1 then customer is logging on
    ' if status = 0 then customer is logged off
    conn.Open "DSN=IsleHop_Online;UID=sa;PWD=;"
    strSQL = "Select CustomerID, Status from CustomersOnline Where CustomerID = '" & strCustomerID & "'"
    Set rs = conn.Execute(strSQL, varRecords)
    'If rs!Status = 1 Then
    '    Err.Raise caErrCustomerAlreadyOn, "db_CustOnline.Customer", caErrCustomerAlreadyOnDesc
    'End If
    strSQL = "Update CustomersOnline Set Status = " & intStatus & " Where CustomerID = '" & strCustomerID & "'"
    conn.Execute strSQL, varRecords
    
    If varRecords = 0 Then
        Err.Raise Err.Number, Err.Source, Err.Description
    End If
    
    'GetObjectContext.SetComplete
    
    Exit Function
    
errHandler:
    
    'GetObjectContext.SetAbort
    
    Err.Raise Err.Number, SetErrSource(modName, "UpdateStatus"), Err.Description
    
End Function

Function GetByID(ByVal strCustomerID As String) As ADODB.Recordset

    On Error GoTo errHandler
    
    Dim rs As New ADODB.Recordset
    Dim strSQL As String
    
    rs.CursorLocation = adUseClient
    strSQL = "Select * from Customers Where CustomerID = '" & strCustomerID & "'"
    rs.Open strSQL, "DSN=IsleHop_Online;UID=sa;PWD=;", adOpenStatic, adLockBatchOptimistic, adCmdText
    
    'GetObjectContext.SetComplete
    
    Set GetByID = rs
    
    Exit Function
    
errHandler:

    If Not rs Is Nothing Then
        Set rs = Nothing
    End If
    
    'GetObjectContext.SetAbort
    
    Err.Raise Err.Number, SetErrSource(modName, "GetByID"), Err.Description

End Function

