
HBEventClassps.dll: dlldata.obj HBEventClass_p.obj HBEventClass_i.obj
	link /dll /out:HBEventClassps.dll /def:HBEventClassps.def /entry:DllMain dlldata.obj HBEventClass_p.obj HBEventClass_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del HBEventClassps.dll
	@del HBEventClassps.lib
	@del HBEventClassps.exp
	@del dlldata.obj
	@del HBEventClass_p.obj
	@del HBEventClass_i.obj
