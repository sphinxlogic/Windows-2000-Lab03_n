VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{5E9E78A0-531B-11CF-91F6-C2863C385E30}#1.0#0"; "MSFLXGRD.OCX"
Begin VB.Form frmOrder 
   Caption         =   "XML Order Form"
   ClientHeight    =   8595
   ClientLeft      =   165
   ClientTop       =   450
   ClientWidth     =   11880
   Icon            =   "XML_Order.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MDIChild        =   -1  'True
   ScaleHeight     =   8595
   ScaleWidth      =   11880
   Begin VB.CommandButton cmdCust 
      Caption         =   "&View Customer"
      Height          =   375
      Left            =   6480
      TabIndex        =   2
      Top             =   120
      Width           =   1335
   End
   Begin VB.Frame frHistory 
      Height          =   4695
      Left            =   120
      TabIndex        =   24
      Top             =   3840
      Visible         =   0   'False
      Width           =   8895
      Begin MSFlexGridLib.MSFlexGrid OrderHistoryGrid 
         Height          =   3135
         Left            =   240
         TabIndex        =   15
         Top             =   1440
         Width           =   8295
         _ExtentX        =   14631
         _ExtentY        =   5530
         _Version        =   393216
         Cols            =   7
      End
      Begin VB.ListBox lstOrders 
         Height          =   840
         Left            =   2640
         Sorted          =   -1  'True
         TabIndex        =   12
         Top             =   240
         Width           =   1335
      End
      Begin VB.CommandButton cmdEdit 
         Caption         =   "Edit &Order"
         Height          =   375
         Left            =   4200
         TabIndex        =   13
         Top             =   240
         Width           =   1455
      End
      Begin VB.CommandButton cmdDeleteOrder 
         Cancel          =   -1  'True
         Caption         =   "&Delete Order"
         Height          =   375
         Left            =   4200
         TabIndex        =   14
         Top             =   720
         Width           =   1455
      End
      Begin VB.Label lblOrder 
         AutoSize        =   -1  'True
         Caption         =   "Select a order number for details:"
         Height          =   195
         Left            =   240
         TabIndex        =   30
         Top             =   240
         Width           =   2325
      End
   End
   Begin VB.Frame frNewOrder 
      Height          =   4815
      Left            =   240
      TabIndex        =   19
      Top             =   1440
      Width           =   8895
      Begin VB.CommandButton cmdCancel 
         Caption         =   "&Cancel"
         Height          =   375
         Left            =   7440
         TabIndex        =   10
         Top             =   1560
         Width           =   1215
      End
      Begin VB.CommandButton cmdSave 
         Caption         =   "&Save Order"
         Height          =   375
         Left            =   6000
         TabIndex        =   9
         Top             =   1560
         Width           =   1215
      End
      Begin MSFlexGridLib.MSFlexGrid OrderGrid 
         Height          =   2655
         Left            =   120
         TabIndex        =   11
         Top             =   2040
         Width           =   8655
         _ExtentX        =   15266
         _ExtentY        =   4683
         _Version        =   393216
         Cols            =   7
         WordWrap        =   -1  'True
         SelectionMode   =   1
         AllowUserResizing=   1
      End
      Begin VB.TextBox txtQty 
         Height          =   285
         Left            =   3480
         TabIndex        =   7
         Text            =   "1"
         Top             =   1560
         Width           =   855
      End
      Begin VB.CommandButton cmdAdd 
         Caption         =   "&Add To Order"
         Height          =   375
         Left            =   4560
         TabIndex        =   8
         Top             =   1560
         Width           =   1215
      End
      Begin VB.TextBox txtDescription 
         Height          =   285
         Left            =   1440
         TabIndex        =   5
         Top             =   1080
         Width           =   7215
      End
      Begin VB.ComboBox cmbProducts 
         Height          =   315
         ItemData        =   "XML_Order.frx":014A
         Left            =   1440
         List            =   "XML_Order.frx":0157
         Sorted          =   -1  'True
         Style           =   2  'Dropdown List
         TabIndex        =   4
         Top             =   600
         Width           =   7215
      End
      Begin VB.TextBox txtPrice 
         Height          =   285
         Left            =   1440
         TabIndex        =   6
         Top             =   1560
         Width           =   1095
      End
      Begin VB.Label lblTotal 
         AutoSize        =   -1  'True
         Caption         =   "Order Total = $0.00"
         Height          =   195
         Left            =   2400
         TabIndex        =   29
         Top             =   240
         Width           =   1380
      End
      Begin VB.Label lblQty 
         AutoSize        =   -1  'True
         Caption         =   "Qty:"
         Height          =   195
         Left            =   3000
         TabIndex        =   28
         Top             =   1560
         Width           =   285
      End
      Begin VB.Label lblDescription 
         AutoSize        =   -1  'True
         Caption         =   "Description:"
         Height          =   195
         Left            =   360
         TabIndex        =   27
         Top             =   1080
         Width           =   840
      End
      Begin VB.Label lblProducts 
         AutoSize        =   -1  'True
         Caption         =   "Products:"
         Height          =   195
         Left            =   480
         TabIndex        =   26
         Top             =   600
         Width           =   675
      End
      Begin VB.Label lblPrice 
         AutoSize        =   -1  'True
         Caption         =   "Price:"
         Height          =   195
         Left            =   720
         TabIndex        =   25
         Top             =   1560
         Width           =   405
      End
      Begin VB.Label lblActualOrderDate 
         AutoSize        =   -1  'True
         Caption         =   "01/04/99"
         Height          =   195
         Left            =   7920
         TabIndex        =   23
         Top             =   240
         Width           =   690
      End
      Begin VB.Label lblOrderDate 
         AutoSize        =   -1  'True
         Caption         =   "Order Date:"
         Height          =   195
         Left            =   6960
         TabIndex        =   22
         Top             =   240
         Width           =   825
      End
      Begin VB.Label lblActualOrderNumber 
         AutoSize        =   -1  'True
         Caption         =   "1"
         Height          =   195
         Left            =   1440
         TabIndex        =   21
         Top             =   240
         Width           =   90
      End
      Begin VB.Label lblOrderNumber 
         AutoSize        =   -1  'True
         Caption         =   "Order Number:"
         Height          =   195
         Left            =   120
         TabIndex        =   20
         Top             =   240
         Width           =   1035
      End
   End
   Begin MSComctlLib.TabStrip TabStrip1 
      Height          =   5295
      Left            =   120
      TabIndex        =   18
      Top             =   1080
      Width           =   9135
      _ExtentX        =   16113
      _ExtentY        =   9340
      Separators      =   -1  'True
      _Version        =   393216
      BeginProperty Tabs {1EFB6598-857C-11D1-B16A-00C0F0283628} 
         NumTabs         =   2
         BeginProperty Tab1 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
            Caption         =   "New Order:"
            ImageVarType    =   2
         EndProperty
         BeginProperty Tab2 {1EFB659A-857C-11D1-B16A-00C0F0283628} 
            Caption         =   "Order History:"
            ImageVarType    =   2
         EndProperty
      EndProperty
   End
   Begin VB.CommandButton cmdExit 
      Caption         =   "&Exit"
      Height          =   375
      Left            =   7920
      TabIndex        =   3
      Top             =   120
      Width           =   1335
   End
   Begin VB.ComboBox cmbCustomer 
      Height          =   315
      Left            =   1440
      TabIndex        =   1
      Text            =   "Select A Customer"
      Top             =   120
      Width           =   4935
   End
   Begin VB.Label lblTotalOrders 
      AutoSize        =   -1  'True
      Caption         =   "Total Orders To Date:"
      Height          =   195
      Left            =   4440
      TabIndex        =   17
      Top             =   600
      Width           =   1545
   End
   Begin VB.Label lblCustID 
      AutoSize        =   -1  'True
      Caption         =   "Customer ID:"
      Height          =   195
      Left            =   120
      TabIndex        =   16
      Top             =   600
      Width           =   915
   End
   Begin VB.Label lblCustName 
      AutoSize        =   -1  'True
      Caption         =   "Customer Name:"
      Height          =   195
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   1170
   End
End
Attribute VB_Name = "frmOrder"
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
'file://XML_Order.frm--------------------------------------------------------------------------
 
 
Private mintCurFrame As Integer ' Keeps track of which current frame is visible

Private Sub cmbCustomer_Click()
    
    '--------------------------------------------------------------
    ' Look up a customer order info when a new customer is selected
    ' from the drop down list box.
    '--------------------------------------------------------------
    
    Dim Find_ID As Integer
    Dim Cust_ID As String
    Dim Query_Result As IXMLDOMNodeList
    Dim Query_String As String
    Dim Order_Count As Double
    
    ' Pull out the customer ID from name in drop down list box
    
    Find_ID = InStr(cmbCustomer.Text, "=")
    
    If cmbCustomer.Text <> "Select a customer" Then
      lblCustID.Caption = "Customer ID: " & Mid(cmbCustomer.Text, (Find_ID + 2), Len(cmbCustomer.Text))
    Else
      lblCustID.Caption = "Customer ID: "
    End If
    
    Cust_ID = Mid(cmbCustomer.Text, (Find_ID + 2), Len(cmbCustomer.Text))
          
    Order_Count = 0 ' Init order count variable
    
    If cmbCustomer.Text <> "Select a customer" Then
       
        '-------------------------------------------
        ' Find all orders from the selected customer
        '-------------------------------------------
        
        ' Two query strings that do the same thing.  Used for example purpose
        
        'Query_String = "//Order_Number[..//Cust_ID[value() = '" & Cust_ID & "']]"
        Query_String = "//Order_Number[ancestor(Orders)/Cust_ID[value() = '" & Cust_ID & "']]"
           
        ' Run query
        Set Query_Result = doc.documentElement.selectNodes(Query_String)
        
        ' go through the entire nodelist and count orders and list existing orders

        lstOrders.Clear ' empty list box before adding new orders
          
        For Each nodelist In Query_Result
  
          If Order_Count = 0 Then
              lstOrders.AddItem (Query_Result.Item(0).Text)
          Else
              lstOrders.AddItem (Query_Result.Item(Order_Count).Text)
          End If
          Order_Count = Order_Count + 1
      
        Next
    End If
              
    ' Display total orders and clear OrderHistoryGrid
    
    lblTotalOrders.Caption = "Total Orders To Date: " & Order_Count

    OrderHistoryGrid.Rows = 2
    OrderHistoryGrid.Row = 1
    OrderHistoryGrid.Col = 0
    OrderHistoryGrid.Text = ""
    OrderHistoryGrid.Col = 1
    OrderHistoryGrid.Text = ""
    OrderHistoryGrid.Col = 2
    OrderHistoryGrid.Text = ""
    OrderHistoryGrid.Col = 3
    OrderHistoryGrid.Text = ""
    OrderHistoryGrid.Col = 4
    OrderHistoryGrid.Text = ""
    OrderHistoryGrid.Col = 5
    OrderHistoryGrid.Text = ""
    OrderHistoryGrid.Col = 6
    OrderHistoryGrid.Text = ""
       
End Sub

Private Sub cmbProducts_Click()
 
    ' Display product info when a product is selected from the product list
    
    Call Find_Product_Description

End Sub

Private Sub cmdAdd_Click()
    
    Dim intX As Integer
    Dim Total_Cost As Double
    
    ' Fix price from any number numbers or exponent notation
    
    txtPrice.Text = Format(txtPrice.Text, "0.00")
    
    If CDbl(txtPrice.Text) < 0 Then
        txtPrice.Text = CDbl(txtPrice.Text) * -1
    End If
    
    If txtDescription = "" Then
        MsgBox "Please select a product before adding item to the order."
        cmbProducts.SetFocus
        Exit Sub
    ElseIf (txtPrice = "") Or Not IsNumeric(txtPrice.Text) Then
        MsgBox "Please enter a valid price for the selected product."
        txtPrice.SetFocus
        Exit Sub
    ElseIf (txtQty = "") Or Not IsNumeric(txtQty.Text) Then
        MsgBox "Please enter a quanity of 1 or greater."
        txtQty.SetFocus
        Exit Sub
    End If
    
    ' Search for a duplicate product in the order.  If one is found then ask user
    ' if they want to add to the existing qty.  If there is no duplicate then
    ' add it to the order
    
    Call Search_For_Dup
    
    ' Update Total Order Cost
        
    Total_Cost = 0 ' Init Total_Cost variable
    
    OrderGrid.Col = 5 ' set order grid to the Total_Cost column
    
    For intX = 1 To (OrderGrid.Rows - 1)
        OrderGrid.Row = intX
        Total_Cost = Total_Cost + OrderGrid.Text
    Next
    
    lblTotal.Caption = "Order Total = $" & Format(Total_Cost, "0.00")
    
    txtDescription.Text = ""
    txtQty.Text = "1"
    txtPrice.Text = ""
    
End Sub

Private Sub cmdCancel_Click()

    '--------------------------------------------------
    ' Cancel the current order and reset the order form
    '--------------------------------------------------
    
    If Edit_Mode = True Then
      
      ' Reset the frames in the tab strip
      
      mintCurFrame = 2 ' select the order history tab
      
      frHistory.Top = 1440
      frHistory.Left = 240
      frHistory.Height = 4815
      frHistory.Width = 8895
      frNewOrder.Visible = False
      frHistory.Visible = True
    
    End If
      
    Call Reset_Form
    
    Edit_Mode = False
    
End Sub

Private Sub cmdCust_Click()
    
    '--------------------------------------------------------------------------------
    ' This will open the customer form.  The customer form will be set to the current
    ' customer that has been selected in the order form.
    '--------------------------------------------------------------------------------
    
    Dim Query_Result As IXMLDOMNode
    Dim Query_String As String
    Dim Cust_ID As String
    Dim Find_ID As Integer
    
    ' Find customer ID and query for the customers index number.  This is used to
    ' set the current customer in the customer form.
    ' BUGBUG: Need to add another index to the customer file to make this fully
    ' work.  Currently this will find the first customer with the index from the
    ' customer ID.  Example:  If you wanted the customer form to open with customer
    ' "BB1" it will not show customer "BB1" with the current code.  This is because
    ' customer one has a customer ID of "AA1" with a index of 1.  Customer two has
    ' a customer ID of "BB1" with index 1 also so the customer form will open with
    ' customer AA1 instead of BB1.
    
    Find_ID = InStr(cmbCustomer.Text, "=")
    
    Cust_ID = Mid(cmbCustomer.Text, (Find_ID + 2), Len(cmbCustomer.Text))
      
    Query_String = "root/customers/customer[@ID = '" & Cust_ID & "']/@Index"

    Set Query_Result = customers.selectSingleNode(Query_String)
    
    On Error Resume Next

    If (Query_Result.Text <> "") Then
        If Err = 0 Then
            Customer_Index = (Query_Result.Text - 1)
            Load frmCustomers
            frmCustomers.ZOrder (0) ' Place form on top
            frmCustomers.WindowState = 0 ' restore window incase it was min.
            frmCustomers.Height = 5445
            frmCustomers.Width = 8220
            frmCustomer.Show
        End If
    Else
        MsgBox "Customer not found."
    End If
    
    On Error GoTo 0
     
End Sub

Private Sub cmdDeleteOrder_Click()

    '--------------------------------
    ' Delete order if one is selected
    '--------------------------------
        
    If lstOrders.Text = "" Then
        MsgBox "Please select a order before deleting."
        Exit Sub
    ElseIf MsgBox("Are you sure that you want to delete this order?", vbYesNo) = vbYes Then
        Call Delete_Order
    End If
    
    Call cmbCustomer_Click   ' Clean up after deleting order
    
End Sub

Sub Delete_Order()

    '------------------------------------------------------------------------------------------
    ' Delete the order from the orders xml file.  This is called from cmdDeleteOrder_Click and
    ' form cmdSave_Click when a order is being edited
    '------------------------------------------------------------------------------------------
    
    Dim node1 As IXMLDOMNode
    Dim node2 As IXMLDOMNode
    Dim Query_Result As IXMLDOMNode
    Dim nodelist As IXMLDOMNode
        
    Set node1 = doc.documentElement.childNodes(0)
 
    Set Query_Result2 = doc.selectNodes("//Orders[Order_Number = '" + lstOrders.Text + "']")

    ' go through the entire nodelist and delete customer nodes

    For Each nodelist In Query_Result2
    
        Set node2 = doc.documentElement.removeChild(nodelist)
        
    Next
    
    Call Save_XML_File(Order_File, doc) ' Save file after deleting order
 
End Sub
Private Sub cmdEdit_Click()

    Dim intX As Integer
    Dim Line_Count As Integer
    Dim Total_Cost As Double
    
    Total_Cost = 0
    
    '--------------------------------
    ' Edit existing order
    '--------------------------------
    
    If lstOrders.Text = "" Then
        MsgBox "Please select a order before editing."
        Exit Sub
    End If
    
    '---------------------------------------------------------
    ' Add all items from order history grid to the order grid.
    ' Disable the History tab while editing existing order.
    ' If the edited order is canceled or saved then reset the
    ' entire order form.
    '---------------------------------------------------------
    
    Edit_Mode = True
    
    Line_Count = 0
    
    OrderGrid.Rows = OrderHistoryGrid.Rows ' set the order grid rows to the same amount
    
    For intX = 1 To (OrderHistoryGrid.Rows - 1)
        Line_Count = Line_Count + 1
        OrderGrid.Col = 0 ' Line Item
        OrderGrid.Row = Line_Count
        OrderGrid.CellAlignment = 4
        OrderGrid.Text = Line_Count
         
        OrderHistoryGrid.Col = 2 ' Part Description
        OrderGrid.Col = 2
        OrderGrid.Row = Line_Count
        OrderHistoryGrid.Row = Line_Count
        OrderGrid.CellAlignment = 1
        OrderGrid.Text = OrderHistoryGrid.Text
        
        OrderHistoryGrid.Col = 1 ' Part Number
        OrderGrid.Col = 1
        OrderGrid.CellAlignment = 1
        OrderGrid.Text = OrderHistoryGrid.Text
         
        OrderHistoryGrid.Col = 3 ' Price
        OrderGrid.Col = 3
        OrderGrid.CellAlignment = 1
        OrderGrid.Text = OrderHistoryGrid.Text
         
        OrderHistoryGrid.Col = 4 ' Qty
        OrderGrid.Col = 4
        OrderGrid.CellAlignment = 1
        OrderGrid.Text = OrderHistoryGrid.Text
         
        OrderHistoryGrid.Col = 5 ' Total Cost
        OrderGrid.Col = 5
        OrderGrid.CellAlignment = 1
        OrderGrid.Text = OrderHistoryGrid.Text
     
        Total_Cost = Total_Cost + (CDbl(Mid$(OrderHistoryGrid.Text, 1, Len(OrderHistoryGrid.Text))))
        
        OrderHistoryGrid.Col = 6 ' Product ID
        OrderGrid.Col = 6
        OrderGrid.CellAlignment = 1
        OrderGrid.Text = OrderHistoryGrid.Text
    Next
      
    mintCurFrame = 1 ' select the new order tab
    
    TabStrip1.SelectedItem.Selected = True

    lblTotal.Caption = "Order Total = $" & Format(Total_Cost, "0.00") ' Display the entire order total
    
    lblActualOrderNumber.Caption = lstOrders.Text ' Set Order Number
    
End Sub

Private Sub cmdExit_Click()

    '------------------------------------------
    ' Unload the order form from memory on exit
    '------------------------------------------
    
    frmOrder.Hide
    Unload frmOrder
End Sub

Private Sub cmdSave_Click()
    
    '-----------------------
    ' Save the current order
    '-----------------------
    
    Dim node1 As IXMLDOMNode
    Dim node2 As IXMLDOMNode
    Dim node3 As IXMLDOMNode
    Dim new_sub_tree As New DOMDocument
    Dim Find_ID As Integer
    
    ' Make sure that at least one item has been ordered and a customer has been selected
    
    If OrderGrid.Rows <= 2 Then
        OrderGrid.Col = 2
        OrderGrid.Row = 1
        If OrderGrid.Text = "" Then
            MsgBox "Please order at least one item before saving."
            Exit Sub
        End If
    End If
    
    If cmbCustomer.Text = "Select a customer" Then
        MsgBox "Please select a customer before saving the order."
        cmbCustomer.SetFocus
        Exit Sub
    End If
      
    ' Delete order first if order is being edited
    
    If Edit_Mode = True Then
        Call Delete_Order
    End If
    
    Find_ID = InStr(cmbCustomer.Text, "=")
  
    ' Make new "Orders" node

    Set node1 = doc.createElement("Orders")

    Set node2 = doc.documentElement.appendChild(node1)

    ' Make a new "Order_Number" node under the "Orders" node

    Set node1 = doc.createElement("Order_Number")

    node1.Text = lblActualOrderNumber.Caption

    Set node2 = doc.documentElement.lastChild.appendChild(node1)

    ' Make a new "Cust_ID" node under the "Orders" node

    Set node1 = doc.createElement("Cust_ID")

    node1.Text = Mid(cmbCustomer.Text, (Find_ID + 2), Len(cmbCustomer.Text))

    Set node2 = doc.documentElement.lastChild.appendChild(node1)

    ' create "Date" attribute
    
    Set node1 = doc.createAttribute("Date")
    
    node1.Text = Date
    
    Set node2 = doc.documentElement.lastChild.childNodes.Item(0).Attributes.setNamedItem(node1)
    
    ' create "Total_Cost" attribute
    
    Set node1 = doc.createAttribute("Total_Cost")
    
    node1.Text = Mid(lblTotal.Caption, InStr(lblTotal.Caption, "$") + 1, Len(lblTotal.Caption))
    
    Set node2 = doc.documentElement.lastChild.childNodes.Item(0).Attributes.setNamedItem(node1)
    
    ' Loop through all products that have been selected for ordering
    
    For intX = 1 To (OrderGrid.Rows - 1)
    
        ' Create new "Item" tree
        
        new_sub_tree.loadXML ("<Item></Item>")
         
        OrderGrid.Row = intX
        
        ' Make a new "ProductID" node under the "Orders" node
      
        OrderGrid.Col = 6 ' Part ID column
     
        Set node1 = new_sub_tree.createElement("ProductID")
    
        node1.Text = OrderGrid.Text
    
        Set node3 = new_sub_tree.documentElement.appendChild(node1)
    
        ' Add "Qty" for part order
        
        OrderGrid.Col = 4 ' Qty column
        
        Set node1 = new_sub_tree.createElement("Qty")
    
        node1.Text = OrderGrid.Text
    
        Set node2 = new_sub_tree.documentElement.appendChild(node1)
        
        ' Add "Price" for part order
        
        OrderGrid.Col = 3 ' Price column
         
        Set node1 = new_sub_tree.createElement("Price")
    
        node1.Text = OrderGrid.Text
    
        Set node2 = new_sub_tree.documentElement.appendChild(node1)
        
        Set node2 = new_sub_tree.documentElement
        
        ' append new Item "tree" to the existing order tree
        
        Set node2 = doc.documentElement.lastChild.appendChild(node2)
    Next
    
    ' Add any data types to attributes or nodes
        
    Set node2 = doc.documentElement.lastChild.childNodes.Item(0)
    
    node2.dataType = "int" ' set data type to integer on the "Order_Number" node
        
    Call Save_XML_File(Order_File, doc) ' Save order to XML file
    
    If Edit_Mode = True Then
      
      ' Reset the frames in the tab strip
      
      mintCurFrame = 2 ' select the order history tab
      
      frHistory.Top = 1440
      frHistory.Left = 240
      frHistory.Height = 4815
      frHistory.Width = 8895
      frNewOrder.Visible = False
      frHistory.Visible = True
    
    End If
    
    Edit_Mode = False ' reset the edit order flag
    
    Call Reset_Form ' Clean up the form after saving
       
End Sub

Private Sub Form_Load()

    Edit_Mode = False ' Not in edit mode
    
    Order_Form_hWnd = frmOrder.hWnd ' Used to keep track when the customer window is open
    
    frmOrder.MousePointer = 11 ' turn mouse pointer into hour glass
        
    doc.Load (Order_File) ' load orders.xml file
    
    If (doc.xml) = "" Then ' if orders.xml file does not exist then create a new one
    
        doc.loadXML ("<root xmlns:dt='uuid:C2F41010-65B3-11d1-A29F-00AA00C14882'></root>")
        
    End If
    
    lblActualOrderDate.Caption = Date ' Set Order date to current day
    
    Customer_Index = 0 ' Reset variable that keeps track of customer position.  Used for setting the customer on the customer form
    
    Call Fill_Customer_Select ' fill customer drop down list
    
    Call Fill_Product_Select ' fill drop down list box with product names
    
    Call Reset_Form ' Init order from
    
    ' Setup the Order grid
    
    OrderGrid.Row = 0
    OrderGrid.Col = 0
    OrderGrid.CellAlignment = 4
    OrderGrid.Col = 1
    OrderGrid.Text = "Part Number:"
    OrderGrid.CellAlignment = 1
    OrderGrid.ColWidth(1) = 1200
    OrderGrid.Col = 2
    OrderGrid.Text = "Description:"
    OrderGrid.CellAlignment = 1
    OrderGrid.ColWidth(2) = 4000
    OrderGrid.Col = 3
    OrderGrid.Text = "Price:"
    OrderGrid.ColWidth(3) = 1000
    OrderGrid.CellAlignment = 1
    OrderGrid.Col = 4
    OrderGrid.Text = "Qty:"
    OrderGrid.ColWidth(4) = 900
    OrderGrid.CellAlignment = 1
    OrderGrid.Col = 5
    OrderGrid.Text = "Total Cost:"
    OrderGrid.ColWidth(5) = 1300
    OrderGrid.CellAlignment = 1
    OrderGrid.Col = 6
    OrderGrid.Text = "ID:"
    OrderGrid.ColWidth(6) = 0
    OrderGrid.CellAlignment = 1
    
    ' Setup Order History Grid
    
    OrderHistoryGrid.Row = 0
    OrderHistoryGrid.Col = 0
    OrderHistoryGrid.CellAlignment = 4
    OrderHistoryGrid.Col = 1
    OrderHistoryGrid.Text = "Part Number:"
    OrderHistoryGrid.CellAlignment = 1
    OrderHistoryGrid.ColWidth(1) = 1200
    OrderHistoryGrid.Col = 2
    OrderHistoryGrid.Text = "Description:"
    OrderHistoryGrid.CellAlignment = 1
    OrderHistoryGrid.ColWidth(2) = 4000
    OrderHistoryGrid.Col = 3
    OrderHistoryGrid.Text = "Price:"
    OrderHistoryGrid.ColWidth(3) = 1000
    OrderHistoryGrid.CellAlignment = 1
    OrderHistoryGrid.Col = 4
    OrderHistoryGrid.Text = "Qty:"
    OrderHistoryGrid.ColWidth(4) = 900
    OrderHistoryGrid.CellAlignment = 1
    OrderHistoryGrid.Col = 5
    OrderHistoryGrid.Text = "Total Cost:"
    OrderHistoryGrid.ColWidth(5) = 1300
    OrderHistoryGrid.CellAlignment = 1
    OrderHistoryGrid.Col = 6
    OrderHistoryGrid.Text = "ID:"
    OrderHistoryGrid.ColWidth(6) = 0
    OrderHistoryGrid.CellAlignment = 1
    
    frmOrder.MousePointer = 0 ' turn mouse pointer back to normal pointer

End Sub

Private Sub Form_Unload(Cancel As Integer)
    Order_Form_hWnd = 0
    Customer_Index = 0 ' Reset variable that keeps track of customer position.  Used for setting the customer on the customer form
End Sub

Private Sub lstOrders_Click()

    '----------------------------------------------------------------------------
    ' After selecting a order from the order list box, display the items ordered.
    '----------------------------------------------------------------------------
    
    Dim Find_ID As Integer
    Dim Cust_ID As String
    Dim Query_Result As IXMLDOMNodeList
    Dim Query_Result2 As IXMLDOMNode
    Dim Query_String As String
    Dim Order_Count As Double
      
    Find_ID = InStr(cmbCustomer.Text, "=")
      
    Cust_ID = Mid(cmbCustomer.Text, (Find_ID + 2), Len(cmbCustomer.Text))
                     
    ' Find selected order
        
    Query_String = "//Orders[Order_Number = " & lstOrders.Text & "]"
          
    Set Query_Result = doc.documentElement.selectNodes(Query_String)
          
    ' go through the entire nodelist and display all items that were ordered
  
    OrderHistoryGrid.Rows = Query_Result.Item(0).childNodes.length - 1
    
    Order_Count = 0
    
    For Each nodelist In Query_Result
        For intX = 1 To (Query_Result.Item(0).childNodes.length - 2)
            Order_Count = Order_Count + 1
            OrderHistoryGrid.Col = 0 ' Line Item
            OrderHistoryGrid.Row = Order_Count
            OrderHistoryGrid.CellAlignment = 4
            OrderHistoryGrid.Text = Order_Count
            OrderHistoryGrid.Col = 2 ' Part Description
            OrderHistoryGrid.Row = Order_Count
            OrderHistoryGrid.CellAlignment = 1
            
            ' Find Product from product file
        
            Query_String = "//ID[textnode()= " & Query_Result.Item(0).childNodes(intX + 1).childNodes(0).Text & "]"
          
            Set Query_Result2 = products.documentElement.selectSingleNode(Query_String)
    
            OrderHistoryGrid.Text = Query_Result2.childNodes(3).Text
            OrderHistoryGrid.Col = 6 ' Product ID
            OrderHistoryGrid.Text = Query_Result2.childNodes(0).Text
            OrderHistoryGrid.Col = 1 ' Part Number
            OrderHistoryGrid.CellAlignment = 1
            OrderHistoryGrid.Text = Query_Result2.childNodes(2).Text
            OrderHistoryGrid.Col = 3 ' Price
            OrderHistoryGrid.Text = Query_Result.Item(0).childNodes(intX + 1).childNodes(2).Text
            OrderHistoryGrid.Col = 4 ' Qty
            OrderHistoryGrid.Text = Query_Result.Item(0).childNodes(intX + 1).childNodes(1).Text
            OrderHistoryGrid.Col = 5 ' Total Cost
            OrderHistoryGrid.Text = Format(CDbl(Query_Result.Item(0).childNodes(intX + 1).childNodes(2).Text) * CDbl(Query_Result.Item(0).childNodes(intX + 1).childNodes(1).Text), "0.00")
        Next
    Next

End Sub

Private Sub OrderGrid_SelChange()

    Dim Total_Cost As Double
    Dim Cost_Of_Item_Deleted As Double
        
    '------------------------------------------------------------------------------------
    ' When a item in the order grid gets selected ask the user if they want to delete
    ' that item.  If "yes" then delete the line item.  If "no" then leave it in the grid.
    '------------------------------------------------------------------------------------
      
    Dim intX As Integer
    
    If OrderGrid.Rows = 2 Then ' If empty grid then exit delete routine
        OrderGrid.Col = 2
        If OrderGrid.Text = "" Then Exit Sub
    End If
    
    If (MsgBox("Do you want to delete this line item?", vbYesNo) = vbYes) Then
          
         If OrderGrid.Rows = 2 Then
            OrderGrid.Row = OrderGrid.RowSel
            OrderGrid.Col = 0
            OrderGrid.Text = ""
            OrderGrid.Col = 1
            OrderGrid.Text = ""
            OrderGrid.Col = 2
            OrderGrid.Text = ""
            OrderGrid.Col = 3
            OrderGrid.Text = ""
            OrderGrid.Col = 4
            OrderGrid.Text = ""
            OrderGrid.Col = 5
            Cost_Of_Item_Deleted = OrderGrid.Text ' store old total so I can delete it from the total order cost
            OrderGrid.Text = ""
            OrderGrid.Col = 6
            OrderGrid.Text = ""
         Else
            OrderGrid.Col = 5 ' store old total so I can delete it from the total order cost
            Cost_Of_Item_Deleted = OrderGrid.Text
            
            ' Fix line item numbers in column 0 after deleting row
             OrderGrid.RemoveItem (OrderGrid.RowSel) ' Remove entire row
             
             OrderGrid.Col = 0
             For intX = 1 To (OrderGrid.Rows - 1)
                OrderGrid.Row = intX
                OrderGrid.Text = intX
             Next
         End If
        
         Total_Cost = CDbl(Mid$(lblTotal.Caption, 16, Len(lblTotal.Caption))) - Cost_Of_Item_Deleted
         
         lblTotal.Caption = "Order Total = $" & Format(Total_Cost, "0.00") ' Display the entire order total
   
    End If
    
End Sub

Private Sub Tabstrip1_Click()

    '-----------------------------------------------------------
    ' Switch between the "New Order" tab and "Order History" tab
    '-----------------------------------------------------------
      
    If TabStrip1.SelectedItem.index = mintCurFrame Then
        Exit Sub
    Else
        If Edit_Mode = False Then ' if in edit mode then do not reset the frame variable
            mintCurFrame = TabStrip1.SelectedItem.index
        End If
        
        If mintCurFrame = 1 Then
            frHistory.Visible = False
            frNewOrder.Visible = True
        ElseIf mintCurFrame = 2 Then
            frHistory.Top = 1440
            frHistory.Left = 240
            frHistory.Height = 4815
            frHistory.Width = 8895
            frNewOrder.Visible = False
            frHistory.Visible = True
        End If
    End If
    
End Sub

