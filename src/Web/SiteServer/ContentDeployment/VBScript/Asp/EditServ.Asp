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
<BR> <b>Enumerate globals with Enum</b> <BR>
</CENTER>
<BR>

<%
	On Error Resume Next

	Call InitializeServer()
%>

<%
	'Process The list on the form and see if there are any differences.
	If (Request.Form("PostGlobal") <> "") Then
		Iterator = 0
		Err.Clear

		'Enum the list, if there are differences then set the differences with a put.
		While (Err.Number = 0)
			Value = CrsSrv.Enum( Iterator, Parameter )
			If (Err.Number = 0 ) Then
				StringSend = Parameter
				If ( UCase(Request.Form(Parameter)) <> UCase(Value) ) Then
					Call Response.Write( "Updating " & Chr(34) & Parameter & Chr(34) & " from <B>" & Chr(34) & Value & Chr(34) & "</B> to <B>" & Chr(34) & Request.Form(Parameter) & Chr(34) & "</B><BR>")

					'Now write the new value and then commit the change.
					' CrsSrv.Put Parameter, Request.Form(Parameter)
					'If it is a number make it a long, else leave it as a string
					If (IsNumeric(Request.Form(Parameter)) ) Then 
						NewValue = CLng(Request.Form(Parameter))
					Else
						NewValue = Request.Form(Parameter)
					End If
					CrsSrv.Put Parameter, NewValue
					Call ErrorDisplay ("when setting " & Parameter & " to " & Request.Form(Parameter) )

					CrsSrv.Commit
					Call ErrorDisplay ("when commiting")

				End If
			End IF
		Wend
		Err.Clear
	End If
%>

<BR><HR><BR>
<FORM METHOD=POST ACTION=EditServ.asp>
<TABLE BORDER=1 CELLSPACING=5 CELLPADDING=5 BGCOLOR=WHITE BORDERCOLORDARK=GRAY BORDERCOLORLIGHT=SILVER>
<TR> <TH>Enviroment Name</TH> <TH>Value</TH> </TR>

<%
	Iterator = 0
	Err.Clear

	'Enum the list and put the values in the table.
	While (Err.Number = 0)
		Value = CrsSrv.Enum( Iterator, Parameter )
		If (Err.Number = 0 ) Then
			Call Response.Write( "<TR> <TD>" & Parameter & "</TD> <TD> <INPUT TYPE=TEXT NAME=" & Chr(34) & Parameter & Chr(34) & " VALUE=" & Chr(34) & Value & Chr(34) & "> </TD> </TR>")
		End IF
	Wend
	Err.Clear
%>
</TABLE>
<BR>
<INPUT TYPE=HIDDEN NAME="PostGlobal" VALUE="yes" >
<INPUT TYPE=SUBMIT VALUE="Change Globals">
<INPUT TYPE=RESET VALUE="Reset Project">
<BR>
</FORM>
<BR><A HREF=default.htm>Return HOME</A><BR>
</BODY>
</HTML>

<%
	'Clear out the Server Object
	Set CrsSrv = Nothing
	Call ErrorDisplay("setting crssrv to nothing")
%>

