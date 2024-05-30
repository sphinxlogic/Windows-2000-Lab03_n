REM *************************
REM   Erase Binaries
REM *************************
del *.class
del jt3rec.exe


REM *************************
REM   Generate .class files
REM *************************
jvc   /x- /cp %windir%\java\classes\classes.zip;%windir%\java\trustlib *.java


REM ***************************************
REM   Create a .exe from the .class files
REM ***************************************
jexegen /w /main:jt3rec /out:jt3rec.exe *.class


REM ***************************************************
REM   Create a .cab from the .class files and sign it
REM   currently disabled
REM ***************************************************
cabarc n jt3rec.cab *.class
REM makecert -sk testkey -n "CN=Test" testcert.cer
REM cert2spc testcert.cer testcert.spc
REM signcode -j javasign.dll -jp low -spc testcert.spc -k testkey JT3Rec.cab
REM del testcert.cer
REM del testcert.spc
