VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "Critique"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

Private Const APPNAME = "LitCrit"
Private Const SECTION = "Enhanced"
Private Const KEY = "ShowDialog"

Public Sub ChooseTitle(ByRef BibNo As Variant, ByRef Title As Variant, _
                       ByRef Authors As Variant, ByRef MediaType As Variant, _
                       ByRef ObjectID As Variant, ByVal Logon As String, _
                       ByVal ServerName As String)
   
   Dim Alias As String
   
   If GetApplicationSetting("CritiqueEnabled", ServerName) = "1" Then
      If LibraryItemDialog() = True Then
      
         ' Parse alias name from LDAP string, if passed
         If InStr(Logon, "/cn=") Then
            Alias = Mid(Logon, InStrRev(Logon, "=") + 1)
         Else
            Alias = Logon
         End If
         
         ' Configure the form
         frmChooseTitle.Server = ServerName
         frmChooseTitle.Logon = Alias
         frmChooseTitle.Title = Title
         frmChooseTitle.Authors = Authors
         frmChooseTitle.MediaType = MediaType
         
         ' Call the form
         frmChooseTitle.Show vbModal
         
         ' Copy the return values to the output params
         BibNo = frmChooseTitle.BibNo
         Title = frmChooseTitle.Title
         Authors = frmChooseTitle.Authors
         MediaType = frmChooseTitle.MediaType
         ObjectID = frmChooseTitle.ObjectID
      End If
   End If
End Sub

Public Function GetApplicationSetting(ByVal SettingName As String, ByVal ServerName As String) As String
   Dim RDS As New RDS.DataControl
   
   On Error GoTo ErrHandler
   
   RDS.ExecuteOptions = 1 ' adcExecSync
   RDS.Handler = "MSDFMAP.Handler,FmLibMap.ini"
   RDS.Server = "http://" & ServerName
   RDS.Connect = "Data Source=FmLib"
   RDS.SQL = "GetAppSetting(" & SettingName & ")"
   RDS.Refresh
   
   If Not RDS.Recordset Is Nothing Then
      If Not RDS.Recordset.EOF Then
         GetApplicationSetting = CStr(RDS.Recordset(0))
      End If
      RDS.Recordset.Close
   End If
   
   Set RDS = Nothing
   Exit Function
   
ErrHandler:
   MsgBox "Failed to get application setting (" & SettingName & ")." & vbCrLf & _
          "[" & Hex(Err.Number) & "] " & Err.Description, vbCritical, Err.Source
End Function

Private Function LibraryItemDialog() As Boolean
   Dim setting As String
   
   ' Show ChooseSetting form if default value is empty
   setting = GetSetting(APPNAME, SECTION, KEY)
   If setting = "" Then
      frmChooseSetting.Show vbModal
      'If user selects the check box then save the setting in registry
      If frmChooseSetting.isChecked Then
         SaveSetting APPNAME, SECTION, KEY, frmChooseSetting.Response
      End If
   Else
      frmChooseSetting.Response = setting
   End If
   
   'Returning the boolean value whether or not user selected the check box
   LibraryItemDialog = CBool(frmChooseSetting.Response)

End Function

