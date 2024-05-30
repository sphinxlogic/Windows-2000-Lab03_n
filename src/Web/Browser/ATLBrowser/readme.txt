Description 

This sample application demonstrates how to host the WebBrowser 
Control in a C++ application using ATL and Visual C++ 6.0. In addition 
to demonstrating use of methods and events exposed by the WebBrowser 
Control, the sample implements the advanced hosting interfaces for 
further customizing the behavior of the WebBrowser Control. 

More Details

The WebBrowser Control exposes a set of methods, properties and events 
which allow a hosting application to exercise control over such things 
as Web and local file system navigation, printing, changing font sizes 
and other typical browser functionality. This sample shows you how to 
utilize these methods, properties and events in your hosting application. 

In addition, this sample implements the advanced hosting interfaces 
which are needed to further customize the operation of the WebBrowser 
Control. The advanced hosting interfaces implemented/demonstrated by 
this sample application include: 

IDocHostUIHandler: allows control over various user interface elements 
such as preventing text selection in Web documents, hiding or altering 
context menu, modifying translated keystrokes, providing an alternate 
set of user preferences from those specified for Internet Explorer, 
and modifying default scroll bar and window border behavior. 

IDocHostShowUI: allows the hosting application to control the display 
of help and message dialog boxes. 

This sample also demonstrates how applications hosting the WebBrowser 
Control can also exercise additional control over certain aspects of 
downloading and execution that normally occur on Web pages. This allows 
the hosting application to prevent images, sounds, client-side scripting, 
Java applets and ActiveX controls from being downloaded or executed. You 
can learn more about this in the Download Control section of the Browser 
Overview document.

In addition, this sample demonstrates how to access other Internet Explorer 
functionality that is not directly exposed by the WebBrowser Control, such 
as showing the "Internet Options..." and "Find (on this page)" dialogs. 

Finally, the sample demonstrates how to extend the Dynamic HTML Object Model 
with the window.external object. This allows Web page scripts to access 
desired custom functionality that is provided by the hosting application. 
This is demonstrated by navigating to the AtlBrowser.htm file included with 
the sample application.


Browser/Platform Compatibility

This sample application requires Internet Explorer 4.0x or Internet 
Explorer 5. While you are not required to utilize Internet Explorer as 
your default browser of choice, it must be installed on the target 
computer. Hence, applications that host the WebBrowser Control must 
also redistribute Internet Explorer. Refer to this Licensing & 
Distribution article for more information about redistributing 
Internet Explorer with your application. 

Usage

As discussed in this Application Types overview to Reusing the WebBrowser 
Control, there are two common scenarios for hosting the WebBrowser Control 
in applications: 

Web browsing applications host the WebBrowser control in order to focus 
development efforts on new and original browsing features. The advantages to 
basing browser applications on the WebBrowser control stem from avoiding the 
drudgery of implementing functionality already provided, as well as benefiting 
from the control's extensibility and customization features. This approach 
also leverages the control's standards compliance and provides compatibility 
with Web pages designed to take advantage of Internet Explorer. 

Traditional applications host the WebBrowser Control in order to integrate 
a browsing experience. This ranges from browsing targeted content on the 
Web to presenting a rich user interface based upon Dynamic HTML. The advantages 
to creating elements of the application's user interface with Dynamic HTML 
include easier localization of content, built-in presentation and printing 
support, and streamlining the development process by allowing user interface 
specialists complete control over presentation elements. 

Related Links