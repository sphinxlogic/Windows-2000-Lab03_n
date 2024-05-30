<!--
//====================================================================
//                                                                     
//   Microsoft Site Server v3.00                                   
//                                                                     
//   Copyright (c) 1997-98 Microsoft Corporation.  All rights reserved.   
//   THIS CODE AND INFORMATION IS PROVIDED 'AS IS' WITHOUT WARRANTY OF
//   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//   PARTICULAR PURPOSE.
//=====================================================================
-->

<!--#include file="code.asp"-->

<HTML>
<BODY>

<CENTER>
<B> Delete Project Example </B>
</CENTER>

<%
	On Error Resume Next

	Call InitializeServer()
%>

<%
	If Request.QueryString("Project") <> "" Then
	' Setup the page for PRE Post information

		Err.Clear

		CrsSrv.DeleteProject(Request.QueryString("Project"))

		If (Err.Number <> 0) Then
			Call ErrorDisplay("Deleting Project " + Request.QueryString("Project"))
		Else
			Call Response.Write("<B> Successfully deleted project " + Request.QueryString("Project") + "</B><BR>")
		End If
	End If
%>

<!-- Create This page with a table, and part of the table is the
	Flags, and the other is general information	-->

<BR><HR><BR>

<FORM METHOD=POST ACTION=ProjDel.asp>

<TABLE BORDER=1 CELLSPACING=5 CELLPADDING=5 BGCOLOR=WHITE BORDERCOLORDARK=GRAY BORDERCOLORLIGHT=SILVER>
<TR> <TH>Name</TH> <TH>Method</TH> <TH>Local Directory</TH> <TH>Delete?</TH> </TR>

<%
	Iterator = 0
	Err.Clear

	On Error Resume Next
	set Project = CrsSrv.EnumProjects( Iterator )

	while (Err.Number = 0)
	
		Name   = Project.Name
		Method = Project.ReplicationMethod
		Dir    = Project.LocalDirectory

		DeleteStr = "<input type=BUTTON name=" & Name & " value=" & Name & " language=VBScript onclick=""Window.location.href = 'projdel.asp?Project=" & Name & "'"">"
		Call Response.Write( "<TR> <TD>" & Name & "</TD> <TD>" & Method & "</TD> <TD>" & Dir & "</TD> <TD>" & DeleteStr & "</TD> </TR>")

		Set Project = Nothing
		Call ErrorDisplay("setting project to nothing")

		set Project = CrsSrv.EnumProjects( Iterator )
	Wend
	Err.Clear
%>

</TABLE>
</FORM>

<BR><A HREF=default.htm> Return HOME</A>

</BODY>
</HTML>

<%
	'Clear out the Server Object
	Set CrsSrv = Nothing
	Call ErrorDisplay("setting CrsSrv to nothing")
%>

