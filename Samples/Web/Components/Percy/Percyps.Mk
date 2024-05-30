
Percyps.dll: dlldata.obj Percy_p.obj Percy_i.obj
	link /dll /out:Percyps.dll /def:Percyps.def /entry:DllMain dlldata.obj Percy_p.obj Percy_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL $<

clean:
	@del Percyps.dll
	@del Percyps.lib
	@del Percyps.exp
	@del dlldata.obj
	@del Percy_p.obj
	@del Percy_i.obj
