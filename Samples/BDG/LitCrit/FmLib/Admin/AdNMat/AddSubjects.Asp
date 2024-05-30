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
Dim theForm, theSel, aOpt, i, bFound

' Remove the entry from the form (since it will appear below)
Set theForm = parent.document.frmAddTitle
theForm.Text.Value = ""

Set theSel = theForm.SubjNum
Set theOpts = theSel.options

Set aOpt = parent.document.createElement("OPTION")
aOpt.Text = "<%= strSubject %>"
aOpt.Value = "<%= nSubj %>"

i = BSearch(theSel.options,aOpt.text,True,bFound)

' Only insert if not found in the list
If Not bFound Then
   theSel.Add aOpt, i
   Parent.window.SetDirty
Else
   MsgBox "Subject has already been assigned to this title.",vbInformation,"Can't add subject"
End If
</script>