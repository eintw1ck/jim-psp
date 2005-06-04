<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/TR/WD-xsl">
  <xsl:template match="root">
   <html><head><title>PSPLIBDOC XML Viewer</title></head><body>
     <xsl:apply-templates/>
   </body></html> 
  </xsl:template>

  <xsl:template match="/">
    <TABLE STYLE="border:0px solid black; width=100%">
      <TR STYLE="font-size:12pt; font-family:Verdana; font-weight:bold; text-decoration:underline">
        <TD>Libname</TD>
        <TD><xsl:value-of select="PSPLIBDOC/PSPLIBDOCOPTS/LIBNAME"/></TD>
      </TR>
      <TR STYLE="font-size:12pt; font-family:Verdana; font-weight:bold; text-decoration:underline">
        <TD>Version</TD>
        <TD><xsl:value-of select="PSPLIBDOC/PSPLIBDOCOPTS/VERSION"/></TD>
      </TR>
      <TR STYLE="font-size:12pt; font-family:Verdana; font-weight:bold; text-decoration:underline">
        <TD>Description</TD>
        <TD><xsl:value-of select="PSPLIBDOC/PSPLIBDOCOPTS/DESCRIPTION"/></TD>
      </TR>
      <TR STYLE="font-size:12pt; font-family:Verdana; font-weight:bold; text-decoration:underline">
        <TD>Comments</TD>
        <TD><xsl:value-of select="PSPLIBDOC/PSPLIBDOCOPTS/Comments"/></TD>
      </TR>
      <TR STYLE="font-size:12pt; font-family:Verdana; font-weight:bold; text-decoration:underline">
        <TD></TD>
        <TD></TD>
      </TR>
    </TABLE>

    <TABLE STYLE="border:0px solid black; width=100%">
    <TR STYLE="font-size:12pt; font-family:Verdana; font-weight:bold; text-decoration:underline">
        <TD>Filename</TD>
        <TD>PRX Name</TD>
        <TD>Version</TD>
        <TD>Mode</TD>
        <TD></TD>
    </TR>
    <xsl:for-each select="PSPLIBDOC/PRXFILES/PRXFILE" order-by="PRX">
        <TR STYLE="font-family:Verdana; font-size:12pt; padding:5px 6px">
          <TD STYLE="background-color:lightgrey"><xsl:value-of select="PRX"/></TD>
          <TD STYLE="background-color:lightgrey"><A><xsl:attribute name="href">#<xsl:value-of select="PRXNAME"/></xsl:attribute></A><xsl:value-of select="PRXNAME"/></TD>
          <TD STYLE="background-color:lightgrey"><xsl:value-of select="VERSION"/></TD>
          <TD STYLE="background-color:lightgrey"><xsl:value-of select="MODE"/></TD>
          <TD></TD>
        </TR>
    </xsl:for-each>
    </TABLE>

    <TABLE STYLE="border:0px solid black; width=100%">
      <TR STYLE="font-size:12pt; font-family:Verdana; font-weight:bold; text-decoration:underline">
        <TD>Filename</TD>
        <TD>PRX Name</TD>
        <TD>Version</TD>
        <TD></TD>
        <TD></TD>
      </TR>
      <xsl:for-each select="PSPLIBDOC/PRXFILES/PRXFILE" order-by="PRX">
        <TR STYLE="font-family:Verdana; font-size:12pt; padding:5px 6px">
          <TD STYLE="background-color:lightgrey"><xsl:value-of select="PRX"/></TD>
          <TD STYLE="background-color:lightgrey"><A><xsl:attribute name="id">#<xsl:value-of select="PRXNAME"/></xsl:attribute></A><xsl:value-of select="PRXNAME"/></TD>
          <TD STYLE="background-color:lightgrey"><xsl:value-of select="VERSION"/></TD>
          <TD STYLE="background-color:lightgrey"><xsl:value-of select="MODE"/></TD>
          <TD></TD>
        </TR>
        <xsl:for-each select="LIBRARIES/LIBRARY" order-by="PRX">
          <TR STYLE="font-family:Verdana; font-size:12pt; padding:5px 6px">
            <TD></TD>
            <TD STYLE="background-color:lightgrey"><xsl:value-of select="VERSION"/></TD>
            <TD STYLE="background-color:lightgrey"><xsl:value-of select="NAME"/></TD>
            <TD></TD>
            <TD></TD>
          </TR>      
          <TR STYLE="font-family:Verdana; font-size:12pt; padding:5px 6px">
            <TD></TD>
            <TD>Functions</TD>
            <TD></TD>
            <TD></TD>
            <TD></TD>
          </TR>      
		  <xsl:for-each select="FUNCTIONS/FUNCTION" order-by="PRX">
                <TR STYLE="font-family:Verdana; font-size:12pt; padding:5px 6px">
                  <TD></TD>
                  <TD></TD>
			<TD><xsl:value-of select="NID"/></TD>
			<TD><xsl:value-of select="NAME"/></TD>
			<TD><xsl:value-of select="RETURNTYPE"/></TD>
                </TR>      
              </xsl:for-each>
              <TR STYLE="font-family:Verdana; font-size:12pt; padding:5px 6px">
                <TD></TD>
                <TD>Variables</TD>
                <TD></TD>
                <TD></TD>
                <TD></TD>
              </TR>      
		  <xsl:for-each select="VARIABLES/VARIABLE" order-by="PRX">
		    <TR STYLE="font-family:Verdana; font-size:12pt; padding:5px 6px">
                  <TD></TD>
                  <TD></TD>
			<TD><xsl:value-of select="NID"/></TD>
			<TD><xsl:value-of select="NAME"/></TD>
			<TD><xsl:value-of select="RETURNTYPE"/></TD>
                </TR>      
              </xsl:for-each>
           </xsl:for-each>
      </xsl:for-each>
    </TABLE>
  </xsl:template>
</xsl:stylesheet>
