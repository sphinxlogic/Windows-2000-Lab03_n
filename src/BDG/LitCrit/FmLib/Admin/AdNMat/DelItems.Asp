<%@ Language=VBScript EnableSessionState=False %>
<% Option Explicit %>
<% ' Copyright Microsoft 1998-1999.  All rights reserved. %>
<!--#include file="ReportError.asp"-->
<% Dim rs, item, strArray, strComma
   
   On Error Resume Next
   
   Set rs = Server.CreateObject("ADODB.Recordset")
   rs.Open "Item", Application("FmLib_ConnectionString"), adOpenForwardOnly, adLockOptimistic, adCmdTable
   If Err.number <> 0 Then ReportError(Err.description)
   
   For Each item In Request.QueryString("item")
      rs.Filter = "item#=" & item
      rs.Requery
      If Not rs.EOF Then
         Response.Write "DEL ITEM#: " & item & "<br>"
         rs.Delete
         If Err.Number = 0 Then
            strArray = strArray & strComma & item
            strComma = ","
         Else
            ReportError(Err.Description)
         End If
      End If
   Next
   rs.Close
%>
<script LANGUAGE=VBScript>
   Dim theDels,theOpts,i,item,nDeleted,nToFind
   
   ' These are the items to delete
   theDels = Array(<%= strArray %>)
   
   Set theOpts = parent.document.frmAddItem.ItemNum.options
   nToFind = UBound(theDels) + 1
   nDeleted = 0
   For i = 0 To theOpts.length - nToFind
      For Each item In theDels
         If CLng(theOpts(i).Value) = item Then
            theOpts.remove(i)
            nDeleted = nDeleted + 1
            i = i - 1   ' Account for the loss of the current option
            Exit For
         End If
      Next
      If nDeleted = nToFind Then Exit For  ' No more to find
   Next
</script>
