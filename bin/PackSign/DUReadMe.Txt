README for Distribution Unit Builder
16 September 1997
------------------------------------

The DUBuild tool creates Distribution Units which work only with Microsoft Internet Explorer 4.  DUBuild is discussed in the Microsoft SDK for Java 2.0 in the Tools section under "Using DUBuild".  DUBUILD.EXE is in the SDK-Java\Bin\PackSign directory.

Although Microsoft Internet Explorer 4 can install packages created for earlier versions, distribution units allow local installation of less-trusted code, offer improved compression, and are managed by the Java VM's Package Manager.  By making distribution unit installation a feature of the <APPLET> tag, it is possible to install restricted code on Microsoft Internet Explorer 4, while causing prior versions to retrieve the untrusted code from the server.


To package Java classes or libraries for use with Microsoft Internet Explorer 3, or for compatibility with both versions of Microsoft Internet Explorer, use CABARC and the MASTER.INF template.  Packaging using CABARC is discussed in the Tools section under "Creating and Using Cabinet Files for Java Applets and Libraries".  CABARC.EXE and the MASTER.INF template are in the SDK-Java\Bin\PackSign directory.

Although CABARC supports multiple compression methods, Microsoft Internet Explorer 3 only recognizes the MSZIP format.


In either case, the produced .CAB files should be signed using SignCode.