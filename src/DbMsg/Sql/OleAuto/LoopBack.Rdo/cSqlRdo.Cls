VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "CSqlRdo"
Attribute VB_Creatable = True
Attribute VB_Exposed = True
Option Explicit


'This function uses RDO to call SQL Server and get
'the contents of the authors table.  It returns
'a tabular array equivalent to the rowset
'returned from SQL Server.
'
Public Function RdoGetData(TableName As String, Token As Variant) As Variant
    Dim aRecords As Variant
    Dim cnDatabase As rdoConnection
    Dim rs As rdoResultset
    Dim sConnect As String
    Dim sSQL As String
    Dim iRec As Integer
    
    'Create connection string to SQL Server
    sConnect = "UID=sa;PWD=;DATABASE=pubs"
    
    'The DSN name in this sample is named PUBS; when setting up the ODBC driver for this
    'Data Source, the checkbox "Generate Stored Procedure for Prepared Statement"
    'should NOT be checked
    Set cnDatabase = rdoEngine.rdoEnvironments(0).OpenConnection(dsname:="pubs", _
                                                                 Prompt:=rdDriverNoPrompt, _
                                                                 Connect:=sConnect)
    
    'Bind the extended procedure to the client session
    sSQL = "exec sp_bindsession '" + Token + "'"
    cnDatabase.Execute sSQL, rdExecDirect
    
    'Set the SQL statement to run
    sSQL = "Select * from " + TableName
    Set rs = cnDatabase.OpenResultset(Name:=sSQL, Type:=rdOpenStatic)
    
    'Move to last record in order to count how many
    'records are in the result set.  Then, adjust the
    'array to contain the proper number of rows.
    With rs
        .MoveLast
        .MoveFirst
    End With
    
    'Copy the whole recordset into a variant
    aRecords = rs.GetRows(rs.RowCount)
    
    'Close resultset
    rs.Close
    
    'Close db connection
    cnDatabase.Close
    
    'Return the recordset to the caller as a variant
    RdoGetData = aRecords

End Function



