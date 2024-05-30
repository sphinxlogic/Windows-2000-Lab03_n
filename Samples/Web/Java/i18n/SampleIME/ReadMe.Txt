README.TXT

SampleIME is a sample class which demostarates how to use DefaultInputManager and
InputMethodListener interface to implement an IME in Microsoft VM. SampleIME
allows users to input unicode characters by typing the hexadecimal value
of the unicode characters.

To Compile SampleIME
====================
To compile this example, just compile all of the *.java files. You
could type the following under DOS prompt if Microsoft SDK for Java
is installed:

jvc *.java

To Run SampleIME
================
To run SampleIME, please compile all the *.java file. You could 
use the following under DOS prompt to start this example:

jview SampleIMETest.class

Or you could run it from Internet Explorer, open the
following file using IE:

Sample.html

To Use SampleIME
================
When this example is started, you could use TextArea and TextField 
as normal. When you want to use SampleIME, click on the button which
says "Click here to activate SampleIME."

After doing so, you could click on the TextFields again,
, type '41', and press Enter. You should see an 'A' appearing on
the TextField, because 0x41( hexadecimal value ) is the unicode
represenation of 'A'. If you are using a FarEast version of Windows,
you could input CJK characters by typing their unicode value.
For example, if you type '4e00', you should see
the Chinese character "one".

As you type along, you will find the IME will move the composition
window to the lower right corner of the input caret. This is called
IME level 2 ( near-caret ) support.

Only digit 0 to digit 9, and 'a' through 'f' are accepted for this IME.
Those characters which are not accepted by the IME will appear on the TextFiled.
If you type something wrong on the IME, you could use BackSpace to 
correct them.

If there are no characters appearing on the TextField, please make
sure that the input focus is on the TextField. You could do so by
clicking on the TextField.

There is a button on the left of the IME which is used to activate/
deactivate the IME. Besides, you could use mouse to click on the window
of IME except the button area to drag the IME around.

Toggle IMEs
===========
You could use Ctrl-Alt to toggle between different Java-based IMEs. In this 
example, there is only one Java IME, therefore, pressing Ctrl-Alt will 
activate/deactivate SampleIME. If you are running this under Far East 
version of Windows, pressing Ctrl-Alt for the first time will switch to 
system IME. And pressing it again will deactivate both system IME and
SampleIME. If you press Ctrl-Alt again,SampleIME will be activated.

File List
=========
 SampleIME.java
	The IME itself. 
 SampleIMEWindow.java
    The composition window.	
 SampleIMETest.java
	The sample application which uses SampleIME.
 SampleIMETestFrame.java
	The Frame used by sample application.
