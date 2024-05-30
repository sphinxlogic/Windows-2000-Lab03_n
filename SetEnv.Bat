@ECHO OFF
REM -------------------------------------------------------------------
REM File    : SetEnv.Bat
REM
REM Usage   : SetEnv.Bat
REM
REM Abstract: This batch file sets the appropriate environment
REM           variables for the Platform SDK build envionment with
REM           respect to OS and platform type.
REM
REM -------------------------------------------------------------------

:Chk_MSSdk
REM Set the common env. variables
Goto Set_Common

:Chk_SetEnv
REM Verify that we have %MSSdk%\SetEnv.Bat
IF NOT EXIST "%MSSdk%\SetEnv.Bat" Goto ErrorBadPath

:Chk_MsVCDir
If "x%MSVCDir%x" == "xx" Goto NotMsVcDirExists
Goto MsVcDirExists

:NotMsVcDirExists
REM MSVCDir does not exist, does MSDevDir Exist (looking for known VC6 issue)?
IF "x%MSDevDir%x"=="xx" Goto ErrorMSDevDir

REM MSDevDir Exists (VC6 setup did not create MSVCDir).
REM Can we derive MSVCDir from MSDevDir?
IF NOT EXIST "%MSDevDir%\..\..\vc98\." Goto ErrorMSDevDir
set MSVCDir=%MSDevDir%\..\..\vc98

:MsVcDirExists
IF "x%OS%x" == "xWindows_NTx" Goto ATL_WinNT
Goto ATL_Win9x

:Finish
Goto end


REM -------------------------------------------------------------------
REM Set common variables
:Set_Common
REM -------------------------------------------------------------------
Set MSSdk=C:\Platform SDK
Set Lib=%MSSdk%\Lib;%Lib%
Set Bkoffice=%MSSdk%\
Set Basemake=%MSSdk%\Include\BKOffice.Mak
Set DXSDKROOT=%MSSdk%
Set DXMEDIASDK=%MSSdk%
Set INETSDK=%MSSdk%
Set MSSdk=%MSSdk%
Set Mstools=%MSSdk%
Set LOG=NO

REM Set OS specific variables
IF "x%OS%x" == "xWindows_NTx" Goto Set_WinNT
Goto Set_Win9x


REM -------------------------------------------------------------------
REM Set Windows 9x specific variables
:Set_Win9x
REM -------------------------------------------------------------------
Echo Setting SDK environment relative to %MSSdk%. Targeting Windows 9x
Set Include=%MSSdk%\Include;%Include%
Set Path="%MSSdk%\Bin;%MSSdk%\Bin\win95;%path%"
Set CPU=i386
doskey > Nul
Goto Chk_SetEnv


REM -------------------------------------------------------------------
REM Set Windows NT specific variables
:Set_WinNT
REM -------------------------------------------------------------------
IF /i "%PROCESSOR_ARCHITECTURE%" == "ALPHA" (Set CPU=ALPHA) else (Set CPU=i386)
Echo.
Echo Setting SDK environment relative to %MSSdk%. Targeting Windows NT (%Cpu%)
Echo.

Set Include=%MSSdk%\Include;%Include%
Set Path=%MSSdk%\Bin;%MSSdk%\Bin\WinNT;%path%

REM Patch path to put Bin\WinNT\NT4 in path ahead of NT5 tools that don't run on NT4
For /F "delims=;" %%i IN ('Cmd /c Ver') DO (
    IF "%%i"=="Windows NT Version 4.0" (
        Set Path=%MSSdk%\Bin\WinNT\NT4;%Path%
        Goto Chk_SetEnv
        )
    )
Goto Chk_SetEnv


REM -------------------------------------------------------------------
REM This is a temporary solution to the VC 6.0 ATL problem
REM Determine if we are running VC 6.0 (or sp3), based on the linker version, %MSVCDir%\Bin\link.exe
:ATL_WinNT
REM -------------------------------------------------------------------
IF NOT EXIST "%MSVCDir%\Bin\link.exe" Goto Finish
IF NOT EXIST "%MSVCDir%\ATL\Include\atlbase.h" Goto Finish

IF "%PROCESSOR_ARCHITECTURE%" == "ALPHA" (
For /F "delims=;" %%i IN ('"%MSVCDir%\Bin\link.exe" /?') DO (
    IF "%%i"=="Microsoft (R) Incremental Linker Version 6.00.8178" (
        Echo Implemented temporary patch in Include path For VC 6.0 ATL problem.
        Set Include=%MSSdk%\Include\ATL30;%Include%
        Goto Finish
        )
    IF "%%i"=="Microsoft (R) Incremental Linker Version 6.00.8447" (
        Echo Implemented temporary patch in Include path For VC 6.0 ATL problem.
        Set Include=%MSSdk%\Include\ATL30;%Include%
        Goto Finish
        )
    )
) else (
For /F "delims=;" %%i IN ('"%MSVCDir%\Bin\link.exe" /?') DO (
    IF "%%i"=="Microsoft (R) Incremental Linker Version 6.00.8168" (
        Echo Implemented temporary patch in Include path For VC 6.0 ATL problem.
        Set Include=%MSSdk%\Include\ATL30;%Include%
        Goto Finish
        )
    IF "%%i"=="Microsoft (R) Incremental Linker Version 6.00.8447" (
        Echo Implemented temporary patch in Include path For VC 6.0 ATL problem.
        Set Include=%MSSdk%\Include\ATL30;%Include%
        Goto Finish
        )
    )
)
Goto Finish


REM -------------------------------------------------------------------
REM This is a temporary solution to the VC 6.0 ATL problem
REM Determine if we are running VC 6.0, based on the linker version, %MSVCDir%\Bin\link.exe
:ATL_Win9x
REM -------------------------------------------------------------------
IF NOT EXIST "%MSVCDir%\Bin\link.exe" Goto Finish
IF NOT EXIST "%MSVCDir%\ATL\Include\atlbase.h" Goto Finish
Echo.
Echo Implemented temporary patch in Include path For VC 6.0 ATL problem.
Echo Warning: It is assumed that VC 6.0 is installed. If it is not installed,
Echo          it may be necessary to remove the %MSSdk%\Include\ATL30
Echo          line from your Include env. variable.
Set Include=%MSSdk%\Include\ATL30;%Include%
Goto Finish


REM -------------------------------------------------------------------
:ErrorMSDevDir
REM -------------------------------------------------------------------
Echo.
Echo Warning: The environmental variables MSDevDir and MSVCDir
Echo  were not found to exist. Check your Lib, Include and PATH to
Echo  verify that the SDK Lib, Include, and Bin directories precede
Echo  the compiler directories in the environment.
Echo.
Echo Note: Microsoft Visual Studio provides VCVARS32.BAT to Set them.
Echo  You must run VCVARS32.BAT first and then run SETENV.BAT.
Echo.
Echo Current settings:
Echo Lib=%Lib%
Echo Include=%Include%
Echo PATH=%PATH%
Echo.
Goto Finish


REM -------------------------------------------------------------------
:ErrorBadPath
REM -------------------------------------------------------------------
Echo.
Echo Error: The file "%MSSdk%\setenv.bat" does not appear to exist, or
Echo        an existing MSSdk env. variable does not match the expected
Echo        value encoded in this batch file by Platform SDK Setup.
Echo        Please check the path and an existing MSSdk variable
Echo        for correctness.
Echo.
Goto Finish


REM -------------------------------------------------------------------
:end
REM -------------------------------------------------------------------