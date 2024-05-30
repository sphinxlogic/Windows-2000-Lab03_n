
AtlBrowserps.dll: dlldata.obj AtlBrowser_p.obj AtlBrowser_i.obj
	link /dll /out:AtlBrowserps.dll /def:AtlBrowserps.def /entry:DllMain dlldata.obj AtlBrowser_p.obj AtlBrowser_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL $<

clean:
	@del AtlBrowserps.dll
	@del AtlBrowserps.lib
	@del AtlBrowserps.exp
	@del dlldata.obj
	@del AtlBrowser_p.obj
	@del AtlBrowser_i.obj
