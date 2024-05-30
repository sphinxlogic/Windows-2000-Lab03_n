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
<!--#Include File="LibRes.asp"-->
<!--#Include File="LibUtil.asp"-->

<HTML>
<HEAD>
  <TITLE></TITLE>
<SCRIPT LANGUAGE="JavaScript">
function doCommand(strCmd)
{
    var strFileName;


    if (strCmd == "add") {
        strFileName = prompt("Type a value for the new file name.", "");
        if(strFileName != null && strFileName != "") {
            document.HiddenFormAdd.FileName.value = strFileName;
            document.HiddenFormAdd.submit();
        }
    }
    else if (strCmd == "edit") {
        iSelected = document.grid.getSelectedIndex();
        if(iSelected >= 0) {
            strFileName = prompt("Edit the file name.", document.grid.getValue(iSelected, 0));
            if(strFileName != null && strFileName != "") {
                document.HiddenFormEdit.FileName.value = strFileName;
                document.HiddenFormEdit.idx.value = document.grid.getHiddenValue(iSelected);
                document.HiddenFormEdit.submit();
            }
        }
        else {
            alert("You must select a file name to perform this operation.");
        }
    }
    else if (strCmd == "del") {
        iSelected = document.grid.getSelectedIndex();
        if(iSelected >= 0) {
            document.HiddenFormRemove.idx.value = document.grid.getHiddenValue(iSelected);

            if(confirm("Click OK to remove this file name."))
                document.HiddenFormRemove.submit();
        }
        else {
            alert("You must select a file name to perform this operation.");
        }
    }
        
}

</SCRIPT>
</HEAD>
<BODY <%= g_prmCntBody %>>
<FONT <%= g_fntCntText %>>

<%
  ' --------------------------------------------------------------------------
  Dim m_strProjectName ' the Project Name
  Dim m_prj            ' the Project Object
  Dim m_chn            ' the channel item
  Dim m_strChnItmPath  ' the Channel/Item Path
  Dim m_options        ' the refresh options dictionary

  m_strProjectName = Request.QueryString(g_strKeyProjectName)
  m_strChnItmPath = Request.QueryString(g_strKeyChnItmPath)

  Set m_prj = PrjLoadFromName(m_strProjectName)
  Set m_chn = ChnItmFromPrj(m_prj, m_strChnItmPath)

  Set m_options = m_chn.RefreshOptions

  If IsObject(m_chn) Then
    SavePage m_prj

    ' --------------------------------------------------------------------------
  AddToNavTool L_ManageChannelsItemsNav_Text,   StrMakeQueryUrl("PjPrCh.asp", m_strProjectName, "", "")
  AddToNavTool L_EditChannelPropertiesNav_Text, StrMakeQueryUrl("ChPr.asp", m_strProjectName, m_strChnItmPath, "")
  AddToNavTool L_ChannelAgentPropertiesNav_Text, StrMakeQueryUrl("ChPrAg.asp",m_strProjectName,m_strChnItmPath, "")

    DrawNavTool

  ' --------------------------------------------------------------------------

%>
<FONT <%= g_fntCntHeader %>>
<B>Sample Properties page for Agents</B> 
</FONT>
<BR>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
Channel <B><I><%= Server.HTMLEncode(m_Chn.Title) %></I></B>, project <B><I><%= m_strProjectName %></I></B>
<BR><BR>
To specify file names, click Add.  Add file names one at a time.
<BR><BR>

<TABLE BORDER=0>
  <TR>
    <TD>
    <% DrawGrid %>
    </TD>
  </TR>
</TABLE>
<FORM NAME="GeneralForm" ACTION="<%= StrMakeQueryUrl("", m_strProjectName, m_strChnItmPath, "") %>" METHOD=POST>
    <INPUT TYPE=BUTTON NAME="Add" VALUE="<%= L_Add_Button %>" onClick="doCommand('add')">
    <INPUT TYPE=BUTTON NAME="Remove" VALUE="<%= L_Remove_Button %>" onClick="doCommand('del')">
    <INPUT TYPE=BUTTON NAME="Props" VALUE="<%= L_Properties_Button %>" onClick="doCommand('edit')">
<BR>
</FORM>
</FONT>
<%
    Else
      Randomize
      WriteClientAlertAndRedirect L_InvalidItem_ErrorMessage,"PjPrCh.asp?" & g_strKeyProjectName & "=" & m_strProjectName & "&Random=" & Rnd()
    End If
%>

<FORM NAME="HiddenFormAdd" METHOD=POST ACTION="<%= StrMakeQueryUrl("AgSampleAgent.asp", m_strProjectName, m_strChnItmPath, "") %>">
<INPUT TYPE=HIDDEN NAME=Action VALUE="Add">
<INPUT TYPE=HIDDEN NAME=FileName VALUE="">
</FORM>
<FORM NAME="HiddenFormEdit" METHOD=POST ACTION="<%= StrMakeQueryUrl("AgSampleAgent.asp", m_strProjectName, m_strChnItmPath, "") %>">
<INPUT TYPE=HIDDEN NAME=Action VALUE="Edit">
<INPUT TYPE=HIDDEN NAME=FileName VALUE="">
<INPUT TYPE=HIDDEN NAME=idx VALUE="">
</FORM>
<FORM NAME="HiddenFormRemove" METHOD=POST ACTION="<%= StrMakeQueryUrl("AgSampleAgent.asp", m_strProjectName, m_strChnItmPath, "") %>">
<INPUT TYPE=HIDDEN NAME=Action VALUE="Remove">
<INPUT TYPE=HIDDEN NAME=idx VALUE="">
</FORM>

<BR>
<HR>
<FORM NAME="HiddenFormDir" METHOD=POST ACTION="<%= StrMakeQueryUrl("AgSampleAgent.asp", m_strProjectName, m_strChnItmPath, "") %>">
Type in the complete path to the directory where the files are located (for example, <I>c:\directory_name\</I>.)<P>
Directory path: <BR>
<INPUT TYPE=HIDDEN NAME=Action VALUE="DirChange">
<INPUT TYPE=TEXT NAME="Directory" VALUE="<%
       If Not IsNull(m_options("Directory")) Then
         Response.Write Server.HTMLEncode(m_options("Directory"))
       End If
%>" SIZE=40>
<BR>

<INPUT TYPE=SUBMIT NAME="Submit" VALUE="<%= L_Submit_Button %>">
</FORM>

</BODY>
</HTML>

<%
  ' --------------------------------------------------------------------------
  Sub SavePage(prj)
    Dim strFileName
    Dim rgFileName, I


    strFileName = Request.Form("FileName")

    rgFileName = m_options.Item("Files")


    If Request.Form("Action") = "Add" Then

        DebugWriteNameValue "vartype", vartype(rgFileName)

        If IsArray(rgFileName) Then

            For I = 0 To UBound(rgFileName)
                DebugWriteNameValue "rgFileName(I): ", rgFileName(I)
                If strFileName = rgFileName(I) Then
                    WriteClientAlert "You already added this one."
                    Exit Sub
                End If
            Next


            AddArrayElement rgFileName, strFileName

        Else
            ReDim rgFileName(0)
            rgFileName(0) = strFileName
            DebugWriteNameValue "vartype(rgFileName)", vartype(rgFileName)
            DebugWriteNameValue "strFileName", strFileName
        End If

        m_options.Item("Files") = rgFileName

    Elseif Request.Form("Action") = "Remove" Then

        RemoveArrayElement rgFileName, CInt(Request.Form("idx"))

        m_options.Item("Files") = rgFileName

    Elseif Request.Form("Action") = "Edit" Then
        rgFileName(CInt(Request.Form("idx"))) = strFileName
        m_options.Item("Files") = rgFileName

    Elseif Request.Form("Action") = "DirChange" Then
        m_options.Item("Directory") = CStr(Request.Form("Directory"))
        m_options.Item("Files") = rgFileName
        
    End If
    SaveProject prj
    
  End Sub

  Sub DrawGrid
    Dim str, str2, str3, I, rgFileName
    AddGridAppletParam "columns", "1"
    AddGridAppletParam "headings", "File Names"

    rgFileName = m_options.Item("Files")
    DebugWriteNameValue "vartype(rgFileName)", vartype(rgFileName)

 

    If IsArray(rgFileName) Then

    For I = 0 To UBound(rgFileName)
            AddGridColumnData(rgFileName(I))
            AddGridHiddenData(CStr(I))
            AddGridRow
    Next

    End If

    DrawGridApplet "grid", "300", "120"
  End Sub


%>
