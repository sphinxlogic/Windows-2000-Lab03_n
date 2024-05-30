<%@ Language=VBScript EnableSessionState=False Transaction=Required %>
<% Option Explicit %>
<% ' Copyright Microsoft 1998-1999.  All rights reserved. %>
<% Response.Buffer = True %>
<!--#include file="ReportError.asp"-->
<% Dim oAdmin,nItemNo,fUpdate,strItemText

   '--- Get the item#, if present in the form
   nItemNo = Request.Form("ItemNum")
   If IsNumeric(nItemNo) Then
      nItemNo = CLng(nItemNo)
   Else
      ItemNo = 0
   End If

   fUpdate = (Request.QueryString("Action") = "Update")
   
   Set oAdmin = Server.CreateObject("CML.Admin")
   oAdmin.ConnectionString = Application("FmLib_ConnectionString")
   oAdmin.ConnectionTimeout = Application("FmLib_ConnectionTimeout")
   
   On Error Resume Next
   
   '--- UPDATE or ADD item depending on Action param
   If fUpdate Then
      nItemNo = oAdmin.UpdateItem(nItemNo, Trim(Request.Form("Barcode")), _
                CLng(Request.Form("BibNo")), Trim(Request.Form("Location")), _
                Trim(Request.Form("Source")), CDbl(Trim(Request.Form("Price"))), _
                Trim(Request.Form("Notes")), (Request.Form("StaffOnly") = "on"), _
                Trim(Request.Form("Item_Status")))
   Else ' Add new item
      strItemText = Trim(Request.Form("NewBarcode"))
      nItemNo = oAdmin.UpdateItem(0, strItemText, CLng(Request.Form("BibNo")), _
                Application("DefaultLocation"), "", 0, "", False, _
                Application("DefaultItemStatus"))
   End If

   '--- Catch duplicate barcode error   
   If Err.Number <> 0 Then
      If InStr(Err.Description,"UQ_Item_Barcode") > 0 Then
         ReportError "Barcode labels must be unique. Please enter another barcode."
      Else
         ReportError Err.Description
      End If
   End If

   If nItemNo > 0 Then
      Response.Write "ITEM#: " & nItemNo & "<br>"
      ObjectContext.SetComplete
   Else
      ObjectContext.SetAbort
   End If

   ' IFRAME scripts...   
   If fUpdate Then
%>

   <script LANGUAGE=VBScript>
      parent.Reset
   </script>

<% Else ' Add %>      

   <script LANGUAGE=VBScript>
   Dim theForm, aOpt, theSel, theOpts

   ' Remove the entry from the form (since it will appear below)
   Set theForm = parent.document.frmAddItem
   theForm.NewBarcode.Value = ""

   Set aOpt = document.createElement("OPTION")
   aOpt.Text = "<%= strItemText %>"
   aOpt.Value = "<%= nItemNo %>"

   ' Add the new item to the end of the list
   Set theSel = theForm.ItemNum
   Set theOpts = theSel.options
   theSel.add aOpt
   theOpts(theOpts.Length-1).Selected = True

   ' Move the wizard forward
   parent.nLastSel = <%= nItemNo %>
   parent.GetData(<%= nItemNo %>)
   parent.WizForward()
   </script>

<% End If %>
