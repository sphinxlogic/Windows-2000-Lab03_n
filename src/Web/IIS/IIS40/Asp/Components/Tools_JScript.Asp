<%@ LANGUAGE = JScript %>


<HTML>
    <HEAD>
        <TITLE>Tools Component</TITLE>
    </HEAD>

    <BODY BGCOLOR="White" topmargin="10" leftmargin="10">


        <!-- Display Header -->

        <font size="4" face="Arial, Helvetica">
        <b>Tools Component</b></font><br>
      
        <hr size="1" color="#000000">

		<%
			var Tools;
			var FoundFile, FileExists, FileDoesNotExist, NotFoundFile;
			var RandInt, RandPosInt, RandIntBelow;

			Tools = Server.CreateObject("MSWC.Tools");
		%>
	

		<h3> FileExists Example </h3>
	
		<%
			FoundFile = "Tools_VBScript.asp";
			NotFoundFile = "blah.asp";

	
			// Check if file exists
	
			FileExists = Tools.FileExists(FoundFile);


			// Output Response Appropriately

			if (FileExists == true)
			{ 
				Response.Write("The File " + FoundFile + " Exists<BR>");
			}
			else
			{ 
				Response.Write("The File " + FoundFile + " Does Not Exist<BR>");
			}


			// Check if file exists
			
			FileDoesNotExist = Tools.FileExists(NotFoundFile);


			// Output Response Appropriately
		
			if (FileDoesNotExist == true)
			{ 
				Response.Write("The File " + NotFoundFile + " Exists");
			}
			else
			{ 
				Response.Write("The File " + NotFoundFile + " Does Not Exist");
			}
		%>
	

		<h3> Random Integer Example </h3>
	
		<%
			// Random Integer
	
			RandInt = Tools.Random();
			Response.Write("Random integer: ");
			Response.Write(RandInt);
			Response.Write("<BR>");

	
			// Positive Random Integer
			
			RandPosInt = Math.abs( Tools.Random() );
			Response.Write("Positive random integer: ");
			Response.Write(RandPosInt);
			Response.Write("<BR>");

			
			// Positive Random Integer between 0 and 100
			
			RandIntBelow =  Math.abs( Tools.Random() ) % 100;
			Response.Write("Random integer below 100: ");
			Response.Write(RandIntBelow);
			Response.Write("<BR>");
		%>
    </BODY>
</HTML>
