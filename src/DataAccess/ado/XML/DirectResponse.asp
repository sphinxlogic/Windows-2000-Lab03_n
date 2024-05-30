<HTML>
<HEAD>
<TITLE>SAMPLE: Writing ADO Recordsets to Response Object as XML</TITLE>
<STYLE>
<!--
BODY {
	font-family: sans-serif;
	margin-top: 10;
	margin-left: 20;
	margin-right: 0;
	margin-bottom: 0;
	 }
.thead {
	background-color: #008080; 
	font-family: 'Arial Narrow','Arial',sans-serif; 
	font-size: x-small;
	color: white;
	}
.tbody1 { 
	text-align: center;
	background-color: #f7efde;
	font-family: 'Arial Narrow','Arial',sans-serif; 
	font-size: x-small;
	 }
-->
</STYLE>
</HEAD>
<BODY BACKGROUND="AddressBook/Arcadia.gif">

<H3>ADO 2.5 Features Sample</H3>
<H5>Using the URL Property with RDS.DataControl Object</H5>
<H5>Writing ADO 2.5 Recordsets to ASP Response Object as XML</H5>

<CENTER>
<table>
  <tr><td>Source URL:<td><INPUT NAME=srcurl SIZE=50></td></td></tr>
  <tr><td>Destination URL:<td><INPUT NAME=desturl SIZE=50></td></td></tr>
</table>

<BR>
<INPUT TYPE=BUTTON NAME="Requery" VALUE="Run!"> 
<INPUT TYPE=BUTTON NAME="MoveFirst" VALUE="First"> 
<INPUT TYPE=BUTTON NAME="MovePrev" VALUE="Prev"> 
<INPUT TYPE=BUTTON NAME="MoveNext" VALUE="Next"> 
<INPUT TYPE=BUTTON NAME="MoveLast" VALUE="Last"> 
<INPUT TYPE=BUTTON NAME="Update" VALUE="Save Changes">
<BR><BR>
</CENTER>

<OBJECT classid="clsid:BD96C556-65A3-11D0-983A-00C04FC29E33"
    ID=DC1 HEIGHT=1 WIDTH=1>
</OBJECT>

<SCRIPT LANGUAGE="VBScript">
'---- enum Values ----
Const adcExecSync = 1
Const adcExecAsync = 2

'---- enum Values ----
Const adcFetchUpFront = 1
Const adcFetchBackground = 2
Const adcFetchAsync = 3

'---- enum Values ----
Const adcStateClosed = &H00000000
Const adcStateOpen = &H00000001
Const adcStateConnecting = &H00000002
Const adcStateExecuting = &H00000004
Const adcStateFetching = &H00000008

'---- enum Values ----
Const adcReadyStateUninitialized = 0
Const adcReadyStateLoading = 1
Const adcReadyStateLoaded = 2
Const adcReadyStateInteractive = 3
Const adcReadyStateComplete = 4


Sub Window_OnLoad
	' To use this file without ASP: 
	' Set srcurl.value   = full URL path to FlatADOResp.asp 
	' and desturl.value  = full URL path to FlatADOReq.asp 
	' (e.g.  "http://server/path/FlatADOReq.asp")
		
	srcurl.value  = "<%=BuildURL("FlatADOResp.asp")%>"
	desturl.value = "<%=BuildURL("FlatADOReq.asp")%>"
End Sub

Sub DC1_OnReadyStateChanged
  'Fires every time that DC1.ReadyState changes
  MsgBox "OnReadyStateChanged has fired"	
End Sub

Sub DC1_OnDataSetChanged
  'Fires after execution is done
  MsgBox "OnDataSetChanged has fired"
End Sub

Sub DC1_OnDataSetComplete
  'Fires after fetching is complete
  MsgBox "OnDataSetComplete has fired"
  refreshGrid
End Sub

Sub Move (strDirection)
  'Custom sub to handle Asyncronous fetching
  'Asynchronous fetching allows you to cancel in the middle of fetching a large
  'recordset
  If DC1.Recordset.State = adcStateClosed Then
    If DC1.ReadyState = adcReadyStateComplete Then
      MsgBox "Query results failed to arrive, please rerun query synchronously and check for errors."
    End If
    If DC1.ReadyState = adcReadyStateLoaded Then
      MsgBox "Query results have not yet arrived"	
    End If
  Else
    If DC1.Recordset.State = adcStateOpen Then	
      On Error Resume Next
      Select Case strDirection
        Case "First"
          DC1.Recordset.MoveFirst
        Case "Next"
          DC1.Recordset.MoveNext
        Case "Last"
          DC1.Recordset.MoveLast
        Case "Prev"
          DC1.Recordset.MovePrevious
       End Select
      If Err.Number <> 0 Then
        If Err.Number = 3021 Then
          If DC1.Recordset.BOF Then
            DC1.Recordset.MoveFirst  'If already at start of recordset stay at top.
          Else 
            DC1.Recordset.MoveLast   'If already at end of recordset stay at bottom.
          End If
        Else 
          MsgBox "Unexpected error in Move actions. " & Err.Description
        End If
      End If
    Else
      MsgBox "The state is unexpected, an error has occurred"   'Very General error msg. 
    End If
  End If
End Sub

Sub MoveFirst_OnClick
  'Call to Custom Sub, Move, to handle attempts to move the record pointer during asynch fetches
  Move "First"
End Sub

Sub MoveNext_OnClick
  'Call to Custom Sub, Move, to handle attempts to move the record pointer during asynch fetches
  Move "Next"
End Sub

Sub MovePrev_OnClick
  'Call to Custom Sub, Move, to handle attempts to move the record pointer during asynch fetches
  Move "Prev"
End Sub

Sub MoveLast_OnClick
  'Call to Custom Sub, Move, to handle attempts to move the record pointer during asynch fetches
  Move "Last"
End Sub

'Submits edits made and pulls a clean copy of the new data.
Sub Update_OnClick
  If DC1.ReadyState <> adcReadyStateLoaded then
	DC1.URL = desturl.value
    DC1.SubmitChanges
    DC1.Refresh
  Else
    MsgBox "Query results still arriving, Please wait"
  End If
End Sub

Sub Requery_OnClick
  If DC1.ReadyState <> adcReadyStateComplete then
    MsgBox "Query results still arriving, Please wait"
  Else
	DC1.URL = srcurl.value
    DC1.Refresh
  End If
End Sub
</SCRIPT>


<!--Begin DHTML Grid -->
<DIV ID="Grid1" 
     STYLE="position:relative;left:25;top:0;height:200;width:600;overflow:auto;border:1pt;" 
     DATASRC="#DC1"
     ALIGN=CENTER
     MAXFIELDLEN=30
     EDITABLE=TRUE>

<TABLE DATASRC="" ID="tblGrid">
	<THEAD CLASS=thead>
		<TR ID="tblHead"></TR>
	</THEAD>

	<TBODY CLASS=tbody1>
		<TR ID=tblBody></TR>
	</TBODY>
</TABLE>

<SCRIPT LANGUAGE=VBSCRIPT>
Dim m_bEdit, m_ParentDataCtrl, m_ParentDoc, m_iMaxFieldLen
Const adBoolean = 11

m_iMaxFieldLen = Grid1.getAttribute("MaxFieldLen")
If IsNull(m_iMaxFieldLen) Then m_iMaxFieldLen = 30

Sub RefreshGrid()
	m_bEdit = Grid1.getAttribute("EDITABLE")
		
	constructGrid
End Sub

Sub constructGrid()
	Dim i, oNewHead, oNewCell, sRow, sFieldName, _
	       iNumCols, iFieldLen, sFieldType, sID
	    
	'erase the old grid so we don't get multiple copies 
	destroyGrid
		
	iNumCols = DC1.Recordset.Fields.Count - 1

	m_bEdit = Grid1.getAttribute("Editable")
	
	'unbind the table so we can modify bound elements
	tblGrid.dataSrc = ""
		
	For i = 0 to iNumCols
		sFieldName = DC1.Recordset.Fields(i).name
		iFieldLen  = DC1.Recordset.Fields(i).DefinedSize
		sFieldType = DC1.Recordset.Fields(i).Type
				
		Set oNewHead = document.createElement("TH")
		tblHead.appendChild(oNewHead)	
		oNewHead.InnerText =  sFieldName
		Set oNewHead = Nothing
		
		Set oNewCell = document.createElement("TD")
		tblBody.appendChild(oNewCell)
		
		If m_bEdit Then
			Select Case sFieldType
				Case adBoolean
					sRow = "<INPUT DATAFLD=" & sFieldName & " TYPE=CHECKBOX>"
				Case Else
					If CInt(iFieldLen) <= CInt(m_iMaxFieldLen) Then
						sRow = "<INPUT DATAFLD=" & sFieldName & " SIZE=" & _ 
						        CStr(iFieldLen) & ">"
					Else
						sRow = "<INPUT DATAFLD=" & sFieldName & " SIZE=" & _ 
						        CStr(m_iMaxFieldLen) & ">"
					End If
			End Select
		Else
			sRow = "<SPAN DATAFLD=" & sFieldName & "></SPAN>&nbsp;"
		End If
		
		oNewCell.InnerHTML = sRow
		Set oNewCell = Nothing
	Next
	
	'rebind the table to the DataControl object
	tblGrid.dataSrc = "#DC1"
End Sub

Sub destroyGrid()
	Dim oRows, i
	
	'unbind the table so we can modify bound elements
	tblGrid.dataSrc = ""	
	
	For i=(tblHead.children.length-1) to 0 Step -1
		tblHead.deleteCell(i)
	Next
	
	For i=(tblBody.children.length-1) to 0 Step -1
		tblBody.deleteCell(i)
	Next
End Sub

Sub tblGrid_onreadystateChange()
	If tblGrid.readyState = "complete" Then			
		handleRowEnter
	End If
End Sub

Sub tblGrid_onclick()
	DC1.recordset.absoluteposition = CInt(window.event.srcElement.recordNumber)
	window.event.cancelBubble = TRUE
End Sub

Function handleRowEnter()
	tblGrid.rows(DC1.recordset.absoluteposition).style.backgroundcolor = "navy"
End Function

Sub DC1_onrowexit()
	tblGrid.rows(DC1.recordset.absoluteposition).style.backgroundcolor = ""
End Sub

Sub DC1_onrowenter()
	If tblGrid.readyState = "complete" Then
		If DC1.recordset.BOF Then
			tblGrid.rows(1).style.backgroundcolor = "navy"
		ElseIf DC1.recordset.EOF Then
			tblGrid.rows(DC1.recordset.recordcount).style.backgroundcolor = "navy"
			DC1.recordset.absoluteposition = DC1.recordset.recordcount
		Else
			tblGrid.rows(DC1.recordset.absoluteposition).style.backgroundcolor = "navy"
		End If
	End If
End Sub
</SCRIPT>

</DIV>
<!-- End DHTML Grid -->

<FONT SIZE=1>For best results, maximize browser window.</FONT>
</BODY>
</HTML>

<% Function BuildURL(sFile)
		 sPath = Request.ServerVariables("PATH_INFO")
		 BuildURL = "http://" & Request.ServerVariables("SERVER_NAME") & Left(sPath, InStrRev(sPath, "/")) & sFile
   End Function %>
