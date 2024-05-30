
@REM   If the regsvr32 fails, make sure MSVBVM50.DLL (installed
@REM   by Visual Basic 5.0) is on your system path. The sample
@REM   will not run without Visual Basic 5.0. 
start /w regsvr32 SimpleObject.dll
jview /cp:p . run

