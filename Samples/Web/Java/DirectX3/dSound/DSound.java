// 
// 
//  Copyright (C) 1997 Microsoft Corporation. All Rights Reserved.
// 
//  File: DirectSoundTest.java
// 		 
//  Description: shows use of DirectSound (via DirectSoundLIB.java).
// 
// 


import java.applet.*;
import java.awt.*;
import com.ms.com.*;
import com.ms.directX.*;
import java.net.URL;
import java.net.MalformedURLException;

                                                
//==============================================================================
// Main Class for applet DirectSoundTest
//
//==============================================================================
public class DSound extends Applet implements Runnable, DirectXConstants, IEnumSoundDriversCallback
{
    private DSoundLIB m_dsLib;
    private TextArea  m_TextArea = null;
    private DSoundFrame m_DebugFrame;
    private boolean running;

    // THREAD SUPPORT:
    //              m_DirectSoundTest       is the Thread object for the applet
    //--------------------------------------------------------------------------
    Thread   m_DirectSoundTest = null;

    //if top level exception, print a message in the window
    //--------------------------------------------------------------------------
    boolean m_topException = false;
    String m_exceptionMessage;

    // STANDALONE APPLICATION SUPPORT:
	//		m_fStandAlone will be set to true if applet is run standalone
	//--------------------------------------------------------------------------
	boolean m_fStandAlone = false;

	// STANDALONE APPLICATION SUPPORT
	// 	The main() method acts as the applet's entry point when it is run
	// as a standalone application. It is ignored if the applet is run from
	// within an HTML page.
	//--------------------------------------------------------------------------
	public static void main(String args[])
	{
		// Create Toplevel Window to contain applet DirectSoundTest
		//----------------------------------------------------------------------
		DSoundFrame frame = new DSoundFrame("DirectSound Sample");

		// Must show Frame before we size it so insets() will return valid values
		//----------------------------------------------------------------------
		frame.show();
		frame.hide();
		frame.resize(frame.insets().left + frame.insets().right  + 320,
					 frame.insets().top  + frame.insets().bottom + 240);


		// The following code starts the applet running within the frame window.
		// It also calls GetParameters() to retrieve parameter values from the
		// command line, and sets m_fStandAlone to true to prevent init() from
		// trying to get them from the HTML page.
		//----------------------------------------------------------------------
		DSound applet_directSoundTest = new DSound();

		frame.add("Center", applet_directSoundTest);

		applet_directSoundTest.m_fStandAlone = true;
		applet_directSoundTest.init();
		applet_directSoundTest.start();
		frame.show();
	}

   //------------------------------------------------

   private void DebugMsg (String s)
   {
      String ss;

      ss = "DirectSoundTest " + s;
      System.out.println (ss);
      if (m_TextArea != null)
         m_TextArea.appendText (ss + "\n");
      
      // this will make those pesky numbers update to show it's 
      // still alive...
      repaint();
   }

	// DirectSoundTest Class Constructor
	//--------------------------------------------------------------------------
	public DSound()
	{
	}

	// APPLET INFO SUPPORT:
	//		The getAppletInfo() method returns a string describing the applet's
	// author, copyright date, or miscellaneous information.
        //--------------------------------------------------------------------------
	public String getAppletInfo()
	{
		return "Name: DirectSoundTest\r\n" +
		       "Author: Microsoft\r\n" +
		       "Created with Microsoft Visual J++ Version 1.0";
	}

        //--------------------------

	public String GetFullFileName (String rawFileName)
	{
		String file;

		try
		{
			URL url = new URL( getDocumentBase(), rawFileName);

			file = url.getFile();
			char c0 = file.charAt(0);
			char c2 = file.charAt(2);
			if( (c0 == '/') && (c2 == ':') )
			{
				char ch[] = new char[file.length()-1];
				file.getChars(1,file.length(),ch,0);
				file = new String(ch);
			}
		}
		catch(MalformedURLException me)
		{
         DebugMsg ("GetFullFileName caught exception \n   " + me);
			file = new String (rawFileName);
		}
      catch (Exception e)
      {
         DebugMsg ("GetFullFileName caught exception \n   " + e);
			file = new String (rawFileName);
		}

		return file;
	}

	//--------------------------------

        public void CreateDebugWindow (int nWidth, int nHeight)
        {

      m_DebugFrame = new DSoundFrame ("DirectSoundTest Msgs");
      m_DebugFrame.resize (nWidth, nHeight);

      m_TextArea = new TextArea (nWidth, nHeight);
      m_DebugFrame.add ("Center", m_TextArea);
      m_DebugFrame.show();
   }

   // The init() method is called by the AWT when an applet is first loaded or
	// reloaded.  Override this method to perform whatever initialization your
	// applet needs, such as initializing data structures, loading images or
	// fonts, creating frame windows, setting the layout manager, or adding UI
	// components.
   //--------------------------------------------------------------------------
	public void init()
	{
      resize (320, 240);
      
//      if (m_fStandAlone)
//         CreateDebugWindow (300, 400);

      try
      {
         m_dsLib = new DSoundLIB (this, DSSCL_NORMAL);
      }
      catch (Exception e)
      {
         m_topException = true;
         m_exceptionMessage = e.getMessage();
         ErrorExit ("m_dsLib exception \n" + e, 1);
         return;
      }

      String sFile = new String ("walk.wav");   
      
      // 
      // URL throws an exception when we try to get document base if
      // we're not running from a browser (ie. JVIEW DirectSoundTest).  
      // Otherwise we need to find the path to the wave file.
      if (! m_fStandAlone)
         sFile = GetFullFileName (sFile);

      if (! m_dsLib.PlayWave (sFile, true))
         ErrorExit ("Can't play wave file [" + sFile + "]", 3);
	}
   
   //--------------------------------------------------------------------------

   public void ErrorExit (String s, int nExitValue)
   {
      DebugMsg ("FatalError: [" + s + "]");
		if(m_fStandAlone)
         System.exit (nExitValue);
   }

   // Place additional applet clean up code here.  destroy() is called when
	// when you applet is terminating and being unloaded.
	//-------------------------------------------------------------------------
	public void destroy()
	{
	}

	// DirectSoundTest Paint Handler
	//--------------------------------------------------------------------------
	public void paint(Graphics g)
	{
		if (! m_fStandAlone)
		{
			g.drawString("For debug output, see ", 10, 20);
	        g.drawString("<windows dir>\\java\\JavaLog.txt..." , 10, 40);
		}

        if(m_topException)
        {
            g.drawString(m_exceptionMessage, 10, 100);
        }
        else
        {
		    g.drawString("Note: this window needs focus in ", 10, 100);
		    g.drawString("     order to hear the sound.", 10, 120);
		    g.drawString("Running (sound should be playing): " + Math.random(), 10, 140);
        }
	}

	//		The start() method is called when the page containing the applet
	// first appears on the screen. The AppletWizard's initial implementation
	// of this method starts execution of the applet's thread.
	//--------------------------------------------------------------------------
	public void start()
	{
		running = true;
		m_DirectSoundTest = new Thread(this);
		m_DirectSoundTest.start();
	}
	
	//		The stop() method is called when the page containing the applet is
	// no longer on the screen. The AppletWizard's initial implementation of
	// this method stops execution of the applet's thread.
	//--------------------------------------------------------------------------
	public void stop()
	{
		m_dsLib.StopWave();
		running = false;
		if (m_DirectSoundTest != null)
			m_DirectSoundTest.stop();
	}

	// THREAD SUPPORT
	//		The run() method is called when the applet's thread is started. If
	// your applet performs any ongoing activities without waiting for user
	// input, the code for implementing that behavior typically goes here. For
	// example, for an applet that performs animation, the run() method controls
	// the display of images.
	//--------------------------------------------------------------------------
	public void run()
	{
      // Test some basic DirectSound api's...
      // 
      // Note, if you just wanted to play a wave file, all you'd need is the
      //       code in the Init()...
      TestDirectSoundMethods();
      DebugMsg (" ");
      TestDirectSoundBufferMethods();
      
      while (running)
		{
         try
			{
				repaint();
				m_DirectSoundTest.sleep(50);
			}
			catch (InterruptedException e)
			{
				stop();
			}
		}
	}

   //---------------------------------------

   public void callbackEnumSoundDrivers(_Guid g, String Description, 
                              String mod, IUnknown lpContext)
   {
      DebugMsg ("   EnumSoundDrivers: [" + Description + ", " + mod + "]");
   }

   //---------------------------------------

   public void TestDirectSoundMethods()
      // 
      // call some DirectSound api's to make sure things are working...
   {
		DirectSound ds;

      DebugMsg ("TestDirectSoundMethods =================");
      try
      {
         // Get the initialized DirectSound object from the library
         ds = m_dsLib.GetDirectSoundObject();

         
         // Enumerate devices on system
         DebugMsg ("TEST: EnumSoundDrivers...");
		 try{
         ds.enumSoundDrivers ((IEnumSoundDriversCallback)this, (IUnknown)null);
		 }
		 catch (Exception e)
		 {
			String s = e.toString();
			System.out.println(s);
		 }

         // TEST  compact the sound card memory 
         DebugMsg ("TEST: Compact()");
         ds.setCooperativeLevel (this, DSSCL_EXCLUSIVE);
         ds.compact();
         ds.setCooperativeLevel (this, DSSCL_NORMAL);

         // TEST  speaker config
         DebugMsg ("TEST: Get/SetSpeakerConfig()");
         int nSpeakerConfig[] = new int [1];
         ds.setSpeakerConfig (DSSPEAKER_HEADPHONE);
         ds.getSpeakerConfig (nSpeakerConfig);
         if (nSpeakerConfig[0] != DSSPEAKER_HEADPHONE)
            DebugMsg ("Get/Set speaker config failed");

         
         // TEST GetCaps()
         DebugMsg ("TEST: GetCaps()");
         DSCaps dsCaps = new DSCaps();
         ds.getCaps (dsCaps);
         DebugMsg ("   dsCaps.freeHwMemBytes         = " + dsCaps.freeHwMemBytes);
         DebugMsg ("   dsCaps.freeHwMixingAllBuffers = " + dsCaps.freeHwMixingAllBuffers);
         DebugMsg ("   dsCaps.primaryBuffers         = " + dsCaps.primaryBuffers);
      }
      catch (Exception e)
      {
         DebugMsg ("TestDirectSoundMethods, caught exception \n " + e);
		 e.printStackTrace();
         stop();
      }
   }

   //---------------------------------------

   public void TestDirectSoundBufferMethods()
      // 
      // * call some DirectSound api's to make sure things are working...
      // * assumes there's a wave file playing on LOOP mode.
      // 
   {
      DebugMsg ("TestDirectSoundBufferMethods =================");
      try
      {
         // Get the initialized DirectSound objects from the library
         DirectSoundBuffer dsBuffer = m_dsLib.GetDirectSoundBufferObject();
         DirectSound       ds       = m_dsLib.GetDirectSoundObject();
   
         // TEST GetCaps()
         DebugMsg ("TEST: GetCaps()");
         DSBCaps dsbCaps = new DSBCaps();
         dsBuffer.getCaps (dsbCaps);
         DebugMsg ("   dsbCaps.bufferBytes        = " + dsbCaps.bufferBytes);
         DebugMsg ("   dsbCaps.unlockTransferRate = " + dsbCaps.unlockTransferRate);
         DebugMsg ("   dsbCaps.playCpuOverhead    = " + dsbCaps.playCpuOverhead );

         // TEST GetCurrentPosition()
         DebugMsg ("TEST: GetCurrentPosition()");
         DSCursors dsCursors = new DSCursors();

         dsBuffer.getCurrentPosition (dsCursors);
         DebugMsg ("   dsCursors.play  = " + dsCursors.play);
         DebugMsg ("   dsCursors.write = " + dsCursors.write);


         // TEST GetFormatSize()
         DebugMsg ("TEST: GetFormatSize()");
         int nSize;
         nSize = dsBuffer.getFormatSize ();
         DebugMsg ("   GetFormatSize = " + nSize);


         // TEST GetFormat()
         // note: GetFormat() returns a new WaveFormatEx(); 
         DebugMsg ("TEST: GetFormat()");
         WaveFormatEx waveForm;  
         
         waveForm = dsBuffer.getFormat();
         DebugMsg ("   waveForm.channels      = " + waveForm.channels);
         DebugMsg ("   waveForm.bitsPerSample = " + waveForm.bitsPerSample);
         DebugMsg ("   waveForm.samplesPerSec = " + waveForm.samplesPerSec);


         // let users get used to current volume level              
         Wait (5);      

         // TEST GetVolume()
         DebugMsg ("TEST: GetVolume()");
         int nTemp = 10;
         nTemp = dsBuffer.getVolume();
         DebugMsg ("TEST: GetVolume() = " + nTemp);
         

         // Test SetVolume()
         DebugMsg ("   Setting volume to 1/2");

         // NOTE: units are in hundreths of decibels 
         dsBuffer.setVolume (nTemp - 1000);   
         Wait (6);
         DebugMsg ("   Restoring volume to original level");
         dsBuffer.setVolume (nTemp);

         // Test GetPan()
         DebugMsg ("TEST: GetPan()");
         nTemp = dsBuffer.getPan();
         DebugMsg ("TEST: GetPan() = " + nTemp);

         // Test SetPan()
         DebugMsg ("   Setting pan from LEFT to RIGHT....");
         for (int nPan = -10000; nPan < 10000; nPan += 1000)
         {
            dsBuffer.setPan (nPan);
            Wait (1);
         }
         
         DebugMsg ("   Restoring original pan setting.... " + nTemp);
         dsBuffer.setPan (nTemp);


         // Test GetFrequency()
         DebugMsg ("TEST: GetFrequency()");
         nTemp = dsBuffer.getFrequency();
         DebugMsg ("TEST: GetFrequency() = " + nTemp);

         // Test SetFrequency(); note upper limit is 100000
         DebugMsg ("   Setting Frequency from 100 to 50000....");
         for (int nFreq = 100; nFreq < 50000; nFreq += 3000)
         {
            dsBuffer.setFrequency (nFreq);
            Wait (2);
         }
         
         DebugMsg ("   Restoring original frequency setting.... " + nTemp);
         dsBuffer.setFrequency (nTemp);


         // Test: GetStatus
         nTemp = dsBuffer.getStatus();
         DebugMsg ("TEST: GetStatus() = " + nTemp);


         // Test: Stop
         DebugMsg ("TEST: Stop()");
         m_dsLib.StopWave();
         DebugMsg ("   wave playback is stopped now...");


         // Test: SetCurrentPosition.  Wave buffer positions are 0 to maxBufferSize
         DebugMsg ("TEST: SetCurrentPosition()");
         int nBufferSize = m_dsLib.GetBufferSize();
         DebugMsg ("   BufferSize = " + nBufferSize);
         
         // 
         // play the wave file starting from different positions within
         // the wave file.
         int nPos;
         for (int n = 0; n < 4; n++)
         {
            nPos = (int)((double)nBufferSize * Math.random());
            DebugMsg ("   Setting current position to: " + nPos);
            dsBuffer.setCurrentPosition (nPos);
            m_dsLib.PlayWave (0);
            while (dsBuffer.getStatus() == DSBSTATUS_PLAYING)
               ;

            Wait (3);
         }


         Wait (2);
         m_dsLib.PlayWave (DSBPLAY_LOOPING);
         DebugMsg ("Normal wave playback has resumed now, \n   end of test...");
      }
      catch (Exception e)
      {
         DebugMsg ("TestDirectSoundBufferMethods, caught exception \n " + e);
         stop();
      }
   }

   //--------------------------------------------------

   public void Wait(int nLoopCounter)
   {
      try
      {
         Thread.sleep (nLoopCounter * 500);
      }
      catch (InterruptedException e)
      {
         DebugMsg ("Wait: caught exception \n   " + e);
      }
   }
}
