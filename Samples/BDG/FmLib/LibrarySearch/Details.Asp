<%@ Language=VBScript %>
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
      strSQL = "SELECT STUFF('../images/icon.gif',15,0,coll) AS icon," &_
               " CONVERT(char(4),t.pubdate,112) AS pubdate," &_
               " t.bib#,t.title,t.coll,t.call,t.isbn,t.notes,t.description" &_
               " FROM Title AS t WHERE t.bib#=<%= nBibNo %>"
               
      ' Instruct RDS control to retrieve search results from table of results
      Set RDS = Parent.RDS_LongDisplay
      RDS.ExecuteOptions = adcExecSync
      RDS.FetchOptions = adcFetchUpFront
      RDS.Server = "http://<%= Request.ServerVariables("SERVER_NAME") %>"
      RDS.Connect = "<%= Application("FmLib_ConnectionString") %>"
      RDS.SQL = strSQL
      RDS.Refresh
      
      ' Retrieve the authors and subject keywords
      strSQL = "SELECT DISTINCT STUFF('javascript:DoAuthor()',21,0,LTRIM(STR(a.auth#))) AS link," &_
               "       a.lname,a.fname" &_
               " FROM Title AS t, Author AS a, TitleAuth AS ta" &_
               " WHERE t.bib#=ta.bib# AND ta.auth#=a.auth# AND " &_
               "       t.bib#=<%= nBibNo %>"
               
      Set RDS = Parent.RDS_AuthorDetail
      RDS.ExecuteOptions = adcExecSync
      RDS.FetchOptions = adcFetchUpFront
      RDS.Server = "http://<%= Request.ServerVariables("SERVER_NAME") %>"
      RDS.Connect = "<%= Application("FmLib_ConnectionString") %>"
      RDS.SQL = strSQL
      RDS.Refresh

      ' Retrieve the authors and subject keywords
      strSQL = "SELECT DISTINCT STUFF('javascript:DoSubject()',22,0,LTRIM(STR(s.subj#))) AS link," &_
               "       s.text" &_
               " FROM Title AS t, Subject AS s, TitleSubj AS ts" &_
               " WHERE t.bib#=ts.bib# AND ts.subj#=s.subj# AND " &_
               "       t.bib#=<%= nBibNo %>"

      Set RDS = Parent.RDS_SubjectDetail
      RDS.ExecuteOptions = adcExecSync
      RDS.FetchOptions = adcFetchUpFront
      RDS.Server = "http://<%= Request.ServerVariables("SERVER_NAME") %>"
      RDS.Connect = "<%= Application("FmLib_ConnectionString") %>"
      RDS.SQL = strSQL
      RDS.Refresh
   End If      
</script>
</html>