
Accountps.dll: dlldata.obj Account_p.obj Account_i.obj
	link /dll /out:Accountps.dll /def:Accountps.def /entry:DllMain dlldata.obj Account_p.obj Account_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib uuid.lib 

.c.obj:
	cl /c /Ox /DWIN32 /DREGISTER_PROXY_DLL $<

clean:
	@del Accountps.dll
	@del Accountps.lib
	@del Accountps.exp
	@del dlldata.obj
	@del Account_p.obj
	@del Account_i.obj
