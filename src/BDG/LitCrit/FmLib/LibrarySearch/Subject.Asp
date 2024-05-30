<%@ Language=VBScript %>
<% ' Copyright 1998-1999 Microsoft Corporation. All rights reserved. %>
<% Option Explicit %>
<% Dim nSubjectNo

   nSubjectNo = Request.QueryString("SubjectNo")
   If IsEmpty(nSubjectNo) Or nSubjectNo="" Then
      Response.Write "ERROR: Must specify a valid Subject number."
      Response.End
   Else
      nSubjectNo = CLng(nSubjectNo)
      If nSubjectNo = 0 Then
         Response.Write "ERROR: Invalid Subject number specified."
         Response.End
      End If
   End If
  
   '--- Save IFRAME location for refresh
   Session("LastPage") = "subject.asp?SubjectNo=" & nSubjectNo
%>
<html>
<title>Search results for Subject#: <%= nSubjectNo %></title>
<script LANGUAGE=VBScript>
<!-- #include file="adcvbs.inc" -->

   If Parent.RDS_SearchResults.ReadyState <> adcReadyStateComplete Then
      MsgBox "Query results still arriving.  Please wait...", vbInformation, "Please Wait"
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
      RDS.SQL = "SearchBySubject(<%= nSubjectNo %>)"
      RDS.Refresh
   End If
</script>
</html>
