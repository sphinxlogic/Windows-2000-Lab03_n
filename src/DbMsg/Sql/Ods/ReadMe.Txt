****************************************************************
                    MICROSOFT SQL SERVER
              OPEN DATA SERVICES SAMPLE PROGRAMS
****************************************************************
This file describes the Open Data Services sample programs 
included with Microsoft(R) SQL Server(TM).

For additional information about SQL Server and Open Data
Services "Programming Open Data Services" of SQL Server Books 
Online, which contains the most up-to-date information
available.

****************************************************************
OPEN DATA SERVICES SAMPLE APPLICATIONS

The following 32-bit C sample programs are located in the
C:\MSSQL7\DEVTOOLS\SAMPLES\ODS directory by default:

Xp_hello
A simple application illustrating the major components of an
Open Data Services application. The application builds an
extended stored procedure that is installed and tested using
the Xp_hello.sql Transact-SQL script.
    Xp_hello.c
    Xp_hello.def
    Xp_hello.mak
    Xp_hello.mdp
    Xp_hello.sql
    Readme.txt

Xp_param
Sample extended stored procedure example illustrating parameter
information retrieval and use. The extended stored procedure is
installed and tested using the Xp_param.sql Transact-SQL script.
    Xp_param.c
    Xp_param.def
    Xp_param.mak
    Xp_param.mdp
    Xp_param.sql
    Readme.txt
 
Xp_dblib
Sample extended stored procedure using 32-bit Visual C++ and the 
DB-Library interface to open a new connection to the SQL Server 
that called the extended stored procedure. Returns a result set and 
passes the results to the client. Uses a bound session for the 
loopback connection.
    Xp_dblib.c
    Xp_dblib.def
    Xp_dblib.mak
    Xp_dblib.mdp
    Xp_dblib.sql

Xp_odbc
Sample extended stored procedure using 32-bit Visual C++ and the 
ODBC interface to open a new connection to the SQL Server that 
called the extended stored procedure. Returns a result set and 
passes the results to the client. Uses a bound session for the 
loopback connection. Note: To connect to the server using integrated 
security, the local server data source name (registered using ODBC 
in the Control Panel) must be used. Includes the following 
files:
    Xp_odbc.c
    Xp_odbc.def
    Xp_odbc.mak
    Xp_odbc.mdp
    Xp_odbc.sql

Each project on the Intel(R) platform includes Visual C++ 4.2 
workspace files (.mdp). Double-click the workspace file to load 
the workspace and make file into the Developer Studio environment.

Each project also contains cross-platform native Visual C++ 4.2 make 
files (.mak). For each 32-bit project the .mak file contains Intel 
and Alpha AXP(R) build information. When the project is loaded
into Developer Studio, pick the appropriate target, for example
"xp_hello - Win32 (ALPHA) Debug", and build it.

You can also build from the command line using nmake and the
.mak files provided.

To use these samples with Visual C++, you need to ensure that 
your Library and Include directory settings point to your own 
directories. To do this using Developer Studio, from the Tools menu, 
choose Options, then click the Directories tab. From the "Show 
directories for" box, choose Include files and Library files, and 
ensure that these directories (as appropriate) are included:

      Include files:                Library files:
	C:\MSSQL7\DEVTOOLS\INCLUDE 		C:\MSSQL7\DEVTOOLS\LIB


These samples require SQL Server 7.0 or later versions of srv.h and 
opends60.lib.

You might have older versions of srv.h and opends60.lib in you include 
and library paths. Ensure that \MSSQL7\DEVTOOLS\INCLUDE and 
\MSSQL7\DEVTOOLS\LIB directories are placed above other include 
and library paths when you build these samples.