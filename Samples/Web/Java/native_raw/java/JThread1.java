// Copyright (c) 1996-1997 Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////
//
//	JThread1
//
//	runs with JThread2;  this can be considered the master thread i.e.
//	JThread2 will block on this thread, until we pulse the passed event
//	sync object.
//
////
public class JThread1 implements Runnable
{
	int	m_SleepMillis ;
	int	m_hEvent ;

	////////////////////////////////////////////////////////////////////////
	//
	//	JThread1()
	//
	//	constructor; sets our event sync object and the time to sleep
	//	prior to pulsing the object.
	//
	////
	JThread1(int iSleepMillis, int hEvent)
	{
		m_SleepMillis = iSleepMillis ;
		m_hEvent = hEvent ;
	}

	////////////////////////////////////////////////////////////////////////
	//
	//	natively implemented method (see ..\native\natlib.c for
	//	details)
	//
	//		w32PulseEvent()
	//
	////
	public native void w32PulseEvent(int hEvent) ;

	////////////////////////////////////////////////////////////////////////
	//
	//	run()
	//
	//	thread runs on this method; we sleep for specified time then
	//	pulse the event object (resuming JThread2 object); banners
	//	display progress.
	//
	////
	public synchronized void run()
	{
		// sleep
		try { Thread.sleep(m_SleepMillis) ; }
		catch (Exception e)
		{
			e.printStackTrace() ;
		}

		System.out.println("JThread1: calling w32PulseEvent()") ;

		// pulse the object
		w32PulseEvent(m_hEvent) ;

		System.out.println("JThread1 completing") ;
	}
}

