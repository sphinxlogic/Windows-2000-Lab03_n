<%@ language=javascript %>
<% 
	Response.Expires = -1000;

	var xmldoc = Application("SHAREDXML");
	if (xmldoc == null)
	{
		xmldoc = Server.CreateObject("Microsoft.FreeThreadedXMLDOM");
		Application("SHAREDXML") = xmldoc;
	}
  	xmldoc.load(Request);
%>Ok
