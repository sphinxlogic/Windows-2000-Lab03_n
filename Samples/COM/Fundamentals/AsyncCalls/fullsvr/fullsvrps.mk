
FullSvrps.dll: dlldata.obj FullSvr_p.obj FullSvr_i.obj
	link /dll /out:FullSvrps.dll /def:FullSvrps.def /entry:DllMain dlldata.obj FullSvr_p.obj FullSvr_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0500 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del FullSvrps.dll
	@del FullSvrps.lib
	@del FullSvrps.exp
	@del dlldata.obj
	@del FullSvr_p.obj
	@del FullSvr_i.obj
