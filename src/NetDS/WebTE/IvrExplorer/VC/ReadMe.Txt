======================================================
Notes for IvrExplorer
======================================================
IvrExplorer is an MFC based application, intended to demonstrate
the use of WebTE hook interfaces.
How to build:
1. The sample is supplied with a VC++5.0 project files.
2. On the Tools menu, select Options. 
3. On the Directories tab, select "Include files" from the "Show 
   directories for" list box. Delete all the directories listed (if 
   any). Then, add the following directories:
   * full path to the Windows 2000 SDK\inc directory (for example, 
     d:\nt\public\sdk\inc)
   * full path to the Windows 2000 SDK\inc\crt directory (for example, 
     d:\nt\public\sdk\inc\crt)
   * the path to the MFC\INCLUDE of your VC++5.0 installation
   * the path in which you installed WebTE SDK\INC.
4. On the Directories tab, select "Include files" from the "Show 
   directories for" list box. Delete all the directories listed (if 
   any). Then, add the following directories: 
   * full path to the MFC\LIB of your VC++5.0 installation
   * full path to the Windows 2000 SDK\LIB\I386 directory. 
   * the path in which you installed WebTE SDK\LIB\I386

How to use:
1. Stop the MSWTESRV service if it is running, by typing the following 
   at the command line:
         net stop mswtesrv
2. Run IvrExplorer.EXE.
3. In IvrExplorer, select Connect from the File menu to start the 
   service in hooks mode.
4. Select New Application from the File menu to add a window to an 
   application. 
   Note: You must use a name of an already defined application, that 
   has a device assigned to it. This will make WebTE listen on this 
   device.
5. Call the device. The flow of events will be displayed in the 
   IvrExplorer's application window.
Note: You can connect to multiple applications simultaneously.