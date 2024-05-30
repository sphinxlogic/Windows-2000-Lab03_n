<%@ language=javascript %>
<% 
    Response.Expires = -1000;
    if (Request.ServerVariables("REQUEST_METHOD") == "POST") 
    {
       // Load the posted XML document
       var doc = Server.CreateObject("Microsoft.XMLDOM");
       doc.load(Request);
       // and ping it right back to the client.
       Response.ContentType = "text/xml";
       doc.save(Response);
    }
    else
    {
      var strPOSTURL = "http://" + Request.ServerVariables("SERVER_NAME") +
        Request.ServerVariables("SCRIPT_NAME");
%>

<html>

<script>
  function postXML()
  {    
    var xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
    xmlhttp.Open("POST", "<%=strPOSTURL%>", false);
    xmlhttp.Send(XML.value);
    alert("Round tripped XML document:\n\n" + xmlhttp.responseXML.xml);
  }
</script>
<textarea id=XML rows=12 cols=60><XML>
This is the XML document that will be round tripped...
</XML></textarea>
<P>
<input type=button value="PING" onclick="postXML()">

<P>The source of the ASP script is:
<PRE>
&lt;%@ language=javascript %>
&lt;% 
    Response.Expires = -1000;
    <B>// Load the posted XML document</B>
    var doc = Server.CreateObject("Microsoft.XMLDOM");
    doc.load(Request);
    <B>// and ping it right back to the client.</B>
    Response.ContentType = "text/xml";
    doc.save(Response);
%&gt;
</PRE>

<%
    }
%>
