Attribute VB_Name = "CoreObjectRoutines"
Option Explicit

Public gobjBase As Object
Public gobjSched As Object

Global Const SINGLE_APPOINTMENTS = "SingleAppointments"
Global Const RECURRING_APPOINTMENTS = "RecurringAppointments"
Global Const SINGLE_EVENTS = "SingleEvents"
Global Const RECURRING_EVENTS = "RecurringEvents"
Global Const SINGLE_TASKS = "SingleTasks"
Global Const RECURRING_TASKS = "RecurringTasks"
Global Const CONTACTS = "Contacts"
Global Const PROJECTS = "Projects"
Global Const ATTENDEES = "Attendees"
Global Const ACCESS_CONTROLS = "AccessControls"

'Sacls for setting AccessActual and AccessEffective and AccessDefault
Global Const saclNone = (0)
Global Const saclReadMinimal = (1)
Global Const saclRead = (2)
Global Const saclCreate = (3)
Global Const saclWrite = (4)
Global Const saclOwner = (5)
Global Const saclMax = (6)

'RecurringType for recurring tasks and appointments
'/* Pattern = Every X days */
Global Const trecurDaily = (64)
'/* Pattern = Every X weeks on DayOfWeekMask days */
Global Const trecurWeekly = (48)
'/* Pattern = Day X of every Y months */
Global Const trecurMonthly1 = (12)
'/* Pattern = {1st | 2nd | 3rd | 4th | Last} Day of Week of every Y months */
Global Const trecurMonthly2 = (56)
'/* Pattern = On Month Day */
Global Const trecurYearly1 = (7)
'/* Pattern = {1st | 2nd | 3rd | 4th | Last} Day of Week of Month */
Global Const trecurYearly2 = (51)

Function objSetBaseObject() As Object

    Set objSetBaseObject = CreateObject("Schedule+.Application")

End Function

'*****************************************
'
' objGetTable - returns obj for Task
'
'   szTable - Constant passed in for table name (see General Declaractions
'
'*****************************************
Function objGetTable(szTable As String) As Object

Select Case szTable
    Case SINGLE_APPOINTMENTS
        Set objGetTable = gobjSched.SingleAppointments
    Case RECURRING_APPOINTMENTS
        Set objGetTable = gobjSched.RecurringAppointments
    Case SINGLE_EVENTS
        Set objGetTable = gobjSched.SingleEvents
    Case RECURRING_EVENTS
        Set objGetTable = gobjSched.RecurringEvents
    Case SINGLE_TASKS
        Set objGetTable = gobjSched.SingleTasks
    Case RECURRING_TASKS
        Set objGetTable = gobjSched.RecurringTasks
    Case CONTACTS
        Set objGetTable = gobjSched.CONTACTS
    Case PROJECTS
        Set objGetTable = gobjSched.PROJECTS
    Case ATTENDEES
        Set objGetTable = gobjSched.ATTENDEES
    Case ACCESS_CONTROLS
        Set objGetTable = gobjSched.AccessControls
    Case Else
        Debug.Print "objGetTaskTable: invalid table name passed"
End Select

End Function

'****************************************************************************************************
' szGetMuchText --   Generate a specified amount of text
'
'   STATE:  Not state dependent
'
'   INPUTS:
'       nCharacters - The number of characters to be generated from 1 to 65,500(?)
'       szReturnText - Variable the generated characters will be stored in
'
'****************************************************************************************************
Function szGetMuchText(nCharacters As Integer) As String

Dim a As String             ' repeated string
Dim a_len As Integer        ' length of "a" (short integer)
Dim GMTLoop As Long         ' number of times to loop
Dim GMTRemain As Long       ' messy remainder of division
Dim i As Long               ' counter
Dim szReturnText As String

' Initialize variables
    szReturnText = ""
    a = "This is " + Str$(nCharacters) + " characters of text.*"
    a_len = Len(a)

' Generate characters
    If a_len >= nCharacters Then
        szReturnText = Left$(a, nCharacters)
    Else
        GMTLoop = Int(nCharacters / a_len)
        GMTRemain = nCharacters Mod a_len
        For i = 1 To GMTLoop
            szReturnText = szReturnText + a
        Next
        szReturnText = szReturnText + Left$(a, GMTRemain)
    End If

szGetMuchText = szReturnText

End Function 'nGetMuchText


'****************************************************************************************************
' szGetIntlText --   Generate a specified amount of international text.
'
'   STATE:  Not dependent on Boomerang state
'
'   INPUTS:
'       nCharacters - The number of international characters to be generated from 1 to 65,500(?)
'       szReturnText - Variable the generated characters will be stored in
'
'   WRITTEN BY: ryanw
'
'****************************************************************************************************
Function szGetIntlText(nCharacters As Integer) As String

Dim a As String             ' repeated string
Dim a_len As Integer        ' length of "a" (short integer)
Dim GITLoop As Long         ' number of times to loop
Dim GITRemain As Long       ' messy remainder of division
Dim i As Long               ' counter

' Initialize variables
    szReturnText = ""
    a$ = ""

' Generate international string where chr() values are international characters
    For i = 128 To 168
        a$ = a$ + Chr$(i)
    Next
    For i = 173 To 175
        a$ = a$ + Chr$(i)
    Next

    ' Add to string the desired length of the string
    a$ = a$ + "-=<" + Str$(nCharacters) + " characters>=-"

    a_len = Len(a)

' Generate characters
    If a_len >= nCharacters Then
        szReturnText$ = Left$(a$, nCharacters)
    Else
        GITLoop = Int(nCharacters / a_len)
        GITRemain = nCharacters Mod a_len
        For i = 1 To GITLoop
            szReturnText$ = szReturnText$ + a$
        Next
        szReturnText$ = szReturnText + Left$(a$, GITRemain)
    End If

szGetIntlText = szReturnText

End Function 'nGetIntlText


