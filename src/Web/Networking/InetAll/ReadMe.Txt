INetAll sample is a client application that can download files using FTP URL, HTTP
URL or FILE URL. It implements FTP and HTTP URL access using Wininet functions, and 
FILE URL access using Win32 CopyFile API.

This sample uses InternetOpenUrl, InternetReadFile to do FTP and HTTP access. When
accessing a FTP server with direct Internet access or a TIS proxy server, it also uses
the INTERNET_FLAG_RAW_DATA flag in InternetOpenUrl and InternetFindNextFile to 
enumerate the directories and files on the FTP server. When a CERN proxy is used to do 
FTP, the proxy server uses FTP protocol to communication with the FTP server, and HTTP 
Protocol with the client.  You can not use INTERNET_FLAG_RAW_DATA with a CERN proxy 
server. The following diagram shows how a FTP request is forwarded using a CERN-compatible 
proxy service.

(Better viewed with fixed with font such as Courier.)
  Get ftp://host.com/root/test.doc HTTP 1.0        FTP Request
  |=========|                 |=============|          |=============|
  |         |---------------->| Cern-based  |--------->|             |
  | Client  |    HTTP         | Proxy Server|   FTP    |  Ftp Server |
  |         |<----------------|             |<---------|             |
  |=========|                 |=============|          |=============|
	HTTP/1.0 200 <document>                  FTP Response

To pass username and password to InternetOpenUrl, the sample internally constructs a 
URL in the following format: http://username:password@server:port/path

To enumerate directories and files for a FILE URL, the sample uses WNetOpenEnum, 
WNetEnumResource, WNetClose to enumerate shares given a machine name; and 
FindFileFile, FindNextFile, FindClose to enumerate sub-directories and files 
of a complete UNC name.
