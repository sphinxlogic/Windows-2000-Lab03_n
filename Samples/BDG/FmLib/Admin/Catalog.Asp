<%@ Language=VBScript %>
<% ' Copyright 1998-1999 Microsoft Corp. All rights reserved. %>
<% Option Explicit %>
<% If Session("CatalogSQL") = "" Then Response.Redirect "CFilter.asp" %>
<HTML>
<HEAD>
<META name=VI60_DTCScriptingPlatform content="Client (IE 4.0 DHTML)">
<TITLE>Library Catalog</TITLE>
<META NAME="GENERATOR" Content="Microsoft Visual Studio 6.0">
</HEAD>
<BODY topMargin=20 leftMargin=20 rightMargin=20 bottomMargin=30>
<% ' VI 6.0 Scripting Object Model Enabled %>
<!--#include file="../_ScriptLibrary/pm.asp"-->
<% if StartPageProcessing() Then Response.End() %>
<FORM name=thisForm METHOD=post>

<link type="text/css" rel="stylesheet" href="../_Themes/fm/theme.css">	
<img class="logo" SRC="../images/fmlogo.gif" WIDTH="187" HEIGHT="90">
<img class="sublogo" SRC="../images/Fmcorplib.gif" WIDTH="180" HEIGHT="18"> 
<!-- #include file= "Navigation.asp"-->

<script LANGUAGE="JavaScript">
function EditLink() {
   var title = Recordset1.fields.getValue('title');
   title = title.replace(/&/g,'&amp;').replace(/</g,'&lt;').replace(/>/g,'&gt;');
   return '<a HREF="AdNMat/AddTitles.asp?bibno=' + Recordset1.fields.getValue('bib#') + '">' + title + '</a>';
}

function AddNewTitle() {
     document.location.href="adnMat/AddTitles.asp";
}

function LinkItems() {
   return '<a HREF="ADNMat/AddItems.asp?bibNo=' + Recordset1.fields.getValue('bib#') + '">' + Recordset1.fields.getValue('n_items') + '</a>';  
}

function CollIcon() {
   return '<img SRC="../Images/Icon' + Recordset1.fields.getValue('coll') + '.gif" WIDTH=12 HEIGHT=12>'
}

</script>


<div ID="Items" STYLE="LEFT: 20px; POSITION: absolute; TOP: 130px; WIDTH: 95%; Z-INDEX: 5">
   <span style="COLOR: #000000; FONT-FAMILY: Verdana,arial; FONT-SIZE: 12pt; FONT-WEIGHT: bold; TEXT-DECORATION: none">Library Catalog</span>
   
   <table COLS=2 WIDTH=95% CELLSPACING=4 CELLPADDING=0 BORDER=0>
   <tr><td><font SIZE=-2>Select a <strong>Title</strong> to edit title information. 
   Select the <strong>Items</strong> number to edit or add new items.</font>
   </td><td ALIGN=Right><input type="button" value="Add New Titles" width = "60" onClick="AddNewTitle()" id=button1 name=button1><br>
   </td></tr>
   </table>
   
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:9CF5D7C2-EC10-11D0-9862-0000F8027CA0" id=Recordset1 style="LEFT: 0px; TOP: 0px">
   <PARAM NAME="ExtentX" VALUE="12197">
   <PARAM NAME="ExtentY" VALUE="2090">
   <PARAM NAME="State" VALUE="(TCConn=\qFmLib\q,TCDBObject_Unmatched=\qSQL\sStatement\q,TCDBObjectName_Unmatched=\q\l%=\sSession(\q\qCatalogSQL\q\q)\s%\g\q,TCControlID_Unmatched=\qRecordset1\q,TCPPConn=\qFmLib\q,TCPPDBObject=\qTables\q,TCPPDBObjectName=\qtitle\q,RCDBObject=\qRCSQLStatement\q,TCSQLStatement_Unmatched=\q\l%=\sSession(\q\qCatalogSQL\q\q)\s%\g\q,TCCursorType=\q3\s-\sStatic\q,TCCursorLocation=\q3\s-\sUse\sclient-side\scursors\q,TCLockType=\q1\s-\sRead\sOnly\q,TCCacheSize_Unmatched=\q100\q,TCCommTimeout_Unmatched=\q30\q,CCPrepared=0,CCAllRecords=1,TCNRecords_Unmatched=\q10\q,TCODBCSyntax_Unmatched=\q\q,TCHTargetPlatform=\q\q,TCHTargetBrowser_Unmatched=\qClient\s(IE\s4.0\sDHTML)\q,TCTargetPlatform=\qInherit\sfrom\spage\q,RCCache=\qRCBookPage\q,CCOpen=1,GCParameters=(Rows=0))">
   <PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
<SCRIPT LANGUAGE="JavaScript" src="../_ScriptLibrary/EventMgr.HTM"></SCRIPT>
<SCRIPT LANGUAGE="JavaScript" src="../_ScriptLibrary/Recordset.HTM"></SCRIPT>
<SCRIPT LANGUAGE="JavaScript">
function _initRecordset1()
{
	Recordset1.setRecordSource('<%=escape(Application("FmLib_ConnectionString") + ";User Id=" + Application("FmLib_RuntimeUserName") + ";PASSWORD=" + Application("FmLib_RuntimePassword"))%>', '<%= Session("CatalogSQL") %>');
	Recordset1.open();

}
CreateRecordset('Recordset1', _initRecordset1, null);
</SCRIPT>

<!--METADATA TYPE="DesignerControl" endspan-->
<!--METADATA TYPE="DesignerControl" startspan
<OBJECT classid="clsid:277FC3F2-E90F-11D0-B767-0000F81E081D" height=147 id=Grid1 style="HEIGHT: 147px; LEFT: 0px; TOP: 0px; WIDTH: 459px" 
   width=459>
   <PARAM NAME="_ExtentX" VALUE="12144">
   <PARAM NAME="_ExtentY" VALUE="3889">
   <PARAM NAME="DataConnection" VALUE="">
   <PARAM NAME="SourceType" VALUE="">
   <PARAM NAME="Recordset" VALUE="Recordset1">
   <PARAM NAME="CtrlName" VALUE="Grid1">
   <PARAM NAME="UseAdvancedOnly" VALUE="0">
   <PARAM NAME="AdvAddToStyles" VALUE="-1">
   <PARAM NAME="AdvTableTag" VALUE='WIDTH="100%"'>
   <PARAM NAME="AdvHeaderRowTag" VALUE="">
   <PARAM NAME="AdvHeaderCellTag" VALUE="">
   <PARAM NAME="AdvDetailRowTag" VALUE="">
   <PARAM NAME="AdvDetailCellTag" VALUE="">
   <PARAM NAME="ScriptLanguage" VALUE="0">
   <PARAM NAME="ScriptingPlatform" VALUE="1">
   <PARAM NAME="EnableRowNav" VALUE="0">
   <PARAM NAME="HiliteColor" VALUE="">
   <PARAM NAME="RecNavBarHasNextButton" VALUE="-1">
   <PARAM NAME="RecNavBarHasPrevButton" VALUE="-1">
   <PARAM NAME="RecNavBarNextText" VALUE="   >   ">
   <PARAM NAME="RecNavBarPrevText" VALUE="   <   ">
   <PARAM NAME="ColumnsNames" VALUE='"=CollIcon()","=EditLink()","=LinkItems()","call","ISBN","pubdate","publisher"'>
   <PARAM NAME="columnIndex" VALUE="0,1,2,3,4,5,7">
   <PARAM NAME="displayWidth" VALUE="24,198,68,45,45,45,60">
   <PARAM NAME="Coltype" VALUE="1,1,1,1,1,1,1">
   <PARAM NAME="formated" VALUE="0,0,0,0,0,0,0">
   <PARAM NAME="DisplayName" VALUE='"&nbsp;","Title","Items","Call Number","ISBN","Published","Publisher"'>
   <PARAM NAME="DetailAlignment" VALUE=",,,,,,">
   <PARAM NAME="HeaderAlignment" VALUE=",,,,,,">
   <PARAM NAME="DetailBackColor" VALUE=",,,,,,">
   <PARAM NAME="HeaderBackColor" VALUE=",,,,,,">
   <PARAM NAME="HeaderFont" VALUE=",,,,,,">
   <PARAM NAME="HeaderFontColor" VALUE=",,,,,,">
   <PARAM NAME="HeaderFontSize" VALUE=",,,,,,">
   <PARAM NAME="HeaderFontStyle" VALUE=",,,,,,">
   <PARAM NAME="DetailFont" VALUE=",,,,,,">
   <PARAM NAME="DetailFontColor" VALUE=",,,,,,">
   <PARAM NAME="DetailFontSize" VALUE=",,,,,,">
   <PARAM NAME="DetailFontStyle" VALUE=",,,,,,">
   <PARAM NAME="ColumnCount" VALUE="7">
   <PARAM NAME="CurStyle" VALUE="Basic Navy">
   <PARAM NAME="TitleFont" VALUE="Arial">
   <PARAM NAME="titleFontSize" VALUE="-1">
   <PARAM NAME="TitleFontColor" VALUE="16777215">
   <PARAM NAME="TitleBackColor" VALUE="13416">
   <PARAM NAME="TitleFontStyle" VALUE="1">
   <PARAM NAME="TitleAlignment" VALUE="0">
   <PARAM NAME="RowFont" VALUE="Arial">
   <PARAM NAME="RowFontColor" VALUE="0">
   <PARAM NAME="RowFontStyle" VALUE="0">
   <PARAM NAME="RowFontSize" VALUE="-2">
   <PARAM NAME="RowBackColor" VALUE="16777215">
   <PARAM NAME="RowAlignment" VALUE="0">
   <PARAM NAME="HighlightColor3D" VALUE="268435455">
   <PARAM NAME="ShadowColor3D" VALUE="268435455">
   <PARAM NAME="PageSize" VALUE="10">
   <PARAM NAME="MoveFirstCaption" VALUE="    |<    ">
   <PARAM NAME="MoveLastCaption" VALUE="    >|    ">
   <PARAM NAME="MovePrevCaption" VALUE="    <<    ">
   <PARAM NAME="MoveNextCaption" VALUE="    >>    ">
   <PARAM NAME="BorderSize" VALUE="1">
   <PARAM NAME="BorderColor" VALUE="13421772">
   <PARAM NAME="GridBackColor" VALUE="8421504">
   <PARAM NAME="AltRowBckgnd" VALUE="12632256">
   <PARAM NAME="CellSpacing" VALUE="0">
   <PARAM NAME="WidthSelectionMode" VALUE="1">
   <PARAM NAME="GridWidth" VALUE="459">
   <PARAM NAME="EnablePaging" VALUE="-1">
   <PARAM NAME="ShowStatus" VALUE="-1">
   <PARAM NAME="StyleValue" VALUE="429033">
   <PARAM NAME="LocalPath" VALUE="../"></OBJECT>
-->
<script language="JavaScript" src="../_ScriptLibrary/Button.HTM"></script>
<script language="JavaScript" src="../_ScriptLibrary/RSNavBar.HTM"></script>
<script language="JavaScript" src="../_ScriptLibrary/DataGrid.HTM"></script>
<SCRIPT LANGUAGE=JavaScript>
function _initGrid1()
{
Grid1.pageSize = 10;
Grid1.setDataSource(Recordset1);
Grid1.tableAttributes = 'WIDTH="100%" cellpadding=2  cellspacing=0 bordercolor=#cccccc bgcolor=Gray border=1 cols=7 rules=ROWS nowrap';
Grid1.headerAttributes = '   bgcolor=#003468 align=Left nowrap';
Grid1.headerWidth[0] = '';
Grid1.headerWidth[1] = '';
Grid1.headerWidth[2] = '';
Grid1.headerWidth[3] = '';
Grid1.headerWidth[4] = '';
Grid1.headerWidth[5] = '';
Grid1.headerWidth[6] = '';
Grid1.headerFormat = '<Font face="Arial" size=-1 color=White> <b>';
Grid1.colHeader[0] = '\'&nbsp;\'';
Grid1.colHeader[1] = '\'Title\'';
Grid1.colHeader[2] = '\'Items\'';
Grid1.colHeader[3] = '\'Call Number\'';
Grid1.colHeader[4] = '\'ISBN\'';
Grid1.colHeader[5] = '\'Published\'';
Grid1.colHeader[6] = '\'Publisher\'';
Grid1.rowAttributes[0] = '  bgcolor = White align=Left nowrap  bordercolor=#cccccc';
Grid1.rowAttributes[1] = '  bgcolor = Silver align=Left nowrap  bordercolor=#cccccc';
Grid1.rowFormat[0] = ' <Font face="Arial" size=-2 color=Black >';
Grid1.colAttributes[0] = ' ';
Grid1.colFormat[0] = '<Font Size=-2 Face="Arial" Color=Black >';
Grid1.colData[0] = 'CollIcon()';
Grid1.rowFormat[1] = ' <Font face="Arial" size=-2 color=Black >';
Grid1.colAttributes[1] = ' ';
Grid1.colFormat[1] = '<Font Size=-2 Face="Arial" Color=Black >';
Grid1.colData[1] = 'EditLink()';
Grid1.colAttributes[2] = ' ';
Grid1.colFormat[2] = '<Font Size=-2 Face="Arial" Color=Black >';
Grid1.colData[2] = 'LinkItems()';
Grid1.colAttributes[3] = ' ';
Grid1.colFormat[3] = '<Font Size=-2 Face="Arial" Color=Black >';
Grid1.colData[3] = 'Recordset1.fields.getValue(\'call\')';
Grid1.colAttributes[4] = ' ';
Grid1.colFormat[4] = '<Font Size=-2 Face="Arial" Color=Black >';
Grid1.colData[4] = 'Recordset1.fields.getValue(\'ISBN\')';
Grid1.colAttributes[5] = ' ';
Grid1.colFormat[5] = '<Font Size=-2 Face="Arial" Color=Black >';
Grid1.colData[5] = 'Recordset1.fields.getValue(\'pubdate\')';
Grid1.colAttributes[6] = ' ';
Grid1.colFormat[6] = '<Font Size=-2 Face="Arial" Color=Black >';
Grid1.colData[6] = 'Recordset1.fields.getValue(\'publisher\')';
Grid1.navbarAlignment = 'Right';
var objPageNavbar = Grid1.showPageNavbar(170,1);
objPageNavbar.getButton(0).value = '    |<    ';
objPageNavbar.getButton(1).value = '    <<    ';
objPageNavbar.getButton(2).value = '    >>    ';
objPageNavbar.getButton(3).value = '    >|    ';
Grid1.hasPageNumber = true;
}
	CreateDataGrid('Grid1',_initGrid1);
</SCRIPT>



<!--METADATA TYPE="DesignerControl" endspan-->
</div>
<% ' VI 6.0 Scripting Object Model Enabled %>
<% EndPageProcessing() %>
</FORM>
</BODY>
</HTML>
