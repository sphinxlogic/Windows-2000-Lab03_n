<%@ LANGUAGE = JScript 	%>


<%
	// Because the Expiration Information is sent in the HTTP
	// headers, it must be set before any HTML is transmitted

	// Ensure that this page expires within 10 minutes...	
	Response.Expires = 10;
	
	// ...or before Jan 1, 1999, which ever comes first
	Response.ExpiresAbsolute="Jan 1,1999 13:30:15";
%>


<HTML>
    <HEAD>
        <TITLE>Setting Expiration Information</TITLE>
    </HEAD>

	<BODY BGCOLOR="White" topmargin="10" leftmargin="10">

		<!-- Display Header -->

		<font size="4" face="Arial, Helvetica">
		<b>Setting Expiration Information</b></font><br>
      
		<hr size="1" color="#000000">

		<p>This page will expire from your browser's cache in
		10 minutes.  If it is after Jan. 1, 1999 (1:30 PM), then
		the page will expire from the cache immediately.
		
	</BODY>
</HTML>
