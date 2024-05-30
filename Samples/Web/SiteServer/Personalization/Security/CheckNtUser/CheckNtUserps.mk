
CheckNTUserps.dll: dlldata.obj CheckNTUser_p.obj CheckNTUser_i.obj
	link /dll /out:CheckNTUserps.dll /def:CheckNTUserps.def /entry:DllMain dlldata.obj CheckNTUser_p.obj CheckNTUser_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL $<

clean:
	@del CheckNTUserps.dll
	@del CheckNTUserps.lib
	@del CheckNTUserps.exp
	@del dlldata.obj
	@del CheckNTUser_p.obj
	@del CheckNTUser_i.obj
