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

<%
	Public CrsSrv
%>

<SCRIPT LANGUAGE="VBScript"  RUNAT=Server>
Function ErrorDisplay (vString)
	if (Err.Number <> 0) Then
		Call Response.Write( "Error <B>" & Hex(Err.Number) & "</B> Message=<B>" & Err.Description & "</B> " & vString & "<BR>")
		Err.Clear
	End If
End Function
</SCRIPT>

<SCRIPT LANGUAGE="VBScript"  RUNAT=Server>
Function InitializeServer ()

	'Initialize the server and return an error if applicable
	set CrsSrv = Server.CreateObject("CrsApi.ReplicationServer")
	CrsSrv.Initialize ("")
	Call ErrorDisplay("Initializing Server")

End Function
</SCRIPT>

