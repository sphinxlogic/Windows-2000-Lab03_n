
<div CLASS=CMenu>
<table CLASS=CAdMin COLSPAN=5 CELLSPACING=2 CELLPADDING=4 WIDTH=75%>
<tr>
<td><span onclick="javascript:GoHomePage()"  TITLE="Go to home page">Home</span></td>
<td><span onclick="javascript:GoCatalogPage()"  TITLE="Go to catalog page" >Catalog</span></td>
<td><span onclick="javascript:GoCheckOutPage()" TITLE="Go to checkout page">CheckOut</span></td>
<td><span onclick="javascript:GoCheckInPage()"  TITLE="Go to checkin page">CheckIn</span> </td>
<td><span onclick="javascript:GoRenewPage()"    TITLE="Go to renew page">Renew</span> </td>
<td><span onclick="javascript:GoSettingsPage()" TITLE="Go to settings page">Settings</span></td>
</tr>
</table>
</div>

<script language=JavaScript>
function GoHomePage(){
   document.location.href="../default.asp";
}
function GoCatalogPage(){
   document.location.href="cfilter.asp";
}
function GoCheckOutPage(){
   document.location.href="viewrequests.asp";
}
function GoCheckInPage(){
   document.location.href="checkin.asp";
}
function GoRenewPage(){
   document.location.href="Renew.asp";
}
function GoSettingsPage(){
   document.location.href="Appsettings.asp";
}
</script>
