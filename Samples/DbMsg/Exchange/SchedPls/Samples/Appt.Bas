Attribute VB_Name = "ApptObjectRoutines"
Option Explicit

'******************************
'
' Calls all scripts in this module
'
'******************************
Function CallAllApptScripts()

Set gobjBase = objSetBaseObject

If gobjBase.LoggedOn = False Then
    gobjBase.Logon profileName:="ryanw24"
End If

Set gobjSched = gobjBase.ScheduleSelected
gobjSched.Activate

'Create a simple task (desc. and notes)
'    bCreateSimpleTask (1)

'Create a task with all fields filled (except contact and role)
 '   bCreateTaskAllFields (1)
    
'Create an 8K Task
    bCreate8KAppt (1000)

'Create simple recurring task
'    bCreateSimpleRecurTask (1)
'Create recurring task with all fields filled
'Create an 8K task


Set gobjSched = Nothing
Set gobjBase = Nothing

End Function
Function bCreate8KAppt(nNumber As Integer) As Boolean
Dim objTable As Object
Dim objItem As Object
Dim i As Integer
Dim szText As String

    
'Check to make sure nNumber was set
nNumber = IIf(nNumber = 0, 1, nNumber)

'Get the 8k of text
szText = szGetMuchText(8192)

'Create some simple tasks

Set objTable = objGetTable(SINGLE_APPOINTMENTS)

For i = 1 To nNumber
    Set objItem = objTable.New
    objItem.SetProperties Text:=("OLE: bCreate8KAppt " & Str$(i) & " " & Now() & szText), Notes:="Notes", _
        BusyType:=CLng(1), _
        Start:=(DateAdd("h", i, Now())), End:=(DateAdd("h", i + 1, Now()))
    Set objItem = Nothing
Next i

Set objTable = Nothing

bCreate8KAppt = True

End Function


