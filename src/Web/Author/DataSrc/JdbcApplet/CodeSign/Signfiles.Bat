Set outputfilename=output.bat
Set inputfilename=list.txt

if exist %outputfilename% del %outputfilename%

IF "%UseBBN%"=="TRUE" goto BbnYes
:BbnNo

    REM -----
    REM set test parms
    REM -----
    set signspc=\"test.spc\"
    set signpvk=\"TestKey\"

    if exist %signspc% 	del %signspc%

    REM -----
    REM create and use test credentials
    REM -----
    makecert -u:TestKey -n:CN=TestCompany -D:12 test.cer    
    Cert2Spc test.cer test.spc

    REM -----
    REM create output.bat with the signcode statements
    REM -----
    exptext %inputfilename% %outputfilename% "signcode -spc %signspc% -pvk %signpvk% -prog" -name -info

    REM -----
    REM Turn ON the switch to ensure WinVerifyTrust can verify test roots
    REM -----
    regedit wvtston.reg

    Goto BbnEnd

:BbnYes

    REM -----
    REM set real parms
    REM -----
    set signspc=\"nehemiah.spc\"
    set signpvk=\"Nehemiah\"
    set signprov=\"BBN SafeKeyper Crypto Provider V0.1\"
    set signprovtype=\"2\"

    exptext %inputfilename% %outputfilename% "signcode -md5 -spc %signspc% -pvk %signpvk% -provider %signprov% -providertype %signprovtype% -commercial -prog" -name -info

:BbnEnd

pause "hit any key to continue..."

REM -----
REM Output.bat contains the signcode statements
REM -----
call output.bat

pause "hit any key to continue..."

REM -----
REM run chktrust to ensure batch file worked
REM leeg: note that this change assumes list.txt is properly filled in and formatted.
REM -----
awk -f check.awk < list.txt > check.bat
call check.bat
