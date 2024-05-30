<!--
	File:      	NavigationBar.js
	Purpose:	Holds navigation bar functionality and content
	Methods:	navbar_rollon -- controls rollover functionality
				navbar_rolloff -- controls rollover functionality
				navbar_link -- controls navigation destinations for navbar			
				
	This file is provided as part of the Microsoft Visual Studio 6.0 Samples

	THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT
	WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED,
	INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES
	OF MERCHANTABILITY AND/OR FITNESS FOR A  PARTICULAR
	PURPOSE.

	Copyright (C) 1997, 1998 Microsoft Corporation, All rights reserved
-->
<SCRIPT LANGUAGE="JAVASCRIPT">

//Navigation Bar Mouse Events using event bubbling
//Event bubbling allows a single function to be written for each event(onmouseover, onmouseout, onclick).
//The event will bubble up to the highest element within the hierarchy(like the window object)
//unless it is cancelled.  In this case, the events are assigned at the division level.

function navbar_rollon() 
{	
	if (window.event.srcElement.className == "navbar") {
		window.event.srcElement.className = "navbarMouseOver";
	}
}

function navbar_rolloff() 
{
	if (window.event.srcElement.className == "navbarMouseOver") {
		window.event.srcElement.className = "navbar";
	}
}

function navbar_link()
{
	//Assign an arbitrary property whose value can be referenced(made possible
	//by the expando property).  Note how the LINK property varies for the different
	//SPANs listed below

	if (event.srcElement.LINK) {
		document.location.href = event.srcElement.LINK;
	}
	else 
	{}
}
</SCRIPT>

<!--- NAVIGATION BAR BEGINS --->

<DIV STYLE="position:absolute; top:<% =m_intNavBarTop %>; left:<% =m_intNavBarLeft %>; width:765; height:100"
	onmouseover="navbar_rollon()"
	onmouseout="navbar_rolloff()"
	onclick="navbar_link()">
<TABLE WIDTH=100% CELLPADDING=0 CELLSPACING=0 BORDER=0>
	
	<TR>
		<TD>&nbsp;&nbsp;
		</TD>
	</TR>
	<TR>
		<TD ALIGN=left>
			<!--#include file=ViewSource.js -->
		</TD>
	</TR>
	<TR>
		<TD ALIGN=center>
			<IMG SRC="images/bluerule.gif" ALIGN=middle WIDTH=55 HEIGHT=1>
			<SPAN ID=topstories LINK="headlines.asp"
				CLASS=navbar STYLE="width:93">Top Stories</SPAN>
			<IMG SRC="images/bluerule.gif" ALIGN=middle WIDTH=25 HEIGHT=1>
			<SPAN ID=weather LINK="headlines.asp"
				CLASS=navbar STYLE="width:68">Weather</SPAN>
			<IMG SRC="images/bluerule.gif" ALIGN=middle WIDTH=25 HEIGHT=1>
			<SPAN ID=arts LINK="headlines.asp"
				CLASS=navbar STYLE="width:166">Arts & Entertainment</SPAN>
			<IMG SRC="images/bluerule.gif" ALIGN=middle WIDTH=25 HEIGHT=1>
			<SPAN ID=sports LINK="headlines.asp"
				CLASS=navbar STYLE="width:58">Sports</SPAN>
			<IMG SRC="images/bluerule.gif" ALIGN=middle WIDTH=25 HEIGHT=1>
			<SPAN ID=classads LINK="browse.asp"
				CLASS=navbarOff STYLE="width:108"
				onmouseover="classads.className='navbarHighlight'"
				onmouseout="classads.className='navbarOff'">
				Classified Ads</SPAN>
			<IMG SRC="images/bluerule.gif" ALIGN=middle WIDTH=55 HEIGHT=1>
		</TD>
	</TR>
</TABLE>
</DIV>
<!------ NAVIGATION BAR ENDS ------>
