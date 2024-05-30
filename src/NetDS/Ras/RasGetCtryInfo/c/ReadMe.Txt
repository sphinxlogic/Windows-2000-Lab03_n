RasGetCtryInfo

RasGetCtryInfo is a console application that enumerates all the country names and their 
respective country codes and country IDs which are listed in the systems telephony book.

FILES
=====

The RasGetCtryInfo application uses the following files

File                Description

README.TXT          Readme file for RasGetCtryInfo application
RASGETCTRYINFO.C    C source code
MAKEFILE            Nmake file for Windows NT or Windows 9x


RAS API's USED
==============

RASGETCOUNTRYINFO


-------------------------------------------
BUILDING THE APPLICATION FOR
MICROSOFT WINDOWS NT OR WINDOWS 9x:
-------------------------------------------

To build the application on either Windows NT or Windows 9x you will
need to have the rasapi32.dll installed in the system folder. 

Build the application:

  nmake cleanall
  nmake

The above commands build the executable program RasGetCtryInfo.exe
for Microsoft Windows NT or Windows 9x.


----------------------------------------------------
RUNNING THE APPLICATION ON WINDOWS NT AND WINDOWS 9x
----------------------------------------------------

To run the application type:

	RasGetCtryInfo > [filename]

For Windows 95(pre OSR2) you need to install DUN 1.2x upgrade.