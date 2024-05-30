<%@ Language=VBScript EnableSessionState=False %>
<% Option Explicit %>
<% ' Copyright Microsoft 1998-1999.  All rights reserved. %>
<!--#include file="ReportError.asp"-->
<% Dim rs, strFirst, strLast, nAuth

   strLast = Request("lname")
   If IsEmpty(strLast) Or strLast="" Then
      ReportError "You must specify a last name."
   End If

   strFirst = Request("fname")
   
   Response.Write "DEBUG: LName = " & strLast & "<br>"
   Response.Write "DEBUG: FName = " & strFirst & "<br>"
   
   Set rs = Server.CreateObject("ADODB.Recordset")
   rs.Filter = "lname='" & Replace(strLast, "'", "''") & _
               "' AND fname='" & Replace(strFirst, "'", "''") & "'"
   rs.Open "Author", Application("FmLib_ConnectionString"), adOpenForwardOnly, adLockOptimistic, adCmdTable
   If rs.EOF Then
      Response.Write "DEBUG: Adding new author record.<br>"
      rs.AddNew
      rs("lname") = strLast
      rs("fname") = strFirst
      rs.Update
      rs.Requery  ' Because it's a F/O cursor
   Else
      strLast = rs("lname")
      strFirst = rs("fname")
   End If
   nAuth = rs("auth#")
   Response.Write "DEBUG: Auth# = " & nAuth & "<br>"
%>   
<script LANGUAGE=VBScript>
Dim theForm, aOpt, strCmp, theSel, theOpts, i, bAdded

' Remove the entry from the form (it moves to the selection box)
Set theForm = parent.document.frmAddTitle
theForm.lname.Value = ""
theForm.fname.Value = ""

Set theSel = theForm.AuthNum
Set theOpts = theSel.options

Set aOpt = document.createElement("OPTION")
<% If strFirst<>"" Then %>
aOpt.Text = "<%= strLast %>, <%= strFirst%>"
<% Else %>
aOpt.Text = "<%= strLast %>"
<% End If %>
aOpt.Value = "<%= nAuth %>"

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
         For i = 0 To theOpts.Length-1
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
   MsgBox "Author has already been assigned to this title.",vbInformation,"Can't add author"
Else
   Parent.window.SetDirty
End If
</script>