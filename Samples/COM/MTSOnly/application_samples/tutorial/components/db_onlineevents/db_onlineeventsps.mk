
db_OnlineEventsps.dll: dlldata.obj db_OnlineEvents_p.obj db_OnlineEvents_i.obj
	link /dll /out:db_OnlineEventsps.dll /def:db_OnlineEventsps.def /entry:DllMain dlldata.obj db_OnlineEvents_p.obj db_OnlineEvents_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL $<

clean:
	@del db_OnlineEventsps.dll
	@del db_OnlineEventsps.lib
	@del db_OnlineEventsps.exp
	@del dlldata.obj
	@del db_OnlineEvents_p.obj
	@del db_OnlineEvents_i.obj
