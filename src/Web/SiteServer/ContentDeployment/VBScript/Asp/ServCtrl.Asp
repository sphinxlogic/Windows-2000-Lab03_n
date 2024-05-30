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
<B>Service Control</B>
</CENTER>

<%
	On Error Resume Next

	Call InitializeServer()
%>

<%
	If (Request.Form("ServiceControl") <> "") Then
		If ( Request.Form("START") = "Start CRS" ) Then
			Call Response.Write( "Starting CRS Service...<BR>")
			CrsSrv.Start
			Call ErrorDisplay("when starting CRS")
		End IF

		If ( Request.Form("STOP") = "Stop CRS" ) Then
			Call Response.Write( "Stoping CRS Service...<BR>")
			CrsSrv.Stop
			Call ErrorDisplay("when stoping CRS")
		End IF

		If ( Request.Form("PAUSE") = "Pause CRS" ) Then
			Call Response.Write( "Pausing CRS Service...<BR>")
			CrsSrv.Pause
			Call ErrorDisplay("when pausing CRS")
		End IF

		If ( Request.Form("CONTINUE") = "Continue CRS" ) Then
			Call Response.Write( "Continuing CRS Service...<BR>")
			CrsSrv.Continue
			Call ErrorDisplay("when continuing CRS")
		End IF

	End If
%>

<BR><HR><BR>
<FORM METHOD=POST ACTION=servctrl.asp>
<INPUT TYPE=HIDDEN NAME="ServiceControl" VALUE="yes" >
<INPUT TYPE=SUBMIT NAME="START" 	 VALUE="Start CRS">
<INPUT TYPE=SUBMIT NAME="STOP" 		 VALUE="Stop CRS">
<INPUT TYPE=SUBMIT NAME="PAUSE" 	 VALUE="Pause CRS">
<INPUT TYPE=SUBMIT NAME="CONTINUE" 	 VALUE="Continue CRS">

</FORM>

<HR>
<BR><A HREF=default.htm>Return HOME</A>
</BODY>
</HTML>

<%
	'Clear out the Server Object
	Set CrsSrv = Nothing
	Call ErrorDisplay("setting CrsSrv to Nothing")
%>

