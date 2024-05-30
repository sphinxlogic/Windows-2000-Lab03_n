<%Response.Expires=0%>
<HTML>
<!-- 
/**************************************************************************
 *
 * Copyright (c) 1998 Microsoft Corporation.  All rights reserved.
 *
 * This is prerelease software and is provided as is and Microsoft
 * makes no warranties, either express or implied.  The entire risk of
 * the use or the results of the use of this prerelease software
 * remains with the user.
 **************************************************************************/

-->
<HEAD>
            <TITLE>ANSWER ASP FORM</TITLE>
</HEAD>
<!-- Style Sheet for the links -->
<STYLE>
	a:link 
		{
			color:green;
			font-family:verdana;
			font-size:14pt;
			text-decoration:none;
			cursor:hand;
		}
	a:vlink
		{
			color:green;
			font-family:verdana;
			font-size:14pt;
			text-decoration:none;
			cursor:hand;
		}
	a:hover
		{
			color:forstgreen;
			font-family:verdana;
			font-size:14pt;
			font-weight:bold;
			text-decoration:none;
			cursor:hand;
		}
	a:alink
		{
			color:green;
			font-family:verdana;
			font-size:14pt;
			text-decoration:underline;
			font-weight:bold;
			cursor:hand;
		}
	P	
		{
			color:black;
			font-family:arial;
			font-size:10pt;
		}


</STYLE>
<!-- End of stylesheet -->

<BODY STYLE="background:MOCCASIN">

<H1>Order confirmation</H1>
         
<% part = Request.Form("part number") %>
<% checked = Request.Form("checked") %>
<% radiod = Request.Form("radio") %>
<a VoiceFile=Waves\ThePartNumberIs.wav>Part number: </A>
<a VoiceFile=Waves\Or<%=part%>.wav><%=part%>.</a>
<br>
<a VoiceFile=Waves\ToDeliver.wav > The number of item to be delivered is </a>
<a VoiceFile=Waves\Or<%=radiod%>.wav><%=radiod%>.</a>
<a>You have requested</a>
<% if checked="" then%>
<a VoiceFile=Waves\RequestedRegular.wav>regular mail</a>
<% Else %>
<a VoiceFile=Waves\RequestedExpress.wav>express mail</a>
<% End If %>
<br>
<form>
<input type=button VALUE="Home" STYLE = "Cut-Through : NO" OnClick="navigate('Demo.htm');">
</form>

<HR>

</BODY>
</HTML>
