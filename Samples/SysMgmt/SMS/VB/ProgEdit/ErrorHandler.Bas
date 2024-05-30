Attribute VB_Name = "ErrorHandler"
' Copyright (c)1999 Microsoft Corporation, All Rights Reserved
'
' Version 1.0
'************************************************************
'ErrorHandler.bas
'
'This file contains the global CheckError function.
'************************************************************

Option Explicit

'Global Error Checking function.  Returns true and offers extended status if an error occurred.
Public Function CheckError(ErrNumber As Long, TaskDescription As String) As Boolean
    
    'Used to store existing mousepointer
    Dim PrevMousePointer As Long
    
    'Store Current MousePointer
    PrevMousePointer = Screen.MousePointer
        
    'Set default mousepointer
    Screen.MousePointer = vbDefault
    
    
    'See if an error occurred
    If ErrNumber <> 0 Then
    
        'Display error message, offer extended status
        If MsgBox("Error (" & Hex(ErrNumber) & ") occurred attempting to " & TaskDescription & vbCrLf & "Would you like extended error information?", vbYesNo, "An error has occurred") = vbYes Then
            
            'Display extended status
            Dim ErrorForm As New frmError
            ErrorForm.Show 1
                        
        End If
        
        CheckError = True
    
    Else
    
        CheckError = False
    
    End If
    
    'restore previous mousepointer
    Screen.MousePointer = PrevMousePointer
    
End Function


'In case of emergency, bail out.
Public Sub FatalError(errormessage As String)
    
    'Print error message
    MsgBox errormessage, vbCritical, "A fatal error has occurred - Shutting down"
    
    'Halt execution
    End
    
End Sub
