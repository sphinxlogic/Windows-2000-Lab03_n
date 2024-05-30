<%@ Language=VBScript EnableSessionState=False %>
<% Option Explicit %>
<% ' Copyright Microsoft 1998-1999.  All rights reserved. %>
<% Dim nBibNo

   nBibNo = Request("bibno")
   If Not (IsEmpty(nBibNo) Or nBibNo="") Then
      nBibNo = CLng(nBibNo)
   Else
      Err.Raise &H80040005, "ASP", "Must specify 'bibno' as URL parameter."
   End If
%>
<HTML>
<HEAD>
<TITLE>Add Library Items</TITLE>
<META NAME="GENERATOR" Content="Microsoft Visual Studio 6.0">

<!-- DATA CONTROLS -- Title, Author, Subject Details -->
<object id="RDS_ItemDetail" CLASSID="clsid:BD96C556-65A3-11D0-983A-00C04FC29E33"
        height=1 width=1 VIEWASTEXT>
</object>

<script LANGUAGE=VBScript>
<!-- #include file="../../librarysearch/adcvbs.inc" -->

Sub GetData(nItemID)
   Dim RDS

   If RDS_ItemDetail.ReadyState <> adcReadyStateComplete Then
      MsgBox "Query results still arriving.  Please wait...", vbInformation
   Else
      ' Retrieve the details of this title from the database
      Set RDS = RDS_ItemDetail
      RDS.ExecuteOptions = adcExecSync
      RDS.FetchOptions = adcFetchAsync
      RDS.Handler = "MSDFMAP.Handler,FmLibMap.ini"
      RDS.Server = "http://<%= Request.ServerVariables("SERVER_NAME") %>"
      RDS.Connect = "Data Source=FmLib"
      RDS.SQL = "ItemDetails(" & nItemID & ")"
      RDS.Refresh
   End If      
End Sub
</script>

<script Language="VBScript">
Dim nLastSel

Sub Window_OnLoad()
   <% If Application("Debug") = True Then %>
   document.all.ifControl.style.display = ""
   <% End If %>
   Call Reset
End Sub

Sub SubmitForm()
   Dim theForm,theFields,item,strMissing
   
   Set theForm = document.frmAddItem
   
   ' Check for missing information in text fields
   theFields = Array("Location")
   For Each item In theFields
      If Trim(theForm.Elements(item).Value) = "" Then
         strMissing = strMissing & item & vbCrLf
      End If
   Next

   If strMissing = "" Then
      ' SUCCESS: Proceed with submission
      theForm.Action = "AddNewItem.asp?Action=Update"
      theForm.Submit
   Else
      MsgBox "You are missing information from the following field(s):" & _
             vbCrLf & vbCrLf & strMissing & vbCrLf & "Please fill in these fields.",_
             vbCritical, "Missing Information"
      ShowPage 2
      ' Focus on the first missing element in the form
      theForm.Elements(Left(strMissing,InStr(strMissing,vbCrLf)-1)).Focus
   End If
End Sub

Sub ShowPage(nPage)
   Dim theSel,nSel
   ClearAllDivs
   ' MsgBox "ShowPage: " & nPage
   Select Case nPage
   Case 0:
      ' Return to previous page
      document.location.href = "AddTitles.asp?bibno=<%= nBibNo %>"
   Case 1: 
      Items.style.display = ""
      Call CheckSelection
   Case Else:
      Set theSel = Document.frmAddItem.ItemNum
      nSel = theSel.SelectedIndex
      If nSel <> nLastSel Then
         nLastSel = nSel
         GetData(theSel.Options(nSel).Value)
      End If
      ItemDetail.style.display = ""
      WizardEnd.style.display = ""
      Document.frmAddItem.Location.Focus
   End Select
End Sub

Sub Reset()
   document.frmAddItem.Reset
   nLastSel = -1
   WizStart
End Sub

Sub AddItem()
   Dim theForm
   Set theForm = Document.frmAddItem
   If Trim(theForm.NewBarcode.Value) <> "" Then
      theForm.Action = "AddNewItem.asp?Action=Add"
      theForm.Submit    ' It's empty, but it's easier to POST from VBScript than to encode URL params for a GET
   Else
      MsgBox "You must specify a barcode (or identifying text) when adding a new item.", vbCritical, "Missing Input"
      Document.frmAddItem.NewBarcode.Focus
   End If
End Sub

Sub DeleteItems()
   Dim theSel,theOpts,src,div,i,nRet
   
   ' Confirm that an item has been selected, and that it's OK to delete it.
   Set theSel = Document.frmAddItem.ItemNum
   If theSel.selectedIndex < 0 Then
      MsgBox "You must select an item first.", vbInformation, "Missing Input"
      nRet = vbNo
   Else
      nRet = MsgBox("Are you sure you wish to delete the selected items?", vbQuestion + vbYesNo, "Confirm Delete")
   End If
   
   ' Continue with deletion...
   If nRet = vbYes Then
      src = "DelItems.asp?"
      div = ""
      Set theOpts = theSel.Options
      For i = 0 To theOpts.Length - 1
         If theOpts(i).Selected = True Then
            src = src & div & "item=" & theOpts(i).Value
            div = "&"
         End If
      Next
      ' Call the worker thread...
      Document.all.ifControl.src = src
   End If
End Sub

'--- Toggle button highlight as selections are made 
Sub CheckSelection()
   If Document.frmAddItem.ItemNum.SelectedIndex < 0 Then
      WizardMid.style.display = "none"
      WizardBackOK.style.display = ""
   Else
      WizardMid.style.display = ""
      WizardBackOK.style.display = "none"
   End If
End Sub

'--- Called by double-click
Sub MoveForward()
   If WizardMid.style.display = "" Then WizForward()
End Sub

Sub ClearAllDivs
   Call ClearWizardDivs
   Items.style.display = "none"
   ItemDetail.style.display = "none"
End Sub

'--- Trap ENTER key and invoke appropriate ADD function
Sub Document_OnKeyPress()
   Dim nASCII
   nASCII = window.event.keyCode
   ' Check for ENTER
	IF nASCII = 13 Then
		Select Case nCurrentPage
		Case 1: Call AddItem
		Case 2: Call SubmitForm
		End Select
   ' Check for CTRL+BKSP (formally DEL)
	ElseIf nASCII = 127 Then
      Call DeleteItems
	End if
End Sub

</script>
</HEAD>

<BODY>

<link type="text/css" rel="stylesheet" href="../../_Themes/fm/theme.css">	
<img class="logo" SRC="../../images/fmlogo.gif" WIDTH="187" HEIGHT="90">
<img class="sublogo" SRC="../../images/Fmcorplib.gif" WIDTH="180" HEIGHT="18">

<div class=menui style="position:absolute;top:100;left:13px;">
<TABLE border=0 height=250 width=200 CELLSPACING=0 CELLPADDING=0>
<TR vAlign=top><TD>
   <TABLE class=admin WIDTH=75% BORDER=0 CELLSPACING=2 CELLPADDING=2>
   <TR>
      <TD BGCOLOR=#ce6300 valign=top ALIGN=center NOWRAP id=mI>Administration</TD>
   </TR>
   </TABLE></TD>
</TR>
</TABLE>
</div>

<form NAME="frmAddItem" ACTION="<%'Set in script above %>" METHOD=Post TARGET="ifControl">
<input TYPE=Hidden NAME="BibNo" VALUE="<%= nBibNo %>">

<div ID="Items" STYLE="DISPLAY: none; LEFT: 60px; POSITION: absolute; TOP: 150px; WIDTH: 550 px; Z-INDEX: 5">
   <span style="COLOR: #000000; FONT-FAMILY: Verdana,arial; FONT-WEIGHT: bold; FONT-SIZE: 12pt; TEXT-DECORATION: none">Add/Edit Item</span>
   <table COLS=2 CELLPADDING=0 CELLSPACING=2 BORDER=0 WIDTH="100%">
   <tr><td COLSPAN=2 ALIGN=Center>Barcode: <input NAME="NewBarcode" SIZE=30 MAXLENGTH=16 TITLE="Enter new barcode here">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
   <input TYPE=Button VALUE="Add New Item" onClick="AddItem()"></td></tr>
   <tr><td COLSPAN=2>
   <select NAME="ItemNum" SIZE=14 MULTIPLE STYLE="WIDTH: 100%" onChange="CheckSelection()" onDblClick="MoveForward()">
   <% Dim rs,cn
   
      '--- Open a connection to use for filling in author and subject lists
      Set cn = Server.CreateObject("ADODB.Connection")
      cn.ConnectionTimeout = Application("FmLib_ConnectionTimeout")
      cn.Open Application("FmLib_ConnectionString")

      '--- Populate author list from table
      Set rs = Server.CreateObject("ADODB.Recordset")
      rs.Open "SELECT item#,barcode FROM Item WHERE bib#=" & nBibNo, cn
      Do Until rs.EOF
         Response.Write "<OPTION VALUE=" & rs("item#") & ">" & rs("barcode") & "</OPTION>" & vbCrLf
         rs.MoveNext
      Loop
      rs.Close
   %>
   </select></td></tr>
   <tr><td><font SIZE=-2>Select multiple by using CTRL+click or SHIFT+click</font></td>
   <td align=right><input type=button VALUE="Delete Selected Items" onClick="DeleteItems()">
   </td></tr>
   </table>
</div>

<div ID="ItemDetail" STYLE="DISPLAY: none; LEFT: 60px; POSITION: absolute; TOP: 150px; WIDTH: 550 px; Z-INDEX: 5">
   <span style="COLOR: #000000; FONT-FAMILY: Verdana,arial; FONT-WEIGHT: bold; FONT-SIZE: 12pt; TEXT-DECORATION: none">Item Detail</span>
   <input TYPE=Hidden NAME="Barcode" DATASRC="#RDS_ItemDetail" DATAFLD="Barcode">
   <table DATASRC="#RDS_ItemDetail" COLS=2 CELLPADDING=0 CELLSPACING=2 BORDER=0>
	<tr ALIGN=Center><td BGCOLOR="#C0C0C0">&nbsp;Barcode:&nbsp;</td><td><strong><span ID="Barcode" SIZE=30 DATAFLD="Barcode"></span></strong></td></tr>
	<tr ALIGN=Center><td BGCOLOR="#C0C0C0">&nbsp;Location:&nbsp;</td><td><input name="Location" SIZE=60 DATAFLD="Location"></td></tr>
	<tr ALIGN=Center><td BGCOLOR="#C0C0C0">&nbsp;Source:&nbsp;</td><td><input name="Source" SIZE=60 DATAFLD="Source"></td></tr>
	<tr ALIGN=Center><td BGCOLOR="#C0C0C0">&nbsp;Price:&nbsp;</td><td><input name="Price" SIZE=60 DATAFLD="Price"></td></tr>
	<tr ALIGN=Center><td BGCOLOR="#C0C0C0">&nbsp;Notes:&nbsp;</td><td>
	   <textarea name="Notes" COLS=44 ROWS=5 DATAFLD="Notes"></textarea>
	</td></tr>
	<tr ALIGN=Center><td BGCOLOR="#C0C0C0">&nbsp;Item Status:&nbsp;</td><td>
	   <input name="Item_Status" TYPE=Radio VALUE="in" ID=cbIn DATAFLD="Item_Status" CHECKED><LABEL FOR=cbIn>In</LABEL>&nbsp;&nbsp;
	   <input name="Item_Status" TYPE=Radio VALUE="out" ID=cbOut DATAFLD="Item_Status"><LABEL FOR=cbOut>Out</LABEL>&nbsp;&nbsp;
	   <input name="Item_Status" TYPE=Radio VALUE="lost" ID=cbLost DATAFLD="Item_Status"><LABEL FOR=cbLost>Lost</LABEL>&nbsp;&nbsp;
	   <input name="Item_Status" TYPE=Radio VALUE="pend" ID=cbPend DATAFLD="Item_Status"><LABEL FOR=cbPend>On Order</LABEL>
   </td></tr>	   
	<tr ALIGN=Center><td BGCOLOR="#C0C0C0">&nbsp;Library Use Only?&nbsp;</td><td>
	   <input name="StaffOnly" TYPE=Radio VALUE=1 ID=cbYes DATAFLD="Staff_Only"><LABEL FOR=cbYes>Yes</LABEL>&nbsp;&nbsp;&nbsp;
	   <input name="StaffOnly" TYPE=Radio VALUE=0 ID=cbNo  DATAFLD="Staff_Only" CHECKED><LABEL FOR=cbNo>No</LABEL>
	</td></tr>
	</table>
</div>

</form>

<!--#include file="wButtons.asp"-->

<!-- IFRAME -- This frame controls updates -->
<iframe ID="ifControl" NAME="ifControl" STYLE="POSITION:absolute;display:none;top:520;left:60px;height:60px;width:540px" FRAMEBORDER=0 NORESIZE SCROLLING=NONE>
</iframe>

</BODY>
</HTML>
