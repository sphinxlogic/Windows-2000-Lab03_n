<%@ LANGUAGE = VBScript %>
<%  Option Explicit     %>

<%
	' Ensure that this page is not cached
	Response.Expires = 0
%>

<HTML>
    <HEAD>
        <TITLE>Using Application Variables</TITLE>
    </HEAD>

    <BODY BGCOLOR="White" topmargin="10" leftmargin="10">

        <!-- Display Header -->

        <font size="4" face="Arial, Helvetica">
        <b>Using Application Variables</b></font><br>
      
        <hr size="1" color="#000000">


        <%
            ' If this is the first time any user has visited
            ' the page, initialize Application Value

            If (Application("AppPageCountVB") = "") Then
                Application("AppPageCountVB") = 0
            End If


            ' Increment the Application AppPageCount by one.
            ' Note that this AppPageCount value is being
            ' shared, locking must be used to prevent 
            ' two sessions from simultaneously attempting 
            ' to update the value.

            Application.Lock
            Application("AppPageCountVB") = Application("AppPageCountVB") + 1
            Application.UnLock
        %>


        <!-- Output the Application Page Counter Value -->
        <!-- Note that locking does not need to be used -->
        <!-- because the value is not being changed by -->
        <!-- this user session -->

        Users have visited this page 
        <%=Application("AppPageCountVB")%> times!


        <!-- Provide a link to revisit the page -->

        <p><A href = "Application_VBScript.asp">Click here to visit it again</A>

    </BODY>
</HTML>
