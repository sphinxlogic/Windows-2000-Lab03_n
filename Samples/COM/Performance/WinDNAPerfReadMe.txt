Kit Version 1.0.24.0 August 31, 1999
------------------------

The Windows Distributed InterNet Architecture Performance Kit 
can be installed by running WinDNAPerf.exe. This setup program will
prompt for a target directory (default C:\WinDNAPerf), and ask whether
you want to install binaries, source, or both.
 
The documentation for this kit is installed in %WinDNAPerf%\Doc, 
and is named WinDNAPerf.chm. This is an HTML Help Format document
stored in a compressed file format.

The index file has a .chi extension. To open the HTML Help file,
double-click the .chm icon. 

To view these files you need: 

Microsoft Internet Explorer 3.02 (or later).
The latest edition of Microsoft Internet Explorer can be downloaded
from

http://www.microsoft.com/windows/ie. 

HTML Help Workshop.
These files are installed on most systems that have Microsoft products
already installed. If you don't have HTML Help, it can be downloaded
for free from 

http://msdn.microsoft.com/workshop/author/htmlhelp/default.asp

If you have difficulty running the setup program, have any other
problems, or have feedback on the kit, please send mail to
winptool@microsoft.com.

Native SQL Server Provider Components don't work on NT4/MTS
-----------------------------------------------------------
The following 3 components will not work on NT4/MTS.
DCBankATLADO_Lux.dll
DCBankATLOLEDBASP_Lux.dll
DCBankATLOLEDB_Lux.dll
These can be rebuilt using the Windows 2000 RC2 Platform SDK or later.

Another workaround is to wrap the following line in
\Program Files\Platform SDK\Include\comsvcs.h with an #ifdef

#define GetObjectContext(ppIOC) (CoGetObjectContext(IID_IObjectContext, (void **) (ppIOC)) == S_OK ? S_OK : CONTEXT_E_NOCONTEXT)

with 

#if _WIN32_WINNT >= 0x0500)
#define GetObjectContext(ppIOC) (CoGetObjectContext(IID_IObjectContext, (void **) (ppIOC)) == S_OK ? S_OK : CONTEXT_E_NOCONTEXT)
#else
extern HRESULT __cdecl GetObjectContext (IObjectContext** ppInstanceContext);
#endif

and link the component with MTX.LIB.
 

SETTING UP THE IBank ASP EXPERIMENTS  
------------------------------------
The following .asp files have been added to the source portion of
the kit in source\scripts\

ado.asp
adoatl.asp
adoatl_tx.asp
adoDirect.asp
adoDirect_tx.asp
ado_tx.asp
odbc.asp
odbcpool.asp
odbcpool_tx.asp
odbc_tx.asp
oledb_lux.asp

These files specify the database scale of 10 (10 is the default that
is setup when the scripts are used) in a line like:

Bank.DoDebitCreditTx1SP(0, 10, Session.sessionID, ErrorString)
or
DoDebitCreditTx1SP 0, 10, ErrorString

If you are using a different scale you will need to change the database
scale to be a different scale e.g. 1600 then change these lines to:

Bank.DoDebitCreditTx1SP(0, 1600, Session.sessionID, ErrorString)
or
DoDebitCreditTx1SP 0, 1600, ErrorString


To setup the IIS server create a directory under
...\inetpub\wwwroot\ called IBankAsp and copy the above .asp files
 to the new directory.  For Windows 2000 look under Administrative
Tools and find the Internet Service Manager.  For NT4 it is under
Windows NT 4.0 Option Pack, Microsoft Internet Information Server,
Internet Service Manager.  Add to the default website a new virtual
directory called IBankASP.  Use the wizard to connect this to the
IBankASP directory under wwwroot created above.  Also in the wizard
allow read and run scripts such as .asp from this new virtual
directory and enable directory browsing.

Modify the default website properties from the Internet Service
Manager on the Performance tab to allow more than 100,000 hits
per day.

The Populate.vbs script in source\scripts will load the COM
configurations and scenarios. Select the defaults for the Driver
Node Name and the Applications Node Name and the configuration will
be setup for a single node running IIS, SQL and the harness software.
In addition it loads a set of Web configurations and scenarios for
the above set of .asp files.

For example scenario 300 is for /ibankasp/odbc.asp.

Create a file called webini.ini in the WinDNAPerf directory with the
following contents - replacing "MyNode" with the name of the computer
that is being used for this experiment.

-----------------------------------------------
[WinDNALoadController]
Scenario=300
Scale=10
Tier=1
ConfigDataBase="perfbank"
ConfigServer="MyNode"
ConfigUserID="perfuser"
ConfigPassword=""
Token=1
-----------------------------------------------

Then from the WinDNAPerf directory run the following command:
c:\WinDNAPerf>bin\WinDNALoadController -fwebini.ini


ADDITIONS TO PERFCOL
--------------------
PerfColMgr:
This version allows the inclusion of instance indices in the
browse counter dialog (in order to distinguish instances of the
same name). The inclusion is optional on an *.ini per *.ini basis:

1) Run PerfColMgr
2) Open *.ini
3) Default is no indices. If you want indices do
   Counter|Include Instance Index (or simply Ctrl+N). 
4) Open the browse dialog as before (+ button, Ctrl+A, etc.)

If the instance index option is enabled you will see a check
mark in front. It operates like a toggle (Ctrl+N, etc. goes
back to no indices.)

PerfCol:
No changes.


 