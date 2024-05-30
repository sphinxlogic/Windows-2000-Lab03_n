<?xml version="1.0" encoding="ISO-8859-1"?>

<html xmlns:xsl="http://www.w3.org/TR/WD-xsl">
<body STYLE="font-family:Arial, helvetica, sans-serif; font-size:12pt; background-color:white">

<table border="1" style="table-layout:fixed" width="600">

  <col width="200"></col>

  <tr bgcolor="teal">
    <th><font color="white">CustomerId</font></th>
    <th><font color="white">CompanyName</font></th>
    <th><font color="white">ContactName</font></th>
  </tr>

<xsl:for-each select="xml/rs:data/z:row">

  <tr bgcolor="navy">
    <td><font color="white"><xsl:value-of select="@CustomerID"/></font></td>
    <td><font color="white"><xsl:value-of select="@CompanyName"/></font></td>
    <td><font color="white"><xsl:value-of select="@ContactName"/></font></td> 
  </tr>

  <xsl:for-each select="rstNestedOrders">

    <tr bgcolor="white">
		<td>Order Id: <xsl:value-of select="@OrderID"/></td>
	    <td>Order Date: <xsl:value-of select="@OrderDate"/></td>
	    <td>Shipped Date: <xsl:value-of select="@ShippedDate"/></td>
	</tr>

  </xsl:for-each>

</xsl:for-each>

</table>

</body>
</html>