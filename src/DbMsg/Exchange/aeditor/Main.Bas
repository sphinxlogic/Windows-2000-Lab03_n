Attribute VB_Name = "MainModule"
Option Explicit

'***********************************************************************
'  Copyright (c) by Microsoft 1998
'***********************************************************************
'
'                  MAIN MODULE
'
'  Overview: This is the entry and exit point for the program. From here
'  it goes to the UI code (AEditorUI).
'
'  The main UI form calls terminateapp during a QueryUnload Event.
'-----------------------------------------------------------------------

'Public Classes used in all forms and modules.

Public AEClass As Object
Public AgentMap As Object


'-----------------------------------------------------------
'                       MAIN
'
'   THIS IS THE ENTRY POINT FOR THE APPLICATION
'-----------------------------------------------------------
Sub Main()

On Error Resume Next

Dim b_OK As Boolean     'Boolean Success

'Initialize Classes
Set AgentMap = New AgentMapClass
Set AEClass = New AEditorClass

'Logon and get create AgentMap object
b_OK = bEstablishConnection()
If b_OK Then
   AEditorUI.Show
End If

End Sub

'--------------------------------------------------------------
'                         TERMINATE APP
'
'       THIS IS THE TERMINATION ROUTINE FOR THE APPLICATION
'--------------------------------------------------------------
Sub TerminateApp()

   Dim item As Object
     For Each item In Forms
        If item.name <> "AEditorUI" Then
           Unload item
        End If
     Next

   If Not AgentMap Is Nothing Then
      If AgentMap.IsLoggedOn Then
         AgentMap.LogOff
      End If
   End If
   
   Set AEClass = Nothing
   Set AgentMap = Nothing
   
   Unload AEditorUI
   
End Sub

