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
<!-- This page will list out the current Projects that are defined on this machine -->

<%
	On Error Resume Next

	Call InitializeServer()
%>

<CENTER>
<BR> <b> Enumerate Replications</b> <BR>
</CENTER>
<BR>

<%
	Iterator = 0

	Set RepInfo = CrsSrv.EnumReplications ("", 0, Iterator)
	If (Err.Number = 0) Then
		'Display the table
		Call Response.Write ("<TABLE BORDER=1 CELLSPACING=5 CELLPADDING=5 BGCOLOR=WHITE BORDERCOLORDARK=GRAY BORDERCOLORLIGHT=SILVER>")
		Call Response.Write ("<TR><TH>Name</TH> <TH>State</TH></TR>")
	Else
		Call Response.Write ("There were no Run Replications!<BR>")
	End If

	While (Err.Number =0)
		Name = RepInfo.Name
		ErrorDisplay("get name")
		State = RepInfo.State
		ErrorDisplay("get state info")
		Call Response.Write("<TR><TH>" & Name & "</TH><TH>" & State &"</TH></TR>")

		Set RepInfo = CrsSrv.EnumReplications ("", 0, Iterator)
	Wend
	Err.Clear

%>
</TABLE>

<BR><A HREF=default.htm> Return HOME</A>

</BODY>
</HTML>

