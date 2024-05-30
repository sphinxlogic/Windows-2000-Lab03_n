Attribute VB_Name = "modRasDial"
Option Explicit

'Global constant declarations
Global Const APINULL = 0&
Global Const MaxEntryName = 256
Global Const RAS_MaxPhoneNumber = 128
'Global Const
Global Const MaxCallbackNumber = RAS_MaxPhoneNumber
Global Const UNLEN = 256
Global Const PWLEN = 256
Global Const DNLEN = 18
Global Const NOT_SUPPORTED = 120&
Global Const RAS_MaxIpAddress = 15
Global Const RASP_PppIp = &H8021&

'Declaration for lstrcpy() API
Declare Function lstrcpy Lib "kernel32" Alias "lstrcpyA" _
    (lpString1 As Any, ByVal lpString2 As String) As Long
    
'Declaration for RasDial() API
Declare Function RasDial Lib "rasapi32" Alias "RasDialA" _
    (ByVal lpRasDialExtensions As Long, _
     ByVal lpszPhonebook As String, _
     lpRasDialParams As RasDialParams, _
     ByVal dwNotifierType As Long, _
     ByVal lpvNotifier As Long, _
     lphRasConn As Long) As Long
    
'Declaration for RasHangUp() API
Declare Function RasHangUp Lib "rasapi32" Alias "RasHangUpA" _
    (ByVal hRasConn As Long) As Long
    
'Declaration for RasGetErrorString() API
Declare Function RasGetErrorString Lib "rasapi32" Alias "RasGetErrorStringA" _
    (ByVal uErrorValue As Long, _
     ByVal lpszErrorString As String, _
     ByVal cBufSize As Long) As Long
     
'Declaration for RasGetProjectionInfo() API
Declare Function RasGetProjectionInfo Lib "rasapi32" Alias "RasGetProjectionInfoA" _
    (ByVal hRasConn As Long, _
     ByVal rasprojection As Long, _
     lpProjection As RASPPPIP, _
     lpcb As Long) As Long

'Type declaration for RASDIALPARAM structure
Public Type RasDialParams
    dwSize As Long
    szEntryName(MaxEntryName) As Byte
    szPhoneNumber(RAS_MaxPhoneNumber) As Byte
    szCallbackNumber(MaxCallbackNumber) As Byte
    szUserName(UNLEN) As Byte
    szPassword(PWLEN) As Byte
    szDomain(DNLEN) As Byte
End Type

'Type declaration for RASPPPIP structure
Public Type RASPPPIP
    'set dwsize to 40
    dwSize As Long
    dwError As Long
    szIpAddress(RAS_MaxIpAddress) As Byte
    szServerIpAddress(RAS_MaxIpAddress) As Byte
End Type

Global Const Ras_MaxDeviceName = 128
Global Const RAS_MaxDeviceType = 16

Type RASCONNSTATUS

    dwSize As Long
    rasconnstate As Long
    dwError As Long
    szDeviceType(RAS_MaxDeviceType) As Byte
    szDeviceName(Ras_MaxDeviceName) As Byte
End Type
      

Public Const ERROR_INVALID_HANDLE = 6&
Declare Function GetTickCount Lib "kernel32" () As Long
Declare Sub Sleep Lib "kernel32" (ByVal dwMilliseconds As Long)
   
Declare Function RasGetConnectStatus Lib "rasapi32" Alias "RasGetConnectStatusA" _
    (ByVal hRasConn As Long, _
     lpRasConnStatus As RASCONNSTATUS) As Long

'RasHangUp function
Function fcnRasHangUp(hRasConn As Long) As Long
    Dim tmpRasConnStatus As RASCONNSTATUS
    Dim tcLast As Long
    Dim dwRet As Long
    
    fcnRasHangUp = RasHangUp(hRasConn)
    tcLast = GetTickCount + 10000
    tmpRasConnStatus.dwSize = LenB(tmpRasConnStatus)
    RasHangUp (hRasConn)
    Do
        dwRet = RasGetConnectStatus(hRasConn, tmpRasConnStatus)
        If dwRet = ERROR_INVALID_HANDLE Then Exit Do
        If tcLast < GetTickCount Then Exit Do
        Sleep 50
    Loop
    
End Function

' RasGetErrorString function
Function fcnRasErrorString(lngRasErrorNumber As Long) As String
    Dim lngnRet As Long
    Dim strRasErrorString As String
    
    strRasErrorString = Space$(256)
    
    Select Case lngRasErrorNumber
        Case Is >= 600 ' Ras Error
            lngnRet = RasGetErrorString _
                        (lngRasErrorNumber, _
                         strRasErrorString, _
                         256&)
            If lngnRet Then
                fcnRasErrorString = "Call to RasGetErrorString Failed"
            Else
                fcnRasErrorString = strRasErrorString
            End If
        Case 0 ' No Error
            fcnRasErrorString = "Ras Connected"
        Case NOT_SUPPORTED
            fcnRasErrorString = "Function is not supported on this version of Windows"
        Case Else
            fcnRasErrorString = "Unexpected Error"
    End Select
End Function

'RasDial function
Function fcnRasDial(PhoneNumber As String, _
                    CallBackNumber As String, _
                    UserName As String, _
                    Password As String, _
                    Domain As String, _
                    hRasConn As Long) As Long
    Dim lngnRet As Long
    Dim MyRasDialParams As RasDialParams
    Dim OldMouse
        
    ' Fill in the RASDIALPARAMS structure
    MyRasDialParams.dwSize = LenB(MyRasDialParams)
    lngnRet = lstrcpy(MyRasDialParams.szEntryName(0), "")
    lngnRet = lstrcpy(MyRasDialParams.szPhoneNumber(0), PhoneNumber)
    lngnRet = lstrcpy(MyRasDialParams.szCallbackNumber(0), CallBackNumber)
    lngnRet = lstrcpy(MyRasDialParams.szUserName(0), UserName)
    lngnRet = lstrcpy(MyRasDialParams.szPassword(0), Password)
    lngnRet = lstrcpy(MyRasDialParams.szDomain(0), Domain)
        
    OldMouse = Screen.MousePointer
    Screen.MousePointer = vbHourglass
    ' Call RasDial
    fcnRasDial = RasDial(0, vbNullString, _
                         MyRasDialParams, 0, ByVal 0, hRasConn)
    Screen.MousePointer = OldMouse
End Function

' RasGetProjectionInfo function
Function fcnRasGetProjectionInfo(lnghRasConn As Long, _
                                 strIpAddress() As Byte, _
                                 strServerIpAddress() As Byte) _
                                 As Long
    Dim lpProjection As RASPPPIP
    Dim lpcb As Long
    Dim lngnRet As Long
    Dim rasprojection As Long
    Dim i
    
    ' Fill in the RASPPPIP structure
    rasprojection = RASP_PppIp
    lpProjection.dwSize = 40
    lpcb = 40
    
    ' Call RasGetProjectionInfo
    lngnRet = RasGetProjectionInfo(lnghRasConn, _
                    rasprojection, lpProjection, lpcb)
    If lngnRet Then
        fcnRasGetProjectionInfo = lngnRet
    Else
        ' Return the IP addresses in the arguments
        For i = 0 To 15
            strIpAddress(i) = lpProjection.szIpAddress(i)
            strServerIpAddress(i) = lpProjection.szServerIpAddress(i)
        Next i
        fcnRasGetProjectionInfo = 0
    End If
End Function
