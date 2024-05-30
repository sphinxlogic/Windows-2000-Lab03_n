DBMonitor readme

DBMonitor is a monitoring application that can be used to watch any command line
launched process from outside of the monitored process, logging the requested
information.  DBMonitor does this by making itself the debugger of the monitored
process and taking advantage of the built-in debugger support offered by Win32.

DBMonitor currently collects data on DLL loads, process and thread creation and
destruction, expection reporting, debug output string, and will provide stack
traces and a shortened paramater list for all LoadLibrary calls.  Command line
parameters allow the user to pick and choose among these options, as well as the
output file.

As a sample, DBMonitor provides examples of how to start a process as a debugee
and trap debugging events using the built in Win32 debugging support.  It
provides an example of how to set and handle breakpoints in an executable, and
how to obtain a stack trace from a seperate process (where most of the examples
show how to get a stack trace from an in process exception).

Finally, the DBMonitor source can trivally be extended to allow stacktrace
reporting of any exported API that one may wish to monitor. 