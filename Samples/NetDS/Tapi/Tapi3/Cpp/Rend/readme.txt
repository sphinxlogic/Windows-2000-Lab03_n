THIS IS NOT SUPPORTED BY MICROSOFT CORPORATION. IT IS PROVIDED "AS IS" BECAUSE WE BELIEVE IT MAY BE USEFUL TO YOU


	TAPI 3.0 Rendezvous Controls Sample Program


What the sample does?
~~~~~~~~~~~~~~~~~~~~~

RendSam is a simple program demonstrates how to use TAPI 3.0 Rendezvous Controls COM interfaces to 

. open an ILS directory, 
. configure a conference, 
. add a conference,
. enumerate conferences, 
. delete a conference,
. configure a user,
. add a user,
. enumerate users, and
. delete a user,

A few methods in TAPI 3.0 SDPBLB COM interfaces are also used in configuring a conference.


How to build the sample program?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Set the SDK build environment (see SDK readme file.), then type "nmake" in this "Rend" directory. RendSam.exe will be built.


How to use the sample program?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

After RendSam.exe is built, run 
	RendSam <ils>
where <ils> is the name or IP address of an ILS server. Note that credentials of the currently logged on user's will be used to bind to the ILS server.


What this sample does not show?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This sample does not query NTDS to find all available ILS servers, instead an ILS server is specified in command line. Conference and user configurations were minimal. One can use other methods in Rendezvous Control or SDP BLOB COM interfaces to do more complex configurations. 


 
