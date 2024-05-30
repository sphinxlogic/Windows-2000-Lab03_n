General:

The Movie sample illustrates the use of #include "danim.h" instead of #import "danim.dll", and how to render movies through DirectAnimation.  This sample uses IDAViewPtr::IDirectDrawSurface to render to a DDraw Surface.

Build Instructions:

How to Build the DirectAnimation C++ Samples that Render to DirectDraw Surfaces, using #include "danim.h"

To build the DirectAnimation C++ samples from the command line, follow these steps: 

Make sure that the directories containing the Danim.h, Ddrawex.h, Guids.lib, and DAguid.lib files are in your computer's path, include, and lib environment, respectively. For example: SET LIB=c:\dxmedia\lib\;  Make sure that you use the danim.h which is provided with this SDK.

If you can't find Danim.h, Ddrawex.h, Guids.lib, or DAguid.lib on your computer, there are copies in the Include and Lib directories of the DirectX Media SDK. 

Go to the directory where the samples are located and run NMAKE. Note that for the C++ samples included in this SDK, the Release build is the default build.

To build DirectAnimation C++ samples in Microsoft Visual C++ 5.x, set the paths as described in Step 1, and then follow these steps: 

- Start Microsoft Visual C++ 5.x and create a new Win32 application. 
- From the Project menu, choose Settings, and then choose the Link tab. 
- Select General in the Category drop-down list. 
- Add Guids.lib and Daguid.lib to the Object/library modules text box. 
- Click OK. 
- From the Project menu, choose Add To Project, then select Files and insert the DirectAnimation C++ files into the project. 
- Press the F7 key to build. 
