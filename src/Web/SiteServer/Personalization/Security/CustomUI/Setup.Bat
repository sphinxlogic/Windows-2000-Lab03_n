@echo off
rem (C) Copyright 1996-1997 Microsoft Corporation.  

if exist %WINDIR%\system32 set SYSDIR=%WINDIR%\system32&& goto startcp
    set SYSDIR=%WINDIR%\system

:startcp
if not exist %SYSDIR%\samplerc.dll goto copycustom
if not exist %SYSDIR%\samplerc.org  goto renam2
del %SYSDIR%\samplerc.org
:renam2
rename  %SYSDIR%\samplerc.dll  samplerc.org
echo.
echo *** IMPORTANT: You must restart your machine after setup is complete
echo.
:copycustom
copy samplerc.dll %SYSDIR%
regedit config.reg

:done
echo Finished Setting Up Custom UI Resource DLL
echo.

