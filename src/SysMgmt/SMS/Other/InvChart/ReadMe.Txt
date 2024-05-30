****************************************************************
  Copyright (c)1999 Microsoft Corporation, All Rights Reserved
****************************************************************

1. What InvChart Does & How

    InvChart is a Microsoft Excel application that contains a VBA macro that connects
    to and uses the SMS Provider.  This macro will put up a login dialog and ask for
    user and SMS site information.  It will then use that information to connect to the
    SMS Provider for a particular SMS Site.  At this point it will query the 
    SMS Provider and build a list of all the OS's that are in use at that site.
    When it has a list of all the OS's it will then query the SMS Provider again
    to determine how many machines of each OS exist within the Site.
    Along the way it will put this data onto the Excel worksheet allowing
    a chart object to display the data.
    
2. Running the Sample

    Open up the InvChart.xls file in Microsoft Excel.  Choose Yes, if you are 
    prompted to run any macros.  Click the Populate OS Info button and fill 
    in the fields on the Connection box.

3. Requirements

    Requires Microsoft Excel 97 or newer
    Runs on: NT 4.0+
    Windows Management Instrumentation (WMI) must be installed.


    