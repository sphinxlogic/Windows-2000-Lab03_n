<HTML>
<HEAD>
<TITLE>RDS Sample Query Page</TITLE>
</HEAD>
<BODY BACKGROUND="../AddressBook/Arcadia.gif">

<CENTER>
<H1>Remote Data Service Sample Query Page</H1>

<table>
	<tr><td>RDS Server: </td><td><INPUT NAME=Server   SIZE=70> </td></tr>
	<tr><td>Connection: </td><td><INPUT NAME=Connect  SIZE=70> </td></tr>
	<tr><td>Query:      </td><td><INPUT NAME=SQL      SIZE=70> </td></tr>
	<tr><td>Execute Opt:</td><td><INPUT NAME=ExecType SIZE=70> </td></tr>
</table>

<!--Result columns -->
<INPUT TYPE=TEXT NAME=Name0 SIZE=15> <INPUT TYPE=TEXT NAME=COL0 SIZE=30 DATASRC="#DC1"><br>
<INPUT TYPE=TEXT NAME=Name1 SIZE=15> <INPUT TYPE=TEXT NAME=COL1 SIZE=30 DATASRC="#DC1"><br>
<INPUT TYPE=TEXT NAME=Name2 SIZE=15> <INPUT TYPE=TEXT NAME=COL2 SIZE=30 DATASRC="#DC1"><br>
<INPUT TYPE=TEXT NAME=Name3 SIZE=15> <INPUT TYPE=TEXT NAME=COL3 SIZE=30 DATASRC="#DC1"><br>
<INPUT TYPE=TEXT NAME=Name4 SIZE=15> <INPUT TYPE=TEXT NAME=COL4 SIZE=30 DATASRC="#DC1"><br>
<INPUT TYPE=TEXT NAME=Name5 SIZE=15> <INPUT TYPE=TEXT NAME=COL5 SIZE=30 DATASRC="#DC1"><br>
<INPUT TYPE=TEXT NAME=Name6 SIZE=15> <INPUT TYPE=TEXT NAME=COL6 SIZE=30 DATASRC="#DC1"><br>
<INPUT TYPE=TEXT NAME=Name7 SIZE=15> <INPUT TYPE=TEXT NAME=COL7 SIZE=30 DATASRC="#DC1"><br>
<INPUT TYPE=TEXT NAME=Name8 SIZE=15> <INPUT TYPE=TEXT NAME=COL8 SIZE=30 DATASRC="#DC1"><br>
<INPUT TYPE=TEXT NAME=Name9 SIZE=15> <INPUT TYPE=TEXT NAME=COL9 SIZE=30 DATASRC="#DC1">
<HR>

<INPUT TYPE=BUTTON NAME="Requery"   VALUE="Run!">
<INPUT TYPE=BUTTON NAME="MoveFirst" VALUE="First">
<INPUT TYPE=BUTTON NAME="MovePrev"  VALUE="Prev">
<INPUT TYPE=BUTTON NAME="MoveNext"  VALUE="Next">
<INPUT TYPE=BUTTON NAME="MoveLast"  VALUE="Last"> 
<HR>

<INPUT TYPE=BUTTON NAME="Update"    VALUE="Save Changes">
<INPUT TYPE=BUTTON NAME="Cancel"    VALUE="Cancel Changes">
<HR>

<INPUT TYPE=BUTTON NAME="Stop"      VALUE="Cancel Query">
<INPUT TYPE=BUTTON NAME="Asynchoff" VALUE="Turn Asynch off">
<INPUT TYPE=BUTTON NAME="Asynchon"  VALUE="Turn Asynch on">

<OBJECT classid="clsid:BD96C556-65A3-11D0-983A-00C04FC29E33" 
        codebase="HTTP://"<%=Request.ServerVariables("SERVER_NAME")%>/MSADC/mdac20_a.cab#version=2,0,0,0"
        ID=DC1 
        HEIGHT=1 
        WIDTH=1>
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


SUB Window_OnLoad
	Server.Value = "http://<%=Request.ServerVariables("SERVER_NAME")%>"
   	Connect.Value = "DSN=AdvWorks"
   	SQL.Value = "Select * from Products"
   	
	If DC1.ExecuteOptions = adcExecSync Then 
		ExecType.value="Synchronous" 
	Else 
		ExecType.value="Asynchronous"
	End If
END SUB

SUB DC1_OnDataSetChanged
  'Fires after execution is done
  ' Set the names of each field.
  if (DC1.Recordset.Fields.count) > 0 then Name0.Value=DC1.Recordset.Fields(0).name
  if (DC1.Recordset.Fields.count) > 1 then Name1.Value=DC1.Recordset.Fields(1).name
  if (DC1.Recordset.Fields.count) > 2 then Name2.Value=DC1.Recordset.Fields(2).name
  if (DC1.Recordset.Fields.count) > 3 then Name3.Value=DC1.Recordset.Fields(3).name
  if (DC1.Recordset.Fields.count) > 4 then Name4.Value=DC1.Recordset.Fields(4).name
  if (DC1.Recordset.Fields.count) > 5 then Name5.Value=DC1.Recordset.Fields(5).name
  if (DC1.Recordset.Fields.count) > 6 then Name6.Value=DC1.Recordset.Fields(6).name
  if (DC1.Recordset.Fields.count) > 7 then Name7.Value=DC1.Recordset.Fields(7).name
  if (DC1.Recordset.Fields.count) > 8 then Name8.Value=DC1.Recordset.Fields(8).name
  if (DC1.Recordset.Fields.count) > 9 then Name9.Value=DC1.Recordset.Fields(9).name
END SUB

SUB DC1_OnDataSetComplete
  'Fires after fetching is complete
  if (DC1.Recordset.Fields.count) > 0 then COL0.DATAFLD=DC1.Recordset.Fields(0).name
  if (DC1.Recordset.Fields.count) > 1 then COL1.DATAFLD=DC1.Recordset.Fields(1).name
  if (DC1.Recordset.Fields.count) > 2 then COL2.DATAFLD=DC1.Recordset.Fields(2).name
  if (DC1.Recordset.Fields.count) > 3 then COL3.DATAFLD=DC1.Recordset.Fields(3).name
  if (DC1.Recordset.Fields.count) > 4 then COL4.DATAFLD=DC1.Recordset.Fields(4).name
  if (DC1.Recordset.Fields.count) > 5 then COL5.DATAFLD=DC1.Recordset.Fields(5).name
  if (DC1.Recordset.Fields.count) > 6 then COL6.DATAFLD=DC1.Recordset.Fields(6).name
  if (DC1.Recordset.Fields.count) > 7 then COL7.DATAFLD=DC1.Recordset.Fields(7).name
  if (DC1.Recordset.Fields.count) > 8 then COL8.DATAFLD=DC1.Recordset.Fields(8).name
  if (DC1.Recordset.Fields.count) > 9 then COL9.DATAFLD=DC1.Recordset.Fields(9).name  
END SUB

sub Move (strDirection)
	'Custom sub to handle Asyncronous fetching
	'Asynchronous fetching allows you to cancel in the middle of fetching a large
	'recordset
	if DC1.Recordset.State = adcStateClosed then
		if DC1.ReadyState = adcReadyStateComplete then
			msgbox "Query results failed to arrive, please rerun query synchronously and check for errors."
		end if
		if DC1.ReadyState = adcReadyStateLoaded then
			msgbox "Query results have not yet arrived"	
		end if
	else
		if DC1.Recordset.State = adcStateOpen Then	
			select case strDirection
				Case "First"
					DC1.Recordset.MoveFirst
				Case "Next"
					If Not DC1.Recordset.EOF Then
						DC1.Recordset.MoveNext
					End If
				Case "Last"
					DC1.Recordset.MoveLast
				Case "Prev"
					If Not DC1.Recordset.BOF Then
						DC1.Recordset.MovePrevious
					End If
 			end select
		else
     			msgbox "The state is unexpected, an error has occurred"   'Very General error msg. 
   		end if
	end if
End Sub

SUB MoveFirst_OnClick
	'Call to Custom Sub, Move, to handle attempts to move the record pointer during asynch fetches
	move "First"
END SUB

SUB MoveNext_OnClick
	'Call to Custom Sub, Move, to handle attempts to move the record pointer during asynch fetches
	Move "Next"
END SUB

SUB MovePrev_OnClick
	'Call to Custom Sub, Move, to handle attempts to move the record pointer during asynch fetches
	Move "Prev"
END SUB

SUB MoveLast_OnClick
	'Call to Custom Sub, Move, to handle attempts to move the record pointer during asynch fetches
	Move "Last"
END SUB

'Submits edits made and pulls a clean copy of the new data.
SUB Update_OnClick
	If DC1.ReadyState <> adcReadyStateLoaded then
  		DC1.SubmitChanges
		DC1.Refresh
	Else
		MsgBox "Query results still arriving, Please wait"
	End if
END SUB

'Cancel edits and restores original values.
SUB Cancel_OnClick
	If DC1.ReadyState <> adcReadyStateLoaded then
	  	DC1.CancelUpdate
  	Else
		MsgBox "Query results still arriving, Please wait"
	End if
END SUB

SUB Requery_OnClick
	If DC1.ReadyState <> adcReadyStateComplete then
		MsgBox "Query results still arriving, Please wait"
	Else
		DC1.Server = Server.Value
	   	DC1.Connect = Connect.Value
   		DC1.SQL = SQL.Value

		' Clear the column names.
		Name0.Value=""
		Name1.Value=""
		Name2.Value=""
		Name3.Value=""
		Name4.Value=""
		Name5.Value=""
		Name6.Value=""
		Name7.Value=""
		Name8.Value=""
		Name9.Value=""
		
		' Clear the text box bindings
		COL0.DATAFLD=""
		COL1.DATAFLD=""
		COL2.DATAFLD=""
		COL3.DATAFLD=""
		COL4.DATAFLD=""
		COL5.DATAFLD=""
		COL6.DATAFLD=""
		COL7.DATAFLD=""
		COL8.DATAFLD=""
		COL9.DATAFLD=""
		
		' Clear the values  
		COL0.VALUE=""
		COL1.VALUE=""
		COL2.VALUE=""
		COL3.VALUE=""
		COL4.VALUE=""
		COL5.VALUE=""
		COL6.VALUE=""
		COL7.VALUE=""
		COL8.VALUE=""
		COL9.VALUE=""

		DC1.Refresh
	End if
END SUB

SUB Stop_OnClick
  'If an asychronous query is taking too long to execute you can use this to cancel the query
  DC1.Cancel
END SUB

SUB Asynchoff_OnClick
  'In cases where there are problems querying the database you may need to switch to synchronous mode
  'in order to get the error
  DC1.ExecuteOptions = adcExecSync
  DC1.FetchOptions   = adcFetchBackground
  ExecType.value     = "Synchronous" 
END SUB

SUB Asynchon_OnClick
  'In cases where there are problems querying the database you may need to switch to synchronous mode
  'in order to get the error
  DC1.ExecuteOptions = adcExecAsync
  DC1.FetchOptions   = adcFetchAsync
  ExecType.value     = "Asynchronous" 
END SUB

</SCRIPT>
</BODY>
</HTML>
