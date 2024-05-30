<!--
---------------------------------------------------------------------------
 (C) Copyright 1997-1998 Microsoft Corporation.  All Rights Reserved.

 THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
 ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
 THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 PARTICULAR PURPOSE.
---------------------------------------------------------------------------
-->

<!--#include file="code.asp"-->

<HTML>
<BODY>
<!-- This page will list out the current Projects that are defined on this machine -->

<%
	On Error Resume Next

	Call InitializeServer()
%>
<b>NOTE: Click on project name to start project replication</b>
<BR>
<BR>
<CENTER>
<BR> <b> Enumerate Projects with Enum</b> <BR>
</CENTER>
<BR>
<TABLE BORDER=1 CELLSPACING=5 CELLPADDING=5 BGCOLOR=WHITE BORDERCOLORDARK=GRAY BORDERCOLORLIGHT=SILVER>
<TR> <TH>Name</TH> <TH>Method</TH> <TH>Destinations</TH> <TH>Local Directory</TH> <TH>Flags</TH> <TH>Comments</TH> </TR>

<%
	Iterator = 0
	Err.Clear

	set Project = CrsSrv.EnumProjects( Iterator )

	while (Err.Number = 0)

		'Initialize the local Variables	
		EnumIterator = 0
		Destination = ""
		Dir = ""
		Method = ""
		Comment = ""

		while (Err.Number = 0)
			Value = Project.Enum(EnumIterator, Parameter)
			
			if (Err.Number = 0) Then
				if(Parameter = "LocalDirectory") Then Dir = Value
				if(Parameter = "ReplicationMethod") Then Method = Value
				if(Parameter = "Comments") Then Comment = Value
				if(Parameter = "Flags") Then Flags = Value
				if(Parameter = "Destination") Then
					For Count = 0 to UBound(Value)
						Destination = Destination + Value(Count) + " "
						if(Err.Number <> 0 ) Then
							Err.Clear
							Exit For
						End If
					Next
				End If
			End If
		Wend
		Err.Clear
		
		Name   = Project.Name

		Call Response.Write( "<TR> <TD> <A HREF=ProjList.asp?Project=" & Name & ">" & Name & "</A> </TD> <TD>" & Method & "</TD> <TD>" & Destination & "</TD> <TD>" & Dir & "</TD> <TD>" & Flags & "</TD> <TD>" & Comment & "</TD><TR>")

		Set Project = Nothing
		Call ErrorDisplay("setting project to nothing")

		set Project = CrsSrv.EnumProjects( Iterator )
	Wend
	Err.Clear
%>
</TABLE>

<CENTER>
<BR> <b> Enumerate Projects </b> <BR>
</CENTER>
<BR>
<TABLE BORDER=1 CELLSPACING=5 CELLPADDING=5 BGCOLOR=WHITE BORDERCOLORDARK=GRAY BORDERCOLORLIGHT=SILVER>
<TR> <TH>Name</TH> <TH>Method</TH> <TH>Destinations</TH> <TH>Local Directory</TH> <TH>Flags</TH> <TH>Comments</TH> </TR>

<%
	Iterator = 0
	Err.Clear

	set Project = CrsSrv.EnumProjects( Iterator )

	while (Err.Number = 0)

		'Initialize the local Variables	
		DestIterator = 0
		Destination = ""
		Comment = ""

		Name   = Project.Name
		Method = Project.ReplicationMethod
		Dir = Project.LocalDirectory
		Comment = Project.Get("Comments")
		Flags = Project.Flags

		'Throw this error out since an invalid field will just leave a blank in the table.
		'Call ErrorDisplay("Getting Values")
		Err.Clear

		while (Err.Number = 0)
			Destination = Destination + Project.EnumDestination(DestIterator) + " "
		Wend
		Err.Clear

		Call Response.Write( "<TR> <TD> <A HREF=ProjList.asp?Project=" & Name & ">" & Name & "</A> </TD> <TD>" & Method & "</TD> <TD>" & Destination & "</TD> <TD>" & Dir & "</TD> <TD>" & Flags & "</TD> <TD>" & Comment & "</TD> <TR>")

		Set Project = Nothing
		Call ErrorDisplay("setting project to nothing")

		set Project = CrsSrv.EnumProjects( Iterator )
	Wend
	Err.Clear
%>
</TABLE>
<CENTER>
<BR> <b> Enumerate Projects using GET method</b> <BR>
</CENTER>
<BR>
<TABLE BORDER=1 CELLSPACING=5 CELLPADDING=5 BGCOLOR=WHITE BORDERCOLORDARK=GRAY BORDERCOLORLIGHT=SILVER>
<TR> <TH>Name</TH> <TH>Method</TH> <TH>Destinations</TH> <TH>Local Directory</TH> <TH>Flags</TH> <TH>Comments</TH> </TR>

<%
	Iterator = 0
	Err.Clear

	set Project = CrsSrv.EnumProjects( Iterator )

	while (Err.Number = 0)

		'Initialize the local Variables	
		DestIterator = 0
		Destination = ""
		Comment = ""

		Name   = Project.Name
		Method = Project.Get("ReplicationMethod")
		Dir = Project.Get("LocalDirectory")
		Comment = Project.Get("Comments")
		Flags = Project.Get("Flags")

		'Throw this error out since an invalid field will just leave a blank in the table.
		'Call ErrorDisplay("Getting Values")
		Err.Clear


		while (Err.Number = 0)
			Destination = Destination + Project.EnumDestination(DestIterator) + " "
		Wend
		Err.Clear

		Call Response.Write( "<TR> <TD> <A HREF=ProjList.asp?Project=" & Name & ">" & Name & "</A> </TD> <TD>" & Method & "</TD> <TD>" & Destination & "</TD> <TD>" & Dir & "</TD> <TD>" & Flags & "</TD> <TD>" & Comment & "</TD> <TR>")

		Set Project = Nothing
		Call ErrorDisplay("setting project to nothing")

		set Project = CrsSrv.EnumProjects( Iterator )
	Wend
	Err.Clear
%>
</TABLE>
<BR><BR>
<%
	If Request.QueryString("Project") <> "" Then
		Call Response.Write ("<BR><HR>")
		Call Response.Write ("Starting project <B>" & Request.QueryString("Project") & "</B>...<BR>")

		'Open the project to get to the replication info.
		Err.Clear
		Set Project = CrsSrv.OpenProject(Request.QueryString("Project"), 2)
		Call ErrorDisplay ("when opening project <B>" & Request.QueryString("Project") & "</B>")

		Set Replication = Project.Start(0)
		Call ErrorDisplay ("when starting project <B>" & Request.QueryString("Project") & "</B>")

		LocalStartTime = Replication.StartTime
		Call ErrorDisplay ("when retrieving start time for project <B>" & Request.QueryString("Project") & "</B>")
		Call Response.Write ("Project <B>" & Request.QueryString("Project") & "</B> started at " & LocalStartTime & "<BR>")
	
		'Clear the Project and Replication Objects
		Set Project = Nothing
		Set Replication = Nothing
		Call ErrorDisplay ("when setting project to Nothing")

	End If

%>

<BR><BR>
<A HREF=default.htm>Return HOME</A>

</BODY>
</HTML>

<%
	'Clear out the Server Object
	Set CrsSrv = Nothing
	Call ErrorDisplay("setting CrsSrv to nothing")
%>

