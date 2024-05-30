Attribute VB_Name = "Module1"
Global Const APINULL = 0&
Global Const GMEM_FIXED = &H0
Global Const GMEM_ZEROINIT = &H40
Global Const GPTR = (GMEM_FIXED Or GMEM_ZEROINIT)
Global Const ERROR_BUFFER_TOO_SMALL = 603
Global Const RAS_MaxEntryName = 256
Global Const RAS_MaxDeviceType = 16
Global Const RAS_MaxDeviceName = 128

Declare Sub CopyMemory Lib "kernel32" Alias "RtlMoveMemory" ( _
         hpvDest As Any, hpvSource As Any, ByVal cbCopy As Long)

Declare Function GlobalAlloc Lib "kernel32" (ByVal wFlags As Long, ByVal dwBytes As Long) As Long

Declare Function GlobalFree Lib "kernel32" (ByVal hMem As Long) As Long

Public Type RASCONN
    'set dwsize to 412
    dwSize As Long
    hRasConn As Long
    szEntryName(RAS_MaxEntryName) As Byte
    szDeviceType(RAS_MaxDeviceType) As Byte
    szDeviceName(RAS_MaxDeviceName) As Byte
End Type

Public Declare Function RasEnumConnections Lib "RASAPI32.DLL" _
    Alias "RasEnumConnectionsA" ( _
                                 lprasconn As Any, _
                                 lpcb As Long, _
                                 lpcConnections As Long) As Long

Function ByteToString(bytearray() As Byte) As String
    Dim i As Integer, t As String
    i = 0
    t = ""
    While i < UBound(bytearray) And bytearray(i) <> 0
        t = t & Chr$(bytearray(i))
        i = i + 1
    Wend
    ByteToString = t
End Function
