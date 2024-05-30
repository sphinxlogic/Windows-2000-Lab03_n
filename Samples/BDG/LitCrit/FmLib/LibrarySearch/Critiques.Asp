<%@ LANGUAGE=VBScript EnableSessionState=False %>
<% ' Copyright 1998-1999 Microsoft Corporation. All rights reserved. %>
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
   
%>       
<html>
<head>
<title>View Critiques</title>

<link type="text/css" rel="stylesheet" href="../_Themes/fm/theme.css">
</head>

<img class="logo" SRC="../images/fmlogo.gif" WIDTH="187" HEIGHT="90">
<img class="sublogo" SRC="../images/Fmcorplib.gif" WIDTH="180" HEIGHT="18">

<!-- UserInfo Object - required for check-out requests -->
<object id="UserInfo" 
        classid="CLSID:81163377-6EC1-11D2-9BF0-080009DC024D"
         codebase="../CMLC.CAB#version=1,0,0,0" 
        height="0" width="0" VIEWASTEXT>
</object>

<!-- DATA CONTROLS -- ShortDisplay, AuthorDetail and SubjectDetail -->
<object id="RDS_ShortDisplay" CLASSID="clsid:BD96C556-65A3-11D0-983A-00C04FC29E33" height="1" width="1" VIEWASTEXT>
</object>

<object id="RDS_AuthorDetail" CLASSID="clsid:BD96C556-65A3-11D0-983A-00C04FC29E33" height="1" width="1" VIEWASTEXT>
</object>

<object id="RDS_ReviewList" CLASSID="clsid:BD96C556-65A3-11D0-983A-00C04FC29E33" height="1" width="1" VIEWASTEXT>
</object>

<div ID="RatingsLegend" STYLE="DISPLAY: none; POSITION: absolute; BACKGROUND: #fafad2; WIDTH=260px; Z-INDEX=40" onMouseOut="HideRatings()">
<table BORDER="0" CELLPADDING="0" CELLSPACING="2">
<tr><td>&nbsp;<img SRC="../images/star4.0.gif" BORDER="0" WIDTH="50" HEIGHT="12"><font SIZE="-2">&nbsp;&nbsp;Highly recommended</font></td></tr>
<tr><td>&nbsp;<img SRC="../images/star3.0.gif" BORDER="0" WIDTH="50" HEIGHT="12"><font SIZE="-2">&nbsp;&nbsp;Recommended</font></td></tr>
<tr><td>&nbsp;<img SRC="../images/star2.0.gif" BORDER="0" WIDTH="50" HEIGHT="12"><font SIZE="-2">&nbsp;&nbsp;Recommended with reservations</font></td></tr>
<tr><td>&nbsp;<img SRC="../images/star1.0.gif" BORDER="0" WIDTH="51" HEIGHT="12"><font SIZE="-2">&nbsp;&nbsp;Best avoided</font></td></tr>
</table>
</div>

<!-- BUTTONS -- Do Request highlighted -->
<div ID="ShortDisplay" STYLE="POSITION: absolute; LEFT: 265px; TOP: 50px; HEIGHT: 50px">
	<span class="UpButton" onClick="RequestClick()" OnMouseDown="javascript:push()" OnMouseUp="javascript:unPush()" style="POSITION: relative; TOP: 5px; WIDTH: 100px" title="Request title from the library">Request Title</span>
	<span class="UpButton" onClick="ReDoCurrent()" OnMouseDown="javascript:push()" OnMouseUp="javascript:unPush()" style="POSITION: relative; TOP: 5px; WIDTH: 190px" title="Return to results of library search">Return to Search Results</span>
	<span class="UpButton" onClick="NewCritique()" OnMouseDown="javascript:push()" OnMouseUp="javascript:unPush()" style="POSITION: relative; TOP: 5px; WIDTH: 100px" title="Add new critique for this title">Add Critique</span>
</div>

<!-- TABLE -- Details (Long) Display -->
<div ID="Details" STYLE="LEFT: 20px; POSITION: absolute; TOP: 110px; WIDTH: 400px; FONT-SIZE:1pt">
   <table BORDER="0" CELLSPACING="2" CELLPADDING="0" COLS="2" WIDTH="100%">
   <tbody>
      <tr VALIGN="Top"><td><img DATASRC="#RDS_ShortDisplay" DATAFLD="Icon"></td><td>
      <table ID="TBL_ShortDisplay" BORDER="0" CELLSPACING="2" CELLPADDING="0" COLS="2" DATASRC="#RDS_ShortDisplay">
      <tbody>
         <tr><td COLSPAN="2"><span CLASS="Title" DATAFLD="Title"></span></td></tr>
         <tr><td WIDTH="30%" VALIGN="Top">Author(s): </td><td>
            <table ID="TBL_Authors" BORDER="0" CELLSPACING="2" CELLPADDING="0" COLS="1" DATASRC="#RDS_AuthorDetail">
            <tbody>
               <tr><td><a DATAFLD="Link" TITLE="View other works by this author">
               <span DATAFLD="LName"></span>, <span DATAFLD="FName"></span></a></td></tr>
            </tbody>
            </table></td></tr>
      </tbody>
   </table>
</div>

<div ID="ReviewList" STYLE="LEFT: 0px; POSITION: relative; TOP: 20px; WIDTH: 400px; FONT-SIZE:1pt">
   <table DATASRC="#RDS_ReviewList" BORDER="0" CELLSPACING="2" CELLPADDING="0" COLS="5" WIDTH="100%">
   <thead>
   <tr>
      <td><span id="Title" class="UpButton" onClick="sortClick()" style="POSITION: relative; TOP: 0px; WIDTH: 130px" title="Sort by critique title">Critique Title&nbsp;<img id="iTitle" align="center" style="display:none"></span>
	   </td>
	   <td><span id="Rating" class="UpButton" onClick="sortClick()" style="POSITION: relative; TOP: 0px; WIDTH: 130px" title="Sort by overall rating">Overall Rating&nbsp;<img id="iRating" align="center" style="display:none"></span>
	   </td>
	   <td><span id="Name" class="UpButton" onClick="sortClick()" style="POSITION: relative; TOP: 0px; WIDTH: 130px" title="Sort by reviewer's name">Name&nbsp;<img id="iName" align="center" style="display:none"></span>
	   </td>
	   <td><span id="JTitle" class="UpButton" onClick="sortClick()" style="POSITION: relative; TOP: 0px; WIDTH: 130px" title="Sort by reviewer's job description">Job Title&nbsp;<img id="iJTitle" align="center" style="display:none"></span>
	   </td>
	   <td><span id="Date" class="DownButton" onClick="sortClick()" style="POSITION: relative; TOP: 0px; WIDTH: 130px" title="Sort by date of critique (default)">Date&nbsp;<img id="iDate" align="center" src="../images/desc.gif" WIDTH="12" HEIGHT="12"></span>
	   </td>
	</tr>
	</thead>
   <tbody>
   <tr>
      <td><a DATAFLD="Link"><span DATAFLD="Title"></span></a></td>
      <td ALIGN="Center"><a onMouseOver="ShowRatings()" onMouseOut="HideRatings()">
         <img DATAFLD="Rating" BORDER="0" VALIGN="Center"></a></td>
      <td><span DATAFLD="Name"></span></td>
      <td ALIGN="Center"><span DATAFLD="JTitle"></span>, <span DATAFLD="Dept"></span></td>
      <td ALIGN="Center"><span DATAFLD="Date"></span></td>
   </tr>
   </tbody>
   </table>
</div>

<script language="VBScript">
Sub push()
   window.event.srcElement.className = "DownButton"
End Sub

Sub unPush()
   window.event.srcElement.className = "UpButton"
End Sub

Function GetUserInfo()
   Dim uiOnPC
   uiOnPC = False
   On Error Resume Next
   uiOnPC = IsObject(CreateObject("CMLC.UserInfo"))
   If uiOnPC = False Then
      MsgBox "You must install the CMLC.UserInfo component in order to request books." &_
             vbCrLf & "Please check your security settings and reload this page.", _
             vbCritical, "UserInfo Component Not Installed"
      GetUserInfo = ""
   Else
      GetUserInfo = UserInfo.Logon
   End If
   Err.Clear
End Function

Sub RequestClick()
   sLogon = GetUserInfo
   If sLogon <> "" Then
      url = "request.asp?Logon=" & sLogon & "&BibNo=<%= nBibNo %>"
      window.open url,"Request","menubar=no,toolbar=no,status=no,location=no,resizeable=yes",False
   End If
End Sub

Sub ReDoCurrent()
   document.location.href = "loadpage.asp?search.asp"
End Sub

Sub DoAuthor(authorNo)
   document.location.href = "loadpage.asp?author.asp%3FAuthorNo=" & authorno
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
   bibno = RDS_ShortDisplay.Recordset("bib#").Value
   itemtitle = RDS_ShortDisplay.Recordset("title").Value
   authname = AuthorsToString(RDS_AuthorDetail.Recordset)
   mediatype = RDS_ShortDisplay.Recordset("coll").Value
   approvalreq = <%= Application("ApprovalRequired") %>
   approveremail = "<%= Application("ApproverEmail") %>"
   
   url = "http://<%=Application("ExchangeServer")%>/Exchange/"
   url = url & "Forms/IPM/Post/EnhancedLitCrit/frmRoot.asp?"
   url = url & "command=new&ID=<%=Application("PublicFolderObjectID")%>"
   url = url & "&BN=" & bibno & "&IT=" & itemtitle & "&AN=" & authname & "&MT=" & mediatype
   url = url & "&AR=" & approvalreq & "&AE=" & approveremail
   window.open url,"NewCritique","menubar=no,toolbar=no,status=no,location=no,resizable=yes",False
End Sub

Sub DoCritique(objectID)
   url = "http://<%=Application("ExchangeServer")%>/Exchange/"
   url = url & "Forms/IPM/Post/EnhancedLitCrit/frmRoot.asp?"
   url = url & "command=open&obj=" & objectID
   window.open url,objectID,"menubar=no,toolbar=no,status=no,location=no,resizable=yes",False
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

<script LANGUAGE="VBScript">
' ERROR HANDLERS FOR RDS CONTROLS
Sub RDS_ShortDisplay_OnError(SCode,Description,Source,CancelDisplay)
   RDS_OnError Scode, Description, Source, CancelDisplay
End Sub

Sub RDS_AuthorDetail_OnError(SCode,Description,Source,CancelDisplay)
   RDS_OnError Scode, Description, Source, CancelDisplay
End Sub

Sub RDS_ReviewList_OnError(SCode,Description,Source,CancelDisplay)
   RDS_OnError Scode, Description, Source, CancelDisplay
End Sub

Sub RDS_OnError(SCode,Description,Source,CancelDisplay)
   MsgBox Description,vbCritical,Source
   CancelDisplay = True
End Sub
</script>

<script LANGUAGE="VBScript">
'--- Called during sort "button" clicks
Sub sortClick()
   Dim lastSort,thisSort,oImage
   lastSort = RDS_ReviewList.SortColumn
   thisSort = window.event.srcElement.id
   ' Make sure we are using the DIV id, not the IMG id...
   If Left(thisSort,1) = "i" Then thisSort = Mid(thisSort,2)
   Set oImage = document.all("i"&thisSort)
   If thisSort <> lastSort Then
      RDS_ReviewList.SortColumn = thisSort
      document.all(lastSort).className = "UpButton"
      document.all("i"&lastSort).style.display = "none"
      document.all(thisSort).className = "DownButton"
      oImage.style.display = ""
      Select Case LCase(thisSort)
      Case "rating","date":
         RDS_ReviewList.SortDirection = False
         oImage.src = "../images/desc.gif"
      Case Else
         RDS_ReviewList.SortDirection = True
         oImage.src = "../images/asc.gif"
      End Select
   Else
      ' Second time click, reverse sort order
      RDS_ReviewList.SortDirection = Not RDS_ReviewList.SortDirection 
      If RDS_ReviewList.SortDirection = True Then
         oImage.src = "../images/asc.gif"
      Else
         oImage.src = "../images/desc.gif"
      End If
   End If
   RDS_ReviewList.Reset 
End Sub
</script>

<script LANGUAGE="VBScript">
<!-- #include file="adcvbs.inc" -->

   If RDS_ShortDisplay.ReadyState <> adcReadyStateComplete Then
      MsgBox "Results still arriving. Query canceled.", vbInformation
   Else
      ' Retrieve the details of this title from the database
      Set RDS = RDS_ShortDisplay
      RDS.ExecuteOptions = adcExecSync
      RDS.FetchOptions = adcFetchUpFront
      RDS.Handler = "MSDFMAP.Handler,FmLibMap.ini"
      RDS.Server = "http://<%= Request.ServerVariables("SERVER_NAME") %>"
      RDS.Connect = "Data Source=FmLib"
      RDS.SQL = "TitleDetailShort(<%= nBibNo %>)"
      RDS.Refresh
      
      ' Retrieve the authors and subject keywords
      Set RDS = RDS_AuthorDetail
      RDS.ExecuteOptions = adcExecSync
      RDS.FetchOptions = adcFetchUpFront
      RDS.Handler = "MSDFMAP.Handler,FmLibMap.ini"
      RDS.Server = "http://<%= Request.ServerVariables("SERVER_NAME") %>"
      RDS.Connect = "Data Source=FmLib"
      RDS.SQL = "AuthorDetail(<%= nBibNo %>)"
      RDS.Refresh
      
      ' Retrieve list of critiques for this title
      Set RDS = RDS_ReviewList
      RDS.ExecuteOptions = adcExecSync
      RDS.FetchOptions = adcFetchUpFront
      RDS.Handler = "MSDFMAP.Handler,FmLibMap.ini"
      RDS.Server = "http://<%= Request.ServerVariables("SERVER_NAME") %>"
      RDS.Connect = "Data Source=FmLib"
      RDS.SQL = "ReviewList(<%= nBibNo %>)"
      RDS.Refresh

      ' Set default sort order...
      RDS.SortColumn = "Date"
      RDS.SortDirection = False
   End If
</script>

</body>
</html>
