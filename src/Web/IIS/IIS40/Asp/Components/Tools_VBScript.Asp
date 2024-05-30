<%@ LANGUAGE = VBScript %>
<%  Option Explicit     %>


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
			Dim Tools 
			Dim FoundFile, FileExists, FileDoesNotExist, NotFoundFile
			Dim RandInt, RandPosInt, RandIntBelow

			Set Tools = Server.CreateObject("MSWC.Tools")
		%>
	

		<h3> FileExists Example </h3>
	
		<%
			FoundFile = "Tools_VBScript.asp"
			NotFoundFile = "blah.asp"

	
			' Check if file exists
	
			FileExists = Tools.FileExists(FoundFile)


			' Output Response Appropriately

			If FileExists = TRUE Then 
				Response.Write "The File " & FoundFile & " Exists<BR>"
			Else 
				Response.Write "The File " & FoundFile & " Does Not Exist<BR>"
			End If


			' Check if file exists
			
			FileDoesNotExist = Tools.FileExists(NotFoundFile)


			' Output Response Appropriately
		
			If FileDoesNotExist = TRUE Then 
				Response.Write "The File " & NotFoundFile & " Exists"
			Else 
				Response.write "The File " & NotFoundFile & " Does Not Exist"
			End If
		%>
	

		<h3> Random Integer Example </h3>
	
		<%
			' Random Integer
	
			RandInt = Tools.Random
			Response.Write "Random integer: "
			Response.Write RandInt
			Response.Write "<BR>"

	
			' Positive Random Integer
			
			RandPosInt = Abs( Tools.Random )
			Response.Write "Positive random integer: "
			Response.Write RandPosInt
			Response.Write "<BR>"

			
			' Positive Random Integer between 0 and 100
			
			RandIntBelow =  Abs( Tools.Random ) Mod 100
			Response.write "Random integer below 100: "
			Response.write RandIntBelow
			Response.write "<BR>"
		%>
    </BODY>
</HTML>
