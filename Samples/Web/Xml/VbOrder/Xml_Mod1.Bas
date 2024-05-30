Attribute VB_Name = "Module1"
'*--------------------------------------------------------------------------
' Copyright (c) 1999  Microsoft Corporation.  All Rights Reserved.
'
' THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
' ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
' THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
' PARTICULAR PURPOSE.
'file://XML_Mod1.bas--------------------------------------------------------------------------
  
Global doc As New DOMDocument ' global XML object for the orders file
Global products As New DOMFreeThreadedDocument ' global XML object for the products file
Global Order_File As String ' Path to orders file
Global customers As New DOMDocument ' global XML object for the customer file
Global Customer_Index As Integer ' Used to track current customer when ordering
Global Customers_Path As String ' Path to customers file
Global Order_Form_hWnd As Long ' Form ID for the order form
Global Customer_Form_hWnd As Long ' Form ID for the customer form
Global Edit_Mode As Boolean ' Used to determine if user is editing a order

Sub Find_Last_Order()
      
    '--------------------------------------------------------------------------------
    ' Find the last order so I can increment the order number by 1 for the next order
    '--------------------------------------------------------------------------------
    
    Dim intX As Integer
    Dim Highest_Order_Number As Integer
    Dim node1 As IXMLDOMNode
    
    intX = 0
    Highest_Order_Number = 0
    
    On Error GoTo Find_Error
    
    ' Find the last order number and add one
    
    For intX = 0 To (doc.documentElement.childNodes.length - 1)
    
        Set node1 = doc.documentElement.childNodes(intX).childNodes(0)
        
        If (node1.Text > Highest_Order_Number) Then
        
            Highest_Order_Number = node1.Text
    
        End If
        
    Next
    
    frmOrder.lblActualOrderNumber.Caption = Highest_Order_Number + 1
    
    On Error GoTo 0
    
    Exit Sub
    
Find_Error:
    
    frmOrder.lblActualOrderNumber.Caption = 1 ' No records so start with order number 1
    
    On Error GoTo 0
    
End Sub
Sub Fill_Product_Select()

    '----------------------------------------------------------------------------------
    ' Fill the products drop down list box with all the products from the products file
    '----------------------------------------------------------------------------------
    
    frmOrder.MousePointer = 11
    
    Dim intX As Long
        
    frmOrder.cmbProducts.Clear

    For intX = 0 To products.documentElement.childNodes.length - 1
    
        ' Fill product combo box with product names
        
        frmOrder.cmbProducts.AddItem (products.documentElement.childNodes.Item(intX).childNodes.Item(1).Text & ": " & products.documentElement.childNodes.Item(intX).childNodes.Item(3).Text & " - " & products.documentElement.childNodes.Item(intX).childNodes.Item(0).Text)
    
    Next
    
    frmOrder.MousePointer = 0
    
End Sub

Sub Fill_Customer_Select()

    '-----------------------------------------------------------------------------------
    ' Fill the customer drop down list box with all the customers from the customer file
    '-----------------------------------------------------------------------------------
    
    frmOrder.MousePointer = 11
    
    Dim intX As Long
        
    frmOrder.cmbCustomer.Clear ' Clear all customers

    frmOrder.cmbCustomer.AddItem ("Select a customer")
    
    If customers.xml <> "" Then
    
        For intX = 0 To customers.documentElement.childNodes.Item(0).childNodes.length - 1
        
            ' Fill customer combo box with customer names and company names if they exist
            
            If (customers.documentElement.childNodes.Item(0).childNodes.Item(intX).childNodes.Item(0).Text = "") Then ' No company name associated with the customer
                frmOrder.cmbCustomer.AddItem (customers.documentElement.childNodes.Item(0).childNodes.Item(intX).childNodes.Item(1).Text & " " & customers.documentElement.childNodes.Item(0).childNodes.Item(intX).childNodes.Item(3).Text & " - ID = " & customers.documentElement.childNodes.Item(0).childNodes.Item(intX).Attributes.Item(0).Text)
            Else
                frmOrder.cmbCustomer.AddItem (customers.documentElement.childNodes.Item(0).childNodes.Item(intX).childNodes.Item(0).Text & " - " & customers.documentElement.childNodes.Item(0).childNodes.Item(intX).childNodes.Item(1).Text & " " & customers.documentElement.childNodes.Item(0).childNodes.Item(intX).childNodes.Item(3).Text & " - ID = " & customers.documentElement.childNodes.Item(0).childNodes.Item(intX).Attributes.Item(0).Text)
            End If
        Next
        
    End If
    
    frmOrder.cmbCustomer.ListIndex = 0 ' Select the message in the drop down select box
    
    frmOrder.MousePointer = 0
    
End Sub

Sub Add_Part()

    '---------------------------------------------------------------------------------------
    ' This function will be called (from Search_For_Dup())if this is a new product to add to
    ' the order grid.
    '---------------------------------------------------------------------------------------
    
    Dim Query_Result As IXMLDOMNode
    Dim Query_String As String
    Dim Text_Search As String
    Dim Find_Text As Integer
    Dim Final_Price As Double
    Dim Product_ID As String
    
    frmOrder.OrderGrid.Col = 2 ' Part Description col
    
    'Check to see if this is the first item in the grid.
    
    If (frmOrder.OrderGrid.Rows = 2 And frmOrder.OrderGrid.Text = "") Then
        frmOrder.OrderGrid.Row = 1 ' no products in grid
    Else
        frmOrder.OrderGrid.Rows = (frmOrder.OrderGrid.Rows + 1) ' Add a new row to the grid
        frmOrder.OrderGrid.Row = (frmOrder.OrderGrid.Rows - 1)
    End If
    frmOrder.OrderGrid.Col = 0
    frmOrder.OrderGrid.Text = (frmOrder.OrderGrid.Rows - 1)
    frmOrder.OrderGrid.CellAlignment = 4
    
    On Error Resume Next
    
    Text_Search = Right(frmOrder.cmbProducts.Text, 5) ' Copy only product ID number from selected product
    Find_Text = InStr(Text_Search, "-") ' Find the start of the Product ID number
    
    ' Find part number
    
    Query_String = "//ID[textnode() = " & Mid(Text_Search, (Find_Text + 1)) & "]/Manuf_Part_Num"
    Product_ID = Mid(Text_Search, (Find_Text + 1))
    
    Set Query_Result = products.documentElement
    
    Set Query_Result = Query_Result.selectSingleNode(Query_String)
    
    frmOrder.OrderGrid.Col = 1
    frmOrder.OrderGrid.Text = Query_Result.Text
    frmOrder.OrderGrid.CellAlignment = 1
    
    ' Find product description
    
    Query_String = "//ID[textnode() = " & Mid(Text_Search, (Find_Text + 1)) & "]/Description"
    
    Set Query_Result = products.documentElement
    
    Set Query_Result = Query_Result.selectSingleNode(Query_String)
    
    frmOrder.OrderGrid.Col = 2
    frmOrder.OrderGrid.Text = Query_Result.Text
    frmOrder.OrderGrid.CellAlignment = 1
    
    ' Find out price of product
    
    Query_String = "//ID[textnode() = " & Mid(Text_Search, (Find_Text + 1)) & "]/Price"
    
    Set Query_Result = products.documentElement
    
    Set Query_Result = Query_Result.selectSingleNode(Query_String)
    
    frmOrder.OrderGrid.Col = 3
    
    ' If the price of the product has been changed then ask user to confirm new price
    
    If Query_Result.Text <> frmOrder.txtPrice.Text Then
        If (MsgBox("The price has been changed.  Do you want to use the edited price?", vbYesNo) = vbYes) Then
            frmOrder.OrderGrid.Text = frmOrder.txtPrice.Text
        Else
            frmOrder.OrderGrid.Text = Query_Result.Text
        End If
    Else
            frmOrder.OrderGrid.Text = Query_Result.Text
    End If
    frmOrder.OrderGrid.CellAlignment = 1
    
    Final_Price = frmOrder.OrderGrid.Text
    
    On Error GoTo 0
    
    ' Order Qty
    frmOrder.OrderGrid.Col = 4
    frmOrder.OrderGrid.Text = frmOrder.txtQty.Text
    frmOrder.OrderGrid.CellAlignment = 1
    
    ' Qty * Price = Total Cost
    frmOrder.OrderGrid.Col = 5
    frmOrder.OrderGrid.Text = Format(frmOrder.txtQty.Text * Final_Price, "0.00")
    frmOrder.OrderGrid.CellAlignment = 1
    
    frmOrder.OrderGrid.Col = 6 ' Part ID number - used for saving orders
    frmOrder.OrderGrid.Text = Trim(Product_ID)
    frmOrder.OrderGrid.CellAlignment = 1
        
End Sub

Sub Search_For_Dup()

    '----------------------------------------------------------------------------
    ' Before adding a new item to the order check for dups.  If it is a duplicate
    ' then change the qty ordered
    '----------------------------------------------------------------------------
    
    On Error Resume Next
    
    Dim Query_Result As IXMLDOMNode
    Dim Query_String As String
    Dim Text_Search As String
    Dim Find_Text As Integer
    Dim Add_Flag As Integer
    Dim Orig_Price As Double
    
    Add_Flag = 1 ' Set to true unless a duplicate is found
    
    Text_Search = Right(frmOrder.cmbProducts.Text, 5) ' Copy only product ID number from selected product
    Find_Text = InStr(Text_Search, "-") ' Find the start of the Product ID number
    
    ' Find part number
    
    Query_String = "//ID[textnode() = " & Mid(Text_Search, (Find_Text + 1)) & "]/Description"
    
    Set Query_Result = products.documentElement
    
    Set Query_Result = Query_Result.selectSingleNode(Query_String)
    
    frmOrder.OrderGrid.Col = 2
    
    ' Go through grid for duplicate orders
    
    For intX = 1 To (frmOrder.OrderGrid.Rows - 1)
        frmOrder.OrderGrid.Row = intX
        If frmOrder.OrderGrid.Text = Query_Result.Text Then
            If (MsgBox("A duplicate item has been found.  Do you want to update the quanity of the existing item?", vbYesNo) = vbYes) Then
                frmOrder.OrderGrid.Col = 4
                frmOrder.OrderGrid.Text = CInt(frmOrder.OrderGrid.Text) + frmOrder.txtQty.Text
                frmOrder.OrderGrid.CellAlignment = 1
                
                Find_Text = frmOrder.OrderGrid.Text ' get total QTY
                
                frmOrder.OrderGrid.Col = 3
                Orig_Price = frmOrder.OrderGrid.Text ' get Price
                
                frmOrder.OrderGrid.Col = 5
                frmOrder.OrderGrid.Text = Format((Orig_Price * Find_Text), "0.00")
                frmOrder.OrderGrid.CellAlignment = 1
                
                Add_Flag = 0 ' don't add another entry in the grid
            Else
                Add_Flag = 0 ' don't add another entry because the user does not want to add to the total already on order
                Exit For
            End If
        End If
    Next
    
    If Add_Flag = 1 Then Call Add_Part
    
End Sub
Sub Find_Product_Description()

    '--------------------------------------------------------------
    ' Find the product description and price from the products file
    '--------------------------------------------------------------
    
    Dim Query_Result As IXMLDOMNode
    Dim Query_String As String
    Dim Text_Search As String
    Dim Find_Text As Integer
    
    frmOrder.txtDescription.Text = "" ' Clear text box
    frmOrder.txtPrice.Text = "" ' Clear text box
    frmOrder.txtQty.Text = "1" ' Reset Qty to 1
    
    On Error Resume Next
        
    Text_Search = Right(frmOrder.cmbProducts.Text, 5) ' Copy only product ID number from selected product
    Find_Text = InStr(Text_Search, "-") ' Find the start of the Product ID number
    
    ' Find product description
    
    Query_String = "//ID[textnode() = " & Mid(Text_Search, (Find_Text + 1)) & "]/Description"
    
    Set Query_Result = products.documentElement
    
    Set Query_Result = Query_Result.selectSingleNode(Query_String)
    
    frmOrder.txtDescription.Text = Query_Result.Text ' set part description in order form
        
    ' Find out price of product
    
    Query_String = "//ID[textnode() = " & Mid(Text_Search, (Find_Text + 1)) & "]/Price"
    
    Set Query_Result = products.documentElement
    
    Set Query_Result = Query_Result.selectSingleNode(Query_String)
    
    frmOrder.txtPrice.Text = Query_Result.Text ' set price in order form
    
    On Error GoTo 0
    
End Sub

Sub Reset_Form()

    '---------------------------------------------------------------
    ' Reset the order form by clearing text boxes, grids, list boxes
    '---------------------------------------------------------------
    
    Dim intX As Integer
    
    Call Find_Last_Order ' Find last order number
    
    frmOrder.cmbProducts.ListIndex = 0
    frmOrder.txtPrice.Text = ""
    frmOrder.txtDescription.Text = ""
    frmOrder.lblActualOrderDate.Caption = Date
    frmOrder.lblTotal.Caption = "Order Total = $0.00"
    
    If Edit_Mode <> True Then
        frmOrder.cmbCustomer.ListIndex = 0
        frmOrder.lstOrders.Clear
        frmOrder.lblCustID.Caption = "Customer ID:"
    End If
    
    ' Reset the entire ordergrid
      
    For intX = 1 To (frmOrder.OrderGrid.Rows - 1)
        If frmOrder.OrderGrid.Rows = 2 Then
          frmOrder.OrderGrid.Row = 1
          frmOrder.OrderGrid.Col = 0
          frmOrder.OrderGrid.Text = ""
          frmOrder.OrderGrid.Col = 1
          frmOrder.OrderGrid.Text = ""
          frmOrder.OrderGrid.Col = 2
          frmOrder.OrderGrid.Text = ""
          frmOrder.OrderGrid.Col = 3
          frmOrder.OrderGrid.Text = ""
          frmOrder.OrderGrid.Col = 4
          frmOrder.OrderGrid.Text = ""
          frmOrder.OrderGrid.Col = 5
          frmOrder.OrderGrid.Text = ""
          frmOrder.OrderGrid.Col = 6
          frmOrder.OrderGrid.Text = ""
      Else
          frmOrder.OrderGrid.RemoveItem (1)
      End If
    Next
    
End Sub
Sub Save_XML_File(File_Name As String, XML_Object As DOMDocument)

    '--------------------------
    ' Save the XML file to disk
    '--------------------------
    
    ' This uses the XML DOM to save the file
    
    XML_Object.save (File_Name)
  
    If XML_Object.parseError.reason <> "" Then
        MsgBox "There was an error saving the XML file."
    End If
    
    '****************************************************************
    ' The code below shows how to use VB to save the XML file to disk
    '----------------------------------------------------------------
       
     'On Error GoTo File_Error
     
    ' delete old file
     'Kill File_Name
     
     ' Save XML to disk
     
     'Dim FileNum As Integer
     
     'FileNum = FreeFile
     
     'Open File_Name For Binary As FileNum
     
     'Put #FileNum, 1, XML_Object.xml
     
     'Close
     
     'On Error GoTo 0
     
     'Exit Sub
     
    'File_Error:
     
     'If Err = 53 Then ' File not found
       'Resume Next
     'Else
       'MsgBox "Error saving XML file"
       'On Error GoTo 0
       'Exit Sub
     'End If
     '****************************************************************
     
End Sub

Sub Load_XML_Files()
    
    '-----------------------------------------
    ' Load the products and customer XML files
    '-----------------------------------------
    
    Dim Products_Path As String

    Customer_Index = 0 ' set customer index number
    
    '----------------------------------------------------------------------
    ' Use the following code only if you are using VB to save the XML file
    ' See the notes in the function Save_XML_File() for save info
    '----------------------------------------------------------------------
    'Products_Path = CurDir("c") & "\products.xml"
    'Customers_Path = CurDir("c") & "\customers.xml"
    'Order_File = CurDir("c") & "\orders.xml" ' set global path to xml file
    
    Products_Path = "products.xml"
    Customers_Path = "customers.xml"
    Order_File = "orders.xml" ' set global path to xml file
    
    products.Load (Products_Path) ' load products xml file
    
    customers.Load (Customers_Path) ' loads customer xml file

End Sub
