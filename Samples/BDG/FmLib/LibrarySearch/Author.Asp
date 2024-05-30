<%@ Language=VBScript %>
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
      strSQL = "SELECT STUFF('../images/icon.gif',15,0,coll) AS Icon," & _
               "       STUFF('javascript:DoLong()',19,0,LTRIM(STR(t.bib#))) AS Link," &_
               "       t.title,t.coll,t.call,convert(char(4),t.pubdate,112) AS Pubdate" &_
               " FROM Title AS t, Author AS a, TitleAuth AS ta" &_
               " WHERE t.bib#=ta.bib# AND ta.auth#=a.auth# AND " &_
               "       ta.auth#=<%= nAuthorNo %> AND t.n_items>0"
      
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

