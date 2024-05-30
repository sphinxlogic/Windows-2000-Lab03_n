THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1998-1999.  Microsoft Corporation.  All rights reserved.

*** This is the README for the LsaSamp Platform SDK sample ***

The LSA Policy documentation, which used to be included with this sample 
as Lsaapi.hlp, has been updated and moved to the Platform SDK documentation. 
It is covered in the section "LSA Policy."

Managing user privileges can be achieved programmatically using the
following steps:

1. Open the policy on the target machine with LsaOpenPolicy(). To grant
   privileges, open the policy with 
   POLICY_CREATE_ACCOUNT | POLICY_LOOKUP_NAMES | POLICY_VIEW_LOCAL_INFORMATION
   access. To revoke privileges, open the policy with POLICY_LOOKUP_NAMES access.

2. Obtain a SID (security identifier) representing the user/group of
   interest. The LookupAccountName() and LsaLookupNames() APIs can obtain a
   SID from an account name.

3. Call LsaAddAccountRights() to grant privileges to the user(s)
   represented by the supplied SID.

4. Call LsaRemoveAccountRights() to revoke privileges from the user(s)
   represented by the supplied SID.

5. Close the policy with LsaClose().

To successfully grant and revoke privileges, the caller needs to be an
administrator on the target system.

When targetting a domain controller for privilege update operations,
be sure to target the primary domain controller for the domain.
The privilege settings are replicated by the primary domain controller
to each backup domain controller as appropriate.  The NetGetDCName()
Lan Manager API call can be used to get the primary domain controller
computer name from a domain name.

For a list of privileges which may be granted using this sample, consult 
winnt.h, and search for SE_ASSIGNPRIMARYTOKEN_NAME.

For a list of logon rights, which can also be assigned using this
sample code, consult ntsecapi.h, and search for SE_BATCH_LOGON_NAME

The LSA API LsaEnumerateAccountRights() can be used to determine which
privileges have been granted to an account.

The LSA API LsaEnumerateAccountsWithUserRight() can be used to determine
which accounts have been granted a specified privilege.

NOTE: These LSA APIs are currently implemented as Unicode only.

This sample will grant the privilege SeServiceLogonRight to the account
specified on argv[1].

You can use domain\account as argv[1]. For instance, mydomain\scott will
grant the privilege to the mydomain domain account scott.

The optional target machine is specified as argv[2], otherwise, the
account database is updated on the local machine.

The LSA APIs used by this sample are Unicode only.
