<%@ codepage="65001" %>
<object id="rstCustomers" progid="ADODB.Recordset" runat="Server"></object>
<!--metadata name="Microsoft ActiveX Data Objects 2.5 Library" type="TypeLib" uuid="{00000205-0000-0010-8000-00AA006D2EA4}"-->
<%
  Option Explicit
  Response.Buffer = True

  Dim strSQL, strConnection

  Response.ContentType = "text/xml"
  
  Response.Expires = 0

  ' If you need to debug this .asp file, comment out the next line.
  Response.Buffer = False

  strSQL = "SELECT CustomerID, CompanyName, ContactName FROM Customers" & _
           " ORDER By CompanyName"
  
  strConnection = "Provider=MSDataShape;Data Provider=Microsoft.Jet.OLEDB.4.0;" & _
                  "Data Source=" & Server.MapPath("NWind.mdb")
  
  rstCustomers.Open strSQL, strConnection, adOpenStatic, adLockBatchOptimistic
  
  'rstCustomers.Fields("ContactName").value = "Kamal"
  
  Response.Write "<?xml version='1.0' encoding='ISO-8859-1'?>" & vbCRLF
  
  If CBool(Request.Item("xsl")) = True Then
	Response.Write "<?xml:stylesheet type='text/xsl' href='StaticAttribute.xsl'?>" & vbCRLF
  End If

  rstCustomers.save Response, adPersistXML
	
  rstCustomers.Close
%>