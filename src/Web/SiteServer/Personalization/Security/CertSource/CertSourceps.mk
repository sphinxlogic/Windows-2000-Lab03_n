
CertSourceps.dll: dlldata.obj CertSource_p.obj CertSource_i.obj
	link /dll /out:CertSourceps.dll /def:CertSourceps.def /entry:DllMain dlldata.obj CertSource_p.obj CertSource_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL $<

clean:
	@del CertSourceps.dll
	@del CertSourceps.lib
	@del CertSourceps.exp
	@del dlldata.obj
	@del CertSource_p.obj
	@del CertSource_i.obj
