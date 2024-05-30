start /w regsvr32 com\natcom.dll
call java\_2\reg.bat
jview java._1.JMain
call java\_2\unreg.bat
start /w regsvr32 /u com\natcom.dll
