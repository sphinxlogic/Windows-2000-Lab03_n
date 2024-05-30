<%@ LANGUAGE = VBScript %>
<%  Option Explicit		%>


<HTML>
    <HEAD>
        <TITLE>Using the Browser Capabilities Component</TITLE>
    </HEAD>

    <BODY BGCOLOR="White" topmargin="10" leftmargin="10">


        <!-- Display Header -->

        <font size="4" face="Arial, Helvetica">
        <b>Using the Browser Capabilities Component</b></font><br>
      
        <hr size="1" color="#000000">


        <!-- Create a BrowserType Object -->

        <%
			Dim bc
			Set bc = Server.CreateObject("MSWC.BrowserType")
		%>


        <!-- Output a table describing the capabilities -->
        <!-- of a user's browser-->

        <Table border=1>

            <tr>
            <td>Browser Name</td>
            <td> <%=bc.Browser %> </Td>

            <tr>
            <td>Browser Version</td>            
            <td> <%=bc.Version %> </Td>

            <tr>
            <td>Major Version</td>
            <td> <%=bc.Majorver %> </Td>

            <tr>
            <td>Minor Version</td>
            <td> <%=bc.Minorver %> </Td>

            <tr>
            <td>Frame Support</td>
            <td> <%=bc.Frames %> </Td>

            <tr>
            <td>Table Support</td>
            <td> <%=bc.Tables %> </Td>

            <tr>
            <td>Cookie Support</td>
            <td> <%=bc.Cookies %> </Td>

            <tr>
            <td>Background Sound Support</td>
            <td> <%=bc.BackgroundSounds %> </Td>

            <tr>
            <td>VBScript Support</td>
            <td> <%=bc.VBScript %> </Td>

            <tr>
            <td>JavaScript Support</td>
            <td> <%=bc.JavaScript %> </Td>

        </table>
    </BODY>
</HTML>
