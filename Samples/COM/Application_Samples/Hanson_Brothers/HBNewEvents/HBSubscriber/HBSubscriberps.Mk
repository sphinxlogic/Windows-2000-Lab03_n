
HBSubscriberps.dll: dlldata.obj HBSubscriber_p.obj HBSubscriber_i.obj
	link /dll /out:HBSubscriberps.dll /def:HBSubscriberps.def /entry:DllMain dlldata.obj HBSubscriber_p.obj HBSubscriber_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del HBSubscriberps.dll
	@del HBSubscriberps.lib
	@del HBSubscriberps.exp
	@del dlldata.obj
	@del HBSubscriber_p.obj
	@del HBSubscriber_i.obj
