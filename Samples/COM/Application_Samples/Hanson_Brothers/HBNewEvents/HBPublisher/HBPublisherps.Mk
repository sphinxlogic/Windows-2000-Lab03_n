
HBPublisherps.dll: dlldata.obj HBPublisher_p.obj HBPublisher_i.obj
	link /dll /out:HBPublisherps.dll /def:HBPublisherps.def /entry:DllMain dlldata.obj HBPublisher_p.obj HBPublisher_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del HBPublisherps.dll
	@del HBPublisherps.lib
	@del HBPublisherps.exp
	@del dlldata.obj
	@del HBPublisher_p.obj
	@del HBPublisher_i.obj
