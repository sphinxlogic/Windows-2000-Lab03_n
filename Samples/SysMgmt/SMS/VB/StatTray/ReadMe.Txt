****************************************************************
  Copyright (c)1999 Microsoft Corporation, All Rights Reserved
****************************************************************

1. What StatTray Does & How

    This sample monitors the status of a site by continually looking
    at the "Status" property of an instance of SMS_SummarizerSiteStatus 
    for the site the user connected to.  The sample uses a Timer control
    to perform the update on a user specified interval, that can be changed
    by right clicking on the icon in the system tray, and selecting a 
    new interval.

2. Running the Sample

    Open up the StatTray.vbp file in Visual Basic and run the program.
    Fill in the information fields on the connection box, and press Connect.
    An icon will appear in the system tray that represents the status of the 
    site based on the following colors:

    Green = Site is OK
    Yellow = Site has Warnings
    Red = Site has Errors

3. Requirements

    Requires: Visual Basic 6.0 or greater to compile and run
    Runs on: NT 4.0+ 
    Windows Management Instrumentation (WMI) must be installed.

4. Compiling the Sample

    Note: Compiling the Sample App requires the WMI SDK to be installed.

    Open up the .VBP Project file and select Run -> Start or press F5
	
    For more information about how to manipulate the System Tray from
    VB you can refer to the Microsoft Knowledge Base Article: Q176085.
    This article can be found at http://www.microsoft.com/support/ in
    the Support Online section.
    