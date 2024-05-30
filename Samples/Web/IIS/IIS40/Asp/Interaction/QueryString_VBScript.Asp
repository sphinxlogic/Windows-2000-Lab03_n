<% @Language=VBScript	%>
<% Option Explicit		%>


<HTML>
    <HEAD>
        <TITLE>Form Posting (Get Method with QueryString)</TITLE>
    </HEAD>

    <BODY bgcolor="white" topmargin="10" leftmargin="10">
        
		<!-- Display Header -->

		<font size="4" face="Arial, Helvetica">
		<b>Form Posting (Get Method with QueryString)</b></font> 

		<br><hr><p>

		This page will take the information entered in the form
		fields, and use the GET method to send the data to an
		ASP page.

		<FORM Name=Form1 METHOD=GET ACTION="QueryString_VBScript.asp">
		
			First Name: <Input Type=Text Name=fname><p>
			Last Name: <Input Type=Text Name=lname><p>
			
			<INPUT Type=Submit Value="Submit">
			
		</FORM>


		<hr>

		<% Response.Write(Request.QueryString("fname"))%> <br>
		<% Response.Write(Request.QueryString("lname"))%>
	</BODY>
</HTML>
