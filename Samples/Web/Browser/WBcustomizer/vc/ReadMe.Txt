------------------------------------------------------------------------------------------
(C) Copyright 1999 Microsoft Corporation.  All Rights Reserved

THIS CODE AND INFORMATION IS PROVIDED "AS-IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

--- THIS CODE IS NOT SUPPORTED BY MICROSOFT ---


WBCustomizer - sample that demonstrates how to implement the IDocHostUIHandler interface
KB Article ID: Q183235
------------------------------------------------------------------------------------------

WBCustomizer.dll is a sample COM object that demonstrates how to implement the IDocHostUIHandler interface for use in Visual Basic (VB) applications.  The IDocHostUIHandler interface allows those who are developing applications using the Internet Explorer 4.0x (IE4) WebBrowser control, to perform certain user interface functions such as turning off context menus and accelerator keys.

WBCustomizer allows VB developers who are using the IE4 WebBrowser control to perform the following:

1. Turn context menus on or off.
2. Turn all accelerator keys on or off.
3. Turn specific accelerator keys on or off.

PLEASE NOTE: THIS SAMPLE IS NOT SUPPORTED BY MICROSOFT.  YOU MAY CHANGE THE SOURCE CODE IF YOU REQUIRE ADDITIONAL FUNCTIONALITY.

Instructions for using the WBCustomizer object
----------------------------------------------
1. Register the WBCustomizer.dll on your system by using regsvr32.  

            regsvr32 WBCustomizer.dll

2. Create a new VB application.  (You may use a preexisting VB application 
   that is hosting the WebBrowser control.)

3. Include the component "Microsoft Internet Controls" in your 
   application.

4. Draw the WebBrowser control on your form.

5. Set a reference to "Microsoft WebBrowser Customizer Sample Object".

6. Dim a variable of type WBCustomizer.

            Dim CustomWB As WBCustomizer

7. In your Form_Load event, create a new instance of the WBCustomizer 
   object.
            Set CustomWB = New WBCustomizer

8. In order for WBCustomizer to be able to perform user 
   interface functions for the WebBrowser control, WBCustomizer needs a 
   reference to the WebBrowser control that is on your form.  You set this 
   reference using the WBCustomizer.WebBrowser property.  

            Set WBCustomizer.WebBrowser = WebBrowser1

   Please note that WBCustomizer includes get and put functions for the 
   WebBrowser method.  However, the get function is not currently 
   implemented.  You may implement this yourself if you need this 
   functionality.


9. Turn on/off context menus by setting the EnableContextMenus property.
   A value of True turns context menus are on.  False turns them off.

10. Turn on/off all accelerator keys by setting the EnableAllAccelerators
    property.  A value of True turns context menus are on.  False turns 
    them off.  Only those accelerators that require Ctrl, Shift, or Alt
    key combinations will be turned off.  Those that do not require one
    of these keys, such as tab, F1, etc, can be turned off directly as 
    described in step 11.

11. Turn on/off specific accelerator keys by using the EnableAccelerator 
    method.  This method takes the following parameters:

    nKeyCode - the key code constant that specifies an accelerator key.  
               (vbKeyTab, vbKeyN, vbKeyO, etc.)    

    nVirtExtKey - the virtual key code of an extended key, such as 
                  vbKeyControl, vbKeyAlt, or vbKeyShift.  This parameter is
			optional and has a default value of 0.

    bState - the state of the accelerator key.  True turns on the 
             accelerator key and False turns it off.

REFERENCES
==========

Please refer to "Reusing Browser Technology" in the Web Workshop for more information regarding IDocHostUIHandler.

Also, refer to Knowledge Base article number Q183235: WBCustomizer.dll Implements IDocHostUIHandler for VB

