'***************************************************************************
' 
' WMI Sample Script - Win32_Process enumeration (VBScript)
'
' This script demonstrates how to enumerate processes.
'
'***************************************************************************
for each Process in GetObject("winmgmts:{impersonationLevel=impersonate,(Debug)}").InstancesOf ("win32_process")
	WScript.Echo Process.ProcessId, Process.name
next

