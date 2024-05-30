<%@ LANGUAGE="VBSCRIPT"%>
<html>
<!-------------------------------------------------------------------------
 
	This sample illustrates the use of the WMI Scripting API within
   an ASP, using VBScript.  It displays information in a table
   for each disk on the local host.

   To run this sample, 

   1. Place it in a directory accessible to your web server
   2. Ensure that the registry value:-

        HKEY_LOCAL_MACHINE\Software\Microsoft\WBEM\Scripting\Enable for ASP

      is set to 1.
 
---------------------------------------------------------------------------->

<head>
<title>WMI Scripting ASP Sample - Disk Information (VBScript version)</title>
</head>

<body>
<%
	on error resume next

	' Connect to the default namespace (root/cimv2)
	' on the local host
	Set Locator = CreateObject("WbemScripting.SWbemLocator")
	Set Service = locator.connectserver
	
	if Err = 0 then

		'Retrieve the logical disk class
		Set Disk = Service.Get ("Win32_LogicalDisk")
		Set Path = Disk.Path_

		' Enable impersonation before we retrieve
		' the Disk instances otherwise access will
		' be denied
		Disk.Security_.impersonationLevel = 3
		Set Disks = Disk.Instances_
%>

<p>Path of object is <%=Path.DisplayName%></p>

<table BORDER="1">
  <tr>
    <th>Name</th>
    <th>Volume Name</th>
    <th>Volume Serial Number</th>
  </tr>
<%
	for each DiskInstance in Disks
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
		Next
%>
</table>
<%
	Else
%>

<table>
  <tr>
    <td>Error - <%=Err.description%>, <%=Err.number%>, <%=Err.Source%></td>
  </tr>
</table>
<%
	End If
%>
</body>
</html>
