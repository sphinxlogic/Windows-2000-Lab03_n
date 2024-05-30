Attribute VB_Name = "TaskObjectRoutines"
Option Explicit

Function bCreate8KRecurTask(nNumber As Integer) As Boolean
Dim objTable As Object
Dim objItem As Object
Dim i As Integer
Dim dt As Date
Dim szText As String

'Check to make sure nNumber was set
nNumber = IIf(nNumber = 0, 1, nNumber)

'Get the 8k of text
szText = szGetMuchText(8192)

'Create some simple tasks

Set objTable = objGetTable(RECURRING_TASKS)

For i = 1 To nNumber
    dt = DateAdd("d", i, Now())
    Set objItem = objTable.New
    objItem.SetProperties Text:=("OLE: bCreate8KRecurTask " & Str$(i) & " " & Now() & szText), Notes:="Notes", _
        Priority:=CLng((67 * 2 ^ 8) And (51)), _
        AccessActual:=saclOwner, _
        AlarmAmount:=CLng(10), AlarmTypeUnit:=CLng(0), BusyType:=CLng(1), BeforeEnd:=True, ring:=True, _
        AmountActualEffort:=CLng(10), TypeUnitActualEffort:=CLng(2), AmountEstimatedEffort:=CLng(5), TypeUnitEstimatedEffort:=CLng(2), _
        AmountStartWork:=CLng(2), TypeUnitStartWork:=CLng(2), _
        Billing:="Billing", Mileage:="Mileage", Role:="Role", _
        IsTaskAutoDone:=True, PercentCompleted:=CLng(55)
    objItem.SetProperties RecurringType:=trecurWeekly, WeekInterval:=CLng(1), DayOfWeekMask:=CLng(4), DayOfWeekStart:=CLng(0), _
        StartRecurringDate:=lConvertToJohnnyDate(dt), _
        StartRecurringTime:=lConvertToJohnnyTime(DateAdd("h", 1, dt)), _
        EndRecurringDate:=lConvertToJohnnyDate(DateAdd("yyyy", 1, dt)), _
        EndRecurringTime:=lConvertToJohnnyTime(DateAdd("h", 2, dt))

    Set objItem = Nothing
    DoEvents
Next i

Set objTable = Nothing

bCreate8KRecurTask = True

End Function

'****************************
'
' bCreateRecurTaskAllFields - Creates Recurring Task while setting all fields
'
'****************************
Function bCreateRecurTaskAllFields(nNumber As Integer) As Boolean
Dim objTable As Object
Dim objItem As Object
Dim i As Integer
Dim dt As Date

'Check to make sure nNumber was set
nNumber = IIf(nNumber = 0, 1, nNumber)

'Create some simple tasks

Set objTable = objGetTable(RECURRING_TASKS)

For i = 1 To nNumber
    dt = DateAdd("d", i, Now())
    Set objItem = objTable.New
    objItem.SetProperties Text:=("OLE: bCreateRecurTaskAllFields " & Str$(i) & " " & Now()), Notes:="Notes", _
        Priority:=CLng((67 * 2 ^ 8) And (51)), _
        AccessActual:=saclOwner, _
        AlarmAmount:=CLng(10), AlarmTypeUnit:=CLng(0), BusyType:=CLng(1), BeforeEnd:=True, ring:=True, _
        AmountActualEffort:=CLng(10), TypeUnitActualEffort:=CLng(2), AmountEstimatedEffort:=CLng(5), TypeUnitEstimatedEffort:=CLng(2), _
        AmountStartWork:=CLng(2), TypeUnitStartWork:=CLng(2), _
        Billing:="Billing", Mileage:="Mileage", Role:="Role", _
        IsTaskAutoDone:=True, PercentCompleted:=CLng(55)
    objItem.SetProperties RecurringType:=trecurWeekly, WeekInterval:=CLng(1), DayOfWeekMask:=CLng(4), DayOfWeekStart:=CLng(0), _
        StartRecurringDate:=lConvertToJohnnyDate(dt), _
        StartRecurringTime:=lConvertToJohnnyTime(DateAdd("h", 1, dt)), _
        EndRecurringDate:=lConvertToJohnnyDate(DateAdd("yyyy", 1, dt)), _
        EndRecurringTime:=lConvertToJohnnyTime(DateAdd("h", 2, dt))

    Set objItem = Nothing
    DoEvents
Next i

Set objTable = Nothing

bCreateRecurTaskAllFields = True

End Function

'*******************************************
'
'Creates a weekly recurring task with no end date
'
'*******************************************
Function bCreateSimpleRecurTask(nNumber As Integer) As Boolean
Dim objTable As Object
Dim objItem As Object
Dim i As Integer
Dim dt As Date

'Check to make sure nNumber was set
nNumber = IIf(nNumber = 0, 1, nNumber)

'Create some simple tasks

Set objTable = objGetTable(RECURRING_TASKS)

For i = 1 To nNumber
    Set objItem = objTable.New
    dt = DateAdd("d", i, Now())
    objItem.SetProperties Text:=("OLE: bCreateSimpleRecurTask " & Str$(i) & " " & Now()), Notes:="Notes", _
        Start:=dt, End:=(DateAdd("h", 1, dt)), _
        RecurringType:=trecurWeekly, WeekInterval:=CLng(1), DayOfWeekMask:=CLng(4), DayOfWeekStart:=CLng(0), _
        StartRecurringDate:=lConvertToJohnnyDate(dt), _
        StartRecurringTime:=lConvertToJohnnyTime(DateAdd("h", 1, dt)), _
        EndRecurringTime:=lConvertToJohnnyTime(DateAdd("h", 2, dt))

'        EndRecurringDate:=lConvertToJohnnyDate(DateAdd("yyyy", 1, dt)), _

    objItem.Flush
    Set objItem = Nothing
    DoEvents
Next i

bCreateSimpleRecurTask = True

End Function

'******************************
'
' Calls all scripts in this module
'
'******************************
Function CallAllTaskScripts()

Set gobjBase = objSetBaseObject

If gobjBase.LoggedOn = False Then
    gobjBase.Logon profileName:="ryanw24"
End If

Set gobjSched = gobjBase.ScheduleSelected
gobjSched.Activate

'Create a simple task (desc. and notes)
'    bCreateSimpleTask (1)

'Create a task with all fields filled (except contact and role)
'    bCreateTaskAllFields (1)
    
'Create an 8K Task
'    bCreate8KTask (1)

'Create simple recurring task
    bCreateSimpleRecurTask (1)

'Create recurring task with all fields filled
    bCreateRecurTaskAllFields (1)

'Create an 8K task
    bCreate8KRecurTask (1)

Set gobjSched = Nothing
Set gobjBase = Nothing

End Function




Function bCreateSimpleTask(nNumber As Integer) As Boolean
Dim objTable As Object
Dim objItem As Object
Dim i As Integer

'Check to make sure nNumber was set
nNumber = IIf(nNumber = 0, 1, nNumber)

'Create some simple tasks

Set objTable = objGetTable(SINGLE_TASKS)

For i = 1 To nNumber
    Set objItem = objTable.New
    objItem.SetProperties Text:=("OLE: bCreateSimpleTask " & Str$(i) & " " & Now()), Notes:="Notes"
    Set objItem = Nothing
    DoEvents
Next i

bCreateSimpleTask = True

End Function


Function bCreate8KTask(nNumber As Integer) As Boolean
Dim objTable As Object
Dim objItem As Object
Dim i As Integer
Dim szText As String

'Check to make sure nNumber was set
nNumber = IIf(nNumber = 0, 1, nNumber)

'Get the 8k of text
szText = szGetMuchText(8192)

'Create some simple tasks

Set objTable = objGetTable(SINGLE_TASKS)

For i = 1 To nNumber
    Set objItem = objTable.New
    objItem.SetProperties Text:=("OLE: bCreate8KTask " & Str$(i) & " " & Now() & szText), Notes:="Notes", _
        Priority:=CLng((67 * 2 ^ 8) And (51)), _
        AlarmAmount:=CLng(10), AlarmTypeUnit:=CLng(0), BusyType:=CLng(1), BeforeEnd:=True, ring:=True, _
        Start:=(DateAdd("d", i, Now())), End:=(DateAdd("d", i + 1, Now())), _
        AmountActualEffort:=CLng(10), TypeUnitActualEffort:=CLng(2), _
        AmountEstimatedEffort:=CLng(5), TypeUnitEstimatedEffort:=CLng(2), _
        AmountStartWork:=CLng(2), TypeUnitStartWork:=CLng(2), _
        Billing:="Billing", Mileage:="Mileage", Role:="Role", _
        IsTaskAutoDone:=True, PercentCompleted:=CLng(55)

    Set objItem = Nothing
    DoEvents
Next i

Set objTable = Nothing

bCreate8KTask = True

End Function

Function bCreateTaskAllFields(nNumber As Integer) As Boolean
Dim objTable As Object
Dim objItem As Object
Dim i As Integer

'Check to make sure nNumber was set
nNumber = IIf(nNumber = 0, 1, nNumber)

'Create some simple tasks

Set objTable = objGetTable(SINGLE_TASKS)

For i = 1 To nNumber
    Set objItem = objTable.New
    objItem.SetProperties Text:=("OLE: bCreateTaskAllFields " & Now()), Notes:="Notes", _
        Priority:=CLng((67 * 2 ^ 8) And (51)), _
        AccessActual:=saclOwner, _
        AlarmAmount:=CLng(10), AlarmTypeUnit:=CLng(0), BusyType:=CLng(1), BeforeEnd:=True, ring:=True, _
        Start:=DateAdd("d", i, Now()), End:=DateAdd("d", i + 1, Now()), _
        AmountActualEffort:=CLng(10), TypeUnitActualEffort:=CLng(2), _
        AmountEstimatedEffort:=CLng(5), TypeUnitEstimatedEffort:=CLng(2), _
        AmountStartWork:=CLng(2), TypeUnitStartWork:=CLng(2), _
        Billing:="Billing", Mileage:="Mileage", Role:="Role", _
        IsTaskAutoDone:=True, PercentCompleted:=CLng(55)

    Set objItem = Nothing
    DoEvents
Next i

Set objTable = Nothing

bCreateTaskAllFields = True

End Function

Function UETest() As Boolean
Dim objTable As Object
Dim objItem As Object

'Create a Sched+ object
    Set gobjBase = CreateObject("Schedule+.Application")

'Find out if we're logged on, if not use a profile
    If gobjBase.LoggedOn = False Then
        gobjBase.Logon profileName:="ryanw24"
    End If

'Get the handle for the selected schedule and activate it's window
    Set gobjSched = gobjBase.ScheduleSelected
    gobjSched.Activate

'Create a simple task

    'Get the tasks table
    Set objTable = gobjSched.SingleTasks

    'Create a new item
    Set objItem = objTable.New
    objItem.SetProperties Text:=("OLE: bCreateSimpleTask " & Now()), Notes:="Notes"
    Set objItem = Nothing

'Release Objects and log off
    Set objTable = Nothing
    Set gobjSched = Nothing
    gobjBase.Logoff
    Set gobjBase = Nothing
End Function


