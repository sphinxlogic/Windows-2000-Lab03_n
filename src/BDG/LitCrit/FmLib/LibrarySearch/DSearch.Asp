<% ' Copyright 1998-1999 Microsoft Corporation. All rights reserved. %>

<!-- DATA CONTROL -- Search Results -->
<object id="RDS_SearchResults" CLASSID="clsid:BD96C556-65A3-11D0-983A-00C04FC29E33" height="1" width="1" VIEWASTEXT>
</object>

<!-- BUTTONS -- Sort By Title highlighted -->
<div ID="SortByTitle" STYLE="DISPLAY: none; LEFT: 300px; POSITION: absolute; TOP: 50px; HEIGHT: 50px">
	<span style="COLOR: #000000; FONT-FAMILY: Verdana,arial; FONT-SIZE: 10pt;">Sort By</span>
	<span class="SubButtonDown" onClick="sortBy('title')" style="POSITION: relative; TOP: 5px; WIDTH: 100px">Title</span>
	<span class="SortSubButton" onClick="sortBy('pubYear')" style="POSITION: relative; TOP: 5px; WIDTH: 100px">Pub Date</span>
	<span class="SortSubButton" onClick="sortBy('coll')" style="POSITION: relative; TOP: 5px; WIDTH: 100px">Collection</span>
   <br>
</div>

<!-- BUTTONS -- Sort By PubDate highlighted -->
<div ID="SortByPubDate" STYLE="DISPLAY: none; LEFT: 300px; POSITION: absolute; TOP: 50px; HEIGHT: 50px">
	<span style="COLOR: #000000; FONT-FAMILY: Verdana,arial; FONT-SIZE: 10pt;">Sort By</span>
	<span class="SortSubButton" onClick="sortBy('title')" style="POSITION: relative; TOP: 5px; WIDTH: 100px">Title</span>
	<span class="SubButtonDown" onClick="sortBy('pubYear')" style="POSITION: relative; TOP: 5px; WIDTH: 100px">Pub Date</span>
	<span class="SortSubButton" onClick="sortBy('coll')" style="POSITION: relative; TOP: 5px; WIDTH: 100px">Collection</span>
   <br>
</div>

<!-- BUTTONS -- Sort By Collection highlighted -->
<div ID="SortByCollection" STYLE="DISPLAY: none; LEFT: 300px; POSITION: absolute; TOP: 50px; HEIGHT: 50px">
	<span style="COLOR: #000000; FONT-FAMILY: Verdana,arial; FONT-SIZE: 10pt; ">Sort By</span>
	<span class="SortSubButton" onClick="sortBy('title')" style="POSITION: relative; TOP: 5px; WIDTH: 100px">Title</span>
	<span class="SortSubButton" onClick="sortBy('pubYear')" style="POSITION: relative; TOP: 5px; WIDTH: 100px">Pub Date</span>
	<span class="SubButtonDown" onClick="sortBy('coll')" style="POSITION: relative; TOP: 5px; WIDTH: 100px">Collection</span>
   <br>
</div>

<!-- RESULTS TABLE -->
<div ID="PleaseWait" STYLE="DISPLAY: none; POSITION: absolute; LEFT: 300px; TOP: 113px; ALIGN: Center;">
Retrieving search results from server.  Please wait...	
</div>

<div ID="NoRecords" STYLE="DISPLAY: none; POSITION: absolute; LEFT: 300px; TOP: 113px; ALIGN: Center;">
Your search text didn't match any records.
</div>

<div ID="SearchResults" STYLE="DISPLAY: none; LEFT: 265px; POSITION: absolute; TOP: 130px;FONT-SIZE:1px">
   <table ID="TBL_SearchResults" BORDER="0" CELLSPACING="2" CELLPADDING="0" COLS="2" WIDTH="100%" DATASRC="#RDS_SearchResults" DATAPAGESIZE="6">
   <tbody>
      <tr VALIGN="Center"><td><img DATAFLD="Icon"></td><td>
      <table WIDTH="100%" BORDER="0" CELLSPACING="2" CELLPADDING="0" COLS="2">
      <tbody>
         <tr><td COLSPAN="2"><a DATAFLD="Link" TITLE="Display more details for this item"><span CLASS="Title" DATAFLD="Title"></span></a></td></tr>
         <tr><td WIDTH="50%">Call#: <span DATAFLD="Call"></span></td><td>Published: <span DATAFLD="PubYear"></span></td></tr>
         <% If Application("CritiqueEnabled") = True Then %>
         <tr><td COLSPAN="2">Avg. Critique Rating: <a onMouseOver="javascript:ShowRatings()" onMouseOut="javascript:HideRatings()"><img DATAFLD="Rating" ALIGN="Center" BORDER="0"></a></td></tr>
         <% End If %>
      </tbody>
      </table>
   </td></tr>
   </tbody>
   </table>
</div>

<div ID="showPages" STYLE="DISPLAY: none; LEFT: 568px; POSITION: absolute; TOP:98px;FONT-WEIGHT:BOLD;">
Page: 
</div>
<div ID="countPages" STYLE="DISPLAY: none; LEFT: 613px; POSITION: absolute; TOP:98px">
of
</div>

<!-- PAGING BUTTONS -->
<div ID="NoPageButtons" STYLE="DISPLAY: none;LEFT:300px; POSITION:absolute;TOP:90px;">
	<span class="UpButton" style="POSITION: relative; TOP: 5px; WIDTH:60px; COLOR: #C0C0C0;cursor:default">|&lt;</span>
	<span class="UpButton" style="POSITION: relative; TOP: 5px; WIDTH:60px; COLOR: #C0C0C0;cursor:default">&lt;&lt;</span>
	<span class="UpButton" style="POSITION: relative; TOP: 5px; WIDTH:65px; COLOR: #C0C0C0;cursor:default">&gt;&gt;</span>
	<span class="UpButton" style="POSITION: relative; TOP: 5px; WIDTH:60px; COLOR: #C0C0C0;cursor:default">&gt;|</span>
	<b>Page 1</b> of <b>1</b>
   <br>
</div>

<div ID="FirstPageButtons" STYLE="DISPLAY: none;LEFT:300px; POSITION:absolute;TOP:90px;">
	<span class="UpButton" style="POSITION: relative; TOP: 5px; WIDTH:60px; COLOR: #C0C0C0; cursor:default">|&lt;</span>
	<span class="UpButton" style="POSITION: relative; TOP: 5px; WIDTH:60px; COLOR: #C0C0C0; cursor:default">&lt;&lt;</span>
	<span class="UpButton" onClick="NextPage()" OnMouseDown="javascript:push()" OnMouseUp="javascript:unPush()" style="POSITION: relative; TOP: 5px; WIDTH:65px">&gt;&gt;</span>
	<span class="UpButton" onClick="LastPage()" OnMouseDown="javascript:push()" OnMouseUp="javascript:unPush()" style="POSITION: relative; TOP: 5px; WIDTH:60px">&gt;|</span>
   <br>
</div>
<div ID="NextPageButtons" STYLE="DISPLAY: none;LEFT:300px; POSITION: absolute; TOP:90px;">
	<span class="UpButton" onClick="FirstPage()" OnMouseDown="javascript:push()" OnMouseUp="javascript:unPush()" style="POSITION: relative; TOP: 5px; WIDTH:60px;">|&lt;</span>
	<span class="UpButton" onClick="PrevPage()" OnMouseDown="javascript:push()" OnMouseUp="javascript:unPush()" style="POSITION: relative; TOP: 5px; WIDTH:60px;">&lt;&lt;</span>
	<span class="UpButton" onClick="NextPage()" OnMouseDown="javascript:push()" OnMouseUp="javascript:unPush()" style="POSITION: relative; TOP: 5px; WIDTH:65px;">&gt;&gt;</span>
	<span class="UpButton" onClick="LastPage()" OnMouseDown="javascript:push()" OnMouseUp="javascript:unPush()" style="POSITION: relative; TOP: 5px; WIDTH:60px;">&gt;|</span>
   <br>
</div>

<div ID="LastPageButtons" STYLE="DISPLAY: none;LEFT:300px; POSITION: absolute; TOP:90px;">
	<span class="UpButton" onClick="FirstPage()" OnMouseDown="javascript:push()" OnMouseUp="javascript:unPush()" style="POSITION: relative; TOP: 5px; WIDTH:60px;">|&lt;</span>
	<span class="UpButton" onClick="PrevPage()" OnMouseDown="javascript:push()" OnMouseUp="javascript:unPush()" style="POSITION: relative; TOP: 5px; WIDTH:60px;">&lt;&lt;</span>
	<span class="UpButton" style="POSITION: relative; TOP: 5px; WIDTH:65px; COLOR: #C0C0C0;cursor:default">&gt;&gt;</span>
	<span class="UpButton" style="POSITION: relative; TOP: 5px; WIDTH:60px; COLOR: #C0C0C0;cursor:default">&gt;|</span>
   <br>
</div>

<div ID="RatingsLegend" STYLE="DISPLAY: none; POSITION: absolute; BACKGROUND: #fafad2; WIDTH=260px; Z-INDEX=40" onMouseOut="HideRatings()">
<table BORDER="0" CELLPADDING="0" CELLSPACING="2">
<tr><td>&nbsp;<img SRC="../images/star4.0.gif" BORDER="0" WIDTH="50" HEIGHT="12"><font SIZE="-2">&nbsp;&nbsp;Highly recommended</font></td></tr>
<tr><td>&nbsp;<img SRC="../images/star3.0.gif" BORDER="0" WIDTH="50" HEIGHT="12"><font SIZE="-2">&nbsp;&nbsp;Recommended</font></td></tr>
<tr><td>&nbsp;<img SRC="../images/star2.0.gif" BORDER="0" WIDTH="50" HEIGHT="12"><font SIZE="-2">&nbsp;&nbsp;Recommended with reservations</font></td></tr>
<tr><td>&nbsp;<img SRC="../images/star1.0.gif" BORDER="0" WIDTH="51" HEIGHT="12"><font SIZE="-2">&nbsp;&nbsp;Best avoided</font></td></tr>
</table>
</div>

<script Language="VBScript">
SUB RDS_SearchResults_OnReadyStateChange()
   ' MsgBox "Ready State: " & RDS_SearchResults.ReadyState
End Sub

'Fires when data has arrived
Sub RDS_SearchResults_OnDataSetChanged()  
   ' MsgBox "Data Set Changed"
   If RDS_SearchResults.Recordset.State = adcStateOpen Then
      PleaseWait.style.display = "none"
      Document.Body.style.cursor = "auto"
      If RDS_SearchResults.Recordset.EOF Then
         NoRecords.style.display = ""
      Else
         SearchResults.style.display = ""
         ' BUG : Hard-coded pagesize
         If RDS_SearchResults.Recordset.RecordCount > 6 Then
            RDS_SearchResults.Recordset.PageSize = 6
            FirstPageButtons.style.display = ""
            showPages.style.display=""
            CountPages.style.display =""
            CurrentPage = 1
            TotalPage = RDS_SearchResults.Recordset.PageCount
            call ClearCountValues()
            call InsertCountValues()
         Else 
            NoPageButtons.style.display=""
         End If
      End If
   End If
End Sub

Sub RDS_SearchResults_OnError(SCode,Description,Source,CancelDisplay)
   MsgBox Description,vbCritical,Source
   PleaseWait.style.display = "none"
   NoRecords.style.display = ""
   CancelDisplay = True
End Sub
</script>

<script Language="VBScript">
Sub ShowRatings()
   RatingsLegend.style.posTop = window.event.clientY
   RatingsLegend.style.posLeft = window.event.clientX
   RatingsLegend.style.display = ""
End Sub
Sub HideRatings()
   RatingsLegend.style.display = "none"
End Sub
</script>

<script Language="VBScript">
Dim CurrentPage,TotalPage

'--- Called during sortBy "button" clicks
Sub changeSortBy(x)
   sortByTitle.style.display = "none"
   sortByPubDate.style.display = "none"
   sortByCollection.style.display = "none"
   call ClearCountValues()

   Select Case x
   Case "title"
      'Do sorting in ascending order of title
      RDS_SearchResults.SortDirection = True
      SortByTitle.style.display = ""
   Case "coll"
      'Do sorting in ascending order of collection
      RDS_SearchResults.SortDirection = True
      SortByCollection.style.display = ""
   Case Else
      'Do sorting in descending order of pubdate
      RDS_SearchResults.SortDirection = False
      SortByPubDate.style.display = ""
   End Select
  
End Sub

Sub sortBy(x)
   If RDS_SearchResults.ReadyState <> adcReadyStateComplete Then
      MsgBox "Query results still arriving.  Please wait...", vbInformation
      Exit Sub
   End If
   
   changeSortBy x
   
   'sorting the columns in the result table
   RDS_SearchResults.SortColumn = x
   RDS_SearchResults.Reset
   CurrentPage = 1
End Sub

'--- Called by page "button" clicks

Sub NextPage()
   If CurrentPage < RDS_SearchResults.Recordset.PageCount Then
      TBL_SearchResults.nextPage()
      CurrentPage = CurrentPage + 1
      call ClearCountValues()
      call InsertCountValues()
      call checkPage
   End If
 End Sub

Sub PrevPage()
   If CurrentPage > 1 Then
      TBL_SearchResults.previousPage()
      CurrentPage = CurrentPage - 1
      call ClearCountValues()
      call InsertCountValues()
      call checkPage
       
   End If
 End Sub

Sub FirstPage()
   If CurrentPage > 1 Then
      TBL_SearchResults.Refresh
      CurrentPage = 1
      call ClearCountValues()
      call InsertCountValues()
      call checkPage
   End If
 End Sub

Sub LastPage()
   If CurrentPage < TotalPage Then
      GotoPage TotalPage
      call ClearCountValues()
      call InsertCountValues()
      call checkPage
   End If
 End Sub

Sub GotoPage(LastPage)
   Dim i
   If CurrentPage < LastPage Then
      For i = CurrentPage To LastPage
         TBL_SearchResults.nextPage
      Next
   ElseIf CurrentPage > LastPage Then
      For i = LastPage To CurrentPage
         TBL_SearchResults.previousPage
      Next
   End If
   CurrentPage = LastPage
End Sub

'--- Checks current page no.and accordingly flips on corresponding divs

Sub checkPage()
  const firstpage = 1
  Select case CurrentPage
  case firstpage 
    firstPageButtons.style.display=""
    nextPageButtons.style.display="none"
    lastPageButtons.style.display="none"
  case totalpage
    firstPageButtons.style.display ="none" 
    nextPageButtons.style.display ="none"
    lastPageButtons.style.display= ""
  case else
    firstPageButtons.style.display="none"
    nextPageButtons.style.display=""
    lastPageButtons.style.display="none"
  End select
End Sub
  
'--- The following routines are called from the child IFRAME

Sub ShowSortBy(sSort)
   ClearAllSortBy
   Select Case UCase(sSort)
      Case "TITLE":   Parent.sortByTitle.style.display = ""
      Case "COLL":    Parent.sortByCollection.style.display = ""
      Case Else:      Parent.sortByPubDate.style.display = ""
   End Select
End Sub

Sub ClearAllSortBy()
  	  Parent.sortByTitle.style.display = "none"
	  Parent.sortByPubDate.style.display = "none"
	  Parent.sortByCollection.style.display = "none"
	  Parent.nopagebuttons.style.display="none"
	  Parent.firstpageButtons.style.display = "none"
	  Parent.nextpageButtons.style.display = "none"
	  Parent.lastpageButtons.style.display = "none"
	  Parent.showPages.style.display = "none"
	  Parent.countPages.style.display = "none"
	  Parent.pleaseWait.style.display = "none"
	  Parent.noRecords.style.display = "none"
End Sub

</script>

<script Language="javascript">
//Inserts the Current  Page Numbering
function InsertCountValues(){
    with(document.all) {
    switch(CurrentPage){
      case TotalPage:
        countPages.insertAdjacentHTML("Afterbegin","<b>" + TotalPage + "&nbsp;" + "<b>");
        countPages.insertAdjacentHTML("BeforeEnd", "<b>"+ "&nbsp;" + TotalPage + "<b>");
        break;
      default:
        countPages.insertAdjacentHTML("Afterbegin","<b>" + CurrentPage+ "&nbsp;" + "<b>");
        countPages.insertAdjacentHTML("BeforeEnd", "<b>"+ "&nbsp;" + TotalPage + "<b>");
        break;
    }
    }
 }
//Clear the Current Page Numbering
function ClearCountValues(){
    document.all.countPages.innerHTML = "of";
}
</script>