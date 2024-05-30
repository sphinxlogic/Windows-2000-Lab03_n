<%
'<!--Rules Sample Application-->
'<!--App.inc : Application inc-->
'<!--Copyright (c) Microsoft Corporation 1993-1998. All rights reserved.-->
'
' App.inc contains application routines that may be used by more than one module.
' One routine, App_RenderPage, defines the UI framework for all 
' asp's in the application.
'
' Force refresh under IE
'
If App_bSupportsIE4DHTML() Then 
    Response.Expires = 0
End If

Public Sub App_CheckSession()
'
' App_CheckSession redirects to the logon page if the session is invalid.
'
    If Not CDO_bValidSession() Then
%>
    <SCRIPT Language="JavaScript">
        parent.location="<%=gstrASP_LOGON%>"
    </SCRIPT>
<%
        Response.End
    End If
End Sub

Public Function App_bSupportsIE4DHTML()
'
' bSupportsIE4DHTML returns true if the browser supports IE4's dynamic HTML
'
    Dim bSupportsIE4DHTML
    Dim strUserAgent
    Dim strVersion
    Dim strVersionMajor
    Dim strVersionMinor
    Dim chVersion
    Dim sngVersion
    Dim iUserAgent
    Dim iUserAgent2

    If IsEmpty(Session(gstrSESS_B_SUPPORTS_IE4_DHTML)) Then
        '
        ' Determine whether IE4 DHTML is supported & save boolean in session variable
        '
        strUserAgent = Request.ServerVariables("HTTP_USER_AGENT")
        '
        ' Look for MSIE
        '
        iUserAgent = Instr(strUserAgent, "MSIE")

        If (iUserAgent <> 0) then
            '   
            ' MSIE Agents are of the form "Mozilla/#.# (compatable; MSIE M.m; Platform)"
            ' 
            strVersion = Right(strUserAgent, len(strUserAgent) - iUserAgent - len("MSIE")) 

            ' Get the major version #
            iUserAgent = Instr(strVersion, ".")
            strVersionMajor = Left(strVersion, iUserAgent - 1)

            ' Get the minor version #
            iUserAgent = Instr(strVersion, ".")
            For iUserAgent2 = iUserAgent + 1 to len(strVersion)
                chVersion = asc(Mid(strVersion, iUserAgent2, 1)) 
                If (chVersion < asc("0")) OR (chVersion > asc("9")) Then
                    Exit For
                End If
            Next 
        
            strVersionMinor = Mid(strVersion, iUserAgent + 1, iUserAgent2 - iUserAgent - 1)

            sngVersion = CSng(strVersionMinor) / (10 ^ Len(strVersionMinor)) + CSng(strVersionMajor)
            '
            ' If version >= 4, DHTML is supported
            '
            bSupportsIE4DHTML = (sngVersion >= 4)
        Else
            '
            ' Non-IE browser
            '
            bSupportsIE4DHTML = False
        End If

        Session(gstrSESS_B_SUPPORTS_IE4_DHTML) = bSupportsIE4DHTML
    Else ' Use session variable bool
        bSupportsIE4DHTML = CBool(Session(gstrSESS_B_SUPPORTS_IE4_DHTML))
    End If

    App_bSupportsIE4DHTML = bSupportsIE4DHTML
End Function

Public Sub App_PrepPaging(pc, pcPageSize, piPageFirst, piPage, pcPage, piFirst, piLast)
'
' PrepPaging prepares page count & current page.
'
'   Input:
'       pc              Count of items
'       pcPageSize      Count of items per page
'       piPageFirst     Integer representing first page
'       piPage          Current page
'
'   Output:
'       piPage          Current page
'       pcPage          Count of pages
'       piFirst         Index of first element on current page
'       piLast          Index of last element on current page
'
    '
    ' Calculate page count
    '
    pcPage = pc \ pcPageSize

    If pc Mod pcPageSize > 0 Then
        pcPage = pcPage + 1
    End If
    '
    ' Adjust current page if out of bounds
    '
    If pcPage > 1 Then
        If piPage > pcPage Or piPage < piPageFirst Then
            piPage = piPageFirst
        End If
    Else
        piPage = piPageFirst
    End If
    '
    ' Determine indices of first & last elements of page.
    '
    If pc > 0 Then
        piFirst = ((piPage - 1) * pcPageSize) + 1
        piLast = piFirst + pcPageSize - 1
        If piLast > pc Then
            piLast = pc
        End If
    End If

End Sub

Public Sub App_RenderPage(pstrPageHeading, pstrCtlFocus)
%>
    <HTML>
    <HEAD>
    <TITLE></TITLE>
    <STYLE TYPE="text/css">
       <!--
            .<%=gstrCSS_CLASS_FONT_HEADING%> {font-family: Arial, Helvetica; font-size: Large; font-weight: bold} 
            .<%=gstrCSS_CLASS_FONT_HEADING_SMALL%> {font-family: Arial, Helvetica; font-size: Small; font-weight: bold} 
            .<%=gstrCSS_CLASS_FONT_NORMAL%> {font-family: Arial, Helvetica; font-size: x-Small} 
        --> 
    </STYLE>
<%
        Call Page_RenderJavaScript()
%>
    </HEAD>
    <BODY BGCOLOR="<%=ghtmlBG_COLOR%>">
    <FORM NAME="<%=gstrFORM_MAIN%>" ACTION="<%=gstrASP_HANDLE_CMDS%>" METHOD="POST" TARGET="<%=gstrFRAME_HANDLE_CMDS%>">
    <Font Class=<%=gstrCSS_CLASS_FONT_HEADING%>><%=pstrPageHeading%></Font><HR>
<%
        Call Page_RenderContent()
%>
    <INPUT TYPE=Hidden NAME="<%=gstrREQUEST_CMD%>">
<%
    If Len(pstrCtlFocus) > 0 Then
%>
        <SCRIPT LANGUAGE="JavaScript">
            parent.SetFocus(document.<%=gstrFORM_MAIN & "." & pstrCtlFocus%>)
        </SCRIPT>
<%
    End If
%>
    </FORM>
    </BODY>
    </HTML>
<%
End Sub

Public Sub App_ShowInputText(pstrTxtName, pstrValue, piTxtMaxLen, piTxtSize)
    Dim strTxtSize

    If piTxtSize = giTXT_SIZE_NORMAL Then
        strTxtSize = gstrNONE
    Else
        strTxtSize = " Size=" & CStr(piTxtSize)
    End If
%>
    <Input Type='Text' Name='<%=pstrTxtName%>' Value='<%=pstrValue%>' MaxLength=<%=piTxtMaxLen%> <%=strTxtSize%> OnFocus='parent.txt_OnFocus(document.<%=gstrFORM_MAIN%>.<%=pstrTxtName%>)'>
<%
End Sub

Public Sub App_ShowMsg(pstrMsg, perr, pstrErrDesc)
    Dim strMsg

    If perr = gerrNONE Then
        strMsg = pstrMsg
    Else
        strMsg = pstrMsg _
                & gjsNEW_LINE & gjsNEW_LINE & "Error Number: " & Hex(perr) _
                & gjsNEW_LINE & "Error Description: " & pstrErrDesc
    End If
%>
    <SCRIPT Language="JavaScript">
        window.alert("<%=strMsg%>")
    </SCRIPT>
<%
End Sub

Public Function App_strFromHTML(pstr)
'
' strFromHTML formats a string passed from the browser.
'
    Dim strSav

    strSav = pstr

    strSav = Replace(strSav, Chr(gstrANSI_NB_SPACE), gchSPACE)

    App_strFromHTML = strSav
End Function

Public Function App_strHTML(pstr)
'
' strHTML prepares a string for display, handling special html characters
' and line breaks.
'
    Dim strSav
    Dim rgch
    Dim irgch

    rgch = Array(gchAMPERSAND, gchAPOSTROPHE, gchLESS_THAN, gchGREATER_THAN, gchQUOTE)

    strSav = pstr
    '
    ' Replace special characters w/ numeric entities
    '
    For irgch = LBound(rgch) To UBound(rgch)
        strSav = Replace(strSav, _
                            rgch(irgch), _
                            gstrHTML_NUMERIC_ENTITY_PREFIX _
                            & App_strLeadingZeros(Asc(rgch(irgch)), gcHTML_NUMERIC_ENTITY_CHARACTERS) _
                            & gstrHTML_NUMERIC_ENTITY_SUFFIX)
    Next
    '
    ' Replace spaces w/ nonbreaking space
    '
    strSav = Replace(strSav, gchSPACE, gstrHTML_NB_SPACE)
    '
    ' Add HTML line breaks in place of LF's
    '
    strSav = Replace(strSav, vbLF, gstrHTML_BREAK)
     
    App_strHTML = strSav
End Function

Private Function strNumericEntityFromCh(pstr, pch)
'
' strNumericEntityFromCh replaces the passed character with a numeric entity that may
' be rendered by a browser.
'
    strNumericEntityFromCh = Replace(pstr, _
                                pch, _
                                gstrHTML_NUMERIC_ENTITY_PREFIX _
                                & App_strLeadingZeros(Asc(pch), gcHTML_NUMERIC_ENTITY_CHARACTERS) _
                                & gstrHTML_NUMERIC_ENTITY_SUFFIX)
End Function

Public Function App_strLeadingZeros(pi, pcCh)
'
' strLeadingZeros returns a string of length pcCh consisting of the passed integer and
' leading zeros.
'
    Dim strSav

    strSav = CStr(pi)

    App_strLeadingZeros = String(pcCh - Len(strSav), gchZERO) & strSav
End Function

Public Function App_strReplace(pstr, pchReplace, prgstrReplace())
'
' strReplace replaces the replacement character, pchReplace, in string, pstr, w/
' items in the passed array of replacement values, prgstrReplace.
'
    Dim strReplace
    Dim iReplace

    strReplace = pstr

    For iReplace = LBound(prgstrReplace) To UBound(prgstrReplace)
        strReplace = Replace(strReplace, pchReplace, prgstrReplace(iReplace), 1, 1)   
    Next

    App_strReplace = strReplace
End Function

Public Sub App_RenderPaging(pstrCmd, piPage, pcPage, pstrAltPrevPage, pstrAltNextPage)
%>
    <A HRef="JavaScript:GoToPage('<%=gstrCMD_PREV_PAGE%>')"><Img Src="PrevPage.gif" Height=20 Width=20 Alt="<%=pstrAltPrevPage%>" Border=1 Align="top"></A>
    <A HRef="JavaScript:GoToPage('<%=gstrCMD_GO_TO_PAGE%>')"><Font Class=<%=gstrCSS_CLASS_FONT_NORMAL%>>Page</Font></A>

    <Input Type="text" Size=3 MaxLength=5 Value="<%=piPage%>" Name="<%=gstrTXT_PAGE_GO_TO%>" OnFocus="parent.txt_OnFocus(document.<%=gstrFORM_MAIN%>.<%=gstrTXT_PAGE_GO_TO%>)"><Font Class=<%=gstrCSS_CLASS_FONT_NORMAL%>> of <%=pcPage%></Font>

    <A HRef="JavaScript:GoToPage('<%=gstrCMD_NEXT_PAGE%>')">
        <IMG SRC="NextPage.gif" HEIGHT=20 WIDTH=20 Alt="<%=pstrAltNextPage%>" Border=1 Align="top">
    </A>

    <Input Type=Hidden Name="<%=gstrHIDDEN_I_PAGE%>" Value=<%=piPage%>>
    <Input Type=Hidden Name="<%=gstrHIDDEN_C_PAGE%>" Value=<%=pcPage%>>
    <Input Type=Hidden Name="<%=gstrHIDDEN_I_PAGE_GO_TO%>" Value=<%=piPage%>>
    <Input Type=Hidden Name="<%=gstrHIDDEN_CMD_GO_TO_PAGE%>">

    <Script>
        function GoToPage(pstrCmd) {
            document.<%=gstrFORM_MAIN%>.<%=gstrHIDDEN_CMD_GO_TO_PAGE%>.value = pstrCmd;

            ValidateCmd('<%=pstrCmd%>');
        }
    </Script>
<%
End Sub

Public Function App_RgstrFromRequestForm(pcol)
'
' RgstrFromRequestForm returns an array from a request.form collection.
'
    Dim colstr
    Dim ccolstr
    Dim rgstr()
    Dim irgstr
    '
    ' Format each collection element & move to the array
    '
    Set colstr = pcol

    ccolstr = colstr.Count

    Redim rgstr(ccolstr - 1)

    For irgstr = LBound(rgstr) To UBound(rgstr)
        rgstr(irgstr) = App_strFromHTML(colstr(irgstr + 1))
    Next

    App_RgstrFromRequestForm = rgstr
End Function
%>