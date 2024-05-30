<%@ LANGUAGE=JScript%>
<html>
<head><title>Chet's Damage Assessment</title><head>
<body background="Cldshalf.jpg" BGCOLOR="ffffcc" TEXT="#000000">

<h1>Invoice</h1>

<h3>Titles Ordered</h3>
<%
	var objConn  = Server.CreateObject('ADODB.Connection');
	var rsTitles = Server.CreateObject('ADODB.Recordset');
	var sConn    = 'Provider=SQLOLEDB;Server=MyServer;Database=pubs;User Id=sa;Password=;';
	var sRequest = String(Request('title_id'));
	var sSQL     = '';
	
	var adOpenForwardOnly = 0;
	var adLockReadOnly = 1;
		
	vTitleIds = sRequest.split(', ');

	//Print titles ordered
	for(i=0;i<vTitleIds.length;i++)
	{
		if(i!=0)
		{
			sSQL = sSQL + ' OR title_id=\'' + vTitleIds[i] + "'";
		}
		else
		{
			sSQL = 'SELECT title FROM titles WHERE title_id=\'' + vTitleIds[i] + '\'';
		}
	}
	
	objConn.Open(sConn);
	rsTitles.Open(sSQL, objConn, adOpenForwardOnly, adLockReadOnly);
	
	do
	{
		Response.Write(rsTitles(0) + '<br>');
		rsTitles.MoveNext;
	} while(!rsTitles.EOF);
		
	rsTitles.Close;

	// Figure out the total cost
	var sPriceSQL = 'SELECT SUM(ISNULL(price,19.99)) FROM titles WHERE';
	sPriceSQL = sPriceSQL + ' title_id = \'' + vTitleIds[0] + '\'';
	for(i=0;i<vTitleIds.length;i++)
	{
		sPriceSQL = sPriceSQL + ' OR title_id=\'' + vTitleIds[i] + '\'';
	}
		
	rsTitles.Open(sPriceSQL,objConn,adOpenForwardOnly,adLockReadOnly);
%>

<h3>Total : $ <%Response.Write(rsTitles(0));%> + Tax &amp; Shipping </h3>

<hr size="4">
<img src="ie_anim.gif" width="88" height="31" align="right" alt="ie">
	
</body>
</html>
