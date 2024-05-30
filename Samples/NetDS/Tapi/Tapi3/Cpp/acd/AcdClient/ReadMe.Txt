TAPI 3.0
Sample ACD client application

Overview:

This application allows users to create agents and agent sessions, 
monitors the corresponding address for incoming calls, allows the 
user to answer/disconnect the incoming calls and sets the agent and 
session states to reflect these changes.

In order to receive incoming call notifications, as well as any call
state event notifications, the outgoing ITCallNotification interface
must be implemented by the TAPI 3.0 application, and registered with
TAPI 3.0 through the IConnectionPoint mechanism.  For more information
on IConnectionPoint, and IConnectiontPointContainer, please refer
to the COM documentation.

CALLNOT.CPP and CALLNOT.H show the implementation of the ITCallNotification
interface.  ITCallNotification is defined by TAPI 3.0, and the interface
definition is in tapi3.h.

CLIENT.CPP shows how to create agents, sessions and to register the 
interface, and how to answer an incoming call.

How to build the sample:

To run the CLIENT sample application, set the SDK build environment, then
type "nmake" in the incoming directory.  This will build client.exe


How to use the sample:

After the sample is built, run client.exe.

If the application does not find any agent handlers on your machine,
an error message will be displayed and it will exit, otherwise, a 
dialog box will apprear, with three list boxes, one containing a list
of agent handlers, one containing the ACD groups on the selected agent
handler and the last containing the list of usable addresses on the 
selected agent handler. 

You can select an agent handler and create an agent on it. Upon changing
the agent handler selection, the other two list boxes will automatically 
be updated with the information about the newly selected agent handler.

To create an agent session, you will have to chose an ACD group and an
address in addition to the agent handler.

Once the agent session is created you can proceed to the call monitoring
by selecting OK, which will open up a new Dialog box containing call 
status of the calls on the selected address. 
When the agent is ready to receive calls the status will change to
waiting for incoming calls. When a call arrives, the 
"Answer" button will be enabled and the status message will change to 
"Incoming Call".

When the "Answer" button is clicked, the application will answer
the call. The "Disconnect" button will then be enabled, allowing the 
user to disconnect the call by clicking this button. Once the call is
disconnected, and agent has finished wrapup activity, 
the application goes back to listening for calls on the 
specified address.

In addition, the agent and session status are displayed and constantly
updated. 

What functionality does this sample show:

The ACD client sample application primarily demonstrates how to create 
agents and agent sessions. It also shows how to listen for calls on
address by implementing the ITCallNotification interface.

This sample creates ONLY a single agent / session. This is not a 
limitation and multiple agents / sessions can be creared. This was
not put in the sample in order to keep the sample simple.

Hints:

This sample will not run without  agent handlers 
available on your machine. The agent handler can be created using the ACD proxy 
sample or using tb20 and opening one or more lines as a proxy.
