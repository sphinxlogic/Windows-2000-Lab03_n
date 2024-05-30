VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "Filesink"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
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

Private CrsServer As New CReplicationServer
Private CrsEvent As SiteServerEvent
Private FileNumber As Integer

Implements SiteServerEventSink

Private Sub SiteServerEventSink_Clear()

    On Error Resume Next
    
    ' Normally this routine would clear out the event sink by erasing the old events.
    ' CReplicationServer.ClearEvents can be called with the name of this event sink to
    ' invoke this routine.
    '
    ' Output string to indicate this routine was invoked
    Print #FileNumber, "SiteServerEventSink_Clear!"
    
End Sub

Private Sub SiteServerEventSink_Initialize(ByVal szName As String)

    On Error Resume Next
    
    Dim hr As Long              ' Win32 APIs will return an HResult
    Dim dwType As Long          ' Used by Registry APIs to identify type of a registry value
    Dim dwSize As Long          ' Used by Registry APIs to identify size of a registry value
    Dim hKey As Long            ' Used by Registry APIs as a handle to a registry key
    Dim LogFileName As String   ' Filename where events will be logged
    
    FileNumber = FreeFile()     ' Get the next free file number
    
    ' We expect the event sink was configured with CRS and a sub-key exists as \CRS\EventLogging\<EventSink_Name>
    hr = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\Microsoft\CRS\EventLogging\" & szName, 0, KEY_QUERY_VALUE, hKey)
    If hr <> 0 Then
    End If
    
    ' Set dwSize to 0 the first time to determine how big a string is needed
    dwSize = 0
    hr = RegQueryValueEx(hKey, "Filename", 0, dwType, LogFileName, dwSize)
    If hr <> 0 Then
    End If
    
    LogFileName = Space(dwSize) ' Pre-allocate space in filename string
    
    ' Query the filename a second time with pre-allocated string to retrieve filename
    hr = RegQueryValueEx(hKey, "Filename", 0, dwType, LogFileName, dwSize)
    If hr <> 0 Then
        ' If filename registry key was not found, make up a filename
        LogFileName = "C:\temp\filesink.log"
        Open LogFileName For Output As #FileNumber
        Print #FileNumber, "ERROR: RegQueryValueEx() hr = " & hr & " szName = " & szName
    Else
        Open LogFileName For Output As #FileNumber
    End If

    ' Output string to indicate this routine was invoked
    Print #FileNumber, "SiteServerEventSink_Initialize!"
    ' Output name of event sink and name of the logfile
    Print #FileNumber, "      Name: "; szName
    Print #FileNumber, "      Log FileName: "; LogFileName
    
    ' The registry key is no longer needed
    hr = RegCloseKey(hKey)
    If hr <> 0 Then
    End If

End Sub

Private Sub SiteServerEventSink_OnEvent(pvEvent As Variant)

    On Error Resume Next
    
    Dim NumProperties As Variant    ' # of properties in the event object
    Dim EventCode As Variant        ' EventCode for this event
    Dim Description, Severity, Category As Variant      ' Description, Severity, & Category for this event
    Dim EventProperty, EventPropertyValue As Variant    ' Name of each property and its value

    Set CrsEvent = pvEvent
    
    NumProperties = CrsEvent.NumProperties
    If Err.Number <> 0 Then
    End If
    
    ' Output string to indicate this routine was invoked
    Print #FileNumber, "SiteServerEventSink_OnEvent! ("; NumProperties; " total properties)"
    
    EventCode = CrsEvent.Read("EventCode")
    If Err.Number <> 0 Then
    End If
    
    ' CReplicationServer.TranslateEventCode will return the Description, Severity, & Category
    ' associated with this event
    CrsServer.TranslateEventCode EventCode, Description, Severity, Category
    If Err.Number <> 0 Then
    End If
    
    ' Output Description, Severity, and Category
    Print #FileNumber, "      Description: "; Description
    Print #FileNumber, "      Severity: "; Severity
    Print #FileNumber, "      Category: "; Category
    For Each EventProperty In CrsEvent.PropertyNames
        EventPropertyValue = CrsEvent.Read(EventProperty)
        If Err.Number <> 0 Then
        End If
        ' Output PropertyName: PropertyValue for each event property
        ' Left-align property name in a 20 column field
        Print #FileNumber, "            "; Format(EventProperty, "!@@@@@@@@@@@@@@@@@@@@"); ": "; EventPropertyValue '; " ("; TypeName(EventPropertyValue); ")"
    Next

End Sub

Private Sub SiteServerEventSink_Shutdown()
    
    On Error Resume Next
    ' Output string to indicate this routine was invoked
    Print #FileNumber, "SiteServerEventSink_Shutdown!"
    Close #FileNumber

End Sub


