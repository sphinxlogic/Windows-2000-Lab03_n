<%@ LANGUAGE = VBScript %>
<%  Option Explicit     %>

<%
	' Changes to the HTTP response header, in which cookies
	' are sent back to the client, must be made before
	' sending any data to the user.
	
	Response.Expires = 0
		
	
	' Get the last visit date/time string from the cookie that
	' resides in the http request header.
	
	Dim LastVisitCookie
	LastVisitCookie = Request.Cookies("CookieVBScript")
	
	
	' Send the current date/time string in a cookie enclosed
	' in the response header.  Note that because IE now uses
	' case-sensitive cookie paths, we have explicitly set
	' the cookie path to be that of the url path to this
	' page.  By default, the path would be that of the
	' IIS Application context for this page ("IISSAMPLES")
	
	Response.Cookies("CookieVBScript") = FormatDateTime(NOW)
	Response.Cookies("CookieVBScript").Path = "/IIsSamples"
%>


<HTML>
    <HEAD>
		<TITLE>Using Cookies</TITLE>
    </HEAD>

    <BODY BGCOLOR="White" topmargin="10" leftmargin="10">

    	<font size="4" face="Arial, Helvetica">
    	<b>Using Cookies</b></font><br>
      
        <hr size="1" color="#000000">
		
		<%		
			If (LastVisitCookie = "") Then
			
				' The cookie has never been set. This must
				' be the user's first visit to this page.
				
				Response.Write("Welcome to this page.")
			Else

				' Remind the user of the last time she/he
				' visited this page.

				Response.Write("You last visited this page on " + LastVisitCookie)
			End If		
		%>

		<p><A href="Cookie_VBScript.asp">Revisit This Page</A>

	</BODY>
</HTML>
