*******************************  RASHOST  *************************************

(readme - last revised April 1997, 
 based on testing with NT 4.0 Service Pack 3)


PURPOSE:  verifying basic functionality sample security DLL.


BUILD REQUIREMENTS: headers (.h) and .lib's from the build.  Then run NMAKE.


TEST REQUIREMENTS:  1 NT RAS server, 1 NT RAS client, 
                    both with modem and phone line.


STEPS TO RUN TEST: 

- Edit the registry on the server:

  - Go to  HKLM\SOFTWARE\Microsoft\RAS.  
  - Add a key SecurityHost
  - To that key, add a value named DLLPath of type REG_SZ and give full path
    to the security dll.  (example:  d:\rashost\rashost.dll)

    Example regini script:

    \Registry\Machine
        Software
           Microsoft
              RAS
                 SecurityHost
                    DLLPath = REG_SZ d:\rashost\rashost.dll

- Restart the RAS server

- Attach NTSD to RASSRV.EXE to see debug output from the security DLL.

- From RAS client, configure phonebook entry for post-dial terminal window
  (Edit -> Script -> "After dialing login" -> Pop up a terminal window)
  and dial into the RAS server with appropriate credentials and verify result.

  Currently the security DLL is set to grant access to users whose name 
  starts with 'e'.  This is case-sensitive.  Anyone else attempting to connect 
  will get dropped by the security DLL, regardless of whether their credentials
  are otherwise valid to the server.



SAMPLE TEST CASES:

- username starting with 'e' is granted access (successful RAS connection).

- username not starting with 'e' is denied access (expect RAS error 618).

- credentials (username) used for security dll access must match those used for 
  RAS authentication, or else the connection will be rejected.  (Expect RAS 
  error 629 and the security dll's output will indicate access was granted).


Below is sample debug output for the first two cases.

=========== SAMPLE NTSD OUTPUT FOR VALID ACCESS (username = "eric") ===========

RasSecurityDialogBegin
Returning ERROR_SUCCESS from RasSecurityDialogBegin
CallWorkerThread.
Event 568 created.
gpfnReceiveProc returned: 600
Calling WaitForSingleObject.
The state of the object is signaled.
Buffer= e
gpfnReceiveProc returned: 600
Calling WaitForSingleObject.
The state of the object is signaled.
Buffer= r
gpfnReceiveProc returned: 600
Calling WaitForSingleObject.
The state of the object is signaled.
Buffer= i
gpfnReceiveProc returned: 600
Calling WaitForSingleObject.
The state of the object is signaled.
Buffer= c
gpfnReceiveProc returned: 600
Calling WaitForSingleObject.
The state of the object is signaled.
Buffer=
Returning Buffer: eric
Returning size: 4
gpfnReceiveProc returned: 600
Calling WaitForSingleObject.
The state of the object is signaled.
Buffer=
ricurning Buffer:
Returning size: 0

UserName: eric

DomainName: (RASHOST - Unknown)
Access granted.


========== SAMPLE NTSD OUTPUT FOR INVALID ACCESS (username = "scott") =========

RasSecurityDialogBegin
Returning ERROR_SUCCESS from RasSecurityDialogBegin
CallWorkerThread.
Event 620 created.
gpfnReceiveProc returned: 600
Calling WaitForSingleObject.
The state of the object is signaled.
Buffer= s
gpfnReceiveProc returned: 600
Calling WaitForSingleObject.
The state of the object is signaled.
Buffer= c
gpfnReceiveProc returned: 600
Calling WaitForSingleObject.
The state of the object is signaled.
Buffer= o
gpfnReceiveProc returned: 600
Calling WaitForSingleObject.
The state of the object is signaled.
Buffer= t
gpfnReceiveProc returned: 600
Calling WaitForSingleObject.
The state of the object is signaled.
Buffer= t
gpfnReceiveProc returned: 600
Calling WaitForSingleObject.
The state of the object is signaled.
Buffer=
Returning Buffer: scott
Returning size: 5
gpfnReceiveProc returned: 600
Calling WaitForSingleObject.
The state of the object is signaled.
Buffer=
cottrning Buffer:
Returning size: 0

UserName: scott

DomainName: (RASHOST - Unknown)
Access denied.
RasSecurityDialogEnd

===============================================================================
