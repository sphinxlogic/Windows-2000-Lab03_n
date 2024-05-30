VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "CGetNPV"
Attribute VB_Creatable = True
Attribute VB_Exposed = True
 Public MyProperty As String
 
 



Public Function GetNPV(Cost, RetRate, Pmt0, Pmt1, Pmt2, Pmt3, Pmt4) As Currency
    
    Static Values(5) As Double  ' Set up array.
    'put input vars into array
    Values(0) = Pmt0
    Values(1) = Pmt1
    Values(2) = Pmt2
    Values(3) = Pmt3
    Values(4) = Pmt4
    
    ' Calculate net present value (assume cost start today) .
    GetNPV = NPV(RetRate, Values()) - Cost
    
End Function


Public Function TestError() As Long

    TestError = 1
    
    'following statement generates a runtime error that is retrieved by sp_OAErrInfo
    'If running in the VB environment (for debugging) you must set
    'Tools.Options.Advanced to "Break on unhandled errors" for error to propogate
    
    Err.Raise vbObjectError + 1, "GetNPV.CGetNPV", "runtime error in code"

End Function

Private Sub Class_Initialize()
'Any unhandled run-time errors in an Initialize or Terminate function of an in-proc
'OLE Server can cause the calling application (i.e. SQL Server) to stop.
'So if there is any code that could generate a runtime error in Initialize,
'add an error handler.
On Error GoTo initerrhandler
    MyProperty = 0
    'uncomment this next line to generate a runtime error
    'Err.Raise vbObjectError + 2, "GetNPV.CGetNPV", "Error in Initialize"
    MyProperty = "Success"
    Exit Sub
    
initerrhandler:
    MyProperty = Err.Description

End Sub





