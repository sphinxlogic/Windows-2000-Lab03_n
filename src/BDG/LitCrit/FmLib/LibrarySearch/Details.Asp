<%@ Language=VBScript %>
<% ' Copyright 1998-1999 Microsoft Corporation. All rights reserved. %>
<% Option Explicit %>
<% Dim nBibNo

   nBibNo = Request.QueryString("bibno")
   If IsEmpty(nBibNo) Or nBibNo="" Then
      Response.Write "ERROR: Must specify a valid Bib number."
      Response.End
   Else
      nBibNo = CLng(nBibNo)
      If nBibNo = 0 Then
         Response.Write "ERROR: Invalid Bib number specified."
         Response.End
      End If
   End If
   
   '--- Save IFRAME location for refresh
   Session("LastPage") = "details.asp?BibNo=" & nBibNo
%>       
<html>
<title>Title details for Bib#: <%= nBibNo %></title>
<script LANGUAGE=VBScript>
<!-- #include file="adcvbs.inc" -->

   If Parent.RDS_LongDisplay.ReadyState <> adcReadyStateComplete Then
      MsgBox "Query results still arriving.  Please wait...", vbInformation
   Else
      Parent.ClearAllDivs()
      Parent.PleaseWait.style.display = ""
      
      ' Retrieve the details of this title from the database
      Set RDS = Parent.RDS_LongDisplay
      RDS.ExecuteOptions = adcExecSync
      RDS.FetchOptions = adcFetchUpFront
      RDS.Handler = "MSDFMAP.Handler,FmLibMap.ini"
      RDS.Server = "http://<%= Request.ServerVariables("SERVER_NAME") %>"
      RDS.Connect = "Data Source=FmLib"
      RDS.SQL = "TitleDetailLong(<%= nBibNo %>)"
      RDS.Refresh
      
      ' Retrieve the authors
      Set RDS = Parent.RDS_AuthorDetail
      RDS.ExecuteOptions = adcExecSync
      RDS.FetchOptions = adcFetchUpFront
      RDS.Handler = "MSDFMAP.Handler,FmLibMap.ini"
      RDS.Server = "http://<%= Request.ServerVariables("SERVER_NAME") %>"
      RDS.Connect = "Data Source=FmLib"
      RDS.SQL = "AuthorDetail(<%= nBibNo %>)"
      RDS.Refresh

      ' Retrieve the subject keywords
      Set RDS = Parent.RDS_SubjectDetail
      RDS.ExecuteOptions = adcExecSync
      RDS.FetchOptions = adcFetchUpFront
      RDS.Handler = "MSDFMAP.Handler,FmLibMap.ini"
      RDS.Server = "http://<%= Request.ServerVariables("SERVER_NAME") %>"
      RDS.Connect = "Data Source=FmLib"
      RDS.SQL = "SubjectDetail(<%= nBibNo %>)"
      RDS.Refresh
   End If      
</script>
</html>