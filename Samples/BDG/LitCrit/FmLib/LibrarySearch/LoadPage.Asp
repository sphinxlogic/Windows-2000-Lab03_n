<%@ Language=VBScript %>
<% ' Copyright 1998-1999 Microsoft Corporation. All rights reserved. %>
<% Response.Expires = 0
   '--- Set SRC of IFRAME and redirect to search page.
   Session("LastPage") = UrlDecode(Request.QueryString)
   Response.Redirect "library.asp"
%>
<script Language=VBScript RunAt=Server>
Function UrlDecode(url)
   temp = url
   x = InStr(temp,"%")
   Do While x > 0
      UrlDecode = UrlDecode & Left(temp,x-1)
      UrlDecode = UrlDecode & Chr(CLng("&H" & Mid(temp,x+1,2)))
      temp = Mid(temp,x+3)
      x = InStr(temp,"%")
   Loop
   UrlDecode = UrlDecode + temp
End Function
</script>