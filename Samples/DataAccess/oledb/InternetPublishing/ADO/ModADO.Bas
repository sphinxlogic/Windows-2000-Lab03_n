Attribute VB_Name = "modADO"
Public Function Download(ByRef szURL As String, _
                         ByRef szFilePath As String, _
                         Optional szUsername As String = "", _
                         Optional szPassword As String = "" _
                        ) As Long
    ' local variables
    Dim szItemName As String
    Dim nLoc As Integer
    
    ' objects
    Dim con As ADODB.Connection
    Dim rec As ADODB.Record
    Dim stm As ADODB.Stream
    
    ' start trapping errors
    On Error GoTo ErrHandler
    
    ' create the objects
    Set con = CreateObject("ADODB.Connection")
    Set rec = CreateObject("ADODB.Record")
    Set stm = CreateObject("ADODB.Stream")

    ' setup the connection object
    con.Provider = "MSDAIPP.DSO"
    con.ConnectionString = szURL
    
    ' connect
    If (szUsername <> "") Then
        con.Open , szUsername, szPassword
    Else
        con.Open
    End If
    
    ' setup the record object
    rec.Mode = adModeRead
    
    ' open the record object
    rec.Open "", con

    ' open the stream
    Set stm = rec.Fields(adDefaultStream).Value
    
    ' setup the stream
    stm.Type = adTypeBinary

    ' upload from the local file to the stream
    stm.SaveToFile szFilePath, adSaveCreateOverWrite

    ' everything was cool, return 0
    Download = 0

    GoTo CleanUp

ErrHandler:
    Download = Err.Number

CleanUp:
    ' close the objects if they're still open
    If (adStateOpen = stm.State) Then
        stm.Close: End If
    If (adStateOpen = rec.State) Then
        rec.Close: End If
    If (adStateOpen = con.State) Then
        con.Close: End If

    ' release the objects
    Set stm = Nothing
    Set rec = Nothing
    Set con = Nothing

End Function


                         
Public Function Enumerate(ByRef szURL As String, _
                          Optional szUsername As String = "", _
                          Optional szPassword As String = "" _
                         ) As Long
    ' objects
    Dim rs As ADODB.Recordset
    Dim con As ADODB.Connection
    
    On Error GoTo ErrHandler
    
    ' create the objects
    Set rs = CreateObject("ADODB.Recordset")
    Set con = CreateObject("ADODB.Connection")
    
    ' set up the connection object
    con.Mode = adModeRead
    con.Provider = "MSDAIPP.DSO"
    con.ConnectionString = "Data Source=" + szURL
    
    ' open the connection
    If (szUsername <> "") Then
        con.Open , szUsername, szPassword
    Else
        con.Open
    End If
    
    ' open the recordset to the url
    rs.Open szURL, con, adOpenForwardOnly, adLockPessimistic, adCmdURLBind
    
    ' walk through the recordset and display all the names
    rs.MoveFirst
    Do

        If (rs.Fields(12).Value = True) Then
            frmMain.txtOutput.Text = frmMain.txtOutput.Text + _
                "  (+)" + rs.Fields(15).Value + vbCrLf
        Else
            frmMain.txtOutput.Text = frmMain.txtOutput.Text + _
                "      " + rs.Fields(15).Value + vbCrLf
        End If
        rs.MoveNext
    Loop While (rs.EOF <> True)
    
    GoTo CleanUp

ErrHandler:
    Enumerate = Err.Number
    
CleanUp:
    ' close the objects if they are open
    If (adStateOpen = rs.State) Then
        rs.Close: End If
    If (adStateOpen = con.State) Then
        con.Close: End If

    ' release the objects
    Set rs = Nothing
    Set con = Nothing

End Function


Public Function Upload(ByRef szURL As String, _
                         ByRef szFilePath As String, _
                         Optional szUsername As String = "", _
                         Optional szPassword As String = "" _
                        ) As Long
    On Error GoTo ErrHandler
    
    ' objects
    Dim rec As ADODB.Record
    Dim stm As ADODB.Stream
    
    ' create the objects
    Set rec = CreateObject("ADODB.Record")
    Set stm = CreateObject("ADODB.Stream")

    ' create the file if it doesn't exist
    rec.Mode = adModeReadWrite
    rec.Open szURL, , , adCreateNonCollection Or adCreateOverwrite
    If (adStateOpen = rec.State) Then
        rec.Close: End If

    ' setup the stream object
    stm.Type = adTypeBinary
    
    ' connect
    If (szUsername <> "") Then
        stm.Open szURL, adModeWrite Or adModeShareDenyWrite, , szUsername, szPassword
    Else
        stm.Open szURL, adModeWrite Or adModeShareDenyWrite
    End If
    
    ' upload from the local file to the stream
    stm.LoadFromFile szFilePath

    ' everything was cool, return 0
    Upload = 0

    GoTo CleanUp

ErrHandler:
    Upload = Err.Number

CleanUp:
    ' close the objects if they're still open
    If (adStateOpen = stm.State) Then
        stm.Close: End If

    ' release the objects
    Set stm = Nothing
    Set rec = Nothing

End Function


