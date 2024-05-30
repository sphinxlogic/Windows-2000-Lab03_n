<%
   'Copyright(c) Microsoft corporation 1998-99. All rights reserved
   'Methods to create and check an anonymous Active Messaging Session

Const REG_WEBPARAMS = "HKEY_LOCAL_MACHINE\System\CurrentControlSet\Services\MSExchangeWeb\Parameters"


Public Sub ReportError(strError,bFlag)
  If bFlag = True Then
     If Err.Number <> 0 Then 
        Response.Write "<" & "script Language=vbScript>Msgbox """ & _
                       Replace(strError,vbCrLf,"") & """ & vbCrLf & ""ErrNumber: " & Err.Number & _
                       """ & vbCrLf & ""ErrorDesciption: " & Err.Description & """, vbCritical, ""Error""" & vbCrLf & "<" & "/script>"
        Response.End
     End If
  Else
        Response.Write "<" & "Script Language=vbScript>MsgBox """ & _
                       Replace(strError,vbCrLf,"") & """, vbCritical, ""DebugWindow""" & vbCrLf & "<" & "/script>"

  End If
         
End Sub

Public Function GetPublicFolderID(objSession,objRenderApp)
  Dim  objStore,lMask
  Dim  EnterpriseName,SiteName,ServerName,ProfileInfo
  
  Set GetPublicFolderID = Nothing
  Set objSession = Server.CreateObject("MAPI.Session")
  
  If IsObject(objSession) Then
     Call GetAnonConfig (EnterpriseName,SiteName,ServerName,objRenderApp)
  
     ProfileInfo = "/o=" & EnterpriseName & "/ou=" & SiteName & _
                   "/cn=Configuration/cn=Servers/cn=" & _
                   ServerName & vbLF & "anon" & vbLF & "anon"
  
     Call objSession.Logon("","",False,True,0,True,ProfileInfo)
     
     If Err.Number=0 Then 
        For Each objStore In objSession.InfoStores
            lMask = objStore.Fields.Item(&H340D0003) 'PR_STORE_SUPPORT_MASK
            If lMask And &H00004000 Then 'Store public Folders
               GetPublicFolderID = objStore.ID
               Exit For
            End If
        Next
     Else
        ReportError "Could Not Log On",True 
     End If
  Else
     ReportError "Could not Instantiate MAPI Session",True
  End If
End Function


Sub GetAnonConfig(ByRef EnterpriseName, ByRef SiteName, ByRef ServerName,ByRef objRenderApp)
    Set objRenderApp = Server.CreateObject("AMHTML.Application")
    If Not IsObject(objRenderApp) Then
        ReportError "Invalid Rendering Application Object ",True
    Else
        '1 means load configuration from the registry
        objRenderApp.LoadConfiguration 1,REG_WEBPARAMS
        '2 means load configuration from the Exchange directory
        objRenderApp.LoadConfiguration 2, ""
        If Err.Number <> 0 Then 
          ReportError "Couldn't load configuration",True
        Else
          EnterpriseName = objRenderApp.ConfigParameter("Enterprise")
          SiteName = objRenderApp.ConfigParameter("Site")
          ServerName = objRenderApp.ConfigParameter("Server")
        End If
    End If   
End Sub
   
Function GetPublishedFolderID(PublicFolderName)
   Dim objAnonSession,storeID,Count,objFolder
   Dim amFolders,iFolderCount
   Dim objRenderApp

   Set objAnonSession = Nothing
   Set objRenderApp = Nothing
   storeID = GetPublicFolderID(objAnonSession,objRenderApp)
   If Not objAnonSession Is Nothing Then
      amFolders = objRenderApp.ConfigParameter("Published Public Folders")
      If Not IsEmpty(amFolders) Then      
         Response.Write "<div ID=FolderReport STYLE=""display:none""><table border=0><tr><th ALIGN=LEFT COLSPAN=2>Found Folders:</th></tr>"
         For iFolderCount = LBound(amFolders) To UBound(amFolders)
            Set objFolder = objAnonSession.GetFolder(amFolders(iFolderCount),storeID)
            If Not objFolder Is Nothing Then
               Response.Write "<tr><td>" & objFolder.Name & "</td><td><small>" & amFolders(iFolderCount) & "</td></tr>"
               '=== TWO WAYS TO DO THIS: Remember to compare strings without case
               'If LCase(objFolder.Name) = LCase(PublicFolderName) Then
               If StrComp(objFolder.Name,PublicFolderName,vbTextCompare) = 0 Then
                  GetPublishedFolderID = amFolders(iFolderCount)
                  Exit For
               End If
            End If
         Next
         Response.Write "</table></div>"
      Else
         ReportError "No public folders have been published for anonymous access. Check your Exchange Server settings.", False
      End If
      objAnonSession.Logoff
      Set objAnonSession = Nothing
      Set objRenderApp = Nothing
   End If

End Function  
       
%>



