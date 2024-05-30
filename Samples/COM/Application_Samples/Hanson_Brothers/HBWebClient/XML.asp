

<SCRIPT LANGUAGE=vbscript RUNAT=Server>
sub GetTableStrings()
	AcctNum = Session("AcctNum")
	ssn= Session("SSN")
	Dim objXMLDOM
  
    bDirty = session("Dirty")
	if (bDirty ="") or (bDirty=True) then
		set objXMLDOM = server.CreateObject("MSXML.DOMDocument")
		call UpdateInfoXML(ssn, objXMLDOM)
		call GetHistoryXML(AcctNum, objXMLDOM, tablestr)
		Session("HistoryTableStr")=tablestr
		call GetDetailsXML(AcctNum, objXMLDOM, tablestr)
		session("DetailsTableStr")=tablestr
		call GetHoldingsXML(AcctNum, objXMLDOM, tablestr)
		session("holdingsTableStr")=tablestr
		call GetPendingOrdersXML(AcctNum, objXMLDOM, tablestr)
		session("PendingTableStr")=tablestr
		
		session("Dirty")=False	
		set objXMLDOM = nothing	
	
	end if
end sub	

Sub UpdateInfoXML(ssn, objXMLDOM)
        
    Set objAcct = server.CreateObject("HBInstitution.IAccount")
    Dim strXMLStream
    Dim sMsg
    rc = objAcct.GetXMLAccounts(ssn, strXMLStream, sMsg)
    objXMLDOM.loadXML (strXMLStream)
    set objAcct = nothing          
End Sub
Sub GetDetailsXML(sAcctNum, objXMLDOM, tablestr)
    
    Dim xmlCurNode
    Call XML_FindTopLevelNode(objXMLDOM, "CustomerSSN", "", "", xmlCurNode)
    Call XML_FindTopLevelNode(xmlCurNode, "Accounts", "CustomerSSN", "", xmlCurNode)
    Call XML_FindTopLevelNode(xmlCurNode, "account", "Accounts", "", xmlCurNode)
    tablestr = ""

    Dim vXMLData
    Dim vXMLAccount
    Dim vXMLCash
    Dim vXMLCashDebit
    Dim strRow
    Dim bAccFound
    tablestr = tablestr & "<tr>"
    vXMLAccount = XML_GetValue(xmlCurNode, "acctNumber", "Accounts")
    If vXMLAccount <> "" Then bAccFound = True
    tablestr = tablestr & "<td>" & vXMLAccount & "</td>"
    vXMLData = XML_GetValue(xmlCurNode, "acctType", "Accounts")
    tablestr = tablestr & "<td>" & vXMLData & "</td>"
    vXMLCash = XML_GetValue(xmlCurNode, "cash", "Accounts")
    tablestr = tablestr & "<td>" & FormatCurrency(vXMLCash) & "</td>"
    vXMLCashDebit = XML_GetValue(xmlCurNode, "cashDebit", "Accounts")
    tablestr = tablestr & "<td>" & FormatCurrency(vXMLCashDebit) & "</td>"
    vXMLData = XML_GetValue(xmlCurNode, "netWorth", "Accounts")
    tablestr = tablestr & "<td>" & FormatCurrency(vXMLData) & "</td>"
    vXMLData = FormatCurrency(vXMLCash - vXMLCashDebit)
    tablestr = tablestr & "<td>" & vXMLData & "</td>"
    tablestr = tablestr & "</tr>"
  
  
    While XML_FindNextTopLevelNode(xmlCurNode, "account", "Accounts", xmlCurNode)
         vXMLAccount = ""
         tablestr = tablestr & "<tr>"
                 
         vXMLAccount = XML_GetValue(xmlCurNode, "acctNumber", "Accounts")
         tablestr = tablestr & "<td>" & vXMLAccount & "</td>"
         vXMLData = XML_GetValue(xmlCurNode, "acctType", "Accounts")
         tablestr = tablestr & "<td>" & vXMLData & "</td>"
         vXMLCash = XML_GetValue(xmlCurNode, "cash", "Accounts")
         tablestr = tablestr & "<td>" & FormatCurrency(vXMLCash) & "</td>"
         vXMLCashDebit = XML_GetValue(xmlCurNode, "cashDebit", "Accounts")
         tablestr = tablestr & "<td>" & FormatCurrency(vXMLCashDebit) & "</td>"
         vXMLData = XML_GetValue(xmlCurNode, "netWorth", "Accounts")
         tablestr = tablestr & "<td>" & FormatCurrency(vXMLData) & "</td>"
         vXMLData = FormatCurrency(vXMLCash - vXMLCashDebit)
         tablestr = tablestr & "<td>" & vXMLData & "</td>"
         tablestr = tablestr & "</tr>"

    Wend
    tablestr = tablestr & ""
   
End Sub
 
Public Function XML_FindNextTopLevelNode(DNo, ByVal strXmlPath, ByVal strParent, returnDN)
    If DNo Is Nothing Then Exit Function
    On Error Resume Next
    
    XML_FindNextTopLevelNode = False
    
    Dim DNoSibbling
    Set DNoSibbling = DNo.nextSibling
    If DNoSibbling Is Nothing Then Exit Function
    
    ' Check to see if we have an element
    If (DNoSibbling.nodeType = 1) Then ' NODE_ELEMENT = 1
        'Check to see if it's the correct type, and has the same parent as it's sibbling
        If strXmlPath = DNoSibbling.baseName And strParent = DNoSibbling.parentNode.baseName Then
            XML_FindNextTopLevelNode = True
            Set returnDN = DNoSibbling
            Exit Function
        End If
    End If
    
End Function


Sub GetHistoryXML(sAcctNum, objXMLDOM, tablestr)
    
    Dim xmlCurNode
    Call XML_FindTopLevelNode(objXMLDOM, "CustomerSSN", "", "", xmlCurNode)
    Call XML_FindTopLevelNode(xmlCurNode, "Accounts", "CustomerSSN", "", xmlCurNode)
    Call XML_FindTopLevelNode(xmlCurNode, "account", "Accounts", sAcctNum, xmlCurNode)
    Call XML_FindTopLevelNode(xmlCurNode, "Histories", "account", "", xmlCurNode)
    tablestr = ""
    Call XML_PopulateGrid(xmlCurNode, "History", True, bFound, tablestr)
    tablestr = "" & tablestr & ""
End Sub
Sub GetHoldingsXML(sAcctNum, objXMLDOM, tablestr)
    
    Dim xmlCurNode
    Call XML_FindTopLevelNode(objXMLDOM, "CustomerSSN", "", "", xmlCurNode)
    Call XML_FindTopLevelNode(xmlCurNode, "Accounts", "CustomerSSN", "", xmlCurNode)
    Call XML_FindTopLevelNode(xmlCurNode, "account", "Accounts", sAcctNum, xmlCurNode)
    Call XML_FindTopLevelNode(xmlCurNode, "Holdings", "account", "", xmlCurNode)
    tablestr = ""
    Call XML_PopulateGrid(xmlCurNode, "Holding", False, bFound, tablestr)
    tablestr = "" & tablestr & " "
End Sub
Sub GetPendingOrdersXML(sAcctNum, objXMLDOM, tablestr)
    
    Dim xmlCurNode
    Call XML_FindTopLevelNode(objXMLDOM, "CustomerSSN", "", "", xmlCurNode)
    Call XML_FindTopLevelNode(xmlCurNode, "Accounts", "CustomerSSN", "", xmlCurNode)
    Call XML_FindTopLevelNode(xmlCurNode, "Pending_Orders", "Accounts", sAcctNum, xmlCurNode)
    tablestr = ""
    Call XML_PopulateGrid(xmlCurNode, "Pending", False, bFound, tablestr)
    tablestr = "" & tablestr & ""
End Sub

 

Function XML_FindTopLevelNode(DNo, ByVal strXmlPath, ByVal strParent, ByVal strTwin, returnDN)
    If DNo Is Nothing Then Exit Function
    On Error Resume Next
    Dim i
    Dim bNotFound
    
    ' Check to see if we have and node element
    If (DNo.nodeType = 1) Then ' 1 = 1
        ' Check to see if we have the correct type of element
        If strXmlPath = DNo.baseName Then
            ' If no Twin, then we've found our element
            If strTwin = "" Then
                XML_FindTopLevelNode = True
                Set returnDN = DNo
                Exit Function
            ' If we have a twin, check to see if we have the correct node
            ElseIf DNo.firstChild.Text = strTwin Then
                XML_FindTopLevelNode = True
                Set returnDN = DNo
                Exit Function
            Else
                Exit Function
            End If
        ElseIf DNo.parentNode.baseName = strParent Then
            Exit Function
        End If
    End If
    
    If DNo.childNodes Is Nothing Then Exit Function
    
    While i <= DNo.childNodes.length - 1 And Not bNotFound
        bNotFound = XML_FindTopLevelNode(DNo.childNodes.Item(i), strXmlPath, strParent, strTwin, returnDN)
        i = i + 1
    Wend
End Function

Function XML_PopulateGrid(DNo, ByRef strXmlPath, ByVal bReverse, ByRef bRowAdded, ByRef tablestr)
    If DNo Is Nothing Then Exit Function
    On Error Resume Next
    Dim i
    Dim nInsideLoop
    Dim nIndex
    Dim strRowText
    
    If (DNo.nodeType = 1) Then ' 1 = 1
        If strXmlPath = DNo.baseName Then
            
            While nInsideLoop <= DNo.childNodes.length
                Call XML_PopulateGridRow(DNo.childNodes.Item(nInsideLoop), strRowText)
                nInsideLoop = nInsideLoop + 1
            Wend
            
            'tablestr = tablestr & "<tr>"
            If bReverse Then
                tablestr = "<tr>" & strRowText & "</tr>" & tablestr
                bRowAdded = True
            Else
                tablestr = "tablestr & <tr>" & strRowText & "</tr>"
                bRowAdded = True
            End If
            
        End If
    End If
    
    If DNo.childNodes Is Nothing Then Exit Function
    
    While i <= DNo.childNodes.length - 1
        Call XML_PopulateGrid(DNo.childNodes.Item(i), strXmlPath, bReverse, bRowAdded, tablestr)
        i = i + 1
    Wend
    
End Function

Public Function XML_PopulateGridRow(DNo, ByRef strRowText)
    If DNo Is Nothing Then Exit Function
    On Error Resume Next
    Dim i
    Dim nInsideLoop
    
    If (DNo.nodeType = 1) Then ' 1 = 1
         strRowText = strRowText & "<td>" & DNo.Text & "</td>"
    End If
    
    If DNo.childNodes Is Nothing Then Exit Function
    
    While i <= DNo.childNodes.length - 1
        Call XML_PopulateGridRow(DNo.childNodes.Item(i), tablestr)
        i = i + 1
    Wend
    
End Function

Public Function XML_GetValue(DNo, ByVal strXmlPath, ByVal strParent)
    If DNo Is Nothing Then Exit Function
    On Error Resume Next
    Dim i
    Dim bNotFound
    
    If (DNo.nodeType = 1) Then ' 1 = 1
        If strXmlPath = DNo.baseName Then
            XML_GetValue = DNo.Text
            Exit Function
        End If
    End If
    
    If DNo.childNodes Is Nothing Then Exit Function
    
    While i <= DNo.childNodes.length - 1 And Not XML_GetValue <> ""
        XML_GetValue = XML_GetValue(DNo.childNodes.Item(i), strXmlPath, strParent)
        i = i + 1
    Wend
End Function


</SCRIPT>
