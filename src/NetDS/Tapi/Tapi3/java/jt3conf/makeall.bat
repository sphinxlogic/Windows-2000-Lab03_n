REM ************************
REM   Erase Binaries
REM *************************
del *.class
del jt3conf.exe


REM *************************
REM   Generate .class files
REM *************************


jvc /x- /cp %windir%\java\classes\classes.zip;%windir%\java\trustlib *.java

REM ***************************************
REM   Create a .exe from the .class files
REM ***************************************
jexegen /w /main:jt3conf /out:jt3conf.exe *.class


REM ***************************************************
REM   Create a .cab from the .class files and sign it
REM   currently disabled
REM ***************************************************
REM cabarc n jt3cab.cab jt3conf.class
cabarc n jt3conf.cab *.class
makecert -sk testkey -n "CN=Test" testcert.cer
cert2spc testcert.cer testcert.spc
REM signcode -j javasign.dll -jp -p Microsoft Base Cryptographic Provider v1.0 -y RSA FULL low -spc testcert.spc -a sha1 -k testkey jt3conf.cab
REM del testcert.cer
REM del testcert.spc
