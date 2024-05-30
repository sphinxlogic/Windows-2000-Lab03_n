
/*
Copyright (c) 1996-1997  Microsoft Corporation.  All rights reserved.
*/

package java._1 ;

import tlb.natcom.INatCom ;
import tlb.natcom.CNatCom ;
import tlb.jnatcom.jINatCom ;

////////////////////////////////////////////////////////////////////////////////
//
//	JMain
//
//	main object to demonstrate implementation of Java-Callable Wrappers (JCWs),
//	and COM-Callable Wrappers (CCWs).
//
//	We execute this object with jview.exe.  The constructor "news" a JCW.
//	Once we have it, we call down into COM via various methods.  One method
//	returns a CCW to us, which was created by COM.  We call methods on this
//	CCW (implemented in java, in java._2 package).
//
////
public class JMain
{
	private INatCom inc ;
	private jINatCom jInc ;
	private int[] iaVar = { 5 } ;

	////////////////////////////////////////////////////////////////////////
	//
	//	Jmain()
	//
	//	constructor; creates our JCW.  If an exception is thrown (i.e.
	//	COM call failed) we print out any message that may have come
	//	with it, along with a stack trace.
	//
	////
	JMain()
	{
		try
		{
			// 1. new CNatCom() is equivalent to CoCreateInstance() call
			// 2. casting to INatCom is equivalent to QueryInterface()
			inc = (INatCom) (new CNatCom()) ;
		}
		catch (Exception e)
		{
			// message + stack trace
			System.out.println("Exception thrown during new") ;
			System.out.println(e.getMessage()) ;
			e.printStackTrace() ;
		}
	}

	////////////////////////////////////////////////////////////////////////
	//
	//	ExerciseJCW()
	//
	//	method which demonstrates method calls on the JCW; we bracket
	//	the calls in try/catch clauses in case a call fails in COM.
	//
	////
	public void ExerciseJCW()
	{
		try
		{
			// multiply the two values and display the result
			System.out.print("2 * " + iaVar[0] + " = ") ;
			inc.MultParam(2, iaVar) ;
			System.out.println(iaVar[0]) ;

			// squares and displays the value
			System.out.println("inc.Square(10) = " + inc.Square(10)) ;

			// GetClass() returns a CCW i.e. we could have obtained
			//  this via a new call in Java;  instead we demonstrate
			//  how COM performs this operation and then use the
			//  object in both COM and Java.
			jInc = inc.GetClass() ;
			jInc.HelloWorld() ;		// call a method on the CCW
		}
		catch (Exception e)
		{
			// message and stack trace in case we throw an exception
			System.out.println("Exception thrown while exercising methods") ;
			System.out.println(e.getMessage()) ;
			e.printStackTrace() ;
		}
	}

	////////////////////////////////////////////////////////////////////////
	//
	//	main()
	//
	//	entry point
	//
	////
	public static void main(String argv[])
	{
		JMain jm = new JMain() ;
		jm.ExerciseJCW() ;
	}
}
