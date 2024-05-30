
<DIV xmlns:xsl="http://www.w3.org/TR/WD-xsl">
<TABLE style="table-layout:fixed" BORDER="2" CELLSPACING="2">
  <col width="300"/>
  <col width="300"/>
  <col width="100"/>
  <THEAD>
    <TH>TITLE</TH><TH>AUTHOR</TH><TH>PRICE</TH></THEAD>
  <xsl:for-each select="book">
  <TR>
    <TD><SPAN><xsl:value-of select="title"/></SPAN></TD>
    <TD><SPAN><xsl:value-of select="author"/></SPAN></TD>
    <TD><SPAN><xsl:value-of select="price"/></SPAN></TD>
  </TR>
  </xsl:for-each>
</TABLE>
</DIV>