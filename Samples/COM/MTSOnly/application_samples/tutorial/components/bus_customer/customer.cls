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
Const modName = "bus_Customer.Customer"

Public Sub Login(ByVal strCustomerID As String, ByVal strPassword As String)
    
    On Error GoTo errHandler
    
    Dim objCustomer As New db_CustomerQC6Lib.QC_Customer
    'Dim objCustomer As New db_Customer.Customer
    Dim objCustOnline As db_CustOnline.Customer
    Dim objOnlineEvents As Object
    Dim rs As ADODB.Recordset

    ' First check that the customer ID is valid
    Set objCustOnline = CreateObject("db_CustOnline.Customer")
    Set rs = objCustOnline.GetByID(strCustomerID)
    If rs.BOF = True And rs.EOF = True Then
        Err.Raise caErrCustomerNotFound, Err.Source, caErrCustomerNotFoundDesc
    End If
    
    ' Check that the entered password is valid
    If rs!Password <> strPassword Then
        Err.Raise caErrInvalidLogon, Err.Source, caErrInvalidLogonDesc
    End If
    
    ' Update the Customer Online status to show customer is logged on
    objCustOnline.UpdateStatus strCustomerID, 1
    
    ' Update the Customer Billing log and set start time`
   'Set objCustomer = CreateObject("db_customerQCLib.QC_Customer")
    objCustomer.UpdateStatusLog strCustomerID, 1
    
    Set objOnlineEvents = CreateObject("OnlineEvents")
    objOnlineEvents.Update strCustomerID
    
    ' Put event code here

    GetObjectContext.SetComplete
    
    Exit Sub
    
errHandler:

    If Not rs Is Nothing Then
        Set rs = Nothing
    End If
    
    GetObjectContext.SetAbort
    
    Err.Raise Err.Number, SetErrSource(modName, "Login"), Err.Description
    
End Sub

Public Sub Logout(ByVal strCustomerID As String)

    On Error GoTo errHandler
    
    Dim objCustomer As db_Customer.Customer
    Dim objCustOnline As db_CustOnline.Customer
    Dim strResult1, strResult2 As String

    ' Update the customer billing log with the logout time
    Set objCustomer = CreateObject("db_Customer.Customer")
    objCustomer.UpdateStatusLog strCustomerID, 0
    
    ' Update the customer online status to show logged off
    Set objCustOnline = CreateObject("db_CustOnline.Customer")
    objCustOnline.UpdateStatus strCustomerID, 0
    
    ' Put more events here
    
    GetObjectContext.SetComplete

    Exit Sub
    
errHandler:
    
    GetObjectContext.SetAbort
    
    Err.Raise Err.Number, SetErrSource(modName, "Logout"), Err.Description
    
End Sub
