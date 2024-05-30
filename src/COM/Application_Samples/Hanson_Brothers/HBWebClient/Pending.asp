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
<h1>Pendings for <%=Session("AcctNum")%> </h1>
<TABLE WIDTH=100% BORDER=1 CELLSPACING=1 CELLPADDING=1>
	<TR>
		<TD><div>Confirm #</div> </TD>
		<TD><div>Symbol</div></TD>
		<TD><div>Quantity</div></TD>
		<TD><div>Confirm Date</div></TD>
		<TD><div>Limit Price</div></TD>
		<TD><div>Acct Number</div></TD>	
	</TR>
	<% if Session("UseXML") = False then
			Dim objAcct
			dim sMsg
			dim rst
			dim AcctNum
			AcctNum = Session("AcctNum")
			set objAcct = server.CreateObject("HBInstitution.IAccount")
		    objAcct.GetPendingHierarchy AcctNum, rst, sMsg
		'get all variables
		if not IsEmpty(rst) then
		do while not rst.EOF %> 
		<TR>
			<TD><%= rst("orderId") %></TD>
			<TD><%= rst("symbol")%></TD>
			<TD><%= rst("quantity")%></TD>
			<TD><%= rst("confirmationDate")%></TD>
			<TD><%= rst("limitPrice")%></TD>
			<TD><%= rst("acctNumber")%></TD>
		</TR>
		<% rst.MoveNext
		loop
		else
		Response.Write " <no record found>" 
		end if
	else
		Response.Write Session("PendingTableStr")
	end if
	%>
	
</TABLE>
</td></tr></table>
</BODY>
</HTML>
