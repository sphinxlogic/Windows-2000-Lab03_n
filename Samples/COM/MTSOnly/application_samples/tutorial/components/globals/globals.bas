Attribute VB_Name = "Globals"
Attribute VB_Ext_KEY = "RVB_UniqueId" ,"335E55F701C5"
Option Explicit
Public Const ERROR_NUMBER = vbObjectError + 0 ' start with an offset that is past system error numbers
Private Const caErrBase As Long = 7000
Public Const caErrCustomerNotFound As Long = vbObjectError + caErrBase + 101
Public Const caErrInvalidLogon As Long = vbObjectError + caErrBase + 201
Public Const caErrCustomerAlreadyOn As Long = vbObjectError + caErrBase + 301
Public Const caErrCustomerNotFoundDesc As String = "The Customer Id you requested could not be found." & vbCrLf & "Please try again."
Public Const caErrInvalidLogonDesc As String = "Invalid Login. Please try again."
Public Const caErrCustomerAlreadyOnDesc As String = "Customer is already logged on."

Private Declare Function GetComputerNameAPI Lib "kernel32" Alias "GetComputerNameA" _
 (ByVal lpBuffer As String, nSize As Long) As Long

Function GetComputerName() As String
    ' Set or retrieve the name of the computer.
    Dim strBuffer As String
    Dim lngLen As Long
  
    strBuffer = Space(255 + 1)
    lngLen = Len(strBuffer)
    If CBool(GetComputerNameAPI(strBuffer, lngLen)) Then
        GetComputerName = Left$(strBuffer, lngLen)
    Else
        GetComputerName = ""
    End If
End Function

Function GetSource(ByVal pstrSource As String, ByVal pstrProc As String, ByVal pstrMod As String) As String
    Dim strFront As String
    Dim strBack As String
  
    strBack = pstrProc & "@" & GetComputerName()
  
    If Left$(pstrMod, (InStr(1, pstrMod, ":") - 1)) = pstrSource Then
        strFront = pstrSource & Mid$(pstrMod, InStr(1, pstrMod, ":"))
    Else
        strFront = "|" & pstrMod
    End If
  
    GetSource = strFront & strBack
End Function

Function SetErrSource(modName As String, procName As String) As String

    SetErrSource = Err.Source & _
                   IIf(Left$(modName, (InStr(1, modName, ".") - 1)) = Err.Source, _
                   Mid$(modName, InStr(1, modName, ".")), "->" & modName) & _
                   "." & procName & "@" & GetComputerName()

End Function

'*************************************************************************************
' RunSp()
' Purpose: Call a stored procedure in the database.
' Inputs:  strFileDSN  -- The name of the DSN file pointing to the database.
'          strSP -- The name of the stored procedure to run.
'          intPRMCount -- The number of parameters sent to the stored procedure.
'          strPRM -- Variant containing the names of the parameters sent.
'          strPRMType -- Variant containing the types of the parameters sent.
'          intPRMLength -- Variant containing the sizes of the parameters sent.
'          strPRMValue -- Variant containing the values of the parameters sent.
' Returns: A recordset containing the information returned by the stored procedure.
'*************************************************************************************
Function RunSp(strFileDSN As String, strSP As String, intPRMCount As Integer, strPRM As Variant, strPRMType As Variant, intPRMLength As Variant, strPRMValue As Variant) As Object

    ' Set up Command and Connection objects
    Dim rs As New ADODB.Recordset
    Dim conn As New ADODB.Connection
    Dim cmd As New ADODB.Command
    Dim prm As ADODB.Parameter
    
    conn.Open "FILEDSN=" & strFileDSN
    Set cmd.ActiveConnection = conn
    cmd.CommandText = strSP
    cmd.CommandType = adCmdStoredProc
    
    Dim i As Integer
    For i = 0 To intPRMCount - 1
        Set prm = cmd.CreateParameter(strPRM(i), strPRMType(i), adParamInput, intPRMLength(i), strPRMValue(i))   'PART OF WAY 1
        cmd.Parameters.Append prm
    Next i
    
    rs.CursorLocation = adUseClient
    rs.Open cmd, , adOpenStatic, adLockBatchOptimistic

    Set RunSp = rs
    
End Function

