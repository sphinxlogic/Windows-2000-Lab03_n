Displaying Trusted Domains


The DISPTRUS sample enumerates the trusted domains on the target machine, and
displays them on the standard output device. This list matches (minus sorting)
the list of domains presents by the WinNT Dacl editor. For practical
applications, replace the AddTrustToList function with linked-list management
code, then use the resulting list later on in the application.

The optional target machine is specified as argv[1].

For a Windows NT workstation that is not a member of a domain, the only
relevant trusted domain is the account domain of the machine. The sample
detects a non-member workstation by checking if the primary domain Sid is NULL.

For a Windows NT workstation that is a member of a domain, the relevant trusted
domains are the account domain, the primary domain, and the trusted domain(s)
of the primary domain.

For a Windows NT domain controller, the trusted domains are the account domain
and the trusted domains.
