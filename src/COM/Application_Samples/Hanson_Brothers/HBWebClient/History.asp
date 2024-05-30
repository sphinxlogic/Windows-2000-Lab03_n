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
</TR></table></td></tr>
<tr><td><br></td></tr>
		
<TR><TD>
<h1>History for Account
	<%= Session("AcctNum") %> 
	</h1>
<TABLE  BORDER=1 >
	<TR>
		<TD><div>Confirm No</div></TD>
		<TD><div>Action</div></TD>
		<TD><div>Shares</div></TD>
		<TD><div>Symbol</div></TD>
		<TD><div>Total Price</div></TD>
		<TD><div>Type</div></TD>
		<TD><div>Status</div></TD>
		<TD><div>Limit Price</div> </TD>
		<TD><div>Settled Price</div>  </TD>
		<TD><div>Confirmation Date</div> </TD>
		<TD><div>Settlement Date</div> </TD>
		<TD><div>Reconcile Date</div> </TD>
		<TD><div>Commision </div></TD>
		<TD><div>Check Number</div> </TD>
		<TD><div>acknowledged</div> </TD>
	</TR>
	<% if Session("UseXML") = False then 
	
		Const BUY = 0
		Const SELL = 1
		Const HOLDING_SUMMARY = 99
		Const NO_SUMMARY = 0

		Const MARKET_ORDER = 0
		Const LIMIT_ORDER = 1

		Const UNCONFIRMED = 0
		Const CONFIRMED = 1
		Const SETTLED = 2
		Const RECONCILED = 3
		Const CANCELED = 4
		Const ICONFIRMED = 5

		'get all variables
		Dim objAcct
		dim Confirm_No
		dim Action
		dim Shares
		dim Symbol
		dim Total_Price
		dim TradeType
		dim Status
		dim rst
		dim sAcctNum
		dim sMsg
		dim AcctNum
	
		AcctNum = Session("AcctNum")
		'Response.write "<table><tr><td><div>Account:</div></td><td>" & AcctNum & "</td></tr></table>"
		set objAcct = server.CreateObject("HBInstitution.IAccount")
		objAcct.GetHistory AcctNum, rst, sMsg
		Response.Write sMsg
	
		if not IsEmpty(rst) then
		do while not rst.EOF
		Confirm_No = rst("orderId")
    
		If rst("action") = BUY Then
		   Action = "BUY"
		ElseIf rst("action") = SELL Then
		   Action = "SELL"
		Else
		   Action = "UNKNOWN"
		End If
			
		Shares=rst("quantity")
		Symbol=rst("symbol")
		Total_Price=rst("value")
		If rst("tradeType") = MARKET_ORDER Then
		   TradeType = "MARKET"
		ElseIf rst("tradeType") = LIMIT_ORDER Then
		   TradeType = "LIMIT"
		Else
		    TradeType = "UNKNOWN"
		End If
		If rst("orderStatus") = CONFIRMED Then
		   Status = "M-CONF"
		ElseIf rst("orderStatus") = SETTLED Then
		   Status = "FILLED"
		ElseIf rst("orderStatus") = RECONCILED Then
		   Status= "RECON"
		ElseIf rst("orderStatus") = CANCELED Then
		   Status = "CANC"
		ElseIf rst("orderStatus") = ICONFIRMED Then
		   Status = "I-CONF"
		Else
		    Status = "UNKNOWN"
		End If
   
		limitPrice= rst("limitPrice")
		settledPrice = rst("settledPrice")
		confirmationDate = rst("confirmationDate") & ""
		settlementDate = rst("settlementDate") & ""
		reconcileDate = rst("reconcileDate") & ""
		commision = rst("commision")
		check_number = rst("check_number")
		    
		If rst("acknowledged") = NOT_ACKNOWLEDGED Then
		   acknowledged = "NO"
		Else
		    acknowledged = "YES"
		End If       
	
		 
    
		%> 
		<TR>
			<TD><%= Confirm_No %></TD>
			<TD><%= Action %></TD>
			<TD><%= Shares %></TD>
			<TD><%= Symbol%></TD>
			<TD><%= Total_Price%></TD>
			<TD><%= TradeType %></TD>
			<TD><%= Status%></TD>
			<TD><%= limitPrice%></TD>
			<TD><%= settledPrice %></TD>
			<TD><%= confirmationDate%></TD>
			<TD><%= settlementDate%></TD>
			<TD><%= reconcileDate%></TD>
			<TD><%= commision%></TD>
			<TD><%= check_number%></TD>
			<TD><%= acknowledged%></TD>
		</TR>
		<% rst.MoveNext
		loop
		else
		Response.Write " <no record found>" 
		end if
	else
		Response.Write Session("HistoryTableStr")	
	end if
	%>
</TABLE>

<P>&nbsp;</P>
</TD></TR></TABLE>
</BODY>
</HTML>
