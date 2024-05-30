Controlling Access to Performance Data


The SECPERF sample demonstrates how to control access to the performance data
provided under the registry key HKEY_PERFORMANCE_DATA.

The security on the following registry key dictates which users or groups
can gain access to the performance data:

   HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Perflib

This sample opens the registry key for WRITE_DAC access, which allows it to
apply a new DACL to the registry key.

The sample builds a DACL that grants the following access:

   Administrators are granted full control to allow for future updates to the
   security on the key and to allow for querying performance data.

   Interactively logged on users, through the well-known Interactive Sid,
   are granted KEY_READ access, which allows for querying performance data.

It applies the new DACL to the registry key using the RegSetKeySecurity
function.
