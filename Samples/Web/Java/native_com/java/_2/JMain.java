//============================================================================//
// Copyright (c) 1996-1997 Microsoft Corporation.
// All rights reserved.

package java._2 ;

import tlb.jnatcom.jCNatComImpl;


//============================================================================//
//JMain - implements jcNatComImpl interface as a COM-callable wrapper (CCW).

class JMain extends jCNatComImpl
{
	
  public void ccwHelloWorld()
	{ System.out.println("invoked from COM: Hello World");
	}

	public void HelloWorld()
	{ System.out.println("invoked from Java: Hello World");
	}
}


//============================================================================//
