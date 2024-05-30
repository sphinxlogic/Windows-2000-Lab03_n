Attribute VB_Name = "MailFuncs"
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''
'' ADSI Sample to create and delete Exchange 5.5 Mailboxes
''
'' Richard Ault, Jean-Philippe Balivet, Neil Wemple -- 1998
''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Option Explicit

' Mailbox property settings
Public Const LOGON_CMD = "logon.cmd"
Public Const INCOMING_MESSAGE_LIMIT = 1000
Public Const OUTGOING_MESSAGE_LIMIT = 1000
Public Const WARNING_STORAGE_LIMIT = 8000
Public Const SEND_STORAGE_LIMIT = 12000
Public Const REPLICATION_SENSITIVITY = 20
Public Const COUNTRY = "US"

' Mailbox rights for Exchange security descriptor (home made)
Public Const RIGHT_MODIFY_USER_ATTRIBUTES = &H2
Public Const RIGHT_MODIFY_ADMIN_ATTRIBUTES = &H4
Public Const RIGHT_SEND_AS = &H8
Public Const RIGHT_MAILBOX_OWNER = &H10
Public Const RIGHT_MODIFY_PERMISSIONS = &H80
Public Const RIGHT_SEARCH = &H100

' win32 constants for security descriptors (from VB5 API viewer)
Public Const ACL_REVISION = (2)
Public Const SECURITY_DESCRIPTOR_REVISION = (1)
Public Const SidTypeUser = 1

Type ACL
        AclRevision As Byte
        Sbz1 As Byte
        AclSize As Integer
        AceCount As Integer
        Sbz2 As Integer
End Type

Type ACE_HEADER
        AceType As Byte
        AceFlags As Byte
        AceSize As Long
End Type

Type ACCESS_ALLOWED_ACE
        Header As ACE_HEADER
        Mask As Long
        SidStart As Long
End Type

Type SECURITY_DESCRIPTOR
        Revision As Byte
        Sbz1 As Byte
        Control As Long
        Owner As Long
        Group As Long
        Sacl As ACL
        Dacl As ACL
End Type

' Just an help to allocate the 2dim dynamic array
Private Type mySID
    x() As Byte
End Type


' Declares : modified from VB5 API viewer
Declare Function InitializeSecurityDescriptor Lib "advapi32.dll" _
        (pSecurityDescriptor As SECURITY_DESCRIPTOR, _
        ByVal dwRevision As Long) As Long

Declare Function SetSecurityDescriptorOwner Lib "advapi32.dll" _
        (pSecurityDescriptor As SECURITY_DESCRIPTOR, _
        pOwner As Byte, _
        ByVal bOwnerDefaulted As Long) As Long

Declare Function SetSecurityDescriptorGroup Lib "advapi32.dll" _
        (pSecurityDescriptor As SECURITY_DESCRIPTOR, _
        pGroup As Byte, _
        ByVal bGroupDefaulted As Long) As Long

Declare Function SetSecurityDescriptorDacl Lib "advapi32.dll" _
        (pSecurityDescriptor As SECURITY_DESCRIPTOR, _
        ByVal bDaclPresent As Long, _
        pDacl As Byte, _
        ByVal bDaclDefaulted As Long) As Long

Declare Function SetSecurityDescriptorSacl Lib "advapi32.dll" _
        (pSecurityDescriptor As SECURITY_DESCRIPTOR, _
        ByVal bSaclPresent As Long, _
        pSacl As Byte, _
        ByVal bSaclDefaulted As Long) As Long

Declare Function MakeSelfRelativeSD Lib "advapi32.dll" _
        (pAbsoluteSecurityDescriptor As SECURITY_DESCRIPTOR, _
        pSelfRelativeSecurityDescriptor As Byte, _
        ByRef lpdwBufferLength As Long) As Long

Declare Function GetSecurityDescriptorLength Lib "advapi32.dll" _
        (pSecurityDescriptor As SECURITY_DESCRIPTOR) As Long

Declare Function IsValidSecurityDescriptor Lib "advapi32.dll" _
        (pSecurityDescriptor As Byte) As Long

Declare Function InitializeAcl Lib "advapi32.dll" _
        (pACL As Byte, _
        ByVal nAclLength As Long, _
        ByVal dwAclRevision As Long) As Long

Declare Function AddAccessAllowedAce Lib "advapi32.dll" _
        (pACL As Byte, _
        ByVal dwAceRevision As Long, _
        ByVal AccessMask As Long, _
        pSid As Byte) As Long

Declare Function IsValidAcl Lib "advapi32.dll" _
        (pACL As Byte) As Long

Declare Function GetLastError Lib "kernel32" _
        () As Long

Declare Function LookupAccountName Lib "advapi32.dll" _
        Alias "LookupAccountNameA" _
        (ByVal IpSystemName As String, _
         ByVal IpAccountName As String, _
         pSid As Byte, _
         cbSid As Long, _
         ByVal ReferencedDomainName As String, _
         cbReferencedDomainName As Long, _
         peUse As Integer) As Long

Declare Function NetGetDCName Lib "NETAPI32.DLL" _
        (ServerName As Byte, _
         DomainName As Byte, _
         DCNPtr As Long) As Long
                                         
Declare Function NetApiBufferFree Lib "NETAPI32.DLL" _
        (ByVal Ptr As Long) As Long
        
Declare Function PtrToStr Lib "kernel32" _
        Alias "lstrcpyW" (RetVal As Byte, ByVal Ptr As Long) As Long

Declare Function GetLengthSid Lib "advapi32.dll" _
        (pSid As Byte) As Long


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''
'' Create_NT_Account() -- creates an NT user account
''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Function Create_NT_Account(strDomain As String, _
                                  strAdmin As String, _
                                  strPassword As String, _
                                  UserName As String, _
                                  FullName As String, _
                                  NTServer As String _
                                  ) As Boolean

Dim oNS As IADsOpenDSObject
Dim User As IADsUser
Dim Domain As IADsDomain

    On Error GoTo Create_NT_Account_Error

    Create_NT_Account = False
    
    If (strPassword = "") Then
        strPassword = ""
    End If
    
    Set oNS = GetObject("WinNT:")
    Set Domain = oNS.OpenDSObject("WinNT://" & strDomain, strDomain & "\" & strAdmin, strPassword, 0)
    
    Set User = Domain.Create("User", UserName)
    With User
        .Description = "User created by ADSI"
        .FullName = FullName
        .HomeDirectory = "\\" & NTServer & "\" & UserName
        .LoginScript = LOGON_CMD
        .SetInfo
        ' First password = username
        .SetPassword UserName
    End With
    
    Debug.Print "Successfully created NT Account for user " & UserName
    Create_NT_Account = True
    Exit Function

Create_NT_Account_Error:
    
    Debug.Print "Error 0x" & CStr(Hex(Err.Number)) & " occurred creating NT account for user " & UserName

End Function

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''
'' Delete_NT_Account() -- deletes an NT user account
''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Function Delete_NT_Account(strDomain As String, _
                                  strAdmin As String, _
                                  strPassword As String, _
                                  UserName As String _
                                  ) As Boolean

Dim Domain As IADsDomain
Dim oNS As IADsOpenDSObject

    On Error GoTo Delete_NT_Account_Error
    
    Delete_NT_Account = False
    
    If (strPassword = "") Then
        strPassword = ""
    End If

    Set oNS = GetObject("WinNT:")
    Set Domain = oNS.OpenDSObject("WinNT://" & strDomain, strDomain & "\" & strAdmin, strPassword, 0)
    
    Domain.Delete "User", UserName
    
    Debug.Print "Successfully deleted NT Account for user " & UserName
    Delete_NT_Account = True
    Exit Function
    
Delete_NT_Account_Error:
    
    Debug.Print "Error 0x" & CStr(Hex(Err.Number)) & " occurred deleting NT account for user " & UserName
    
End Function

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''
'' Create_Exchange_Mailbox() -- creates an Exchange mailbox, sets mailbox
''                           properties and and associates the mailbox with
''                           an existing NT user account
''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Function Create_Exchange_MailBox( _
    IsRemote As Boolean, _
    strServer As String, _
    strDomain As String, _
    strAdmin As String, _
    strPassword As String, _
    UserName As String, _
    EMailAddress As String, _
    strFirstName As String, _
    strLastName As String, _
    ExchangeServer As String, _
    ExchangeSite As String, _
    ExchangeOrganization As String _
   ) As Boolean

Dim Container As IADsContainer
Dim strRecipContainer As String
Dim Mailbox As IADs
Dim rbSID(1024) As Byte
Dim OtherMailBox() As Variant
Dim sSelfSD() As Byte
Dim encodedSD() As Byte
Dim I As Integer

Dim oNS As IADsOpenDSObject

    On Error GoTo Create_Exchange_MailBox_Error
    
    Create_Exchange_MailBox = False
    
    If (strPassword = "") Then
        strPassword = ""
    End If

    ' Recipients container for this server
    strRecipContainer = "LDAP://" & ExchangeServer & _
                        "/CN=Recipients,OU=" & ExchangeSite & _
                        ",O=" & ExchangeOrganization
    Set oNS = GetObject("LDAP:")
    Set Container = oNS.OpenDSObject(strRecipContainer, "cn=" & strAdmin & ",dc=" & strDomain, strPassword, 0)
    
    ' This creates both mailboxes or remote dir entries
    If IsRemote Then
        Set Mailbox = Container.Create("Remote-Address", "CN=" & UserName)
        Mailbox.Put "Target-Address", EMailAddress
    Else
        Set Mailbox = Container.Create("OrganizationalPerson", "CN=" & UserName)
        Mailbox.Put "MailPreferenceOption", 0
    End If
    
    With Mailbox
        .SetInfo
        
        ' As an example two other addresses
        ReDim OtherMailBox(1)
        OtherMailBox(0) = "MS$" & ExchangeOrganization & _
                          "/" & ExchangeSite & _
                          "/" & UserName
        
        OtherMailBox(1) = "CCMAIL$" & UserName & _
                          " at " & ExchangeSite
                          
        If Not (IsRemote) Then
            ' Get the SID of the previously created NT user
            Get_Exchange_Sid strDomain, UserName, rbSID
            .Put "Assoc-NT-Account", rbSID
            ' This line also initialize the "Home Server" parameter of the Exchange admin
            .Put "Home-MTA", "cn=Microsoft MTA,cn=" & ExchangeServer & ",cn=Servers,cn=Configuration,ou=" & ExchangeSite & ", o = " & ExchangeOrganization
            .Put "Home-MDB", "cn=Microsoft Private MDB,cn=" & ExchangeServer & ",cn=Servers,cn=Configuration,ou=" & ExchangeSite & ",o=" & ExchangeOrganization
            .Put "Submission-Cont-Length", OUTGOING_MESSAGE_LIMIT
            .Put "MDB-Use-Defaults", False
            .Put "MDB-Storage-Quota", WARNING_STORAGE_LIMIT
            .Put "MDB-Over-Quota-Limit", SEND_STORAGE_LIMIT
            .Put "MAPI-Recipient", True
            
            ' Security descriptor
            ' The rights choosen make a normal user role
            ' The other user is optionnal, delegate for ex.
            
            Call MakeSelfSD(sSelfSD, _
                            strServer, _
                            strDomain, _
                            UserName, _
                            UserName, _
                            RIGHT_MAILBOX_OWNER + RIGHT_SEND_AS + _
                            RIGHT_MODIFY_USER_ATTRIBUTES _
                           )

            ReDim encodedSD(2 * UBound(sSelfSD) + 1)
            For I = 0 To UBound(sSelfSD) - 1
                encodedSD(2 * I) = AscB(Hex$(sSelfSD(I) \ &H10))
                encodedSD(2 * I + 1) = AscB(Hex$(sSelfSD(I) Mod &H10))
            Next I
            
            .Put "NT-Security-Descriptor", encodedSD
        Else
            
            ReDim Preserve OtherMailBox(2)
            OtherMailBox(2) = EMailAddress
            .Put "MAPI-Recipient", False
        End If
        
        ' Usng PutEx for array properties
        .PutEx ADS_PROPERTY_UPDATE, "otherMailBox", OtherMailBox
        
        .Put "Deliv-Cont-Length", INCOMING_MESSAGE_LIMIT
        ' i : initials
        .Put "TextEncodedORaddress", "c=" & COUNTRY & _
                                     ";a= " & _
                                     ";p=" & ExchangeOrganization & _
                                     ";o=" & ExchangeSite & _
                                     ";s=" & strLastName & _
                                     ";g=" & strFirstName & _
                                     ";i=" & Mid(strFirstName, 1, 1) & Mid(strLastName, 1, 1) & ";"
        
        .Put "rfc822MailBox", UserName & "@" & ExchangeSite & "." & ExchangeOrganization & ".com"
        .Put "Replication-Sensitivity", REPLICATION_SENSITIVITY
        .Put "uid", UserName
        .Put "name", UserName

        .Put "GivenName", strFirstName
        .Put "Sn", strLastName
        .Put "Cn", strFirstName & " " & strLastName
        .Put "Initials", Mid(strFirstName, 1, 1) & Mid(strLastName, 1, 1)
        
        ' Any of these fields are simply descriptive and optional, not included in
        ' this sample and there are many other fields in the mailbox
        .Put "Mail", EMailAddress
        'If 0 < Len(Direction) Then .Put "Department", Direction
        'If 0 < Len(FaxNumber) Then .Put "FacsimileTelephoneNumber", FaxNumber
        'If 0 < Len(City) Then .Put "l", City
        'If 0 < Len(Address) Then .Put "PostalAddress", Address
        'If 0 < Len(PostalCode) Then .Put "PostalCode", PostalCode
        'If 0 < Len(Banque) Then .Put "Company", Banque
        'If 0 < Len(PhoneNumber) Then .Put "TelephoneNumber", PhoneNumber
        'If 0 < Len(Title) Then .Put "Title", Title
        'If 0 < Len(AP1) Then .Put "Extension-Attribute-1", AP1
        'If 0 < Len(Manager) Then .Put "Extension-Attribute-2", Manager
        'If 0 < Len(Agence) Then .Put "Extension-Attribute-3", Agence
        'If 0 < Len(Groupe) Then .Put "Extension-Attribute-4", Groupe
        'If 0 < Len(Secteur) Then .Put "Extension-Attribute-5", Secteur
        'If 0 < Len(Region) Then .Put "Extension-Attribute-6", Region
        'If 0 < Len(GroupeBanque) Then .Put "Extension-Attribute-7", GroupeBanque
        'If 0 < Len(AP7) Then .Put "Extension-Attribute-8", AP7
        'If 0 < Len(AP8) Then .Put "Extension-Attribute-9", AP8
        .SetInfo
    End With
    
    Debug.Print "Successfully created mailbox for user " & UserName
    Create_Exchange_MailBox = True
    Exit Function

Create_Exchange_MailBox_Error:
    
    Debug.Print "Error 0x" & CStr(Hex(Err.Number)) & " occurred creating Mailbox for user " & UserName
    
End Function

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''
'' Delete_Exchange_Mailbox() -- deletes an Exchange mailbox
''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Function Delete_Exchange_Mailbox( _
    IsRemote As Boolean, _
    strDomain As String, _
    strAdmin As String, _
    strPassword As String, _
    UserName As String, _
    ExchangeServer As String, _
    ExchangeSite As String, _
    ExchangeOrganization As String _
   ) As Boolean

Dim strRecipContainer As String
Dim Container As IADsContainer
Dim oNS As IADsOpenDSObject

    If (strPassword = "") Then
        strPassword = ""
    End If

    On Error GoTo Delete_Exchange_MailBox_Error
    Delete_Exchange_Mailbox = False
    
    ' Recipients container for this server
    strRecipContainer = "LDAP://" & ExchangeServer & _
                        "/CN=Recipients,OU=" & ExchangeSite & _
                        ",O=" & ExchangeOrganization
    Set oNS = GetObject("LDAP:")
    Set Container = oNS.OpenDSObject(strRecipContainer, "cn=" & strAdmin & ",dc=" & strDomain, strPassword, 0)

    If Not (IsRemote) Then
        Container.Delete "OrganizationalPerson", "CN=" & UserName
    Else
        Container.Delete "Remote-Address", "CN=" & UserName
    End If
    
    Container.SetInfo
    
    Debug.Print "Successfully deleted mailbox for user " & UserName
    Delete_Exchange_Mailbox = True
    Exit Function

Delete_Exchange_MailBox_Error:
    
    Debug.Print "Error 0x" & CStr(Hex(Err.Number)) & " occurred deleting Mailbox for user " & UserName

End Function

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''
'' MakeSelfSD -- builds a self-relative Security Descriptor suitable for ADSI
''
'' Return code : 1 = OK
''               0 = error
'' In    sSelfSD     dynamic byte array, size 0
''       sServer     DC for the domain
''       sDomain     Domain name
''       sAssocUser  Primary NT account for the mail box (SD owner)
''       paramarray  Authorized accounts
''                   This is an array of (userid, role, userid, role...)
''                   where role is a combination of rights (cf RIGHTxxx constants)
'' Out   sSelfSD     Self relative SD allocated and initalized
''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Function MakeSelfSD(sSelfSD() As Byte, _
        sServer As String, sDomain As String, _
        sAssocUSer As String, _
        ParamArray ACEList() As Variant) As Long
Dim SecDesc As SECURITY_DESCRIPTOR
Dim I As Integer
Dim tACL As ACL
Dim tACCESS_ALLOWED_ACE As ACCESS_ALLOWED_ACE
Dim pSid() As Byte
Dim pACL() As Byte
Dim pACESID() As mySID
Dim Longueur As Long
Dim rc As Long
    
    On Error GoTo SDError
    ' Initializing abolute SD
    rc = InitializeSecurityDescriptor(SecDesc, SECURITY_DESCRIPTOR_REVISION)
    If (rc <> 1) Then
        Err.Raise -12, , "InitializeSecurityDescriptor"
    End If
    
    rc = GetSID(sServer, sDomain, sAssocUSer, pSid)
    If (rc <> 1) Then
        Err.Raise -12, , "GetSID"
    End If
    
    rc = SetSecurityDescriptorOwner(SecDesc, pSid(0), 0)
    If (rc <> 1) Then
        Err.Raise -12, , "SetSecurityDescriptorOwner"
    End If
    
    ' I don't know why we had to do this one, but it works for us
    rc = SetSecurityDescriptorGroup(SecDesc, pSid(0), 0)
    If (rc <> 1) Then
        Err.Raise -12, , "SetSecurityDescriptorGroup"
    End If
    
    ' Getting SIDs for all the other users, and computing of total ACL length
    ' (famous formula from MSDN)
    Longueur = Len(tACL)
    ReDim Preserve pACESID((UBound(ACEList) - 1) / 2)
    For I = 0 To UBound(pACESID)
        If 1 <> GetSID(sServer, sDomain, CStr(ACEList(2 * I)), pACESID(I).x) Then Err.Raise -12, , "GetSID"
        Longueur = Longueur + GetLengthSid(pACESID(I).x(0)) + Len(tACCESS_ALLOWED_ACE) - 4
    Next I
    
    ' Initalizing ACL, and adding one ACE for each user
    ReDim pACL(Longueur)
    If 1 <> InitializeAcl(pACL(0), Longueur, ACL_REVISION) Then Err.Raise -12, , "InitializeAcl"
    For I = 0 To UBound(pACESID)
        If 1 <> AddAccessAllowedAce(pACL(0), ACL_REVISION, CLng(ACEList(2 * I + 1)), pACESID(I).x(0)) Then Err.Raise -12, , "AddAccessAllowedAce"
    Next I
    If 1 <> SetSecurityDescriptorDacl(SecDesc, 1, pACL(0), 0) Then Err.Raise -12, , "SetSecurityDescriptorDacl"
    
    ' Allocation and conversion in the self relative SD
    Longueur = GetSecurityDescriptorLength(SecDesc)
    ReDim sSelfSD(Longueur)
    If 1 <> MakeSelfRelativeSD(SecDesc, sSelfSD(0), Longueur) Then Err.Raise -12, , "MakeSelfRelativeSD"
    MakeSelfSD = 1
    Exit Function

SDError:
    MakeSelfSD = 0
End Function

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''
'' GetSID -- gets the Security IDentifier for the specified account name
''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Function GetSID(sServer As String, sDomain As String, sUserID As String, pSid() As Byte) As Long
Dim rc As Long
Dim pDomain() As Byte
Dim lSID As Long, lDomain As Long
Dim sSystem As String, sAccount As String

    On Error GoTo SIDError
    
    ReDim pSid(0)
    ReDim pDomain(0)
    lSID = 0
    lDomain = 0
    sSystem = "\\" & sServer
    sAccount = sDomain & "\" & sUserID
    
    rc = LookupAccountName(sSystem, sAccount, pSid(0), lSID, pDomain(0), lDomain, SidTypeUser)
    
    If (rc = 0) Then
        ReDim pSid(lSID)
        ReDim pDomain(lDomain + 1)

        rc = LookupAccountName(sSystem, sAccount, pSid(0), lSID, pDomain(0), lDomain, SidTypeUser)
        If (rc = 0) Then
            GoTo SIDError
        End If
    End If
    
    GetSID = 1
    Exit Function

SIDError:
    GetSID = 0
End Function

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''
'' Get_Primary_DCName -- gets the name of the Primary Domain Controller for
''                       the NT domain
''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Function Get_Primary_DCName(ByVal MName As String, ByVal DName As String) As String

Dim Result As Long
Dim DCName As String
Dim DCNPtr As Long
Dim DNArray() As Byte
Dim MNArray() As Byte
Dim DCNArray(100) As Byte

    MNArray = MName & vbNullChar
    DNArray = DName & vbNullChar
    Result = NetGetDCName(MNArray(0), DNArray(0), DCNPtr)
    If Result <> 0 Then
        Exit Function
    End If
    Result = PtrToStr(DCNArray(0), DCNPtr)
    Result = NetApiBufferFree(DCNPtr)
    DCName = DCNArray()
    Get_Primary_DCName = DCName
    
End Function

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
''
'' Get_Exchange_Sid -- gets the NT user's Security IDentifier for Exchange
''
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Sub Get_Exchange_Sid(strNTDomain As String, strNTAccount As String, rbSID() As Byte)

Dim pSid(512) As Byte
Dim pDomain(512) As Byte
Dim IReturn As Long
Dim I As Integer

    IReturn = LookupAccountName(Get_Primary_DCName("", strNTDomain), strNTAccount, pSid(0), 512, pDomain, 512, 1)
    
    For I = 0 To GetLengthSid(pSid(0)) - 1
        rbSID(2 * I) = AscB(Hex$(pSid(I) \ &H10))
        rbSID(2 * I + 1) = AscB(Hex$(pSid(I) Mod &H10))
    Next I
End Sub
