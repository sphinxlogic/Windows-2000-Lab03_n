<%@ Language=VBScript %>
<HTML>
<LINK REL=STYLESHEET TYPE="text/css" HREF="StyleIssue.css" Title="Style1">
<HEAD>
<META NAME="GENERATOR" Content="Microsoft Visual Studio 6.0">
</HEAD>

<BODY>
<h1> You are logged in as representative. </h1>
<%	Dim objCust
	Set objCust = Server.CreateObject("HBInstitution.ICustomer")
	ssn = Request("selcustomer")
    if (ssn <> "" and request("submit1")="Access Customer Account") then
		'get ssn and pin and move to customer page
		ssn = Request("selcustomer")
		objCust.GetCustomerInfo ssn, custType, custName, address, phone, email, sMsg
		objCust.GetTotalNetWorth ssn, cTotalNet, cTotalCash, sMsg
		session("PortfolioNetWorth") = FormatCurrency(cTotalNet)
		session("CashAvailable") = FormatCurrency(cTotalCash)
		session("SSN") = ssn
		session("Name")= custName
		session("Address")=  address
		session("Phone")=phone
		session("Email")=email
		if session("RepSSN") <> session("SSN") then
			session("LoggedOnAs") = "representative"
		else
			session("LoggedOnAs") = "customer"
		end if
		set ObjCust = nothing
		Response.Redirect "cust.asp"
	elseif request("submit1")="Add Customer" then
		Response.Redirect "AddCust.asp"
	else
    %>
 
<FORM action="rep.asp" method=POST id=form1 name=form1>
<table align = left>
<tr>
	<td>
	<table  align=left>
	<tr><td>
	<div align=left>Select Customer:</div></td><tr>
	<tr><td>
	<SELECT id=select1 name=selcustomer size=2 style="HEIGHT: 106px; WIDTH: 177px"> 
		<%
		Set objCust = Server.CreateObject("HBInstitution.ICustomer")
		rc = objCust.GetCustomers(Customers, sMsg)
			
		For i = 0 To UBound(Customers, 2)
		%>
		<OPTION
		<% if Customers(0, i)=Request("selcustomer") then %>
		selected
		<% end if %>
		>
		

		<%=Customers(0, i) %> 
		</OPTION> &nbsp;
		<%
		Next
		set Objcust = nothing
	%>

	</SELECT>
	</td></tr>
	</table>
	</td>
</tr>
<tr>
	<td>
	<TABLE border=0 cellPadding=1 cellSpacing=1  align=left>
	  
	  <TR>
	    <TD><div>SSN:</div></TD>
	    <TD><% = Session("RepSSN") %></TD></TR>
	  <TR>
	    <TD><div>Name:</div></TD>
	    <TD><%= Session("RepName") %></TD></TR>
	  <TR>
	    <TD><div>Phone:</div></TD>
	    <TD><%= Session("RepPhone") %></TD></TR>
	  <TR>
	    <TD><div>Address:</div></TD>
	    <TD><%= Session("RepAddress") %></TD></TR>
	  <TR>
	    <TD><div>Email:</div></TD>
	    <TD><%= Session("RepEmail") %></TD></TR>
	    </TABLE><BR>
	    </td>
</tr>
<tr>
	<td>
	<INPUT id=submit1 name=submit1 type=submit value="Access Customer Account">
	<INPUT type="submit" value="Add Customer" id=submit1 name=submit1>
	<INPUT type="submit" value="Refresh" id=submit1 name=submit1>
	</td>
</tr>

</FORM>
<% end if %>
</BODY>
</HTML>
