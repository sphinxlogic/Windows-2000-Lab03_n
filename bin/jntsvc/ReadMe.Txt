Here are the steps to create the sample service (TestService.exe):

1)Build the service using the makefile. nmake.exe is available in the
bin directory of the SDK.

2)Install the service by running
TestService /install
from the command prompt.

3)The service is now installed in the NT Service Manager and can be
started, stopped, or paused from the service manager in the Control
Panel.  The stop, start, and pause events will be visible in the Event
Viewer.  The log must be set to look at Application events in order to
see the results.

More information is available from the SDK documention.  For the java
package and the use of the generated service, please refer to the java
package reference for com.ms.service.  For information on using the
jntsvc.exe tool, please refer to the tools documentation section.


