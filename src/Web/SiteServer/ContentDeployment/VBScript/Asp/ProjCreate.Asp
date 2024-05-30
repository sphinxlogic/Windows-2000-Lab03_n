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
<B> Create Project Example </B>
</CENTER>

<%
	On Error Resume Next

	Call InitializeServer()
%>

<%
	On Error Resume Next

	If Request.Form("PostProject") <> "" Then
		On Error Resume Next
		Err.Clear
		Flags = 0

		If Request.Form("ProjectName") = "" Then 
			Call Response.Write( "No Project Name Defined" )
		Else
			Set Project = CrsSrv.OpenProject ( Request.Form("ProjectName"), 1 )
			Call ErrorDisplay("when opening a new project")
		End If

		If Request.Form("LocalDirectory") = "" Then 
			Call Response.Write( "No Local Directory Defined")
		Else
			Project.LocalDirectory = Request.Form("LocalDirectory")
			Call ErrorDisplay("when adding local directory")
		End If

		'Setup the Flags
		If Request.Form("FastMode") = "on" 	Then Flags = Flags + &H80
		If Request.Form("Incremental") = "on" 	Then Flags = Flags + &H40
		If Request.Form("Force") = "on" 	Then Flags = Flags + &H8
		If Request.Form("ACLs") = "on" 		Then Flags = Flags + &H2
		If Request.Form("Route") = "on" 	Then Flags = Flags + &H200
		If Request.Form("Notify") = "on" 	Then Flags = Flags + &H400
		If Request.Form("Automatic") = "on" 	Then Flags = Flags + &H100
		If Request.Form("DirsOnly") = "on" 	Then Flags = Flags + &H4
		If Request.Form("Permit") = "on" 	Then Flags = Flags + &H10

		'If there are flags defined then set them
		If Flags > 0 Then
			Project.Flags = Flags
			Call ErrorDisplay("when adding the flags")
		End If

		If Request.Form("Comment") <> "" Then
			VarComment = Request.Form("Comment")
			Project.Put "Comments", VarComment
			Call ErrorDisplay ("when adding comments")
		End If

		Project.ReplicationMethod = "SENDINET"
		Call ErrorDisplay ("when setting Replicaion Method")

		If Request.Form("Destination") <> "" Then
			Project.AddDestination(Request.Form("Destination"))
			Call ErrorDisplay("when adding desintations")
		End If

		Project.Commit
		Call ErrorDisplay("when adding the project")
		If Err.Number <> 0 Then
			Call ErrorDisplay("when adding the project")
		Else
			Call Response.Write( "<B>Project " + Request.Form("ProjectName") + " was created!</B><BR>" )
		End If

		Set Project=Nothing
		Call ErrorDisplay("setting project to nothing")
	End If
%>

<BR><HR><BR>

<!-- Create This page with a table, and part of the table is the
	Flags, and the other is general information	-->

<FORM METHOD=POST ACTION=ProjCreate.asp>
<TABLE BORDER=0 WIDTH=500> <TR> <TD>
<INPUT TYPE=HIDDEN NAME="PostProject" VALUE="yes" >
	<P>Project Name &nbsp;
	<INPUT TYPE=text SIZE="24" NAME="ProjectName">

	<P>Local Directory
	<INPUT TYPE=text SIZE="24" NAME="LocalDirectory">

	<P>Destination &nbsp; &nbsp; &nbsp;
	<INPUT TYPE=text SIZE="24" NAME="Destination">

	<P>Comment &nbsp; &nbsp; &nbsp; &nbsp;
	<INPUT TYPE=text SIZE="24" NAME="Comment">

</TD> <TD>
	<INPUT TYPE=CHECKBOX NAME="FastMode">FastMode<p>
	<INPUT TYPE=CHECKBOX NAME="Incremental">Incremental<p>
	<INPUT TYPE=CHECKBOX NAME="Force">Force<p>
	<INPUT TYPE=CHECKBOX NAME="ACLs">ACLs<P>
	<INPUT TYPE=CHECKBOX NAME="Route">Route<P>
	<INPUT TYPE=CHECKBOX NAME="Notify">Notify<P>
	<INPUT TYPE=CHECKBOX NAME="Automatic">Automatic<P>
	<INPUT TYPE=CHECKBOX NAME="DirsOnly">DirsOnly<P>
	<INPUT TYPE=CHECKBOX NAME="Permit">Permit<P>
</TD> </TR> </TABLE>

<P>
<INPUT TYPE=SUBMIT VALUE="Create Project"> <INPUT TYPE=RESET VALUE="Reset Project">

</FORM>

<BR><A HREF=default.htm>Return HOME</A>

</BODY>
</HTML>

<%
	'Clear out the Server Object
	Set CrsSrv = Nothing
	Call ErrorDisplay("Setting server to Nothing")
%>

