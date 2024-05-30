<%
dim confnumber

confnumber=time

%>
<%Response.Expires=0%>

<html>

<head>
<title>ANSWER ASP FORM</title>

<SCRIPT LANGUAGE="JavaScript"> 
            function CancellErrors()        
            {
            return true;
            }
            //window.onerror = CancellErrors;
            var CallConfiguration;
            var PreviousTTS;
            if(window.external.hostName == "Microsoft Web Telephony Engine")
            {
                CallConfiguration=window.external.Configuration;
                PreviousTTS = CallConfiguration.rendertts;
	        CallConfiguration.rendertts = true;
		CallConfiguration.backkey="";
            }
            function CancelPageSettings()
	    {
	    if(window.external.hostName == "Microsoft Web Telephony Engine") 
            {
                CallConfiguration.rendertts=PreviousTTS;
            }
		
            }	      
</script>
</head>

<body background="images/back.jpg" Onunload="CancelPageSettings();">

<h1 align="center"><img src="images/reservation_c.gif" width="600" height="60" alt="reservation_c.gif (13509 bytes)"></h1>

<div align="center"><center>
<table border="0" cellpadding="0" cellspacing="0" width="100%">
  <tr>
    <td width="100%"><% Loca = Request.Form("Loca") %>
<% PartyNum = Request.Form("PartyNum") %>
<% ResTime = Request.Form("ResTime") %>
<% Smoking = Request.Form("Smoking") %>
<p align="center">
<a VoiceFile="Waves\YourRes.wav">Restaurant:</a> <% if Loca="Kirkland" then%> <a VoiceFile="Waves\Kirkland.wav">Kirkland</a> <% End If %> <% if Loca="Raglan" then%> <a VoiceFile="Waves\Raglan.wav">Raglan</a> <% End If %> <% if Loca="Bellevue" then%>
    <a VoiceFile="Waves\Bellevue.wav">Bellevue</a> <% End If %> <% if Loca="Seattle" then%> <a VoiceFile="Waves\Seattle.wav">Seattle</a>
<% End If %>    <br>
    <a VoiceFile="Waves\PartyOf.wav">Party of: <%=PartyNum%> </a><a VoiceFile="Waves\<%=PartyNum%>.wav"></a>
    <br>
    <a VoiceFile="Waves\MadeFor.wav">Reservation Time: <%=ResTime%>:00</a><br>
<% if ResTime="5" then%>    <a VoiceFile="Waves\ResTime5.wav"></a> <% End If %> <% if ResTime="6" then%> <a VoiceFile="Waves\ResTime6.wav"></a> <% End If %> <% if ResTime="7" then%> <a VoiceFile="Waves\ResTime7.wav"></a> <% End If %> <% if ResTime="8" then%> <a VoiceFile="Waves\ResTime8.wav"></a> <% End If %> <% if ResTime="9" then%> <a VoiceFile="Waves\ResTime9.wav"></a> <% End If %> <% if Smoking="" then%> <a VoiceFile="Waves\SmokingSec.wav">Smoking</a> <% Else %> <a VoiceFile="Waves\NonSmokingSec.wav">Non-Smoking</a><br <% End If %> <BR>
    <a VoiceFile="Waves\ConfirmNum.wav">Confirmation Number:<%=PartyNum%><%=ResTime%><%=PartyNum%></a>
    <a VoiceFile="Waves\<%=PartyNum%>.wav"></a>
    <a VoiceFile="Waves\<%=ResTime%>.wav"></a>
    <a VoiceFile="Waves\<%=PartyNum%>.wav"></a>
</p>    
    <hr align="center">
    <!--
    <p align="center"><a accessKey="1" VoiceFile="Waves/ReceiveDir.wav" HREF="DirOption.htm"></a><br>
    <a accessKey="2" VoiceFile="Waves/ConnectRes.wav" HREF="Transfer.htm"></a> <a accessKey="#" VoiceFile="Waves/EndCall.wav" HREF="Final.htm"></a> <a HREF="Default.htm"></a><br>
    -->
    </td>
  </tr>
</table>
</center></div>

<p align="center">
    <a accessKey="*" VoiceFile="Waves/ReturnMain.wav" HREF="Default.htm">
    <img src="images/home.gif" width="140" height="60" alt="home.gif (2942 bytes)" border="0">
</a> 
<a accessKey="1" VoiceFile="Waves/ResOption.wav" href="ResOption.htm">
 <img src="images/reservation.gif" width="140" height="60" alt="reservation.gif (2961 bytes)" border="0">
</a> 
</p>

</body>
</html>
