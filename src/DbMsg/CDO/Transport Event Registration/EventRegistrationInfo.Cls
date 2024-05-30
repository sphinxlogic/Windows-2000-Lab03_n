VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "EventRegistrationInfo"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Attribute VB_Ext_KEY = "SavedWithClassBuilder6" ,"Yes"
Attribute VB_Ext_KEY = "Top_Level" ,"Yes"
'local variable(s) to hold property value(s)
Private mvarVirtualServerNumber As Integer 'local copy
Private mvarService As String 'local copy
Private mvarEventNum As Integer 'local copy
'local variable(s) to hold property value(s)
Private mvarSource As IEventSource 'local copy
Private mvarBinding As IEventBinding 'local copy
'local variable(s) to hold property value(s)
Private mvarSinkType As Integer 'local copy
'local variable(s) to hold property value(s)
Private mvarKey As String 'local copy



Public Property Get Key() As String
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.Key
    Key = Service & ":" & VirtualServerNumber & ":" & EventNum & ":" & Binding.ID
End Property



Public Property Let SinkType(ByVal vData As Integer)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.SinkType = 5
    mvarSinkType = vData
End Property


Public Property Get SinkType() As Integer
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.SinkType
    SinkType = mvarSinkType
End Property



Public Property Set Binding(ByVal vData As IEventBinding)
'used when assigning an Object to the property, on the left side of a Set statement.
'Syntax: Set x.Binding = Form1
    Set mvarBinding = vData
End Property


Public Property Get Binding() As IEventBinding
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.Binding
    Set Binding = mvarBinding
End Property



Public Property Set Source(ByVal vData As IEventSource)
'used when assigning an Object to the property, on the left side of a Set statement.
'Syntax: Set x.Source = Form1
    Set mvarSource = vData
End Property


Public Property Get Source() As IEventSource
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.Source
    Set Source = mvarSource
End Property



Public Property Let EventNum(ByVal vData As Integer)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.EventNum = 5
    mvarEventNum = vData
End Property


Public Property Get EventNum() As Integer
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.EventNum
    EventNum = mvarEventNum
End Property



Public Property Let Service(ByVal vData As String)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.Service = 5
    mvarService = vData
End Property


Public Property Get Service() As String
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.Service
    Service = mvarService
End Property



Public Property Let VirtualServerNumber(ByVal vData As Integer)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.VirtualServerNumber = 5
    mvarVirtualServerNumber = vData
End Property


Public Property Get VirtualServerNumber() As Integer
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.VirtualServerNumber
    VirtualServerNumber = mvarVirtualServerNumber
End Property



