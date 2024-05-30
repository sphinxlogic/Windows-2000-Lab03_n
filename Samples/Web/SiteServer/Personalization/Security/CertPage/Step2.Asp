<%@ LANGUAGE="VBScript" %>
<%
'####################################################################
'                                                                     
'   Microsoft Site Server v3.00                                   
'                                                                     
'   Copyright (c) 1997-98 Microsoft Corporation.  All rights reserved.   
'
' THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
' ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
' THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
' PARTICULAR PURPOSE.
'
'####################################################################
%>

<!--#include file=LogToFile.txt-->
<!--#include file=CertPageError.txt-->
<% Response.Buffer = TRUE %>

<HTML>
<HEAD>
<BASEFONT FACE="Arial, Helvetica" SIZE="2">
<TITLE>Certificate Signup Page</TITLE>
</HEAD>
<CENTER>
<FONT FACE="Arial, Helvetica" SIZE="4">
Certificate Signup Page
</FONT>
</CENTER>

<BR>
<%
On Error Resume Next
Server.ScriptTimeout = 10000

' This page cannot be called directly.
If Session("InProcess") <> 1 Then
  ErrorOut("This page cannot be called directly.")
End if


' Sub to add value to multivalued attribute
Sub AddToAttribute(AttrName, AttrValue)
    On Error Resume Next
	Dim MayContainArr
	MayContainArr = Session("AUO").Get(AttrName)
	if (Err<>0) then
		Err = 0
		REM Add the first value to the thing
		Session("AUO").Put AttrName,Array(AttrValue)
	else
		TopNum = UBound(MayContainArr)
		if Err <> 0 then
			Err = 0	
			REM Add a second value to the thing
			Session("AUO").Put AttrName,Array(MayContainArr, AttrValue)
		else
			REM Add a new value to the list of values
			ReDim Preserve MayContainArr(TopNum+1)
			MayContainArr(TopNum+1) = AttrValue			
			Session("AUO").Put AttrName,(MayContainArr)
		end if
	end if
end sub

If Request.ClientCertificate("SUBJECT") = "" or Request.ClientCertificate("ISSUER") = "" Then
  ErrorOut("The Certificate Subject and/or Issuer were empty. Cannot create certificate hash.")
End if

set x = Server.CreateObject("Membership.verifusr.1")
y = x.HashCert(Request.ClientCertificate("SUBJECT"),Request.ClientCertificate("ISSUER"))
AddToAttribute "userCertificateHash", y
Session("AUO").setinfo
%>
<p>
The certificate has been stored in your account to facilitate easy credentials mapping.<BR>
</p>
<BR>
The specified certificate will map to the following credentials:
<BR><BR>
User name: <b> <%=Session("UserName")%> </b>
<BR>
User GUID: <b> <%=Session("AUO").Get("GUID")%> </b>
<p>
The certificate subject: <b> <%=Request.ClientCertificate("SUBJECT")%> </b>
</p>
<p>
The certificate issuer: <b> <%=Request.ClientCertificate("ISSUER")%> </b>
</p>
<br>
</BODY>

</HTML>
