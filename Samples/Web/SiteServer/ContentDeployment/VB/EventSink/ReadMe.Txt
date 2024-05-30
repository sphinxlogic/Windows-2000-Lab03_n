1) Start VB 5.0
2) Select New ActiveX DLL and click <Open>
3) Select Project->References and check "Microsoft SiteServer 3.0 Server Event Sink Library" or click on <Browse...> and select crssink.tlb
4) Also check "Site Server 3.0 Server Event Type Library" if you wish to use the Event object passed to SiteServerEventSink_OnEvent
5) Also check "Site Server 3.0 Content Deployment Object Library" if you wish to use the helper routines in CReplicationServer
6) Click <OK>
7) Type "Implements SiteServerEventSink" followed by <return> in the "Project1 - Class1 (Code)" window
8) Click on the "(General)" drop down list box and select "SiteServerEventSink"
9) Click on the "Initialize" drop down list box and select each routine: Clear, OnEvent, and Shutdown
10) Write code for each routine
11) Select File->Make Project1.dll to build your DLL
12) regsvr32 Project1.dll
13) Use the following VBScript code to register your event sink with the Content Deployment Service:
	Set Server = CreateObject("CrsApi.ReplicationServer")
	Server.Initialize("")
	' Come up with your own event sink name
	Set EventSink = Server.AddEventSink("Project1_FriendlySinkName")
	' ProgID is ProjectName.ClassName
	EventSink.CLSID = "Project1.Class1"
	' Register for each event you want the sink to receive
	' Add loop here
	EventSink.Commit
14) net stop crs
15) net start crs

Your event sink should now be functional.