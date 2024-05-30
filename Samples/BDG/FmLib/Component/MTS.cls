VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "MTSEnvironment"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Private m_oc As MTxAS.ObjectContext

Private Sub Class_Initialize()
  Set m_oc = GetObjectContext
End Sub

Private Sub Class_Terminate()
  Set m_oc = Nothing
End Sub

Public Function CreateInstance(ProgID As String) As Object
  If Not m_oc Is Nothing Then
    Set CreateInstance = m_oc.CreateInstance(ProgID)
  Else
    Set CreateInstance = CreateObject(ProgID)
  End If
End Function

Public Sub SetComplete()
  If Not m_oc Is Nothing Then
    m_oc.SetComplete
  End If
End Sub

Public Sub SetAbort()
  If Not m_oc Is Nothing Then
    m_oc.SetAbort
  End If
End Sub
