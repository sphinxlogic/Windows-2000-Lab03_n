<%@ Language=VBScript EnableSessionState=False %>
<% Option Explicit %>
<% ' Copyright Microsoft 1998-1999.  All rights reserved. %>
<HTML>
<HEAD>
<TITLE>Add Library Titles</TITLE>
<META NAME="GENERATOR" Content="Microsoft Visual Studio 6.0">
<!--#include file="verify.asp"-->

<% Dim nBibNo

   nBibNo = Request("bibno")
   If IsEmpty(nBibNo) Or nBibNo="" Then
      nBibNo = 0
   Else
      nBibNo = CLng(nBibNo)
   End If
   
   '--- If a title has been specified, this page becomes an UPDATE operation
   '--- Some additional client-side script is required
   If nBibNo > 0 Then
%>
<!-- DATA CONTROLS -- Title Details, Authors, Subjects -->
<object id="RDS_Title" CLASSID="clsid:BD96C556-65A3-11D0-983A-00C04FC29E33"
        height=1 width=1 VIEWASTEXT>
</object>
<object id="RDS_Author" CLASSID="clsid:BD96C556-65A3-11D0-983A-00C04FC29E33"
        height=1 width=1 VIEWASTEXT>
</object>
<object id="RDS_Subject" CLASSID="clsid:BD96C556-65A3-11D0-983A-00C04FC29E33"
        height=1 width=1 VIEWASTEXT>
</object>

<script LANGUAGE=VBScript>
<!-- #include file="../../librarysearch/adcvbs.inc" -->

Sub GetData()
   Dim strSQL, RDS
      
   If RDS_Title.ReadyState <> adcReadyStateComplete Then
      MsgBox "Query results still arriving.  Please wait...", vbInformation
   Else
      ' Retrieve the details of this title from the database
      Set RDS = RDS_Title
      RDS.ExecuteOptions = adcExecSync
      RDS.FetchOptions = adcFetchAsync
      RDS.Handler = "MSDFMAP.Handler,FmLibMap.ini"
      RDS.Server = "http://<%= Request.ServerVariables("SERVER_NAME") %>"
      RDS.Connect = "Data Source=FmLib"
      RDS.SQL = "TitleDetailLong(<%= nBibNo %>)"
      RDS.Refresh

      ' Retrieve the details of this title from the database
      Set RDS = RDS_Author
      RDS.ExecuteOptions = adcExecAsync
      RDS.FetchOptions = adcFetchAsync
      RDS.Handler = "MSDFMAP.Handler,FmLibMap.ini"
      RDS.Server = "http://<%= Request.ServerVariables("SERVER_NAME") %>"
      RDS.Connect = "Data Source=FmLib"
      RDS.SQL = "AuthorDetail(<%= nBibNo %>)"
      RDS.Refresh
           
      ' Retrieve the details of this title from the database
      Set RDS = RDS_Subject
      RDS.ExecuteOptions = adcExecAsync
      RDS.FetchOptions = adcFetchAsync
      RDS.Handler = "MSDFMAP.Handler,FmLibMap.ini"
      RDS.Server = "http://<%= Request.ServerVariables("SERVER_NAME") %>"
      RDS.Connect = "Data Source=FmLib"
      RDS.SQL = "SubjectDetail(<%= nBibNo %>)"
      RDS.Refresh
   End If
End Sub

'=== PUBDATE NOTE ---
'--- We only want to display the YEAR part of the date. We could
'--- have used "CONVERT(char(4),pubdate,112) AS pubyear" in the SQL,
'--- but RDS cannot alter the bound value and will prevent us from
'--- leaving the PubDate text box if we do so. We're forced make a copy
'--- of the expected value, and set the field by hand. No data binding
'--- can take place for the PubDate field.

SUB RDS_Title_OnReadyStateChange()
   Dim rs
   On Error Goto 0
   Set rs = RDS_Title.Recordset
   If rs.State = adcStateOpen Then
      If Not rs.EOF Then
         document.frmAddTitle.PubDate.value = rs("pubyear")
      End If
   End If
End SUB

'--- Data binding doesn't support multi-select listboxes, like the
'--- ones we use for Subject and Author lists. We have to fill those
'--- by hand when the data is returned from RDS.

SUB RDS_Author_OnReadyStateChange()
   Dim rs,sel,theOpt,strText
   On Error Goto 0
   Set rs = RDS_Author.Recordset
   If rs.State = adcStateOpen Then
      If Not rs.EOF Then
         Set sel = document.frmAddTitle.AuthNum
         Do Until rs.EOF
            strText = rs("lname")
            If rs("fname") <> "" Then strText = strText & ", " & rs("fname")
            Set theOpt = document.createElement("OPTION")
            theOpt.Text = strText
            theOpt.Value = rs("auth#")
            sel.Add theOpt
            rs.MoveNext
         Loop
      End If
   End If
End Sub

Sub RDS_Subject_OnReadyStateChange()
   Dim rs,sel,theOpt
   On Error Goto 0
   Set rs = RDS_Subject.Recordset
   If rs.State = adcStateOpen Then
      If Not rs.EOF Then
         Set sel = document.frmAddTitle.SubjNum
         Do Until rs.EOF
            Set theOpt = document.createElement("OPTION")
            theOpt.Text = rs("text")
            theOpt.Value = rs("subj#")
            sel.Add theOpt
            rs.MoveNext
         Loop
      End If
   End If
End Sub
</script>
<% End If %>

<script LANGUAGE=JavaScript>
var bDirty = false;

function SetDirty() {
   bDirty = true;
}

function CheckDirty() {
   if (bDirty)
      return ('Title information has been modified.');
}
</script>

<script Language="VBScript">
Sub Window_OnLoad()
   <% If Application("Debug") = True Then %>
   document.all.ifControl.style.display = ""
   <% End If %>
   
   <% If nBibNo > 0 Then %>
   Call GetData
   <% End If %>
   
   bDirty = False
   ShowPage 1
End Sub

Sub SubmitForm()   
   Dim theForm,theFields,item,strMissing
   Set theForm = document.frmAddTitle

   If bDirty Then
      ' Check for missing information in text fields
      theFields = Array("Title","Call","ISBN","Publisher","PubDate","Description","Notes")
      For Each item In theFields
         If Trim(theForm.Elements(item).Value) = "" Then
            strMissing = strMissing & item & vbCrLf
         End If
      Next

      If strMissing = "" Then
         If theForm.SubjNum.Length = 0 Then
            MsgBox "You must add at least one subject.", vbCritical, "Missing Subject"
            ShowPage 3
         ElseIf theForm.AuthNum.Length = 0 Then
            MsgBox "You must add at least one author.", vbCritical, "Missing Author"
            ShowPage 2
         Else
            ' Special case checks
            If Not (IsValidISBN(theForm.ISBN.Value) Or IsValidISSN(theForm.ISBN.Value)) Then
               MsgBox "You have not entered a valid ISBN or ISSN.", vbCritical, "Invalid Entry"
               ShowPage 1
               theForm.ISBN.Focus
            ElseIf Not IsValidDate(theForm.PubDate.Value) Then
               MsgBox "You have not entered a valid date.", vbCritical, "Invalid Entry"
               ShowPage 1
               theForm.PubDate.Focus
            ElseIf MissingColl Then
               MsgBox "You have not selected a collection.", vbCritical, "Invalid Entry"
               ShowPage 1
               theForm.cbBook.Focus
            Else
               ' To send the rows of a multi-select list box, its options must be selected
               For Each item In theForm.AuthNum.Options
                  item.Selected = True
               Next
               For Each item In theForm.SubjNum.Options
                  item.Selected = True
               Next

               bDirty = False    ' Don't complain during unload
               theForm.Dirty.Value = "True"
               
               ' SUCCESS: Proceed with submission
               theForm.Submit
            End If
         End If
      Else
         MsgBox "You are missing information from the following field(s):" & _
                vbCrLf & vbCrLf & strMissing & vbCrLf & "Please fill in these fields.",_
                vbCritical, "Missing Information"
         ShowPage 1
         ' Focus on the first missing element in the form
         theForm.Elements(Left(strMissing,InStr(strMissing,vbCrLf)-1)).Focus
      End If
   Else
      ' SUCCESS: No changes
      theForm.Submit
   End If
End Sub

Sub ShowPage(nPage)
   nCurrentPage = nPage
   Select Case nCurrentPage
   Case 0:
      ' Return to previous page
      document.location.href = "../Catalog.asp"
   Case 1: 
      ClearAllDivs
      Titles.style.display = ""
      WizardMid.style.display = ""
      Document.frmAddTitle.Title.Focus
   Case 2:
      ClearAllDivs
      Authors.style.display = ""
      WizardMid.style.display = ""
      Document.frmAddTitle.LName.Focus
   Case Else:
      ClearAllDivs
      Subjects.style.display = ""
      WizardEnd.style.display = ""
      Document.frmAddTitle.Text.Focus
   End Select
End Sub

Sub ClearAllDivs
   Call ClearWizardDivs
   Titles.style.display = "none"
   Authors.style.display = "none"
   Subjects.style.display = "none"
End Sub

Sub AddAuthor()
   Document.all.ifControl.src = "addAuthors.asp?Fname=" & document.all.fname.Value & "&Lname=" & document.all.lname.value
End Sub

Sub DeleteAuthors()
   Dim theSel,theOpts,src,div,i,nRet
   
   ' Confirm that an item has been selected, and that it's OK to delete it.
   Set theSel = Document.frmAddTitle.AuthNum
   If theSel.selectedIndex < 0 Then
      MsgBox "You must select an author first.", vbInformation, "Missing Input"
      nRet = vbNo
   Else
      nRet = MsgBox("Are you sure you wish to remove the selected authors?", vbQuestion + vbYesNo, "Confirm Delete")
   End If
   
   ' Continue with deletion...
   If nRet = vbYes Then
      src = "DelAuthors.asp"
      div = "?"
      Set theOpts = theSel.Options
      For i = 0 To theOpts.Length - 1
         If theOpts(i).Selected = True Then
            src = src & div & "auth=" & theOpts(i).Value
            div = "&"
         End If
      Next
      ' MsgBox src
      Document.all.ifControl.src = src
   End If
End Sub

Sub AddSubject()
   Document.all.ifControl.src = "addSubjects.asp?Text=" & document.all.Text.Value
End Sub

Sub DeleteSubjects()
   Dim theSel,theOpts,src,div,i,nRet
   
   ' Confirm that an item has been selected, and that it's OK to delete it.
   Set theSel = Document.frmAddTitle.SubjNum
   If theSel.selectedIndex < 0 Then
      MsgBox "You must select a subject first.", vbInformation, "Missing Input"
      nRet = vbNo
   Else
      nRet = MsgBox("Are you sure you wish to remove the selected subjects?", vbQuestion + vbYesNo, "Confirm Delete")
   End If
   
   ' Continue with deletion...
   If nRet = vbYes Then
      src = "DelSubjects.asp"
      div = "?"
      Set theOpts = theSel.Options
      For i = 0 To theOpts.Length - 1
         If theOpts(i).Selected = True Then
            src = src & div & "subj=" & theOpts(i).Value
            div = "&"
         End If
      Next
      ' MsgBox src
      Document.all.ifControl.src = src
   End If
End Sub

'--- Trap ENTER key and invoke appropriate ADD function
Sub Document_OnKeyPress()
   Dim nASCII
   nASCII = window.event.keyCode
   ' Check for ENTER
	IF nASCII = 13 Then
		Select Case nCurrentPage
		Case 2: Call AddAuthor
		Case 3: Call AddSubject
		End Select
   ' Check for CTRL+BKSP (formally DEL)
	ElseIf nASCII = 127 Then
		Select Case nCurrentPage
		Case 2: Call DeleteAuthors
		Case 3: Call DeleteSubjects
		End Select
	End if
End Sub

'--- Check for (hopefully) rare case when databound record doesn't
'--- match one of the pre-existing radio button choices
Function MissingColl()
   Dim theForm
   Set theForm = document.frmAddTitle
   If theForm.cbAV.Checked Or _
      theForm.cbBook.Checked Or _
      theForm.cbPrd.Checked Or _
      theForm.cbRef.Checked Or _
      theForm.cbSoft.Checked Then
      MissingColl = False
   Else
      MissingColl = True
   End If
End Function
</script>
</HEAD>

<BODY onBeforeUnload="javascript:return CheckDirty()">

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

<form NAME="frmAddTitle" ACTION="AddNewTitle.asp" METHOD=Post>
<input TYPE=Hidden NAME=Dirty VALUE="False">
<div ID="Titles" STYLE="DISPLAY: none; LEFT: 60px; POSITION: absolute; TOP: 150px; WIDTH: 550 px; Z-INDEX: 500">
   <span style="COLOR: #000000; FONT-FAMILY: Verdana,arial; FONT-WEIGHT: bold; FONT-SIZE: 12pt; TEXT-DECORATION: none">Add/Edit Title</span>

   <table DATASRC="#RDS_Title" COLS=2 CELLPADDING=0 CELLSPACING=2 BORDER=0>
	<tr ALIGN=Center><td BGCOLOR="#C0C0C0">&nbsp;Title:&nbsp;</td><td>
	<input name="Title" SIZE=60 DATAFLD="Title" onChange="javascript:SetDirty()">
	<% If nBibNo > 0 Then %>
	<input TYPE=Hidden NAME="BibNo" VALUE="<%=nBibNo%>">
	<br><font SIZE=-2><a HREF="ViewTitle.asp?bibno=<%=nBibNo%>" TARGET=_top>Click here to view this title as detail.</a></font>
	<% End If %></td></tr>
	<tr ALIGN=Center><td BGCOLOR="#C0C0C0">&nbsp;Call#:&nbsp;</td><td>
	<input name="Call" SIZE=60 DATAFLD="Call" onChange="javascript:SetDirty()"></td></tr>
	<tr ALIGN=Center><td BGCOLOR="#C0C0C0">&nbsp;ISBN or ISSN:&nbsp;</td><td>
	<input name="ISBN" SIZE=60 DATAFLD="ISBN" onChange="javascript:SetDirty()"></td></tr>
	<tr ALIGN=Center><td BGCOLOR="#C0C0C0">&nbsp;Publisher:&nbsp;</td><td>
	<input name="Publisher" SIZE=60 DATAFLD="Publisher" onChange="javascript:SetDirty()"></td></tr>
	<tr ALIGN=Center><td BGCOLOR="#C0C0C0">&nbsp;Date of Publication:&nbsp;</td><td>
	<input name="PubDate" SIZE=60 DATAFLD="<% 'NO BINDING: See note above %>" onChange="javascript:SetDirty()"></td></tr>
	<tr ALIGN=Center><td BGCOLOR="#C0C0C0">&nbsp;Physical Description:&nbsp;</td><td>
	<input name="Description" SIZE=60 DATAFLD="Description" onChange="javascript:SetDirty()"></td></tr>
	<tr ALIGN=Center><td BGCOLOR="#C0C0C0">&nbsp;Notes:&nbsp;</td><td>
	   <textarea name="Notes" COLS=44 ROWS=5 DATAFLD="Notes" onChange="javascript:SetDirty()"></textarea></td></tr>
	<tr ALIGN=Center><td BGCOLOR="#C0C0C0">&nbsp;Collection:&nbsp;</td><td>
	   <font SIZE=-2>
	   <input name="Coll" ID=cbAV   TYPE=Radio VALUE="AV" DATAFLD="Coll" onClick="javascript:SetDirty()"><LABEL FOR=cbAV>Audio/Visual</label>&nbsp;
	   <input name="Coll" ID=cbBook TYPE=Radio VALUE="Book" DATAFLD="Coll" onClick="javascript:SetDirty()" CHECKED><LABEL FOR=cbBook>Book</label>&nbsp;
	   <input name="Coll" ID=cbPrd  TYPE=Radio VALUE="Prd" DATAFLD="Coll" onClick="javascript:SetDirty()"><LABEL FOR=cbPrd>Periodical</label>&nbsp;
	   <input name="Coll" ID=cbRef  TYPE=Radio VALUE="Ref" DATAFLD="Coll" onClick="javascript:SetDirty()"><LABEL FOR=cbRef>Reference</label>&nbsp;
	   <input name="Coll" ID=cbSoft TYPE=Radio VALUE="Soft" DATAFLD="Coll" onClick="javascript:SetDirty()"><LABEL FOR=cbSoft>Software</label>
	   </font>
	</td></tr>
	</table>
</div>

<div ID="Authors"  STYLE="DISPLAY: none; LEFT: 60px; POSITION: absolute; TOP: 150px; WIDTH: 550 px; Z-INDEX: 5">
   <span style="COLOR: #000000; FONT-FAMILY: Verdana,arial; FONT-WEIGHT: bold; FONT-SIZE: 12pt; TEXT-DECORATION: none">Assign Authors</span>
   <table COLS=2 CELLPADDING=0 CELLSPACING=2 BORDER=0 WIDTH="100%">
   <tr><td COLSPAN=2>Last, First Name: <input name=LName SIZE=20>,
   <input name=FName SIZE=20> &nbsp;&nbsp; 
   <input TYPE=Button VALUE="Add Author" onClick="AddAuthor()"> </td></tr>
   <tr><td COLSPAN=2>
   <select NAME="AuthNum" SIZE=14 MULTIPLE STYLE="WIDTH: 100%" onChange="javascript:SetDirty()">
   <% ' EMPTY: Filled by RDS_Author if updating %>
   </select></td></tr>
   <tr><td><font SIZE=-2>Multi-select by using CTRL+click or SHIFT+click.</font></td>
   <td align=right><input type=button VALUE="Delete Selected Authors" onClick="DeleteAuthors()">
   </td></tr>
   </table>
</div>

<div ID="Subjects" STYLE="DISPLAY: none; LEFT: 60px; POSITION: absolute; TOP: 150px; WIDTH: 550 px; Z-INDEX: 5">
   <span style="COLOR: #000000; FONT-FAMILY: Verdana,arial; FONT-WEIGHT: bold; FONT-SIZE: 12pt; TEXT-DECORATION: none">Assign Subjects</span>
   <table COLS=2 CELLPADDING=0 CELLSPACING=2 BORDER=0 WIDTH="100%">
   <tr><td COLSPAN=2>Subject: <input NAME="Text" SIZE=50> &nbsp;&nbsp;
   <input TYPE=Button VALUE="Add New Subject" onClick="AddSubject()"> </td></tr>
   <tr><td COLSPAN=2>
   <select NAME="SubjNum" SIZE=14 MULTIPLE STYLE="WIDTH: 100%" onChange="javascript:SetDirty()">
   <% ' EMPTY: Filled by RDS_Subject if updating %>
   </select></td></tr>
   <tr><td><font SIZE=-2>Multi-select by using CTRL+click or SHIFT+click.</font></td>
   <td align=right><input type=button VALUE="Delete Selected Subjects" onClick="DeleteSubjects()">
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
