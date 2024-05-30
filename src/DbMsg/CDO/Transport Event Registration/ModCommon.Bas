Attribute VB_Name = "modCommon"
Public Sub RemoveRegistration(currentReg As EventRegistrationInfo)
    currentReg.Source.GetBindingManager.Bindings(GetEvtGUID(currentReg.EventNum)).Remove (currentReg.Binding.ID)
End Sub

Public Function GetEvtName(Num As EventTypes) As String
    Select Case Num
        Case OnArrival:          GetEvtName = "OnArrival"
        Case OnPostEarly:          GetEvtName = "OnPostEarly"
        Case OnPost:          GetEvtName = "OnPost"
        Case OnPostFinal:          GetEvtName = "OnPostFinal"
    End Select
End Function

Public Function GetEvtGUID(Num As EventTypes) As String
    Select Case Num
        Case OnArrival:          GetEvtGUID = GUIDComCatOnArrival
        Case OnPostEarly:          GetEvtGUID = GUIDComCatOnPostEarly
        Case OnPost:          GetEvtGUID = GUIDComCatOnPost
        Case OnPostFinal:          GetEvtGUID = GUIDComCatOnPostFinal
    End Select
End Function

Public Function GetEvtSourceTypeGUID(Num As EventTypes) As String
    Select Case Num
        Case OnArrival:          GetEvtSourceTypeGUID = GUIDSMTPSourceType
        Case OnPostEarly:          GetEvtSourceTypeGUID = GUIDNNTPSourceType
        Case OnPost:          GetEvtSourceTypeGUID = GUIDNNTPSourceType
        Case OnPostFinal:          GetEvtSourceTypeGUID = GUIDNNTPSourceType
    End Select
End Function

Public Function GetEvtSSClass(Num As EventTypes) As String
    Select Case Num
        Case OnArrival:    GetEvtSSClass = SSOnArrival
        Case OnPostEarly:    GetEvtSSClass = SSOnPostEarly
        Case OnPost:    GetEvtSSClass = SSOnPost
        Case OnPostFinal:    GetEvtSSClass = SSOnPostFinal
    End Select
End Function

Public Function GetEvtInterfaceGUID(Num As EventTypes) As String
    Select Case Num
        Case OnArrival:    GetEvtInterfaceGUID = ISMTPOnArrivalGUID
        Case OnPostEarly:    GetEvtInterfaceGUID = INNTPOnPostEarlyGUID
        Case OnPost:    GetEvtInterfaceGUID = INNTPOnPostGUID
        Case OnPostFinal:    GetEvtInterfaceGUID = INNTPOnPostFinalGUID
    End Select
End Function

Public Function GetEvtService(Num As EventTypes) As String
    Select Case Num
        Case OnArrival:    GetEvtService = szSMTPService
        Case OnPostEarly:    GetEvtService = szNNTPService
        Case OnPost:    GetEvtService = szNNTPService
        Case OnPostFinal:    GetEvtService = szNNTPService
    End Select
End Function
