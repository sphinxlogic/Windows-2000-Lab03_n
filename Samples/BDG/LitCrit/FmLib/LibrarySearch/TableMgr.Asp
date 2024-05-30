<% ' Copyright 1998-1999 Microsoft Corporation. All rights reserved. %>
<script LANGUAGE=VBScript RUNAT=Server>
Function GetTableList()
   Set GetTableList = Session("_TableList")
   If GetTableList Is Nothing Then
      Set GetTableList = Server.CreateObject("Scripting.Dictionary")
      ' Check for error...
      If Not GetTableList Is Nothing Then
         Set Session("_TableList") = GetTableList
      Else
         Err.Raise &H800C2001, "AddTableToSession", "Cannot create dictionary for holding table names."
      End If
   End If
End Function

Sub AddSearchTable(ByRef strTblName)
   Dim dctTables
   Set dctTables = GetTableList
   dctTables.Add strTblName, strTblName
End Sub

'--- Drop tables that have been created during this session
'--- (Duplicated in global.asa, but the script is here for completeness)
Sub DropSearchTables()
   Dim dctTables, key, cmd
   Set dctTables = Session("_TableList")
   If Not dctTables Is Nothing Then
      If dctTables.Count > 0 Then
         Set cmd = Server.CreateObject("ADODB.Command")
         cmd.ActiveConnection = Application("FmLib_ConnectionString")
         For Each key In dctTables.Keys
            cmd.CommandText = "DROP TABLE " & key
            cmd.Execute 
         Next
      End If
   End If
   ' Start over...
   Set Session("_TableList") = Nothing
End Sub
</script>