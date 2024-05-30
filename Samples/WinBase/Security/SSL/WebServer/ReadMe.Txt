SSL/WebServer

This sample is intended as a demonstration of the SSPI interface to the SSL
protocols for secure, authenticated communication provided by secur32.dll and
schannel.dll on Microsoft Windows NT 4.0 w/ SP4, Microsoft Windows 2000 and
Windows 98. On Windows 98, the SSPI interface for SSL will only provide
authentication and not encryption services.

WebServer shows the server side interface while the companion sample WebClient
shows the client side implementation.

WebServer shows how the programmer might conceivably interact directly and
securely with a web browser such as Internet Explorer or a stand-alone, SSL
aware winsock client as demonstrated by the WebClient sample. In this
environment, WebServer would replace a Web Server such as Internet Information
Server and give the programmer full control over the server to client
interaction. The sample shows how to retrieve a server authentication
certificate and present it to the client for validation.

The heart of using the SSL protocols for secure communication is management of
the certificates required for client/server identification and authentication.
On the server side, we must generate and install a X.509 v3 SSL-compatible
server authentication certificate. This server authentication certificate
identifies a server and is used by clients to authenticate a server that the
client wants to access. You may also require that the server to be able to
authenticate the client, in which case, you must generate and install a X.509
v1 and v3 SSL-compatible client authentication certificate.

Generating and installing these certificates correctly is neccessary for proper
functioning of this sample. A possible method for installing the Server
Certificate are detailed below.

Using Microsoft Certificate Server

1) Point your web browser to a machine running Microsoft Internet Information
   Server (IIS) with Microsoft Certificate Server installed. IIS and
   Certificate Server are provided with the Windows NT Option Pack. For
   example, a server named winbase has IIS and Certificate Server installed.
   In this case, you could type "http://winbase/certsrv" in your browser
   address line.

2) Click on Certificate Enrollment Tools/Request a Client Authentication
   Certificate

3) Fill out the enrollment form. The Name field must match the name of the
   server machine exactly. Click on the Advanced button and select "Server
   Authentication" from the Usage drop-down list. Click on "Submit Request"
   and then Download from the next page. You can verify that the certificate
   was installed by using the Certificate Manager utility.

OS Version Caveats:

NT4 SP4:         In the Advanced enrollment dialog, check the box marked "Allow
                 Keys to be Exported".
NT5:             In the advanced dialog, you must choose "Microsoft RSA SChannel
                 Cryptographic Provider" from the CSP list.
NT5 Beta 2 only: You must check the "Use Local Machine Store" checkbox. This is
                 not neccesary on NT5 Beta 3.

Assuming that you followed the instructions above, you may now run the
webserver application. Assuming that you are running this sample on a machine
named winbase3, the following command-line parameters are appropriate:

webserver -Uwinbase3 -v
