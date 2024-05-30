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
' This script creates a notification catalog definition for DirMon
' sample application. 
'==========================================================================

Option Explicit
On Error Resume Next

sub CatalogDetected(strCatalog)

	dim strPrompt, vbButtons, strTitle, vbResponse
	dim objSearchCatalogs, objSearchServerTemp, objIndexDS
	dim objSearchAdminTemp
		
	strPrompt = "Catalog " & strCatalog & " already exists!" & Chr(13) _
	    & "Would you like to remove " & strCatalog & " catalog definition and all it's correspoding Search catalogs?" & Chr(13) _ 
		& "If you press Yes, all the DirMon content will be cleaned up!"
	
	vbButtons = vbYesNo + vbDefaultButton2 + vbExclamation + vbSystemModal
	
	strTitle = "Catalog " & strCatalog & " exists!"
	
	vbResponse = MsgBox(strPrompt, vbButtons, strTitle)
	
	if vbResponse = vbYes then
	'Remove DirmonCatalog catalog definition and all the corresponding search catalogs

		'Remove first the catalog definition
	    objBuildCatalogs.Remove(strCatalog)
		CheckError Err.Number, "deleting " & strCatalog & " catalog definition."
	    Wscript.echo "Catalog definition " & strCatalog & " deleted."

		'Remove now all the corresponding Search catalogs
		for each objIndexDS in objSearchServers
			if objIndexDS.Name = objSearchAdmin.HostName then
				set objSearchAdminTemp = objSearchAdmin
				CheckError Err.Number, "cloning temporary SearchAdmin object."
			else
				set objSearchAdminTemp = CreateObject("Search.SearchAdmin.1")
				CheckError Err.Number, "creating temporary SearchAdmin object."
				objSearchAdminTemp.HostName = objIndexDS.Name
				CheckError Err.Number, "setting host name for temporary SearchAdmin."
			end if
			
			set objSearchServerTemp = objSearchAdminTemp.SearchServer
			CheckError Err.Number, "creating a temporary SearchServer object."
				
			' Get the list of Search catalogs
			set objSearchCatalogs = objSearchServerTemp.SearchCatalogs 
			CheckError Err.Number, "creating SearchCatalogs object."

		    objSearchCatalogs.Remove(strCatalog)
			CheckError Err.Number, "deleting" & strCatalog & "from the Search catalogs list."
		    Wscript.echo "Search catalog " & strCatalog & " deleted from " & objIndexDS.Name _
				& " Search server host."
		next
		
	    Wscript.echo strCatalog & " cleaned up."
	    Wscript.echo
		Wscript.quit
	else
	    Wscript.echo "Nothing changed."
	    Wscript.echo
		Wscript.quit
	end if
	
end sub

sub Usage
    WScript.Echo "Usage:   cscript DirmonCatalog.vbs <NotificationDirectory>"
	WScript.Echo "Example: cscript DirmonCatalog.vbs C:\TEST"
	WScript.Echo
end sub

sub CheckError (Number, Message)
	if Number <> 0 then		'NO ERROR
		Wscript.echo "Error #" & " 0x " & Hex(Number) & " - " & Err.Description
		Wscript.echo "      - received on " & Message
		Wscript.quit
	end if
end sub

'-------------------------------------------------------------------
' Begin main routine.
' Parse command-line.
' There must be one command-line argument, the directory to monitor.
'-------------------------------------------------------------------

if WScript.Arguments.Count <> 1 then
	Usage
	WScript.Quit(1)
end if

if WScript.Arguments(0) = "/?" or WScript.Arguments(0) = "-?" then
	Usage
    WScript.Quit(1)
end if

Wscript.echo "Please wait..."

'--------------------
'Initialize variables
'--------------------

public objSearchAdmin, objBuildCatalogs, objSearchServers
dim objBuildServer, objBuildCatalog
dim objStartPages, objStartPage, strDirectory, strSource, strCatalog
dim nLimit

const nNotification = 0 

strDirectory = WScript.Arguments(0)
strSource    = "DirmonSource"
strCatalog   = "DirmonCatalog"
nLimit       = 500	' 10 is the minimum

set objSearchAdmin = CreateObject("Search.SearchAdmin.1")
CheckError Err.Number, "creating SearchAdmin object."

' Use the current host
objSearchAdmin.HostName = ""

' Get the catalog builder
set objBuildServer = objSearchAdmin.BuildServer 
CheckError Err.Number, "creating BuildServer object."

' Get the list of build catalogs
set objBuildCatalogs = objBuildServer.BuildCatalogs 
CheckError Err.Number, "creating BuildCatalogs object."

'-----------------------------------
' Check whether DirmonCatalog exists
'-----------------------------------

for each objBuildCatalog in objBuildCatalogs
    if Strcomp(objBuildCatalog.Name, strCatalog) = 0 then
		'Get the Search servers list (where DirmonCatalog will be propagated)
		' to be used in CatalogDetected subroutine
		set objSearchServers = objBuildCatalog.SearchServers
		CheckError Err.Number, "creating SearchServers object."

		' Catalog definition exists, so prompt user if they want to remove it
		' and any associated catalogs
		CatalogDetected(objBuildCatalog.Name)
		Exit for
	end if
next

'---------------------------------------------------------------------
' If the user got this far either the catalog definition did not exist
' or they deleted it. So now we can add it.
'---------------------------------------------------------------------

set objBuildCatalog = objBuildCatalogs.Add(strCatalog, "")
CheckError Err.Number, "creating BuildCatalog object."

'Get the list of Search servers (where DirmonCatalog will be propagated)
set objSearchServers = objBuildCatalog.SearchServers
CheckError Err.Number, "creating SearchServers object."

'-----------------------------------------------------------------
' Set the project type, notification source, start page, protocol,
' auto propagation limit, and log success
'-----------------------------------------------------------------

objBuildCatalog.ProjectType = nNotification 
CheckError Err.Number, "setting ProjectType."

' Set notification source to DirmonCatalog
objBuildCatalog.NotificationSource = strSource ' bstrSource in Main.cpp
CheckError Err.Number, "setting NotificationSource."

set objStartPages = objBuildCatalog.StartPages
CheckError Err.Number, "setting StartPages."
	
' Set StartPage to <strDirectory> for the first incremental crawl and build
objStartPages.Add(strDirectory) 
CheckError Err.Number, "adding StartPage."

set objStartPage = objStartPages.Item(strDirectory)
CheckError Err.Number, "setting StartPage."

objStartPage.FollowDirectories = True
CheckError Err.Number, "setting file crawl (follow directories)."

' Automatically propagate DirmonCatalog
objBuildCatalog.AutoPropLimitEnabled = True
CheckError Err.Number, "setting AutoPropLimitEnabled."

objBuildCatalog.AutoPropLimit = nLimit
CheckError Err.Number, "setting AutoPropLimit."

' Enable logging successful accesses
objBuildCatalog.LogSuccess = True
CheckError Err.Number, "setting LogSuccess."

'add <local host> for propagation
objSearchServers.Add("localhost")
CheckError Err.Number, "adding <localhost> as Search server host."

Wscript.echo "Catalog DirmonCatalog configured. Now call:"
Wscript.echo "        Dirmon.exe " & strDirectory
