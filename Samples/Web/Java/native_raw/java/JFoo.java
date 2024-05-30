// Copyright (c) 1997 Microsoft Corporation.  All rights reserved.
/*******************************************************************************

	JFoo

	class which is manipulated by JMain-called natively-implemented
	methods.

*/
public class JFoo
{
	int	m_iVal ;

	JFoo()
	{
		System.out.println("JFoo() constructor without a parameter") ;
		m_iVal = 3 ;
	}

	JFoo(int iVal)
	{
		System.out.println("JFoo() constructor with a parameter") ;
		m_iVal = iVal ;
	}

	static void StaticMethod(long lVal)
	{
		System.out.println("StaticMethod(" + lVal + ")") ;
	}
}


