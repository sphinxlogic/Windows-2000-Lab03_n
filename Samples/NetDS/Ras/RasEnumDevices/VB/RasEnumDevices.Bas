Attribute VB_Name = "Module1"
Option Explicit

' Constants for RASDEVINFO
Global Const RAS_MaxDeviceType = 16
Global Const RAS_MaxDeviceName = 128

' Constants for GlobalAlloc
Global Const GMEM_FIXED = &H0
Global Const GMEM_ZEROINIT = &H40
Global Const GPTR = (GMEM_FIXED Or GMEM_ZEROINIT)

Global Const ApINULL = 0&

' Type definition for RASDEVINFO
Type RASDEVINFO
    dwSize As Long
    szDeviceType(RAS_MaxDeviceType) As Byte
    szDeviceName(RAS_MaxDeviceName) As Byte
End Type

' Function prototype for RasEnumDevices
Declare Function RasEnumDevices Lib "rasapi32.dll" Alias "RasEnumDevicesA" ( _
    lpRasDevInfo As Any, _
    lpcb As Long, _
    lpcDevices As Long) As Long
    
' Function prototype for RtlMoveMemory
Declare Sub CopyMemory Lib "kernel32" Alias "RtlMoveMemory" ( _
         hpvDest As Any, hpvSource As Any, ByVal cbCopy As Long)
         
' Function prototype for GlobalAlloc
Declare Function GlobalAlloc Lib "kernel32" (ByVal wFlags As Long, ByVal dwBytes As Long) As Long

' Function prototype for GlobalFree
Declare Function GlobalFree Lib "kernel32" (ByVal hMem As Long) As Long

' Subroutine to list the RAS capable devices
Sub GetDevices(lst As ComboBox)
    Dim lpRasDevInfo As RASDEVINFO
    Dim lpcb As Long
    Dim cDevices As Long
    Dim t_Buff As Long
    Dim nRet As Long
    Dim t_ptr As Long
    Dim i As Long
    
    lpcb = 0
    ' Initialize the dwSize field
    lpRasDevInfo.dwSize = LenB(lpRasDevInfo) + (LenB(lpRasDevInfo) Mod 4)
    
    ' Call RasEnumDevices with lpcb = 0 to find out the required
    ' input buffer size
    nRet = RasEnumDevices(ByVal 0, lpcb, cDevices)
    
    ' Allocate input buffer with required size
    t_Buff = GlobalAlloc(GPTR, lpcb)
    
    ' Initialize the first entry
    CopyMemory ByVal t_Buff, lpRasDevInfo, LenB(lpRasDevInfo)
    
    ' Call RasEnumDevices to enumerate the RAs capable devices
    nRet = RasEnumDevices(ByVal t_Buff, lpcb, lpcb)

    If nRet = 0 Then ' RasEnumDevices retunred no errors
        t_ptr = t_Buff
        ' List the entries into the combo box
        For i = 0 To cDevices - 1
            CopyMemory lpRasDevInfo, ByVal t_ptr, LenB(lpRasDevInfo)
            lst.AddItem (ByteToString(lpRasDevInfo.szDeviceName))
            t_ptr = t_ptr + lpRasDevInfo.dwSize
        Next i
    Else ' RasEnumDevices retunred an error
        MsgBox nRet
    End If
    
    ' Free the allocated input buffer
    If t_Buff <> 0 Then GlobalFree (t_Buff)

End Sub

' This function takes in a Byte array and converts into a String
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
