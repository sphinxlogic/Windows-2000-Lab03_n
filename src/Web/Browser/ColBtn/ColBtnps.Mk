
colbtnps.dll: dlldata.obj colbtn_p.obj colbtn_i.obj
	link /dll /out:colbtnps.dll /def:colbtnps.def /entry:DllMain dlldata.obj colbtn_p.obj colbtn_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL $<

clean:
	@del colbtnps.dll
	@del colbtnps.lib
	@del colbtnps.exp
	@del dlldata.obj
	@del colbtn_p.obj
	@del colbtn_i.obj
