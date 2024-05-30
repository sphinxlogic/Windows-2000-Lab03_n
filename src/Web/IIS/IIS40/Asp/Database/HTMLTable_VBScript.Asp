<%@ LANGUAGE = VBScript %>
<%  Option Explicit		%>

<HTML>

<HEAD>
<TITLE>Query to Fill HTML Table (using ADO Table Component)</TITLE>
</HEAD>


<BODY bgcolor="white" topmargin="10" leftmargin="10">
        
<!-- Display Header -->

<font size="4" face="Arial, Helvetica">
<b>Query to Fill HTML Table</b> (using ADO Table Component)
</font>
<br>   
<hr size="1" color="#000000">

<%
  Dim Conn			' The connection object
  Dim SQLstatement
  Dim RecSet		' The record set returned
  Dim oHTMLTable	' The HTML Table Formatter object
  Dim iRows			' The place holder for the number of rows returned in the record set

  Set Conn = Server.CreateObject("ADODB.Connection")

  ' You must first create the file DSN for this sample to look at.
  ' This SDK comes with an authors.mdb in the same directory as this file
  ' Go to Control Panels | ODBC | File DSN
  ' Select Add and Microsoft Access Driver (*.mdb)
  ' Name the DSN "Authors.dsn" and point it to the authors.mdb
  Conn.Open "FILEDSN=Authors.dsn"

  SQLstatement = "SELECT * From Authors"

  Set RecSet = Conn.Execute(SQLstatement,iRows)

  ' This sample does NOT include the HTMLTable object.  You will need to get this
  ' component from the Microsoft Web Site.  Follow the installation instructions 
  ' which come with the component to install the component.
  Set oHTMLTable = Server.CreateObject("IISSample.htmlTbl")
  oHtmlTable.Borders = True
  oHtmlTable.Caption = "<b>Authors of These Samples</b>"
  oHtmlTable.CaptionStyle = "align=left"
  oHtmlTable.AutoFormat(RecSet)

  RecSet.close
  oConn.close
%>

</BODY>

</HTML>
