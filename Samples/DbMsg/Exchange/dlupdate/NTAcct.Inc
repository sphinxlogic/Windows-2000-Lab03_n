<%
'<!--Mailbox Maintenance Sample Application-->
'<!--NTAcct.inc : NT Account Manager -->
'<!--Copyright (c) Microsoft Corporation 1993-1998. All rights reserved.-->
'
' NTAcct.inc contains constants, properties, & routines for handling the Windows NT account
' management object.
'
Public Sub NTAcct_PrepareSecurityDescriptor(prgbytSecurityIDOld, prgbytSecurityDescriptorOld, prgbytSecurityIDNew, _
                                            prgbytSecurityDescriptor)
'
' PrepareSecurityDescriptor returns a security descriptor for the passed owner security id.
'   
'   Input:
'       prgbytSecurityIDOld                     Former owner security id
'       prgbytSecurityDescriptorOld             Former security descriptor
'       prgbytSecurityIDNew                     New owner security id
'
'   Output:
'       
'       prgbytSecurityDescriptor 
'      
    Dim strDomainOld
    Dim strUserOld
    Dim strDomain
    Dim strUser
    Dim ntAcct

    Set ntAcct = CreateObject("MSExchange.AcctMgmt")

    Call ntAcct.GetNameFromSid(strDomain, (prgbytSecurityIDNew), strDomain, strUser)
    '
    ' Check value of former Security descriptor to determine whether creating a security descriptor
    ' or modifying an existing one
    '
    If IsEmpty(prgbytSecurityDescriptorOld) Then
        Call ntAcct.GenerateSecDescriptor(strDomain, strUser, prgbytSecurityDescriptor)
    Else
        Call ntAcct.GetNameFromSid(strDomainOld, (prgbytSecurityIDOld), strDomainOld, strUserOld)

        Call ntAcct.ChangeOwnerOfSecDescriptor(strDomainOld, strUserOld, strDomain, strUser, (prgbytSecurityDescriptorOld), prgbytSecurityDescriptor)
    End If

    Set ntAcct = Nothing
End Sub
%>