<!--
// OnDSScriptCommandEvt() is required to receive the ScriptCommand event
// registered by appObs.setByProxyDSScriptCommandObserver().
//
// Other event handlers would have similar syntax.
//
function OnDSScriptCommandEvt(scType, scParam)
{
    alert("ScriptCommand: " + scType + ", " + scParam);

}   /* end OnDSScriptCommandEvt() */
//-->