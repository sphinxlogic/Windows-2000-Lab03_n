======================================================
Notes for Percy, the IpersistHistory Control
======================================================

Percy is an ATL2.0 control that demonstrates the use of IPersistHistory so that state can be retained if the page containing the control is returned to using the back button.

Percy is a subclassed edit control. Having built the control load percyctl.htm into a browser to see it work.
On navigation away from the page IPersistHistory::SaveHistory() is called supplying a stream into which data should be saved. On return IPersistHistory::LoadHistory() is called so that state can be reloaded.

Note: Only nineteen bytes of data are loaded in the LoadHistory implementation of Percy to load into a temporary buffer.

Percy also implements IObjectSafety specifically to allow IPersistHistory to be used without any security warning dialogs, as Percy is a safe control.
