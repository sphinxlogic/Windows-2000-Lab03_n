General:

The Behavior Hook sample demonstrates how to implement a behavior hooks.  In this case is used to constrain the movement of the red square within the polygon.

It derives a container from the CControlHost class to host the DirectAnimation Windowed Control. 

Build Instructions:

How to Build the DirectAnimation C++ Samples that Use the Windowed Control.

To build the DirectAnimation C++ samples from the command line, follow these steps: 

Make sure that the directory containing the Danim.dll file is in your computer's path. For example: SET PATH=c:\windows\system\;
If you are using untilNotify, make sure that Daguid.lib is also in your lib environment. 

Danim.dll should be located in the Windows\System directory for Windows 95 or Windows\System32 directory for Windows NT.

If you can't find Ddrawex.h or Daguid.lib on your computer, there are copies in the Include and Lib directories of the DirectX Media SDK. 

Go to the directory where the samples are located and run NMAKE. Note that for the C++ samples included in this SDK, the Release build is the default build. 

To build DirectAnimation C++ samples in Microsoft® Visual C++® 5.x, set the paths as described in Step 1, and then follow these steps: 

- Start Microsoft Visual C++ 5.x and create a new Win32 application. 
- From the Project menu, choose Add To Project, and then select Files and insert the DirectAnimation C++ files into the project. 
- Press the F7 key to build.

- If you are using untilNotify, you need to perform the following additional steps before you build: 

  - From the Project menu, choose Settings, and then choose the Link tab. 
  - Select General in the Category drop-down list. 
  - Add Daguid.lib to the Object/library modules text box. 
  - Click OK. 

