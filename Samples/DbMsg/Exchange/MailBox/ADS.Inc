<%
'<!--Mailbox Maintenance Sample Application-->
'<!--ADS.inc : Active Directory Services -->
'<!--Copyright (c) Microsoft Corporation 1993-1998. All rights reserved.-->
'
' ADS.inc contains constants, properties, & routines for handling Active Directory Services.
'
%>
<!--#include file="NTAcct.inc"-->
<%
' ADS Constants
'
Const mstrADS_CN_RECIPIENTS = "Recipients"

Const gstrADS_CLASS_MB = "organizationalPerson"
Const gstrADS_CLASS_CR_INTERNET = "Remote-Address"
'
' ADS Property Constants
'
Const mstrADS_COL_ADS_PATH = "adspath"
Const mstrADS_COL_DN = "distinguishedName"
Const mstrADS_COL_RDN = "rdn"

Const mstrADS_COL_ASSOC_NT_ACCOUNT = "Assoc-NT-Account"
Const mstrADS_COL_DELIV_EXT_CONT_TYPES = "Deliv-Ext-Cont-Types"
Const mstrADS_COL_HOME_MTA = "Home-MTA"
Const mstrADS_COL_HOME_MDB = "Home-MDB"
Const mstrADS_COL_MAIL_PREFERENCE_OPTION = "mailPreferenceOption"
Const mstrADS_COL_MAPI_RECIPIENT = "MAPI-Recipient"
Const mstrADS_COL_MDB_USE_DEFAULTS = "MDB-Use-Defaults"
Const mstrADS_COL_NT_SECURITY_DESCRIPTOR = "NT-Security-Descriptor"
Const mstrADS_COL_OTHER_MAILBOX = "otherMailbox"
Const mstrADS_COL_REPLICATION_SENSITIVITY = "Replication-Sensitivity"
Const mstrADS_COL_RFC_822_MAILBOX = "rfc822Mailbox"
Const mstrADS_COL_TARGET_ADDRESS = "Target-Address"
Const mstrADS_COL_TEXT_ENCODED_OR_ADDRESS = "textEncodedORaddress"

Const mstrADS_COL_ALIAS = "uid"
Const mstrADS_COL_ASSISTANT = "secretary"
Const mstrADS_COL_CITY = "l"
Const mstrADS_COL_COMPANY = "Company"
Const mstrADS_COL_COUNTRY = "co"
Const mstrADS_COL_DEPT = "department"
Const mstrADS_COL_DISP_NAME = "cn"
Const mstrADS_COL_EMAIL_ADDR = "mail"
Const mstrADS_COL_NAME_FIRST = "givenName"
Const mstrADS_COL_NAME_LAST = "sn"
Const mstrADS_COL_NAME_MID_INITIAL = "initials"
Const mstrADS_COL_NOTES = "info"
Const mstrADS_COL_OFFICE = "physicalDeliveryOfficeName"
Const mstrADS_COL_PHONE_ASSISTANT = "Telephone-Assistant"
Const mstrADS_COL_PHONE_BUS = "telephoneNumber"
Const mstrADS_COL_PHONE_2_BUS = "Telephone-Office2"
Const mstrADS_COL_PHONE_FAX = "facsimileTelephoneNumber"
Const mstrADS_COL_PHONE_HOME = "homephone"
Const mstrADS_COL_PHONE_2_HOME = "Telephone-Home2"
Const mstrADS_COL_PHONE_MOBILE = "mobile"
Const mstrADS_COL_PHONE_PAGER = "pager"
Const mstrADS_COL_POSTAL_ADDRESS = "postalAddress"
Const mstrADS_COL_POSTAL_CODE = "postalCode"
Const mstrADS_COL_STATE = "st"
Const mstrADS_COL_TITLE = "title"

Const mstrADS_DELIV_EXT_CONT_TYPES_DEFAULT = "2A864886F7140501"
Const mstrADS_REPLICATION_SENSITIVITY_DEFAULT = "20"
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
Const gerrADS_PROPERTY_NOT_DEFINED = &H8000500D
Const gerrADS_PROPERTY_NOT_AVAILABLE = &H800704B8

Dim gerrADS_DUPLICATE_RECIPIENT
Dim gerrADS_DUPLICATE_EMAIL_ADDR
Dim gerrADS_CANT_ASSOC_NT_ACCOUNT
Dim gerrADS_CANT_CREATE_NT_ACCOUNT

gerrADS_DUPLICATE_RECIPIENT = vbObjectError + 100
Const gstrADS_MSG_ALERT_DUPLICATE_RECIPIENT = "This recipient is already on file."

gerrADS_DUPLICATE_EMAIL_ADDR = vbObjectError + 200
Const gstrADS_MSG_ALERT_DUPLICATE_EMAIL_ADDR = "The e-mail address derived from the alias name is already on file."

gerrADS_CANT_ASSOC_NT_ACCOUNT = vbObjectError + 300
Const gstrADS_MSG_ALERT_CANT_ASSOC_NT_ACCOUNT = "Unable to associate mailbox with the Windows NT account.  Verify domain name and user id."

gerrADS_CANT_CREATE_NT_ACCOUNT = vbObjectError + 400
Const gstrADS_MSG_ALERT_CANT_CREATE_NT_ACCOUNT = "Unable to create the Windows NT account.  Verify the account doesn't exist."
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

Public ADS_bAddNTAcct

Public ADS_strAlias
Public ADS_strAssistant
Public ADS_strCity
Public ADS_strCompany
Public ADS_strCountry
Public ADS_strDept
Public ADS_strDispName
Public ADS_strEmailAddr
Public ADS_strNameFirst
Public ADS_strNameLast
Public ADS_strNameMidInitial
Public ADS_strNotes
Public ADS_strNTAcct
Public ADS_strNTPassword
Public ADS_strObjClass
Public ADS_strOffice
Public ADS_strPhoneAssistant
Public ADS_strPhoneBus
Public ADS_strPhone2Bus
Public ADS_strPhoneFax
Public ADS_strPhoneHome
Public ADS_strPhone2Home
Public ADS_strPhoneMobile
Public ADS_strPhonePager
Public ADS_strPostalAddress
Public ADS_strPostalCode
Public ADS_strState
Public ADS_strTitle

Public ADS_rgstrDispName
Public ADS_rgstrADsPath

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
    ADS_rgstrDispName = Array()
    ADS_rgstrADsPath = Array()

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
' ValidateServer validates the server properties, ADS_strServer, ADS_strOrganization,
' & ADS_strOrganizationalUnit, by attempting to instantiate
' a recipients container.
'
    Dim cnRecipients

    Err.Clear

    Set cnRecipients = GetObject(strADsPath(gstrNONE))

    Set cnRecipients = Nothing

End Sub

Public Sub ADS_GetRecipients(pstrSelCriteria, piPage)
'
' GetRecipients gets the passed page of recipients & sets the recipient disp name & path arrays.
'
    Dim conn
    Dim rsRecipient
    Dim strQuery
    Dim cPageSize
    Dim iCModCPage

    Set conn = CreateObject("ADODB.Connection")
    conn.Open "Provider=ADSDSOObject"
    '
    ' Find mail boxes & internet custom recipients matching the selection criteria.
    '
    strQuery = "<" & strADsPath(gstrNONE) & ">;" _
                & "(&(" & mstrADS_COL_DISP_NAME & "=" & strLDAPSearch(pstrSelCriteria) & "*)" _
                        & "(|(objectClass=" & gstrADS_CLASS_MB & ")(objectClass=" & gstrADS_CLASS_CR_INTERNET & ")));" _
                & mstrADS_COL_DISP_NAME & "," & mstrADS_COL_ADS_PATH & ";OneLevel"

    Set rsRecipient = CreateObject("ADODB.Recordset")
    rsRecipient.PageSize = mcADS_RS_PAGE_SIZE
    rsRecipient.Open strQuery, conn
    '
    ' Prep recordset paging
    '
    Call PrepArraysFromRS(rsRecipient, piPage, ADS_iPage, ADS_cPage _
                            , ADS_rgstrDispName, ADS_rgstrADsPath)

    rsRecipient.Close
    conn.Close

    Set rsRecipient = Nothing
    Set conn = Nothing

End Sub

Public Sub PrepArraysFromRS(prs, piPageIn, piPage, pcPage, prgstrDispName, prgstrADsPath)
'
' PrepArraysFromRS prepares data arrays and paging info from the passed recordset:
'
'   . Arrays of disp name (prgstrDispName) & ads path (prgstrADsPath)
'   . Current page (piPage) for display
'   . Page count (pcPage)
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
    ' Prepare data arrays
    '
    If crs > 0 Then
        '
        ' Determine last index for data on the current page
        '
        If pcPage > 1 Then
            irgLast = mcADS_RS_PAGE_SIZE - 1

            If piPage = pcPage Then
                iCModCPage = crs Mod mcADS_RS_PAGE_SIZE 
                If iCModCPage > 0 Then
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
    Else
        '
        ' When the recordset is empty, set display name & path arrays to empty.
        '
        prgstrDispName = Array()
        prgstrADsPath = Array()
    End If
End Sub

Public Sub ADS_Modify(pstrADsPathRecipient)
'
' Modify modifies the mailbox\custom recipient's properties.  
'
    Dim recipient
    Dim strEmailAddr
    Dim varSecurityID
    Dim varSecurityDescriptor
    '
    ' Get the mailbox\custom recipient object
    '
    Set recipient = GetObject(pstrADsPathRecipient)

    If ADS_strObjClass = gstrADS_CLASS_MB Then
        '
        ' Obtain NT Account Security ID & Descriptor
        '
        Call GetSecurityIDDescriptor(recipient, varSecurityID, varSecurityDescriptor)
        '
        ' Set NT Account Properties
        '
        Call SetNTAccountProperties(recipient, varSecurityID, varSecurityDescriptor)
    Else ' Custom Recipient
        strEmailAddr = recipient.mail
        '
        ' Update Email address properties
        '
        If ADS_strEmailAddr <> strEmailAddr Then
                Call SetProperty(recipient, mstrADS_COL_EMAIL_ADDR, ADS_strEmailAddr, strEmailAddr)
                Call SetProperty(recipient, mstrADS_COL_RFC_822_MAILBOX, ADS_strEmailAddr, strEmailAddr)
                Call SetProperty(recipient, mstrADS_COL_TARGET_ADDRESS _
                                    , "SMTP:" & ADS_strEmailAddr _
                                    , strEmailAddr)
        End If
    End If

    Call SetProperty(recipient, mstrADS_COL_ASSISTANT, ADS_strAssistant, recipient.secretary)
    Call SetProperty(recipient, mstrADS_COL_CITY, ADS_strCity, recipient.l)
    Call SetProperty(recipient, mstrADS_COL_COMPANY, ADS_strCompany, recipient.Company)
    Call SetProperty(recipient, mstrADS_COL_COUNTRY, ADS_strCountry, recipient.co)
    Call SetProperty(recipient, mstrADS_COL_DISP_NAME, ADS_strDispName, recipient.cn)

    Call SetProperty(recipient, mstrADS_COL_NAME_FIRST, ADS_strNameFirst, recipient.givenName)
    Call SetProperty(recipient, mstrADS_COL_NAME_LAST, ADS_strNameLast, recipient.sn)
    Call SetProperty(recipient, mstrADS_COL_NAME_MID_INITIAL, ADS_strNameMidInitial, recipient.initials)
    Call SetProperty(recipient, mstrADS_COL_NOTES, ADS_strNotes, recipient.info)

    Call SetProperty(recipient, mstrADS_COL_OFFICE, ADS_strOffice, recipient.physicalDeliveryOfficeName)
    Call SetProperty(recipient, mstrADS_COL_PHONE_FAX, ADS_strPhoneFax, recipient.facsimileTelephoneNumber)
    Call SetProperty(recipient, mstrADS_COL_PHONE_HOME, ADS_strPhoneHome, recipient.homephone)
    Call SetProperty(recipient, mstrADS_COL_PHONE_MOBILE, ADS_strPhoneMobile, recipient.mobile)
    Call SetProperty(recipient, mstrADS_COL_PHONE_PAGER, ADS_strPhonePager, recipient.pager)
    Call SetProperty(recipient, mstrADS_COL_POSTAL_ADDRESS, ADS_strPostalAddress, recipient.postalAddress)
    Call SetProperty(recipient, mstrADS_COL_POSTAL_CODE, ADS_strPostalCode, recipient.postalCode)
    Call SetProperty(recipient, mstrADS_COL_STATE, ADS_strState, recipient.st)
    '
    ' Following properties require special error handling because they return "property not 
    ' defined" error when the property is empty.
    '
    Call PrepSetProperty(recipient, mstrADS_COL_DEPT, ADS_strDept)
    If Err.Number <> gerrNONE Then
        Exit Sub
    End If

    Call PrepSetProperty(recipient, mstrADS_COL_PHONE_BUS, ADS_strPhoneBus)
    If Err.Number <> gerrNONE Then
        Exit Sub
    End If

    Call PrepSetProperty(recipient, mstrADS_COL_TITLE, ADS_strTitle)
    If Err.Number <> gerrNONE Then
        Exit Sub
    End If
    '
    ' Because the following property names include a dash, "object.get(propertyName)" syntax
    ' must be used.
    '
    Call PrepSetProperty(recipient, mstrADS_COL_PHONE_ASSISTANT, ADS_strPhoneAssistant)
    If Err.Number <> gerrNONE Then
        Exit Sub
    End If
     
    Call PrepSetProperty(recipient, mstrADS_COL_PHONE_2_BUS, ADS_strPhone2Bus)
    If Err.Number <> gerrNONE Then
        Exit Sub
    End If
     
    Call PrepSetProperty(recipient, mstrADS_COL_PHONE_2_HOME, ADS_strPhone2Home)
    If Err.Number <> gerrNONE Then
        Exit Sub
    End If

    recipient.SetInfo

    Set recipient = Nothing
End Sub

Private Sub PrepSetProperty(precipient, pstrProperty, pstrPropertyValue)
'
' PrepSetProperty is a wrapper routine for calling SetProperty.  The fourth parameter of
' SetProperty, strPropertyValueOld, can usually be determined by syntax "object.propertyName."
' However, some properties return error "property not defined" when the property is empty.
' This routine uses syntax "object.Get(propertyName)" to obtain the old value & 
' returns errors to the calling routine.
'
    Dim strPropertyValueOld

    strPropertyValueOld = strGetProperty(precipient, pstrProperty)

    If Err.Number = gerrNONE Then
        Call SetProperty(precipient, pstrProperty, pstrPropertyValue, strPropertyValueOld)
    Else
        '
        ' When an error is detected, exit so that the calling routine may handle.
        '
        Exit Sub
    End If
End Sub

Private Sub SetProperty(precipient, pstrProperty, pstrPropertyValue, pstrPropertyValueOld)
'
' SetProperty sets the passed property or if the property value is empty, clears it.
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

Public Sub ADS_Add()
'
' Add adds a mailbox or custom recipient object.    
' Because bValidAdd places error info in the module error variables, ADS_err & ADS_strErr,
' routines calling Add should check both err.Number & ADS_err for errors.
'
    Dim recipientIgnore
    Dim cnRecipients
    Dim recipient
    Dim rgstrOtherMailbox(1)
    Dim strEmailAddr
    Dim strEmailAddrExt
    Dim strAliasNoSpace
    Dim strrdnExchSav
    Dim strMSMailPrefix
    Dim strMSMail
    Dim strCCMail
    Dim strTextEncodedORAddressPrefix
    Dim varSecurityID
    Dim varSecurityDescriptor

    Const cCH_OR_SURNAME = 40
    Const cCH_OTHER_MB_ALIAS = 10
    '
    ' Gather data for add
    '
    Call GetConfigData(strEmailAddrExt, strTextEncodedORAddressPrefix, strMSMailPrefix)

    If Err.Number = gerrNONE Then

        strrdnExchSav = strrdnExch(ADS_strAlias)
        strAliasNoSpace = Replace(ADS_strAlias, gchSPACE, gstrNONE)

        If ADS_strObjClass = gstrADS_CLASS_MB Then
            strEmailAddr = strAliasNoSpace & strEmailAddrExt
        Else
            strEmailAddr = ADS_strEmailAddr
        End If

        If bValidAdd(strrdnExchSav, strEmailAddr) Then
            '
            ' Obtain NT Account Security ID & Descriptor
            '
            Call GetSecurityIDDescriptor(recipientIgnore, varSecurityID, varSecurityDescriptor)
            '
            ' Add the mailbox/custom recipient
            '
            Set cnRecipients = GetObject(strADsPath(gstrNONE))

            Set recipient = cnRecipients.Create(ADS_strObjClass, "cn=" & strrdnExchSav)
            '
            ' Set properties
            '
            Call SetProperty(recipient, mstrADS_COL_ALIAS, ADS_strAlias, gstrNONE)
            Call SetProperty(recipient, mstrADS_COL_ASSISTANT, ADS_strAssistant, gstrNONE)
            Call SetProperty(recipient, mstrADS_COL_CITY, ADS_strCity, gstrNONE)
            Call SetProperty(recipient, mstrADS_COL_COMPANY, ADS_strCompany, gstrNONE)
            Call SetProperty(recipient, mstrADS_COL_COUNTRY, ADS_strCountry, gstrNONE)
            Call SetProperty(recipient, mstrADS_COL_DEPT, ADS_strDept, gstrNONE)
            Call SetProperty(recipient, mstrADS_COL_DISP_NAME, ADS_strDispName, gstrNONE)
            Call SetProperty(recipient, mstrADS_COL_NAME_FIRST, ADS_strNameFirst, gstrNONE)
            Call SetProperty(recipient, mstrADS_COL_NAME_LAST, ADS_strNameLast, gstrNONE)
            Call SetProperty(recipient, mstrADS_COL_NAME_MID_INITIAL, ADS_strNameMidInitial, gstrNONE)
            Call SetProperty(recipient, mstrADS_COL_NOTES, ADS_strNotes, gstrNONE)
            Call SetProperty(recipient, mstrADS_COL_OFFICE, ADS_strOffice, gstrNONE)
            Call SetProperty(recipient, mstrADS_COL_PHONE_ASSISTANT, ADS_strPhoneAssistant, gstrNONE)
            Call SetProperty(recipient, mstrADS_COL_PHONE_BUS, ADS_strPhoneBus, gstrNONE)
            Call SetProperty(recipient, mstrADS_COL_PHONE_2_BUS, ADS_strPhone2Bus, gstrNONE)
            Call SetProperty(recipient, mstrADS_COL_PHONE_FAX, ADS_strPhoneFax, gstrNONE)
            Call SetProperty(recipient, mstrADS_COL_PHONE_HOME, ADS_strPhoneHome, gstrNONE)
            Call SetProperty(recipient, mstrADS_COL_PHONE_2_HOME, ADS_strPhone2Home, gstrNONE)
            Call SetProperty(recipient, mstrADS_COL_PHONE_MOBILE, ADS_strPhoneMobile, gstrNONE)
            Call SetProperty(recipient, mstrADS_COL_PHONE_PAGER, ADS_strPhonePager, gstrNONE)
            Call SetProperty(recipient, mstrADS_COL_POSTAL_ADDRESS, ADS_strPostalAddress, gstrNONE)
            Call SetProperty(recipient, mstrADS_COL_POSTAL_CODE, ADS_strPostalCode, gstrNONE)
            Call SetProperty(recipient, mstrADS_COL_STATE, ADS_strState, gstrNONE)
            Call SetProperty(recipient, mstrADS_COL_TITLE, ADS_strTitle, gstrNONE)

            Call SetProperty(recipient, mstrADS_COL_EMAIL_ADDR, strEmailAddr, gstrNONE)
            Call SetProperty(recipient, mstrADS_COL_REPLICATION_SENSITIVITY _
                                , mstrADS_REPLICATION_SENSITIVITY_DEFAULT, gstrNONE)
            Call SetProperty(recipient, mstrADS_COL_RFC_822_MAILBOX, strEmailAddr, gstrNONE)
            Call SetProperty(recipient, mstrADS_COL_TEXT_ENCODED_OR_ADDRESS _
                                , strTextEncodedORAddressPrefix _
                                    & Left(strrdnExchSav, cCH_OR_SURNAME) & ";" _
                                , gstrNONE)

            If Len(strMSMailPrefix) > 0 Then
                strMSMail = strMSMailPrefix & Left(strAliasNoSpace, cCH_OTHER_MB_ALIAS)
                strCCMail = "CCMAIL$" & ADS_strNameLast & gchCOMMA & gchSPACE _
                                        & ADS_strNameFirst & " at " & ADS_strOrganizationalUnit

                If ADS_strObjClass = gstrADS_CLASS_MB Then
                    rgstrOtherMailbox(0) = strMSMail
                    rgstrOtherMailbox(1) = strCCMail
                Else
                    rgstrOtherMailbox(0) = strCCMail
                    rgstrOtherMailbox(1) = strMSMail
                End If
    
                ' ()'s are necessary to pass the array in VBScript
                recipient.PutEx mADS_PROPERTY_UPDATE, CStr(mstrADS_COL_OTHER_MAILBOX), (rgstrOtherMailbox)
            End If
            '
            ' Set special mailbox/custom recipient properties
            '
            If ADS_strObjClass = gstrADS_CLASS_MB Then
                Call SetProperty(recipient, mstrADS_COL_DELIV_EXT_CONT_TYPES, mstrADS_DELIV_EXT_CONT_TYPES_DEFAULT, gstrNONE)

                Call SetProperty(recipient, mstrADS_COL_HOME_MDB _
                                    , "cn=Microsoft Private MDB,cn=" & strDN(ADS_strServer) _
                                        & ",cn=Servers ,cn=Configuration," _
                                        & "ou=" & strDN(ADS_strOrganizationalUnit) _
                                        & ",o=" & strDN(ADS_strOrganization) _
                                    , gstrNONE)
                Call SetProperty(recipient, mstrADS_COL_HOME_MTA _
                                    , "cn=Microsoft MTA,cn=" & strDN(ADS_strServer) _
                                        & ",cn=Servers ,cn=Configuration," _
                                        & "ou=" & strDN(ADS_strOrganizationalUnit) _
                                        & ",o=" & strDN(ADS_strOrganization) _
                                    , gstrNONE)
                Call SetProperty(recipient, mstrADS_COL_MAIL_PREFERENCE_OPTION, CStr(CInt(False)), gstrNONE)
                Call SetProperty(recipient, mstrADS_COL_MAPI_RECIPIENT, CStr(CInt(True)), gstrNONE)
                Call SetProperty(recipient, mstrADS_COL_MDB_USE_DEFAULTS, CStr(CInt(True)), gstrNONE)
                '
                ' Set NT Account Properties
                '
                Call SetNTAccountProperties(recipient, varSecurityID, varSecurityDescriptor)
            Else ' custom recipient
                Call SetProperty(recipient, mstrADS_COL_TARGET_ADDRESS _
                                    , "SMTP:" & strEmailAddr _
                                    , gstrNONE)
                Call SetProperty(recipient, mstrADS_COL_MAPI_RECIPIENT, CStr(CInt(False)), gstrNONE)
            End If
            '
            ' Save the properties
            '
            recipient.SetInfo

            Set recipient = Nothing
            Set cnRecipients = Nothing
        End If
    End If
End Sub

Private Sub GetSecurityIDDescriptor(precipient, pvarSecurityID, pvarSecurityDescriptor)
'
' GetSecurityIDDescriptor creates an NT account if create account was selected & returns a
' security ID & descriptor for the current domain & user.  It returns empty security id & 
' descriptor if account was not changed.
'
    Dim errSav
    Dim i
    Dim strDomain
    Dim strUser
    Dim varSecurityIDOld
    Dim varSecurityDescriptorOld

    If Len(ADS_strNTAcct) > 0 Then
        If ADS_bAddNTAcct Then
            On Error Resume Next

            Call NTAcct_Create(ADS_strNTAcct, ADS_strNTPassword, pvarSecurityID, pvarSecurityDescriptor)
        
            errSav = Err.Number
            On Error GoTo 0

            If errSav <> gerrNONE Then
                Err.Raise gerrADS_CANT_CREATE_NT_ACCOUNT, , gstrADS_MSG_ALERT_CANT_CREATE_NT_ACCOUNT
            End If
        Else
            '
            ' Get current security descriptor & security id
            '
            If IsEmpty(precipient) Then
                varSecurityIDOld = Empty
                varSecurityDescriptorOld = Empty
            Else
                On Error Resume Next
                precipient.GetInfoEx Array(mstrADS_COL_ASSOC_NT_ACCOUNT, mstrADS_COL_NT_SECURITY_DESCRIPTOR), 0

                errSav = Err.Number
                On Error GoTo 0

                Select Case errSav
                    Case gerrNONE
                        varSecurityIDOld = precipient.Get(mstrADS_COL_ASSOC_NT_ACCOUNT)
                        varSecurityDescriptorOld = precipient.Get(mstrADS_COL_NT_SECURITY_DESCRIPTOR)
                    Case gerrADS_PROPERTY_NOT_AVAILABLE
                        '
                        ' There is no property
                        '
                        Err.Clear

                        varSecurityIDOld = Empty
                        varSecurityDescriptorOld = Empty
                    Case Else ' Handle error in calling routine
                        Err.Raise CLng(errSav)
                End Select
            End If
            '
            ' Get Security ID for new nt acct & prepare updated security descriptor
            '
            On Error Resume Next

            Call NTAcct_GetSecurityIDDescriptor(varSecurityIDOld, varSecurityDescriptorOld _
                                                , ADS_strNTAcct, pvarSecurityID, pvarSecurityDescriptor)
        
            errSav = Err.Number
            On Error GoTo 0
        
            If errSav <> gerrNONE Then
                Err.Raise gerrADS_CANT_ASSOC_NT_ACCOUNT, , gstrADS_MSG_ALERT_CANT_ASSOC_NT_ACCOUNT
            End If
        End If
    Else
        pvarSecurityID = Empty
        pvarSecurityDescriptor = Empty
    End If
End Sub

Private Sub SetNTAccountProperties(precipient, pvarSecurityID, pvarSecurityDescriptor)
'
' SetNTAccountProperties sets associated nt account & security descriptor properties.
'
    If Not IsEmpty(pvarSecurityID) And Not IsEmpty(pvarSecurityDescriptor) Then
        precipient.Put CStr(mstrADS_COL_ASSOC_NT_ACCOUNT), (pvarSecurityID)

        precipient.Put CStr(mstrADS_COL_NT_SECURITY_DESCRIPTOR), (pvarSecurityDescriptor)
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
' GetConfigData reads the "Private MDB" object to get configuration data.  It returns:
'   
'   . the SMTP address extension.
'   . the organization/recipient (OR) address prefix
'   . the prefix for a row of Other MB.
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

    '
    ' Get configuration info in preparation for adding
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
            On Error GoTo 0

            Err.Clear

            pstrMSMailPrefix = gstrNONE
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
    '
    ' Clear module error variables
    '
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
        Call SetErr(gerrADS_DUPLICATE_RECIPIENT, gstrADS_MSG_ALERT_DUPLICATE_RECIPIENT)
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
' strLDAPSearch handles special characters in an LDAP search string as per rfc2254.
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

Public Sub ADS_Get(pstrADsPathRecipient)
'
' Get opens the passed recipient & populates properties.
'
    Dim recipient
    Dim rgbyteSecurityID
    '
    ' Get the mailbox/custom recipient object
    '
    Set recipient = GetObject(pstrADsPathRecipient)

    ADS_strObjClass = recipient.class

    ADS_strAlias = recipient.uid
    ADS_strAssistant = recipient.secretary
    ADS_strCity = recipient.l
    ADS_strCompany = recipient.Company
    ADS_strCountry = recipient.co
    ADS_strDispName = recipient.cn

    ADS_strNameFirst = recipient.givenName
    ADS_strNameLast = recipient.sn
    ADS_strNameMidInitial = recipient.initials
    ADS_strNotes = recipient.info

    ADS_strOffice = recipient.physicalDeliveryOfficeName
    ADS_strPhoneFax = recipient.facsimileTelephoneNumber
    ADS_strPhoneHome = recipient.homephone
    ADS_strPhoneMobile = recipient.mobile
    ADS_strPhonePager = recipient.pager
    ADS_strPostalAddress = recipient.postalAddress
    ADS_strPostalCode = recipient.postalCode
    ADS_strState = recipient.st
    '
    ' Following properties require special error handling because they return "property not 
    ' defined" error when the property is empty.
    '
    ADS_strDept = strGetProperty(recipient, mstrADS_COL_DEPT)
    If Err.Number <> gerrNONE Then
        Exit Sub
    End If

    ADS_strPhoneBus = strGetProperty(recipient, mstrADS_COL_PHONE_BUS)
    If Err.Number <> gerrNONE Then
        Exit Sub
    End If

    ADS_strTitle = strGetProperty(recipient, mstrADS_COL_TITLE)
    If Err.Number <> gerrNONE Then
        Exit Sub
    End If
    '
    ' Because the following property names include a dash, "object.get(propertyName)" syntax
    ' must be used.
    '
    ADS_strPhoneAssistant = strGetProperty(recipient, mstrADS_COL_PHONE_ASSISTANT)
    If Err.Number <> gerrNONE Then
        Exit Sub
    End If
     
    ADS_strPhone2Bus = strGetProperty(recipient, mstrADS_COL_PHONE_2_BUS)
    If Err.Number <> gerrNONE Then
        Exit Sub
    End If
     
    ADS_strPhone2Home = strGetProperty(recipient, mstrADS_COL_PHONE_2_HOME)
    If Err.Number <> gerrNONE Then
        Exit Sub
    End If
    '
    ' Handle class specific properties
    '
    If ADS_strObjClass = gstrADS_CLASS_MB Then
        '
        ' Gather NT account info.  Associated nt account is not placed in the adsi cache
        ' by default.  Move it into the adsi cache & then get it's value.
        '
        On Error Resume Next

        recipient.GetInfoEx Array(mstrADS_COL_ASSOC_NT_ACCOUNT), 0
        Select Case Err.Number
            Case gerrNONE
                On Error GoTo 0

                rgbyteSecurityID = strGetProperty(recipient, mstrADS_COL_ASSOC_NT_ACCOUNT)
                If Err.Number <> gerrNONE Then
                    Exit Sub
                End If

                ADS_strNTAcct = NTAcct_strAccount(rgbyteSecurityID)
            Case gerrADS_PROPERTY_NOT_AVAILABLE
                '
                ' There is no associated NT account
                '
                On Error GoTo 0

                ADS_strNTAcct = gstrNONE
            Case Else ' Handle error in calling routine
                Exit Sub
        End Select
    Else ' Custom Recipient
        ADS_strEmailAddr = recipient.mail
    End If
     
    Set recipient = Nothing
End Sub

Private Function strGetProperty(precipient, pstrProperty)
'
' strGetProperty uses "object.get(propertyName)" syntax to retrieve a property.  This syntax 
' returns a property not defined error when the property is empty.
'
    On Error Resume Next

    strGetProperty = precipient.Get(pstrProperty)
    '
    ' If error "property not defined", clear error
    '
    If Err.Number = gerrADS_PROPERTY_NOT_DEFINED Then
        strGetProperty = gstrNONE

        Err.Clear
    End If
End Function

Public Sub ADS_Delete(pstrADsPathRecipient)
'
' Delete deletes the the passed mailbox/custom recipient.
'
    Dim cnRecipients
    Dim recipient
    '
    ' Get the mailbox/custom recipient object
    '
    Set recipient = GetObject(pstrADsPathRecipient)
    
    Set cnRecipients = GetObject(recipient.Parent)
    '
    ' Delete the mailbox/custom recipient.
    '
    Call cnRecipients.Delete(recipient.class, recipient.name) 

    Set recipient = Nothing
    Set cnRecipients = Nothing
End Sub
%>