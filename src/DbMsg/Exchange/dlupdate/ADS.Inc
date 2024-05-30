<%
'<!--Distribution List Maintenance Sample Application-->
'<!--ADS.inc : Active Directory Services -->
'<!--Copyright (c) Microsoft Corporation 1993-1998. All rights reserved.-->
'
' ADS.inc contains constants, properties, & routines for handling Active Directory Services.
'
' ADS Constants
'
Const mstrADS_CN_RECIPIENTS = "Recipients"

Const gstrADS_CLASS_DL = "groupOfNames"
'
' ADO ADS Constants
'
Const mstrADS_COL_ADS_PATH = "adspath"
Const mstrADS_COL_ALIAS = "uid"
Const mstrADS_COL_DISP_NAME = "cn"
Const mstrADS_COL_DN = "distinguishedName"
Const mstrADS_COL_EMAIL_ADDR = "mail"
Const mstrADS_COL_NOTES = "info"
Const mstrADS_COL_OWNER = "owner"
Const mstrADS_COL_RDN = "rdn"

Const mstrADS_COL_ASSOC_NT_ACCOUNT = "Assoc-NT-Account"
Const mstrADS_COL_NT_SECURITY_DESCRIPTOR = "NT-Security-Descriptor"
Const mstrADS_COL_OTHER_MAILBOX = "otherMailbox"
Const mstrADS_COL_REPLICATION_SENSITIVITY = "Replication-Sensitivity"
Const mstrADS_COL_REPORT_TO_ORIGINATOR = "Report-To-Originator"
Const mstrADS_COL_REPORT_TO_OWNER = "Report-To-Owner"
Const mstrADS_COL_RFC_822_MAILBOX = "rfc822Mailbox"
Const mstrADS_COL_TEXT_ENCODED_OR_ADDRESS = "textEncodedORaddress"
'
' Special Characters
'
Dim mrgchDN_INVALID
mrgchDN_INVALID = ", + = "" < > # ; " & vbCRLF
Const mchDN_ESC = "\"

Const mrgchLDAP_SEARCH_INVALID = "/,*,(,), "
Const mchLDAP_SEARCH_ESC = "\"

Const mcLDAP_SEARCH_HEX_CHARACTERS = 2

Const mrgchEXCH_RDN_INVALID = "^ # $ { } \ ` ~ ; /"
Const mchEXCH_RDN_REPLACE = "?"
'
' Error Constants
'
Const gerrADS_DUPLICATE_DL = &H800700B7
Const gerrADS_DUPLICATE_DL_MEMBER = &H800704B8
Const gerrADS_PROPERTY_NOT_DEFINED = &H8000500D
Const gerrADS_PROPERTY_NOT_AVAILABLE = &H800704B8

Dim gerrADS_DUPLICATE_EMAIL_ADDR
Dim gerrADS_INVALID_DL_OWNER

Const gstrADS_MSG_ALERT_DUPLICATE_DL = "This distribution list is already on file."

gerrADS_DUPLICATE_EMAIL_ADDR = vbObjectError + 100
Const gstrADS_MSG_ALERT_DUPLICATE_EMAIL_ADDR = "The e-mail address derived from the alias name is already on file."
gerrADS_INVALID_DL_OWNER = vbObjectError + 200
Const gstrADS_MSG_ALERT_INVALID_DL_OWNER = "The distribution list owner must be associated with an NT account."
'
' PutEx Constants
'
Const mADS_PROPERTY_CLEAR = 1
Const mADS_PROPERTY_UPDATE = 2
'
' Other Constants
'
Const mcADS_RS_PAGE_SIZE = 100
Const giADS_PAGE_FIRST = 1
'
' Properties
'
Public ADS_strServer
Public ADS_strOrganization
Public ADS_strOrganizationalUnit

Public ADS_strAlias
Public ADS_strDispName
Public ADS_strDispNameOwner
Public ADS_rgstrDispNameMembers
Public ADS_rgstrADsPathMembers
Public ADS_strNotes

Public ADS_rgstrDispNameDL
Public ADS_rgstrADsPathDL

Public ADS_rgstrDispNameSel
Public ADS_rgstrADsPathSel

Public ADS_iPage
Public ADS_cPage
'
' Error variables.  Under VB, the Raise method provides the ability to trap for errors
' & raise to the calling routine.  Raise is not provided under VBScript so trapped errors are
' saved in these variables.
'
Public ADS_err
Public ADS_strErr
'
' Initialize properties
'
    ADS_rgstrDispNameMembers = Array()
    ADS_rgstrADsPathMembers = Array()

    ADS_rgstrDispNameDL = Array()
    ADS_rgstrADsPathDL = Array()

    ADS_rgstrDispNameSel = Array()
    ADS_rgstrADsPathSel = Array()

    ADS_iPage = giADS_PAGE_FIRST
    ADS_cPage = 0

Private Function strADsPath(pstrRecipient)
'
' strADsPath returns an ADs path:
'   . for the recipients container (if pstrADsCN is an empty string) or
'   . for the passed recipient common name (if pstrADsCN is not empty)
'
    If Len(ADS_strServer) > 0 Then
        strADsPath = "LDAP://" & ADS_strServer & "/" 
    End If

    If Len(pstrRecipient) > 0 then
        strADsPath = strADsPath & "cn=" & strrdnExch(pstrRecipient) & ","
    End If

    strADsPath = strADsPath _
                & "cn=" & mstrADS_CN_RECIPIENTS _
                & ",ou=" & strDN(ADS_strOrganizationalUnit) _
                & ",o=" & strDN(ADS_strOrganization)

End Function

Private Function strDN(pstrDN)
'
' strDN handles special characters in the passed distinguished name element as per rfc1779.
'
    Dim strSav
    Dim rgch
    Dim irgch

    rgch = Split(mrgchDN_INVALID)
    strSav = pstrDN

    For irgch = LBound(rgch) To UBound(rgch)
        strSav = Replace(strSav, rgch(irgch), mchDN_ESC & rgch(irgch))
    Next

    If Instr(strSav, gchSPACE) > 0 Then
        strSav = gchQUOTE & strSav & gchQUOTE
    End If

    strDN = strSav
End Function

Public Function strrdnExch(pstr)
'
' strrdnExch replaces special characters in the passed string to return a valid 
' Exchange RDN.
'
    Dim strSav
    Dim rgch
    Dim irgch

    rgch = Split(mrgchEXCH_RDN_INVALID)

    strSav = pstr

    For irgch = LBound(rgch) To UBound(rgch)
        strSav = Replace(strSav, rgch(irgch), mchEXCH_RDN_REPLACE)
    Next

    strrdnExch = strDN(strSav)
End Function

Public Sub ADS_ValidateServer()
'
' ValidateServer validates server properties by attempting to instantiate a server object.
'
    Dim cnRecipients

    Err.Clear

    Set cnRecipients = GetObject(strADsPath(gstrNONE))

    Set cnRecipients = Nothing

End Sub

Public Sub ADS_GetDLs(pstrSelCriteria, piPage)
'
' GetDLs gets the passed page of dl's & sets the dl disp name & alias arrays.
'
    Dim conn
    Dim rsDL
    Dim strQuery
    Dim cPageSize
    Dim iDLLast
    Dim iDL
    Dim iCModCPage

    Set conn = CreateObject("ADODB.Connection")
    conn.Open "Provider=ADSDSOObject"
    strQuery = "<" & strADsPath(gstrNONE) & ">;" _
                & "(&(" & mstrADS_COL_DISP_NAME & "=" & strLDAPSearch(pstrSelCriteria) & "*)" _
                        & "(objectClass=" & gstrADS_CLASS_DL & "));" _
                & mstrADS_COL_DISP_NAME & "," & mstrADS_COL_ADS_PATH & ";OneLevel"

    Set rsDL = CreateObject("ADODB.Recordset")
    rsDL.PageSize = mcADS_RS_PAGE_SIZE
    rsDL.Open strQuery, conn
    '
    ' Prep recordset paging
    '
    Call PrepArraysFromRS(rsDL, piPage, ADS_iPage, ADS_cPage _
                            , ADS_rgstrDispNameDL, ADS_rgstrADsPathDL)

    rsDL.Close
    conn.Close

    Set rsDL = Nothing
    Set conn = Nothing

End Sub

Public Sub PrepArraysFromRS(prs, piPageIn, piPage, pcPage, prgstrDispName, prgstrADsPath)
'
' PrepArraysFromRS sets the property arrays and paging info:
'
'   . Current page (piPage) for display
'   . Page count (pcPage)
'   . Arrays of disp name & alias
'
    Dim crs
    Dim irgLast
    Dim irg
    Dim iCModCPage

    crs = prs.RecordCount
    pcPage = prs.PageCount
    piPage = piPageIn
    '
    ' Set current page only if there are multiple pages
    '
    If pcPage > 1 Then
        '
        ' Adjust current page if out of bounds
        '
        If piPage > pcPage Or piPage < giADS_PAGE_FIRST Then
            piPage = giADS_PAGE_FIRST
        End If

        prs.AbsolutePage = piPage
    Else
        piPage = giADS_PAGE_FIRST
    End If
    '
    ' Set data arrays
    '
    If crs > 0 Then
        '
        ' Determine last index for data on the current page
        '
        If pcPage > 1 Then
            irgLast = mcADS_RS_PAGE_SIZE - 1

            If piPage = pcPage Then
                iCModCPage = crs Mod mcADS_RS_PAGE_SIZE 
                If  iCModCPage > 0 Then
                    irgLast = iCModCPage - 1
                End If
            End If
        Else
            irgLast = crs - 1
        End If

        ReDim prgstrDispName(irgLast)
        ReDim prgstrADsPath(irgLast)

        For irg = 0 To irgLast
            prgstrDispName(irg) = prs(mstrADS_COL_DISP_NAME)
            prgstrADsPath(irg) = prs(mstrADS_COL_ADS_PATH)

            prs.MoveNext
        Next
    End If
End Sub

Public Sub ADS_GetDLProperties(pstrADsPathRecipient, piPage)
'
' GetDLProperties gets the display name, DL owner, members, and notes.
'
    Dim recipient
    Dim recipientDLOwnerSav
    Dim recipientDLMember
    Dim strAliasDL
    Dim strDispNameDL
    Dim rgstrRDNDLMember
    Dim strDispNameOwner
    Dim strNotes
    Dim cPageSize
    Dim objdlMember
    Dim iMemberFirst
    Dim iMemberLast
    Dim iMember
    Dim irgMemberLast
    Dim irgMember
    Dim cMember
    
    Set recipient = GetObject(pstrADsPathRecipient)
    '
    ' Get alias & display name
    '
    strAliasDL = recipient.uid
    strDispNameDL = recipient.cn
    '
    ' Get the owner display name
    '
    Set recipientDLOwnerSav = recipientDLOwner(recipient)

    If Not (recipientDLOwnerSav Is Nothing) Then
        strDispNameOwner = recipientDLOwnerSav.cn
    Else
        strDispNameOwner = gstrNONE
    End If
    '
    ' Get a count of members.
    '
    cMember = recipient.Members.Count
    '
    ' Get notes
    '
    strNotes = recipient.info
    '
    ' Prep paging
    '
    ADS_iPage = piPage
    cPageSize = mcADS_RS_PAGE_SIZE
    ADS_cPage = cMember \ cPageSize

    If cMember Mod cPageSize > 0 Then
        ADS_cPage = ADS_cPage + 1
    End If

    If ADS_cPage > 1 Then
        '
        ' Adjust current page if out of bounds
        '
        If ADS_iPage > ADS_cPage Or ADS_iPage < giADS_PAGE_FIRST Then
            ADS_iPage = giADS_PAGE_FIRST
        End If
    Else
        ADS_iPage = giADS_PAGE_FIRST
    End If
    '
    ' Set properties
    '
    ADS_strAlias = strAliasDL
    ADS_strDispName = strDispNameDL
    ADS_strDispNameOwner = strDispNameOwner
    ADS_strNotes = strNotes

    If cMember > 0 Then
        '
        ' Determine first & last members of the page
        '
        iMemberFirst = ((ADS_iPage - 1) * cPageSize)
        iMemberLast = iMemberFirst + cPageSize - 1
        If iMemberLast > cMember - 1 Then
            iMemberLast = cMember - 1
        End If

        irgMemberLast = iMemberLast - iMemberFirst
        ReDim ADS_rgstrDispNameMembers(irgMemberLast)
        ReDim ADS_rgstrADsPathMembers(irgMemberLast)

        iMember = 0
        '
        ' Get member array & loop through it, setting member disp name & alias arrays
        '
        If cMember = 1 Then
            '
            ' If member count is 1, member returns element in a string rather than an array.
            '
            rgstrRDNDLMember = Array(recipient.Member)
        Else
            rgstrRDNDLMember = recipient.Member
        End If
    
        For iMember = iMemberFirst To iMemberLast
            irgMember = iMember - iMemberFirst

            ADS_rgstrADsPathMembers(irgMember) = "LDAP://" & ADS_strServer & "/" & rgstrRDNDLMember(iMember)
            Set recipientDLMember = GetObject(ADS_rgstrADsPathMembers(irgMember))
            ADS_rgstrDispNameMembers(irgMember) = recipientDLMember.cn
        Next
    End If

    Set recipient = Nothing
    Set recipientDLOwnerSav = Nothing
    Set recipientDLMember = Nothing
End Sub

Private Function recipientDLOwner(precipient)
'
' recipientDLOwner returns the owner of the DL
'
    Dim strRDNOwner

    strRDNOwner = precipient.owner

    If len(strRDNOwner) > 0 Then
        Set recipientDLOwner = GetObject("LDAP://" & ADS_strServer & "/" & strRDNOwner)
    Else
        Set recipientDLOwner = Nothing
    End If
End Function

Public Sub ADS_ModDLOwner(pstrADsPathOwner, pstrADsPathRecipient)
    Dim recipient
    Dim recipientDLOwnerNew
    Dim recipientDLOwnerOld
    Dim rgbytSecurityDescriptor
    Dim rgbytSecurityDescriptorOld
    Dim rgbytSecurityIDOwnerNew
    Dim rgbytSecurityIDOwnerOld
    '
    ' Get the new owner & owner's security ID
    '
    Set recipientDLOwnerNew = GetObject(pstrADsPathOwner)

    rgbytSecurityIDOwnerNew = varGetInfoEx(recipientDLOwnerNew, mstrADS_COL_ASSOC_NT_ACCOUNT)

    If IsEmpty(rgbytSecurityIDOwnerNew) Then
        Err.Raise gerrADS_INVALID_DL_OWNER, , gstrADS_MSG_ALERT_INVALID_DL_OWNER
    Else
        '
        ' Get the DL object & former owner
        '
        Set recipient = GetObject(pstrADsPathRecipient)

        Set recipientDLOwnerOld = recipientDLOwner(recipient)
        '
        ' Set the new owner.  Prep security descriptor & owner attributes.
        '
        Call SetProperty(recipient, mstrADS_COL_OWNER, recipientDLOwnerNew.distinguishedName, recipient.owner)
        '
        ' Get the former owner's security ID
        '
        If recipientDLOwnerOld Is Nothing Then            
            rgbytSecurityIDOwnerOld = Empty
        Else
            rgbytSecurityIDOwnerOld = varGetInfoEx(recipientDLOwnerOld, mstrADS_COL_ASSOC_NT_ACCOUNT)
        End If
        '
        ' Get the DL's security descriptor so that the former owner can be removed & the new
        ' owner added.
        '
        rgbytSecurityDescriptorOld = varGetInfoEx(recipient, mstrADS_COL_NT_SECURITY_DESCRIPTOR)

        Call NTAcct_PrepareSecurityDescriptor(rgbytSecurityIDOwnerOld, rgbytSecurityDescriptorOld _
                                                , rgbytSecurityIDOwnerNew, rgbytSecurityDescriptor)

        recipient.Put CStr(mstrADS_COL_NT_SECURITY_DESCRIPTOR), (rgbytSecurityDescriptor)

        recipient.SetInfo
    End If

    Set recipient = Nothing
    Set recipientDLOwnerNew = Nothing
    Set recipientDLOwnerOld = Nothing
End Sub

Private Function varGetInfoEx(precipient, pstrProperty)
'
' varGetInfoEx returns the value of the passed property.  Some properties are not placed in the
' adsi cache by default.  This routine moves the passed property into the cache & gets it's value.
'
    Dim errNo

    On Error Resume Next

    precipient.GetInfoEx Array(pstrProperty), 0

    errNo = Err.Number

    On Error GoTo 0

    Select Case errNo
        Case gerrNONE
            varGetInfoEx = precipient.Get(pstrProperty)
        Case gerrADS_PROPERTY_NOT_AVAILABLE
            '
            ' There is no property
            '
            Err.Clear

            varGetInfoEx = Empty
        Case Else ' Handle error in calling routine
            Err.Raise CLng(errNo)
    End Select
End Function

Public Sub ADS_ModifyDL(pstrADsPathRecipient)
'
' ModifyDL modifies the DL's display name & notes.
'
    Dim recipient
    '
    ' Get the DL object
    '
    Set recipient = GetObject(pstrADsPathRecipient)

    Call SetProperty(recipient, mstrADS_COL_DISP_NAME, ADS_strDispName, recipient.cn)
    Call SetProperty(recipient, mstrADS_COL_NOTES, ADS_strNotes, recipient.info)

    recipient.SetInfo

    Set recipient = Nothing
End Sub

Private Sub SetProperty(precipient, pstrProperty, pstrPropertyValue, pstrPropertyValueOld)
'
' SetProperty sets the property or if the property value is empty, clears it.
'
    If Len(pstrPropertyValue) = 0 Then
        If Len(CStr(pstrPropertyValueOld)) > 0 Then
            '
            ' Use PutEx w/ mADS_PROPERTY_CLEAR to remove a property of an ADS object
            '
            precipient.PutEx mADS_PROPERTY_CLEAR, CStr(pstrProperty), CStr(gstrNONE)
        End If
    Else
        '
        ' You may also set a property by using syntax, "obj.Property = Value".  Since the
        ' property name is being passed as a string, we use the Put method here.
        '
        precipient.Put CStr(pstrProperty), CStr(pstrPropertyValue)
    End If
End Sub

Public Sub ADS_AddDL(pstrADsPathRecipient)
'
' Add adds a dl object.  Add calls bValidAdd.  Because this routine places error info in the
' module error variables, ADS_err & ADS_strErr, routines calling Add should check both
' err.Number & ADS_err for errors.
'
    Dim errSav
    Dim rgstrOtherMailbox(1)
    Dim strEmailAddr
    Dim strEmailAddrExt
    Dim strAliasNoSpace
    Dim strErr
    Dim strrdnExchSav
    Dim strMSMailPrefix
    Dim strTextEncodedORAddressPrefix
    Dim recipient
    Dim cnRecipients

    Const cCH_OR_SURNAME = 40
    Const iTRUST_LEVEL_DEFAULT = 20
    '
    ' Gather data for add
    '
    Call GetConfigData(strEmailAddrExt, strTextEncodedORAddressPrefix, strMSMailPrefix)

    If Err.Number = gerrNONE Then

        strrdnExchSav = strrdnExch(ADS_strAlias)
        strAliasNoSpace = Replace(ADS_strAlias, gchSPACE, gstrNONE)
        strEmailAddr = strAliasNoSpace + strEmailAddrExt

        If bValidAdd(strrdnExchSav, strEmailAddr) Then
            '
            ' Add the DL
            '
            Set cnRecipients = GetObject(strADsPath(gstrNONE))

            Set recipient = cnRecipients.Create(gstrADS_CLASS_DL, "cn=" + strrdnExchSav)
            '
            ' Set DL properties
            '
            recipient.Put mstrADS_COL_DISP_NAME, CStr(ADS_strDispName)
            recipient.Put mstrADS_COL_ALIAS, CStr(ADS_strAlias)

            If Len(ADS_strNotes) > 0 Then
                recipient.Put mstrADS_COL_NOTES, CStr(ADS_strNotes)
            End If

            recipient.Put CStr(mstrADS_COL_EMAIL_ADDR), CStr(strEmailAddr)
            recipient.Put CStr(mstrADS_COL_REPORT_TO_ORIGINATOR), True
            recipient.Put CStr(mstrADS_COL_REPORT_TO_OWNER), False

            If Len(strMSMailPrefix) > 0 Then
                rgstrOtherMailbox(0) = strMSMailPrefix & Left(strAliasNoSpace, 10)
                rgstrOtherMailbox(1) = "CCMAIL$" & ADS_strAlias & " at " & ADS_strOrganizationalUnit
                ' ()'s are necessary to pass the array in VBScript
                recipient.PutEx mADS_PROPERTY_UPDATE, CStr(mstrADS_COL_OTHER_MAILBOX), (rgstrOtherMailbox)
            End If

            recipient.Put CStr(mstrADS_COL_RFC_822_MAILBOX), CStr(strEmailAddr)
            recipient.Put CStr(mstrADS_COL_TEXT_ENCODED_OR_ADDRESS), CStr(strTextEncodedORAddressPrefix _
                                                          & Left(strrdnExchSav, cCH_OR_SURNAME) & ";")
            recipient.Put CStr(mstrADS_COL_REPLICATION_SENSITIVITY), CInt(iTRUST_LEVEL_DEFAULT)
            '
            ' Save the DL properties
            '
            recipient.SetInfo

            Set recipient = Nothing
            Set cnRecipients = Nothing
            '
            ' Return path
            '
            pstrADsPathRecipient = strADsPath(ADS_strAlias)
        End If
    End If
End Sub

Private Sub ClearErr()
'
' ClearErr clears the ADS error variables.
'
    ADS_err = gerrNONE
    ADS_strErr = gstrNONE
End Sub

Private Sub SetErr(perr, pstrErr)
'
' SetErr sets the ADS error variables.
'
    ADS_err = perr
    ADS_strErr = pstrErr
End Sub

Private Sub GetConfigData(pstrEmailAddrExt, pstrTextEncodedORAddressPrefix, pstrMSMailPrefix)
'
' bGetDLConfigData reads the "Private MDB" object to get configuration data.  It returns:
'   
'   . the SMTP address extension.
'   . the organization/recipient (OR) address prefix
'   . the prefix for Other MB row 1.
'
    Dim iMailAt
    Dim iOtherMailboxFldSeparator
    Dim cnConfiguration
    Dim strMail
    Dim strOtherMBRow
    Dim strPathCnConfig
    Dim rgstrOtherMailbox
    Dim strTextEncodedORAddress         ' Organization/Recipient (OR) Address

    Const strOR_SURNAME_PARM_ID = "s="
    Const strOTHER_MAILBOX_FLD_SEPARATOR = "/"

    Call ClearErr()
    '
    ' Get configuration info in preparation for adding the DL
    '
    strPathCnConfig = "LDAP://" & ADS_strServer & "/" _
                            & "cn=Microsoft Private MDB,cn=" & strDN(ADS_strServer) _
                            & ",cn=Servers ,cn=Configuration,ou=" & strDN(ADS_strOrganizationalUnit) _
                            & ",o=" & strDN(ADS_strOrganization)

    Set cnConfiguration = GetObject(strPathCnConfig)
    cnConfiguration.GetInfo
    '
    ' Get SMTP extension
    '
    strMail = cnConfiguration.Get(mstrADS_COL_EMAIL_ADDR)
    iMailAt = InStr(strMail, "@")
    pstrEmailAddrExt = Mid(strMail, iMailAt, Len(strMail))
    '
    ' Get textEncodedORaddress
    '
    strTextEncodedORAddress = cnConfiguration.Get(mstrADS_COL_TEXT_ENCODED_OR_ADDRESS)
    pstrTextEncodedORAddressPrefix = _
                        Left(strTextEncodedORAddress _
                            , InStr(strTextEncodedORAddress, strOR_SURNAME_PARM_ID) + Len(strOR_SURNAME_PARM_ID) - 1)
    '
    ' Get otherMailbox.  Position after second fld separator to establish OtherMailbox prefix.
    ' The otherMailbox prefix includes the enterprise & site formatted for this property.
    ' 
    On Error Resume Next
    rgstrOtherMailbox = (cnConfiguration.Get(mstrADS_COL_OTHER_MAILBOX))

    Select Case Err.Number
        Case gerrNONE
            On Error GoTo 0

            strOtherMBRow = rgstrOtherMailbox(0)
            iOtherMailboxFldSeparator = Instr(strOtherMBRow, strOTHER_MAILBOX_FLD_SEPARATOR) + Len(strOTHER_MAILBOX_FLD_SEPARATOR)
            iOtherMailboxFldSeparator = Instr(iOtherMailboxFldSeparator, strOtherMBRow, strOTHER_MAILBOX_FLD_SEPARATOR) _
                                            + Len(strOTHER_MAILBOX_FLD_SEPARATOR) - 1
    
            pstrMSMailPrefix = Left(strOtherMBRow, iOtherMailboxFldSeparator)
        Case gerrADS_PROPERTY_NOT_DEFINED
            pstrMSMailPrefix = gstrNONE

            Err.Clear
    End Select

    Set cnConfiguration = Nothing
End Sub

Private Function bValidAdd(pstrrdn, pstrEmailAddr)
'
' bValidAdd checks the rdn & mail address for uniqueness.  If an invalid condition is detected,
' an error msg is moved to ADS_strErr & false is returned.
'
    Dim conn
    Dim rsSel
    Dim strQuery
    Dim strQueryADsPath
    Dim strQueryCriteria
    Dim strQueryResultColumns
    
    Call ClearErr()
    '
    ' Establish an ADO session
    '
    Set conn = CreateObject("ADODB.Connection")
    conn.Open "Provider=ADSDSOObject"

    strQueryADsPath = strADsPath(gstrNONE)

    strQueryResultColumns = mstrADS_COL_ADS_PATH
    '
    ' Verify uniqueness of rdn.  Note that you could add code to generate a unique
    ' rdn instead of raising this validation error.
    '
    strQueryCriteria = mstrADS_COL_RDN & "=" & strLDAPSearch(pstrrdn)

    strQuery = "<" & strQueryADsPath & ">" _
                & ";(" & strQueryCriteria & ")" _
                & ";" & strQueryResultColumns & ";OneLevel"
    
    Set rsSel = conn.Execute(strQuery)
    '
    ' Check record count.
    '
    If rsSel.RecordCount > 0 Then
        Call SetErr(gerrADS_DUPLICATE_DL, gstrADS_MSG_ALERT_DUPLICATE_DL)
        bValidAdd = False

        Set rsSel = Nothing
        Set conn = Nothing

        Exit Function
    End If
    '
    ' Verify uniqueness of SMTP address.  Note that you could add code to generate a unique
    ' address instead of raising this validation error.
    '
    strQueryCriteria = mstrADS_COL_EMAIL_ADDR & "=" & strLDAPSearch(pstrEmailAddr)

    strQuery = "<" & strQueryADsPath & ">" _
                & ";(" & strQueryCriteria & ")" _
                & ";" & strQueryResultColumns & ";OneLevel"

    Set rsSel = conn.Execute(strQuery)
    '
    ' Check record count.
    '
    If rsSel.RecordCount > 0 Then
        Call SetErr(gerrADS_DUPLICATE_EMAIL_ADDR, gstrADS_MSG_ALERT_DUPLICATE_EMAIL_ADDR)
        bValidAdd = False

        Set rsSel = Nothing
        Set conn = Nothing

        Exit Function
    End If
    '
    ' If we arrive here, all validations passed
    '
    bValidAdd = True

    Set rsSel = Nothing
    Set conn = Nothing
End Function

Private Function strLDAPSearch(pstrSearch)
'
' strLDAPSearch handles special characters in the search string as per rfc2254.
'
    Dim strSav
    Dim rgch
    Dim irgch

    rgch = Split(mrgchLDAP_SEARCH_INVALID, gchCOMMA)

    strSav = pstrSearch

    For irgch = LBound(rgch) To UBound(rgch)
        strSav = Replace(strSav, rgch(irgch), mchLDAP_SEARCH_ESC _
                         & App_strLeadingZeros(Hex(Asc(rgch(irgch))), mcLDAP_SEARCH_HEX_CHARACTERS))
    Next

    strLDAPSearch = strSav
End Function

Public Sub ADS_GetQueryResults(pstrSelCriteria, pstrADsPathExclude, piPage, bIncludeDLs)
'
' GetQueryResults performs a query & moves query results into disp name & adspath arrays.
'
    Dim conn
    Dim recipient
    Dim rsSel
    Dim strQuery
    Dim strQueryADsPath
    Dim strQueryCriteria
    Dim strQueryResultColumns
    Dim strrdnExclude

    '
    ' Get DL rdn
    '
    Set recipient = GetObject(pstrADsPathExclude)

    strrdnExclude = recipient.rdn
    '
    ' Perform query
    '
    Set conn = CreateObject("ADODB.Connection")
    conn.Open "Provider=ADSDSOObject"
    '
    ' Build the query
    '
    strQueryADsPath = strADsPath(gstrNONE)
    '
    ' This query selects all records starting w/ the selection criteria, except
    ' for records that match the current dl.
    '
    strQueryCriteria = "&(" & mstrADS_COL_DISP_NAME & "=" & strLDAPSearch(pstrSelCriteria) & "*)" _
                         & "(!(" & mstrADS_COL_RDN & "=" & strLDAPSearch(strrdnExclude) & "))"
    '
    ' When getting alias's for a dl's owner, leave out dl's
    '
    If Not bIncludeDLs Then
        strQueryCriteria = strQueryCriteria & "(!(objectClass=" & gstrADS_CLASS_DL & "))"
    End If

    strQueryResultColumns = mstrADS_COL_DISP_NAME & "," & mstrADS_COL_ADS_PATH _
                            & "," & mstrADS_COL_ALIAS

    strQuery = "<" & strQueryADsPath & ">" _
                & ";(" & strQueryCriteria & ")" _
                & ";" & strQueryResultColumns & ";OneLevel"

    Set rsSel = CreateObject("ADODB.Recordset")
    rsSel.PageSize = mcADS_RS_PAGE_SIZE
    rsSel.Open strQuery, conn
    '
    ' Prep recordset paging
    '
    Call PrepArraysFromRS(rsSel, piPage, ADS_iPage, ADS_cPage _
                            , ADS_rgstrDispNameSel, ADS_rgstrADsPathSel)

    rsSel.Close
    conn.Close

    Set rsSel = Nothing
    Set conn = Nothing
    Set recipient = Nothing

End Sub

Public Sub ADS_AddDLMembers(pstrADsPathRecipient)
'
' AddDLMembers adds the alias's in the passed collection of ADs paths to the dl.
'
    Dim irgstrADsPathMembers
    Dim recipient
    Dim recipientDLMember
    Dim lngErr
    Dim strErr
    '
    ' Get the DL container object
    '
    Set recipient = GetObject(pstrADsPathRecipient)

    For irgstrADsPathMembers = LBound(ADS_rgstrADsPathMembers) To UBound(ADS_rgstrADsPathMembers)
        '
        ' Get the new member's object
        '
        Set recipientDLMember = GetObject(ADS_rgstrADsPathMembers(irgstrADsPathMembers))
        '
        ' Add the new member.  Set Resume next permit
        ' trapping for already in dl error.
        '
        On Error Resume Next

        recipient.Add recipientDLMember.ADsPath
        '
        ' Check for errors other than already in dl
        '
        lngErr = Err.Number
        If Not (lngErr = 0 Or lngErr = gerrADS_DUPLICATE_DL_MEMBER) Then
            '
            ' Raise the error
            '
            strErr = Err.Description
            On Error GoTo 0

            Err.Raise strErr, , lngErr
        End If
        '
        ' Reset error handling
        '
        On Error GoTo 0
    Next

    Set recipientDLMember = Nothing
    Set recipient = Nothing
End Sub

Public Sub ADS_DelDLMembers(pstrADsPathRecipient)
'
' DelDLMembers deletes the alias's in the passed collection from the dl.
'
    Dim irgstrADsPathMembers
    Dim strADsPathMember
    Dim recipient
    Dim recipientDLMember
    '
    ' Get the DL container object
    '
    Set recipient = GetObject(pstrADsPathRecipient)


    For irgstrADsPathMembers = LBound(ADS_rgstrADsPathMembers) To UBound(ADS_rgstrADsPathMembers)
        '
        ' Get member's object
        '
        Set recipientDLMember = GetObject(ADS_rgstrADsPathMembers(irgstrADsPathMembers))
        '
        ' Remove the member.
        '
        recipient.Remove recipientDLMember.ADsPath
    Next

    Set recipientDLMember = Nothing
    Set recipient = Nothing
End Sub

Public Sub ADS_DelDL(pstrADsPathRecipient)
'
' DelDL deletes the the passed dl.
'
    Dim cnRecipients
    Dim recipient
    '
    ' Get the dl's object
    '
    Set recipient = GetObject(pstrADsPathRecipient)
    
    Set cnRecipients = GetObject(recipient.Parent)
    '
    ' Delete the dl.
    '
    Call cnRecipients.Delete(gstrADS_CLASS_DL, recipient.name) 

    Set recipient = Nothing
    Set cnRecipients = Nothing
End Sub
%>