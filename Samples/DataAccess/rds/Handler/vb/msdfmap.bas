'-----------------------------------------------------------------------------
'
' File:         msdfmap.bas
'
' Copyright:    Copyright (c) 1998-1999 Microsoft Corporation
'
' Contents:
'
' Comments:
'
'-----------------------------------------------------------------------------

Attribute VB_Name = "Module1"
Private Declare Function GetUserNameA Lib "advapi32.dll" (ByVal name As String, ByRef length As Long) As Long
Private Declare Function GetPrivateProfileStringA Lib "kernel32.dll" (ByVal sectionName As String, ByVal KeyName As String, ByVal default As String, ByVal ReturnedString As String, ByVal Size As Long, ByVal fileName As String) As Long
Private iniFile As String

'
'SetIniName()
'  Set the name of the INI file.
'
Public Sub SetIniFile(fileName As String)
    'Nothing specified means use the default.
    If fileName = "" Then
        fileName = "msdfmap.ini"
    End If

    'Don't allow a path
    If InStr(1, fileName, ":") > 0 Or InStr(1, fileName, "\") > 0 Then
        'E_ACCESSDENIED
        Call Err.Raise(&H80070005, , "Handler argument can't specify a path.")
    End If

    'Set the name of the INI file to use.
    iniFile = fileName
End Sub


'
'GetUserName()
'  Returns the current user name.
'  It may be the anynomous guest user name
'  or it may be a verified remote user name.
'  It calls the Win32 GetUserName function.
'
Public Function GetUserName() As String
    Dim username As String
    Dim namelen As Long
    Dim rc As Long
    Dim nullOffset As Integer
    
    namelen = 256
    username = String(namelen, Chr$(0))
    rc = GetUserNameA(username, namelen)
    If rc <> 0 Then
        nullOffset = InStr(1, username, Chr$(0))
        If nullOffset > 0 Then
            username = Left$(username, nullOffset - 1)
        End If
    Else
        username = ""
    End If
    GetUserName = username
End Function

'
'SubstituteParameters(str,parms)
'  Replaces each "?" in "str" with the corresponding
'  parameter in the comma separated list in "parms".
'
Public Function SubstituteParameters(str As String, parms As String) As String
    Dim strOffset As Integer
    Dim parmOffset As Integer
    Dim parmLen As Integer

    strOffset = 1
    Do
        strOffset = InStr(strOffset, str, "?")
        If strOffset < 1 Then
            Exit Do
        End If
        parmOffset = InStr(1, parms, ",")
        If parmOffset > 0 Then
            parmLen = parmOffset - 1
        Else
            parmLen = Len(parms)
        End If
        str = Left(str, strOffset - 1) + Left(parms, parmLen) + Mid(str, strOffset + 1)
        If parmOffset > 0 Then
            parms = Mid(parms, parmOffset + 1)
        End If
    Loop
    SubstituteParameters = str
End Function

'
'GetIniString(section,key)
'  Returns the value of the key in the section.
'  The maximum length of the string returned is 4096.
'
Public Function GetIniString(section As String, key As String) As String
    GetIniString = GetPrivateProfileString(section, key, "", 4096, iniFile)
End Function

'
'GetPrivateProfileString(section,key,default,maxlen,file)
'  Returns the value of the key in the section in the file.
'  It calls the Win32 GetPrivateProfileString function.
'
Public Function GetPrivateProfileString(section As String, key As String, default As String, maxlen As Long, file As String) As String
    Dim ReturnStr As String
    Dim returnLen As Long
    Dim rc As Long
    Dim nullOffset As Integer
    
    returnLen = maxlen + 1
    ReturnStr = String(returnLen, Chr$(0))
    rc = GetPrivateProfileStringA(section, key, default, ReturnStr, returnLen, file)
    If rc > 0 And rc < returnLen Then
        nullOffset = InStr(1, ReturnStr, Chr$(0))
        If nullOffset > 0 Then
            ReturnStr = Left$(ReturnStr, nullOffset - 1)
        End If
    Else
        'Error or buffer too small.
        ReturnStr = ""
    End If
    GetPrivateProfileString = ReturnStr
End Function

'
'ParseConnect(Connect)
'  Parse Connect for "Data Source" value.
'
Private Function ParseConnect(ByRef Connect As String) As String
    Dim datasource As String
    Dim offset1 As Integer
    Dim offset2 As Integer

    datasource = ""
    offset1 = InStr(1, Connect, "Data Source=", vbTextCompare)
    If offset1 >= 1 Then
        offset1 = offset1 + 12
        offset2 = InStr(offset1, Connect, ";")
        If offset2 >= offset1 Then
            datasource = Mid$(Connect, offset1, offset2 - offset1)
        Else
            datasource = Mid$(Connect, offset1)
        End If
    End If

    If datasource = "" Then
        datasource = "default"
    End If

    ParseConnect = datasource
End Function

'
'ModifyConnectViaIni(connect)
'  Looks up connect in the ini file,
'  then it modifies connect, userid, password appropiately.
'
Public Sub ModifyConnectViaIni(ByRef Connect As String)
    Dim section As String
    Dim str As String
    Dim datasource As String

    'Parse connect for "Data Source" value.
    datasource = ParseConnect(Connect)

    'Compute the section names.
    section = "connect " + GetSectionName(datasource)

    'Modify the connect string.
    str = GetIniString(section, "Connect")
    If str <> "" Then
        Connect = str
    End If
End Sub

'
'GetSectionName(datasource)
'
Public Function GetSectionName(ByVal datasource As String) As String
    Dim section As String
    Dim str As String

    'Figure out the section name.
    section = "connect " + datasource
    str = GetIniString(section, "Access")
    If str = "" Then
        datasource = "default"
    End If

    'Return the section name.
    GetSectionName = datasource
End Function

'
'GetSqlSectionName(Connect)
'
Public Function GetSqlSectionName(ByVal Connect As String) As String
    Dim section As String
    Dim str As String

    'Figure out the section name.
    section = "sql " + Connect
    str = GetIniString(section, "Sql")
    If str = "" Then
        Connect = "default"
    End If

    'Return the section name.
    GetSqlSectionName = Connect
End Function

'
'ModifySqlViaIni(sql)
'  Looks up sql in the ini file,
'  then modifies sql appropiately.
'
Public Sub ModifySqlViaIni(ByRef sql As String)
    Dim section As String
    Dim str As String
    Dim func As String
    Dim args As String
    
    Call ParseSql(sql, func, args)

    'Compute the section name.
    section = "sql " + GetSqlSectionName(func)

    'Modify the sql string.
    str = GetIniString(section, "Sql")
    If str <> "" Then
        sql = SubstituteParameters(str, args)
    End If
End Sub

'
'changeOptionsToSql(options)
'
Public Sub changeOptionsToSql(ByRef options As Long)
    If options And 8 Then
        'Make it adCmdText
        options = 1
    Else
        'Add adCmdText, remove adCmdTable and adCmdStoredProc
        options = (options And Not (2 Or 4)) Or 1
    End If
End Sub

'
'DecodeAccess(str)
'  decode access string into access number
'
Private Function DecodeAccess(ByVal str As String) As Long
    Dim access As Long

    access = 0
    If str = "ReadOnly" Then
        access = 2
    End If
    If str = "ReadWrite" Then
        access = 3
    End If
    DecodeAccess = access
End Function

'
'GetAccess(connect,user)
'  Looks up connect in the ini file,
'  then it returns access permission appropiately.
'
Public Function GetAccess(ByVal Connect As String, ByVal user As String) As Long
    Dim name As String
    Dim connectSection As String
    Dim userConnectSection As String
    Dim str As String
    Dim temp As Long
    Dim access As Long
    Dim datasource As String

    'Compute the section names.
    datasource = ParseConnect(Connect)
    name = GetSectionName(datasource)
    connectSection = "connect " + name
    userConnectSection = "userlist " + name

    'Get the connect access.
    str = GetIniString(connectSection, "Access")
    access = DecodeAccess(str)

    'See if the user has an access override.
    str = GetIniString(userConnectSection, user)
    If str <> "" Then
        access = DecodeAccess(str)
    End If

    'Return the result.
    GetAccess = access
End Function

'
'ParseSql()
'
Public Sub ParseSql(ByVal sql As String, ByRef func As String, ByRef args As String)
    Dim leftOffset As Integer
    Dim rightOffset As Integer
    
    leftOffset = InStr(1, sql, "(")
    If leftOffset > 1 Then
        func = Left$(sql, leftOffset - 1)
        rightOffset = InStr(leftOffset, sql, ")")
        If rightOffset > leftOffset Then
            args = Mid$(sql, leftOffset + 1, rightOffset - leftOffset - 1)
        Else
            args = Mid$(sql, leftOffset + 1)
        End If
    Else
        func = ""
        args = ""
    End If
End Sub

'For debugging:
'Open "c:\msdfmap_vb.out" For Output As #1

