<%@ Language=VBScript EnableSessionState=False %>
<% Option Explicit %>
<% ' Copyright Microsoft 1998-1999.  All rights reserved. %>
<!--#include file="ReportError.asp"-->
<% Dim rs, strSubject, nSubj

   strSubject = Request("text")
   If IsEmpty(strSubject) Or strSubject="" Then
      ReportError "You must specify a subject."
   End If
   
   Response.Write "DEBUG: Text = " & strSubject & "<br>"
   
   Set rs = Server.CreateObject("ADODB.Recordset")
   rs.Filter = "text='" & Replace(strSubject, "'", "''") & "'"
   rs.Open "Subject", Application("FmLib_ConnectionString"), adOpenForwardOnly, adLockOptimistic, adCmdTable
   If rs.EOF Then
      Response.Write "DEBUG: Adding new subject record.<br>"
      rs.AddNew
      rs("text") = strSubject
      rs.Update
      rs.Requery  ' Because it's a F/O cursor
   Else
      strSubject = rs("text")
   End If
   nSubj = rs("subj#")
   Response.Write "DEBUG: Subj# = " & nSubj & "<br>"
%>   
<script LANGUAGE=VBScript>
Dim theForm, aOpt, strCmp, theSel, theOpts, i, bAdded

' Remove the entry from the form (since it will appear below)
Set theForm = parent.document.frmAddTitle
theForm.Text.Value = ""

Set theSel = theForm.SubjNum
Set theOpts = theSel.options

Set aOpt = document.createElement("OPTION")
aOpt.Text = "<%= strSubject %>"
aOpt.Value = "<%= nSubj %>"

' Compare to existing options in uppercase
strCmp = UCase(aOpt.Text)
bAdded = False
i = theOpts.Length-1
If i >= 0 Then
   ' Check for add at the END of the list first
   If aOpt.Value <> theOpts(i).Value Then
      If strCmp > UCase(theOpts(i).Text) Then
         theSel.add aOpt
         theOpts(i+1).Selected = True
         bAdded = True
      Else
         ' Now search for insertion in alphabetic order
         For i = 0 To theOpts.Length - 1
            If aOpt.Value <> theOpts(i).Value Then
               If strCmp < UCase(theOpts(i).Text) Then
                  theSel.add aOpt, i
                  theOpts(i).Selected = True
                  bAdded = True
                  Exit For
               End If
            Else
               Exit For
            End If
         Next
      End If
   End If
Else
   ' This is the first item
   theSel.add aOpt
   theOpts(0).Selected = True
   bAdded = True
End If

If Not bAdded Then
   MsgBox "Subject has already been assigned to this title.",vbInformation,"Can't add subject"
Else
   Parent.window.SetDirty
End If
</script>