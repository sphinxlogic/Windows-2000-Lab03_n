****************************************************************
           MICROSOFT SQL SERVER WORKSTATION SYSTEM 7.0
  MICROSOFT DISTRIBUTED TRANSACTION COORDINATOR SAMPLE PROGRAMS
****************************************************************
This file describes the Microsoft Distributed Transaction 
Coordinator (MS DTC) sample programs included with Microsoft(R) 
SQL Server(TM) 7.0.

For additional information about SQL Server 7.0, MS DTC, and ODBC,
see the "Performing Distributed Transactions" topic of SQL Server
Books Online. For more information on MS DTC see the Guide to
Microsoft Distributed Transaction Coordinator.

****************************************************************
MICROSOFT DISTRIBUTED TRANSACTION COORDINATOR SAMPLE APPLICATIONS

The following 32-bit C++ sample programs are located in the
C:\MSSQL\SAMPLES\MSDTC directories by default:

DBLIB
Sample C++ program using 32-bit Visual C++ and the DB-Library
interface to communicate with both MS DTC and SQL Server. Includes 
the following files:
    DBLIB.MAK
    DBLIB.CPP
    DBLIB.MDP

ODBC
Sample C++ program using 32-bit Visual C++ and the ODBC interface to 
communicate with both MS DTC and SQL Server. Includes the following 
files:
    ODBC.MAK
    ODBC.CPP
    ODBC.MDP

Each project on the Intel(R) platform includes Visual C++ 4.0 
workspace files (.MDP). Double-click the workspace file to load 
the workspace and make file into the Developer Studio environment.

Each project also contains cross-platform native Visual C++ 4.0 make 
files (.MAK). For each 32-bit project the .MAK file contains Intel, 
Alpha AXP(R), MIPS(R), and PowerPC(TM) build information. When the 
project is loaded into Developer Studio, pick the appropriate target, 
for example "Example1 - Win32 (ALPHA) Debug", and build it.



To use these samples with Visual C++ 4.2, you need to ensure that 
your Library and Include directory settings point to your own 
directories. To do this using Developer Studio, from the Tools menu, 
choose Options, then click the Directories tab. From the "Show 
directories for" box, choose Include files and Library files, and 
ensure that these directories (as appropriate) are included:

	Include files:			Library files:
	C:\MSSQL\DBLIB\INCLUDE		C:\MSSQL\DBLIB\LIB
	C:\MSSQL\MSDTC\INCLUDE		C:\MSSQL\MSDTC\LIB
	C:\MSSQL\ODBC\INCLUDE		C:\MSSQL\ODS\LIB
	C:\MSSQL\ODS\INCLUDE
	C:\MSSQL\SQLOLE\INCLUDE

The following Transact-SQL sample scripts are located in the
C:\MSSQL\SAMPLES\MSDTC directories by default:

DBLIB
Sample Transact-SQL scripts that demonstrate communicating with both 
MS DTC and SQL Server. Includes the following files:
    CHGADDR.SQL
    UPDADR.SQL



