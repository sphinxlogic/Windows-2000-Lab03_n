<%@ LANGUAGE="JSCRIPT"%>
<html>
<!-------------------------------------------------------------------------
 
	This sample illustrates the use of the WMI Scripting API within
   an ASP, using JScript.  It displays information in a table
   for each disk on the local host.

   To run this sample, 

   1. Place it in a directory accessible to your web server
   2. Ensure that the registry value:-

        HKEY_LOCAL_MACHINE\Software\Microsoft\WBEM\Scripting\Enable for ASP

      is set to 1.
 
---------------------------------------------------------------------------->

<head>
<title>WMI Scripting ASP Sample - Disk Information (JScript Version)</title>
</head>

<body>
<%
	// Connect to the default namespace (root/cimv2)
	// on the local host
	var Locator = new ActiveXObject ("WbemScripting.SWbemLocator");
	var Service = Locator.connectserver ();
	
	// Retrieve the logical disk class
	var Disk = Service.Get ("Win32_LogicalDisk");
	var Path = Disk.Path_;

	// Enable impersonation before we retrieve
	// the Disk instances otherwise access will
	// be denied
	Disk.Security_.impersonationLevel = 3;
	var Disks = new Enumerator (Disk.Instances_());
%>

<p>Path of object is <%=Path.DisplayName%></p>

<table BORDER="1">
  <tr>
    <th>Name</th>
    <th>Volume Name</th>
    <th>Volume Serial Number</th>
  </tr>
<%
	for (;!Disks.atEnd ();Disks.moveNext ())
	{
		var DiskInstance = Disks.item();
%>
  <tr>
    <td><%=DiskInstance.Name%>
</td>
    <td><%=DiskInstance.VolumeName%>
</td>
    <td><%=DiskInstance.VolumeSerialNumber%>
</td>
  </tr>
<%
	}
%>
</table>
</body>
</html>
