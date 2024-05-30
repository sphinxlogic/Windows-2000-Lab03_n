<%@ Language=VBScript EnableSessionState=False %>
<% Option Explicit %>
<% ' Copyright Microsoft 1998-1999.  All rights reserved. %>
<!--#include file="ReportError.asp"-->
<% Dim rs, item, strArray, strComma, bFailures

   On Error Resume Next

   Set rs = Server.CreateObject("ADODB.Recordset")
   rs.Open "Author", Application("FmLib_ConnectionString"), adOpenForwardOnly, adLockOptimistic, adCmdTable
   For Each item In Request.QueryString("auth")
      rs.Filter = "auth#=" & item
      rs.Requery
      If Not rs.EOF Then
         rs.Delete
         If Err.Number <> 0 Then
            If InStr(UCase(Err.Description),"TITLEAUTH") > 0 Then
               bFailures = True
               rs.CancelUpdate   ' Don't bother with committing delete
            Else
               ReportError(Err.Description)
            End If
            Err.Clear
         End If
      End If
      ' Remove author from listbox anyway...
      strArray = strArray & strComma & item
      strComma = ","
   Next
   rs.Close
%>
<script LANGUAGE=VBScript>
   Dim theDels,theOpts,i,item,nDeleted,nToFind
   
   ' These are the items to delete
   theDels = Array(<%= strArray %>)
   
   Set theOpts = parent.document.frmAddTitle.AuthNum.options
   nToFind = UBound(theDels) + 1
   nDeleted = 0
   For i = 0 To theOpts.length - nToFind
      For Each item In theDels
         If CLng(theOpts(i).Value) = item Then
            theOpts.remove(i)
            nDeleted = nDeleted + 1
            ' Account for the loss of the current option
            i = i - 1
            Exit For
         End If
      Next
      If nDeleted = nToFind Then Exit For  ' No more to find
   Next
</script>
<%
  Const sErrorText = "Some authors could not be deleted from the database. They may be currently assigned to another title."
  If bFailures Then ReportError(sErrorText)
%>