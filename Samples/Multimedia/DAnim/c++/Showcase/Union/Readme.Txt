General:

The Donut sample takes the DirectDraw donut sample from the DirectX SDK and adds two animating text strings to it using DirectAnimation. It shows how DirectAnimation can be added to an existing DirectDraw application.

Build Instructions:

How to Build the DirectAnimation C++ Samples that Render to DirectDraw Surfaces.

To build the DirectAnimation C++ samples from the command line, follow these steps: 

Make sure that the directories containing the Danim.dll, Ddrawex.h, and Guids.lib files are in your computer's path, include, and lib environment, respectively. For example: SET LIB=c:\dxmedia\lib\;
If you are using untilNotify, make sure that Daguid.lib is also in your lib environment. 

Danim.dll should be located in the Windows\System directory for Windows 95 or Windows\System32 directory for Windows NT; Internet Explorer 4.x installs it. 

If you can't find Ddrawex.h, Guids.lib, or Daguid.lib on your computer, there are copies in the Include and Lib directories of the DirectX Media SDK. 

Go to the directory where the samples are located and run NMAKE. Note that for the C++ samples included in this SDK, the Release build is the default build.

To build DirectAnimation C++ samples in Microsoft Visual C++ 5.x, set the paths as described in Step 1, and then follow these steps: 

- Start Microsoft Visual C++ 5.x and create a new Win32 application. 
- From the Project menu, choose Settings, and then choose the Link tab. 
- Select General in the Category drop-down list. 
- Add Guids.lib (and Daguid.lib if using untilNotify) to the Object/library modules text box. 
- Click OK. 
- From the Project menu, choose Add To Project, then select Files and insert the DirectAnimation C++ files into the       project. 
- Press the F7 key to build. 
