'***************************************************************************
' 
' WMI Sample Script - NT Event Logger (VBScript)
'
' This script demonstrates how to display NT events using a notification
' query.
'
'***************************************************************************
on error resume next
set events = GetObject("winmgmts:{impersonationLevel=impersonate}").ExecNotificationQuery _ 
	("select * from __instancecreationevent where targetinstance isa 'Win32_NTLogEvent'") 					

if err <> 0 then
	WScript.Echo Err.Description, Err.Number, Err.Source
end if 

' Note this next call will wait indefinitely - a timeout can be specified 

WScript.Echo "Waiting for NT Events..."
WScript.Echo ""

do 
	set NTEvent = events.nextevent 
	if err <> 0 then
		WScript.Echo Err.Number, Err.Description, Err.Source
		Exit Do
	else		
		WScript.Echo NTEvent.TargetInstance.Message
	end if
loop

WScript.Echo "finished"

