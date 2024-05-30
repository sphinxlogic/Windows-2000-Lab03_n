<!--
// ********************* BEGIN NETSCAPE SPECIFIC BLOCK - NETSHOW V3 *********************
//
// Event Initialization Template.
//
// Modify and include this file when event handling is required
// on a page with the embedded player.
//
// Include example: (place this in the .htm file)
//
//      <SCRIPT language=javascript src=NsNavInitEvts.js></SCRIPT>
//
// RegisterEventObservers() is called by adding:  onload="RegisterEventObservers()"
// to the <BODY> tag of page.
//
//  Example:
//      <BODY onload="RegisterEventObservers()">
//
// Registering event observers:
//
//  Syntax:
//      var pluginJavaPeerRef = document.OBJECT_NAME;
//      document.appObs.setByProxyDS[event name goes here]Observer(pluginJavaPeerRef, [true|false]);
//
//  Example:
//      var pluginJavaPeerRef = document.NSPlay;
//      document.appObs.setByProxyDSScriptCommandObserver(pluginJavaPeerRef, true);
//

function RegisterEventObservers ()
{
    var pluginJavaPeerRef = document.NSPlay;
    document.appObs.setByProxyDSScriptCommandObserver(pluginJavaPeerRef, true);
    document.appObs.setByProxyDSPlayStateChangeObserver(pluginJavaPeerRef, true);
    document.appObs.setByProxyDSReadyStateChangeObserver(pluginJavaPeerRef, true);

}   /*  end RegisterEventObservers() */

function InitEvents ()
{
    if (document.forms.length > 0)
        RegisterEventObservers();
    else
        setTimeout("InitEvents()", 500);
}
// ********************* END NETSCAPE SPECIFIC BLOCK - NETSHOW V3 *********************
//-->
