<%@ Language=VBScript EnableSessionState=False Transaction=Required %>
<% Option Explicit %>
<% ' Copyright Microsoft 1998-1999.  All rights reserved. %>
<% Response.Buffer = True %>
<!-- #include file="ReportError.asp" -->
<% Dim oAdmin,cn,cmd,item,nBibNo,fUpdate,strDate

   '--- Get the bib#, if present in the form
   fUpdate = False
   nBibNo = Request.Form("BibNo")
   If IsNumeric(nBibNo) Then
      nBibNo = CLng(nBibNo)
      If nBibNo > 0 Then fUpdate = True
   Else
      nBibNo = 0
   End If

   '--- Only update if form was modified
   If CBool(Request.Form("Dirty")) Then
   
      ' DEBUG: What was sent??
      If Application("Debug") Then
         Response.Write "<h2>Testing...</h2>"
         For Each item In Request.Form
            Response.Write "<b>" & item & "</b>: " & Request.Form(item) & "<br>"
         Next
      End If
      
      '--- Munge the date, if necessary
      strDate = Trim(Request.Form("PubDate"))
      If Not IsDate(strDate) Then
         If IsNumeric(strDate) And (Len(strDate)=4 Or Len(strDate)=2) Then
            strDate = "1-1-" & strDate
         Else
            Response.Write "ERROR: Invalid PubDate."
            Response.End
         End If
      End If

      Set oAdmin = Server.CreateObject("CML.Admin")
      oAdmin.ConnectionString = Application("FmLib_ConnectionString")
      
      nBibNo = oAdmin.UpdateTitle(nBibNo, Trim(Request.Form("Title")), Trim(Request.Form("Call")), _
               Trim(Request.Form("Coll")), Trim(Request.Form("ISBN")), Trim(Request.Form("Publisher")), _
               CDate(strDate), Trim(Request.Form("Description")), Trim(Request.Form("Notes")))
      
      '--- If update successful...
      If nBibNo > 0 Then
   
         Set cn = Server.CreateObject("ADODB.Connection")
         cn.ConnectionTimeout = Application("FmLib_ConnectionTimeout")
         cn.Open Application("FmLib_ConnectionString")

         Set cmd = Server.CreateObject("ADODB.Command")
         Set cmd.ActiveConnection = cn
         
         '--- Update linking table for authors
         If fUpdate Then
            cmd.CommandText = "DELETE FROM TitleAuth WHERE bib#=" & nBibNo
            cmd.Execute 
         End If
         For Each item In Request.Form("AuthNum")
            Response.Write "ADD AUTH#: " & item & "<br>"
            cmd.CommandText = "INSERT INTO TitleAuth VALUES(" & nBibNo & "," & item & ")"
            cmd.Execute 
         Next

         '--- Update linking table for subjects
         If fUpdate Then
            cmd.CommandText = "DELETE FROM TitleSubj WHERE bib#=" & nBibNo
            cmd.Execute 
         End If
         For Each item In Request.Form("SubjNum")
            Response.Write "ADD SUBJ#: " & item & "<br>"
            cmd.CommandText = "INSERT INTO TitleSubj VALUES(" & nBibNo & "," & item & ")"
            cmd.Execute 
         Next
         
         '--- Clean up
         Set cmd = Nothing
         cn.Close

         ObjectContext.SetComplete
      Else
         ObjectContext.SetAbort
      End If
   End If
   
   If nBibNo > 0 Then
      Response.Redirect "AddItems.asp?bibno=" & nBibNo
   Else
      Response.Redirect "../Catalog.asp"
   End If
%>
