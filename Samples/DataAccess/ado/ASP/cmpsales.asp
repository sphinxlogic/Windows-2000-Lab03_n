<%@ LANGUAGE=JScript%>
<html>
<head><title>Chet's Book Shop</title><head>
<body background="Cldshalf.jpg" BGCOLOR="ffffcc" TEXT="#000000">

<h1>Chet's Book Shop</h1>
<p>
Click the checkbox beside the title(s) you wish to order, 
then click "Total Your Order".
</p>

<form method="post" action="cmpprice.asp" id=form1 name=form1>
<center>
<table width="100%" border="1">

<%
	var objConn = Server.CreateObject('ADODB.Connection');
	// Replace MyServer with your Microsoft SQL Server's name.
	var sConn = 'Provider=SQLOLEDB;Server=MyServer;Database=pubs;User Id=sa;Password=;';
	var rs = Server.CreateObject('ADODB.Recordset');
	var sPrice = '';
	// Replaces NULL prices with $19.99 since it is a sample.
	var sSQL = 'SELECT title_id, title, type, ISNULL(price,19.99) FROM titles ';
	var sSQL = sSQL + ' ORDER BY type, title';
	var adOpenForwardOnly = 0;
	var adLockReadOnly = 1;

	objConn.open(sConn);

	rs.open(sSQL,objConn,adOpenForwardOnly,adLockReadOnly);

	Response.Write('<tr>\n');
	
	for(i=0;i < (rs.Fields.Count);i++)
	{
		Response.Write(' <th>');
		if(rs.Fields(i).Name != 'title_id')
		{
			Response.Write(rs.Fields(i).Name);
		}
		Response.Write('</th>\n');
	}
	
	Response.Write('</tr>\n');
		
	do
	{
		Response.Write('\n<tr>');
		Response.Write('\n  <td><input type=checkbox name=title_id value="' + rs.Fields(0) + '"></td>');
		Response.Write('\n  <td>' + rs.Fields(1) + '</td>');
		Response.Write('\n  <td>' + rs.Fields(2) + '</td>');
		Response.Write('\n  <td nowrap>' + fmtCurrency(String(rs.Fields(3))) + '</td>');
		Response.Write('\n</tr>\n');
		rs.MoveNext;
	} 
	while(!rs.eof);
	
	rs.close
	
function fmtCurrency(sValue)
{	
	var re = /\./;
	
	if(re.test(sValue))
	{
		return "$ " + sValue;
	}
		else
	{
		return "$ " + sValue + ".00";
	}
}
%>
</table>

</center>

<p>
<input type="submit" value="Total Your Order" id=submit1 name=submit1>
<input type="reset" value="Reset Selections" id=reset1 name=reset1>
</form>


<hr size="4">

<img src="ie_anim.gif" width="88" height="31" align="right" alt="ie">

</body>
</html>
