<% @Language=VBScript	%>


<%
	' Define Constants

	ForReading   = 1
	ForWriting   = 2
	ForAppending = 8
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
			' Map current path to physical path
			curDir = Server.MapPath("\iissamples\sdk\asp\components\")


			' Create FileSytemObject Component
			Set ScriptObject = Server.CreateObject("Scripting.FileSystemObject")


			' Create and Write to a File
			Set MyFile = ScriptObject.CreateTextFile(curDir + "\" + "MyTextFile.txt", ForWriting)
			
			For x = 1 to 5
				MyFile.WriteLine "Line number " & x & " was written on " & now & "<br>"
			Next
			
			Myfile.Close
		%>
		
		<%
			' Read From File and Output to Screen
			Set MyFile = ScriptObject.OpenTextFile(curDir + "\" + "MyTextFile.txt", ForReading)
			Response.Write MyFile.ReadAll
		%>

    </BODY>
</HTML>