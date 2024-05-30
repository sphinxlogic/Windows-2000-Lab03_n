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
<div ID="LongDisplay" STYLE="DISPLAY: none; POSITION: absolute; LEFT: 265px; TOP: 50px; HEIGHT: 25px">
	<span class="UpButton" onClick="RequestClick()" 
	      OnMouseDown="javascript:push()" OnMouseUp="javascript:unPush()"
	      style="POSITION: relative; TOP: 5px; WIDTH: 100px" title="Request title from the library">Request Title</span>
	<span class="UpButton" onClick="ReDoCurrent()"
	      OnMouseDown="javascript:push()" OnMouseUp="javascript:unPush()"
	      style="POSITION: relative; TOP: 5px; WIDTH: 190px" title="Return to results of library search">Return to Search Results</span>
</div>

<% If Application("CritiqueEnabled") = True Then %>
<div ID="ReviewButtonsFull" STYLE="DISPLAY: none; POSITION: absolute; LEFT: 265; TOP: 78px; HEIGHT: 25px">
	<span class="UpButton" onClick="ViewCritiques()" 
	      OnMouseDown="javascript:push()" OnMouseUp="javascript:unPush()"
	      style="POSITION: relative; TOP: 5px; WIDTH: 120px" title="View existing critques for this title">View Critiques</span>
	<span class="UpButton" onClick="NewCritique()"
	      OnMouseDown="javascript:push()" OnMouseUp="javascript:unPush()"
	      style="POSITION: relative; TOP: 5px; WIDTH: 100px" title="Add new critique for this title">Add Critique</span>
</div>
<div ID="ReviewButtonsHalf" STYLE="DISPLAY: none; POSITION: absolute; LEFT: 265; TOP: 78px; HEIGHT: 15px">
	<span class="UpButton" style="POSITION: relative; TOP: 5px; WIDTH: 120px; COLOR: #C0C0C0; cursor:default" 
	      title="View existing critques for this title">View Critiques</span>
	<span class="UpButton" onClick="NewCritique()"
	      OnMouseDown="javascript:push()" OnMouseUp="javascript:unPush()"
	      style="POSITION: relative; TOP: 5px; WIDTH: 100px" title="Add new critique for this title">Add Critique</span>
</div>
<% End If %>

<!-- TABLE -- Details (Long) Display -->
<div ID="Details" STYLE="DISPLAY: none; LEFT: 265px; POSITION: absolute; TOP: 114px;FONT-SIZE:1pt">
   <table BORDER=0 CELLSPACING=2 CELLPADDING=0 COLS=2>
   <tbody>
      <tr VALIGN=Top><td><img DATASRC="#RDS_LongDisplay" DATAFLD="Icon"></td><td>
      <table ID="TBL_LongDisplay" BORDER=0 CELLSPACING=2 CELLPADDING=0 COLS=2
             DATASRC="#RDS_LongDisplay">
      <tbody>
         <tr><td COLSPAN=2><span CLASS=Title DATAFLD="Title"></span></td></tr>
         <tr><td WIDTH="30%" VALIGN=Top>Author(s): </td><td>
            <table ID="TBL_Authors" BORDER=0 CELLSPACING=2 CELLPADDING=0 COLS=1
             DATASRC="#RDS_AuthorDetail">
            <tbody>
               <tr><td><a DATAFLD="Link" TITLE="View other works by this author">
               <span DATAFLD="LName"></span>, <span DATAFLD="FName"></span></a></td></tr>
            </tbody>
            </table></td></tr>
         <tr><td WIDTH="30%">Call#: </td><td><span DATAFLD="Call"></span></td></tr>
         <tr><td WIDTH="30%">ISBN or ISSN: </td><td><span DATAFLD="ISBN"></span></td></tr>
         <tr><td WIDTH="30%">Published: </td><td><span DATAFLD="PubYear"></span></td></tr>
         <tr><td WIDTH="30%">Description: </td><td><span DATAFLD="Description"></span></td></tr>
         <tr><td WIDTH="30%">Notes: </td><td><span DATAFLD="Notes"></span></td></tr>
         <% If Application("CritiqueEnabled") = True Then %>
         <tr><td WIDTH="30%">Avg. Critique Rating: </td><td><a onMouseOver="javascript:ShowRatings()" onMouseOut="javascript:HideRatings()"><img DATAFLD="rating" BORDER=0 ALIGN=Bottom></a></td></tr>
         <% End If %>
         <tr><td WIDTH="30%" VALIGN=Top>Subject(s): </td><td>
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

<% If Application("CritiqueEnabled") = True Then %>
<script LANGUAGE=VBScript>
Sub ViewCritiques()
   bibno = RDS_LongDisplay.Recordset("bib#").Value
   window.location.href = "critiques.asp?bibno=" & bibno
End Sub

Function AuthorsToString(ByRef rs)
    rs.MoveFirst
    Do Until rs.EOF
        sAuthors = sAuthors & sSep & Trim(rs("fname"))
        If Trim(rs("lname")) <> "" Then
            sAuthors = sAuthors & " " & Trim(rs("lname"))
        End If
        sSep = "; "
        rs.MoveNext
    Loop
    AuthorsToString = sAuthors
End Function

Sub NewCritique()
   bibno = RDS_LongDisplay.Recordset("bib#").Value
   itemtitle = RDS_LongDisplay.Recordset("title").Value
   authname = AuthorsToString(RDS_AuthorDetail.Recordset)
   mediatype = RDS_LongDisplay.Recordset("coll").Value
   approvalreq = <%= Application("ApprovalRequired") %>
   approveremail = "<%= Application("ApproverEmail") %>"

   url = "http://<%=Application("ExchangeServer")%>/Exchange/"
   url = url & "Forms/IPM/Post/EnhancedLitCrit/frmRoot.asp?"
   url = url & "command=new&ID=<%=Application("PublicFolderObjectID")%>"
   url = url & "&BN=" & bibno & "&IT=" & itemtitle & "&AN=" & authname & "&MT=" & mediatype
   url = url & "&AR=" & approvalreq & "&AE=" & approveremail
   window.open url,"NewCritique","menubar=no,toolbar=no,status=no,location=no,resizable=yes",False
End Sub
</script>
<% End If %>

<script LANGUAGE=VBScript>
Sub RequestClick()
   DoRequest(RDS_LongDisplay.Recordset("bib#").Value)
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
<% If Application("CritiqueEnabled") = True Then %>            
            If LCase(RDS_LongDisplay.Recordset("coll")) <> "ref" Then
               If InStr(RDS_LongDisplay.Recordset("rating"),"0.0") > 0 Then
                  ReviewButtonsHalf.style.display = ""
               Else
                  ReviewButtonsFull.style.display = ""
               End If
            End If
<% End If %>       
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
<% If Application("CritiqueEnabled") = True Then %>   
   parent.ReviewButtonsFull.style.display = "none"
   parent.ReviewButtonsHalf.style.display = "none"
<% End If %>   
End Sub
</script>


