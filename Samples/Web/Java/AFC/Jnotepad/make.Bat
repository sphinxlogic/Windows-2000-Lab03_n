@echo off
rem Compiles JNotepad
jvc /d classes src\*.java
echo ÿ
echo To run JNotepad, go to the classes directory and type 'jview JNotepad'.
echo Or, to create a standalone Win32 exe, go to the classes directory and
echo run 'buildexe.bat'. This will create JNotepad.exe.
echo ÿ


