========================================================================
       WAB Property Inspector Tool ("wabtool")
========================================================================

The WAB Property Inspector Tool ("wabtool") sample application demonstrates 
how to program to the Internet Explorer Address Book also known as the
Windows Address Book (WAB).

The sample specifically demonstrates the following:
- Loading the WAB DLL
- Getting an instance to IWABObject and IAdrBook
- Reading the contents of a WAB file
- Reading the properties of objects in a WAB 
- Modifying properties of objects in a WAB
- Displaying Details on objects in a WAB
- Deleting objects in a WAB
- Creating new objects in a WAB

When you start the wabtool application, wabtool loads the contents of your
default WAB and displays them in a dialog. To view the properties of any one
of the contacts in your WAB, select an entry in the ListView. A list of 
property tags for that entry are displayed in a list box. Selecting a property
tag in the listbox displays details on that property. If there are no entries
in your default WAB, you can select some other WAB file or create a new entry
and view its properties. Wabtool will also allow you to modify 
string-properties on any object displayed from the WAB.

This sample has been created with Visual C++ 6.0 and MFC. To compile this
sample, its probably easiest to create a new project in Visual C++ 6.0. To
do this, start VC++ 6.0 and open the "wabtool.dsw" file. Make sure to add the 
"Workshop\include" and "Workshop\include\Nt50" directories in your list of include
directories and "Workshop\lib" and "Workshop\lib\Nt50" directories in your list
of lib directories. If you have MFC correctly installed, you can now build the
wabtool.exe.

List of files in this project:

DlgProp.h
DlgProp.cpp
makefile
Resource.h
StdAfx.h
StdAfx.cpp
wabobject.h
wabobject.cpp
wabtool.h
wabtool.cpp
wabtool.dsp
wabtool.ico
wabtool.mak
wabtool.rc
wabtool.rc2
wabtoolDlg.h
wabtoolDlg.cpp

