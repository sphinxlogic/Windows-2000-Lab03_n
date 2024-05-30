<%@ Language=VBScript EnableSessionState=False %>
<% ' Copyright 1998-1999 Microsoft Corp. All rights reserved. %>
<% Option Explicit %>
<% Response.Expires = 0 %>
<HTML>
<HEAD>
<TITLE>View Requests and Check Out</TITLE>
<META NAME="GENERATOR"  Content="Microsoft Visual Studio 6.0">
<link  rel="stylesheet" href="../_Themes/fm/theme.css">
<img CLASS="logo"       SRC="../images/fmlogo.gif"    WIDTH="187" HEIGHT="90">
<img CLASS="sublogo"    SRC="../images/Fmcorplib.gif" WIDTH="180" HEIGHT="18">
</HEAD>
<BODY>
<!--#include file="Navigation.asp"-->
<div class=menui>
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

<div ID="Items" STYLE="POSITION: absolute; LEFT: 20px; TOP: 120px; WIDTH: 95%; Z-INDEX: 5">
   <span style="COLOR: #000000; FONT-FAMILY: Verdana,arial; FONT-WEIGHT: bold; FONT-SIZE: 12pt; TEXT-DECORATION: none">Materials Requested</span>

<% Dim oAdmin,oUser,rsRequests,rsAvailable,bShowNoItems
   Dim nReqNo,nBorrowerNo,cRequests,cNoItems

   '--- If present, this URL param will filter those requests that have
   '--- no available items at this time.
   Set bShowNoItems = Request.QueryString("ShowNoItems")
   If IsEmpty(bShowNoItems) Or bShowNoItems="" Then
      bShowNoItems = False
   Else
      bShowNoItems = CBool(bShowNoItems)
   End If
   
   Set oAdmin = Server.CreateObject ("CML.Admin")
   oAdmin.ConnectionString = Application("FmLib_ConnectionString")
 
   
   Set rsRequests = oAdmin.Requests
   If Not rsRequests.EOF Then
      Set oUser = Server.CreateObject ("CML.User")
      oUser.ConnectionString = Application("FmLib_ConnectionString")
%>
<br><br><br>
<form NAME=frmCheckout ACTION="Checkout.asp" METHOD=Post>
<table COLS=3 BORDER=0 WIDTH="100%" CELLSPACING=4 CELLPADDING=0>
<tr><td COLSPAN=2>
<font SIZE=-2>To check out materials, select a <strong>Barcode</strong> from
 the drop-down list boxes, and click the "Check Out Materials"
 button. Leave selection box empty to ignore a request.</font></td>
<td ALIGN=Right>Due Date: 
<input NAME=DueDate VALUE="<%= DateAdd("d",Application("CheckoutPeriod"),Date) %>">
</td></tr>
<tr><th COLSPAN=2 ALIGN=Left WIDTH="60%">Title</th><th ALIGN=Left>Call#</th></tr>
<%
      '--- Because more than a single request is presented on this page, we
      '--- need some way of mapping barcodes to a borrower's request.  We'll
      '--- create a compound form variable to hold an array of request#'s.
      '--- For each request ### there will be two other form variables.
      '
      '     u### --> borrower ID
      '     b### --> item barcode (blank if no check-out)
      
      cRequests = 0
      cNoItems = 0
      Do Until rsRequests.EOF
         Set rsAvailable = oAdmin.Available(rsRequests("BibNo"))
         If Not (rsAvailable.EOF And Not bShowNoItems) Then
            cRequests = cRequests + 1
            nReqNo = rsRequests("request#")
            Response.Write "<input TYPE=Hidden NAME=Requests VALUE=" & rsRequests("request#") & ">" & vbCrLf
            
            nBorrowerNo = rsRequests("BorrowerNo")
            Response.Write "<input TYPE=Hidden NAME=u" & nReqNo & " VALUE=" & nBorrowerNo & ">"
            
            Response.Write "<tr VALIGN=Top><td><img SRC=""../images/icon" & _
                           rsRequests("Coll") & ".gif"">&nbsp;&nbsp;</td><td><span CLASS=Title>" & _
                           rsRequests("Title") & "</span></td><td><strong>" & _
                           rsRequests("Call") & "</strong></td></tr>" & vbCrLf
            
            oUser.GetInfoFromTable nBorrowerNo
            Response.Write "<tr VALIGN=Top><td COLSPAN=2>" & oUser.FullName & " (" & rsRequests("Location") & _
                           ")<br><font SIZE=-2>" & rsRequests("Comment") & "&nbsp;</font></td><td>" & vbCrLf
            If Not rsAvailable.EOF Then
               Response.Write "<select NAME=b" & nReqNo & " WIDTH=""100%""><option VALUE=""""></option>" & vbCrLf
               Do Until rsAvailable.EOF
                  Response.Write "<option VALUE=""" & rsAvailable("barcode") & """>" & _
                                 rsAvailable("barcode") & "</option>" & vbCrLf
                  rsAvailable.MoveNext
               Loop
               Response.Write "</select></td></tr>" & vbCrLf
            Else
               cNoItems = cNoItems + 1
               Response.Write "<strong>No items are available to satisfy this request.</strong></td></tr>" & vbCrLf
            End If
            Response.Write "<tr HEIGHT=1><td COLSPAN=3><hr HEIGHT=1></td></tr>" & vbCrLf
         End If
         rsRequests.MoveNext
      Loop
      
      If cRequests = 0 Then
         Response.Write "<tr><td COLSPAN=3><i>Requests exist, but were not shown due to lack of available items.</i><br>" & _
                        "<a HREF=""ViewRequests.asp?ShowNoItems=1"">Click here to show requests with no available items.</a></td></tr>"
      End If
      
      If cNoItems > 0 Then
         Response.Write "<tr><td COLSPAN=3><i>Some requests cannot be satisfied because of unavailable items.</i><br>" & _
                        "<a HREF=""ViewRequests.asp?ShowNoItems=0"">Click here to hide requests with no available items.</a></td></tr>"
      End If
%>
<tr><td COLSPAN=2><font SIZE=-1>&nbsp;</font></td></tr>
<tr><td COLSPAN=2><input TYPE=Submit VALUE="Check Out Materials"></td></tr>
</table>
</form>
<font SIZE=-2>Requests displayed: <%= cRequests %></font>
<%
      Set oUser = Nothing
   Else
      Response.Write "<br><br><br><i>No requests found.</i>"
   End If
   
   Set oAdmin = Nothing
%>
</div>
</BODY>
</HTML>
