<object id="rstCustomers" progid="ADODB.Recordset" runat="Server"></object>
<!--metadata name="Microsoft ActiveX Data Objects 2.5 Library" type="TypeLib" uuid="{00000205-0000-0010-8000-00AA006D2EA4}"-->
<%
	Option Explicit

	Dim strSQL, strConnection

	On Error Resume Next

	strConnection = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" & Server.MapPath("NWind.mdb")
	strSQL = "Select * from customers"

	rstCustomers.Open Request
'	rstCustomers.Open strSQL, strConnection

	rstCustomers.ActiveConnection = strConnection

	rstCustomers.UpdateBatch

	Response.Write "Got the Recordset in XML format back into ADO on the server."

    If Err.Number <> 0 Then
		Response.Status = "500 " + Err.Source + ": " + Err.Description
    End If

	rstCustomers.Close

    Response.End
%>