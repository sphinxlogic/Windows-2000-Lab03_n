<xsl:stylesheet xmlns:xsl="http://www.w3.org/TR/WD-xsl">

	<xsl:template><xsl:copy><xsl:apply-templates select="@* | node()"/></xsl:copy></xsl:template>
	
	<xsl:template match="xsl:*"><xsl:copy><xsl:attribute name="xsl-debugger-id"><xsl:eval>unique()</xsl:eval></xsl:attribute><xsl:apply-templates select="@* | node()"/></xsl:copy></xsl:template>
		
	<xsl:script>
		<![CDATA[
			var idNum = 0;
			
			function unique() {
				return "ss" + idNum++;
			}
		]]>
	</xsl:script>
	
</xsl:stylesheet>
