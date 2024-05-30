// Copyright (c) 1996-1997 Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////
//
//	JThread2
//
//	thread runs on this to demonstrate GC-awareness in native code.
//
////

public class JThread2 implements Runnable
{
	int	m_hEvent ;

	////////////////////////////////////////////////////////////////////////
	//
	//	JThread2()
	//
	//	constructor; sets our handle to the event object, which will
	//	be used for synchronization in native code.
	//
	////
	JThread2(int hEvent)
	{
		m_hEvent = hEvent ;
	}

	////////////////////////////////////////////////////////////////////////
	//
	//	natively implemented methods (see ..\native\natlib.c for
	//	details)
	//
	//		GCSafeNative()
	//		w32CloseHandle()
	//
	////
	public native void GCSafeNative(int hEvent) ;
	public native int w32CloseHandle(int hObject) ;

	////////////////////////////////////////////////////////////////////////
	//
	//	Thread runs on this method; show banners to display progress
	//
	////
	public synchronized void run()
	{
		System.out.println("JThread2 calling GCSafeNative()") ;

		// call out to native code
		GCSafeNative(m_hEvent) ;

		// in this case, we know we're the last to use hEvent, so
		//  we close it prior to exit.
		w32CloseHandle(m_hEvent) ;

		System.out.println("JThread2 completing") ;
	}
}

