//***************************************************************************
// 
// WMI Sample Script - Win32_Process enumeration (JScript)
//
// This script demonstrates how to enumerate processes.
//
//***************************************************************************

// Note use of impersonation and setting of Debug (SeDebugPrivilege) to
// ensure access to data.

var e = new Enumerator (GetObject("winmgmts:{impersonationLevel=impersonate,(Debug)}").InstancesOf("Win32_process"));

for (;!e.atEnd();e.moveNext())
{
	var p = e.item ();
	WScript.Echo (p.Name, p.Handle);
}
