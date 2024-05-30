<xsl:stylesheet xmlns:xsl="http://www.w3.org/TR/WD-xsl">
	<xsl:template match="/">
		<xsl:apply-templates/>
	</xsl:template>

	<xsl:template match="*">
		<DIV class="style1">
			<xsl:attribute name="id"><xsl:eval>unique()</xsl:eval></xsl:attribute>

		<SPAN class="dataNode" onclick="toggleDataBreak()">&lt;<xsl:node-name/><xsl:apply-templates select="@*"/> /&gt;</SPAN>
		</DIV>
	</xsl:template>

	<xsl:template match="*[node()]">
		<DIV class="style1">
			<xsl:attribute name="id"><xsl:eval>unique()</xsl:eval></xsl:attribute>
		<SPAN class="dataNode" onclick="toggleDataBreak()">&lt;<xsl:node-name/><xsl:apply-templates select="@*"/>&gt;</SPAN>
		<xsl:apply-templates/>&lt;/<xsl:node-name/>&gt;
		</DIV>
	</xsl:template>

	<xsl:template match="textnode()"><xsl:value-of/></xsl:template>
		
	<xsl:template match="cdata()">
		<pre>&lt;![CDATA[<xsl:value-of/>]]&gt;</pre>
	</xsl:template>
		
	<xsl:template match="@*">
		<xsl:entity-ref name="nbsp"/><SPAN class="styleAttr" onclick="toggleDataBreakAt()">
			<xsl:attribute name="id"><xsl:eval>uniqueAttr()</xsl:eval></xsl:attribute>
		<xsl:node-name/>="<xsl:value-of/>"</SPAN>
	</xsl:template>
	
	<xsl:script>
		<![CDATA[
			var idNum = 0;
			
			function unique() {
				return "data" + idNum++;
			}

			function uniqueAttr() {
				return "data" + (idNum - 1) + "_" + this.nodeName;
			}
			
		]]>
	</xsl:script>

</xsl:stylesheet>
