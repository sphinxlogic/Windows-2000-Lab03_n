Attribute VB_Name = "Module1"
'****************************************************************************
'
'  Module:     VBCARD.EXE
'  File:       Module1.frm
'  Content:    Implementation of the VbCard processes
'
'  Copyright (c) Microsoft Corporation 1995-1997
'
' THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
' ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
' THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
' PARTICULAR PURPOSE.
'****************************************************************************

Option Explicit

Public Const BIZCARD_DATA_SIZE As Integer = 568
Const SIZE_OFFSET As Integer = 0
Const NAME_OFFSET As Integer = 4
Const TITLE_OFFSET As Integer = 84
Const COMPANY_OFFSET As Integer = 164
Const ADDRESS_OFFSET As Integer = 244
Const PHONE_OFFSET As Integer = 324
Const FAX_OFFSET As Integer = 404
Const EMAIL_OFFSET As Integer = 484
Const IMAGESIZE_OFFSET As Integer = 564
Const STRING_LENGTH As Integer = 80

' Beta2 NetMeeting breaks up data transfers into 4K packets
Const MAX_DATA_PACKET As Integer = 4096

' of course this is a bad thing
Const PictureDir As String = "c:\"

Private Type LongBytes
    b0 As Byte
    b1 As Byte
    b2 As Byte
    b3 As Byte
End Type

Private Type LongType
    l As Long
End Type

Public Type BizCardInfo
    Name As String
    Title As String
    Company As String
    Address As String
    Phone As String
    Fax As String
    EMail As String
    PhotoFile As String
End Type

Public Type MemberInfo
    Name As String
    Card As BizCardInfo
    Photo As Picture
    ImageSize As Long
    FileOpen As Boolean
End Type

Public MyCard As BizCardInfo
Public ActiveCard As BizCardInfo
Public MemberInfoArray(15) As MemberInfo
Public ActiveIndex As Integer

Public Sub ReadBizCard( _
    App As String, _
    Name As String, _
    Card As BizCardInfo)
    
    Card.Name = GetSetting(App, Name, "Name", "")
    Card.Title = GetSetting(App, Name, "Title", "")
    Card.Company = GetSetting(App, Name, "Company", "")
    Card.Address = GetSetting(App, Name, "Address", "")
    Card.Phone = GetSetting(App, Name, "Phone", "")
    Card.Fax = GetSetting(App, Name, "Fax", "")
    Card.EMail = GetSetting(App, Name, "EMail", "")
    Card.PhotoFile = GetSetting(App, Name, "Photo", "")
End Sub

Public Sub WriteBizCard( _
    App As String, _
    Name As String, _
    Card As BizCardInfo)
    
    SaveSetting App, Name, "Name", Card.Name
    SaveSetting App, Name, "Title", Card.Title
    SaveSetting App, Name, "Company", Card.Company
    SaveSetting App, Name, "Address", Card.Address
    SaveSetting App, Name, "Phone", Card.Phone
    SaveSetting App, Name, "Fax", Card.Fax
    SaveSetting App, Name, "EMail", Card.EMail
    SaveSetting App, Name, "Photo", Card.PhotoFile
End Sub

Private Sub UpdateActivePhoto()
    VbCard.Photo.Picture = MemberInfoArray(ActiveIndex).Photo
End Sub

Public Sub UpdateActiveIndex(Name As String)
    ActiveIndex = GetMemberIndex(Name)
    If ActiveIndex < 0 Then
        ActiveIndex = 0
    End If
    
    UpdateActivePhoto
End Sub

Public Function GetActiveCard() As BizCardInfo
    If ActiveIndex >= 0 Then
        GetActiveCard = MemberInfoArray(ActiveIndex).Card
    End If
End Function

Private Sub InitMember(Index As Integer)
    MemberInfoArray(Index).Name = ""
    MemberInfoArray(Index).FileOpen = False
    Set MemberInfoArray(Index).Photo = VbCard.Unknown.Picture
End Sub

Public Sub InitMemberArray()
    Dim Index As Integer
    
    For Index = 0 To 15
        InitMember Index
    Next
End Sub

Public Function GetMemberIndex(Name As String) As Integer
    Dim Index As Integer
    
    GetMemberIndex = -1
    For Index = 0 To 15
        If MemberInfoArray(Index).Name = Name Then
            GetMemberIndex = Index
            Exit For
        End If
    Next
End Function

Public Sub DeleteMember(Member As IConfMemberX)
    Dim Index As Integer
    
    Index = GetMemberIndex(Member.Name)
    If Index >= 0 Then
        InitMember Index
    End If
End Sub

Public Sub AddMember(Member As IConfMemberX)
    Dim Index As Integer

    Index = GetMemberIndex(Member.Name)
    If Index >= 0 Then
        ' already a member
        Exit Sub
    End If

    ' find next empty slot
    Index = GetMemberIndex("")
    If Index >= 0 Then
        MemberInfoArray(Index).Name = Member.Name
        
        ' If adding self, need to load user's picture
        If Member.IsSelf Then
            Dim MyPict As Picture
            
            MemberInfoArray(Index).Card = MyCard
            On Error Resume Next
            Set MyPict = LoadPicture(MyCard.PhotoFile)
            If Not Err Then
                Set MemberInfoArray(Index).Photo = MyPict
            End If
        End If
    End If
End Sub

Public Sub ReceiveImage(Name As String, DataTransfer As IConfDataTransferX)
    Dim Size As Integer
    Dim Index As Integer
    Dim FileNumber As Integer
    
    ' Create the member's picture from the transferred data
    ' Allows for Beta2 NetMeeting 4K packet breakup
    
    Index = GetMemberIndex(Name)
    FileNumber = Index + 1
    
    ' Make sure that the temporary file is open
    If Not MemberInfoArray(Index).FileOpen Then
        On Error Resume Next
        MemberInfoArray(Index).Card.PhotoFile = PictureDir & Name & ".bmp"
        Open MemberInfoArray(Index).Card.PhotoFile For Binary As #FileNumber
        If Err Then
            Exit Sub
        End If
        MemberInfoArray(Index).FileOpen = True
    End If
            
    Size = DataTransfer.BytesTransferred
    ReDim buf(1 To Size) As Byte
    buf = DataTransfer.Array(1)
    Put #FileNumber, , buf
    
    ' Assumes complete if the packet is not 4K
    ' This will cause problems if the picture is an exact multiple of 4K
    If Size <> MAX_DATA_PACKET Then
        'Close the file
        Close #FileNumber
        MemberInfoArray(Index).FileOpen = False
        
        ' Load the picture
        Set MemberInfoArray(Index).Photo = _
            LoadPicture(MemberInfoArray(Index).Card.PhotoFile)
        
        ' Delete the file
        Kill MemberInfoArray(Index).Card.PhotoFile
        
        ' If this is the current member, update the picture
        If Index = ActiveIndex Then
            UpdateActivePhoto
        End If
    End If
End Sub

Private Function getVbString( _
    Buffer() As Byte, _
    first As Integer, _
    length As Integer)
    
    ' Convert a fixed length array of Bytes into a VB string
    ' (each Byte is an 8 bit ASCII character)
    
    Dim i As Integer
    Dim j As Integer
    ReDim szText(1 To length) As Byte
    
    j = first
    For i = 1 To length
        szText(i) = Buffer(j)
        j = j + 1
    Next
    getVbString = StrConv(szText, vbUnicode)
End Function

Public Sub ReceiveBizCard( _
    Name As String, _
    DataTransfer As IConfDataTransferX)
    
    ' Copy transfered data into the member's BizCardInfo structure
    
    Dim Index

    Index = GetMemberIndex(Name)
    If Index >= 0 Then
        Dim Data() As Byte
        Data = DataTransfer.Array(1)
    
        MemberInfoArray(Index).Card.Name = getVbString(Data, _
            NAME_OFFSET, STRING_LENGTH)
        MemberInfoArray(Index).Card.Title = getVbString(Data, _
            TITLE_OFFSET, STRING_LENGTH)
        MemberInfoArray(Index).Card.Company = getVbString(Data, _
            COMPANY_OFFSET, STRING_LENGTH)
        MemberInfoArray(Index).Card.Address = getVbString(Data, _
           ADDRESS_OFFSET, STRING_LENGTH)
        MemberInfoArray(Index).Card.Phone = getVbString(Data, _
            PHONE_OFFSET, STRING_LENGTH)
        MemberInfoArray(Index).Card.Fax = getVbString(Data, _
            FAX_OFFSET, STRING_LENGTH)
        MemberInfoArray(Index).Card.EMail = getVbString(Data, _
            EMAIL_OFFSET, STRING_LENGTH)
    End If
    
End Sub

Private Sub setVbString( _
    strText As String, _
    Buffer() As Byte, _
    first As Integer, _
    length As Integer)
    
    ' Convert a VB String into an fixed length array of Bytes
    ' (each Byte is an 8 bit ASCII character)
    
    Dim i As Integer
    Dim j As Integer
    Dim szText() As Byte
    
    szText = StrConv(strText, vbFromUnicode)
    
    ' just in case szText is ""
    Buffer(first) = 0
    
    j = first
    For i = LBound(szText) To UBound(szText)
        Buffer(j) = szText(i)
        j = j + 1
    Next
End Sub

Public Sub BizCardToBytes(ByRef Card As BizCardInfo, _
    Buffer() As Byte, _
    Size As Integer)
    
    ' Convert a BizCardInfo structure into an array of Bytes
    
    Dim bSize As LongBytes
    Dim lSize As LongType
    ReDim Buffer(BIZCARD_DATA_SIZE - 1) As Byte
    
    lSize.l = BIZCARD_DATA_SIZE
    LSet bSize = lSize
    
    Buffer(SIZE_OFFSET) = bSize.b0
    Buffer(SIZE_OFFSET + 1) = bSize.b1
    Buffer(SIZE_OFFSET + 2) = bSize.b2
    Buffer(SIZE_OFFSET + 3) = bSize.b3
    
    lSize.l = Size
    LSet bSize = lSize
    
    Buffer(IMAGESIZE_OFFSET) = bSize.b0
    Buffer(IMAGESIZE_OFFSET + 1) = bSize.b1
    Buffer(IMAGESIZE_OFFSET + 2) = bSize.b2
    Buffer(IMAGESIZE_OFFSET + 3) = bSize.b3
    
    setVbString Card.Name, Buffer, _
        NAME_OFFSET, STRING_LENGTH
    setVbString Card.Title, Buffer, _
        TITLE_OFFSET, STRING_LENGTH
    setVbString Card.Company, Buffer, _
        COMPANY_OFFSET, STRING_LENGTH
    setVbString Card.Address, Buffer, _
        ADDRESS_OFFSET, STRING_LENGTH
    setVbString Card.Phone, Buffer, _
        PHONE_OFFSET, STRING_LENGTH
    setVbString Card.Fax, Buffer, _
        FAX_OFFSET, STRING_LENGTH
    setVbString Card.EMail, Buffer, _
        EMAIL_OFFSET, STRING_LENGTH
End Sub

Public Function PictureToBytes( _
    FileName As String, _
    Buffer() As Byte) As Integer
    Dim FileNumber As Integer
    
    ' Convert a bitmap file into an array of Bytes
    
    FileNumber = 99
    On Error Resume Next
    Open FileName For Binary As #FileNumber
    If Err Then
        ' check for empty file name here
        If FileName = "" Then
            MsgBox "Picture file name is empty"
        Else
            MsgBox "Unable to open " & FileName
        End If
        PictureToBytes = 0
    Else
        Dim Size As Integer
        
        Size = LOF(FileNumber)
        ReDim Buffer(1 To Size) As Byte
        Get #FileNumber, , Buffer()
        Close #FileNumber
        PictureToBytes = Size
    End If
End Function

