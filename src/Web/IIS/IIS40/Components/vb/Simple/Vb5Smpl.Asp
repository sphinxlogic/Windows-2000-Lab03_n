<HTML>

<HEAD>
<TITLE>Testing VB5Smpl</TITLE> 
</HEAD> 

<H1>Testing VB5Smpl</H1>

<% Set myobj = Server.CreateObject("IISSample.VB5Simple") %>
myProperty Value = <%= myobj.myProperty %><BR>

<% newvalue = "Simple" %>
Set myProperty to <%= newvalue %>
<% myobj.myProperty = newvalue %><BR>
myProperty Value is now: <%= myobj.myProperty %><BR>

<% mystring = "My String" %>
Call myMethod with <%= mystring %>: <%= myobj.myMethod(mystring) %><BR>

</HTML>
