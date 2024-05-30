// 
// 
//  Copyright (C) 1997 Microsoft Corporation. All Rights Reserved.
// 
//  File: DirectSoundLIB.java
// 		 
//  Description: Class does basic play, stop of wav files. 
//               See DirectSoundTest.java for sample usage...   
// 
import java.awt.*;
import com.ms.com.*;
import com.ms.directX.*;

class DSoundLIB implements DirectXConstants
{
   // hidden class variablez
   private DirectSound			ds;
   private DirectSoundBuffer	m_dsBuffer;
   private DSBufferDesc			m_dsBufferDesc = null;
   private DSResourceDesc		m_dsrDesc;

   private boolean				m_bSoundLoaded;
   private WaveFormatEx			m_waveFormat;
   private DirectSoundResource	m_dsr;
   private int					m_PlayLoopFlag;

   protected void finalize()
   {
		ComLib.release(m_dsBuffer);
		ComLib.release(ds);
   }

   //---------------------------------------
   //---------------------------------------

   private void DebugMsg (String s)
   {
      System.out.println ("DirectSoundLIB: " + s);
   }

   //---------------------------------------
   
   public DirectSound GetDirectSoundObject()
   {
      return ds;
   }

   //---------------------------------------
   
   public DirectSoundResource GetDirectSoundResourceObject()
   {
      return m_dsr;
   }

   //---------------------------------------
   
   public DirectSoundBuffer GetDirectSoundBufferObject()
   {
      return m_dsBuffer;
   }
   
   //---------------------------------------
   
   public int GetBufferSize()
   {
      return m_dsBufferDesc.bufferBytes;
   }
   
   //---------------------------------------

   public DSoundLIB (Component c, int nLevel) throws Exception
   {
      m_bSoundLoaded = false;
      
      try 
      {
         DebugMsg ("Calling new DirectSound()....");
         DebugMsg ("   Note: If your app stops here, you need to register DX3J.DLL");
         ds = new DirectSound();

         // note: if there is no sound device available, this will throw an 
         // exception.
         DebugMsg ("Calling SetCooperativeLevel " + nLevel);
         DebugMsg ("   Note: If your app stops here, you don't have a sound device");
         try
         {
            ds.setCooperativeLevel (c, nLevel);
         }
         catch (Exception e)
         {
            throw new Exception ("No Sound Card: SetCooperativeLevel() failed");
         }
      }
      catch (Exception e)
      {
         DebugMsg ("Constructor caught exception \n   " + e);
         throw new Exception ("DSLIB: " + e);
      }                            
      
      DebugMsg ("Constructor finished");
   }

   //---------------------------------------

   public boolean PlayWave (String sFilename, boolean bLoop)
   {
      DebugMsg ("PlayWave [" + sFilename + "]");
      if (! LoadWaveFile (sFilename))
         return false;

      // save the play flag for use w/ StopWave() below
      if (bLoop)
         m_PlayLoopFlag = DSBPLAY_LOOPING;
      else
         m_PlayLoopFlag = 0;

      try 
      {
         m_dsBuffer.play (m_PlayLoopFlag);
      }
      catch (Exception e)
      {
         DebugMsg ("DirectSoundBuffer::Play() threw Exception \n" + e);
         return false;
      }

      return true;
   }

   //---------------------------------------
   
   public boolean PlayWave ()
      // 
      // this one restarts a wave file previously stopped with StopWave()
      // 
   {
      try 
      {
         m_dsBuffer.play (m_PlayLoopFlag);
      }
      catch (Exception e)
      {
         DebugMsg ("DirectSoundBuffer::Play() threw Exception \n" + e);
         return false;
      }

      return true;
   }
   
   //---------------------------------------
   
   public boolean PlayWave (int nFlag)
      // 
      // this one plays a wave file with the nFlag play parameter.
      // 
   {
      try 
      {
         m_dsBuffer.play (nFlag);
      }
      catch (Exception e)
      {
         DebugMsg ("DirectSoundBuffer::Play() threw Exception \n" + e);
         return false;
      }

      return true;
   }
   
   //---------------------------------------
   
   public boolean StopWave()
   {
      try
      {
         m_dsBuffer.stop();
      }
      catch (Exception e)
      {
         DebugMsg ("DirectSoundBuffer::Stop() threw Exception \n" + e);
         return false;
      }

      return true;
   }
   
   //---------------------------------------
   
   public boolean LoadWaveFile (String sFilename)

   {
      DebugMsg ("LoadWaveFile ============");

      try 
      {
         m_dsrDesc    = new DSResourceDesc();
         m_dsr        = new DirectSoundResource();
         
         // this guy returns us the size of the wave file in 
         // dwBufferBytes
         m_waveFormat = m_dsr.loadWaveFile (sFilename, m_dsrDesc);

         // create the sound buffer
         m_dsBufferDesc                = new DSBufferDesc();

         // need to specify DSBCAPS_CTRLDEFAULT so you can control the
         //    volume, pan, frequency.
         m_dsBufferDesc.flags        = DSBCAPS_STATIC | DSBCAPS_CTRLDEFAULT;
         m_dsBufferDesc.bufferBytes  = m_dsrDesc.bufferBytes;

         m_dsBuffer = ds.createSoundBuffer (m_dsBufferDesc, m_waveFormat);
   
         // get the sound data from the internal memory from LoadWaveFile
         //  to the sound buffer.  The flags are the same as those used 
         //  for Lock()
         m_dsBuffer.transferToSoundBuffer (m_dsrDesc, 0);
         
         return m_bSoundLoaded = true;
      }
      catch (Exception e)
      {
         DebugMsg ("LoadWaveFile caught exception \n   " + e);
         return false;
      }
   }
}
