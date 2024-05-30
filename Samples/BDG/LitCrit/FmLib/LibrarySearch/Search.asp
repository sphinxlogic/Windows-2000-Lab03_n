<%@ Language=VBScript Transaction=Required %>
<% ' Copyright 1998-1999 Microsoft Corporation. All rights reserved. %>
<% Option Explicit %>
<!--#include file="tablemgr.asp"-->
<script LANGUAGE=VBScript RUNAT=Server>
Sub ReportError(strError)
      Response.Write "<" & "script LANGUAGE=""VBScript"">" & vbCrLf & "MsgBox """ & _
                     Replace(strError,vbCrLf,"") & """, vbCritical, ""Error""" & vbCrLf & "<" & "/script>"
      Response.End
End Sub
</script>
<% Dim strTableName,strSearch,optSearch,newSearch
   Dim cbAV,cbBook,cbPrd,cbRef,cbSoft
   Dim count,joinStrings,joinValues,index,checkString
   Dim WhereClz()

   '---checks if the entry is done from user to radiobuttons or is it using session variables
   newSearch = CStr(Request.QueryString("newSearch"))
   
   '--- Yes signifies that its new search done by the user and not to use session variables
   '--- otherwise it assumes that user has clicked the refresh button to refresh the page
   '--- and in this case it has to use session variables
   
   If newSearch = "Yes" Then
      strSearch = CStr(Request.QueryString("CurrentWord"))
      optSearch = CInt(Request.QueryString("optSearch"))
    
      '--- Get selected collections from QueryString   
      cbAV   = CInt(Request.QueryString("cbAV"))
      cbBook = CInt(Request.QueryString("cbBook"))
      cbPrd  = CInt(Request.QueryString("cbPrd"))
      cbRef  = CInt(Request.QueryString("cbRef"))
      cbSoft = CInt(Request.QueryString("cbSoft"))
   End If  

   If Not (IsEmpty(strSearch) Or strSearch="") Then
      Dim oSearch, iCounter
      
      '--- Save IFRAME location for refresh
      Session("LastPage")  = "search.asp?CurrentWord=" & strSearch
      Session("SearchWord")= strSearch
      Session("optSearch") = optSearch
      Session("cbAV")      = cbAV
      Session("cbBook")    = cbBook
      Session("cbPrd")     = cbPrd
      Session("cbRef")     = cbRef
      Session("cbSoft")    = cbSoft
      
      joinStrings = Array("AV","Book","Prd","Ref","Soft")
      joinValues  = Array(cbAV,cbBook,cbPrd,cbRef,cbSoft)
   
      '--- Make an array of the selected document types, for passing to Search function
      index = 0
      For count = 0 to UBound(joinValues)
        If joinValues(count) Then 
          Redim Preserve WhereClz(index)
          WhereClz(index) = joinStrings(count)
          index = index + 1
        End if
      Next
      
      checkString = Join(whereClz)

      If IsEmpty(checkString) or checkString="" Then ReportError "Please include at least one collection type for your search"
      
      '--- Pick a number from 1 to 100
      Randomize 
      iCounter = CInt(Rnd * 100) + 1

      strTableName = "srch" & Now() & iCounter
      strTableName = Replace(strTableName, " ", "")
      strTableName = Replace(strTableName, "-", "")
      strTableName = Replace(strTableName, "/", "")
      strTableName = Replace(strTableName, ":", "")
      'MsgBox "strTableName = " & Table

      '--- Store table name now for dropping later...
      AddSearchTable strTableName
      Session("TblName") = strTableName
   
      Set oSearch = Server.CreateObject("CML.Search")
      oSearch.SearchString = strSearch
      oSearch.ConnectionString = Application("FmLib_ConnectionString")
      oSearch.ConnectionTimeout = Application("ConnectionTimeout")
      
      On Error Resume Next
      oSearch.SearchType = ftsInflection
      oSearch.CreateTable  strTableName, whereClz, optSearch
      Set oSearch = Nothing
      
      If Err.Number <> 0 Then ReportError Err.Description 

   Else
      ' Called when re-doing current search
      strTableName = Session("TblName")
      strSearch    = Session("SearchWord")
      optSearch    = Session("optSearch")
      cbAV         = Session("cbAV")
      cbBook       = Session("cbBook")
      cbPrd        = Session("cbPrd")
      cbRef        = Session("cbRef")
      cbSoft       = Session("cbSoft")
      
      If IsEmpty(strTableName) or strTableName = "" Then
         optSearch = cbAV = cbBook = cbprd = cbRef = cbSoft = 1
         ReportError("Yours session has timed out. Previous search results are no longer available")
      End If
   End If   
  
%>
<html>
<title>Searching for: <%= strSearch %></title>
<script Language=VBScript>
<!-- #include file="adcvbs.inc" -->

   Dim nRet,RDS
   
   ' If search request will interrupt current query, ask user to cancel
   If Parent.RDS_SearchResults.ReadyState <> adcReadyStateComplete Then
      nRet = MsgBox("Cancel current query results?", vbQuestion + vbYesNo + vbDefaultButton2)
      If nRet = vbYes Then
         Parent.RDS_SearchResults.Cancel
      End If
   Else
      nRet = vbYes
   End If

   If nRet = vbYes Then
      Set RDS = Parent.RDS_SearchResults
      If <%=optSearch%> = 1 Then     
          Parent.cbTitle.checked = true
      Elseif  <%=optSearch%> = 2 Then 
          Parent.cbAuthor.checked = true
      Else 
          Parent.cbSubject.checked = true
      End if
      
      Parent.SetCheckBoxes <%= cbAV%>,<%= cbBook%>,<%= cbPrd %>,<%= cbRef %>,<%= cbSoft %>
      Parent.ClearAllDivs()
      Parent.ShowSortBy(RDS.SortColumn)
      Parent.PleaseWait.style.display = ""
      Parent.txtWord.Value = "<%= strSearch %>"
      Parent.CurrentPage = 1
      
      ' Instruct RDS control to retrieve search results from table of results
      RDS.ExecuteOptions = adcExecAsync
      RDS.FetchOptions = adcFetchAsync
      RDS.Handler = "MSDFMAP.Handler,FmLibMap.ini"
      RDS.Server = "http://<%= Request.ServerVariables("SERVER_NAME") %>"
      RDS.Connect = "Data Source=FmLib"
      RDS.SQL = "DetailsFromSearch(<%= strTableName %>)"
      RDS.Refresh
   End If
</script>
</html>