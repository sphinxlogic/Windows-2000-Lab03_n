<%@ Language=VBScript %>
<% ' Copyright 1998-1999 Microsoft Corp. All rights reserved. %>
<% Option Explicit %>
<% Response.Buffer = True %>
<!-- #include file="AdNMat/Verify.asp" -->
<% Dim item,strSQL,nColls,strAnd,strFilter

   If (UCase(Request.ServerVariables("HTTP_METHOD")) = "POST") Then
   
      'TESTING!
      Response.Write "<h1>Testing</h1>" & _
                     "<strong>Turn off application debugging to hide these messages.</strong><br><br>"
      For Each item In Request.Form
         Response.Write "<b>" & item & "</b>: " & Request.Form(item) & "<br>"
      Next
      
      '--- Start with basic query (same fields every time!)
      strSQL = "SELECT t.bib#,t.title,t.coll,t.call,t.isbn,t.publisher," & _
               "t.n_items,convert(char(4),t.pubdate,112) as pubyear " & _
               "FROM title AS t"
      strAnd = " WHERE "
      
      '--- Select from specified collections...
      nColls = Request.Form("cbColl").Count
      If nColls > 0 And nColls < 5 Then
         ' Replace converts "X, Y" to "X','Y"
         strSQL = strSQL & strAND & "t.coll IN ('" & _
                  Replace(Request.Form("cbColl"),", ","','") & "')"
         strAND = " AND "
      End If
      
      '--- Include items with zero items?
      If LCase(Request.Form("cbAll")) <> "on" Then
         strSQL = strSQL & strAND & "t.n_items>0"
         strAND = " AND "
      ElseIf nColls = 0 Then
         strSQL = strSQL & strAND & "t.n_items=0"
         strAND = " AND "
      End If
      
      '--- Searching for <title>?
      strFilter = Request.Form("txtTitle")
      If Not (IsEmpty(strFilter) Or strFilter="") Then
         Dim oSearch
         Set oSearch = Server.CreateObject("CML.Search")
         oSearch.SearchType = ftsContains
         oSearch.SearchString = strFilter
         strSQL = strSQL & strAnd & "CONTAINS(t.Title,'" & oSearch.SearchString & "')"
         strAND = " AND "
      End If
      
      '--- Searching for items earlier than <date>?
      strFilter = Request.Form("txtPubDate")
      If Not (IsEmpty(strFilter) Or strFilter="") Then
         'Assume date checking has been performed by the client
         strSQL = strSQL & strAnd & "t.pubdate>='" & strFilter & "'"
         strAND = " AND "
      End If
      
      '--- Set sort order
      Select Case Request.Form("cbSortBy")
      Case "Title":   strSQL = strSQL & " ORDER BY t.Title"
      Case "PubDate": strSQL = strSQL & " ORDER BY t.PubDate DESC,t.Title"
      Case Else:      strSQL = strSQL & " ORDER BY t." & Request.Form("cbSortBy") & ",t.Title"
      End Select
      
      '--- SAVE SQL IN SESSION (prepare it for embedding in JavaScript)
      Session("CatalogSQL") = Replace(strSQL,"'","\'")
      
      If Application("Debug") Then
         Response.Write "<br>CatalogSQL = " & Session("CatalogSQL") & "<br><br>"
         Response.Write "<a HREF=catalog.asp>Click here to continue forward to catalog.</a>"
         Response.End
      Else
         '--- Continue forward to catalog page
         Response.Redirect "Catalog.asp"
      End If
   End If
%>

<HTML>
<HEAD>
<TITLE>Library Catalog (Select Filter)</TITLE>
<META NAME="GENERATOR" Content="Microsoft Visual Studio 6.0">
</HEAD>
<BODY>

<link type="text/css" rel="stylesheet" href="../_Themes/fm/theme.css">	
<img class="logo" SRC="../images/fmlogo.gif" WIDTH="187" HEIGHT="90">
<img class="sublogo" SRC="../images/Fmcorplib.gif" WIDTH="180" HEIGHT="18"> 
<!-- #include file= "Navigation.asp"-->

<div class=menui>
<TABLE border=0 class="watermark" height=250 width=200 CELLSPACING=0 CELLPADDING=0>
<TR vAlign=top><TD>
   <TABLE class=admin WIDTH=75% BORDER=0 CELLSPACING=2 CELLPADDING=2>
   <TR>
      <TD BGCOLOR=#ce6300 valign=top ALIGN=center NOWRAP id=mI>Administration</TD>
   </TR>
   </TABLE></TD>
</TR>
</TABLE>
</div>

<script LANGUAGE=VBScript>
Function SubmitForm()
   Dim theForm
   Set theForm = document.frmFilter
   
   SubmitForm = True 
   
   If theForm.txtPubDate.Value <> "" Then
      If Not IsValidDate(theForm.txtPubDate.Value) Then
         MsgBox "Invalid date entered."
         theForm.txtPubDate.Focus
         SubmitForm = False
      End If
   End If

End Function
</script>

<div ID="Items" STYLE="POSITION: absolute; LEFT: 20px; TOP: 120px; WIDTH: 95%; Z-INDEX: 5">
   <span style="COLOR: #000000; FONT-FAMILY: Verdana,arial; FONT-WEIGHT: bold; FONT-SIZE: 12pt; TEXT-DECORATION: none">Catalog Filter</span>

<FORM NAME=frmFilter ACTION="<%= Request.ServerVariables("SCRIPT_NAME") %>" METHOD=POST
      onSubmit="javascript:return SubmitForm()">
<table COLS=2 BORDER=0 CELLSPACING=2 CELLPADDING=0 WIDTH="80%" ALIGN=Center>

<tr><td COLSPAN=2 ALIGN="Right"><input TYPE=Submit VALUE="View Library Catalog"></td></tr>
<tr><td COLSPAN=2><font SIZE=-1>&nbsp;</font></td></tr>

<tr BGCOLOR="#C0C0C0"><th COLSPAN=2 ALIGN=Left>Include</th></tr>

<tr><td>
<input NAME="cbColl" ID="cbAV" VALUE="AV" TYPE="checkbox" CHECKED>
<img onClick="flipSelection(cbAV)" src="../images/iconav.gif" width=12 height=12>&nbsp;
<LABEL FOR="cbAV"   TITLE="Include Audio and Video">Audio/Visual</LABEL>
<br>

<input NAME="cbColl" ID="cbBook" VALUE="Book" TYPE="checkbox" CHECKED>
<img onClick="flipSelection(cbBook)" src="../images/iconbook.gif" width=12 height=12>&nbsp;
<LABEL FOR="cbBook" TITLE="Include Books (Hard/Softcover)">Books</LABEL>
<br>

</td><td>

<input NAME="cbColl" ID="cbPrd" VALUE="Prd" TYPE="checkbox" CHECKED>
<img onClick="flipSelection(cbPrd)" src="../images/iconprd.gif" width=12 height=12>&nbsp;
<LABEL FOR="cbPrd"  TITLE="Include Magazines and Journals">Periodicals</LABEL>
<br>

<input NAME="cbColl" ID="cbRef" VALUE="Ref" TYPE="checkbox" CHECKED>
<img onClick="flipSelection(cbRef)" src="../images/iconref.gif" width=12 height=12>&nbsp;
<LABEL FOR="cbRef"  TITLE="Include Non-Circulating Materials">Reference</LABEL>
<br>

<input NAME="cbColl" ID="cbSoft" VALUE="Soft" TYPE="checkbox" CHECKED>
<img onClick="flipSelection(cbSoft)" src="../images/iconsoft.gif" width=12 height=12>&nbsp;
<LABEL FOR="cbSoft" TITLE="Include Computer Programs">Software</LABEL>
</td></tr>

<tr><td COLSPAN=2>
<input NAME="cbAll" ID="cbAll" TYPE="checkbox">
<LABEL FOR="cbAll" TITLE="Include materials with 0 items">Titles without items</LABEL>
</td></tr>

<tr><td COLSPAN=2><font SIZE=-1>&nbsp;</font></td></tr>
<tr BGCOLOR="#C0C0C0"><th COLSPAN=2 ALIGN=Left>Filters</th></tr>

<tr><td>
Where <strong>Title</strong> contains:</td><td>
<input NAME="txtTitle" SIZE=30 MAXLENGTH=50 TITLE="Leave blank to view all records">
</td></tr>

<tr><td>
Where <strong>PubDate</strong> is at least:</td><td>
<input NAME="txtPubDate" VALUE="<%= Year(DateAdd("yyyy",-5,Date)) %>" SIZE=30 MAXLENGTH=20 TITLE="Leave blank to view all records">
</td></tr>

<tr><td COLSPAN=2><font SIZE=-1>&nbsp;</font></td></tr>
<tr BGCOLOR="#C0C0C0"><th COLSPAN=2 ALIGN=Left>Sort By</th></tr>

<tr><td COLSPAN=2>
<input NAME="cbSortBy" ID="cbTitle" VALUE="Title" TYPE=Radio CHECKED>
<LABEL FOR="cbTitle" TITLE="Sort by Title">Title</LABEL>
<br>

<input NAME="cbSortBy" ID="cbCollection" VALUE="Coll" TYPE=Radio>
<LABEL FOR="cbCollection" TITLE="Sort by type of materials">Collection</LABEL>
<br>

<input NAME="cbSortBy" ID="cbItemCount" VALUE="n_Items" TYPE=Radio>
<LABEL FOR="cbItemCount" TITLE="Sort by number of items">Item Count</LABEL>
<br>

<input NAME="cbSortBy" ID="cbPubdate" VALUE="PubDate" TYPE=Radio>
<LABEL FOR="cbPubdate" TITLE="Sort by date of publication">Date published (latest works first)</LABEL>
</td></tr>

</table>
</FORM>
</div>

<script LANGUAGE=VBScript>
'--- Changes the status of a single checkbox
Sub flipSelection(oSel)
   oSel.checked = Not oSel.checked
End Sub
</script>

</BODY>
</HTML>
