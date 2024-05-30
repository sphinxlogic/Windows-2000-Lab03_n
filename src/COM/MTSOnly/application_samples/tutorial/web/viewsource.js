<!--
	File:      	ViewSource.js
	Purpose:	holds the viewsource button and spawns window for viewing source code
	Methods:	openWindow -- spawns new window and passes URL of source code			
				
This file is provided as part of the Microsoft Visual Studio 6.0 Samples

	THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT
	WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED,
	INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES
	OF MERCHANTABILITY AND/OR FITNESS FOR A  PARTICULAR
	PURPOSE.

	Copyright (C) 1997, 1998 Microsoft Corporation, All rights reserved
-->
<SCRIPT LANGUAGE="JavaScript">

	//Uses the URL supplied by the GetPageName variable and opens a second
	//window that shows the code of the current page
	function openWindow(SourceURL)
	{
	    // Set some defaults for the second window
	    width=600;
	    height=450;
		url = "code.asp?Source=" + SourceURL;
		//Supply the necessary parameters for the open method
		window.open(url,"Sample","resizable=yes,scrollbars=yes,width=" + width + ",height=" + height);
	}
</SCRIPT>

	<SPAN ID=ViewScriptLink
			CLASS=LINK 
			onmouseover="this.className = 'hlinkMouseOver'; window.status='View Script'; return true;" 
			onmouseout="this.className = 'hlink'; window.status=''; return true;"
			onclick="openWindow('<%= GetPageName %>')" 
			STYLE="position:relative;top:2;left:15; width:80;">
			<IMG src="images/t_viewscript.gif" width=83 height=40 ID='ViewSourceImage' CLASS=LINK>
		</SPAN>

	<%
		'Server side function that takes the URL of the current page and 
		'assigns it to the variable PageName which is then assigned to the variable 
		'GetPageName.  This is the variable used in the openWindow function that is 
		'fired by the onclick event
		Function GetPageName()
			Dim strPageName
			strPageName = request.servervariables("URL")
			GetPageName = strPageName
		End Function
	%>

		
