****************************************************************
  Copyright (c)1999 Microsoft Corporation, All Rights Reserved
****************************************************************

1. What AssetWiz Does & How

    The Asset Information Wizard demonstrates how to extend SMS Client 
    Inventory via the SMS SDK.

    AssetWiz is designed to be run on SMS Clients, as such, it cannot be
    assumed that the WMI core components are installed on the target
    computer.  If a VB application is early bound to a component, the 
    application will be unable to execute if that component is not available.
    Because of these limitations, AssetWiz uses late binding to access all 
    WMI objects.  Late binding allows AssetWiz to programmatically detect
    if the WMI core components are not installed, and act accordingly.

    AssetWiz first opens a connection to the root\cimv2 namespace on the
    local machine.  If the SMS_AssetWizard_1 class exists,
    the properties are read and stored in their respective controls on
    the Wizard Pages.  If SMS_AssetWizard_1 does not exist,
    it is automatically created.

    If it was necessary to create the SMS_AssetWizard_1 class, 
    AssetWiz then checks for the existence of the root\cimv2\sms 
    namespace, creates it if necessary, and connects to it.  In the
    root\cimv2\sms namespace, another SMS_AssetWizard_1 
    class is created.  Special qualifiers are added to the class
    and each property:

    Qualifier     Scope               Type       Purpose    
    ------------- ------------------- ---------- ---------------------------
    SMS_Report    class and property  boolean    Should this class/property 
                                                 propagate to the server?

    SMS_Class_ID  class only          string     Assigns an inventory class-
                                                 name to this object.  ex:
                                                 MICROSOFT|CDROM|1.0

    SMS_Group_ID  class only          string     Assigns a display name to
                                                 this class.
    
    When the user clicks the "Finish" button in the Asset Wizard, the information
    on the Wizard Pages is collected and stored in a new instance of 
    SMS_AssetWizard_1.  If the instance already exists, the information is
    updated.  The SMS server will collect the information on the next inventory cycle.

    AssetWiz has been designed to be extensible.  Support code has been added
    to allow the user to add, modify, and remove existing wizard pages and
    controls with minimal modification to the source code.

    To add a new wizard page to the asset wizard, you must first add a new frame control
    to the fraWizardPages control array.  Be sure to position and size the new frame to
    match the existing frames.  Next, add and position new controls in the new frame to
    suit your needs.  Code to store and retrieve information from WMI is located in the
    Form_Load and FinishProcedure procedures.  Form_Load must be modified to create and
    load any new properties you have created.  FinishProcedure must be modified to store
    your new information.

    To add your new information to the summary on the final wizard page, modify the
    GenerateSummary function.  If you need to validate information entered by the user
    before he or she proceeds, implement a new validation section in the ValidatePage
    function.

    Note:  If you add, delete, or modify any properties in the SMS_AssetWizard_1
    class, you should use a new class name to store the information.  Much like COM
    classes, changing WMI classes after they have been deployed should be considered
    a poor practice.

2. Running the Sample

    Open assetwiz.vbp in Microsoft Visual Basic 6.0 and select Run / Start, or
    press F5.

3. Requirements

    Requires: Visual Basic 6.0 or greater.
    Runs on: NT 4.0+ and Windows 9x
    Windows Management Instrumentation (WMI) must be installed to compile.
	

    