Attribute VB_Name = "Trigger"
Public iThreshold As Integer
Public iPollingFrequency As Integer
Public sQueueName As String
Public bContinue As Boolean

Declare Function GetPerfmonInfo Lib "permain" (ByVal lpwcsInstanceName As String) As Long

Sub Main()
    bContinue = True
    
    ' Launch Config dialogs if this is the first run of the program.
    If GetSetting("MQTrigger", "Settings", "QueueName") = "" Then
        frmConfig.Show vbModal
    End If
    

    If bContinue Then
        If GetSetting("MQTrigger", "Settings", "PollingFrequency") = "" Then
            frmPollingConfig.Show vbModal
        End If
        
        'Set the global values from settings in the registry
        InitGlobals
    
        'Load the Monitor form
        frmMonitor.Show
    End If
End Sub

Public Sub InitGlobals()
    'Called from Sub Main() and frmMonitor.cmdConfigure_Click()
    'Initialize the global variables from settings in the registry
    iThreshold = GetSetting("MQTrigger", "Settings", "Threshold")
    iPollingFrequency = Val(GetSetting("MQTrigger", "Settings", "PollingFrequency"))
    sQueueName = GetSetting("MQTrigger", "Settings", "QueueName")
End Sub

