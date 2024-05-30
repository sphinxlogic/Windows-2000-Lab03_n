<%@ Language=VBScript EnableSessionState=False %>
<% Option Explicit %>
<% ' Copyright Microsoft 1998-1999.  All rights reserved. %>
<!--#include file="ReportError.asp"-->
<!--#include file="BSearch.asp"-->
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
Dim theForm, theSel, aOpt, i, bFound

' Remove the entry from the form (it moves to the selection box)
Set theForm = parent.document.frmAddTitle
theForm.lname.Value = ""
theForm.fname.Value = ""

Set theSel = theForm.AuthNum
Set aOpt = parent.document.createElement("OPTION")

<% If strFirst<>"" Then %>
aOpt.Text = "<%= strLast %>, <%= strFirst%>"
<% Else %>
aOpt.Text = "<%= strLast %>"
<% End If %>
aOpt.Value = "<%= nAuth %>"
aOpt.Selected = True

i = BSearch(theSel.options,aOpt.text,True,bFound)

' Only insert if not found in the list
If Not bFound Then
   theSel.Add aOpt, i
   Parent.window.SetDirty
Else
   MsgBox "Author has already been assigned to this title.",vbInformation,"Can't add author"
End If
</script>

