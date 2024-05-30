REM *************************
REM   Erase Binaries
REM *************************
del *.class
del jt3call.exe


REM *************************
REM   Generate .class files
REM *************************


#jvc  /nomessage /x- /cp %windir%\java\classes\classes.zip;%windir%\java\trustlib *.java
jvc   /x- /cp %windir%\java\classes\classes.zip;%windir%\java\trustlib *.java
REM ***************************************
REM   Create a .exe from the .class files
REM ***************************************
jexegen /w /main:jt3call /out:jt3call.exe *.class


REM ***************************************************
REM   Create a .cab from the .class files and sign it
REM   currently disabled
REM ***************************************************
REM cabarc n jt3cab.cab jt3call.class
cabarc n jt3call.cab *.class
makecert -sk testkey -n "CN=Test" testcert.cer
cert2spc testcert.cer testcert.spc
REM signcode -j javasign.dll -jp -p Microsoft Base Cryptographic Provider v1.0 -y RSA FULL low -spc testcert.spc -a sha1 -k testkey jt3call.cab
REM del testcert.cer
REM del testcert.spc
