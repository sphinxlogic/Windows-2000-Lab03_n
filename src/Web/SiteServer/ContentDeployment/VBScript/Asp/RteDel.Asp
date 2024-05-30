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
<B> Delete Route Example </B>
</CENTER>

<%
	On Error Resume Next

	Call InitializeServer()
%>

<%
	If Request.QueryString("Route") <> "" Then

		CrsSrv.DeleteRoute(Request.QueryString("Route"))

		If (Err.Number <> 0) Then
			Call ErrorDisplay("deleting route " + Request.QueryString("Route"))
		Else
			Call Response.Write("<B> Successfully deleted route " + Request.QueryString("Route") + "</B><BR>")
		End If
	End If
%>

<!-- Create This page with a table, and part of the table is the
	Flags, and the other is general information	-->

<BR><HR><BR>

<FORM METHOD=POST ACTION=rtedel.asp>

<TABLE BORDER=1 CELLSPACING=5 CELLPADDING=5 BGCOLOR=WHITE BORDERCOLORDARK=GRAY BORDERCOLORLIGHT=SILVER>
<TR> <TH>Name</TH> <TH>Base Directory</TH> <TH>Delete?</TH> </TR>

<%
	'Initialize Variables
	Iterator = 0

	set Route = CrsSrv.EnumRoutes( Iterator )

	while (Err.Number = 0)

		Name   = Route.Name
		Dir    = Route.BaseDirectory
		DeleteStr = "<input type=BUTTON name=" & Name & " value=" & Name & " language=VBScript onclick=""Window.location.href = 'rtedel.asp?Route=" & Name & "'"">"
		'DeleteStr = "<A HREF=RouteDelete.asp?Route=" + Name + "> Delete? </A>"
		Call Response.Write( "<TR> <TD>" & Name & "</TD> <TD>" & Dir & "</TD> <TD>" & DeleteStr & "</TD> </TR>")

		Set Route = Nothing
		Call ErrorDisplay("setting Route to Nothing")

		set Route = CrsSrv.EnumRoutes( Iterator )
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
	Call ErrorDisplay("Setting CrsSrv to Nothing")
%>

