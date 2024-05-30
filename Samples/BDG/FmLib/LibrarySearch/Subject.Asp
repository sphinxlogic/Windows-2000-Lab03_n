<%@ Language=VBScript %>
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
      strSQL = "SELECT STUFF('../images/icon.gif',15,0,coll) AS Icon," & _
               "       STUFF('javascript:DoLong()',19,0,LTRIM(STR(t.bib#))) AS Link," &_
               "       t.title,t.coll,t.call,convert(char(4),t.pubdate,112) AS Pubdate" &_
               " FROM Title AS t, Subject AS s, TitleSubj AS ts" &_
               " WHERE t.bib#=ts.bib# AND ts.subj#=s.subj# AND " &_
               "       s.subj#=<%= nSubjectNo %> AND t.n_items>0"

      ' Instruct RDS control to retrieve search results from table of results
      RDS.ExecuteOptions = adcExecAsync
      RDS.FetchOptions = adcFetchAsync
      RDS.Server = "http://<%= Request.ServerVariables("SERVER_NAME") %>"
      RDS.Connect = "<%= Application("FmLib_ConnectionString") %>"
      RDS.SQL = strSQL
      RDS.Refresh
   End If
</script>
</html>
