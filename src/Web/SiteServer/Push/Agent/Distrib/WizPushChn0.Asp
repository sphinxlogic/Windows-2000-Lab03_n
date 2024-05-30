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
<HTML>
<HEAD>
<!--#Include File="LibWizardScript.asp"-->
<SCRIPT LANGUAGE=JavaScript>
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
<%= g_strIndent %> <B></B>
<P>
<%
    Dim m_dict

    If IsObject(Session("Dict")) Then
        Set m_dict = Session("Dict")
    Else
        Set m_dict = Server.CreateObject("Scripting.Dictionary")
        Set Session("Dict") = m_dict
    End If


    On Error Resume Next

    Dim m_prj,m_chn,m_parent,m_Item, m_fSuccess, m_strProjectName, m_str, m_strErr

    m_strProjectName = Session("ProjectName")
    
    Set m_prj = PrjLoadFromName(m_strProjectName)

    Set m_parent = ChnItmFromPrj(m_prj, Session("ChannelPath"))
	if Session("NewProject") = "True"  Then
      Set m_chn = m_parent
	Else
	  Set m_chn = m_parent.AddSubChannel()
	End If

    m_chn.Title = CStr(Session("Title"))
    m_chn.Abstract = Session("Abstract")
    m_chn.Base = Session("BaseURL")

    If Session("BaseURL") <> "" Then
      If Right(Session("BaseURL"), 1) <> "/" Then m_chn.Base = m_chn.Base & "/"
    End If
    
    m_chn.HREF = Session("IntroURL")
    m_chn.DeleteOnRefresh = 0

	If Session("NewProject") = "True"  Then
      If UCase(Session("RequireLogin")) = "OFF" Then
        m_chn.NeedsLogin = 0
      Else
        m_chn.NeedsLogin = 1
      End If

      If Session("ChannelType") = "Application" Then
        m_chn.AddUsage "SoftwareUpdate", ""
      End If

	End If


    If Session("MinStorage") <> "" Then 
      m_chn.MinStorage = CInt(Session("MinStorage"))
    End If
    m_chn.RefreshType = CStr(Session("Agent"))

    If m_chn.RefreshType = "userscript" Then
      m_chn.RefreshScript = Session("AgentScript")
    Else

      For Each m_str In m_dict
        DebugWriteNameValue m_str, m_dict(m_str)
        If m_str = "LogEvents" Then
            Dim rgLogs(0)
            rgLogs(0) = "document:view"
            m_chn.RefreshOptions.Item("ItemLogs") = rgLogs
        Elseif m_str = "MatchCriteria" Then
            m_chn.RefreshOptions.Item("MatchCriteria") = Split(m_dict(m_str), ";")
        Elseif m_str = "Files" Then
            m_chn.RefreshOptions.Item("Files") = Split(m_dict(m_str), ";")
        Else
            m_chn.RefreshOptions.Item(m_str) = CStr(m_dict(m_str))
        End If
      Next
    End If

    SaveProject m_prj
    If Err.Number = 0 and Err.Description="" Then
      m_fSuccess = True
    Else
      m_fSuccess = False
      If Err.Description <> "" Then
        m_strErr =  Server.HTMLEncode(Err.Description) & " (0x" & Hex(Err.Number) & ")"
      Else
        m_strErr = "0x" & Hex(Err.Number)
      End If
    End If

    On Error Goto 0

    CacheProject m_prj
%>

<% If m_fSuccess Then %>
The new channel was created successfully.  

You can configure additional channel properties from the Channels / Items / Packages page. 
Click OK to return to the page from which you created this channel.
<% Else %>
The following error occurred:  <%= m_strErr %>
<% End If %>

<P>


</FONT></TD></TR>
</TABLE>
<HR>
<TABLE WIDTH=100%>
<TR><TD><IMG <%= g_swhWizIcon %> ALT="<% = L_Image_Text %>"></TD><TD ALIGN=RIGHT>
<INPUT TYPE=SUBMIT NAME="Done" VALUE="<%= L_OK_Button %>">
<INPUT TYPE=HIDDEN NAME="_goto" VALUE="<%= Session("Origin") %>">
<INPUT TYPE=HIDDEN NAME="_abandon" VALUE="true">
</TD></TR>
</TABLE>

</FORM>

</FONT>
</BODY>
</HTML>
