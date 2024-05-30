<%@ Language=VBScript EnableSessionState=False %>
<% Option Explicit %>
<% Response.Expires = 0 %>
<% 'Copyright Microsoft 1998-1999.  All rights reserved. %>
<HTML>
<HEAD>
<Title> Check In Materials </Title>
<META NAME="GENERATOR" Content="Microsoft Visual Studio 6.0">
<link rel="stylesheet" href="../_Themes/fm/theme.css">
</HEAD>

<BODY>

<img CLASS="logo"     SRC="../images/fmlogo.gif" WIDTH="187" HEIGHT="90">
<img CLASS= "sublogo" SRC="../images/Fmcorplib.gif" WIDTH="180" HEIGHT="18">

<!-- #include file="Navigation.asp"-->
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

<div ID="Items" STYLE="POSITION: absolute; LEFT: 20px; TOP: 120px; WIDTH: 95%; Z-INDEX:500">
   <span style="COLOR: #000000; FONT-FAMILY: Verdana,arial; FONT-WEIGHT: bold; FONT-SIZE: 12pt; TEXT-DECORATION: none">Check In Materials</span>

<br><br><br><br>
<FORM name=frmCheckin action="<%= Request.ServerVariables("SCRIPT_NAME") %>" method="POST">
<TABLE COLS=3 WIDTH=60% COLSPAN=2 BORDER=0 CELLSPACING=0 CELLPADDING=1>
  <tr><td COLSPAN=3><font SIZE=-2>Enter the <strong>Barcode</strong> for the items you
   wish to check in and click the "Check In" button. Select <strong>Auto-Checkout</strong>
   to automatically assign the item to the next request in line.</font><br><br>
  </td></tr>

  <TR>
		<TD>Bar code:</TD>
		<TD><INPUT type="textbox" name="txtBarcode"></TD>
  </TR>
  <TR>
   	<TD>Location:</TD>
		<TD><INPUT type="textbox" name="txtLocation" value="<%= Application("DefaultLocation") %>"></TD>
  </TR> 
  <TR>
		<TD>Auto-Checkout:&nbsp;&nbsp;<input type ="checkbox" name ="chkCheckOut" checked></TD>
		<TD><INPUT type="submit" name ="submit" value="Check In"></TD>
  </TR> 
 </TABLE>
</FORM>
</div>

<script language=VbScript>

sub window_Onload()
   document.all.frmCheckin.txtBarcode.focus 
end sub

If frmCheckin.chkCheckOut.Checked = True Then 
   frmCheckIn.chkCheckOut.Value = 1
Else
   frmCheckIn.chkCheckOut.Value = 0
End If
</script>

<div ID="checkin" STYLE="position:absolute;left:60;top:340;z-index:5">
<table COLS=3 BORDER=0 CELLSPACING=4 CELLPADDING=0>
<% Dim barCode,objAdmin,location,nBibNo,objUser,borrowerNo,strComment,rsRequests
   Dim nRequests
   If Request.ServerVariables("HTTP_METHOD")="POST" then

      barCode = Request.Form("txtBarcode")
      If barCode=""  Then
         Response.Write "<tr VALIGN=Top><td COLSPAN=2>You must specify a barcode" & _
                  "<td></td></tr>" & vbCrLf
      End If

      location = Request.Form("txtLocation")
      
      Set objAdmin = Server.CreateObject("CML.Admin")
      If Not IsObject(objAdmin) then 
         Response.Write "ERROR: Unable to Instantiate the Admin Object"
         Response.End
      End If
   
      objAdmin.ConnectionString = Application("FmLib_ConnectionString")
      Set rsRequests = objAdmin.LookupBarcode(barCode)
      
      Response.Write "<tr VALIGN=Top><td><img SRC=""../images/icon" & _
                     rsRequests("Coll") & ".gif"">&nbsp;</td><td><span CLASS=Title>" & _
                     rsRequests("Title") & "</span></td><td><strong>" & _
                     rsRequests("Call") & "</strong></td></tr>" & vbCrLf
                     
      nBibNo = objAdmin.CheckIn(barCode, location)
      
      If nBibNo > 0 Then
         If CInt(Request.Form("chkCheckout"))= 1 Then 

            '--- If AutoCheckout, search for other requests for this bib#
            Set rsRequests = objAdmin.Requests(nBibNo)
            If Not rsRequests.EOF Then
            
               Set objUser = Server.CreateObject ("CML.User")
               objUser.ConnectionString = objAdmin.ConnectionString
               
               borrowerNo = objAdmin.CheckOut(barCode, DateAdd("d",Application("CheckoutPeriod"),Date))

               objUser.GetInfoFromTable (borrowerNo)
               Response.Write "<tr><td COLSPAN=3>Item checked out to: " & objUser.FullName & " (" & _ 
                              rsRequests("Location") & ")<br><font SIZE=-2>" & rsRequests("Comment") & _
                              "</font></td></tr>" & vbCrLf
                              
            Else
               Response.Write "<tr><td COLSPAN=3>No more requests for this item exist. Item was checked in.</td></tr>" & vbCrLf
            End If
         Else
            Response.Write "<tr><td COLSPAN=3>Item has been checked in.</td></tr>" & vbCrLf
         End If
      Else
         Response.Write "<tr><td COLSPAN=3>This item was already checked in. No action performed.</td></tr>" & vbCrLf
      End If
           
      Set objAdmin = Nothing 
      Set objUser = Nothing
   End If
%>
</table>
</div>

</BODY>
</HTML>

