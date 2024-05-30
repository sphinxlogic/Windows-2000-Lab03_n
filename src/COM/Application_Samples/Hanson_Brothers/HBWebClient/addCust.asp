<%@ Language=VBScript %>
<HTML>
<HEAD>
<!--#include file="xml.asp"-->
<LINK REL=STYLESHEET TYPE="text/css" HREF="StyleIssue.css" Title="Style1">
<META NAME="GENERATOR" Content="Microsoft Visual Studio 6.0">
</HEAD>
<BODY>
<h1 align=center> Add New Customer </h1>
 

<%

  
If Not (request("submit1") = "") then
	bAccountSilver=(request("AccountSilver")="on") 
	bAccountGold=(request("AccountGold")  ="on")
	bAccountPlatinium=(request("AccountPlatinium")="on")
	bNetworth1=not(request("NetWorth1") = "")
	bNetworth2= not(request("NetWorth2")="")
	bNetworth3=not(request("NetWorth3") ="")
	cond1 = ( bAccountSilver And bNetworth3) Or ( bAccountGold And bNetworth2) Or ( bAccountPlatinium And bNetworth1)
	cond2 = (bAccountSilver = bNetworth3) and  (bAccountGold = bNetworth2) and  (bAccountPlatinium = bNetworth1)

	if (request("NetWorth1") = "") then
		Networth1 = CCur(0)
	else
		Networth1 = CCur(request("NetWorth1"))
	end if
	if request("NetWorth2") = "" then
		Networth2 = CCur(0)
	else
		Networth2 = CCur(request("NetWorth2"))
	end if
	if request("NetWorth3") = "" then
		Networth3 = CCur(0)
	else
		Networth3 = CCur(request("NetWorth3"))
	end if

	cond3 = (Networth1 <= 100000) and (Networth2 <= 100000) and (Networth3 <= 100000)
	if  Not (request("SSN") = "") _
		And Not (request("FirstName")= "") _
		And Not (request("LastName") = "") _
		And Not (request("password1") = "") _
		And Not (request("password2") = "") _
		And (request("Password2") = request("Password1")) _
		And cond1 and cond2 and cond3 then
		
		
		'add customer here
		set objCust = server.CreateObject("HBInstitution.ICustomer")
		call objCust.AddCustomer(request("SSN"), request("password1"), _
		request("FirstName"), request("LastName"), request("MiddleName"), _
		request("HomePhone"), request("WorkPhone"), request("Email"), _
		request("StreetAddress"), request("City"), request("State"), request("Zip"), _
		bAccountPlatinium, bAccountGold, bAccountSilver, _
		NetWorth1,NetWorth2,NetWorth3,	sMsg)
      
		Response.Write "<h2>" & sMsg &  "</h2>"
	else
		Response.Write "<h2>One of the required field is empty.</h2>"
    end if
    
else
%>
<FORM action="AddCust.asp" method=POST id=form1 name=form1>

<table border=0>
<tr><td><h2>Personal Information:</h2></td></tr>

<tr><td><table border=1><tr><td>
<TABLE>
  <TR>
    <TD><div>SSN</div></TD>
    <TD><INPUT id=SSN name=SSN value=<%=request("SSN")%>>&nbsp;&nbsp;</TD>
    <TD><div>Email</div></TD>
    <TD><INPUT id=Email name=Email value=<%=request("Email") %>></TD></TR>
  <TR>
    <TD><div>First Name</div></TD>
    <TD><INPUT id=FirstName name=FirstName value=<%=request("FirstName") %>>&nbsp;&nbsp;</TD>
    <TD><div>Last Name</div></TD>
    <TD><INPUT id=LastName name=LastName value=<%=request("LastName") %>></TD></TR>
  <TR>
    <TD><div>Middle Name</div></TD>
    <TD><INPUT id=MiddleName name=MiddleName value=<%=request("MiddleName") %>>&nbsp;&nbsp;</TD>
    <TD><div>Home Phone</div></TD>
    <TD><INPUT id=HomePhone name=HomePhone value=<%=request("HomePhone") %>></TD></TR>
  <TR>
    <TD><div>Work Phone</div></TD>
    <TD><INPUT id=WorkPhone name=WorkPhone value=<%=request("WorkPhone") %>>&nbsp;&nbsp;</TD>
    <TD><div>Street Address</div></TD>
    <TD><INPUT id=StreetAddress name=StreetAddress value=<%=request("StreetAddress") %>></TD></TR>
  <TR>
	<TD><div>City</div></TD>
    <TD><INPUT id=City name=City value=<%=request("City") %>>&nbsp;&nbsp;</TD>
    <TD><div>State</div></TD>
    <TD><INPUT id=State name=State value=<%=request("State") %>>&nbsp;&nbsp;</TD>
   </TR>
   <TR>
    <TD><div>Zip</div></TD>
    <TD><INPUT id=Zip name=Zip value=<%=request("Zip") %>></TD>
    </TR>
  <TR>
    <TD><div>Password</div></TD>
    <TD><INPUT id=Password1 name=password1 
    type=password value=<%=request("password1") %>>&nbsp;&nbsp;</TD>
    <TD><div>Confirm Password</div></TD>
    <TD><INPUT id=password2 name=password2 
    type=password value=<%=request("password2") %>></TD></TR>
    </TABLE>
  </td></tr> </table>
	</td></tr>
  <tr><td><h2>Account Information:</h2></td></tr>
  <tr><td>
  <table border=1><tr><td>
 <TABLE>  
  <TR>
    <TD><INPUT id=AccountPlatinium name=AccountPlatinium  type=checkbox      <% if request("AccountPlatinium")= "on" then  %>     checked <%end if%>   ></td><td><div>Platinium(no restrictions)</div></TD>
    <TD><div>Cash Deposit</div></TD>
    <TD><INPUT id=NetWorth1 name=NetWorth1 value=<%=request("NetWorth1") %>></TD>
    <TD></TD></TR>
  <TR>
    <TD><INPUT id=AccountGold name=AccountGold  type=checkbox <%if request("AccountGold")= "on" then  %> checked <%end if%>></td><td><div>Gold(moderate restrictions)</div></TD>
    <TD><div><div>Cash Deposit</div></TD>
    <TD><INPUT id=NetWorth2 name=NetWorth2  value=<%= request("NetWorth2")%>></TD>
    <TD></TD></TR>
  <TR>
    <TD><INPUT id=AccountSilver name=AccountSilver type=checkbox <%if request("AccountSilver")= "on" then  %> checked <%end if%>></td>    <td><div>Silver(limited)</div></TD>    <TD><div><div>Cash Deposit</div></TD>
    <TD><INPUT id=NetWorth3 name=NetWorth3 value=<%=request("NetWorth3") %>></TD>
   </TR>
   </TABLE>
   </td></tr></TABLE>
   </td></tr>
 <tr><td ></td><tr>

</TABLE>
<INPUT id=submit1 name=submit1 type=submit value="Add Customer">
<INPUT type="reset" value="Reset" id=reset1 name=reset1>

</FORM>
<% end if %>
</BODY>
</HTML>
