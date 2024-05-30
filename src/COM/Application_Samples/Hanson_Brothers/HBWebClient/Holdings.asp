<%@ Language=VBScript %>
<HTML>
<HEAD>
<LINK REL=STYLESHEET TYPE="text/css" HREF="StyleIssue.css" Title="Style1">
<META NAME="GENERATOR" Content="Microsoft Visual Studio 6.0">
</HEAD>
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

<h1>Holdings for <%=Session("AcctNum")%> </h1>
<TABLE WIDTH=100% BORDER=1 CELLSPACING=1 CELLPADDING=1>
	<TR>
		<TD><div>symbol</div></TD>
		<TD><div>quantity</div></TD>
		<TD><div>Net Worth</div></TD>
		<TD><div>reconciled</div></TD>
		<TD><div>Current Price</div></TD>
		<TD><div>Current Value</div></TD>
	</TR>
	
	<% if Session("UseXML") = False then
		AcctNum = Session("AcctNum")
	
		Set objCust = server.CreateObject("HBInstitution.ICustomer")
		objCust.CalcHolding AcctNum, rs, sMsg
		objCust.GetHoldingHierarchy AcctNum, rst, sMsg
			
		dim symbol 
		dim	quantity  
		dim Net_Worth 
		dim reconciled  
		dim	Current_Price 
		dim Current_Value 
	
		if not IsEmpty(rst) then
		do while not rst.EOF 
			symbol = rst("symbol")
			quantity  =rst("quantity")
			Net_Worth =rst("value")
			reconciled  =rst("reconcileDate")
			Current_Price =rst("settledPrice")
			Current_Value =rst("CurrentValue")
		%> 
		<TR>
			<TD><%= symbol %></TD>
			<TD><%= quantity  %></TD>
			<TD><%= Net_Worth %></TD>
			<TD><%= reconciled  %></TD>
			<TD><%= Current_Price %></TD>
			<TD><%= Current_Value %></TD>
		</TR>
		<% rst.MoveNext
		loop 
		else
		Response.Write " <no record found>" 
		end if
	else
		Response.Write Session("HoldingsTableStr")
	end if
	%>
</TABLE>
</td></tr></table>
<P>&nbsp;</P>

</BODY>
</HTML>
