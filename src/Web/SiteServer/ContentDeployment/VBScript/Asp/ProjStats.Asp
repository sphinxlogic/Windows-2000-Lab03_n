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
<!-- This allows for getting stats from the Com interface on defined projects
-->

<%
	On Error Resume Next

	Call InitializeServer()
%>

<CENTER>
<BR> <b> Enumerate Projects with Enum</b> <BR>
</CENTER>
<BR><HR><BR>

<TABLE BORDER=1 CELLSPACING=5 CELLPADDING=5 BGCOLOR=WHITE BORDERCOLORDARK=GRAY BORDERCOLORLIGHT=SILVER>
<TR><TH>Name of Project to get stats </TH></TR>

<%
	Iterator = 0
	Err.Clear

	On Error Resume Next
	set Project = CrsSrv.EnumProjects( Iterator )

	while (Err.Number = 0)
		'Get the project Name and write it to the Table, then clear the object to continue enumeration.
		Name   = Project.Name
		Call ErrorDisplay ("getting project Name")

		Call Response.Write( "<TR><TD> <A HREF=ProjStats.asp?Project=" & Name & ">" & Name & "</A> </TD><TR>")
		Set Project = Nothing
		Call ErrorDisplay ("deleting object project")

		set Project = CrsSrv.EnumProjects( Iterator )
	Wend
	Err.Clear
%>
</TABLE>

<%
	If Request.QueryString("Project") <> "" Then
		Call Response.Write ("<BR><HR><CENTER>")
		Call Response.Write ("Stats for <B>" & Request.QueryString("Project") & "</B></CENTER><BR>")

		'Open the project to get to the replication info.
		Err.Clear
		Set Project = CrsSrv.OpenProject(Request.QueryString("Project"), 2)
		Call ErrorDisplay ("when opening project <B>" & Request.QueryString("Project") & "</B>")

		Iterator = 0
		Set Replication = Project.EnumReplications( 0, Iterator)
		If (Err.Number <> 0) Then
			Call Response.Write ("No Replications have been run<BR>")
		End If

		While (Err.Number = 0)
			Replication.Query
			Call ErrorDisplay ("when querying replication")

			'Enumerate Replicaiton information
			Call Response.Write ( "State =" 		& Replication.State & "<BR>")
			Call Response.Write ( "ID =" 			& Replication.ID & "<BR>")			
			Call Response.Write ( "Bytes Received =" 	& Replication.BytesReceived & "<BR>")
			Call Response.Write ( "Bytes Sent =" 		& Replication.BytesSent & "<BR>")
			Call Response.Write ( "Files Errored =" 	& Replication.FilesErrored & "<BR>")
			Call Response.Write ( "Files Errored Bytes =" 	& Replication.FilesErroredBytes & "<BR>")
			Call Response.Write ( "Files Matched =" 	& Replication.FilesMatched & "<BR>")
			Call Response.Write ( "Files Matched Bytes ="	& Replication.FilesMatchedBytes & "<BR>")
			Call Response.Write ( "Files Received =" 	& Replication.FilesReceived & "<BR>")
			Call Response.Write ( "Files Sent =" 		& Replication.FilesSent & "<BR>")
			Call Response.Write ( "Starting Time =" 	& Replication.StartTime & "<BR>")
			Call Response.Write ( "Ending Time =" 	& Replication.EndTime & "<BR>")

			'Setup for the next Project.
			Call Response.Write ("<BR><HR><BR>")

			Set Replication = Project.EnumReplication( 0, Iterator)
		Wend

		'Clear this error since this is an enumeration error
		Err.Clear

		'Clear the Project Object
		Set Project = Nothing
		Call ErrorDisplay("when setting project to Nothing")

	End If

%>

<A HREF=default.htm>Return HOME</A>

</BODY>
</HTML>

<%
	'Clear out the Server Object
	CrsSrv = Nothing
%>


