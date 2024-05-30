           Microsoft Platform Software Development Kit (SDK)
                Windows 2000 RC2 Release Edition
                             Readme.Txt

=========
Contents
=========

1. General Release Notes and Known Issues
2. Tested Compilers and New Linker
3. Header File Conventions
4. RPC/MIDL Release Notes
5. COM+ (Component Services) Developer Release Notes
6. Windows Management Instrumentation (WMI) Release Notes
7. Windows Debuggers and Visual C++ 6.0 Support
8. Windows Debuggers
9. Platform SDK Content Overview
10. Other Known Issues
11. Providing Feedback on the Platform SDK
12. Building Visual Basic DirectX Samples
13. Sample Compile Errors
14. Updates to the Platform SDK
15. Technologies not Supported in the Platform SDK
16. Future Microsoft Support of the Alpha Processor

========================================================
1.0  General Release Notes and Known Issues
========================================================

The contents of the Platform SDK change as Windows 2000 evolves. 
To get the latest released version of the Platform SDK, subscribe 
to the Microsoft Developer Network (MSDN), or visit our Web site at
http://msdn.microsoft.com/developer/sdk/. An MSDN Professional 
subscription is the best way to receive current Microsoft operating
system beta versions, releases, and the Platform SDK.

The Platform SDK includes support for Windows(R) 2000, Windows NT(R) 4.0, 
Windows 98, and BackOffice(R), and limited support for Win64(TM) development.

1.1 Setup
---------

The setup program for the Platform SDK is the Microsoft Windows 
Installer. 
If you have feedback on the SDK setup program, please 
send it to sdkfdbk@microsoft.com. The SDK team will use this feedback to 
improve future versions. You can use the installer tools included in the 
SDK to examine the SDK setup program's use of the installer. 

The Platform SDK for RC2 setup program is not supported on Windows 95.  

Many advanced installer features do not work in this release of the SDK . These 
include advertising, administrator installs, network installs, and 
install-on-demand.

1.1.1 Uninstalling or Installing Over Previous Versions 
-------------------------------------------------------
We recommend that you either remove any previous installations 
of the Platform SDK or install this release into a new, separate 
directory. 

To remove an old Platform SDK installation, use the Windows 
Control Panel Add/Remove Programs utility.

If Add/Remove Programs does not remove your old Windows Installer-based 
installation (the Platform SDK for Windows 2000 Beta 3 or later), run the 
following command from the Platform SDK CD: 

  <CD>:\Setup\SDKZap.bat

This tool is only available on the CD.  It will remove all Windows Installer 
information about any Platform SDK installation, as well as the InProgress key 
for all applications.  In general, this should not be a problem.  
You still must manually remove the installed Platform SDK image from your hard
drive.  Your environment variables may also need to be edited.  

1.1.2 New Visual C++ IDE Directory Settings
-------------------------------------------
The Microsoft Visual C++ (R) Integrated Development Environment (IDE) 
does not use the environment variable settings. During setup, 
you will have the option to update your Visual C++ 5.0 or 6.0 
directory settings to match those in the Platform SDK build 
environment. 

Choosing this option places the Platform SDK library, executable 
directories, and include directories at the beginning of the list of 
directories searched by Visual C++ when building programs in the IDE.
This creates a consistent build environment both on the command line 
and in the IDE. 

Note: This is a global change and will affect all programs built in 
the IDE. If you have customized your IDE directory settings to search 
custom library directories or include directories before searching 
Visual C++ directories, you may want to verify the changes to ensure 
that you maintain correct behavior in your other IDE-based programming
projects. See your Microsoft Visual C++ documentation for instructions
on how to check and modify the IDE search paths.

1.2 Environment Variables
-------------------------
To set the Platform SDK path, run SetEnv.bat from your Platform SDK 
installation directory. The SDK path must appear before your
compiler path.

If you are using Visual C++ as your compiler, run VCVars32.bat before 
running SetEnv.bat from the Platform SDK directory.

Usage:   SetEnv MSSDK
Where:   MSSDK specifies where the Platform SDK was installed.

Example: SetEnv C:\MSSDK sets the environment relative to C:\MSSDK.


1.3 Documentation Setup
-----------------------
The Platform SDK documentation is provided in HTML Help format.
If you are running Windows NT or Windows 2000, the update program for 
HTML Help may fail during setup unless you have Administrator 
privileges. 

If you encounter an error such as the following:

    Cannot open the file d:\%MSSDK%\help\psdk.col

be sure that you have Internet Explorer 3.02 or later installed, then
run the HTML Help update program, HHUpd.exe, from the Platform
SDK CD-ROM. 

HHUpd.exe is located in your <MSSDK>\Setup directory after 
installation. You can run it from the command line or from Explorer 
to verify that your version of HTML Help is up to date.

1.3.2 InfoViewer Integration
----------------------------
The Platform SDK documentation is no longer integrated with the
Visual Studio (R) 97 documentation. If you previously installed
the Platform SDK and deleted the %MSSDK%\Help directory, Visual
Studio help may encounter an error indicating that it cannot find
the Platform SDK documentation files. This occurs because the
registry settings are pointing the InfoViewer to files that no
longer exist.

If this occurs, uninstall your version of the Microsoft Developer Network Library 
and reinstall it.

To verify that InfoViewer is looking for the correct files, 
check whether the following registry keys point to valid file 
locations:

    Key: HKLM\SOFTWARE\Microsoft\Infoviewer\5.0\Titles\<BASENAME>\Content
    Should point to: <HelpFileCDPath><BASENAME>.ivt

    Key: HKLM\SOFTWARE\Microsoft\Infoviewer\5.0\Titles\<BASENAME>\Index
    Should point to: <HelpFileLocalPath><BASENAME>.ivi
    Where: <BASENAME> is in the following list of Platform SDK InfoViewer
files and <HelpFileCDPath> is the full path to the MSDN CD-ROM 
directory containing the .ivt file. 

        pdintro
        pdapp
        pdmsg
        pdgrmm
        pdinet
        pdnds
        pdobj
        pdsms
        pdui
        pdwbase
        pdref

    Where: <HelpFileLocalPath> is the full path to the MSDN installed 
	directory containing the .ivi file. If you have MSDN installed you can 
	verify the paths by looking at a different Title\<BASENAME> key.


1.4 Removal of Native Structured Storage 
(NSS)
-----------------------------------------------------------------
The Native Structured Storage (NSS) Implementation within COM 
Structured Storage has been removed from Windows 2000. All NSS files have 
been converted to .doc files.

1.5 Known Issues
----------------
- New linker format (see "2.0 Tested Compilers and New Linker,"
  following).

- Building all of the samples requires more than 2 GB of disk space.

- Building assembler files.

  A few of the samples build some components out of .asm files. If you
  do not have a program equivalent to ML.exe, the Microsoft Assembler
  product, MASM, can be purchased.  No assembler is provided with the
  Platform SDK. If you are an MSDN Universal subscriber, MASM is
  included in your Office Test Platform CD-ROMs.

- The following samples require ATL 2.0:

    Mssdk\Samples\Internet\Components\TDC
    Mssdk\Samples\WinBase\Scard\Aggreg
ATL2.0 can be downloaded from the Microsoft Web site at 
  http://msdn.microsoft.com/visualc/downloads/atl/default.asp.

- The following sample requires ATL 2.1, which can be installed with 
  Visual C 5.0:

    Mssdk\Samples\NetDS\Tapi\Tapi3\Cpp\SampleMSP

- If Microsoft Visual C++ is installed from the administrator 
  account, the Platform SDK \lib and \include directories are added 
  at the bottom of the IDE search paths. If you encounter errors 
  when compiling the Platform SDK samples from the IDE, you may need 
  to move these directories to the top. 

  See your Microsoft Visual C++ documentation for instructions on 
  how to check and modify the IDE search paths.

- The Internet\IE\Components\spruuids sample can be built properly 
  from the IDE, but not from the command line.

- The DbMsg\Exchange\LibSrc\acl can be built properly from the IDE,
 but not from the command line.

===================================
2.0 Tested Compilers and New Linker
===================================

The Platform SDK has been tested with Visual C++ version 6.0 Service 
Pack 3. Some samples may not build without applying Visual Studio Service Pack 3. 
See http://msdn.microsoft.com/vstudio/ for more information.
Most samples can be built with other compilers, but other compilers 
were not completely tested. The Active Template Library (ATL) requires 
updates to work with the current headers. These updates can be found 
in the %mssdk%\Include\ATL30 directory. The files in this subdirectory 
must replace the ones shipped with Visual C++ 6.0.

If you are using Visual C++ 5.0, you must use the linker supplied in 
this version of the Platform SDK (\Bin\Link\link.exe).

Some samples require that you install the Unicode MFC libraries. You can
select them during a custom Visual C++ installation. If you do not install these 
libraries, building samples that need them generates an error similar to the 
following:

    LINK : fatal error LNK1104: cannot open file "mfc42ud.lib"

2.1  New Import Library Format
------------------------------
The import libraries included with this release of the Platform SDK
have a new format that reduces their size and allows for faster link
times. If you cannot use the linker that comes with the Platform SDK,
or if you do not have Visual C++ 6.0, the supplied libraries must be
converted to the old format by using the linker supplied with this
Platform SDK. Create a new directory to contain the old format import
libraries. For each import library, use the command: 

    link /lib /convert /out:.\{oldformat}\{library}.lib {library}.lib

where {oldformat} is the directory that will contain the converted 
library and {library} is the import library to be converted. 
Visual C++ 5.0 users can replace the linker supplied with Visual C++ 
with the one in this version of the Platform SDK.

Visual C++ 5.0 users who have trouble debugging binaries should 
delete or rename the following files in MSSDK\BIN:

  Link.exe
  CvPack.exe
  CvtRes.exe

2.2  Common Sources of Warnings
-------------------------------
- MakeProcInstance: Do not use this function. Pass 
  DLGPROC directly (the first parameter to MakeProcInstance).
  Also, be sure to delete the FreeProcInstance function
  that is paired with MakeProcInstance.

- Explicit casts are now necessary in many situations 
  in which intrinsic casts worked before. An example:
  MSSDK\samples\dbmsg\sql\dblib\c\sqltestn\SqltestN.c(186).
  The (DLGPROC) cast was not necessary before. A warning
  is now generated if a cast is omitted.

- CODE and DATA statements are not supported for use in 
  makefiles.

===========================
3.0 Header File Conventions
===========================

While this version of the Platform SDK can be used to target 
applications for Windows 95, Windows NT 4.0, and Windows 98 using 
the following header file conventions, it is primarily intended for 
Windows 2000 preliminary development and testing.

The following table indicates the macros you must define to target 
each system using the SDK headers.

Target platform                    Value to set
---------------                    ------------

  Microsoft Windows 95             WINVER=0x0400
  and Windows NT 4.0

  Microsoft Windows 98             _WIN32_WINDOWS=0x0410 and
  and Windows NT 4.0               WINVER=0x0400

  Windows NT 4.0                   _WIN32_WINNT=0x0400 and
                                   WINVER=0x0400

  Windows 98 and Windows 2000      WINVER=0x0500

  Windows 2000                     _WIN32_WINNT=0x0500 and
                                   WINVER=0x0500

  Internet Explorer 3.0            _WIN32_IE=0x0300
  (and later)

  Internet Explorer 4.0            _WIN32_IE=0x0400
  (and later)

  Internet Explorer 5.0            _WIN32_IE=0x0500
  (and later)

Note that setting WINVER to 0x0500 implies _WIN32_IE=0x0500.

The SDK headers use guard statements to determine the system on which 
each element is supported. The following table describes these 
statements.

Guard statement                 Implemented in
------------------------        ---------------

 #if _WIN32_WINNT >= 0x0400     Windows NT 4.0 and later. 
                                It is not implemented in
                                Windows 95.

 #if _WIN32_WINDOWS >= 0x0410   Windows 98. The image
                                may not run on Windows 95. 

 #if _WIN32_WINNT >= 0x0500     Windows 2000. The image
                                may not run on Windows 95/98 or
                                Windows NT.

 #if WINVER >= 0x0410           Windows 98.

 #if WINVER >= 0x0500           Windows 2000 and Windows 98.

 #if _WIN32_IE >= 0x0300        Internet Explorer 3.0 
                                and later.

 #if _WIN32_IE >= 0x0400        Internet Explorer 4.0 
                                and later.

 #if _WIN32_IE >= 0x0500        Internet Explorer 5 
                                and later.

The value of _WIN32_WINNT is set in Win32.mak, depending on the
platform you choose to target. By default, Win32.mak sets the
TARGETOS to WINNT and the APPVER to 4.0. As a result, by default, 
_WIN32_WINNT is now defined as 0x0400.  

By default, Win32.mak sets _WIN32_IE to 0x0400 if it is not
already defined. To specifically target Internet Explorer 5, 
set _WIN32_IE to 0x0500.

If you are building an application to run on Windows 95 and you want 
compile-time notification of compatibility issues, set TARGETOS=BOTH 
in your makefile. When TARGETOS is defined as BOTH, _WIN32_WINNT is 
not defined for the precompiler, and the only information parsed at 
compile time is applicable to both Windows 95 and Windows NT.

If you do not include Win32.mak in your makefile, you must
explicitly define _WIN32_WINNT as 0x0500 to use the 
Windows 2000-specific material from the header files.

CryptoAPI is one of several API sets present in Windows 95
OEM Service Release 2 (OSR2) that are still guarded by
(_WIN32_WINNT >= 0x0400). If you are writing an application
specifically for OSR2 and you want the header files to provide
compile-time access to these functions, it is necessary to define
_WIN32_WINNT as 0x0400. Notice that an application that uses these
technologies does not run correctly on the retail release of
Windows 95. Most applications that are expected to run on unmodified
Windows 95 should be built without defining _WIN32_WINNT.

Previous releases of the Platform SDK included
the following definitions in Win32.mak to map structured exception
handling keywords to their proper underscored names:

    try -> __try 
    except -> __except 
    finally -> __finally 
    leave -> __leave

This caused problems for developers who chose to use C++ 
structured exception handling in which "try" is supposed to
be "try" rather than "__try". For this reason, by default, 
the mapping has been removed from Win32.mak. This may
cause compile-time errors for your applications. To get 
the old behavior, add the following to your makefile before including Win32.mak: 

    SEHMAP = TRUE 



==========================
4.0 RPC/MIDL Release Notes
==========================

The following items are new for this release. 

4.0.1 Asynchronous Remote Procedure Call
The Remote Procedure Call (RPC) run-time environment now supports 
asynchronous remote procedure calls to allow your programs to handle 
multiple outstanding calls from a single-threaded client. This 
prevents data transmission bottlenecks that can arise from slow or 
delayed clients or servers. With asynchronous pipe parameters, 
client/server applications can transfer large amounts of data 
incrementally, without blocking the client or server threads from 
performing other tasks. For more information, see the "Asynchronous 
RPC" section in the Platform SDK documentation.

4.0.2 New HTTP Protocol Sequence
The ncacn_http protocol allows client and server applications to 
communicate across the Internet by using the Microsoft Internet 
Information Server (IIS) as a proxy. Because calls are tunneled 
through an established HTTP port, they can cross most firewalls. 

4.0.3 Name Service
The RPC Name Service (Locator) uses Windows 2000 Active Directory 
as its database. This means that exported entries can be made 
persistent even when a server is rebooted. For more information, 
see the RPC reference pages for RpcNsBindingExport,
RpcNsBindingImportNext, RpcNsBindingLookupBegin, and
RpcNsBindingUnexport in the Platform SDK documentation.

4.0.4 New Type Library Attributes
Microsoft Interface Definition Language (MIDL) supports double-byte 
character set (DBCS) international locales. Type Library (TLB) file 
generation has been significantly improved and all the type library 
attributes are supported. For more information, see "Type Library 
Attributes" in the Platform SDK documentation.

4.1 Using New and Updated SDK Headers
-------------------------------------
Headers that were compiled with the new MIDL compiler (including most
MIDL-generated headers in the Platform SDK) require the new SDK
headers to work. This is intentional. As long as the SDK remains
in the include path ahead of the compiler, everything should work.

=====================================================
5.0 COM+ (Component Services) Developer Release Notes
=====================================================

5.1 COM+ Application Export
---------------------------
A COM+ application export can fail with the following message:

    Error occurred writing to the application file.

This can occur if the same type library is registered with two 
different paths under the HKEY_CLASSES_ROOT\TypeLib key and the 
HKEY_CLASSES_ROOT\CLSID\{<clsid>}\TypeLib key. An example of this is 
short file name versus long file name or different capitalization in 
the paths. This should not affect components generated by Visual Basic. 
The workaround for Windows 2000 RC2 is to either change the component's
self-registration code to write the same path to both the type library 
and the class registration key, or to manually modify one of the 
registry keys using Regedit.exe before exporting the application. The 
problem will be fixed in the final release of Windows 2000.

5.2 COM+ Application Proxies
----------------------------
The CLSIDFromProgID for COM+ application proxies is case sensitive. COM+ 
application proxies do not appear in the registry (HKEY_CLASSES_ROOT). 
All class information is stored in the COM+ Registration Database. For 
Windows 2000 RC2, progID lookups in the Registration Database are case
sensitive. This limitation will be removed in the final release of 
Windows 2000.

5.3 Administrative Interfaces
-----------------------------
The following items will be changed for the final release.

5.3.1 COM Administrative Interfaces
The signature or format of the query string for 
ICOMAdmin::GetCollectionByQuery is likely to change in the final release 
of Windows 2000.

5.3.2 MTS 2.0-Style Administrative Interfaces
COM+ offers MTS 2.0-style administrative interfaces (MTSAdmin class) 
that enable existing applications targeting MTS 2.0 to continue to 
run without changes on Windows 2000 and allow new applications to target 
both MTS 2.0 and Windows 2000. However, note that these interfaces are 
not entirely compatible due to changes in the underlying functionality. 
Refer to the Platform SDK for a detailed listing of all compatibility 
breaks.

In particular, ApplicationInstallPath is available in Windows 2000 RC2
for read/write through the COM administrative interfaces, but it does not 
have any effect. In the final release of Windows 2000, this property will 
be removed. The Replication Share property will also be removed in the final 
release.

5.4 Bring Your Own Transaction
------------------------------
When using Bring Your Own Transaction (BYOT), you must not begin the 
transaction inside a COM+ configured component. Should you do so, 
deadlocks are likely to occur.

5.5 Role Names And IMDB Data Sources
------------------------------------
In Windows 2000 RC2, using a semicolon (ASCII 0x3b) in role names and 
IMDB data sources is not supported. Attempting to do this can cause 
unexpected system behavior.

5.6 Queued Components (QC)
--------------------------
QC interfaces can be marshaled only through typelibs. Marshaling by 
a proxystub DLL is not supported.

5.6.1 Cluster Failover Support
COM+ Queued Components does not yet support failover in a cluster 
environment. This feature will be available in the next release.

5.6.2 Getting Started
The best way to get a feel for Queued Components is to go through the 
step-by-step instructions in the Queued Components SDK samples. QCSamp1 
and QCSamp2 are Visual C++ samples, QCSamp3 is a Visual Basic sample.

5.7 Autoeverything
------------------
5.7.1 Development
Although unmodified MTS packages are completely supported, for new COM+ 
applications, please link to Uuid.lib and #include "Comsvcs.h." This 
supersedes all other headers and libraries that were shipped with MTS.

5.7.2 JIT
Just-in-Time (JIT) Activation is no longer optional when components are 
transacted. You can disable JIT only when the component is marked 
"Transaction Ignored" or "Transaction Not Supported."

5.7.3 CoGetObjectContext
Instead of calling GetObjectContext, new applications should use the new 
CoGetObjectContext function to get the object context. This function is 
described as follows:

    HRESULT CoGetObjectContext(REFIID iid, void **ppInterface);

    iid - Desired interface for returned object context
    ppInterface - Address to receive the interface pointer of the 
                  desired interface for the returned object context

IObjectContext::CreateInstance is no longer mandatory

Any of the standard activation functions, such as CoCreateInstance, 
will correctly propagate context to the newly created object.

5.7.4 AutoComplete/AutoAbort
Methods that have this attribute will automatically complete or abort
the current transaction when the method returns, depending on the 
HRESULT. In other words, COM+ examines the HRESULT on return and does
the equivalent of calling SetComplete if the HRESULT is S_OK, or 
SetAbort otherwise.

5.7.5 Synchronization
In a component with synchronization, avoid calling out of 
IObjectControl::Deactivate. Deadlock may occur, as in the following 
example:

  Component A, B, and C are hosted in their own COM+ Applications 
  (implying they are hosted by their own processes) and reside in the 
  same synchronization domain, avoid application designs where component 
  A can call into Component C directly and indirectly through Component 
  B. The following situation might occur: 

  - A calls B, which calls C.
  - B dies.
  - A's call to B returns (with failure).
  - A proceeds to call into C directly.

The COM+ Services Runtime detects the second call into C as having the 
same logical thread ID as the first call and therefore allows the 
reentrance, but nevertheless this creates a situation where there may 
actually be two physical threads of execution running inside C.

5.8 In-Memory Database
----------------------
The following issues are associated with In-Memory Database (IMDB):

- When using IMDB to access SQL Server tables containing binary large 
objects (BLOBs), such as SQL Server ntext, text, and image data types, 
use the Microsoft OLE DB Provider for SQL Server (SQLOLEDB). The 
Microsoft OLE DB Provider for ODBC (MSDASQL) is not supported.

- IMDB support for ITableDefinitionWithConstraints::AddConstraint is 
limited to the creation of a primary key for tables in the IMDB cache.

- DBPROP_MAXORSINFILTER is defined to be 0 (if view filters are not 
supported by a provider), 1 (if a provider does not support multiple OR 
conditions), or a VT_14 value indicating the maximum number of disjoint 
conditions that can be supported in a view filter. In the case of the 
IMDB provider, there is no set maximum value for this property. To help 
indicate this, IMDB currently returns the maximum possible value for the 
VT_14 data type through DBPROP_MAXORSINFILTER. In the future, this value 
can change as the OLE DB specification evolves to provide a method for 
OLE DB providers to indicate that they have no set maximum value 
associated with DBPROP_MAXORSINFILTER.

- Using IMDB, the ADO method .MovePrevious is currently unable to 
re-position the record pointer to the row immediately preceding a row 
that has just been deleted.

- Oracle Synonyms are not currently supported by IMDB.

- IMDB provider does not currently support the OLE DB interface 
IRowsetCurrentIndex. Because of this, it is also not possible for the 
IMDB provider to support the Seek method for ADO recordsets.

5.9 Windows Clustering
----------------------
5.9.1 How to Set Up COM+ and DTC to Run on a Windows 2000 Cluster
COM+ and DTC are now components of Windows 2000 Server editions. To set 
up COM+ and DTC to run on a Windows 2000 Advanced Server or Data Center 
Server, you must run the COM+ Cluster Wizard on your newly created 
Windows 2000 Advanced or Data Center Cluster. This Wizard will upgrade 
your standalone COM+ and DTC installations to run on the new Cluster. 

The COM+ Cluster Wizard does the following:

For DTC:
- Creates a DTC resource
- Moves the log file to a shared disk drive
- Marks the registry keys for replication
 
For Component Load Balancing Service (CLBS):
- Creates a component load balancing resource
- Sets up the router node for failover
- Marks the registry key for replication

The following three items are all part of COM+ (Component Services); 
however, they cannot be clustered:

- Queued Components on Windows 2000 cluster is not supported in RC2 
  but will be supported for RTM.
- COM+ Events on Windows 2000 Cluster is not supported in RC2.
- COM+ In-Memory Database (IMDB) on Windows 2000 cluster will NOT be 
  supported in RC2 or RTM. A future version of IMDB will be supported 
  after Windows 2000 RTM. A white paper detailing how to run IMDB in a 
  cluster environment will be released at RTM.

To run the new COM+ Cluster Wizard (COMclust.exe), make sure both nodes 
of the cluster are running and enter the following in the command prompt 
window: 

  ComClus.exe

The COMClus.exe is a wizard located in the 
System32 directory. If your CD-ROM is not the D drive, enter the 
appropriate drive letter.

5.9.2 Registrar Component Threading Model 
When using the registrar component, you may get errors when using the 
IComponentRegistrar::Attach method. In the error log, these errors will 
manifest themselves as an "Access Denied" error from the Attach method. 
This error occurs because the registry entry for CLSID_ReadTypeLib has 
been set to "Apartment" by default. To fix this error, you must change 
the value of CLSID_ReadTypeLib to "Both." The GUID for this entry is 
{E94836C5-E4D6-11CF-B938-00A0C9034817}.

5.10 Documentation
------------------
5.10.1 COM+ Software Development Kit
COM+ samples help you understand how to use COM+ features. We provide projects 
compilable in Visual Basic, Visual C++, and Visual J++ that demonstrate the 
implementation of services such as queued components and events.

Compile the samples to see how the application runs. Then you can drill 
down into the code by stepping through the server components and client 
implementations. You can either use these applications as a learning 
tool, or modify them to use in your applications.

Here is a list of the COM+ samples, each preceded by their directory 
location: 

- Administration -- Applications demonstrating how to use and automate 
  COM+ administration.
- Application_Samples -- Enterprise-level COM+ user applications useful 
  as a "best practice" model.
- Fundamentals -- Tutorial samples for basic COM programming and other 
  COM feature samples.
- Installation_Verification -- COM+ application to verify correct 
  installation of COM+.
- Performance -- Toolkit beta for tuning MTS, COM+, or IIS application 
  performance.
- Services -- Applications demonstrating COM+ services.
- Tools -- COM+ pack containing a COM+ wizard and a COM+ add-in.
  
5.10.2 Obtaining Complete Documentation on COM+ Features
For complete documentation and reference material on implementing a COM+ 
feature, see the COM+ documentation located in the Platform 
SDK documentation.

The COM+ SDK can be installed as part of the MSDN Platform SDK. For 
additional last-minute changes, please take a look at the readme in the 
[MSSDK]\samples\com directory.

5.11 Bring Your Own Transaction (BYOT)
--------------------------------------
COM+ BYOT will not work unless the COM+ BYOT object is first configured 
as a COM+ configured component. To do this, you must import the BYOT object 
into a COM+ application. The ProgId of the BYOT component is 
"Byot.ByotServerEx". The following sample script can be pasted into a 
.vbs (VB Script) file to accomplish this automatically:

'
'  cfgbyotex.vbs
'
'  This VB script file imports the COM+ BYOT gateway object into
'  a COM+ application. This step must be performed or else the 
'  COM+ BYOT feature will not work. Note that this script is 
'  just one representative way of doing this; you are free to copy
'  and change the script to suit your own individual needs (for 
'  instance, if you wanted to change the security settings, etc.).
'
'

Dim I
Dim cat
Dim apps
Dim app
Dim comps
Dim comp
Dim strByotAppName
Dim strByotProgId

strByotAppName = "BYOT Host Server"
strByotProgId = "Byot.ByotServerEx"

set cat=CreateObject("COMAdmin.COMAdminCatalog")
Set apps = cat.GetCollection("Applications")
WScript.Echo "Deleting the " & strByotAppName & " app if it exists..."
DeleteApp apps, strByotAppName
WScript.Echo "Recreating & configuring the application...."
set app = apps.Add
app.Value("Name") = strByotAppName
app.Value("3GigSupportEnabled") = 0
app.Value("AccessChecksLevel") = 0
app.Value("Activation") = 1
app.Value("ApplicationAccessChecksEnabled") = 0
app.Value("Authentication") = 0
app.Value("AuthenticationCapability") = 64
app.Value("CRMEnabled") = 0
app.Value("Changeable") = -1
app.Value("Deleteable") = -1
app.Value("Description") = "Application for hosting the COM+ BYOT gateway object"
app.Value("EventsEnabled") = 0
app.Value("Identity") = "Interactive User"
app.Value("Password") = ""
app.Value("ImpersonationLevel") = 4
app.Value("QueuingEnabled") = 0
app.Value("QueueListenerEnabled") = 0
app.Value("RunForever") = 0
app.Value("ShutdownAfter") = 1
apps.SaveChanges
apps.Populate

WScript.Echo "Importing the byotex component..."
cat.ImportComponent strByotAppName, strByotProgId

WScript.Echo "Configuring the byotex component..."
Set comps = apps.GetCollection("Components", app.Key)
comps.Populate
Set comp = comps.Item(0)
comp.Value("Transaction") = 1
comp.Value("Synchronization") = 4
comp.Value("JustInTimeActivation") = False
comp.Value("ObjectPoolingEnabled") = False
comp.Value("EventTrackingEnabled") = False
comp.Value("ComponentAccessChecksEnabled") = False
comps.SaveChanges
WScript.Echo ""
WScript.Echo "All done!"
WScript.Echo ""
WScript.Quit 0

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Private Sub DeleteApp(apps, strAppName)
  Dim I
  Dim lNumApps
  Dim app
  apps.Populate
  lNumApps = apps.Count
  For I = 0 to lNumApps - 1
    Set app = apps.Item(I)
    If app.Value("Name") = strAppName Then
      WScript.Echo "Deleting application <" & strAppName & "> now..."
      apps.Remove(I)
      apps.SaveChanges
      Exit For
    End If
  Next
End Sub

5.12 COM+ Component Load Balancing 
----------------------------------
COM+ Component Load Balancing (CLB) has been removed from 
Windows 2000 Advanced Server and DataCenter. A CLB Technology Preview, 
which allows customers to continue to develop and deploy 
applications using CLB functionality, is available now from Microsoft.   
Please send email to: clb@microsoft.com for more information.

==========================================================
6.0 Windows Management Instrumentation (WMI) Release Notes
==========================================================

To register the Event Viewer tools to receive WMI events, 
you must do the following:

- Set "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\WBEM\Application Directory" 
  to the Platform SDK\bin\wmi\ directory.

- Set "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\WBEM\SDK Directory" to the 
  Platform SDK\bin\wmi\ directory.

- Set "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\WBEM\SDK Build" to the 
  SDK build number.

In the Platform SDK\bin\wmi\ directory, run the following:

  %SystemRoot%\System32\WBEM\MOFCOMP Eviewer.mof

=====================================================
7.0 Windows Debuggers and Visual C++ 6.0 Support
=====================================================

The debuggers in the Platform SDK (WinDbg, i386KD, AlphaKD, NTSD, and
CDB) have been updated to support the new PDB symbol format used by
Visual C++ 6.0, part of the Microsoft Visual Studio(R) suite. This 
SDK was tested primarily with Visual C++ 5.0 because Visual C++ 6.0 
was not yet generally available. Visual C++ 6.0 coverage was 
not as complete as with Visual C++ 5.0. For example, Visual C++ 6.0 
is more stringent about warnings and errors in code; not all of the 
samples have been modified to compile cleanly under Visual C++ 6.0. 
For more information, see the Visual C++ 6.0 release notes and 
<http://msdn.microsoft.com/visualc/>.

=====================
8.0 Windows Debuggers
=====================

For more information on WinDBG, the KD debuggers included in the 
Platform SDK, and debugging, please see Debuggers.txt in 
the directory where the debugger is installed (\Bin). For more information, 
see <http://www.microsoft.com/hwdev/driver/ntdebugging.htm>.


=================================
9.0 Platform SDK Content Overview
=================================

The Platform SDK is the successor to the Win32 and 
BackOffice SDKs. It is intended to support development 
for Microsoft's Distributed Network Architecture--the infrastructure 
provided by Microsoft for the "digital nervous system."

Many of the technology components of this infrastructure were once
shipped in separate SDKs and did not always work well together.
The Platform SDK integrates these components and tests the build 
environment as a whole, provides a unified set of documentation, and 
provides "one-stop shopping" for samples, headers, and so on.

The following is a partial list of SDKs that are now integrated into
the Platform SDK:

  ActiveX SDK
  BackOffice SDK
  COM+ Services SDK
  Data Access SDK
  DirectX SDK
  Internet Client SDK
  MAPI SDK
  ODBC SDK
  OLEDB SDK
  SDK for Java
  Win32 SDK

Following is a brief description of the contents of the Platform SDK:

BIN       SDK tools, DLLs, and self-extracting .exe files
HELP      SDK documentation files use HTML Help
INCLUDE   Headers, IDL files, and global Platform SDK makefiles--
          Win32.mak and BkOffice.mak--used from most SDK command-line
          makefiles
LIB       Libraries
REDIST    Redistributables
SAMPLES   Platform SDK samples (see following)

This readme file refers to the tools, the INCLUDE files, and the LIB
files collectively as the "build environment." 

======================
10.0 Other Known Issues
======================

10.1 Revised DsAddSidHistory API documentation
----------------------------------------------
The DsAddSidHistory API has changed significantly since this release of 
the Platform SDK documentation was completed. An updated version of the
DsAddSidHistory documentation can be found in 
<MSSDK>\Help\DsAddSidHistory_Revised.doc.

10.2 MapDebugInformation deprecated; use SymGetModuleInfo instead
------------------------------------------------------------------
The MapDebugInformation function is obsolete for Windows 2000. 
Instead, use the SymGetModuleInfo function. Note that DbgHelp.Dll is a 
redistributable file, so this change affects all applications that install 
the Windows 2000 version of DbgHelp.Dll. 

MapDebugInformation does not work with PDB-style symbols. The existing 
SymGetModuleInfo provides all the necessary functionality, so a new 
MapDebugInformationEx function was not created.

The UnmapDebugInformation function and the IMAGE_DEBUG_INFORMATION structure 
are also obsolete. They have been replaced by the SymGetModuleInfo, 
SymLoadModule, SymUnloadModule functions and the IMAGEHLP_MODULE structure. 

ImageHlp.dll has been split into two parts: 
ImageHlp.dll and DbgHelp.dll (and the related .h and .lib files, included 
with the Platform SDK). For applications using symbol-handling and other 
debugging-related functionality, use DbgHelp instead of ImageHlp. In 
Windows 2000, the system-installed version of both of these DLLs are protected 
from being updated by Windows File Protection, and ImageHlp cannot be 
redistributed. Applications that need to ship an updated version of DbgHelp 
with their product can install an updated local copy of DbgHelp to the install 
directory. This also reduces an extra system reboot. This updated DbgHelp can 
also be used on Windows NT 4.0.

10.3 NTDSBCLI Conflicts with EDBBCLI
-----------------------------------
In this release of the Platform SDK, the NTDSBCLI functions conflict
with some of the EDBBCLI functions. This conflict will be resolved 
in a future release.

10.4 COM and SSL Support
-----------------------
The Platform SDK documentation refers to using the SSL security
protocol with COM. This feature is not supported in Windows 2000
RC2.

10.5 Visual Basic Command-Line Makefiles
---------------------------------------
Some of the Visual Basic samples have command-line makefiles. To 
build these samples from the command line, you must include Vb5.exe 
or Vb6.exe in your path.

10.6 ATL Header Problem
-----------------------
AtlBase.h has a problem with InlineIsEqualGuid.
The workaround is to define _SYS_GUID_OPERATORS_ before including any headers. 

10.7 Platform SDK HTMLHelp Collection Not Installed on Terminal Servers
-----------------------------------------------------------------------
The Platform SDK HTMLHelp documentation collection file (platsdk.col) will not 
be installed on Terminal Servers.  The workaround is to reinstall the SDK 
documentation after using cmd: change user/install -- then after you've 
installed, use cmd: change user/execute.

===========================================
11.0 Providing Feedback on the Platform SDK
===========================================
We are sincerely interested in your feedback on the Platform SDK. 
Please mail suggestions or bug reports for the Platform SDK
to SdkFdBk@Microsoft.com. This is not a support alias, but your
feedback helps us plan future changes for the Platform SDK and
will make the SDK more useful to you. 

===========================================
12.0 Building Visual Basic DirectX Samples
===========================================
To build the DirectX Visual Basic samples, you may need to register one 
or more controls located in the MSSdk\Bin\i386\VBSupport directory on 
the Platform SDK CD. These files will not be installed or registered 
during setup.

===========================================
13. Sample Compile Errors
===========================================
The following samples are known to have problems compiling in this 
release. These samples will be updated in a future Platform SDK release.

  DbMsg\Exchange\LibSrc\rule
  DbMsg\SQL\ODS\XP_ODBC

The samples in \samples\com\services\Queued_Components include some
hard coded paths in their makefiles. By updating the paths, the samples
can be compiled.

===========================================
14. Updates to the Platform SDK
===========================================
Please note that this is a preliminary version of the SDK for Windows 2000. 
Microsoft will be making periodic updates and fixes to the content of the kit. 
Please visit http://msdn.microsoft.com/developer/sdk/platform.asp to download 
the latest Platform SDK material.

===================================================
15. Technologies not Supported in the Platform SDK
===================================================
Broadcast Architecture and Microsoft Data Access Objects (DAO) material are no 
longer supported by the Platform SDK. Contact Microsoft Developer Support if 
you have questions about Broadcast Architecture or Microsoft Data Access 
Objects. Send comments or feedback to sdkfdbk@microsoft.com. 

Routing for Windows NT 4.0 (also known as RRAS or Steelhead) support 
has been removed from the Platform SDK. A replacement for Windows 2000 
routing will be available at a future date.

===================================================
16. Future Microsoft Support of the Alpha Processor
===================================================
For more information about the changes to Microsoft's support of the 
Compaq Alpha processor, see 
http://www.microsoft.com/ntserver/nts/news/msnw/compaq.asp.


