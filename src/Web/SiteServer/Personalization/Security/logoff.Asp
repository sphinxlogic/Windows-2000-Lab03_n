<% Response.Buffer = true %>
<%
    ' (C) Copyright 1998 Microsoft Corporation. All Rights Reserved.
    ' THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
    ' ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
    ' THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
    ' PARTICULAR PURPOSE.
%>

<%
  set x = Server.CreateObject("Membership.verifusr.1")
  y = x.CancelCookie("FormsAuth")
%>

<HTML>
You have been logged off.
</HTML>

