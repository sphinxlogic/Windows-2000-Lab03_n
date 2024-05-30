****************************************************************
                 MICROSOFT SQL SERVER
              DB-LIBRARY FOR C SAMPLE PROGRAMS
****************************************************************
This file describes the DB-Library for C sample programs included
with Microsoft(R) SQL Server(TM).

For additional information about SQL Server Sphinx, DB-Library
for C, and ODBC, see SQL Server Books Online, which contains the
most up-to-date information available.

****************************************************************
DB-LIBRARY FOR C SAMPLE APPLICATIONS

The DB-Library for C sample program files are stored as projects
in their own directories. The following DB-Library sample projects 
are targeted to specific client operating systems: Microsoft(R) 
Windows NT(R) and Microsoft Windows(R) 95/98 for Intel(R), and Alpha
AXP(R) platforms; Each of these samples has an associated make 
file for building with the NMAKE utility.

****************************************************************
DB-LIBRARY FOR C SAMPLE 32-BIT APPLICATIONS

Project directories are located in the following path:

     C:\MSSQL7\DEVTOOLS\SAMPLES\DBLIB\C

     SQLTESTC    Windows NT-based console sample 
     SQLTESTN    Windows NT-based GUI sample
     TEXTCOPY    Windows NT-based console text and image sample, 
		 also uses GETOPT.*
     SQLCURS     Using cursor functions
     SQLEXAMP    Command-line interpreter
     EXAMPLE8    Using remote stored procedures and return 
		 parameters

Each project on the Intel platform includes Visual C++ 4.0 
workspace files (.MDP). Double-click the workspace file to load 
the workspace and make file into the Developer Studio environment.

Each project also contains cross-platform native Visual C++ 4.0 make 
files (.MAK). For each 32-bit project the .MAK file contains Intel
and Alpha build information. When the project is loaded into
Developer Studio, pick the appropriate target, for example
"Example8 - Win32 (ALPHA) Debug", and build it.

To use these samples with Visual C++, you need to ensure that 
your Library and Include directory settings point to your own 
directories. To do this using Developer Studio, from the Tools menu, 
choose Options, then click the Directories tab. From the "Show 
directories for" box, choose Include files and Library files, and 
ensure that these directories (as appropriate) are included:

Include files: C:\MSSQL7\DEVTOOLS\INCLUDE
Library files: C:\MSSQL7\DEVTOOLS\LIB



