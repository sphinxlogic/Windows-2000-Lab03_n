
<%@ Language=VBScript %>
<HTML>
<HEAD>
<!--#include file="xml.asp"-->
<LINK REL=STYLESHEET TYPE="text/css" HREF="StyleIssue.css" Title="Style1">
<META NAME="GENERATOR" Content="Microsoft Visual Studio 6.0">
</HEAD>
<BODY>
<% if session("LoggedOnAs") = "representative" then 
	Response.Write "<h2>Please contact trader to trade on behalf of customer.<h2>"
else
%>

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
<%
 EnableConfirm = "disabled"
 AcctNum = session("AcctNum")
 ssn     =session("SSN")
 symbol = Request("symbol")
 shares = Request("quantity")
 price = Request("price")
 
 if not (Request("submit")="") then 
	 If request("BuyRB") = "Buy"  Then
	       TradeAction = 0
	 Else
	       TradeAction = 1
	 End If
		   
	 If request("MarketRB") = "Market" Then
	     TradeType = 0'Market_ORDER
	 Else
	     TradeType = 1'Limit_ORDER
	 end if
		   
	If price = "" Then 
	 	price =0
	 else
	 	price = CCur(price)
	End If
		   
	If shares = "" Then
	    shares = 0
	Else
	    shares = CInt(shares)
	End If

	Set objQuote = server.CreateObject("HBExchange.IQuote")
	
	objQuote.RetrieveEx symbol, QuoteTime, Bid_Price, Ask_Price,  _
	Last_Trade, LastTradePrice, Change, Daily_High, Daily_Low, _ 
	Ask_Size, bid_Size, OpenValue, CloseValue, closeDate, sMsg
	set objQuote = nothing
	
	Set objOrder =server.createobject("HBInstitution.IOrder")
 
	if Request("submit") = "Verify" then
		rc = objOrder.Verify(AcctNum,symbol, shares, price, Bid_Price, Ask_Price, TradeAction, TradeType, sMsg)
		if (rc = 1) then
			EnableConfirm = ""
		end if
			
	elseif Request("submit") = "Execute" then
		
		rc = objOrder.Execute(ssn, AcctNum, symbol, shares, price, Bid_Price, Ask_Price, TradeAction, TradeType, ConfirmNumber, true, sMsg)
		if (rc = 1) then
			sMsg = "Order Entered Successfully. Your Confirmation Number is " & ConfirmNumber
			'XML stream needs to be refreshed
			session("Dirty") = True
			if Session("UseXML") then
				call GetTableStrings()
			end if
		else
			sMsg = "Enter Order Failed. " & sMsg
		end if

		EnableConfirm = "disabled"
	else
		price = LastTradePrice	
		sMsg = "Start Trading" 
	end if
	
	set objOrder = nothing

else
	sMsg =  "Start Trading"
end if 

Response.Write "<DIV STYLE=color:blue>" & sMsg & "</DIV>"		
%>

<FORM action="trade.asp" method=POST id=form1 name=form1>
<table border=1><tr><td>
<TABLE  BORDER=0 CELLSPACING=1 CELLPADDING=1 align=left>

	<TR>
		<TD><div>Account</div></TD>
		<TD><%= AcctNum %></TD>
	</TR>
	<TR>
		<TD><div>Symbol</div></TD>
		<TD><SELECT id=select2 name=symbol style="HEIGHT: 22px; WIDTH: 100px"> 
		<% 	
		Set objQuote = server.CreateObject("HBExchange.IQuote")
		objQuote.GetSymbolList symbollist, sMsg
		if not symbollist.EOF then
			do while not symbollist.EOF %>
		
			<OPTION
			<% if request("symbol") = symbollist("symbol") then  %> selected
			<%end if %>
			>
			 <%= symbollist("symbol") %></OPTION>
		<%	symbollist.movenext
			loop
		else %>
			<OPTION>""</OPTION>
		<% end if
		set objQuote = nothing
		%>
		</SELECT></TD>
	</TR>
	<TR>
		<TD><div>Quantity</div></TD>
		<TD><INPUT id=text1 name=quantity style="HEIGHT: 22px; WIDTH: 100px" value=
		<% if Request("quantity") = "" then %>
		0
		<% else %>
		<%= Request("quantity") %>
		<% end if %>
		></TD>
	</TR>
	<TR>
		<TD><div>Price</div></TD>
		<TD><INPUT id=text2 name=price style="HEIGHT: 22px; WIDTH: 100px" value=
		<% =price %>
		></TD>
	</TR>
	
<TR><TD><div>Trade Action:</div></td></tr>
<TR><TD><INPUT id=radio1 name=Buyrb type=radio  value=Buy defaultselected
	<% if (request("Buyrb") = "Buy") or (request("Buyrb") = "") then %>
	checked <%end if %>>Buy</TD>
	<TD ><INPUT id=radio2 name=Buyrb type=radio  value=Sell
	<% if request("Buyrb") = "Sell" then %>
	checked<%end if %>>Sell</TD></tr>

<TR><TD><div>Trade Type:</div></td></tr>
<TR><TD ><INPUT id=radio1 name=Marketrb type=radio  value=Market defaultselected
	<% if (request("Marketrb") = "Market") or (request("Marketrb") = "") then %>
	checked<%end if %> >Market</TD>
	<TD ><INPUT id=radio2 name=Marketrb type=radio  value=Limit
	<% if request("Marketrb") = "Limit" then %>
	checked<%end if %>>Limit</TD></tr>
	</TR>
<tr><td><br></td></tr>
<tr ><td colspan=2>
	<INPUT type="submit" value="Refresh" id=submit3 name=submit>
	<INPUT type="submit" value="Verify" id=submit1 name=submit>
	<INPUT type="submit" value="Execute" id=submit2 name=submit 
	<%= EnableConfirm %>
></td></tr>
</TABLE>
</td>
</tr>


</FORM>


</table>

<% end if %>	 
</BODY>
</HTML>
