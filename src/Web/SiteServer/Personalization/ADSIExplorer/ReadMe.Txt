Purpose of this sample is to view/expose Active Directories in an Explorer-style application. If you are not familar with Active Directories (ADSI) or the corresponding COM interfaces (IADS), here are some references:
	http://www.microsoft.com/ntserver/guide/adsi.asp
	http://premium.microsoft.com/msdn/library/sdkdoc/adsi/ds2intro_7agj.htm

ADSI is a layer between an application (such as ADSIExplorer) and the underlying Active Directory. ADSI provides interfaces that allow an Active Directory to be manipulated from C/C++, Visual Basic, and Visual Basic Script. 

ADSIExplorer will allow you to connect to the following ADSI providers:
	IIS (ex. use to connect to IIS metabase)
	LDAP (ex. use to connect to Site Server Personalization database)
	WinNT (ex. use to connect to User Manager database)

***Visual Basic MUST be installed before Site Server. Visual Basic sp3 or most current service pack must be installed. 

1) Site Server must be installed
2) Start VB 5.0
3) Select Existing Project and choose "ADSIExplorer.vbp"
4) Add the following Project|References to the project
      FastADS Extensions v1.0
      Active DS Type Library
      OLE Automation
5) Build/Run project
6) The window should display all available ADSI providers. Choose a provider
7) Type in a machine name.
8) Top level DS containers should be visible.
9) Right-click and choose properties to view properties or children.

If a provider has specific non-standand functions such as enumerating children, the values of these functions will not display in this application. Additional programming is required to see that information.
