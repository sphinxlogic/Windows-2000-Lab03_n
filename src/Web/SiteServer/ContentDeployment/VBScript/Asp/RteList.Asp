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

<%
	On Error Resume Next

	Call InitializeServer()
%>

<CENTER>
<BR> <b> Enumerate Routes through Enum</b> <BR>
</CENTER>
<BR>

<TABLE BORDER=1 CELLSPACING=5 CELLPADDING=5 BGCOLOR=WHITE BORDERCOLORDARK=GRAY BORDERCOLORLIGHT=SILVER>
<TR> <TH>Route</TH> <TH>Base Directory</TH> <TH>Destination</TH> </TR>

<%
	Iterator = 0
	Err.Number = 0

	set Route = CrsSrv.EnumRoutes( Iterator )

	while (Err.Number = 0)
	
		'Initialize Local Variables
		Name   = Route.Name
		EnumIterator = 0
		Destination = ""

		while (Err.Number = 0)
			Value = Route.Enum( EnumIterator, Parameter )
			if (Err.Number = 0) Then
				if (Parameter = "BaseDirectory") Then Dir = Value
				if (Parameter = "Destination" ) Then
					For Count = 0 to UBound(Value)
						Destination = Destination + Value(Count) + " "
						if (Err.Number <> 0 ) Then
							Err.Clear
							Exit For
						End If
					Next
				End If
			End If
		Wend
		Err.Clear

		Call Response.Write( "<TR> <TD>" & Name & "</TD> <TD>" & Dir & "</TD> <TD>" & Destination & "</TD> </TR>")

		Set Route = Nothing
		Call ErrorDisplay("setting Route to Nothing")

		set Route = CrsSrv.EnumRoutes( Iterator )
	Wend
	Err.Clear

	Set Route = Nothing
	Call ErrorDisplay("setting route to Nothing")

%>
</TABLE>
<BR>
<CENTER>
<BR> <b> Enumerate Routes </b> <BR>
</CENTER>
<BR>

<TABLE BORDER=1 CELLSPACING=5 CELLPADDING=5 BGCOLOR=WHITE BORDERCOLORDARK=GRAY BORDERCOLORLIGHT=SILVER>
<TR> <TH>Route</TH> <TH>Base Directory</TH> <TH>Destination</TH> </TR>

<%
	Iterator = 0

	set Route = CrsSrv.EnumRoutes( Iterator )

	while (Err.Number = 0)
		'Initialize Local Variables	
		Name   = Route.Name
		Dir = Route.BaseDirectory
		Destination = ""
		DestIterator = 0

		while (Err.Number = 0)
			Destination = Destination + Route.EnumDestination(DestIterator) + " "
		Wend
		Err.Clear

		Call Response.Write( "<TR> <TD>" & Name & "</TD> <TD>" & Dir & "</TD> <TD>" & Destination & "</TD> </TR>")

		Set Route = Nothing
		Call ErrorDisplay("setting Route to Nothing")

		set Route = CrsSrv.EnumRoutes( Iterator )
	Wend
	Err.Clear	

	Set Route = Nothing
	Call ErrorDisplay("setting route to Nothing")
%>
</TABLE>

<BR><A HREF=default.htm>Return HOME</A>

</BODY>
</HTML>

<%
	'Clear out the Server Object
	Set CrsSrv = Nothing
	Call ErrorDisplay("setting CrsSrv to Nothing")
%>

