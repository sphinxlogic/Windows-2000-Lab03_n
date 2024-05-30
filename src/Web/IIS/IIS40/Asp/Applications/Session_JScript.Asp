<%@ LANGUAGE = JScript %>

<%
	// Ensure that this page is not cached
	Response.Expires = 0;
%>

<HTML>
    <HEAD>
        <TITLE>Using Session Variables</TITLE>
    </HEAD>

    <BODY BGCOLOR="White" topmargin="10" leftmargin="10">

        <!-- Display Header -->

        <font size="4" face="Arial, Helvetica">
        <b>Using Session Variables</b></font><br>
      
        <hr size="1" color="#000000">

        <%
            // If this is the first time a user has visited
            // the page, initialize Session Value

            if (Session("SessionCountJScript") == null) 
            {
                Session("SessionCountJScript") = 0;
            }


            // Increment the Session PageCount by one.
            // Note that this PageCount value is only
            // for this user's individual session

            Session("SessionCountJScript") = Session("SessionCountJScript") + 1;
        %>


        <!-- Output the Session Page Counter Value -->

        You have personally visited this page 
        <%=Session("SessionCountJScript")%> times.


        <!-- Provide a link to revisit the page -->

        <p><A href = "Session_JScript.asp">Click here to visit it again</A>

    </BODY>
</HTML>
