REM Note that missing classes in log file mean tthe hat WMI cannot access them.
REM Most likely this indicates a problem with the driver.
REM See %windir%\system32\wbem\wmiprov.log and nt eventlog for more details.
REM You could also delete the line On Error Resume Next and examine the
REM specific VBScript error


On Error Resume Next

Set fso = CreateObject("Scripting.FileSystemObject")
Set a = fso.CreateTextFile("filter.log", True)
Set Service = GetObject("winmgmts:{impersonationLevel=impersonate}!root/wmi")
Rem Vendor_SampleClass1 - Description of sample class 1
Set enumSet = Service.InstancesOf ("Vendor_SampleClass1")
a.WriteLine("Vendor_SampleClass1")
for each instance in enumSet
    a.WriteLine("    InstanceName=" & instance.InstanceName)
    a.WriteLine("        instance.Xboolean=" & instance.Xboolean)
    a.WriteLine("        instance.Xuint8=" & instance.Xuint8)
    a.WriteLine("        instance.Xuint16=" & instance.Xuint16)
    a.WriteLine("        instance.Xuint32=" & instance.Xuint32)
    a.WriteLine("        instance.Xuint64=" & instance.Xuint64)
    a.WriteLine("        instance.Xint8=" & instance.Xint8)
    a.WriteLine("        instance.Xint16=" & instance.Xint16)
    a.WriteLine("        instance.Xint32=" & instance.Xint32)
    a.WriteLine("        instance.Xint64=" & instance.Xint64)
    a.WriteLine("        instance.Xdatetime=" & instance.Xdatetime)
next 'instance

Rem Vendor_SampleClass2 - Description of Sample Class 2
Set enumSet = Service.InstancesOf ("Vendor_SampleClass2")
a.WriteLine("Vendor_SampleClass2")
for each instance in enumSet
    a.WriteLine("    InstanceName=" & instance.InstanceName)
    a.WriteLine("        instance.EmbeddedClass1.Xboolean=" & instance.EmbeddedClass1.Xboolean)
    a.WriteLine("        instance.EmbeddedClass1.Xuint8=" & instance.EmbeddedClass1.Xuint8)
    a.WriteLine("        instance.EmbeddedClass1.Xuint16=" & instance.EmbeddedClass1.Xuint16)
    a.WriteLine("        instance.EmbeddedClass1.Xuint32=" & instance.EmbeddedClass1.Xuint32)
    a.WriteLine("        instance.EmbeddedClass1.Xuint64=" & instance.EmbeddedClass1.Xuint64)
    a.WriteLine("        instance.EmbeddedClass1.Xint8=" & instance.EmbeddedClass1.Xint8)
    a.WriteLine("        instance.EmbeddedClass1.Xint16=" & instance.EmbeddedClass1.Xint16)
    a.WriteLine("        instance.EmbeddedClass1.Xint32=" & instance.EmbeddedClass1.Xint32)
    a.WriteLine("        instance.EmbeddedClass1.Xint64=" & instance.EmbeddedClass1.Xint64)
    a.WriteLine("        instance.EmbeddedClass1.Xdatetime=" & instance.EmbeddedClass1.Xdatetime)
next 'instance

Rem Vendor_SampleClass3 - Description of Sample Class 3
Set enumSet = Service.InstancesOf ("Vendor_SampleClass3")
a.WriteLine("Vendor_SampleClass3")
for each instance in enumSet
    a.WriteLine("    InstanceName=" & instance.InstanceName)
    for i1 = 0 to (4-1)
    a.WriteLine("        instance.EmbeddedClass1("&i1&").Xboolean=" & instance.EmbeddedClass1(i1).Xboolean)
    a.WriteLine("        instance.EmbeddedClass1("&i1&").Xuint8=" & instance.EmbeddedClass1(i1).Xuint8)
    a.WriteLine("        instance.EmbeddedClass1("&i1&").Xuint16=" & instance.EmbeddedClass1(i1).Xuint16)
    a.WriteLine("        instance.EmbeddedClass1("&i1&").Xuint32=" & instance.EmbeddedClass1(i1).Xuint32)
    a.WriteLine("        instance.EmbeddedClass1("&i1&").Xuint64=" & instance.EmbeddedClass1(i1).Xuint64)
    a.WriteLine("        instance.EmbeddedClass1("&i1&").Xint8=" & instance.EmbeddedClass1(i1).Xint8)
    a.WriteLine("        instance.EmbeddedClass1("&i1&").Xint16=" & instance.EmbeddedClass1(i1).Xint16)
    a.WriteLine("        instance.EmbeddedClass1("&i1&").Xint32=" & instance.EmbeddedClass1(i1).Xint32)
    a.WriteLine("        instance.EmbeddedClass1("&i1&").Xint64=" & instance.EmbeddedClass1(i1).Xint64)
    a.WriteLine("        instance.EmbeddedClass1("&i1&").Xdatetime=" & instance.EmbeddedClass1(i1).Xdatetime)
    next 'i1
next 'instance

Rem Vendor_SampleClass4 - Description of Sample Class 4
Set enumSet = Service.InstancesOf ("Vendor_SampleClass4")
a.WriteLine("Vendor_SampleClass4")
for each instance in enumSet
    a.WriteLine("    InstanceName=" & instance.InstanceName)
    a.WriteLine("        instance.Count=" & instance.Count)
    for i1 = 0 to (instance.Count-1)
    a.WriteLine("        instance.EmbeddedClass1("&i1&").Xboolean=" & instance.EmbeddedClass1(i1).Xboolean)
    a.WriteLine("        instance.EmbeddedClass1("&i1&").Xuint8=" & instance.EmbeddedClass1(i1).Xuint8)
    a.WriteLine("        instance.EmbeddedClass1("&i1&").Xuint16=" & instance.EmbeddedClass1(i1).Xuint16)
    a.WriteLine("        instance.EmbeddedClass1("&i1&").Xuint32=" & instance.EmbeddedClass1(i1).Xuint32)
    a.WriteLine("        instance.EmbeddedClass1("&i1&").Xuint64=" & instance.EmbeddedClass1(i1).Xuint64)
    a.WriteLine("        instance.EmbeddedClass1("&i1&").Xint8=" & instance.EmbeddedClass1(i1).Xint8)
    a.WriteLine("        instance.EmbeddedClass1("&i1&").Xint16=" & instance.EmbeddedClass1(i1).Xint16)
    a.WriteLine("        instance.EmbeddedClass1("&i1&").Xint32=" & instance.EmbeddedClass1(i1).Xint32)
    a.WriteLine("        instance.EmbeddedClass1("&i1&").Xint64=" & instance.EmbeddedClass1(i1).Xint64)
    a.WriteLine("        instance.EmbeddedClass1("&i1&").Xdatetime=" & instance.EmbeddedClass1(i1).Xdatetime)
    next 'i1
next 'instance

Rem Vendor_SampleClass5 - Description of Sample Class 5
Set enumSet = Service.InstancesOf ("Vendor_SampleClass5")
a.WriteLine("Vendor_SampleClass5")
for each instance in enumSet
    a.WriteLine("    InstanceName=" & instance.InstanceName)
    for i2 = 0 to (8-1)
    a.WriteLine("        instance.EmbeddedClass2.Xboolean("&i2&")=" & instance.EmbeddedClass2.Xboolean(i2))
    next 'i2
    for i2 = 0 to (8-1)
    a.WriteLine("        instance.EmbeddedClass2.Xuint8("&i2&")=" & instance.EmbeddedClass2.Xuint8(i2))
    next 'i2
    for i2 = 0 to (4-1)
    a.WriteLine("        instance.EmbeddedClass2.Xuint16("&i2&")=" & instance.EmbeddedClass2.Xuint16(i2))
    next 'i2
    for i2 = 0 to (2-1)
    a.WriteLine("        instance.EmbeddedClass2.Xuint32("&i2&")=" & instance.EmbeddedClass2.Xuint32(i2))
    next 'i2
    a.WriteLine("        instance.EmbeddedClass2.Xuint64=" & instance.EmbeddedClass2.Xuint64)
    for i2 = 0 to (8-1)
    a.WriteLine("        instance.EmbeddedClass2.Xint8("&i2&")=" & instance.EmbeddedClass2.Xint8(i2))
    next 'i2
    for i2 = 0 to (4-1)
    a.WriteLine("        instance.EmbeddedClass2.Xint16("&i2&")=" & instance.EmbeddedClass2.Xint16(i2))
    next 'i2
    for i2 = 0 to (2-1)
    a.WriteLine("        instance.EmbeddedClass2.Xint32("&i2&")=" & instance.EmbeddedClass2.Xint32(i2))
    next 'i2
    a.WriteLine("        instance.EmbeddedClass2.Xint64=" & instance.EmbeddedClass2.Xint64)
    a.WriteLine("        instance.EmbeddedClass2.Xdatetime=" & instance.EmbeddedClass2.Xdatetime)
next 'instance

Rem Vendor_SampleClass6 - Description of Sample Class 6
Set enumSet = Service.InstancesOf ("Vendor_SampleClass6")
a.WriteLine("Vendor_SampleClass6")
for each instance in enumSet
    a.WriteLine("    InstanceName=" & instance.InstanceName)
    for i1 = 0 to (4-1)
    for i2 = 0 to (8-1)
    a.WriteLine("        instance.EmbeddedClass2("&i1&").Xboolean("&i2&")=" & instance.EmbeddedClass2(i1).Xboolean(i2))
    next 'i2
    for i2 = 0 to (8-1)
    a.WriteLine("        instance.EmbeddedClass2("&i1&").Xuint8("&i2&")=" & instance.EmbeddedClass2(i1).Xuint8(i2))
    next 'i2
    for i2 = 0 to (4-1)
    a.WriteLine("        instance.EmbeddedClass2("&i1&").Xuint16("&i2&")=" & instance.EmbeddedClass2(i1).Xuint16(i2))
    next 'i2
    for i2 = 0 to (2-1)
    a.WriteLine("        instance.EmbeddedClass2("&i1&").Xuint32("&i2&")=" & instance.EmbeddedClass2(i1).Xuint32(i2))
    next 'i2
    a.WriteLine("        instance.EmbeddedClass2("&i1&").Xuint64=" & instance.EmbeddedClass2(i1).Xuint64)
    for i2 = 0 to (8-1)
    a.WriteLine("        instance.EmbeddedClass2("&i1&").Xint8("&i2&")=" & instance.EmbeddedClass2(i1).Xint8(i2))
    next 'i2
    for i2 = 0 to (4-1)
    a.WriteLine("        instance.EmbeddedClass2("&i1&").Xint16("&i2&")=" & instance.EmbeddedClass2(i1).Xint16(i2))
    next 'i2
    for i2 = 0 to (2-1)
    a.WriteLine("        instance.EmbeddedClass2("&i1&").Xint32("&i2&")=" & instance.EmbeddedClass2(i1).Xint32(i2))
    next 'i2
    a.WriteLine("        instance.EmbeddedClass2("&i1&").Xint64=" & instance.EmbeddedClass2(i1).Xint64)
    a.WriteLine("        instance.EmbeddedClass2("&i1&").Xdatetime=" & instance.EmbeddedClass2(i1).Xdatetime)
    next 'i1
next 'instance

Rem Vendor_SampleClass7 - Description of Sample Class 7
Set enumSet = Service.InstancesOf ("Vendor_SampleClass7")
a.WriteLine("Vendor_SampleClass7")
for each instance in enumSet
    a.WriteLine("    InstanceName=" & instance.InstanceName)
    a.WriteLine("        instance.Count=" & instance.Count)
    for i1 = 0 to (instance.Count-1)
    for i2 = 0 to (8-1)
    a.WriteLine("        instance.EmbeddedClass2("&i1&").Xboolean("&i2&")=" & instance.EmbeddedClass2(i1).Xboolean(i2))
    next 'i2
    for i2 = 0 to (8-1)
    a.WriteLine("        instance.EmbeddedClass2("&i1&").Xuint8("&i2&")=" & instance.EmbeddedClass2(i1).Xuint8(i2))
    next 'i2
    for i2 = 0 to (4-1)
    a.WriteLine("        instance.EmbeddedClass2("&i1&").Xuint16("&i2&")=" & instance.EmbeddedClass2(i1).Xuint16(i2))
    next 'i2
    for i2 = 0 to (2-1)
    a.WriteLine("        instance.EmbeddedClass2("&i1&").Xuint32("&i2&")=" & instance.EmbeddedClass2(i1).Xuint32(i2))
    next 'i2
    a.WriteLine("        instance.EmbeddedClass2("&i1&").Xuint64=" & instance.EmbeddedClass2(i1).Xuint64)
    for i2 = 0 to (8-1)
    a.WriteLine("        instance.EmbeddedClass2("&i1&").Xint8("&i2&")=" & instance.EmbeddedClass2(i1).Xint8(i2))
    next 'i2
    for i2 = 0 to (4-1)
    a.WriteLine("        instance.EmbeddedClass2("&i1&").Xint16("&i2&")=" & instance.EmbeddedClass2(i1).Xint16(i2))
    next 'i2
    for i2 = 0 to (2-1)
    a.WriteLine("        instance.EmbeddedClass2("&i1&").Xint32("&i2&")=" & instance.EmbeddedClass2(i1).Xint32(i2))
    next 'i2
    a.WriteLine("        instance.EmbeddedClass2("&i1&").Xint64=" & instance.EmbeddedClass2(i1).Xint64)
    a.WriteLine("        instance.EmbeddedClass2("&i1&").Xdatetime=" & instance.EmbeddedClass2(i1).Xdatetime)
    next 'i1
next 'instance

Rem Vendor_GetSetData - Methods that can get and set data
Set enumSet = Service.InstancesOf ("Vendor_GetSetData")
a.WriteLine("Vendor_GetSetData")
for each instance in enumSet
    a.WriteLine("    InstanceName=" & instance.InstanceName)
next 'instance

Rem Vendor_FireEvent - Method that fire events
Set enumSet = Service.InstancesOf ("Vendor_FireEvent")
a.WriteLine("Vendor_FireEvent")
for each instance in enumSet
    a.WriteLine("    InstanceName=" & instance.InstanceName)
next 'instance

a.Close
Wscript.Echo "filter Test Completed, see filter.log for details"
