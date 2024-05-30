//***************************************************************************
// 
// WMI Sample Script - Method invocation (JScript)
//
// This script demonstrates how to invoke a CIM method
// as if it were an automation method of SWbemObject
//
//***************************************************************************

var process = GetObject("winmgmts:{impersonationLevel=impersonate}!Win32_Process");

var processid;

var result = process.Create ("notepad.exe",null,null,processid);
WScript.Echo ("Method returned result = " + result);

