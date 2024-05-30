VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "CSqlDao"
Attribute VB_Creatable = True
Attribute VB_Exposed = True
Option Explicit

'This function uses DAO to call SQL Server and get
'the contents of the input table name provided to
'the DAO table.  It returns a tabular array equivalent
'to the rowset returned from SQL Server.

Public Function DaoGetData(TableName As String, Token As Variant) As Variant
    Dim aRecords As Variant
    Dim dbDatabase As Database
    Dim rs As Recordset
    Dim sConnect As String
    Dim sSQL As String
    
    'Create connection string to SQL Server
    sConnect = "ODBC;DSN=pubs;DATABASE=pubs;UID=sa;PWD=;"
    Set dbDatabase = Workspaces(0).OpenDatabase("", False, False, sConnect)
    
    'Bind the extended procedure to the client session
    sSQL = "exec sp_bindsession '" + Token + "'"
    dbDatabase.Execute sSQL, dbSQLPassThrough
    
    'Set the SQL statement to run
    sSQL = "Select * from " + TableName
    Set rs = dbDatabase.OpenRecordset(sSQL, Type:=dbOpenSnapshot)
    
    'Move to last record in order to count how many
    'records are in the result set.
    With rs
        .MoveLast
        .MoveFirst
    End With
    
    'Get all the rows in the recordset and put them in a variant array
    aRecords = rs.GetRows(rs.RecordCount)
  
    'Close resultset
    rs.Close
    
    'Close db connection
    dbDatabase.Close
    
    'Return the recordset to the caller in the form
    'of a variant array
    DaoGetData = aRecords
   
End Function



