<%@ Language=VBScript EnableSessionState=False %>
<% Option Explicit %>
<% ' Copyright Microsoft 1998-1999.  All rights reserved. %>
<!--#include file="ReportError.asp"-->
<% Dim rs, item, strArray, strComma, bFailures
   
   On Error Resume Next
   
   Set rs = Server.CreateObject("ADODB.Recordset")
   rs.Open "Subject", Application("FmLib_ConnectionString"), adOpenForwardOnly, adLockOptimistic, adCmdTable
   For Each item In Request.QueryString("subj")
      rs.Filter = "subj#=" & item
      rs.Requery
      If Not rs.EOF Then
         rs.Delete
         If Err.Number = 0 Then
            strArray = strArray & strComma & item
            strComma = ","
         Else
            If InStr(UCase(Err.Description),"TITLESUBJ") > 0 Then
               bFailures = True
            Else
               ReportError(Err.Description)
            End If
            Err.Clear
         End If
      End If
   Next
   rs.Close
%>
<script LANGUAGE=VBScript>
   Dim theDels,theOpts,i,item,nDeleted,nToFind
   
   ' These are the items to delete
   theDels = Array(<%= strArray %>)
   
   Set theOpts = parent.document.frmAddTitle.SubjNum.options
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
  If bFailures Then ReportError("Some subjects could not be deleted. Please verify that they are not currently assigned to a title and try again.")
%>