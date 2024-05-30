<%@ Language=VBScript %>

<HTML>
<HEAD>
<LINK REL=STYLESHEET TYPE="text/css" HREF="StyleIssue.css" Title="Style1">
<META NAME="GENERATOR" Content="Microsoft Visual Studio 6.0">
</HEAD>
<BODY>
<Table border=0 bordercolorlight=Gray bordercolordark=Fuchsia>
<tr><td><table border=1>
<TR  bgcolor=SlateGray> 
	<TD bordercolor=Black><A HREF="History.asp">History</A><TD>
	<TD bordercolor=Black><A HREF="Details.asp">Account Details</A><TD>
	<TD bordercolor=Black><A HREF="Holdings.asp">Holdings</A></TD>
	<TD bordercolor=Black><A HREF="Pending.asp">Pending</A></TD>
	<TD bordercolor=Black><A HREF="quote.asp">Quote</A></TD>
	<TD bordercolor=Black><A HREF="cust.asp">Customer</A></TD>
	<TD bordercolor=Black><A HREF="Trade.asp">Trade</A></TD>
</TR></table> </td></tr>
<tr><td><br></td></tr>		
<TR><TD>
<h1>Account Details for <%=Session("SSN")%></h1>
<TABLE WIDTH=100% BORDER=1 CELLSPACING=1 CELLPADDING=1>
	<TR>
		<TD><div>Account#</div></TD>
		<TD><div>Type</div></TD>
		<TD><div>Cash</div></TD>
		<TD><div>Cash Debit</div></TD>
		<TD><div>Net worth</div></TD>
		<TD><div>Cash Avail</div></TD>
	</TR>
	<% if Session("UseXML") = False then
		 dim sMsg
		 dim rst
		 dim objCust
		 dim sSSN
		 sSSN = Session("SSN")
		 	 
		 set objCust = server.CreateObject("HBInstitution.ICustomer")
		 
		objCust.GetAccountsDetails sSSN, rst, sMsg
		'get all vars
		if not IsEmpty(rst) then
		do while not rst.EOF %> 
		<TR>
			<TD><%= rst("acctNumber") %></TD>
			<TD><%= rst("acctType") %></TD>
			<TD><%= rst("cash") %> </TD>
			<TD><%= rst("cashDebit") %></TD>
			<TD><%= rst("netWorth")%></TD>
			<TD><%= rst("AvailCash")%></TD>
		</TR>
		<% 
		rst.MoveNext
		loop 
		else
		Response.Write " <no record found>" 
		end if
	else
		Response.Write Session("DetailsTableStr")
	end if	
	%>
</TABLE>

<P>&nbsp;</P>
</td></tr></table>
</BODY>
</HTML>
