<%@ Language=VBScript %>
<% ' Copyright 1998-1999 Microsoft Corporation. All rights reserved. %>
<% Option Explicit
   Response.Expires = 0
%>
<html>
<head>
<title>Library Catalog</title>

<object id="UserInfo" 
        classid="CLSID:81163377-6EC1-11D2-9BF0-080009DC024D"
        codeBase="../CMLC.CAB#version=1,0,0,0" 
        height="0" width="0" VIEWASTEXT>
</object>


<link type="text/css" rel="stylesheet" href="../_Themes/fm/theme.css">	

<script LANGUAGE="VBSCRIPT">
Option Explicit

<!-- #include file="adcvbs.inc" -->

' Dim strSource
Dim sLogon

Function GetUserInfo()
   Dim uiOnPC
   uiOnPC = False
   On Error Resume Next
   uiOnPC = IsObject(CreateObject("CMLC.UserInfo"))
   If uiOnPC = False Then
      MsgBox "You must install the CMLC.UserInfo component in order to request books." &_
             vbCrLf & "Please check your security settings and reload this page.", _
             vbCritical, "UserInfo Component Not Installed"
   Else
      GetUserInfo = UserInfo.Logon
   End If
   Err.Clear
End Function

Sub Window_OnLoad()
	<% If Application("Debug") = True Then %>
   document.all.ifControl.style.display = ""
	<% End If %>
	'--- Confirm the download of the CMLC.UserInfo component, and
	'--- retreive current user logon
	sLogon = GetUserInfo()
	 
<% IF Session("LastPage") = "" THEN %>
   gettingStarted.style.display = ""
   initialinfo.style.display = ""
   txtWord.Focus
<% END IF %>
End Sub

'--- Invoked by child pages to reset display to a known state
Sub ClearAllDivs()
   ClearAllSortBy()
   ClearAllDetails()
   Parent.searchresults.style.display ="none"   
   parent.gettingStarted.style.display = "none"
   parent.initialinfo.style.display = "none"
   parent.pleasewait.style.display = "none"
   parent.norecords.style.display = "none"
   parent.request.style.display = "none"
   parent.requestok.style.display = "none"
   parent.document.all.ifRequest.style.display = "none"
End Sub

Dim nLastSearch
Dim nLastAuthor
Dim nLastSubject

Const cAuthor = 1
Const cSubject = 2
Const cSearch = 3

Function DoLong(bibno)
	document.all.ifControl.src = "details.asp?BibNo=" & bibno
END Function

Function DoSubject(subjectno)
   nLastSearch = cSubject
   nLastSubject = subjectno
   document.all.ifControl.src = "subject.asp?SubjectNo=" & subjectno
End Function

Function DoAuthor(authorno)
   nLastSearch = cAuthor
   nLastAuthor = authorno
   document.all.ifControl.src = "author.asp?AuthorNo=" & authorno
End Function

SUB DoRequest(bibno)
   document.all.ifRequest.src = "request.asp?Logon=" & sLogon & "&BibNo=" & bibno
END SUB

SUB ReDoCurrent()
   document.all.ifRequest.src = "current.asp"
End Sub

Sub ReDoLong()
   ' readjust DIVs to return to previous display
   Request.style.display = "none"
   document.all.ifRequest.style.display = "none"
   LongDisplay.style.display = ""
   Details.style.display = ""
End Sub

</script>
</head>

<body>
<img class="logo" SRC="../images/fmlogo.gif" WIDTH="187" HEIGHT="90">
<img class="sublogo" SRC="../images/Fmcorplib.gif" WIDTH="180" HEIGHT="18">
<img class="line" SRC="../images/vertline.gif" WIDTH="1" HEIGHT="100"> 

<div STYLE="POSITION:absolute; LEFT:30px; TOP:120px;z-index:5;color:blue;font-weight:bold;">
<a href ="../default.asp">Home</a>&nbsp;&nbsp;&nbsp;<a href="../viewmyrequests.asp">View Requests</a>
</div>

<!-- #include file="DFilter.asp" -->

<!-- FIRST PAGE -- Getting Started -->
<div ID="GettingStarted" STYLE="DISPLAY: none; FONT-FAMILY: Verdana, Arial; FONT-SIZE: 10pt; FONT-WEIGHT:BOLD;POSITION: absolute; LEFT: 275px; TOP: 85px">
	SEARCHING THE LIBRARY 
</div>
<div ID="InitialInfo" STYLE="DISPLAY: none; POSITION: absolute; LEFT: 300px; TOP: 113px; WIDTH: 350px">
	To search for materials in the library's collection, just enter your keywords in the box on the left. The results of your search
	will appear in this window. Click on an item's title to get more details on that item. When you find an item that you'd like to borrow, click the 
	<b>Request Title</b> button to make your request. We'll have the item sent to your location.
	
	<p>If you can't find what you're looking for, <a HREF="mailto:<%= Application("DefaultContactEmail")%>@<%= Application("DefaultDomainName")%>"><b>e-mail us</b></a> and let us know&mdash;we'll track it down for you.
</div>

<!-- #include file="DSearch.asp" -->
<!-- #include file="DDetails.asp" -->

<!-- Request Page -->
<div ID="request" STYLE="DISPLAY: none; LEFT: 265px; POSITION: absolute; TOP: 50px; HEIGHT:50px; Z-INDEX: 5">
	<span class="UpButton" onClick="ReDoLong()" OnMouseDown="javascript:push()" OnMouseUp="javascript:unPush()" style="POSITION: relative; TOP: 5px; WIDTH: 120px" title="Return to Detail">Return to Detail</span>
	<span class="UpButton" onClick="ReDoCurrent()" OnMouseDown="javascript:push()" OnMouseUp="javascript:unPush()" style="POSITION: relative; TOP: 5px; WIDTH: 100px" title="Return to List">Return to List</span> 
	<br>
</div>

<!-- Request Confirmation Page -->
<div ID="requestok" STYLE="DISPLAY: none; LEFT: 265px; POSITION: absolute; TOP: 50px;HEIGHT:50px;  Z-INDEX: 5">
	<span class="UpButton" onClick="ReDoCurrent()"  style="POSITION: relative; TOP: 5px; WIDTH: 100px" title="Return to List">Return to List</span> 
	<br>
</div>

<script LANGUAGE=VBScript>
Dim screenWidth,screenHeight,x
screenWidth = CInt((screen.availWidth - 265) * 0.75)
screenHeight = CInt((screen.availHeight - 113) * 0.70)
x = "<iframe ID=""ifRequest"" STYLE=""display:none;POSITION:absolute;top:113;left:265;height:" & screenHeight & " px;width:" & screenWidth & " px"" FRAMEBORDER=0 NORESIZE SCROLLING=no></iframe>"
document.write x
</script>

<!-- This child window controls the parent -->
<% ' ASP Session object retains the current location, so that refresh doesn't restart us from the beginning. %>
<iframe ID="ifControl" STYLE="display:none;top:0;left:250;height:40 px;width:540 px;POSITION:absolute" FRAMEBORDER=0 NORESIZE SCROLLING=none SRC="<%= Session("LastPage") %>"></iframe>

</body>
</html>
