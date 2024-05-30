<%

Const sGUID = "{2903020000000000C000000000000046}"

' Custom script code for selecting library item type image
Function MediaImage(ByVal ShortMedia)
   ' Response.Write "SHORTMEDIA: " & shortmedia & "<br>"
   Select Case ShortMedia
   Case "AV","Audio/Visual": MediaImage = "AudioVisual.gif"
   Case "Prd","Periodicals": MediaImage = "Periodicals.gif"
   Case "Soft","Software":   MediaImage = "Software.gif"
   Case Else:                MediaImage = "Book.gif"
   End Select
End Function

Sub SetApproverInfo(sApprovalRequired,sApproverEmail)
   'Response.Write "Setting Approver Info...<br>"
   'Response.Write "APPROVALREQUIRED: " & sApprovalRequired & _
   '               "<br>APPROVEREMAIL: " & sApproverEmail & _
   '               "<BR>"

   If sApprovalRequired = "True" Then
      SetInitialValue sGUID & "ApprovalRequired", vbLong, False, 1, 0, 1, objOneMsg
      SetInitialValue sGUID & "ApproverEmail", vbString, False, sApproverEmail, 0, 1, objOneMsg
      SetInitialValue sGUID & "isApproved", vbLong, False, 0, 0, 1, objOneMsg
   Else
      SetInitialValue sGUID & "ApprovalRequired", vbLong, False, 0, 0, 1, objOneMsg
      SetInitialValue sGUID & "isApproved", vbLong, False, 1, 0, 1, objOneMsg
   End If
End Sub

Sub SetTitleInfo(nBibNo,sItemTitle,sAuthors,sMediaType)
   ' Response.Write "Setting Title Info...<br>"
   ' Response.Write "BIBNO: " & nBibNo & "<br>ITEM TITLE: " & sItemTitle & _
   '               "<br>AUTHNAME: " & sAuthors & "<br>MEDIA TYPE: " & sMediaType & _
   '               "<BR>"

   If sAuthors = "" Then sAuthors = "Not Mentioned"

   Select Case sMediaType
   Case "AV":   sMediaType = "Audio/Visual"
   Case "Soft": sMediaType = "Software"
   Case "Prd":  sMediaType = "Periodicals"
   Case "Ref":  sMediaType = "Reference"
   End Select

   objOneMsg.Subject = "Critique of: " & sItemTitle

   SetInitialValue sGUID & "Item Title", vbString, False, sItemTitle, 0, 1, objOneMsg
   SetInitialValue sGUID & "bibNo", vbLong, False, nBibNo, 0, 1, objOneMsg
   SetInitialValue sGUID & "AuthName", vbString, False, sAuthors, 0, 1, objOneMsg
   SetInitialValue sGUID & "Media", vbString, False, sMediaType, 0, 1, objOneMsg
   SetInitialValue sGUID & "LongAuthor", vbString, False, "by " & sAuthors, 0, 1, objOneMsg

   sUserName = objOMSession.CurrentUser.Name
   SetInitialValue sGUID & "OldUserName", vbString, False, sUserName, 0, 1, objOneMsg

   sLongMedia = sMediaType & " reviewed by " & sUserName & " on " & Date & " " & Time
   SetInitialValue sGUID & "LongMedia", vbString, False, sLongMedia, 0, 1, objOneMsg
End Sub

Sub SetLitCritFieldsFromURL()
   sBibNo = Request.QueryString("BN")
   If sBibNo <> "" Then
      Call SetTitleInfo(CLng(sBibNo), Request.QueryString("IT"), _
                        Request.QueryString("AN"), Request.QueryString("MT"))
      firstPage = "Page_3.asp"	' Display HALF-READ form page
   End If
   Call SetApproverInfo(Request.QueryString("AR"), Request.QueryString("AE"))
End Sub

%>