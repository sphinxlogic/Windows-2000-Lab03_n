
<HTML>
<HEAD>
<LINK REL=STYLESHEET TYPE="text/css" HREF="StyleIssue.css" Title="Style1">
<META NAME="GENERATOR" Content="Microsoft Visual Studio 6.0">
<TITLE>login</TITLE>
</HEAD>
<BODY>
<SCRIPT LANGUAGE=vbscript RUNAT=Server>
sub SetCustomerInfo(sSSN,pin, custType, custName, address, phone, email, sTotalNetTED, sTotalCashTED )
	session("SSN") = sSSN
	session("Name")= custName
	session("Address")=  address
	session("Phone")=phone
	session("Email")=email
	session("PortfolioNetWorth")=sTotalNetTED
	session("CashAvailable")=sTotalCashTED
	session("LoggedOnAs") = "customer"
end sub
sub SetRepInfo(sSSN,pin, custType, custName, address, phone, email, sTotalNetTED, sTotalCashTED )
	session("RepSSN") = sSSN
	session("RepName")= custName
	session("RepAddress")=  address
	session("RepPhone")=phone
	session("RepEmail")=email
	session("LoggedOnAs") = "representative"
end sub

function ValidateUserType (sSSN, pin,ByRef custType, ByRef custName, ByRef address, ByRef phone, ByRef email, ByRef sTotalNetTED, ByRef sTotalCashTED )

		dim objCust
		set objCust = server.CreateObject("HBInstitution.ICustomer")
		dim  sMsg
		dim cTotalNet
		dim cTotalCash
		if ( NOT objCust.ValidateUser(sSSN, pin)= FAILED) then
			objCust.GetCustomerInfo sSSN, custType, custName, address, phone, email, sMsg
			objCust.GetTotalNetWorth sSSN, cTotalNet, cTotalCash, sMsg
		 	sTotalNetTED = FormatCurrency(cTotalNet)
			sTotalCashTED = FormatCurrency(cTotalCash)
		 	ValidateUserType = custType
		 else
			ValidateUserType = -1
		 end if
end function
</SCRIPT>

<% if not(Request.Item("text1")="") and not (Request.Item("password1")="") then
	dim sSSN
	dim pin
	dim custType
	dim custName
	dim address
	dim phone
	dim email
	dim sTotalNetTED
	dim sTotalCashTED 
	
	sSSN = Request.Item("text1")
	pin =  Request.Item("password1")
	
	UserType = ValidateUserType(sSSN, pin,custType, custName, address, phone, email, sTotalNetTED, sTotalCashTED )
	Response.Write UserType
	if UserType = 2 then 'representative
		SetRepInfo sSSN,pin, custType, custName, address, phone, email, sTotalNetTED, sTotalCashTED
		Response.Redirect "Rep.asp"
	elseif UserType = 3 then 'customer
		SetCustomerInfo sSSN,pin, custType, custName, address, phone, email, sTotalNetTED, sTotalCashTED
		Response.Redirect "cust.asp" 
	else
		Response.write "<h1>Invalid user, please check your ssn and pin.</h1>"
	end if
else %>


<FORM action=login.asp method=POST id=form1 name=form1>
<table>
<tr><td><div>SSN:</div></td> <td><INPUT id=text1 name=text1></td></P></tr>
<tr><td><div>Pin:</div></td> <td><INPUT id=password1 name=password1 type=password></td></P>
</table>
<table align=left cellpadding=1 cellspacing=1>
<tr>
<td colspan=2>&nbsp;&nbsp;&nbsp;&nbsp;</td>
<td align=right><INPUT id=submit1 name=submit1 type=submit value=Submit style="LEFT: 9px; TOP: 101px"></td>
<td ><INPUT id=reset1 name=reset1 type=reset value=Reset></td>
</tr>
</table>
</FORM>
</BODY>
<% end if %>
</HTML>
