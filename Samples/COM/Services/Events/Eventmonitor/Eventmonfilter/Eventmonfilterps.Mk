
EventMonFilterps.dll: dlldata.obj EventMonFilter_p.obj EventMonFilter_i.obj
	link /dll /out:EventMonFilterps.dll /def:EventMonFilterps.def /entry:DllMain dlldata.obj EventMonFilter_p.obj EventMonFilter_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del EventMonFilterps.dll
	@del EventMonFilterps.lib
	@del EventMonFilterps.exp
	@del dlldata.obj
	@del EventMonFilter_p.obj
	@del EventMonFilter_i.obj
