VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "FoundTitle"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Public Enum ReviewStatus
   statusNotReviewed = 1
   statusInProcess = 2
   statusApproved = 3
End Enum

Private m_bibNo As Long
Private m_title As String
Private m_authors As String
Private m_mediatype As String
Private m_reviewStatus As ReviewStatus
Private m_objectid As String
Private m_pubdate As String

Private Sub Class_Initialize()
   m_reviewStatus = statusNotReviewed
End Sub

Public Property Get BibNo() As Long
   BibNo = m_bibNo
End Property

Friend Property Let BibNo(RHS As Long)
   m_bibNo = RHS
End Property

Public Property Get Title() As String
   Title = m_title
End Property

Friend Property Let Title(RHS As String)
   m_title = RHS
End Property

Public Property Get Authors() As String
   Authors = m_authors
End Property

Friend Property Let Authors(RHS As String)
   m_authors = RHS
End Property

Public Property Get MediaType() As String
   MediaType = m_mediatype
End Property

Friend Property Let MediaType(RHS As String)
   Select Case RHS
   Case "AV":   m_mediatype = "Audio/Visual"
   Case "Prd":  m_mediatype = "Periodical"
   Case "Soft": m_mediatype = "Software"
   Case Else:   m_mediatype = RHS
   End Select
End Property

Public Property Get ReviewStatus() As ReviewStatus
   ReviewStatus = m_reviewStatus
End Property

Friend Property Let ReviewStatus(RHS As ReviewStatus)
   m_reviewStatus = RHS
End Property

Public Property Get ObjectID() As String
   ObjectID = m_objectid
End Property

Friend Property Let ObjectID(RHS As String)
   m_objectid = RHS
End Property

Public Property Get Published() As String
   Published = m_pubdate
End Property

Friend Property Let Published(RHS As String)
   m_pubdate = RHS
End Property

