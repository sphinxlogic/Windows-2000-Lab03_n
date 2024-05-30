Attribute VB_Name = "XMSConf"
'****************************************************************************
'
'  Module:     VBCARD.EXE
'  File:       XMSConf.frm
'  Content:    Implementation of the Conference control globals
'
'  Copyright (c) Microsoft Corporation 1995-1997
'
' THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
' ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
' THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
' PARTICULAR PURPOSE.
'****************************************************************************

Option Explicit

Public Const IIDIConfDataExchangeX As String = _
    "{be5b8707-92e1-11cf-8796-444553540000}"
Public Const IIDIConfFileExchangeX As String = _
    "{be5b8708-92e1-11cf-8796-444553540000}"
Public Const IIDIConfAppSharingX As String = _
    "{be5b8709-92e1-11cf-8796-444553540000}"
Public Const IIDIConfAppControlX As String = _
    "{be5b870a-92e1-11cf-8796-444553540000}"

Public Const CNF_SHR_UNKNOWN As Long = 0
Public Const CNF_SHR_SHARED As Long = 1
Public Const CNF_SHR_UNSHARED As Long = 2
        
Public Const CNF_FILE_IDLE As Long = 0
Public Const CNF_FILE_INITIALIZING As Long = 1
Public Const CNF_FILE_PROGRESS As Long = 2
Public Const CNF_FILE_COMPLETE As Long = 3

Public Const CNF_MEMB_ADDED As Long = 0
Public Const CNF_MEMB_REMOVED As Long = 1
Public Const CNF_MEMB_UPDATED As Long = 2

Public Const CNF_STATE_IDLE As Long = 0
Public Const CNF_STATE_INIT As Long = 1
Public Const CNF_STATE_START As Long = 2
Public Const CNF_STATE_STOP As Long = 3
Public Const CNF_STATE_OFFERED As Long = 4

Public Const CNF_CAPS_NONE As Long = 0
Public Const CNF_CAPS_DATA As Long = 1
Public Const CNF_CAPS_AUDIO As Long = 2
Public Const CNF_CAPS_VIDEO As Long = 4

Public Const CNF_USER_UNKNOWN As Long = 0
Public Const CNF_USER_IP As Long = 1
Public Const CNF_USER_MACHINENAME As Long = 2
Public Const CNF_USER_PSTN As Long = 3

Public Const CNFF_SDOPT_NONE As Long = 0

Public Const CNFF_SFOPT_NONE As Long = 0
Public Const CNFF_SFOPT_NOUI As Long = 2
Public Const CNFF_SFOPT_NOCOMPRESS As Long = 4

Public DataChannel As IConfDataExchangeX
Public FileChannel As IConfFileExchangeX

Public Sub InitChannels()
    Set DataChannel = Nothing
    Set FileChannel = Nothing
End Sub

Public Sub OpenChannels(Conf As IConferenceX)
    Dim Channels As IConfChannels
    Dim Channel As IConfChannelX
    
    On Error Resume Next
    Set Channels = Conf.Channels
    If Not (Channels Is Nothing) Then
        For Each Channel In Channels
            Dim Interface As String
            
            Interface = Channel.Interface
            If Interface = IIDIConfDataExchangeX Then
                Set DataChannel = Channel.object
                DataChannel.Advise
            ElseIf Interface = IIDIConfFileExchangeX Then
                Set FileChannel = Channel.object
                FileChannel.Advise
            End If
        Next
    End If
End Sub

Public Sub CloseChannels()
    If Not (DataChannel Is Nothing) Then
        DataChannel.Unadvise
        Set DataChannel = Nothing
    End If
    If Not (FileChannel Is Nothing) Then
        FileChannel.Unadvise
        Set FileChannel = Nothing
    End If
End Sub

Public Function ConfCapsToString(lCaps As Long) As String
    Select Case lCaps
        Case CNF_CAPS_NONE
            ConfCapsToString = "None."
        Case CNF_CAPS_DATA
            ConfCapsToString = "Data Only."
        Case CNF_CAPS_AUDIO
            ConfCapsToString = "Voice Only."
        Case CNF_CAPS_AUDIO + CNF_CAPS_DATA
            ConfCapsToString = "Voice and Data."
    End Select
End Function

