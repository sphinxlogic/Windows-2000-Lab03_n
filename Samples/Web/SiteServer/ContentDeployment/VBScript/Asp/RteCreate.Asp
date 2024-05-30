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
<B> Create Route Example </B>
</CENTER>

<%
	On Error Resume Next

	Call InitializeServer()
%>

<%
	If Request.Form("PostRoute") <> "" Then
		Flags = 0

		If Request.Form("RouteName") = "" Then 
			Call Response.Write( "No route name defined<BR>" )
		Else
			Set Route = CrsSrv.AddRoute ( Request.Form("RouteName") )
			Call ErrorDisplay("when opening a new route " + Request.Form("RouteName"))
		End If

		If Request.Form("BaseDirectory") = "" Then 
			Call Response.Write( "No base directory defined<BR>")
		Else
			RouteBase = Request.Form("BaseDirectory")
			Route.BaseDirectory = RouteBase
			Call ErrorDisplay("when adding base directory " + Request.Form("BaseDirectory"))
		End If

		If Request.Form("Destination") <> "" Then
			Route.AddDestination(Request.Form("Destination"))
			Call ErrorDisplay("when adding desintations " + Request.Form("Destination"))
		End If

		Route.Commit
		If Err.Number <> 0 Then
			Call ErrorDisplay("when adding the route")
		Else
			Call Response.Write( "<B>Route " + Request.Form("ProjectName") + " was created!</B><BR>" )
		End If

		Set Route = Nothing
		Call ErrorDisplay("setting route to nothing")
	End If
%>

<BR><HR><BR>

<FORM METHOD=POST ACTION=rtecreate.asp>
<INPUT TYPE=HIDDEN NAME="PostRoute" VALUE="yes" >
	<P>Route Name &nbsp;
	<INPUT TYPE=text SIZE="24" NAME="RouteName">

	<P>Base Directory
	<INPUT TYPE=text SIZE="24" NAME="BaseDirectory">

	<P>Destination &nbsp; &nbsp; &nbsp;
	<INPUT TYPE=text SIZE="24" NAME="Destination">

<P>
<INPUT TYPE=SUBMIT VALUE="Create Route"> <INPUT TYPE=RESET VALUE="Reset Route">

</FORM>

<BR><A HREF=default.htm>Return HOME</A>

</BODY>
</HTML>

<%
	'Clear out the Server Object
	Set CrsSrv = Nothing
	Call ErrorDisplay("setting CrsSrv to nothing")
%>

