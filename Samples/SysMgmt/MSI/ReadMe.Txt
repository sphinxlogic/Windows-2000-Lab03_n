Windows Installer 1.0 SDK Release  -  Microsoft Corporation, April 16, 1999

---------------------------------------------------------------------------
This release includes the following components, in the indicated folders:

    ReadMe.txt 		- this file, contents and notes
    License.rtf		- SDK license agreement
    Redist.txt 		- redistibution terms and conditions

Redist - components that may be redistributed with your application
    WINNT\InstMsi.exe 	- Windows Installer self-installer for use with Windows NT4 only
    WIN9x\InstMsi.exe 	- Windows Installer self-installer for use with Windows 95 and Windows 98

Help
    Msi.chm+Msi.chi		- Documentation for Windows Installer, HTML help format (see note below)
    MsiTool.hlp+MsiTool.cnt 	- Tool help, describing tools in the Tools folder
    Language.txt 		- Language support in Windows Installer

Include
    Msi.h		- install management API functions
    MsiQuery.h 		- database and custom action API functions
    MsiDefs.h  		- property names and database data bit flags
    MergeMod.h 		- definitions for use with MergeMod.dll COM object
    PatchApi.h 		- definitions for use with MsPatchC.lib and MsPatchC.dll
    PatchWiz.h 		- definitions for use with the installer patch package creation tool

Lib
    Msi.lib	     	- import lib for MSI API functions
    MsPatchC.lib	- import lib for patch generation engine MsPatchC.dll
    PatchWiz.lib 	- import lib for patch package creation tool PatchWiz.dll

Tools
    Instlr1.adm	   	- used with the Group Policy Editor. See the "System Policy" help topic.
    Instlr11.adm   	- used with the Group Policy Editor. See the "System Policy" help topic.
    Orca.msi     	- graphical table editor supporting validation and merge modules
    MsiVal2.msi  	- command-line installer package validation tool, provides darice.cub and logo.cub files
    MsiDb.exe    	- database import, export, merge, transform
    MsiInfo.exe  	- summary information property manager, string pool validation
    MsiMerg.exe  	- merges two databases
    MsiTran.exe  	- generates and applies database transforms
    MsiZap.exe   	- used to remove selected MSI management data from a machine. Use with caution.
    MsiTool.mak		- shared makefile for tools and custom actions
    MergeMod.dll	- COM object providing support for installer merge modules

Patching
    MakeCab.exe	  	- general compressed file cabinet generation tool, not installer-specific
    MPatch.exe   	- test application to create a patch file using MsPatchC.dll
    APatch.exe   	- test application to apply a patch using MsPatchA.dll (part of InstMsi package)
    MsPatchC.dll	- patch file creation engine, used by PatchWiz.dll and MPatch.exe
    PatchWiz.dll 	- installer patch package creation tool
    ReadMe.doc   	- documentation for use of PatchWiz.dll
    Template.pcp	- schema for patch wizard project settings
    Example.pcp  	- sample project settings for patch wizard
    Source	 	- folder containing source files to build PatchWiz.dll

SampProd - sample product installation package - MSI viewer tool
    ReadMe.txt		- notes describing installation and usage
    MsiSpy.msi		- installation database for all platforms
    MsiSpy 		- folder containing source files, to be installed only via MsiSpy.msi

Database
    Schema.msi   	- database containing all standard tables, but no installation data
    Schema.msm   	- merge module containing all standard module tables, but no installation data
    UISample.msi	- sample database demonstrating a UI implementation         
    Error.mst    	- transform to provide debug error messages during development
    Intl         	- localized Error and ActionText tables in multiple languages
    
Samples - examples demonstrating the use of the Windows Installer APIs
    CustAct1.cpp 	- sample DLL custom action for testing
    CustExe1.cpp 	- sample EXE custom action for testing
    MsiMerg.cpp  	- sample database merge tool
    MsiTran.cpp  	- sample transform creation and application tool
    InitMsi.cpp  	- sample module from msispy
    Scripts 		- folder containing doc and scripts to perform a variety of installer-related tasks

---------------------------------------------------------------------------
Windows Installer core files installed by installation package InstMsi.exe:
    Msi.dll		- installation engine, use by install clients and install service
    MsiExec.exe		- command-line invocation of install functions, and service control functions
    MsiHnd.dll		- UI process, loaded only when full UI is authored and used for installation

Other files that are updated as needed by installation package InstMsi.exe:
    riched20.dll, usp10.dll, msls31.dll	- rich-edit and complex script support
    cabinet.dll  			- extraction of files from compressed file cabinets
    imagehlp.dll 			- used for import table binding
    mspatcha.dll 			- used to apply file-level patches
    shfolder.dll 			- special shell folder location and creation

---------------------------------------------------------------------------
Notes: 

If HTML help is already installed on your system, msi.chm can be invoked via file association
HTML help can be installed from: http://msdn.microsoft.com/workshop/author/htmlhelp/localize.asp

The .msi packages in the SDK may be installed by activating them in the Windows Explorer,
or by using "MsiExec.exe -i path_to_package". Use "MsiExec.exe -?" to see more options.
The object model is exposed as the ProdId: WindowsInstaller.Installer

UISample.msi provides a sample UI sequence, but that sequence will not function
properly until the database has been populated with valid installation data.
For help in populating a database with valid installation data, see the help topic
titled "An Installation Example" under "Windows Installer Examples". For an
example of a completed installation package that uses the same UI sequence as
UISample.msi, install one of the msi packages under the Tools or SampProd folders.

---------------------------------------------------------------------------
Compiling sample code:

There are two options for compiling the sample code in the Samples subfolder:
use nmake or use a project in the MSDev environment.

To use nmake, make certain that the MSVCDIR environment variable is set. You can
generally run the VCVARS32.BAT to set this. VCVARS32.BAT is located in the BIN
subdirectory of your VC install. The command line to compile the CUSTACT1.CPP
sample file (given default install locations for both Microsoft Visual C++ 6
and the Windows Installer SDK) would look like this:
C:\MsiIntel.SDK\Samples> nmake -f custact1.cpp include="%include%;c:\MsiIntel.SDK\Include" lib="%lib%;c:\MsiIntel.SDK\Lib"
Note: the quotes are included because the default install locations for Visual
C++ include spaces in path names. If the INCLUDE and LIB environment variables
on the machine do not have spaces in the path, then the quotes are unnecessary.

To use the MSDev environment, create a new Win32 EXE or Win32 DLL project, and
add the appropriate file as a source. MSI.LIB will need to added to the library
list in the Project Settings dialog. MsiIntel.SDK\Include and MsiIntel.SDK\Lib
directories will need to be added to the Directories tab under Tools\Options.

---------------------------------------------------------------------------
Known issues:

Msi.chm is not yet properly integrated w/ the typelib in msi.dll - context sensitive 
help is not available in VB w/ this release.

Tools that create customization transforms require special considerations that are
not yet documented in msi.chm.  A KB article on this topic will be published
shortly after this SDK is released - go to http://support.microsoft.com/support/search/c.asp
and enter "Q225522" in the "My Question Is" box.

Additional support articles and solutions will be placed on 
http://support.microsoft.com/support/search/c.asp as they become available.