<%@ LANGUAGE="VBScript" %>
<% Option Explicit %>
<% 
' ****************************************************************************
' **                                                                          
' ** Microsoft Site Server v3.00                                              
' ** (C) Copyright 1997-1998 by Microsoft Corporation.  All rights reserved.  
' **                                                                          
' ** THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY    
' ** KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE      
' ** IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR    
' ** PURPOSE.                                                                 
' **                                                                          
' ****************************************************************************
%>

<!--#Include File="LibGlobals.asp"-->
<!--#Include File="LibUtil.asp"-->
<!--#Include File="LibRes.asp"-->
<!--#Include File="LibWizard.asp"-->
<HTML>
<HEAD>
<!--#Include File="LibWizardScript.asp"-->
<SCRIPT LANGUAGE=JavaScript>
function validate()
{
    return true;
}
</SCRIPT>
</HEAD>
<BODY <%= g_prmCntWizBody %> OnLoad="focusFirst()">
<FONT <%= g_fntCntText %>>
<FORM NAME="Wizard" ACTION="wiz.asp" METHOD=POST>
<TABLE WIDTH=100% HEIGHT=85%>
<TR><TD VALIGN=TOP><FONT <%= g_fntCntText %>>

<FONT <%= g_fntCntHeader %>>
<B>Create New Active Channel Wizard</B>
</FONT>
<BR>
<%= g_strIndent %> <B>Set Agent Options</B>
<P>

The file system agent can gather content items from any file directory in your network.
Type the directory path you want to scan.
<P>
Type file names, separated by semicolons
<P>

<BLOCKQUOTE>

<TABLE BORDER=0>
<TR>
  <TD><FONT <%= g_fntCntText %>>
  Directory: 
  </TD>
  <TD>
  <INPUT TYPE=TEXT NAME="Dict_Directory" VALUE="<%= Server.HTMLEncode(Session("Dict_Directory")) %>" SIZE=40>
  </TD>
</TR>
<% SpaceRow(2) %>
<TR>
  <TD><FONT <%= g_fntCntText %>>
  File Names: 
  </TD>
  <TD>
  <INPUT TYPE=TEXT NAME="Dict_Files" VALUE="<%= Server.HTMLEncode(Session("Dict_Files")) %>" SIZE=40>
  </TD>
</TR>
</TABLE>
</BLOCKQUOTE>

</FONT></TD></TR>
</TABLE>

<INPUT TYPE=Hidden NAME=Origin VALUE="<%= Session("Origin") %>">
<INPUT TYPE=Hidden NAME=CommonBack VALUE="WizFileSystem.asp">

<HR>
<TABLE WIDTH=100%>
<TR><TD><IMG <%= g_swhWizIcon %> ALT="<% = L_Image_Text %>"></TD><TD ALIGN=RIGHT>
<INPUT TYPE=BUTTON NAME="Back" VALUE="<%= L_Back_Button %>" onClick="wizard(cmdBack, 'WizPushChn3.asp')">
<!--<INPUT TYPE=BUTTON NAME="Next" VALUE="<%= L_Next_Button %>" onClick="wizard(cmdNext, 'WizAgCommon.asp')">-->
<INPUT TYPE=BUTTON NAME="Finish" VALUE="<%= L_Finish_Button %>" onClick="wizard(cmdFinish, 'WizPushChn0.asp')">&nbsp;&nbsp;
<INPUT TYPE=BUTTON NAME="Cancel" VALUE="<%= L_Cancel_Button %>" onClick="wizard(cmdCancel, '<%= Session("Origin") %>')">
<INPUT TYPE=HIDDEN NAME="_goto" VALUE="">
<INPUT TYPE=HIDDEN NAME="_abandon" VALUE="">
</TD></TR>
</TABLE>

</FORM>

</FONT>
</BODY>
</HTML>
