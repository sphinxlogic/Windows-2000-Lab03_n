<%@ Language=VBScript %>
<% ' Copyright 1998-1999 Microsoft Corporation. All rights reserved. %>
<% Option Explicit %>
<% Dim nAuthorNo

   nAuthorNo = Request.QueryString("AuthorNo")
   If IsEmpty(nAuthorNo) Or nAuthorNo="" Then
      Response.Write "ERROR: Must specify a valid Author number."
      Response.End
   Else
      nAuthorNo = CLng(nAuthorNo)
      If nAuthorNo = 0 Then
         Response.Write "ERROR: Invalid Author number specified."
         Response.End
      End If
   End If
   
   '--- Save IFRAME location for refresh
   Session("LastPage") = "author.asp?AuthorNo=" & nAuthorNo
%>       
<html>
<title>Search Results for Author#: <%= nAuthorNo %></title>
<script LANGUAGE=VBScript>
<!-- #include file="adcvbs.inc" -->

   If Parent.RDS_SearchResults.ReadyState <> adcReadyStateComplete Then
      MsgBox "Query results still arriving.  Please wait...", vbInformation,"Waiting Box"
   Else
      Set RDS = Parent.RDS_SearchResults
      
      Parent.ClearAllDivs()
      Parent.ShowSortBy(RDS.SortColumn)
      Parent.PleaseWait.style.display = ""
      Parent.CurrentPage = 1
      
      ' Retrieve the details of this title from the database
      RDS.ExecuteOptions = adcExecAsync
      RDS.FetchOptions = adcFetchAsync
      RDS.Handler = "MSDFMAP.Handler,FmLibMap.ini"
      RDS.Server = "http://<%= Request.ServerVariables("SERVER_NAME") %>"
      RDS.Connect = "Data Source=FmLib"
      RDS.SQL = "SearchByAuthor(<%= nAuthorNo %>)"
      RDS.Refresh
   End If
</script>
</html>

