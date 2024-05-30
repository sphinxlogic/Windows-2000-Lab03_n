SSL/WebClient

This sample is intended as a demonstration of the SSPI interface to the SSL/PCT
protocols for secure, authenticated communication provided by secur32.dll and
schannel.dll on Microsoft Windows NT 4.0 w/SP4, Microsoft Windows 2000 and
Windows 98. On Windows 98, the SSPI interface for SSL will only provide
authentication and not encryption services. If you require full SSL/PCT
authentication and encryption services on a Windows 9x client, then a possible
solution is to use the WinInet APIs to establish a HTTPS connection to the
webserver application. A module that accomplishes this, WI_SSL_Client.cpp, can
be found in the WebClient directory.

WebClient shows the client side interface while the companion sample WebServer
shows the server side implementation.

WebClient shows how the programmer might conceivably interact directly and
securely with a web server such as IIS. In this environment, WebClient would
replace a browser such as Internet Explorer and give the programmer full
control over the server to client interaction.

The heart of using the SSL/PCT protocols for secure communication is management
of the certificates required for client/server identification and
authentication. On the server side, we must generate and install a X.509 v3
SSL-compatible server authentication certificate. This server authentication
certificate identifies a server and is used by clients to authenticate a server
that the client wants to access. On the client side, we must generate and
install a X.509 v1 and v3 SSL-compatible client authentication certificate.
This client authentication certificate identifies a client and is used by
servers to authenticate a client that requests server access.

Generating and installing these certificates correctly is neccessary for proper
functioning of this sample. One possible method for installing the Client
Certificate is detailed below.

Using Microsoft Certificate Server

1) Connect to a machine running Microsoft Internet Information Server (IIS)
   with Microsoft Certificate Server installed. IIS and Certificate Server are
   provided with the Windows NT Option Pack. For the purposes of this sample, we
   will assume that our certificate server is accessible at
   http://winbase/certsrv

2) Click on Certificate Enrollment Tools/Request a Client Authentication
   Certificate

3) Fill out the enrollment form. At the minimum, provide as part of the Name
   field an easily remembered term that you will be able to use from the
   WebClient application. For instance, the full name for the client
   certificate might be "DaveMo the client". Click on "Submit Request" and
   then Download from the next page. You can verify that the certificate was
   installed by using the CERTMGR utility that ships with the Platform SDK.

