<%@ Language=VBScript %>
<SCRIPT id=DebugDirectives runat=server language=javascript>
// Set these to true to enable debugging or tracing
@set @debug=false
@set @trace=false
</SCRIPT>
<HTML>
<HEAD>
<!--#include file="xml.asp"-->
<LINK REL=STYLESHEET TYPE="text/css" HREF="StyleIssue.css" Title="Style1">
<META NAME="GENERATOR" Content="Microsoft Visual Studio 6.0">
</HEAD>


<SCRIPT LANGUAGE=vbscript RUNAT=Server>

</SCRIPT>


<% 
	if not(request("submit")="") then
		if (Request("submit")="Acknowledge") then
			liststr= request("selNacTrades")
			if not(liststr = "") then
				conf = Left(liststr, InStr(1, liststr, " ",1)-1)
				Set objOrder = Server.CreateObject("HBInstitution.IOrder")
				rc = objOrder.Acknowledge(CInt(conf), sMsg)
				
				if (rc = 1) then
					'sMsg = "Order has been acknowledged successfully"
				else
					'sMsg = "Order acknowledgement failed"
				end if
				
				Set objOrder = Nothing
			else
				'sMsg = "Please select unacknowleged trade." 
			end if
			Response.Write sMsg
		else
			Session("AcctNum") = Request("selectAccountNum")
			bUseXML = (request("UseXML")="on")
			Session("UseXML") = bUseXML
	
			if bUseXML then
				call GetTableStrings()
			end if
		
			if request("submit")="Details" then
				Response.Redirect "Details.asp"
			elseif  request("submit")="holdings" then
				Response.Redirect "holdings.asp"
			elseif  request("submit")="History" then
				Response.Redirect "History.asp"
			elseif  request("submit")="Pending" then
				Response.Redirect "Pending.asp"
			elseif  request("submit")="Trade" then
				Response.Redirect "Trade.asp"
			elseif  request("submit")="Quote" then
				Response.Redirect "Quote.asp"
			end if
		end if

	end if%>	
    
<BODY>   

<h1>Customer </h1>
<P></P>
<P>

<FORM action="cust.asp" method=POST id=form1 name=form1>

<TABLE border=1>
<tr><td>
<table><tr><td>
  
  <TR>
    <TD><div>SSN:</TD>
    <TD><% = Session("SSN") %></TD></TR>
  <TR>
    <TD><div>Name:</div></TD>
    <TD><%= Session("Name") %></TD></TR>
  <TR>
    <TD><div>Phone:</div></TD>
    <TD><%= Session("Phone") %></TD></TR>
  <TR>
    <TD><div>address:</div></TD>
    <TD><%= Session("Address") %></TD></TR>
  <TR>
    <TD><div>Email:</div></TD>
    <TD><%= Session("Email") %></TD></TR>
  
    <TD><div>Portfolio Net Worth:</div></TD>
    <TD><%= Session("PortfolioNetWorth") %></TD></TR>
  <TR>
    <TD><div>Cash Available:</div></TD>
    <TD><%= Session("CashAvailable") %> </TD>
    </TR>
    <TR>
    <TD><div>Account:</div></TD>
    <TD>
    <SELECT name="selectAccountNum">
    <%
    dim rst
    dim sMsg
	Set objCust = Server.CreateObject("HBInstitution.ICustomer")
    
    objCust.GetAccounts session("SSN"), rst, sMsg
    
    if not IsEmpty(rst) then
	    do while not rst.EOF
    %>
    <OPTION><%= rst("acctNumber") %>    </OPTION>
    
    <% rst.MoveNext
		loop 
	    end if 
    %>
    </SELECT>
    </TD>
    </TR>
  <TR>
	
  </TR>
  <tr>
  <td><div>UseXML</div></td>
  <Td>
  <INPUT type="checkbox" id=UseXML name=UseXML 
  <% if Session("UseXML")=True then %>
  checked
  <% end if %>
  >
  </td></tr>
  </table>
  </td>
  <td bgcolor=LightSlateGray>&nbsp;&nbsp;&nbsp;&nbsp;</td>
   <td>
	<table border=0><tr><td>
		<table>
		<tr><td><div>Unacknowledged Trades:</div></td></tr>
		<tr><td><br></td></tr>
		<tr><td ><SELECT style=width:200 size=8 id=selNacTrades name=selNacTrades multiple>
		<%
		set objCust = server.CreateObject("HBInstitution.ICustomer")
		rc = objCust.GetNonAcknowledgedTrades(Session("SSN"), nakTrades, sMsg)
		
		If rc = 1 Then
		cnt = UBound(nakTrades, 2)
		
        For i = 0 To cnt
            If nakTrades(13, i) = 0 then 'BUY 
                sAction = "B"
            ElseIf nakTrades(13, i) = 1 then 'SELL 
                sAction = "S"
            Else
                sAction = "?"
            End If
            ' Confirm# + Action + Quantity + Symbol
            str = Trim(nakTrades(17, i)) & " &nbsp; : &nbsp;" & sAction & "&nbsp;  " & Trim(nakTrades(3, i)) & "&nbsp; " & Trim(nakTrades(2, i)) & " &nbsp; " & Trim(nakTrades(11, i))
            Response.Write "<OPTION>" & str & "</OPTION>"
        Next
		End If
		%>
		
		
		</SELECT></td></tr>
		<tr><td><br></td></tr>
		<tr><td align=center><INPUT type="submit" value="Acknowledge" id=Acknowledge name="Submit"></td></tr>
	</table>
	</td></tr></table>
	</td> </tr></TABLE>
	<BR>
   
   <INPUT type="submit" value="Details" id=submit1 name=submit> 
	<INPUT type="submit" value="holdings" id=submit2 name=submit>
	<INPUT type="submit" value="History" id=submit3 name=submit>
	<INPUT type="submit" value="Pending" id=submit4 name=submit>
	
	<INPUT type="submit" value="Trade" id=submit5 name=submit
	<% if session("LoggedOnAs") = "representative" then %>
	disabled
	<%end if %>
	>
	<INPUT type="submit" value="Quote" id=submit6 name=submit>
   </FORM> 
</BODY>


</HTML>
