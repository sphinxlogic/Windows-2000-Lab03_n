Attribute VB_Name = "Module1"
Declare Function GetUserName Lib "advapi32.dll" Alias "GetUserNameA" (ByVal lpBuffer As String, nSize As Long) As Long
Declare Function GetComputerName Lib "kernel32.dll" Alias "GetComputerNameA" (ByVal lpBuffer As String, nSize As Long) As Long
Declare Function GetLastError Lib "kernel32.lib" () As Long

Public Const UNLEN = 256    ' as defined in LMCONS.H
Public Const MAX_COMPUTERNAME_LENGTH = 31 ' as defined in WINBASE.H
