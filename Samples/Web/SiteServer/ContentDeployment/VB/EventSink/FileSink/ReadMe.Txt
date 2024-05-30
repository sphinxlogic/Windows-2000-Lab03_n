*** NOTE: This sample requires Visual Basic 5.0 and Visual Studio
***       Service Pack 3

The VB Project file, cdsink.vbp, in this directory can be used to build
cdsink.dll.  After you open the project, go to the Project menu and
select "References...".  Click the Browse button and select the file
%SiteServer_SDK_Location%\include\crssink.tlb.  Then go to the File
menu and select "Make cdsink.dll".

To use this sample event sink, you must first run "cscript regsink.vbs"
to register this sample event sink with the Content Deployment service.
By default the regsink.vbs script will register the event sink for all
events.

This event sink will log events to a text file.  It first looks in the
registry under:
  HKLM\Software\Microsoft\CRS\EventLogging\<EventSinkName>\Filename
for the filename to log to, and if that lookup fails defaults to
"c:\temp\filesink.log".  If you do not have a c:\temp directory it will
fail to log because it makes no attempt to create a "temp" directory.

To create the event sink from scratch without the VB project file, the
same steps followed by the readme.txt located in
Content Deployment\vb\eventsink\readme.txt are followed.  The key is to
use the "implements SiteServerEventSink" to add stubs for all the
interface's subroutines or methods automatically.

    NOTE: In C++ the interface is called IReplicationEventSink, not
    SiteServerEventSink.

The sink will only listen to events for which it is registered.  If a
project filter is used, the sink must not be registered for any events
and all events pertaining to the project will be received instead.