<%@ Language=VBScript EnableSessionState=False %>
<% ' Copyright 1998-1999 Microsoft Corp. All rights reserved. %>
<% Option Explicit %>
<% Response.Buffer = True %>
<html>
<title>Failed Checkouts</title>
<link  rel="stylesheet" href="../_Themes/fm/theme.css">
<img CLASS="logo"       SRC="../images/fmlogo.gif"    WIDTH="187" HEIGHT="90">
<img CLASS="sublogo"    SRC="../images/Fmcorplib.gif" WIDTH="180" HEIGHT="18">
</HEAD>
<BODY>
<!-- #include file="Navigation.asp"-->

<div class=menui style="position:absolute;left:15px;top:140;">
<TABLE border=0 class="watermark" height=250 width=200 CELLSPACING=0 CELLPADDING=0>
<TR vAlign=top><TD>
   <TABLE class=admin WIDTH=75% BORDER=0 CELLSPACING=2 CELLPADDING=2>
   <TR>
      <TD BGCOLOR=#ce6300 valign=top ALIGN=center NOWRAP id=mI>Administration</TD>
   </TR>
   </TABLE></TD>
</TR>
</TABLE>
</div>

<div ID="Items" STYLE="POSITION: absolute; LEFT: 20px; TOP: 120px; WIDTH: 95%; Z-INDEX: 500">
   <span style="COLOR: #000000; FONT-FAMILY: Verdana,arial; FONT-WEIGHT: bold; FONT-SIZE: 12pt; TEXT-DECORATION: none">Failed Checkouts</span>


<% Dim oAdmin,item,strBarcode,nBorrowerID,dtDueDate
   Dim nOK,oUser,bStopAndWarn

   dtDueDate = Request.Form("DueDate")
   If IsDate(dtDueDate) Then
      dtDueDate = CDate(dtDueDate)
   Else
      Response.Write "Invalid due date specified."
      Response.End
   End If
   
   Set oAdmin = Server.CreateObject ("CML.Admin")
   oAdmin.ConnectionString = Application("FmLib_ConnectionString")
   
   '--- Loop through Requests and check-out items that have been assigned
   
   For Each item In Request.Form("Requests")
      strBarcode = Request.Form("b" & item)
      If strBarcode <> "" Then
         nBorrowerID = CLng(Request.Form("u" & item))
         nOK = oAdmin.CheckOut(strBarcode, dtDueDate)
         If nOK <> nBorrowerID Then
            If oUser Is Nothing Then Set oUser = Server.CreateObject("CML.User")
            oUser.GetInfoFromTable nBorrowerID
            Response.Write "Failed to checkout '" & strBarcode & "' to " & oUser.Fullname & ".<br>"
            If nOK > 0 Then
               oUser.GetInfoFromTable nOK
               Response.Write "Item checked out to " & oUser.Fullname & " instead.<br>"
            End If
            bStopAndWarn = True
         End If
      End If
   Next
   
   Set oAdmin = Nothing
   
   If Not bStopAndWarn Then
      Response.Redirect "ViewRequests.asp"
   Else
      Response.Write "<br><br><a HREF=""ViewRequests.asp"">Click here to return to Checkout Page</a>"
   End If
%>
</div>

</BODY>
</HTML>