<%@LANGUAGE = VBScript%>
<%
   Set Conn = Server.CreateObject("ADODB.Connection")
   Conn.Open "employees","",""
   Set reports = Conn.Execute("select * from direct_reports")
   reports.Save(1)
  'Do While Not reports.EOF
%>


<% 
   'reports.MoveNext
   'Loop
%>
