VERSION 5.00
Begin VB.Form frmCustomers 
   Caption         =   "Customers"
   ClientHeight    =   5040
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   8100
   Icon            =   "frmCustomers.frx":0000
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MDIChild        =   -1  'True
   ScaleHeight     =   5040
   ScaleWidth      =   8100
   Begin VB.CommandButton cmdSave 
      Caption         =   "&Save"
      Enabled         =   0   'False
      Height          =   375
      Left            =   5640
      TabIndex        =   26
      Top             =   4560
      Width           =   1095
   End
   Begin VB.CommandButton cmdEnd 
      Caption         =   ">>"
      Height          =   375
      Left            =   1440
      TabIndex        =   22
      Top             =   4560
      Width           =   375
   End
   Begin VB.CommandButton cmdNext 
      Caption         =   ">"
      Height          =   375
      Left            =   1080
      TabIndex        =   21
      Top             =   4560
      Width           =   375
   End
   Begin VB.CommandButton cmdPrevious 
      Caption         =   "<"
      Height          =   375
      Left            =   600
      TabIndex        =   20
      Top             =   4560
      Width           =   375
   End
   Begin VB.CommandButton cmdFirst 
      Caption         =   "<<"
      Height          =   375
      Left            =   240
      TabIndex        =   19
      Top             =   4560
      Width           =   375
   End
   Begin VB.CommandButton cmdDelete 
      Caption         =   "&Delete"
      Height          =   375
      Left            =   3240
      TabIndex        =   24
      Top             =   4560
      Width           =   1095
   End
   Begin VB.CommandButton cmdExit 
      Caption         =   "&Exit"
      Height          =   375
      Left            =   6840
      TabIndex        =   27
      Top             =   4560
      Width           =   1095
   End
   Begin VB.CommandButton cmdAdd 
      Caption         =   "&Add"
      Height          =   375
      Left            =   2040
      TabIndex        =   23
      Top             =   4560
      Width           =   1095
   End
   Begin VB.CommandButton cmdEdit 
      Caption         =   "Edi&t"
      Height          =   375
      Left            =   4440
      TabIndex        =   25
      Top             =   4560
      Width           =   1095
   End
   Begin VB.TextBox txtShipZip 
      Height          =   285
      Left            =   3480
      TabIndex        =   17
      Top             =   3960
      Width           =   855
   End
   Begin VB.TextBox txtShipState 
      Height          =   285
      Left            =   5400
      TabIndex        =   18
      Top             =   3960
      Width           =   1815
   End
   Begin VB.TextBox txtShipCity 
      Height          =   285
      Left            =   600
      TabIndex        =   16
      Top             =   3960
      Width           =   2175
   End
   Begin VB.TextBox txtShipAddress2 
      Height          =   285
      Left            =   1440
      TabIndex        =   15
      Top             =   3480
      Width           =   6495
   End
   Begin VB.TextBox txtShipAddress1 
      Height          =   285
      Left            =   1440
      TabIndex        =   14
      Top             =   3240
      Width           =   6495
   End
   Begin VB.TextBox txtCCNumber 
      Height          =   285
      Left            =   6240
      TabIndex        =   13
      Top             =   2760
      Width           =   1695
   End
   Begin VB.TextBox txtCCExp 
      Height          =   285
      Left            =   3720
      TabIndex        =   12
      Top             =   2760
      Width           =   1335
   End
   Begin VB.TextBox txtMethod 
      Height          =   285
      Left            =   1800
      TabIndex        =   11
      Top             =   2760
      Width           =   1095
   End
   Begin VB.TextBox txtWorkPhone 
      Height          =   285
      Left            =   4920
      TabIndex        =   10
      Top             =   2280
      Width           =   2295
   End
   Begin VB.TextBox txtHomePhone 
      Height          =   285
      Left            =   1320
      TabIndex        =   9
      Top             =   2280
      Width           =   2295
   End
   Begin VB.TextBox txtZip 
      Height          =   285
      Left            =   5400
      TabIndex        =   8
      Top             =   1800
      Width           =   1815
   End
   Begin VB.TextBox txtState 
      Height          =   285
      Left            =   3480
      TabIndex        =   7
      Top             =   1800
      Width           =   855
   End
   Begin VB.TextBox txtCity 
      Height          =   285
      Left            =   600
      TabIndex        =   6
      Top             =   1800
      Width           =   2175
   End
   Begin VB.TextBox txtAddress2 
      Height          =   285
      Left            =   1440
      TabIndex        =   5
      Top             =   1320
      Width           =   6495
   End
   Begin VB.TextBox txtAddress1 
      Height          =   285
      Left            =   1440
      TabIndex        =   4
      Top             =   1080
      Width           =   6495
   End
   Begin VB.TextBox txtCompanyName 
      Height          =   285
      Left            =   3960
      TabIndex        =   0
      Top             =   120
      Width           =   3975
   End
   Begin VB.TextBox txtLastName 
      Height          =   285
      Left            =   6360
      TabIndex        =   3
      Top             =   600
      Width           =   1575
   End
   Begin VB.TextBox txtMiddleName 
      Height          =   285
      Left            =   3840
      TabIndex        =   2
      Top             =   600
      Width           =   1575
   End
   Begin VB.TextBox txtFirstName 
      Height          =   285
      Left            =   1080
      TabIndex        =   1
      Top             =   600
      Width           =   1575
   End
   Begin VB.Line Line1 
      X1              =   0
      X2              =   8160
      Y1              =   4440
      Y2              =   4440
   End
   Begin VB.Label lblCustID 
      AutoSize        =   -1  'True
      Caption         =   "Customer ID:"
      Height          =   195
      Left            =   120
      TabIndex        =   47
      Top             =   120
      Width           =   915
   End
   Begin VB.Label lblShipZip 
      AutoSize        =   -1  'True
      Caption         =   "Zip Code:"
      Height          =   195
      Left            =   4560
      TabIndex        =   46
      Top             =   3960
      Width           =   690
   End
   Begin VB.Label lblShipState 
      AutoSize        =   -1  'True
      Caption         =   "State:"
      Height          =   195
      Left            =   3000
      TabIndex        =   45
      Top             =   3960
      Width           =   420
   End
   Begin VB.Label lblShipCity 
      AutoSize        =   -1  'True
      Caption         =   "City:"
      Height          =   195
      Left            =   240
      TabIndex        =   44
      Top             =   3960
      Width           =   300
   End
   Begin VB.Label lblShipAddress2 
      AutoSize        =   -1  'True
      Caption         =   "Ship Address 2:"
      Height          =   195
      Left            =   240
      TabIndex        =   43
      Top             =   3480
      Width           =   1110
   End
   Begin VB.Label lblShipAddress1 
      AutoSize        =   -1  'True
      Caption         =   "Ship Address 1:"
      Height          =   195
      Left            =   240
      TabIndex        =   42
      Top             =   3240
      Width           =   1110
   End
   Begin VB.Label lblCCExp 
      AutoSize        =   -1  'True
      Caption         =   "CC Exp:"
      Height          =   195
      Left            =   3120
      TabIndex        =   41
      Top             =   2760
      Width           =   570
   End
   Begin VB.Label lblCCNumber 
      AutoSize        =   -1  'True
      Caption         =   "CC Number:"
      Height          =   195
      Left            =   5280
      TabIndex        =   40
      Top             =   2760
      Width           =   855
   End
   Begin VB.Label lblMethod 
      AutoSize        =   -1  'True
      Caption         =   "Method of Payment:"
      Height          =   195
      Left            =   240
      TabIndex        =   39
      Top             =   2760
      Width           =   1425
   End
   Begin VB.Label lblWorkPhone 
      AutoSize        =   -1  'True
      Caption         =   "Work Phone:"
      Height          =   195
      Left            =   3840
      TabIndex        =   38
      Top             =   2280
      Width           =   945
   End
   Begin VB.Label lblHomePhone 
      Caption         =   "Home Phone:"
      Height          =   255
      Left            =   240
      TabIndex        =   37
      Top             =   2280
      Width           =   975
   End
   Begin VB.Label lblZip 
      AutoSize        =   -1  'True
      Caption         =   "Zip Code:"
      Height          =   195
      Left            =   4560
      TabIndex        =   36
      Top             =   1800
      Width           =   690
   End
   Begin VB.Label lblState 
      AutoSize        =   -1  'True
      Caption         =   "State:"
      Height          =   195
      Left            =   3000
      TabIndex        =   35
      Top             =   1800
      Width           =   420
   End
   Begin VB.Label lblCity 
      AutoSize        =   -1  'True
      Caption         =   "City:"
      Height          =   195
      Left            =   240
      TabIndex        =   34
      Top             =   1800
      Width           =   300
   End
   Begin VB.Label lblAddress2 
      AutoSize        =   -1  'True
      Caption         =   "Maill Address 2:"
      Height          =   195
      Left            =   240
      TabIndex        =   33
      Top             =   1320
      Width           =   1110
   End
   Begin VB.Label lblAddress1 
      AutoSize        =   -1  'True
      Caption         =   "Mail Address 1:"
      Height          =   195
      Left            =   240
      TabIndex        =   32
      Top             =   1080
      Width           =   1080
   End
   Begin VB.Label lblCompanyName 
      AutoSize        =   -1  'True
      Caption         =   "Company Name:"
      Height          =   195
      Left            =   2760
      TabIndex        =   31
      Top             =   120
      Width           =   1170
   End
   Begin VB.Label lblLastName 
      AutoSize        =   -1  'True
      Caption         =   "Last Name:"
      Height          =   195
      Left            =   5520
      TabIndex        =   30
      Top             =   600
      Width           =   810
   End
   Begin VB.Label lblMiddleName 
      AutoSize        =   -1  'True
      Caption         =   "Middle Name:"
      Height          =   195
      Left            =   2760
      TabIndex        =   29
      Top             =   600
      Width           =   975
   End
   Begin VB.Label lblFirstName 
      AutoSize        =   -1  'True
      Caption         =   "First Name:"
      Height          =   195
      Left            =   240
      TabIndex        =   28
      Top             =   600
      Width           =   795
   End
End
Attribute VB_Name = "frmCustomers"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'*--------------------------------------------------------------------------
' Copyright (c) 1999  Microsoft Corporation.  All Rights Reserved.
'
' THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
' ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
' THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
' PARTICULAR PURPOSE.
'file://frmCustomers.frm--------------------------------------------------------------------------
 
Dim Customer_Position As Integer ' Used to keep position in the XML tree

Sub Get_Customer(index As Integer)

    '-----------------------------------------------------------------------
    ' This function pulls out all the customer information from the XML file
    ' and puts the info in the customer form
    '-----------------------------------------------------------------------
    
    If customers.xml <> "" Then
    
        txtCompanyName.Text = customers.documentElement.childNodes(0).childNodes(index).childNodes.Item(0).Text
        txtFirstName.Text = customers.documentElement.childNodes(0).childNodes(index).childNodes.Item(1).Text
        txtMiddleName.Text = customers.documentElement.childNodes(0).childNodes(index).childNodes.Item(2).Text
        txtLastName.Text = customers.documentElement.childNodes(0).childNodes(index).childNodes.Item(3).Text
        txtAddress1.Text = customers.documentElement.childNodes(0).childNodes(index).childNodes.Item(4).Text
        txtAddress2.Text = customers.documentElement.childNodes(0).childNodes(index).childNodes.Item(5).Text
        txtCity.Text = customers.documentElement.childNodes(0).childNodes(index).childNodes.Item(6).Text
        txtState.Text = customers.documentElement.childNodes(0).childNodes(index).childNodes.Item(7).Text
        txtZip.Text = customers.documentElement.childNodes(0).childNodes(index).childNodes.Item(8).Text
        txtHomePhone.Text = customers.documentElement.childNodes(0).childNodes(index).childNodes.Item(9).Text
        txtWorkPhone.Text = customers.documentElement.childNodes(0).childNodes(index).childNodes.Item(10).Text
        txtMethod.Text = customers.documentElement.childNodes(0).childNodes(index).childNodes.Item(11).Text
        txtCCExp.Text = customers.documentElement.childNodes(0).childNodes(index).childNodes.Item(12).Text
        txtCCNumber.Text = customers.documentElement.childNodes(0).childNodes(index).childNodes.Item(13).Text
        txtShipAddress1.Text = customers.documentElement.childNodes(0).childNodes(index).childNodes.Item(14).Text
        txtShipAddress2.Text = customers.documentElement.childNodes(0).childNodes(index).childNodes.Item(15).Text
        txtShipCity.Text = customers.documentElement.childNodes(0).childNodes(index).childNodes.Item(16).Text
        txtShipState.Text = customers.documentElement.childNodes(0).childNodes(index).childNodes.Item(17).Text
        txtShipZip.Text = customers.documentElement.childNodes(0).childNodes(index).childNodes.Item(18).Text
        
        lblCustID.Caption = "Customer ID:" & customers.documentElement.childNodes(0).childNodes(index).Attributes(0).Text
    Else
        cmdNext.Enabled = False
        cmdPrevious.Enabled = False
        cmdEnd.Enabled = False
        cmdFirst.Enabled = False
        cmdEdit.Enabled = False
        cmdDelete.Enabled = False
        
        ' setup customer form to add a new customer since no customers exist
        cmdSave.Enabled = True
        cmdAdd.Caption = "&Cancel"
    End If
    
End Sub

Private Sub cmdAdd_Click()

    ' ----------------------------------
    ' Add a new customer to the XML file
    ' ----------------------------------
    
    ' Setup the form to add a new customer
    
    If cmdAdd.Caption = "&Add" Then
        cmdSave.Enabled = True
        cmdDelete.Enabled = False
        cmdEdit.Enabled = False
        cmdFirst.Enabled = False
        cmdNext.Enabled = False
        cmdEnd.Enabled = False
        cmdPrevious.Enabled = False
        cmdAdd.Caption = "&Cancel"
        
        txtCompanyName.Text = ""
        txtFirstName.Text = ""
        txtMiddleName.Text = ""
        txtLastName.Text = ""
        txtAddress1.Text = ""
        txtAddress2.Text = ""
        txtCity.Text = ""
        txtState.Text = ""
        txtZip.Text = ""
        txtHomePhone.Text = ""
        txtWorkPhone.Text = ""
        txtMethod.Text = ""
        txtCCExp.Text = ""
        txtCCNumber.Text = ""
        txtShipAddress1.Text = ""
        txtShipAddress2.Text = ""
        txtShipCity.Text = ""
        txtShipState.Text = ""
        txtShipZip.Text = ""
        lblCustID.Caption = "Customer ID:"
        
        txtCompanyName.SetFocus
        
    Else ' If cancel was hit then reset the form
        cmdSave.Enabled = False
        cmdDelete.Enabled = True
        cmdEdit.Enabled = True
        cmdFirst.Enabled = True
        cmdNext.Enabled = True
        cmdEnd.Enabled = True
        cmdPrevious.Enabled = True
        cmdAdd.Caption = "&Add"
        
        Call Get_Customer(Customer_Position) ' reset the customer form to the last customer that was viewed
        
    End If
End Sub

Private Sub cmdDelete_Click()

    '----------------------------
    ' Delete the current customer
    '----------------------------
    
    Dim Tree1 As IXMLDOMNode
    Dim Tree2 As IXMLDOMNode
    Dim Query_Result As IXMLDOMNodeList
    Dim nodelist As IXMLDOMNode
    
    If Order_Form_hWnd <> 0 Then
        MsgBox "Cannot delete a customer when the order form is open."
        
        Exit Sub
    End If
    
    If MsgBox("Are you sure that you want to delete this customer?", vbYesNo) = vbYes Then
    
        ' NOTE: I do not delete the existing orders for a customer.  If a customer has open
        ' orders then you should not be able to delete the customer.  Not needed for this demo.

        '----------------------------------------
        ' Find customer in XML file and delete it
        '----------------------------------------
        
        Set Tree1 = customers.documentElement.childNodes(0)

        Set Query_Result = Tree1.selectNodes("//customer[@ID = '" + Mid(lblCustID.Caption, 13, Len(lblCustID.Caption)) + "']")

        ' go through the entire nodelist and delete customer

        For Each nodelist In Query_Result
        
            Set Tree2 = customers.documentElement.childNodes(0).removeChild(nodelist)
            
        Next

        Call Save_XML_File(Customers_Path, customers) ' Save new customer file
        
        Customer_Position = 0 ' set which customer to start the customer viewer on
    
        Call Get_Customer(Customer_Position) ' reset customer viewer
    
    End If
    
End Sub

Private Sub cmdEnd_Click()
    
    '--------------------------------------
    ' Move to the last customer in the tree
    '--------------------------------------
    
    Customer_Position = (customers.documentElement.childNodes(0).childNodes.length - 1) ' set which customer to start the customer viewer on
    
    Call Get_Customer(Customer_Position)

End Sub

Private Sub cmdExit_Click()

    Unload frmCustomers ' unload customer form from memory
    
End Sub

Private Sub cmdFirst_Click()

    '--------------------------------------
    ' Go to the first record in the tree
    '--------------------------------------

    Customer_Position = 0 ' set which customer to start the customer viewer on
    
    Call Get_Customer(Customer_Position)

End Sub

Private Sub cmdNext_Click()
    
    '--------------------------------------
    ' Go to the next customer in the tree
    '--------------------------------------
    
    If (customers.documentElement.childNodes(0).childNodes.length - 1) > Customer_Position Then
    
        Customer_Position = Customer_Position + 1 ' set which customer to start the customer viewer on
    
        Call Get_Customer(Customer_Position)

    End If
    
End Sub

Private Sub cmdPrevious_Click()

    '----------------------------------------
    ' Go to the previous customer in the tree
    '----------------------------------------
    
    If Customer_Position > 0 Then
        Customer_Position = Customer_Position - 1 ' set which customer to start the customer viewer on
    
        Call Get_Customer(Customer_Position)
    End If
    
End Sub

Private Sub cmdSave_Click()

    '---------------------------
    ' Save the new customer info
    '---------------------------
    
    Dim New_Cust_Id As String
    Dim Tree1 As IXMLDOMNode
    Dim Query_Result As IXMLDOMNode
    Dim Query_Result2 As IXMLDOMNodeList
    Dim ID_Counter As Integer
    Dim New_Id As Boolean
    Dim Tree3 As IXMLDOMNode
    Dim Tree4 As IXMLDOMNode
    Dim new_sub_tree As New DOMDocument
    Dim Tree2 As IXMLDOMNode
    Dim Tree5 As IXMLDOMNode

    ' --------------------------------------------------
    ' Do some very basic validation on the customer info
    ' --------------------------------------------------
    
    If txtFirstName.Text = "" Then
        MsgBox "Please enter a first name."
        txtFirstName.SetFocus
        Exit Sub
    ElseIf txtLastName.Text = "" Then
        MsgBox "Please enter a last name."
        txtLastName.SetFocus
        Exit Sub
    ElseIf txtAddress1.Text = "" Then
        MsgBox "Please enter a address."
        txtAddress1.SetFocus
        Exit Sub
    ElseIf txtCity.Text = "" Then
        MsgBox "Please enter a city."
        txtCity.SetFocus
        Exit Sub
    ElseIf txtState.Text = "" Then
        MsgBox "Please enter a state."
        txtState.SetFocus
        Exit Sub
    ElseIf txtZip.Text = "" Then
        MsgBox "Please enter a zip code."
        txtZip.SetFocus
        Exit Sub
    ElseIf (txtHomePhone.Text = "" And txtWorkPhone.Text = "") Then
        MsgBox "Please enter a phone number."
        txtHomePhone.SetFocus
        Exit Sub
    ElseIf txtMethod.Text = "" Then
        MsgBox "Please enter a method of payment."
        txtMethod.SetFocus
        Exit Sub
    ElseIf txtCCExp.Text = "" Then
        MsgBox "Please enter a credit card exper date."
        txtCCExp.SetFocus
        Exit Sub
    ElseIf txtCCNumber.Text = "" Then
        MsgBox "Please enter a credit card number."
        txtCCNumber.SetFocus
        Exit Sub
    ElseIf txtShipAddress1.Text = "" Then
        If (MsgBox("Do you want to ship to the billing address?", vbYesNo) = vbYes) Then
            txtShipAddress1.Text = txtAddress1.Text
            txtShipAddress2.Text = txtAddress2.Text
            txtShipCity.Text = txtCity.Text
            txtShipState.Text = txtState.Text
            txtShipZip.Text = txtZip.Text
        Else
            txtShipAddress1.SetFocus
            Exit Sub
        End If
        
    End If
    
    '-------------------------------------------------------------------------------------
    ' If editing existing customer or deleting a customer then delete the old record first
    '-------------------------------------------------------------------------------------
    
    If cmdEdit.Caption = "&Cancel" Then
    
        Set Tree1 = customers.documentElement.childNodes(0)
 
        Set Query_Result2 = Tree1.selectNodes("//customer[@ID = '" + Mid(lblCustID.Caption, 13, Len(lblCustID.Caption)) + "']")

        ' go through the entire nodelist and delete customer nodes

        For Each Tree5 In Query_Result2
        
            Set Tree2 = customers.documentElement.childNodes(0).removeChild(Tree5)
            
        Next
    
        New_Cust_Id = Mid(lblCustID.Caption, 13, Len(lblCustID.Caption)) ' reset the original customer ID
        
    Else ' adding new customer so make new customer ID
        
        '-----------------------
        ' Find a new Customer ID
        '-----------------------
        
        On Error Resume Next
         
        ID_Counter = 1 ' Init ID counter
        
        New_Cust_Id = UCase(Left(txtFirstName.Text, 1) & Left(txtLastName.Text, 1) & ID_Counter)
        
        Set Tree1 = customers.documentElement
    
        While New_Id = False
                
            Set Query_Result = Tree1.selectSingleNode("//@ID[value() $ieq$ '" + New_Cust_Id + "']")
    
            ' If customer Id is found then increment ID number and search again.
            
            If Query_Result.Text = "" Then
                If Err <> 0 Then
                    New_Id = True
                End If
            Else
                ID_Counter = ID_Counter + 1
                
                New_Cust_Id = Left(txtFirstName.Text, 1) & Left(txtLastName.Text, 1) & ID_Counter
                Err = 0 ' resest error number to catch it again in the loop
            End If
        Wend
        
        lblCustID.Caption = "Customer ID:" & New_Cust_Id ' Display the new Cust ID
        
        On Error GoTo 0
    
    End If
    
    '-------------------
    ' Start Save Routine
    '-------------------
    
    If customers.xml = "" Then ' create new customers file if it does not exist
        customers.loadXML ("<root><customers></customers></root>")
    End If
    
    ' Make new "customer" node

    new_sub_tree.loadXML ("<new_customer><customer></customer></new_customer>")
    
    ' Create Attribute for Customer ID
    
    Set Tree3 = new_sub_tree.createAttribute("ID")
    Tree3.Text = New_Cust_Id
    Set Tree4 = new_sub_tree.documentElement.lastChild.Attributes.setNamedItem(Tree3)
    
    ' Create Attribute for Customer Index
    
    Set Tree3 = new_sub_tree.createAttribute("Index")
    Tree3.Text = Mid(New_Cust_Id, 3, Len(New_Cust_Id))
    Set Tree4 = new_sub_tree.documentElement.lastChild.Attributes.setNamedItem(Tree3)
    
    ' Make a new "company_name" node under the "customer" node

    Set Tree3 = new_sub_tree.createElement("company_name")
    Tree3.Text = txtCompanyName.Text
    Set Tree4 = new_sub_tree.documentElement.lastChild.appendChild(Tree3)

    ' Make a new "first-name" node under the "customer" node

    Set Tree3 = new_sub_tree.createElement("first-name")
    Tree3.Text = txtFirstName.Text
    Set Tree4 = new_sub_tree.documentElement.lastChild.appendChild(Tree3)

    ' Make a new "middle-name" node under the "customer" node

    Set Tree3 = new_sub_tree.createElement("middle-name")
    Tree3.Text = txtMiddleName.Text
    Set Tree4 = new_sub_tree.documentElement.lastChild.appendChild(Tree3)
    
    ' Make a new "last-name" node under the "customer" node

    Set Tree3 = new_sub_tree.createElement("last-name")
    Tree3.Text = txtLastName.Text
    Set Tree4 = new_sub_tree.documentElement.lastChild.appendChild(Tree3)
    
    ' Make a new "address_1" node under the "customer" node

    Set Tree3 = new_sub_tree.createElement("address_1")
    Tree3.Text = txtAddress1.Text
    Set Tree4 = new_sub_tree.documentElement.lastChild.appendChild(Tree3)
    
    ' Make a new "address_2" node under the "customer" node

    Set Tree3 = new_sub_tree.createElement("address_2")
    Tree3.Text = txtAddress2.Text
    Set Tree4 = new_sub_tree.documentElement.lastChild.appendChild(Tree3)
    
    ' Make a new "city" node under the "customer" node

    Set Tree3 = new_sub_tree.createElement("city")
    Tree3.Text = txtCity.Text
    Set Tree4 = new_sub_tree.documentElement.lastChild.appendChild(Tree3)
    
    ' Make a new "state" node under the "customer" node

    Set Tree3 = new_sub_tree.createElement("state")
    Tree3.Text = txtState.Text
    Set Tree4 = new_sub_tree.documentElement.lastChild.appendChild(Tree3)
    
    ' Make a new "zip" node under the "customer" node

    Set Tree3 = new_sub_tree.createElement("zip")
    Tree3.Text = txtZip.Text
    Set Tree4 = new_sub_tree.documentElement.lastChild.appendChild(Tree3)
    
    ' Make a new "home_phone" node under the "customer" node

    Set Tree3 = new_sub_tree.createElement("home_phone")
    Tree3.Text = txtHomePhone.Text
    Set Tree4 = new_sub_tree.documentElement.lastChild.appendChild(Tree3)
    
    ' Make a new "work_phone" node under the "customer" node

    Set Tree3 = new_sub_tree.createElement("work_phone")
    Tree3.Text = txtWorkPhone.Text
    Set Tree4 = new_sub_tree.documentElement.lastChild.appendChild(Tree3)
    
    ' Make a new "method_of_payment" node under the "customer" node

    Set Tree3 = new_sub_tree.createElement("method_of_payment")
    Tree3.Text = txtMethod.Text
    Set Tree4 = new_sub_tree.documentElement.lastChild.appendChild(Tree3)
    
    ' Make a new "cc_exp" node under the "customer" node

    Set Tree3 = new_sub_tree.createElement("cc_exp")
    Tree3.Text = txtCCExp.Text
    Set Tree4 = new_sub_tree.documentElement.lastChild.appendChild(Tree3)
    
    ' Make a new "cc_num" node under the "customer" node

    Set Tree3 = new_sub_tree.createElement("cc_num")
    Tree3.Text = txtCCNumber.Text
    Set Tree4 = new_sub_tree.documentElement.lastChild.appendChild(Tree3)
    
    ' Make a new "ship_address_1" node under the "customer" node

    Set Tree3 = new_sub_tree.createElement("ship_address_1")
    Tree3.Text = txtShipAddress1.Text
    Set Tree4 = new_sub_tree.documentElement.lastChild.appendChild(Tree3)
    
    ' Make a new "ship_address_2" node under the "customer" node

    Set Tree3 = new_sub_tree.createElement("ship_address_2")
    Tree3.Text = txtShipAddress2.Text
    Set Tree4 = new_sub_tree.documentElement.lastChild.appendChild(Tree3)
    
    ' Make a new "ship_city" node under the "customer" node

    Set Tree3 = new_sub_tree.createElement("ship_city")
    Tree3.Text = txtShipCity.Text
    Set Tree4 = new_sub_tree.documentElement.lastChild.appendChild(Tree3)
    
    ' Make a new "ship_state" node under the "customer" node

    Set Tree3 = new_sub_tree.createElement("ship_state")
    Tree3.Text = txtShipState.Text
    Set Tree4 = new_sub_tree.documentElement.lastChild.appendChild(Tree3)
    
    ' Make a new "ship_zip" node under the "customer" node

    Set Tree3 = new_sub_tree.createElement("ship_zip")
    Tree3.Text = txtShipZip.Text
    Set Tree4 = new_sub_tree.documentElement.lastChild.appendChild(Tree3)

    ' append new Item "tree" to the existing customer tree
    
    Set Tree4 = new_sub_tree.documentElement.childNodes(0)
    Set Tree4 = customers.documentElement.lastChild.appendChild(Tree4)
 
    Call Save_XML_File(Customers_Path, customers) ' Save new customer file
    
    ' Reset form buttons
    
    cmdSave.Enabled = False
    cmdDelete.Enabled = True
    cmdAdd.Enabled = True
    cmdEdit.Enabled = True
    cmdFirst.Enabled = True
    cmdNext.Enabled = True
    cmdEnd.Enabled = True
    cmdPrevious.Enabled = True
    cmdEdit.Caption = "E&dit"
    cmdAdd.Caption = "&Add"

End Sub

Private Sub Form_Load()

    Customer_Form_hWnd = frmCustomers.hWnd ' Used to tell when the Customer form is open
    
    Customer_Position = Customer_Index ' set which customer to start the customer viewer on
    
    Call Get_Customer(Customer_Position)
    
End Sub

Private Sub cmdEdit_Click()
    
    '---------------------------
    ' Edit the existing customer
    '---------------------------
    
    If cmdEdit.Caption = "E&dit" Then
        cmdSave.Enabled = True
        cmdDelete.Enabled = False
        cmdAdd.Enabled = False
        cmdFirst.Enabled = False
        cmdNext.Enabled = False
        cmdEnd.Enabled = False
        cmdPrevious.Enabled = False
        cmdEdit.Caption = "&Cancel"
        
        txtCompanyName.SetFocus
        
    Else ' If cancel was hit then reset the customer form
        cmdSave.Enabled = False
        cmdDelete.Enabled = True
        cmdAdd.Enabled = True
        cmdFirst.Enabled = True
        cmdNext.Enabled = True
        cmdEnd.Enabled = True
        cmdPrevious.Enabled = True
        cmdEdit.Caption = "E&dit"
        
        Call Get_Customer(Customer_Position)
        
    End If
    
End Sub

Private Sub Form_Unload(Cancel As Integer)
    Customer_Form_hWnd = 0
End Sub

Private Sub txtAddress1_GotFocus()
    '-----------------------------------------------
    ' When entering the text box select all the text
    '-----------------------------------------------
    txtAddress1.SelStart = 0
    txtAddress1.SelLength = Len(txtAddress1)
End Sub

Private Sub txtAddress2_GotFocus()
    '-----------------------------------------------
    ' When entering the text box select all the text
    '-----------------------------------------------
    txtAddress2.SelStart = 0
    txtAddress2.SelLength = Len(txtAddress2)
End Sub

Private Sub txtCCExp_GotFocus()
    '-----------------------------------------------
    ' When entering the text box select all the text
    '-----------------------------------------------
    txtCCExp.SelStart = 0
    txtCCExp.SelLength = Len(txtCCExp)
End Sub

Private Sub txtCCNumber_GotFocus()
    '-----------------------------------------------
    ' When entering the text box select all the text
    '-----------------------------------------------
    txtCCNumber.SelStart = 0
    txtCCNumber.SelLength = Len(txtCCNumber)
End Sub

Private Sub txtCity_GotFocus()
    '-----------------------------------------------
    ' When entering the text box select all the text
    '-----------------------------------------------
    txtCity.SelStart = 0
    txtCity.SelLength = Len(txtCity)
End Sub

Private Sub txtCompanyName_GotFocus()
    '-----------------------------------------------
    ' When entering the text box select all the text
    '-----------------------------------------------
    txtCompanyName.SelStart = 0
    txtCompanyName.SelLength = Len(txtCompanyName)
End Sub

Private Sub txtFirstName_GotFocus()
    '-----------------------------------------------
    ' When entering the text box select all the text
    '-----------------------------------------------
    txtFirstName.SelStart = 0
    txtFirstName.SelLength = Len(txtFirstName)
End Sub

Private Sub txtHomePhone_GotFocus()
    '-----------------------------------------------
    ' When entering the text box select all the text
    '-----------------------------------------------
    txtHomePhone.SelStart = 0
    txtHomePhone.SelLength = Len(txtHomePhone)
End Sub

Private Sub txtLastName_GotFocus()
    '-----------------------------------------------
    ' When entering the text box select all the text
    '-----------------------------------------------
    txtLastName.SelStart = 0
    txtLastName.SelLength = Len(txtLastName)
End Sub

Private Sub txtMethod_GotFocus()
    '-----------------------------------------------
    ' When entering the text box select all the text
    '-----------------------------------------------
    txtMethod.SelStart = 0
    txtMethod.SelLength = Len(txtMethod)
End Sub

Private Sub txtMiddleName_GotFocus()
    '-----------------------------------------------
    ' When entering the text box select all the text
    '-----------------------------------------------
    txtMiddleName.SelStart = 0
    txtMiddleName.SelLength = Len(txtMiddleName)
End Sub

Private Sub txtShipAddress1_GotFocus()
    '-----------------------------------------------
    ' When entering the text box select all the text
    '-----------------------------------------------
    txtShipAddress1.SelStart = 0
    txtShipAddress1.SelLength = Len(txtShipAddress1)
End Sub

Private Sub txtShipAddress2_GotFocus()
    '-----------------------------------------------
    ' When entering the text box select all the text
    '-----------------------------------------------
    txtShipAddress2.SelStart = 0
    txtShipAddress2.SelLength = Len(txtShipAddress2)
End Sub

Private Sub txtShipCity_GotFocus()
    '-----------------------------------------------
    ' When entering the text box select all the text
    '-----------------------------------------------
    txtShipCity.SelStart = 0
    txtShipCity.SelLength = Len(txtShipCity)
End Sub

Private Sub txtShipState_GotFocus()
    '-----------------------------------------------
    ' When entering the text box select all the text
    '-----------------------------------------------
    txtShipState.SelStart = 0
    txtShipState.SelLength = Len(txtShipState)
End Sub

Private Sub txtShipZip_GotFocus()
    '-----------------------------------------------
    ' When entering the text box select all the text
    '-----------------------------------------------
    txtShipZip.SelStart = 0
    txtShipZip.SelLength = Len(txtShipZip)
End Sub

Private Sub txtState_GotFocus()
    '-----------------------------------------------
    ' When entering the text box select all the text
    '-----------------------------------------------
    txtState.SelStart = 0
    txtState.SelLength = Len(txtState)
End Sub

Private Sub txtWorkPhone_GotFocus()
    '-----------------------------------------------
    ' When entering the text box select all the text
    '-----------------------------------------------
    txtWorkPhone.SelStart = 0
    txtWorkPhone.SelLength = Len(txtWorkPhone)
End Sub

Private Sub txtZip_GotFocus()
    '-----------------------------------------------
    ' When entering the text box select all the text
    '-----------------------------------------------
    txtZip.SelStart = 0
    txtZip.SelLength = Len(txtZip)
End Sub
