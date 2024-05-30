<HTML>
<HEAD>
<TITLE>RDS Sample Query Page</TITLE>
</HEAD>
<BODY BACKGROUND="../AddressBook/Arcadia.gif">
<CENTER>
<H1>Remote Data Service Sample Query Page</H1>

<BR>
<table>
	<tr><td>RDS Server:<td><INPUT NAME=Server SIZE=70>
	<tr><td>Connection:<td><INPUT NAME=Connect SIZE=70>
	<tr><td>Query:<td><INPUT NAME=SQL SIZE=70>
	</table>
<BR>
<!--Result columns -->
<INPUT TYPE=TEXT NAME=Name0 SIZE=15><INPUT TYPE=TEXT NAME=COL0 SIZE=30 DATASRC="#RDS"><br>
<INPUT TYPE=TEXT NAME=Name1 SIZE=15><INPUT TYPE=TEXT NAME=COL1 SIZE=30 DATASRC="#RDS"><br>
<INPUT TYPE=TEXT NAME=Name2 SIZE=15><INPUT TYPE=TEXT NAME=COL2 SIZE=30 DATASRC="#RDS"><br>
<INPUT TYPE=TEXT NAME=Name3 SIZE=15><INPUT TYPE=TEXT NAME=COL3 SIZE=30 DATASRC="#RDS"><br>
<INPUT TYPE=TEXT NAME=Name4 SIZE=15><INPUT TYPE=TEXT NAME=COL4 SIZE=30 DATASRC="#RDS"><br>
<INPUT TYPE=TEXT NAME=Name5 SIZE=15><INPUT TYPE=TEXT NAME=COL5 SIZE=30 DATASRC="#RDS"><br>
<INPUT TYPE=TEXT NAME=Name6 SIZE=15><INPUT TYPE=TEXT NAME=COL6 SIZE=30 DATASRC="#RDS"><br>
<INPUT TYPE=TEXT NAME=Name7 SIZE=15><INPUT TYPE=TEXT NAME=COL7 SIZE=30 DATASRC="#RDS"><br>
<INPUT TYPE=TEXT NAME=Name8 SIZE=15><INPUT TYPE=TEXT NAME=COL8 SIZE=30 DATASRC="#RDS"><br>
<INPUT TYPE=TEXT NAME=Name9 SIZE=15><INPUT TYPE=TEXT NAME=COL9 SIZE=30 DATASRC="#RDS">
<BR>
<BR>
<INPUT TYPE=BUTTON NAME="Requery" VALUE="Run!">
<INPUT TYPE=BUTTON NAME="MoveFirst" VALUE="First">
<INPUT TYPE=BUTTON NAME="MovePrev" VALUE="Prev">
<INPUT TYPE=BUTTON NAME="MoveNext" VALUE="Next">
<INPUT TYPE=BUTTON NAME="MoveLast" VALUE="Last"> <BR><BR>
<INPUT TYPE=BUTTON NAME="Update" VALUE="Save Changes">
<INPUT TYPE=BUTTON NAME="Cancel" VALUE="Cancel Changes">
<BR><BR>
<INPUT TYPE=BUTTON NAME="Stop" VALUE="Cancel Query">
<INPUT TYPE=BUTTON NAME="Asynchoff" VALUE="Turn Asynch off">
<INPUT TYPE=BUTTON NAME="Asynchon" VALUE="Turn Asynch on">
</CENTER>

<OBJECT classid="clsid:BD96C556-65A3-11D0-983A-00C04FC29E33"
     codebase="HTTP://<%=Request.ServerVariables("SERVER_NAME")%>/MSADC/mdac20_a.cab#version=2,0,0,0"
    ID=RDS HEIGHT=1 WIDTH = 1>
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

'---- enum Values ----
Const adErrNoCurrentRecord = 3021

SUB Window_OnFocus

'	if window.navigator.appversion >= "4.0" and window.navigator.appname >= "Microsoft" then
'		if window.navigator.cpuclass="x86" then
'			nextpage = "adctest.asp"
'			window.navigate nextpage
'		end if
'	end if

END SUB

SUB Window_OnLoad

	Dim sProvider
	Dim sDataSrc
	Dim sDataSrcPath
	Dim sConnString
    
	sProvider = "Microsoft.Jet.OLEDB.3.51"
  
' The following lines assign a value to the datasource parameter of the connection string.
' The code derives the path from the URL path of this asp file. 
' The default is C:\Program Files\Platform SDK\samples\dataaccess\rds.
' If the advWorks.mdb file is located somewhere else on your web server, 
'  replace sDataSrc value with the correct path on your web server.
 
	sDataSrcPath = "<%= Left(Request.ServerVariables("PATH_TRANSLATED"), InStrRev(Request.ServerVariables("PATH_TRANSLATED"),"\"))%>"
  	sDataSrc  = sDataSrcPath & "AdvWorks.mdb"

	sConnString = "Provider=" & sProvider & ";Data Source=" & sDataSrc & ";"

  
	Server.Value = "http://<%=Request.ServerVariables("SERVER_NAME")%>"
   	Connect.Value = sConnString
   	SQL.Value = "Select * from Products"

END SUB


SUB RDS_OnDataSetChanged

  'Fires after execution is done
  ' Set the names of each field.
  if (RDS.Recordset.Fields.count) > 0 then Name0.Value=RDS.Recordset.Fields(0).name
  if (RDS.Recordset.Fields.count) > 1 then Name1.Value=RDS.Recordset.Fields(1).name
  if (RDS.Recordset.Fields.count) > 2 then Name2.Value=RDS.Recordset.Fields(2).name
  if (RDS.Recordset.Fields.count) > 3 then Name3.Value=RDS.Recordset.Fields(3).name
  if (RDS.Recordset.Fields.count) > 4 then Name4.Value=RDS.Recordset.Fields(4).name
  if (RDS.Recordset.Fields.count) > 5 then Name5.Value=RDS.Recordset.Fields(5).name
  if (RDS.Recordset.Fields.count) > 6 then Name6.Value=RDS.Recordset.Fields(6).name
  if (RDS.Recordset.Fields.count) > 7 then Name7.Value=RDS.Recordset.Fields(7).name
  if (RDS.Recordset.Fields.count) > 8 then Name8.Value=RDS.Recordset.Fields(8).name
  if (RDS.Recordset.Fields.count) > 9 then Name9.Value=RDS.Recordset.Fields(9).name

END SUB


SUB RDS_OnDataSetComplete
  'Fires after fetching is complete
  if (RDS.Recordset.Fields.count) > 0 then COL0.DATAFLD=RDS.Recordset.Fields(0).name
  if (RDS.Recordset.Fields.count) > 1 then COL1.DATAFLD=RDS.Recordset.Fields(1).name
  if (RDS.Recordset.Fields.count) > 2 then COL2.DATAFLD=RDS.Recordset.Fields(2).name
  if (RDS.Recordset.Fields.count) > 3 then COL3.DATAFLD=RDS.Recordset.Fields(3).name
  if (RDS.Recordset.Fields.count) > 4 then COL4.DATAFLD=RDS.Recordset.Fields(4).name
  if (RDS.Recordset.Fields.count) > 5 then COL5.DATAFLD=RDS.Recordset.Fields(5).name
  if (RDS.Recordset.Fields.count) > 6 then COL6.DATAFLD=RDS.Recordset.Fields(6).name
  if (RDS.Recordset.Fields.count) > 7 then COL7.DATAFLD=RDS.Recordset.Fields(7).name
  if (RDS.Recordset.Fields.count) > 8 then COL8.DATAFLD=RDS.Recordset.Fields(8).name
  if (RDS.Recordset.Fields.count) > 9 then COL9.DATAFLD=RDS.Recordset.Fields(9).name  

END SUB


sub Move (strDirection)
	'Custom sub to handle Asyncronous fetching
	'Asynchronous fetching allows you to cancel in the middle of fetching a large
	'recordset
	if RDS.Recordset.State = adcStateClosed then
		if RDS.ReadyState = adcReadyStateComplete then
			msgbox "Query results failed to arrive, please rerun query synchronously and check for errors."
		end if
		if RDS.ReadyState = adcReadyStateLoaded then
			msgbox "Query results have not yet arrived"	
		end if
	else
		if RDS.Recordset.State = adcStateOpen then	
			
			select case strDirection
				Case "First"
					If Not RDS.Recordset.EOF Then
						RDS.Recordset.MoveFirst
					End If
					
				Case "Next"
					RDS.Recordset.MoveNext
					
				Case "Last"
					RDS.Recordset.MoveLast
					
				Case "Prev"
					If Not RDS.Recordset.BOF Then
						RDS.Recordset.MovePrevious
					End If
 			end select
 			
			end if
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
	If RDS.ReadyState <> adcReadyStateLoaded then
  		RDS.SubmitChanges
		RDS.Refresh
		
	Else
		MsgBox "Query results still arriving, Please wait"
	End if
	
END SUB

'Cancel edits and restores original values.
SUB Cancel_OnClick
	if RDS.ReadyState <> adcReadyStateLoaded then
	  	RDS.CancelUpdate
  	
	Else
		MsgBox "Query results still arriving, Please wait"
	End if

END SUB

SUB Requery_OnClick
	If RDS.ReadyState <> adcReadyStateComplete then
		MsgBox "Query results still arriving, Please wait"
	Else
		RDS.Server = Server.Value
	   	RDS.Connect = Connect.Value
   		RDS.SQL = SQL.Value

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
		' clear the values  
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

		RDS.Refresh
		
	End if


END SUB

SUB Stop_OnClick
  'If an asychronous query is taking too long to execute you can use this to cancel the query
  RDS.Cancel

END SUB

SUB Asynchoff_OnClick
  'In cases where there are problems querying the database you may need to switch to synchronous mode
  'in order to get the error
  RDS.ExecuteOptions = adcExecSync
  RDS.FetchOptions = adcFetchBackground

END SUB

SUB Asynchon_OnClick
  'In cases where there are problems querying the database you may need to switch to synchronous mode
  'in order to get the error
  RDS.ExecuteOptions = adcExecAsync
  RDS.FetchOptions = adcFetchAsync

END SUB

</SCRIPT>
</BODY>
</HTML>
