<%@ LANGUAGE="JSCRIPT" %>
<%  Response.ContentType = "application/x-cdf" %>

<?XML version="1.0"?>

<CHANNEL HREF="http://www.microsoft.com/">

	<TITLE>IIS SDK CDF Test</TITLE>
	<ABSTRACT>CDF file with ASP</ABSTRACT>

	<SCHEDULE>
		<INTERVALTIME HOUR="1" />
	</SCHEDULE>

	<%
		GetChannelItems();
	%>

</CHANNEL>


<%
	// GetChannelItems uses the FileSystem Object
	// to access a file on the server that holds
	// all the latest news headlines. 

	function GetChannelItems()
	{
		// Open FileList.txt to provide dynamic CDF information

		fso = Server.CreateObject("Scripting.FileSystemObject");
		prFile = fso.OpenTextFile(Server.MapPath("FileList.txt"));


		// Iterate through the file, dynamically creating CDF
		// item entries

		while(!prFile.AtEndOfStream)
		{

			// Get headline for item
        
			strTitle = prFile.ReadLine();


			// Get URL of item
        
			strLink = prFile.ReadLine();


			// Write CDF Item Tag
            
			Response.Write("<ITEM HREF=" + strLink + ">");
			Response.Write("  <TITLE>" + strTitle + "!!!</TITLE>");
			Response.Write("  <ABSTRACT>" + strTitle + "</ABSTRACT>");
			Response.Write("</ITEM>");
		}
	}
%>
