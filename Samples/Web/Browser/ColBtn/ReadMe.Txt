======================================================
Notes for "COLBTN" Samples
======================================================

The COLBTN example shows a control that accesses and changes the HTML document in which it is contained.

COLBTN is written using ATL2.0 and was originally built using VC++5. The control subclasses a button and causes the background color of the document to change to pink when pressed. Loading the button.htm file into Internet Explorer 4.0 or above, demonstrates the control.

The control actually implements the equivalent of the following line of script to make use of the Dynamic HTML support of IE4:
	document.bgcolor = "pink"

When clicked the button follows these steps to access its container and the document and are shown in the button.h file.

	1) Call getContainer on the client site, to obtain the container's IOleContainer interface
	2) Calls QueryInterface for IHTMLDocument2, this interface gives access to the document.
	3) Call get_Body to obtain the IHTMLBodyElement interface
	4) call put_bgColor

