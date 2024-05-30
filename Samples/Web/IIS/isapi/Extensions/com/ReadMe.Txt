Description:

InvokObj is a sample ISAPI extension to demonstrate invoking
a method from an ActiveX Automation Server.  Included with the
project is an automation dll, GetUserName.dll.  This is a simple
ATL-based component with a single method, GetMyName(), which
returns the user name for the context in which the component is
running.  The InvokObj sample demonstrates creating an instance
of the object from within and ISAPI extension, invoking the
GetMyName() method, and returning the information to the browser. 

This sample uses Microsoft specific compiler extensions included
with Microsoft Visual C++, and requires version 5.0 of the compiler
or later.

To Install:

Build the InvokObj.dsw project and copy the resulting InvokObj.dll
file into a virtual directory containing execute permissions.

Register GetUserName.dll with the following command line.  If you
do not do this, the browser will report error 800401f3:

   regsvr32 getusername.dll

To Run:

Reference the InvokObj.dll file as a URL from a browser.  For
example, the following URL entered on the address line of
Internet Explorer will demonstrate the dll:

   http://server/scripts/invokobj.dll

Disclaimer:

This sample, and the included automation dll, is provided for the
purposes of demonstrating an ISAPI extension.  It has not been
tested for use in a production environment and no support will
be provided for use in a production environment.