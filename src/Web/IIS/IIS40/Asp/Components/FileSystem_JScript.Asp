<% @Language=JScript 	%>

<%
	// Define Constants

	ForReading   = 1;
	ForWriting   = 2;
	ForAppending = 8;
%>

<HTML>
    <HEAD>
        <TITLE>FileSystem Component</TITLE>
    </HEAD>

    <BODY bgcolor="white" topmargin="10" leftmargin="10">
        
		
        <!-- Display Header -->

        <font size="4" face="Arial, Helvetica">
        <b>FileSystem Component</b></font><br>   

		<hr size="1" color="#000000">


		<%
			// Map current path to physical path
			curDir = Server.MapPath("\\iissamples\\sdk\\asp\\components\\");


			// Create FileSytemObject Component
			ScriptObject = Server.CreateObject("Scripting.FileSystemObject");


			// Create and Write to a File
			MyFile = ScriptObject.CreateTextFile(curDir + "\\" + "MyTextFile.txt", ForWriting);
			
			for (x = 1; x < 5; x++)
			{
				MyFile.WriteLine("Line number " + x + " was written to MyTextFile.txt <br>");
			}
						
			MyFile.Close();
		%>
		
		<%
			// Read From File and Output to Screen
			MyFile = ScriptObject.OpenTextFile(curDir + "\\" + "MyTextFile.txt", ForReading);
			Response.Write(MyFile.ReadAll());
			
			MyFile.Close();
		%>

    </BODY>
</HTML>