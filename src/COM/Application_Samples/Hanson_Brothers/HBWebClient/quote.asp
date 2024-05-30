<%@ Language=VBScript %>
<HTML>
<LINK REL=STYLESHEET TYPE="text/css" HREF="StyleIssue.css" Title="Style1">
<% 
'if (session("LoggedOnAs") = "representative") then
'	Response.Redirect "quoteUpdate.asp"
'end if 
%>
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

<FORM action=quote.asp method=POST id=form1 name=QuoteForm>

<TABLE >
<tr><td><div> Select Symbol:</div></td>

<td ><SELECT id=select1 name=select1 >

<%  sel = Request.Item("select1")
	Set obj = server.CreateObject("HBExchange.IQuote")

	FillCB sel, obj, firstsymbol
	dim  QuoteTime
	dim  Bid_Price
	dim  Ask_Price 
	dim  Last_Trade
	dim  LastTradePrice
	dim  Change
	dim  Daily_High
	dim  Daily_Low
	dim  Ask_Size
	dim  bid_Size
	dim  OpenValue
	dim  CloseValue
	dim  closeDate
	dim  sMsg
	dim fullname
	if sel = "" then
		OnRefreshQuote firstsymbol, obj
	else
		OnRefreshQuote Request.Item("select1"), obj
    end if
%>
<SCRIPT LANGUAGE=vbscript RUNAT=Server>

sub FillCB(symbol, obj, ByRef firstsymbol)
	'add code to fill the stock symbol drop down list box
	dim sMsg
	dim symbollist
	dim i 

	obj.GetSymbolList symbollist, sMsg
	i = 0
	if not (symbollist.EOF) then
		firstsymbol = symbollist.fields(0).value
	else 
		firstsymbol = ""
	end if
	
	do while not symbollist.EOF 
	curSymbol = symbollist("Symbol")
	i = i+1
	Response.Write "<OPTION "
	if curSymbol = Symbol then
		Response.Write " selected " 
	end if
		Response.Write ">" & curSymbol &  "</OPTION>"  
	
	symbollist.MoveNext
	loop

end sub


sub OnRefreshQuote(symbol, obj)

obj.RetrieveEx symbol, QuoteTime, Bid_Price, Ask_Price,  _
Last_Trade, LastTradePrice, Change, Daily_High, Daily_Low, _ 
Ask_Size, bid_Size, OpenValue, CloseValue, closeDate, sMsg

obj.GetSymbolInfo symbol,fullname, sMsg

end sub
</SCRIPT>


</SELECT></td>
<td ><INPUT type=submit value=Refresh id=submit1 name=submit1></td>
</tr>
<tr><td colspan=3>
<table border=1 ><tr><td>
<table>
	<TR>
		<TD><div>Symbol Name:</div></TD>
		<TD><%=fullname%></TD>
	</TR>
	<TR>
		<TD><div>Last Trade:</div></TD>
		<TD><%=Last_Trade%></TD>
	</TR>
	<TR>
		<TD><div>Change:</div></TD>
		<TD><%=Change%></TD>
	</TR>
	<TR>
		<TD><div>Open:</div></TD>
		<TD><%=OpenValue%></TD>
	</TR>
	<TR>
		<TD><div>Close:</div></TD>
		<TD><%=CloseValue%></TD>
	</TR>
	<TR>
		<TD><div>Daily Low:</div></TD>
		<TD><%=Daily_Low%></TD>
	</TR>
	<TR>
		<TD><div>Bid Price:</div></TD>
		<TD><%=Bid_Price%></TD>
	</TR>
	<TR>
		<TD><div>Ask Price:</div></TD>
		<TD><%=Ask_Price%></TD>
	</TR>
	<TR>
		<TD><div>Bid Size:</div></TD>
		<TD><%=bid_Size%></TD>
	</TR>
	<TR>
		<TD><div>Ask Size:</div></TD>
		<TD><%=Ask_Size%></TD>
	</TR>
	<TR>
		<TD><div>Daily High:</div></TD>
		<TD><%=Daily_High%></TD>
	</TR>
	</table>
	</td></tr></table>


</TABLE>
</form>
</td></tr></table>


</BODY>
</HTML>
