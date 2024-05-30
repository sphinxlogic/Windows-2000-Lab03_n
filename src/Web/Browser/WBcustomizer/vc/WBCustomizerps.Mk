
WBCustomizerps.dll: dlldata.obj WBCustomizer_p.obj WBCustomizer_i.obj
	link /dll /out:WBCustomizerps.dll /def:WBCustomizerps.def /entry:DllMain dlldata.obj WBCustomizer_p.obj WBCustomizer_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL $<

clean:
	@del WBCustomizerps.dll
	@del WBCustomizerps.lib
	@del WBCustomizerps.exp
	@del dlldata.obj
	@del WBCustomizer_p.obj
	@del WBCustomizer_i.obj
