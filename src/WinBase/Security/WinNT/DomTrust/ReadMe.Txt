Managing Trusted Domains


The DOMTRUST sample demonstrates how to manage Windows NT trusted domains at
the domain controller level.

The first command line argument indicates the name of the new or existing
trusted domain to create or modify.

The second command line argument indicates the new password for the
trusted domain specified in the first argument.

The optional third argument indicates the domain name that is the target
of the trusted domain update operation. If this argument is not specified,
the update occurs on the local domain. Note that this sample will not
allow a trusted domain update to occur on a non-domain controller.

This sample works correctly compiled ANSI or Unicode. Note that the Ported LAN
Manager functions are Unicode only, and LSA API functions are also Unicode
only.
