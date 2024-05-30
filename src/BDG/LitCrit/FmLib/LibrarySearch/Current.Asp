<%@ Language=VBScript EnableSessionState=False %>
<% ' Copyright 1998-1999 Microsoft Corporation. All rights reserved. %>
<html>
<title>Current Search Results</title>
<script LANGUAGE=VBScript>
   <!--#include file="adcvbs.inc"-->
   
   ' This script readjusts parent DIVs to return to previous display
   Set RDS = Parent.RDS_SearchResults
   If RDS.Recordset.State = adcStateOpen Then
      Parent.ClearAllDivs
      Parent.window.changeSortBy(RDS.SortColumn)
      If RDS.Recordset.EOF Then
         Parent.NoRecords.style.display = ""
      Else
         Parent.SearchResults.style.display = ""
         ' BUG : Hard-coded pagesize
         If RDS.Recordset.RecordCount > 6 Then
            Call Parent.window.checkPage()
            Parent.showPages.style.display = ""
            Parent.CountPages.style.display = ""
            Call Parent.window.ClearCountValues()
            Call Parent.window.InsertCountValues()
         End If
      End If
   Else
      ' No current recordset, so use the last FTS results
      Parent.document.all.ifControl.src = "search.asp"
   End If
</script>
</html>