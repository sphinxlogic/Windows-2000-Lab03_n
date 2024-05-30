<% ' Copyright 1998-1999 Microsoft Corporation. All rights reserved. %>

<!-- DATA CONTROLS -- LongDisplay, AuthorDetail and SubjectDetail -->
<object id="RDS_LongDisplay" CLASSID="clsid:BD96C556-65A3-11D0-983A-00C04FC29E33"
        height=1 width=1 VIEWASTEXT>
</object>

<object id="RDS_AuthorDetail" CLASSID="clsid:BD96C556-65A3-11D0-983A-00C04FC29E33"
        height=1 width=1 VIEWASTEXT>
</object>

<object id="RDS_SubjectDetail" CLASSID="clsid:BD96C556-65A3-11D0-983A-00C04FC29E33"
        height=1 width=1 VIEWASTEXT>
</object>

<!-- BUTTONS -- Do Request highlighted -->
<div ID="LongDisplay" STYLE="DISPLAY: none; POSITION: absolute; LEFT: 265px; TOP: 50px; HEIGHT: 50px">
	<span class="UpButton" onClick="RequestClick()" 
	      OnMouseDown="javascript:push()" OnMouseUp="javascript:unPush()"
	      style="POSITION: relative; TOP: 5px; WIDTH: 100px" title="Request Title">Request Title</span>
	<span class="UpButton" onClick="ReDoCurrent()"
	      OnMouseDown="javascript:push()" OnMouseUp="javascript:unPush()"
	      style="POSITION: relative; TOP: 5px; WIDTH: 100px" title="Return to List">Return to List</span>
</div>

<!-- TABLE -- Details (Long) Display -->
<div ID="Details" STYLE="DISPLAY: none; LEFT: 265px; POSITION: absolute; TOP: 110px;FONT-SIZE:1pt">
   <table BORDER=0 CELLSPACING=2 CELLPADDING=0 COLS=2>
   <tbody>
      <tr VALIGN=Top><td><img DATASRC="#RDS_LongDisplay" DATAFLD="Icon"></td><td>
      <table ID="TBL_LongDisplay" BORDER=0 CELLSPACING=2 CELLPADDING=0 COLS=2
             DATASRC="#RDS_LongDisplay">
      <tbody>
         <tr><td COLSPAN=2><span CLASS=Title DATAFLD="Title"></span></td></tr>
         <tr><td WIDTH="30%" VALIGN=Top>Author: </td><td>
            <table ID="TBL_Authors" BORDER=0 CELLSPACING=2 CELLPADDING=0 COLS=1
             DATASRC="#RDS_AuthorDetail">
            <tbody>
               <tr><td><a DATAFLD="Link" TITLE="View other works by this author">
               <span DATAFLD="LName"></span>, <span DATAFLD="FName"></span></a></td></tr>
            </tbody>
            </table></td></tr>
         <tr><td WIDTH="30%">Call#: </td><td><span DATAFLD="Call"></span></td></tr>
         <tr><td WIDTH="30%">ISBN or ISSN: </td><td><span DATAFLD="ISBN"></span></td></tr>
         <tr><td WIDTH="30%">Published: </td><td><span DATAFLD="Pubdate"></span></td></tr>
         <tr><td WIDTH="30%">Description: </td><td><span DATAFLD="Description"></span></td></tr>
         <tr><td WIDTH="30%">Notes: </td><td><span DATAFLD="Notes"></span></td></tr>
         <tr><td WIDTH="30%" VALIGN=Top>Subject: </td><td>
            <table ID="TBL_Subjects" BORDER=0 CELLSPACING=2 CELLPADDING=0 COLS=1
             DATASRC="#RDS_SubjectDetail">
            <tbody>
               <tr><td><a DATAFLD="Link" TITLE="View other works on this subject">
               <span DATAFLD="Text"></span></a></td></tr>
            </tbody>
            </table></td></tr>
      </tbody>
      </table>
      </td></tr>
   </tbody>
   </table>
</div>

<script LANGUAGE=VBScript>
Sub RequestClick()
   DoRequest(RDS_LongDisplay.Recordset("bib#").Value)
End Sub

Sub RDS_AuthorDetail_OnReadyStateChange()
   'MsgBox "AuthorDetail: " & RDS_AuthorDetail.ReadyState
End Sub

Sub RDS_SubjectDetail_OnReadyStateChange()
   'MsgBox "SubjectDetail: " & RDS_SubjectDetail.ReadyState
End Sub

Sub RDS_LongDisplay_OnReadyStateChange()
   'Fires every time that ReadyState changes
   If RDS_LongDisplay.ReadyState = adcReadyStateComplete Then
      If RDS_LongDisplay.Recordset.State = adcStateOpen Then
         PleaseWait.style.display = "none"
         If RDS_LongDisplay.Recordset.EOF Then
            NoRecords.style.display = ""
         Else
            LongDisplay.style.display = ""
            Details.style.display = ""
         End If
      End If
   End If
End Sub

Sub RDS_LongDisplay_OnError(SCode,Description,Source,CancelDisplay)
   All_OnError SCode, Description, Source, CancelDisplay
End Sub

Sub RDS_AuthorDetail_OnError(SCode,Description,Source,CancelDisplay)
   All_OnError SCode, Description, Source, CancelDisplay
End Sub

Sub RDS_SubjectDetail_OnError(SCode,Description,Source,CancelDisplay)
   All_OnError SCode, Description, Source, CancelDisplay
End Sub

Sub All_OnError(SCode,Description,Source,CancelDisplay)
   MsgBox Description,vbCritical,Source
   PleaseWait.style.display = "none"
   NoRecords.style.display = ""
   CancelDisplay = True
End Sub

Sub ClearAllDetails()
   parent.LongDisplay.style.display = "none"
   parent.Details.style.display = "none"
End Sub
</script>


