<%
dim currentpage
currentpage = LCase(Request.ServerVariables("SCRIPT_NAME"))
currentpage = Mid(currentpage,InStrRev(currentpage,"/")+1)

sub Blue(description, page)
   dim imgx
	imgx = "images/bluedot.gif"
	if currentpage = page then imgx="images/bluearrow.gif"
	
	Response.Write("<TD><IMG src='" & imgx & "'WIDTH=21 HEIGHT=21 id=mI>")
	Response.Write("<TD nowrap class=menu><a class=menu href='" & page & "' id=mIa>" & description & "</a>")
end sub

sub Orange(description, page)
   dim imgx
	imgx = "images/orangedot.gif"
	if currentpage = page then imgx="images/orangearrow.gif"
	
	Response.Write("<TD><IMG src='" & imgx & "'WIDTH=21 HEIGHT=21 id=mI>")
	Response.Write("<TD nowrap class=menu><a class=menu href='" & page & "' id=mIa>" & description & "</a>")
end sub
%>

<div class=menui id=menu>
<TABLE border=0 class="watermark" height=250 width=250 CELLSPACING=0 CELLPADDING=0>
<TR vAlign=top><TD>

   <div class="bluemenu">
   <table class="small" BORDER="0" CELLSPACING="0" CELLPADDING="0">
   <tr> <% Blue "Library Home Page", "default.asp" %> </tr>
   <tr> <% Blue "Search for Library Materials", "librarysearch/Library.asp" %> </tr>
  	<tr> <% Blue "View Current Requests", "ViewMYRequests.asp" %> </tr>
	</table>
   </div>
   <TABLE class=admin WIDTH=75% BORDER=0 CELLSPACING=2 CELLPADDING=2>
   <TR>
   <TD BGCOLOR=#ce6300 valign=top ALIGN=center NOWRAP id=mI>
       Administration</TD>
   </TR>
   </TABLE>
   <br>
	<DIV class=orangemenu>
	<TABLE class=small BORDER=0 CELLSPACING=2 CELLPADDING=2>
		<tr> <%Orange "Log On", "admin/Menu.asp"%> </tr>
	</TABLE>
	</DIV>
</TD></TR>
</TABLE>
</div>
