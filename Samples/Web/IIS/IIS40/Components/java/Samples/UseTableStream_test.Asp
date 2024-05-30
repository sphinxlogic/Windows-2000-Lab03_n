<%@ LANGUAGE = VBScript %>
<%  Option Explicit     %>

<HTML>
<HEAD>
<META NAME="GENERATOR" Content="Microsoft Developer Studio">
<META HTTP-EQUIV="Content-Type" content="text/html; charset=iso-8859-1">
<TITLE>Java Component Samples: UseTableStream</TITLE>
</HEAD>
<BODY>

This Java class calls another Java class, HTMLTableStream, from within.<P>
HTMLTableStream expects an OutputStream, and conveniently the Framework's Request object is one.<P>

<%

    Dim Obj

    Set Obj = Server.CreateObject("IISSample.UseTableStream")

    Obj.makeTable

%>

</BODY>
</HTML>
