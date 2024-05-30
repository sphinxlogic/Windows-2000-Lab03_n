<%@ language=javascript %>
<object id=xmldoc progid=Microsoft.XMLDOM runat=Server></object>
<% 
    Response.Expires = -1000;
    if (Request.ServerVariables("REQUEST_METHOD") == "POST") 
    {
        // Load the posted XML data and save it to disk.
        xmldoc.load(Request);
        xmldoc.save(Server.MapPath("saved.xml"));
%>
Ok        
<%
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
    alert(xmlhttp.responseText);
  }
</script>
<body>
<font size=2>
<P>
Type in the data you want saved, click the SAVE button then to view the new file
created on the server click the GOTO SAVED XML button.  You then may need to hit the
refresh button to see changes.
<P>
<textarea id=XML rows=12 cols=60><XML>
This is the XML document that will be saved on the server.
</XML></textarea>
<P>
<input type=button value="SAVE" onclick="postXML()">
<input type=button value="GOTO SAVED XML" title="saved.xml" onclick="window.location = 'saved.xml'">
<P>
The code on the server is :<font size=3>
<PRE>
&lt;object id=xmldoc progid=Microsoft.XMLDOM runat=Server></object>
&lt;% 
    <B>// Load the posted XML data and save it to disk.</B>
    xmldoc.load(Request);
    xmldoc.save(Server.MapPath("saved.xml"));
%>

</PRE>

<%
    }
%>