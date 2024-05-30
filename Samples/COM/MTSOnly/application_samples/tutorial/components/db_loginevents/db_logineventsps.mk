
db_LoginEventsps.dll: dlldata.obj db_LoginEvents_p.obj db_LoginEvents_i.obj
	link /dll /out:db_LoginEventsps.dll /def:db_LoginEventsps.def /entry:DllMain dlldata.obj db_LoginEvents_p.obj db_LoginEvents_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL $<

clean:
	@del db_LoginEventsps.dll
	@del db_LoginEventsps.lib
	@del db_LoginEventsps.exp
	@del dlldata.obj
	@del db_LoginEvents_p.obj
	@del db_LoginEvents_i.obj
