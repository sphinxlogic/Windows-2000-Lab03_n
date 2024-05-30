<%@ LANGUAGE = VBScript %>
<%  Option Explicit     %>

<% 
	' Create and Set Variables that will be used in populating
	' the form.  In a typical application, these values would come
	' from a database or text file.

	Dim strFirstName
	Dim strLastName
	Dim strAddress1
	Dim strAddress2
	Dim blnInfo

	strFirstName = "John"
	strLastName = "Doe"
	strAddress1 = "1 Main Street"
	strAddress2 = "Nowhere ZA, 12345"
%>

<HTML>
    <HEAD>
        <TITLE>PopulateForm Sample</TITLE>
    </HEAD>

    <BODY BGCOLOR="White" topmargin="10" leftmargin="10">


        <!-- Display Header -->

        <font size="4" face="Arial, Helvetica">
        <b>PopulateForm Sample</b></font><br>
      
        <hr size="1" color="#000000">


		<FORM ACTION="">
		
		<!-- Use ASP variables to fill out the form -->

		<P>First Name: <INPUT TYPE="TEXT" NAME="FNAME" VALUE="<%=strFirstName%>"></p>
		<P>Last Name: <INPUT TYPE="TEXT" NAME="LNAME" VALUE="<%=strLastName%>"></p>
		<P>Street: <INPUT TYPE="TEXT" NAME="STREET" VALUE="<%=strAddress1%>"></p>
		<P>City State, Zip: <INPUT TYPE="TEXT" NAME="FNAME" VALUE="<%=strAddress2%>"></p>	

    </BODY>
</HTML>
