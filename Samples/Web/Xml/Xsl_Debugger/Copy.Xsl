<xsl:stylesheet xmlns:xsl="http://www.w3.org/TR/WD-xsl">
	<xsl:template match="/"><xsl:apply-templates/></xsl:template>
	
	<xsl:template match="text()"><xsl:value-of/></xsl:template>
	
	<xsl:template match="*"><xsl:copy><xsl:apply-templates select="@* | node()"/></xsl:copy></xsl:template>
		
	<xsl:template match="@*"><xsl:attribute><xsl:value-of/></xsl:attribute></xsl:template>
</xsl:stylesheet>
