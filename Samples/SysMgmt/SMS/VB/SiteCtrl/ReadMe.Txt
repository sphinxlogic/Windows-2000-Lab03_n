****************************************************************
  Copyright (c)1999 Microsoft Corporation, All Rights Reserved
****************************************************************

1. What SiteCtrl Does & How

    The SiteCtrl sample connects to an SMS Provider namespace and
    retrieves the current Inter-Poll Delay Time from an instance of
    SMS_SCI_Component where the ItemName property equals
    "SMS_SITE_COMPONENT_MANAGER|<site name>".  The sample allows 
    the user to change the Inter-Poll delay and commits the
    change back to the Site Control File.  

    This sample demonstrates how to handle the Site Control File, and
    how to changes the values of embedded properties

2. Running the Sample

    Open up the SiteCtrl.vbp file in Visual Basic and run the program.
    Press connect and fill in the information fields on the connection
    box.  After connecting, a dialog box with the current inter-poll
    Delay time (in seconds) will pop-up.  To change the inter-poll delay
    time, Type in a new number (in seconds) for the time and press Commit

3. Requirements

    Requires: Visual Basic 6.0 or greater to compile and run
    Runs on: NT 4.0+
    Windows Management Instrumentation (WMI) must be installed.

4. Compiling the Sample

    Note: Compiling the Sample App requires the WMI SDK to be installed.

    Open up the .VBP Project file and select Run -> Start or press F5
	

    