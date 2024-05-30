SUMMARY

VBFTP is a sample that implements FTP connection, download, and upload using the WinInet FTP API from Visual Basic. It demonstrates the APIs and techniques to set FTP connection attributes and transfer mode that are not exposed in the MS Internet Transfer Control. 

The sample requires Visual Basic SP2 or Visual Studio SP2 installed to run because it uses the updated comctl32.ocx from those Service Packs. 

When adding FTP functionality to your application, it is important to understand the capability and limitation of each of the different Internet technologies. At the lowest level, you could use the Microsoft Winsock Control to send commands directly to FTP server port 21. The sequence and syntax of the commands you send to the server would have to follow the specification of the FTP protocol. The WinInet FTP API wraps the socket code and most low-level FTP commands and provides a set of much simpler task-oriented APIs that do not require detailed knowledge of FTP protocol. However, there is a chance that some FTP servers use FTP commands not implemented by WinInet. If this happens, you have to use the Microsoft Winsock Control to communicate with the server directly at the protocol level. Test your FTP server with the VBFTPJR sample before you decide whether to choose WinInet API or the Winsock Control. The Microsoft Internet Transfer Control, on the other hand, offers a more simplified interface than WinInet but offers less flexibility and cannot be used if you want to customize the connection and transfer mode. 

If you are using a proxy to access an FTP server, the proxy has to be capable of handling FTP commands and cannot be a CERN proxy. Please see the following article in the Microsoft Knowledge Base for more information: 


   ARTICLE-ID: Q166961
   TITLE     : HOWTO: FTP with CERN-Based Proxy Using WinInet API
