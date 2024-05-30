****************************************************************
  Copyright (c)1999 Microsoft Corporation, All Rights Reserved
****************************************************************

1. What CollTree Does & How

    The CollTree sample allows Collection hierarchies to be edited by
    a very simple Drag and Drop system.  CollTree first connects to a provider
    via the information collected when the Connect button is clicked.
    CollTree then creates, modifies, and deletes instances of 
    SMS_CollectToSubCollect when collections are dragged and dropped above and 
    below other collections. 

2. Running the Sample

    Open up the CollTree.vbp file in Visual Basic and run the program.
    Press connect and fill in the information fields on the connection
    box.  After the collections box has populated, the collections can
    be dragged and dropped over each other to form links between them, thus 
    editing the collections hierarchy.

3. Requirements

    Requires: Visual Basic 6.0 or greater to compile and run
    Runs on: NT 4.0+ 
    Windows Management Instrumentation (WMI / WBEM) must be installed.

4. Compiling the Sample

    Note: Compiling the Sample App requires the WMI SDK to be installed.

    Open up the .VBP Project file and select Run -> Start or press F5
	

    