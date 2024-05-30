=======================================================================

Release notes for the IISLog Sample of the Internet Client Software 
Development Kit:

Copyright (c) Microsoft Corporation, 1999
=======================================================================

Description:

The IISLog sample demonstrates how to receive and parse the IE4 user
logging profile from the server side. When the user subscribes to a
channel which has hit count logging specified and they later browse to
those pages, IE40 will log the hit counts and post them back to the
server when the channel subscribed to gets updated. The user can
globally turn logging off from the control panel UI if desired. IE40
uses the W3C extended server log file format and may encode a posted
string as directed in the CDF file associated with the channel
subscribed to. This sample shows how to parse the extended server log
file format and merge to a W3C flexible log file format. This sample
also shows how to decode a posted string if it is encoded using
pluggable protocol filters. IISLog.htm is a sample page to post a string
to logparse.dll on the server side. The posted string should simulate
the extended server log file format.

Building procedure:

The Logparse ISAPI DLL was created and built using VC++ 6.0 ISAPI
extension wizard. VC++ 6.0 is required to build this sample. It links
to urlmon.lib to obtain the pluggable protocol filters.

Install the ISAPI DLL:

You need IIS 4.0 or greater to run this sample. Copy LogParse.dll to
that server's scripts directory. A detailed description of how to
install an ISAPI DLL can be found in the MSDN library.
