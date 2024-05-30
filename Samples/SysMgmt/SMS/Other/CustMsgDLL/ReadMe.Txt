// **********************************************************************
//  Copyright (c)1999 Microsoft Corporation, All Rights Reserved
// **********************************************************************

 -=* Using & Creating Message DLLs with the SMS SDK *=-

** Section 1: What are Message DLLs **

Message DLLs contain unicode specific strings that are used to generate
Status Messages in the SMS Provider.  The DLLs define status messages
and their properties, such as the Severity, Language, and MessageID.
SMS has 3 default Message DLLs listed by their ModuleName: 'SMS Provider', 
'SMS Site', and 'SMS Client'.  

When SMS needs to raise an event message, such as when a task has completed,
or an error condition was encountered, it raises a status message.  These status 
messages can be accessed via the SMS Provider as instances of SMS_StatusMessage.  Each 
message is unique by its ModuleName and its MessageID.  The ModuleName defines the 
DLL from which the message was retrieved, and the message id is used to index 
that actual message text.

For example, when a user creates a package, the SMS Provider raises a 
status message with the ID of 30000 in the 'SMS Provider' module.
30000 represents the Message for Creating a Package.


** Section 2: Using the 'SMS Provider' Message DLL **

Any application written with the SMS SDK has the option of raising its
own status messages.  Through the methods defined in the SMS_StatusMessage
class, an application can raise generic Error, Warning, and Informational status 
messages.  These methods are RaiseErrorStatusMsg, RaiseWarningStatusMsg, and
RaiseInformationalStatusMsg.  

The 3 generic status message methods use the IDs 39997, 39998, and 39999 which
are defined in the 'SMS Provider' Message DLL.  

An application could also use the 4th Status Message method "RaiseRawStatusMsg" 
to raise a status message with a different ID then the generic ones.
RaiseRawStatusMessage allows the application to use the text defined in the 
associated Message DLL instead of specifying the text.  This method also requires
Insertion Strings which are used to fill in 'fields' in the status message.
For instance, the Create Package status message (ID 30000), uses
2 Insertion Strings, the UserName and the PackageId.  Here is the format of the message string
"User <UserName> created the Package <PackageID>"


** Section 3: Creating Custom Message DLLS **

SMS also supports Custom Message DLLs that define Message Strings and their 
respective Message IDs.  If you wish to create your own Message DLL, there is
a series of steps you must follow in order to create and install the DLL

  Creating the Messages - How to create the messages

    In order to create custom Message Strings, edit the included
       Template file <custmsgs.mc>.  Instructions for creating your
       own messages can be found in the comments of the .mc file.

  Compiling & Linking - turning your .MC file into a Resource DLL
    
    Once you've created your .mc file, you must compile and link it
      into a Resource DLL

    Note: You will need a compiler than can Convert .MC files into
          .RC Resource files (preferably Microsoft Visual C++ 5.0 and up)
          Subsitute the following (CUSTMSG.EXT) file names with your Custom Message file names
          You will also need to add the \VC\bin and \SharedIDE\bin directories for VC++ to your path

    Step 1:  Compiling an MC file into an RC file
          At the command line, run the following:
	     MC CustMsgs.MC

    Step 2:  Compiling an RC file into an RES file
          At the command line, run the following:
             RC CustMsgs.RC

    Step 3:  Making a Resource DLL from the RES file
          At the command line, run the following:
             LINK CustMsgs.RES /dll /noentry /machine:I386 
          Note: If your DLL if for another machine, such as an Alpha, you
                may substitute the machine type for 'I386'

  Distributing the CustomMsg.DLL file to SMS 

    In order for every SMS Site in the heirarchy to process Custom Message DLL's
    EVERY site must have the CustMsg.DLL file in EVERY directory that the SRVMSGS.DLL 
    file resides.  The best way to distribute your custom DLL to EVERY directory is to
    perform a Find All Files on the SRVMSGS.DLL file, then copy your custom DLL to every
    directory that an instance of the SRVMSGS.DLL file was found

    After you've copied your DLL out to every Site, You must install the DLL into the
    SMS Site Control File.  The 'AddMsgDLL' Tool will handle this complicated task
    for you, just specify the connection settings, the DLL file name, the Module name,
    and the Component names.  Component names allow you to specify a set of components
    that use your custom message DLL.  The example in the <custmsgs.mc> template
    uses 'Unknown Component' and 'Custom Component' as its component names.  
    The Module name is described in the template <custmsgs.mc> file

	Note: You will need the Visual Basic 6.0 runtime files in order to use the AddMsgDLL Tool

  Reseting the sites to enforce the changes

    Reset each site in your hierarchy, starting from the central site and working down, 
    using SMS Setup (use Setup's "Modify Installation" option, but don't change anything.
    Setup will ask you if you want to "Reset" the site, say yes.)

** Section 4: Using the Custom Message DLL **

  The CustMsg sample program in the SMS SDK demostrates the use of the 
  SMS_StatusMessage::RaiseRawStatusMessage method.  Use this sample application
  to test raising a custom status message.  Be sure to use the -M: option and specify 
  your custom DLL's 'ModuleName'

  When using the RaiseRawStatusMessage method, you must specify a MessageID, but this
  MessageID is not exactly the same as the one in your .MC file.  
  After running MC.EXE on your MC file, you will have 2 new files, a .H file, and a .RC file
  The .H file contains the REAL MessageID that your custom messages will use.
  Open up the .H file, and scroll down to the actual message definitions
  Underneath every message will be a #define statement similar to the following:

  #define CUSTOM_MESSAGES_CUSTCOMP_INFO_MY_MESSAGE ((DWORD)0x40009C40L)
                                                           ^MessageID^
  The .H file will give a new MessageID based on the original MessageID and the
  Severity of the message.  The high word of the DWORD is the severity, and the low word 
  is the original MessageID.  When you call RaiseRawStatusMessage, or use the CustMsg sample
  program, use this new MessageID. 


