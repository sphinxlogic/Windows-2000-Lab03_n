VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "TableQueue"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Public ConnectionString As String  ' OLE DB Connection String
Attribute ConnectionString.VB_VarDescription = "The OLE-DB connection string"

'--- Probably not transacted, but we can use the MTS object here
Private MTS As New MTSEnvironment

Private Sub Class_Initialize()
  ConnectionString = "DSN=FmLib"
End Sub

' Number of items in queue by book number
Public Property Get Length(ByVal Bib As Long)
Attribute Length.VB_Description = "Number of requests in the queue"
  Dim cmd As ADODB.Command
  Dim params As ADODB.Parameters
  
  On Error GoTo ErrHandler
  
  Set cmd = MTS.CreateInstance("ADODB.Command")
  With cmd
      .ActiveConnection = ConnectionString
      .CommandTimeout = 90
      
      .CommandText = "fm_queue_length"
      .CommandType = adCmdStoredProc
      
      'Pass Arguments to stored procedure
      Set params = .Parameters
      params.Append .CreateParameter("retval", adInteger, adParamReturnValue, 8)
      params.Append .CreateParameter("@bibNo", adInteger, adParamInput, 8, Bib)
      
      'Execute the command
      .Execute
  End With
  
  'Return value
  Length = params("retval")
  
  'Release the memory
  Set cmd = Nothing
  Exit Property

ErrHandler:
    Err.Raise Err.Number, Err.Source, Err.Description
End Property

' Add request to queue
Public Function Enqueue(ByVal Bib As Long, ByVal borrower As Long, Optional ByVal Location As String, Optional ByVal comment As String) As Long
Attribute Enqueue.VB_Description = "Add user request to end of queue"
  Dim cmd As ADODB.Command
  Dim params As ADODB.Parameters
  
  On Error GoTo ErrHandler
  
  Set cmd = MTS.CreateInstance("ADODB.Command")
  With cmd
      .ActiveConnection = ConnectionString
      .CommandTimeout = 90
      
      .CommandText = "fm_queue_enqueue"
      .CommandType = adCmdStoredProc
      
      'Pass arguments to stored procedures
      Set params = .Parameters
      
      params.Append .CreateParameter("retval", adInteger, adParamReturnValue)
      params.Append .CreateParameter("@borrowerNo", adInteger, adParamInput, 0, borrower)
      params.Append .CreateParameter("@bibNo", adInteger, adParamInput, 0, Bib)
      params.Append .CreateParameter("@Location", adVarChar, adParamInput, 255, Location)
      params.Append .CreateParameter("@Comment", adVarChar, adParamInput, 255, comment)
      
      'Execute the command
      .Execute
  End With
  
  'Set return value
  Enqueue = params("retval")

  'Release the memory
  Set cmd = Nothing
  Exit Function
  
ErrHandler:
  Err.Raise Err.Number, Err.Source, Err.Description
End Function

' Get next request from queue
Public Sub Dequeue(ByVal Bib As Long, ByRef BorrowerNo As Variant, ByRef Location As Variant, ByRef Comments As Variant)
Attribute Dequeue.VB_Description = "Get first request from queue"
  Dim cmd As ADODB.Command
  Dim params As ADODB.Parameters
  
  On Error GoTo ErrHandler
  
  Set cmd = MTS.CreateInstance("ADODB.Command")
  With cmd
      .ActiveConnection = ConnectionString
      .CommandTimeout = 90
      
      .CommandText = "fm_queue_dequeue"
      .CommandType = adCmdStoredProc
      
      'Pass arguments to stored procedures
      Set params = .Parameters
      params.Append .CreateParameter("@bibNo", adInteger, adParamInput, 8, Bib)
      params.Append .CreateParameter("@borrowerNo", adInteger, adParamOutput, 8)
      params.Append .CreateParameter("@location", adVarChar, adParamOutput, 64)
      params.Append .CreateParameter("@comment", adVarChar, adParamOutput, 255)
      
      'Execute the command
      .Execute
  End With
  
  BorrowerNo = params("@borrowerNo")
  Location = params("@location")
  Comments = params("@comment")
  
  'Release the memory
  Set cmd = Nothing
  Exit Sub

ErrHandler:
  Err.Raise Err.Number, Err.Source, Err.Description
End Sub

' Cancel user request from queue
Public Sub Cancel(ByVal Bib As Long, ByVal borrower As Long)
Attribute Cancel.VB_Description = "Remove user request from queue"
  Dim cmd As ADODB.Command
  Dim params As ADODB.Parameters
  
  On Error GoTo ErrHandler
  
  Set cmd = MTS.CreateInstance("ADODB.Command")
  With cmd
      .ActiveConnection = ConnectionString
      .CommandTimeout = 90
      
      .CommandText = "fm_queue_cancel"
      .CommandType = adCmdStoredProc
      
      'Pass arguments to stored procedures
      Set params = .Parameters
      
      params.Append .CreateParameter("@borrowerNo", adInteger, adParamInput, 8, borrower)
      params.Append .CreateParameter("@bibNo", adInteger, adParamInput, 8, Bib)
      
      'Execute the command
      .Execute
  End With
  
  'Release the memory
  Set cmd = Nothing
  Exit Sub

ErrHandler:
  Err.Raise Err.Number, Err.Source, Err.Description
End Sub

' Returns user location in queue
Public Property Get Position(ByVal Bib As Long, ByVal borrower As Long)
Attribute Position.VB_Description = "Offset from beginning of queue"
  Dim cmd As ADODB.Command
  Dim params As ADODB.Parameters
  
  On Error GoTo ErrHandler
  
  Set cmd = MTS.CreateInstance("ADODB.Command")
  With cmd
      .ActiveConnection = ConnectionString
      .CommandTimeout = 90
      
      .CommandText = "fm_queue_location"
      .CommandType = adCmdStoredProc
      
      'Pass arguments to stored procedures
      Set params = .Parameters
      params.Append .CreateParameter("retval", adInteger, adParamReturnValue, 8)
      params.Append .CreateParameter("@borrowerNo", adInteger, adParamInput, 8, borrower)
      params.Append .CreateParameter("@bibNo", adInteger, adParamInput, 8, Bib)
      
      'Execute the command
      .Execute
  End With
  
  'Set return value
  Position = params("retval")
  
  'Release the memory
  Set cmd = Nothing
  Exit Property
  
ErrHandler:
    Err.Raise Err.Number, Err.Source, Err.Description
End Property

