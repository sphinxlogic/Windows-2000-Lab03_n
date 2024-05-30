Sample: VB_DRAW

Purpose: 
This application demonstrates how to use the MSMQ COM objects from VB.  The application basically allows the user to send/receive line drawings to/from other draw applications.  Note that there are other implementations of this "line drawing" protocol in C which inter-operate with this sample.

A private text based format is used to encode line-drawing information.  VB event handling is used to implement asynchronous message arrival.


Requirements:
VB5 is required (specifically the Dim WithEvents construct is used).

MSMQ must be installed -- specifically mqoa.dll must be registered and on the path.


Overview:
When a VB_DRAW application is started, the user is prompted to specify her "login" name -- this can be any string and is used to create a local queue by that name.

At this point a VB_DRAW form is displayed that allows the user to draw lines on its client area by dragging and clicking the left mouse button.  Click the right button to erase the screen.  These mouse movements are captured and translated into a series of line coordinates.  These coordinates are echoed on the form using standard VB Line commands and also sent to the queue specified by the "login" string.  Likewise text can be entered.

In addition, there is a "Remote Friend" textbox that allows the user to specify the name of a queue from which she wishes to receive "remote" drawings.  If this queue name is specified then an asynchronous message handler is invoked to monitor this queue: messages that arrive are interpreted as line drawings and displayed on the form. 

The upshot is that both local and remote drawings/text can appear on the same form.


