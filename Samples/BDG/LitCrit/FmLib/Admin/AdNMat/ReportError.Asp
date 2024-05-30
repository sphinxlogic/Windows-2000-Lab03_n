<% ' Copyright Microsoft 1998-1999.  All rights reserved. %>
<script LANGUAGE=VBScript RUNAT=Server>
Sub ReportError(strError)
      Response.Write "<" & "script LANGUAGE=""VBScript"">" & vbCrLf & "MsgBox """ & _
                     strError & """, vbCritical, ""Error""" & vbCrLf & "<" & "/script>"
      Response.End
End Sub
</script>
