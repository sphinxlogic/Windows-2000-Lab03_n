'==========================================================================
'                                                                     
'   Microsoft Site Server v3.00                                   
'                                                                     
'   Copyright (c) 1997-98 Microsoft Corporation.  All rights reserved.   
'   THIS CODE AND INFORMATION IS PROVIDED 'AS IS' WITHOUT WARRANTY OF
'   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
'   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
'   PARTICULAR PURPOSE.
'==========================================================================
' This script forces Search to propagate DirmonCatalog.
' If a server name is provided in the command line, it is
' added to the Search servers list before forcing propagation
'==========================================================================

Option Explicit
On Error Resume Next

sub Usage
    WScript.Echo "Usage:    cscript ForcePropDirmonCatalog.vbs [<SearchServerHost>]"
	WScript.Echo "Examples: cscript ForcePropDirmonCatalog.vbs"
	WScript.Echo "          cscript ForcePropDirmonCatalog.vbs KNOWLEDGE_HOST"
	WScript.Echo
end sub

sub CheckError (Number, Message)
	if Number <> 0 then		'NO ERROR
		Wscript.echo "Error #" & " 0x " & Hex(Number) & " - " & Err.Description
		Wscript.echo "      - received on " & Message
		Wscript.quit
	end if
end sub

'-----------------------------------------------------------------
' Begin main routine. Parse command-line.
'-----------------------------------------------------------------
if WScript.Arguments.Count = 1 then
	if WScript.Arguments(0) = "/?" or WScript.Arguments(0) = "-?" then
		Usage
	    WScript.Quit(1)
	end if
end if

'-----------------------------------------------------------------
' Initializing.
'-----------------------------------------------------------------
dim objSearchAdmin, objBuildServer, objBuildCatalogs, objBuildCatalog, strCatalog
dim objSearchServers, objServer

strCatalog = "DirmonCatalog"

set objSearchAdmin = CreateObject("Search.SearchAdmin.1")
CheckError Err.Number, "creating SearchAdmin object."

objSearchAdmin.HostName = "" 

' Get the catalog builder
set objBuildServer = objSearchAdmin.BuildServer 
CheckError Err.Number, "creating BuildServer object."

' Get the list of catalogs
set objBuildCatalogs = objBuildServer.BuildCatalogs 
CheckError Err.Number, "creating BuildCatalogs object."

set objBuildCatalog = objBuildCatalogs.Item(strCatalog)
CheckError Err.Number, "creating BuildCatalog object."

set objSearchServers = objBuildCatalog.SearchServers
CheckError Err.Number, "creating SearchServers object."

'-----------------------------------------------------------------
' If the command line does not include a server name,
' check that there is at least one Search server defined
'-----------------------------------------------------------------
if WScript.Arguments.Count = 0 then
	if objSearchServers.Count = 0 then	' Use <localhost> if no Search server defined
	    Wscript.echo "Propagating " & strCatalog & " catalog to <localhost>" 
		objSearchServers.Add("localhost")
	   	CheckError Err.Number, "adding <localhost> as Search server host."
	end if
else ' Add Search server host
	objSearchServers(Wscript.arguments(0))
	if Err.Number = 1 then
	    Wscript.echo "Adding Search server host: " & Wscript.arguments(0)
		objSearchServers.Add(Wscript.arguments(0))
	end if
	CheckError Err.Number, "adding Search server host." & Wscript.arguments(0)
end if

'We must have at least one Search server defined. Let's list them.
Wscript.echo "Start propagation to the Search server on each of the following host(s):"
for each objServer in objSearchServers
    Wscript.echo "    " & objServer.Name
next

'-----------------------------------------------------------------
' Start propagation
'-----------------------------------------------------------------
objBuildCatalog.ForceProp 
CheckError Err.Number, "forcing propagation."
