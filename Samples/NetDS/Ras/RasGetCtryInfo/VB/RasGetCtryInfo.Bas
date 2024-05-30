Attribute VB_Name = "Module1"
Global Const GMEM_FIXED = &H0
Global Const GMEM_ZEROINIT = &H40
Global Const GPTR = (GMEM_FIXED Or GMEM_ZEROINIT)

'Declaration for RtlMoveMemory()
Declare Sub CopyMemory Lib "kernel32" Alias "RtlMoveMemory" ( _
         hpvDest As Any, hpvSource As Any, ByVal cbCopy As Long)

'Declaration for GlobalAlloc()
Declare Function GlobalAlloc Lib "kernel32" (ByVal wFlags As Long, ByVal dwBytes As Long) As Long

'Declaration for GlobalFree()
Declare Function GlobalFree Lib "kernel32" (ByVal hMem As Long) As Long

'Declaration for lstrcpy() API
Declare Function lstrcpy Lib "kernel32" Alias "lstrcpyA" _
    (lpString1 As Any, ByVal lpString2 As String) As Long
    
'Type declaration for RASCTRYINFO structure
Public Type RASCTRYINFO
    dwSize As Long
    dwCountryID As Long
    dwNextCountryID As Long
    dwCountryCode As Long
    dwCountryNameOffset As Long
End Type

'Declaration fro RasGetCountryInfo() API
Declare Function RasGetCountryInfo Lib "rasapi32" Alias _
    "RasGetCountryInfoA" (lpRasCtryInfo As Long, _
                          lpdwSize As Long) As Long

'ByteToString() accepts a Byte array and converts it into a string
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
