<%@ language=javascript %>
<% 
	Response.Expires = -1000;

	var xmldoc = Application("SHAREDXML");
	if (xmldoc != null)
	{
		Response.ContentType = "text/xml";
		xmldoc.save(Response);
	}
%>
       
