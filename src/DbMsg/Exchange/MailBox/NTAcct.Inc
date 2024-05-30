<%
'<!--Mailbox Maintenance Sample Application-->
'<!--NTAcct.inc : NT Account Manager -->
'<!--Copyright (c) Microsoft Corporation 1993-1998. All rights reserved.-->
'
' NTAcct.inc contains constants, properties, & routines for handling the Windows NT account
' management object.
'
Dim mntAcct

Private Sub InitNtAcct()
'
' InitNtAcct creates an ntAcct object.
'
    Set mntAcct = CreateObject("MSExchange.AcctMgmt")
End Sub

Public Sub NTAcct_Create(pstrNTAcct, pstrPassword, pvarSecurityID, pvarSecurityDescriptor)
'
' Create establishes a new NT account & returns a security ID & descriptor.
'
    Dim strDomain
    Dim strUser

    Call InitNtAcct()

    Call DomainUserFromAccount(pstrNTAcct, strDomain, strUser)

    Call mntAcct.NtAccountCreate(strDomain, strUser, pstrPassword, gstrNone, gstrNone)
    
    Call GetSecIDDesc(strDomain, strUser, pvarSecurityID, pvarSecurityDescriptor)

    Set mntAcct = Nothing
End Sub

Public Sub NTAcct_GetSecurityIDDescriptor(pvarSecurityIDOld, pvarSecurityDescriptorOld _
                                            , pstrNTAcct, pvarSecurityID, pvarSecurityDescriptor)
'
' GetSecurityIDDescriptor returns a security ID for the passed nt account &
' & returns an update security descriptor.
'
    Dim strDomainOld
    Dim strUserOld
    Dim strDomain
    Dim strUser

    Call InitNtAcct()

    Call DomainUserFromAccount(pstrNTAcct, strDomain, strUser)

    Call mntAcct.GetSidFromName(strDomain, strUser, pvarSecurityID)
    '
    ' Check value of former Security descriptor to determine whether creating a security descriptor
    ' or modifying an existing one
    '
    If IsEmpty(pvarSecurityDescriptorOld) Then
        Call mntAcct.GenerateSecDescriptor(strDomain, strUser, pvarSecurityDescriptor)
    Else
        Call mntAcct.GetNameFromSid(strDomainOld, (pvarSecurityIDOld), strDomainOld, strUserOld)

        Call mntAcct.ChangeOwnerOfSecDescriptor(strDomainOld, strUserOld, strDomain, strUser, (pvarSecurityDescriptorOld), pvarSecurityDescriptor)
    End If

    Set mntAcct = Nothing
End Sub

Public Function NTAcct_strAccount(prgbyteSecurityID)
'
' strAccount returns domain name & user ID for an existing account.
'
    Dim strDomain
    Dim strUser

    Call InitNtAcct()

    Call mntAcct.GetNameFromSid(strDomain, (prgbyteSecurityID), strDomain, strUser)

    NTAcct_strAccount = strAccountFromDomainUser(strDomain, strUser)

    Set mntAcct = Nothing
End Function

Private Sub GetSecIDDesc(pstrDomain, pstrUser, pvarSecurityID, pvarSecurityDescriptor)
'
' GetSecIDDesc returns a security ID & descriptor for the passed user.
'
    Call mntAcct.GetSidFromName(pstrDomain, pstrUser, pvarSecurityID)

    Call mntAcct.GenerateSecDescriptor(pstrDomain, pstrUser, pvarSecurityDescriptor)
End Sub

Private Function strAccountFromDomainUser(pstrDomain, pstrUser)
    Dim strNTAcct

    If Len(pstrDomain) > 0 Then
        strNTAcct = pstrDomain & gchBACK_SLASH & pstrUser
    Else
        strNTAcct = pstrUser
    End If

    strAccountFromDomainUser = strNTAcct
End Function

Private Function DomainUserFromAccount(pstrNTAcct, strDomain, strUser)
    Dim iNTAcctBackslash

    iNTAcctBackslash = Instr(pstrNTAcct, gchBACK_SLASH)
    
    If iNTAcctBackslash > 0 And iNTAcctBackslash < Len(pstrNTAcct) Then
        strDomain = Left(pstrNTAcct, iNTAcctBackslash - 1)
        strUser = Mid(pstrNTAcct, iNTAcctBackslash + 1)
    Else
        strDomain = gstrNONE
        strUser = pstrNTAcct
    End If
End Function
%>