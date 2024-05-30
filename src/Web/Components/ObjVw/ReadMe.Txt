//-------------------------------------------------------------------------
// Readme.txt
//-------------------------------------------------------------------------
// Objvw: A sample that illustrates using IE's Automation and scripting interfaces
// from a contained control
//-------------------------------------------------------------------------
// (C) Copyright 1992-1999 by Microsoft Corporation.  All rights reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//-------------------------------------------------------------------------

PURPOSE
=======

This sample: 

   - illustrates accessing IE's Automation model and scripting model from within a 
     contained ATL control.  

   - illustrates enumerating all ActiveX controls and links in a page and sub 
     pages.  This includes an algorithm for recursively enumerating floating 
     frames and framesets.

   - illustrate implementing an event sink in a ATL control.

   - illustrates using the DocumentComplete event to identify when pages have been 
     completely loaded.  DocumentComplete is fired for each frame in a document.
     DocumentComplete returns the IDispatch for the document that has completed 
     loading.  The outermost frame will always fire last so by comparing the 
     IDispatch pointer returned by DocumentComplete with the IDispatch of the 
     outer frame, it is possible to tell when all frames have completely loaded.

   - Illustrates marking an ATL control "Safe for scripting".

   - Note this sample must be executed outside a frame (will not work within a frame)
     because it is designed to connect with events in the top level (Web
     Browser Control).

FILES SUPPLIED
==============
     This is a standard VC 5.0 project.  All code relevant to the sample is located 
     in ObjVwCtl.cpp and ObjVwCtl.h.

RUNNING THE SAMPLE
==================
     Compile the sample with VC 5.0 ( this will also register the control ).  Open 
     the file TestCtl.htm.  This file contains an instance of the control and links 
     to several test pages.  

     NOTE: You may need to change the #import statements in ObjVwCtl.h to point to your
     Windows system directory.

SINKING EVENTS
==============
     This ATL control directly implements the DWebBrowserEvents2 interface.  An 
     alternative approach would be to implement the sink as a separate object and 
     use CComObject::CreateObject to instantiate the sink.  The event sink is 
     connected and disconnected in the CObjVw::SetClientSite function. 

NOTES
=====

* With Internet Explorer 5.0, you may receive the following warning when compiling:

"..\objvw\debug\mshtml.tli(70296) : warning C4049: compiler limit : terminating line number emission"

This warning indicates that you will not be able to step into COM compiler support
source for some calls into MSHTML. This minor problem will have no effect on the
execution of OBJVW and can be safely ignored.




