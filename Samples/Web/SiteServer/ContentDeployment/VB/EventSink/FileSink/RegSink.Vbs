'====================================================================
'                                                                     
'   Microsoft Site Server v3.00                                   
'                                                                     
'   Copyright (c) 1997-98 Microsoft Corporation.  All rights reserved.   
'   THIS CODE AND INFORMATION IS PROVIDED 'AS IS' WITHOUT WARRANTY OF
'   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
'   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
'   PARTICULAR PURPOSE.
'=====================================================================
	Option Explicit
	On Error Resume Next

	Dim Server
	Dim MyEventSink
	Dim i


	Set Server = CreateObject("CrsApi.ReplicationServer")
	if Err.Number <> 0 then
		WScript.Echo "CreateObject failed with 0x" & Hex(Err.Number)
		WScript.Quit(Err.Number)
	end if

	Server.Initialize("")
	if Err.Number <> 0 then
		WScript.Echo "ReplicationServer.Initialize failed with 0x" & Hex(Err.Number)
		WScript.Quit(Err.Number)
	end if
	WScript.Echo "Server initialized..."
	

	' Come up with your own event sink name
	Set MyEventSink = Server.AddEventSink("MyFileSinkName")
	if Err.Number <> 0 then
		WScript.Echo "ReplicationServer.AddEventSink failed with 0x" & Hex(Err.Number)
		WScript.Quit(Err.Number)
	end if
	WScript.Echo "Configuring event sink..."

	' ProgID is ProjectName.ClassName
	MyEventSink.CLSID = "cdsink.Filesink"
	if Err.Number <> 0 then
		WScript.Echo "ReplicationEventSinkConfig.put_CLSID failed with 0x" & Hex(Err.Number)
		WScript.Quit(Err.Number)
	end if



	' Register for each event you want the sink to receive
	' Add loop here
	for i = 15000 to 15999		' Add all events!

		MyEventSink.RegisterForEvent(i)
		if Err.Number <> 0 then
			WScript.Echo "ReplicationEventSinkConfig.RegisterForEvent failed with 0x" & Hex(Err.Number)
			Err.Clear
			' Keep trying
		end if

	next

	MyEventSink.Commit
	Server.Commit

	WScript.Echo "Name" & vbTab & vbTab & " = " & MyEventSink.Name
	WScript.Echo "CLSID" & vbTab & vbTab & " = " & MyEventSink.CLSID
	WScript.Echo "ProjectFilter" & vbTab & " = " & MyEventSink.ProjectFilter
	WScript.Echo "DataSource" & vbTab & " = " & MyEventSink.DataSource
	WScript.Echo "UserName" & vbTab & " = " & MyEventSink.UserName
	WScript.Echo "Password" & vbTab & " = " & MyEventSink.Password
	WScript.Echo "Server" & vbTab & vbTab & " = " & MyEventSink.Server
	WScript.Echo "Disabled" & vbTab & " = " & MyEventSink.Disabled
	WScript.Echo "Synchronous" & vbTab & " = " & MyEventSink.Synchronous
	WScript.Echo "ProviderCLSID" & vbTab & " = " & MyEventSink.ProviderCLSID
	WScript.Echo "EventLifetime" & vbTab & " = " & MyEventSink.EventLifetime

	WScript.Echo
	WScript.Echo "Note: You must stop and restart Content Deployment to use the event sink."
	WScript.Echo "      Be sure to run ""regsvr32.exe filesink.dll"" first."
	WScript.Echo
	WScript.Echo "      By default, events are logged to c:\temp\filesink.log."