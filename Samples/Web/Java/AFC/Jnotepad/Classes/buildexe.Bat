@echo off
rem JNotepad EXE builder
rem Assumes jexegen is in your path

jexegen /main:JNotePad /out:jnotepad.exe /w /v *.class
