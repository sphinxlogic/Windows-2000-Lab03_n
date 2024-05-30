<%@ Language=VBScript %>
<% ' Copyright Microsoft 1998-1999.  All rights reserved. %>
<% '--- Set SRC of IFRAME and redirect to search page.
   Session("LastPage") = "details.asp?" & Request.QueryString
   Response.Redirect "../../librarysearch/library.asp"
%>