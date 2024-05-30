<SCRIPT LANGUAGE=VBScript RUNAT=Server>
 REM Returns the minimum number greater than 0
 REM If both are 0, returns -1
 FUNCTION fMin (iNum1, iNum2)
  If iNum1 = 0 AND iNum2 = 0 Then
    fMin = -1
  ElseIf iNum2 = 0 Then
    fMin = iNum1
  ElseIf iNum1 = 0 Then
    fMin = iNum2
  ElseIf iNum1 < iNum2 Then
    fMin = iNum1
  Else 
    fMin = iNum2
  End If
 END FUNCTION
</SCRIPT>

<SCRIPT LANGUAGE=VBScript RUNAT=Server>
 FUNCTION fCheckLine (ByVal strLine)

  fCheckLine = 0
  iTemp = 0

  iPos = InStr(strLine, "<" & "%")
  If fMin(iTemp, iPos) = iPos Then
    iTemp = iPos
    fCheckLine = 1
  End If
  
  iPos = InStr(strLine, "%" & ">")
  If fMin(iTemp, iPos) = iPos Then
    iTemp = iPos
    fCheckLine = 2
  End If

  iPos = InStr(1, strLine, "<" & "SCRIPT", 1)
  If fMin(iTemp, iPos) = iPos Then
    iTemp = iPos
    fCheckLine = 3
  End If

  iPos = InStr(1, strLine, "<" & "/SCRIPT", 1)
  If fMin(iTemp, iPos) = iPos Then
    iTemp = iPos
    fCheckLine = 4
  End If

  iPos = InStr(1, strLine, "<" & "!--", 1)
  If fMin(iTemp, iPos) = iPos Then
    iTemp = iPos
    fCheckLine = 5
  End If

  iPos = InStr(1, strLine, "-" & "->", 1)
  If fMin(iTemp, iPos) = iPos Then
    iTemp = iPos
    fCheckLine = 6
  End If

 END FUNCTION
</SCRIPT>

<SCRIPT LANGUAGE=VBScript RUNAT=Server>
SUB PrintHTML (ByVal strLine)
	iSpaces = Len(strLine) - Len(LTrim(strLine))
	i = 1
	While Mid(Strline, i, 1) = Chr(9)
		iSpaces = iSpaces + 5
		i = i + 1
	Wend
  If iSpaces > 0 Then
    For i = 1 to iSpaces
      Response.Write("&nbsp;")
    Next
  End If
  iPos = InStr(strLine, "<")
  If iPos Then
    Response.Write(Left(strLine, iPos - 1))
    Response.Write("&lt;")
    strLine = Right(strLine, Len(strLine) - iPos)
    Call PrintHTML(strLine)
  Else
    Response.Write(strLine)
  End If
 END SUB
</SCRIPT>
	
<SCRIPT LANGUAGE=VBScript RUNAT=Server>
 SUB PrintLine (ByVal strLine, iFlag)
	
  Select Case iFlag
    Case 0
      Call PrintHTML(strLine)

    Case 1
      iPos = InStr(strLine, "<" & "%")
      Call PrintHTML(Left(strLine, iPos - 1))
      Response.Write("<FONT COLOR=#ff0000>")
      Response.Write("&lt;%")
      strLine = Right(strLine, Len(strLine) - (iPos + 1))
      Call PrintLine(strLine, fCheckLine(strLine))

    Case 2
      iPos = InStr(strLine, "%" & ">")
      Call PrintHTML(Left(strLine, iPos -1))
      Response.Write("%&gt;")
      Response.Write("</FONT>")
      strLine = Right(strLine, Len(strLine) - (iPos + 1))
      Call PrintLine(strLine, fCheckLine(strLine))

    Case 3
      iPos = InStr(1, strLine, "<" & "SCRIPT", 1)
      Call PrintHTML(Left(strLine, iPos - 1))
      Response.Write("<FONT COLOR=#0000ff>")
      Response.Write("&lt;SCRIPT")
      strLine = Right(strLine, Len(strLine) - (iPos + 6))
      Call PrintLine(strLine, fCheckLine(strLine))

    Case 4
      iPos = InStr(1, strLine, "<" & "/SCRIPT>", 1)
      Call PrintHTML(Left(strLine, iPos - 1))
      Response.Write("&lt;/SCRIPT&gt;")
      Response.Write("</FONT>")
      strLine = Right(strLine, Len(strLine) - (iPos + 8))
      Call PrintLine(strLine, fCheckLine(strLine))

    Case 5
      iPos = InStr(1, strLine, "<" & "!--", 1)
      Call PrintHTML(Left(strLine, iPos - 1))
      Response.Write("<FONT COLOR=#0000ff>")
      Response.Write("&lt;!--")
      strLine = Right(strLine, Len(strLine) - (iPos + 3))
      Call PrintLine(strLine, fCheckLine(strLine))

    Case 6
      iPos = InStr(1, strLine, "-" & "->", 1)
      Call PrintHTML(Left(strLine, iPos - 1))
      Response.Write("--&gt;")
      Response.Write("</FONT>")
      strLine = Right(strLine, Len(strLine) - (iPos + 2))
      Call PrintLine(strLine, fCheckLine(strLine))

    Case Else
      Response.Write("FUNCTION ERROR -- PLEASE CONTACT ADMIN.")
  End Select
 END SUB
</SCRIPT>

<HTML>
    <HEAD>
        <META NAME="DESCRIPTION" CONTENT="ASP Source code browser">
        <META NAME="GENERATOR" CONTENT="Microsoft Visual InterDev 1.0">
        <META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=iso8859-1">
    </HEAD>

    <BODY BGCOLOR="#FFFFFF">

        <FONT FACE="VERDANA, ARIAL, HELVETICA">
        <%
        strVirtualPath = Request("Source")
        %>

             <!-- DISPLAY THE COLOR LEGEND -->
        <TABLE BORDER=1>
	        <TR>
	          <TD WIDTH="25" BGCOLOR="#FF0000">&nbsp;&nbsp;
	          </TD>
	          <TD><FONT FACE="VERDANA, ARIAL, HELVETICA" SIZE="2">ASP Script</FONT>
	          </TD>
            </TR>
            <TR>
	          <TD BGCOLOR="#0000FF">&nbsp;&nbsp;
	          </TD>
	          <TD><FONT FACE="VERDANA, ARIAL, HELVETICA" SIZE="2">Comments</FONT>
	          </TD>
            </tr>
            <tr>
	          <TD BGCOLOR="#000000">&nbsp;&nbsp;
	          </TD>
	          <TD><FONT FACE="VERDANA, ARIAL, HELVETICA" SIZE="2">HTML and Text</FONT>
	          </TD>
	        </TR>
        </TABLE>

               
        <hr size="1" color="#000000">

        <FONT FACE="VERDANA, ARIAL, HELVETICA" SIZE="2">

        <%
        strFilename = Server.MapPath(strVirtualPath)
        Set FileObject = Server.CreateObject("Scripting.FileSystemObject")
        Set oInStream = FileObject.OpenTextFile(strFilename)

	

	  While NOT oInStream.AtEndOfStream
          strOutput = oInStream.ReadLine
		
          Call PrintLine(strOutput, fCheckLine(strOutput))
          Response.Write("<BR>")
        Wend
        %>


        <hr>


        </FONT>
    </BODY>
</HTML>
