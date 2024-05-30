TAPI 3.0
Sample ACD proxy application

Overview:

This application demonstrates the working of an ACD proxy application.
This application allows creation of ACD groups and software call 
queues, handles proxy request messages from clients and sends status 
messages back to TAPI to reflect any changes in status. You can set 
the users who will be allowed to create agents on this proxy. All the
above details should be specified in a file proxy.ini. Edit this file 
to replace GoodAgentName in 

"[Users]
Name=GoodAgentName"

with the user name you want to create acd agent with say your account name.


Also, make sure you modify the following value in proxy.ini:
"[General]
NumProxies=10"

to be value bigger than 10, if you have more then 10 tapi lines 
on your system. Otherwise the app will only work with the first 10 ones.


After you are done modifying proxy.ini, before starting this application, 
copy proxy.ini file to %windir%.

    

This app detects incoming calls and adds the calls to appropriate queues.
Periodically (every 5 seconds) it also checks queues for calls to 
be answered, if any are found, it looks for a free agent and agent
session and if any are found, it uses these to service the call.

ACDPROXY.CPP is the implementation of the proxy server.

How to build the sample:

namke command will build the sample (set up sdk build environment first).

How to use the sample:


What functionality does this sample show:

The ACD proxy sample application primarily demonstrates how to open lines 
with proxy previlages, create acdgroups, acd queues, acd agent, acd agent 
sessions, and ditribute calls among different agent sessions.



Notes:

One of the applications that can be run in order to use the ACDClient 
application under sdk\sample\netds\tapi\tapi3\cpp\acd\acdclient
