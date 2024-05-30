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
Const modName = "db_Customer.Customer"

Sub UpdateStatusLog(ByVal strCustomerID As String, ByVal intStatus As Integer)
    
    On Error GoTo errHandler
    
    Dim conn As New ADODB.Connection
    Dim strSQL As String
    
    ' if status = 1 then customer is logging on
    ' if status = 0 then customer is logging off
    conn.Open "DSN=IsleHop_Billing;UID=sa;PWD=;"
    If intStatus = 1 Then
        strSQL = "Insert CustomerLogs Values('" & strCustomerID & "', GetDate(), NULL)"
    Else
        strSQL = "Update CustomerLogs Set LogoffTime = GetDate() Where CustomerID='" & strCustomerID & "' AND LogoffTime = NULL"
    End If
    conn.Execute strSQL
    
    'GetObjectContext.SetComplete
    
    Exit Sub
    
errHandler:
    
    'GetObjectContext.SetAbort
    
    Err.Raise Err.Number, SetErrSource(modName, "UpdateStatusLog"), Err.Description
    
End Sub

