<xsl:stylesheet xmlns:xsl="http://www.w3.org/TR/WD-xsl">
	<xsl:template match="/"><xsl:apply-templates/></xsl:template>
	
	<xsl:template match="*">
		<DIV class="style1">
	  	<SPAN class="style1">&lt;<xsl:node-name/><xsl:apply-templates select="@*"/> /&gt;</SPAN>
		</DIV>
	</xsl:template>
		
	<xsl:template match="xsl:*">
		<DIV class="style1" onclick="toggleBreak()">
			<xsl:attribute name="id"><xsl:eval>unique()</xsl:eval></xsl:attribute>
  		<SPAN class="xslNode">&lt;<xsl:node-name/><xsl:apply-templates select="@*"/> /&gt;</SPAN>
		</DIV>
	</xsl:template>

	<xsl:template match="*[node()]">
		<DIV class="style1">
  		<SPAN class="style1">&lt;<xsl:node-name/><xsl:apply-templates select="@*"/>&gt;</SPAN>
	  	<xsl:apply-templates/><SPAN class="style1">&lt;/<xsl:node-name/>&gt;</SPAN>
		</DIV>
	</xsl:template>

	<xsl:template match="xsl:*[node()]">
		<DIV class="style1" onclick="toggleBreak()">
  		<xsl:attribute name="id"><xsl:eval>unique()</xsl:eval></xsl:attribute>
	  	<SPAN class="xslNode">&lt;<xsl:node-name/><xsl:apply-templates select="@*"/>&gt;</SPAN>
		  <xsl:apply-templates/><SPAN class="xslEndNode">&lt;/<xsl:node-name/>&gt;</SPAN>
		</DIV>
	</xsl:template>

	<xsl:template match ="textnode()"><xsl:value-of/></xsl:template>
		
	<xsl:template match ="cdata()">
		&lt;![CDATA[<pre><xsl:value-of/></pre>]]&gt;
	</xsl:template>

	<xsl:template match="@*">
		<xsl:entity-ref name="nbsp"/><xsl:node-name/>="<xsl:value-of/>"
	</xsl:template>

	<xsl:script>
		<![CDATA[
			var idNum = 0;
			
			function unique() {
				return "ss" + idNum++;
			}
			
		]]>
	</xsl:script>
</xsl:stylesheet>
