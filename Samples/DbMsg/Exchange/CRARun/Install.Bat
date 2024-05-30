@if [%1] == [] goto Usage
 
@echo \registry\machine\software\Microsoft\Exchange\Client\Custom Actions > %TEMP%\reg.ini
@echo      Launch = REG_SZ "4.0;%1\crarun.dll;1;00000101001100" >> %TEMP%\reg.ini
@regini %TEMP%\reg.ini
@echo Custom Nothing Rule Installed!
@goto end

:Usage
@echo off
@echo Usage -	install [drive][path]
@echo		eg.  install c:\exchsdk\samples\exchange\crarun

:end
