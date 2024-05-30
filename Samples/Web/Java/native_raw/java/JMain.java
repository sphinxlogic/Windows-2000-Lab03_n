// Copyright (c) 1996-1997 Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////
//
//	JMain
//
//	main class; calls out to natively-implemented methods to perform
//	various operations.
//
////
public class JMain
{
	// VARIABLES -----------------------------------------------------------

	public int iVar1 = 5 ;
	private int[] iCVar2 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 } ;


	////////////////////////////////////////////////////////////////////////
	//
	//	JMain()
	//
	//	constructor; loads our dll which implements native methods.
	//
	////
	JMain()
	{
		System.loadLibrary("natlib") ;
	}

	////////////////////////////////////////////////////////////////////////
	//
	//	GetiCVar2()
	//
	//	returns (private) array of ints iCVar2.
	//
	////
	public int[] GetiCVar2()
	{
		return iCVar2 ;
	}

	////////////////////////////////////////////////////////////////////////
	//
	//	GetiVar1()
	//
	//	returns value of instance variable iVar1.
	//
	////
	public int GetiVar1()
	{
		return iVar1 ;
	}

	////////////////////////////////////////////////////////////////////////
	//
	//	GCUsage()
	//
	//	spawn two threads: JThread1 and JThread2.  JThread2 will block
	//	in native code on JThread1, which will pulse an event object
	//	after it sleeps for the given time.
	//
	////
	public void GCUsage()
	{
		int	hEvent = w32CreateEvent(0) ;

		if (hEvent != 0)
		{
			new Thread(new JThread1(1000, hEvent)).start() ;
			new Thread(new JThread2(hEvent)).start() ;
		}
	}

	////////////////////////////////////////////////////////////////////////
	//
	//	natively-implemented methods
	//
	//	see ..\native\natlib.c for specifics of each method.
	//
	////
	public native int Square(int iVar) ;
	public native void DoubleInstanceVar() ;
	public native void showMemberArray() ;
	public native void Various() ;
	public native int w32CreateEvent(int iInitState) ;

	////////////////////////////////////////////////////////////////////////
	//
	//	main()
	//
	//	entry point;  executes various methods (implemented in java
	//	and natively) for demonstration purposes.
	//
	////
	public static void main(String argv[])
	{
		// instantiate our class
		JMain jm = new JMain() ;

		// and demonstrate use of native methods
		System.out.println("Square(" + jm.iVar1 + ") = " + jm.Square(jm.iVar1)) ;
		System.out.println("iVar1 before = " + jm.iVar1) ;
		System.out.println("calling DoubleInstanceVar()") ;
		jm.DoubleInstanceVar() ;
		System.out.println("iVar1 after = " + jm.iVar1) ;
		jm.showMemberArray() ;
		jm.Various() ;
		jm.GCUsage() ;
	}
}
