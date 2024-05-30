// Filename: MoveMoney.java
//
// Description: Declaration of MoveMoney
//
// This file is provided as part of the Microsoft Transaction Server
// Software Development Kit
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT 
// WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, 
// INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES 
// OF MERCHANTABILITY AND/OR FITNESS FOR A  PARTICULAR 
// PURPOSE.
//
// Copyright (C) 1997 Microsoft Corporation, All rights reserved

package Account;

import com.ms.mtx.*;
import com.ms.com.*;

import accountlib.*;


public class MoveMoney implements IMoveMoney {
	
	private static final String CLSID = "b790937a-e902-11d0-b5be-00c04fb957d8";

	// Perform() performs error handling for TruePerform().  If TruePerform() throws an 
	// exception, then Perform() will call SetAbort() and pass the exception up 
	// to the caller.  Otherwise, Perform() will simply call SetComplete() and return.

	public String Perform (int lngPrimeAccount, int lngSecondAccount, int lngAmount, int tranType) throws ComFailException {

		String result;
		boolean bSuccess = false;

		// First of all, get the object context
		IObjectContext ctxObject = MTx.GetObjectContext();

		try {
			// Check for security
			if ((lngAmount > 500 || lngAmount < -500) && !ctxObject.IsCallerInRole ("Managers"))
				throw new ComFailException ("Need 'Managers' role for amounts over $500");
			
			// Call the true function
			result = truePerform (lngPrimeAccount, lngSecondAccount, lngAmount, tranType);
			
			bSuccess = true;
			return result;
		}

		// Upon exit, always call SetComplete if happy, or SetAbort if unhappy.
		// We do this because we never save state across method calls.
		finally {
			if (bSuccess)
				ctxObject.SetComplete();
			else
				ctxObject.SetAbort();
		}
	}
	
	
	// TruePerform() is the function that performs the actual work for the Account class.
	// If an error occurs during execution, it will throw a ComFailException for Perform()
	// to handle.
	
	private String truePerform (int lngPrimeAccount, int lngSecondAccount, int lngAmount, int tranType)
		throws ComFailException {

		String result;
		IAccount objAccount = null;
		IGetReceipt objReceipt = null;
		
		try {
			// Create the account object
			objAccount = (IAccount) MTx.GetObjectContext().CreateInstance 
					(CAccount.clsid, IAccount.iid);

			switch (tranType)
			{
			case 1:		// debit
				result = objAccount.Post (lngPrimeAccount, (- lngAmount));
				break;

			case 2:		// credit
				result = objAccount.Post (lngPrimeAccount, lngAmount);
				break;

			case 3:		// transfer
				result = objAccount.Post (lngPrimeAccount, (- lngAmount));
				result += "    ";
				result += objAccount.Post (lngSecondAccount, lngAmount);
				break;

			default:
				throw new ComFailException ("Invalid transaction type");
			}

			// Get the receipt for the transaction
			objReceipt = (IGetReceipt) MTx.GetObjectContext().CreateInstance 
					(CGetReceipt.clsid, IGetReceipt.iid);
			int iReceiptNo = objReceipt.GetNextReceipt ();
			result += "; Receipt No:  " + iReceiptNo;

			return result;
		}

		finally {
			// The following code is not strictly necessary. By calling ComLib.release here,
			// the object counts seen in the MTX explorer remain correct. Without these release
			// calls, the objects used here would not get released until after the next time
			// the Java garbage collector runs. No other ill effect would be caused by omitting
			// this code.

			// Note that this code will be executed regardless of whether we leave this
			// method via return or via an exception.
			if (objAccount != null) ComLib.release (objAccount);
			if (objReceipt != null) ComLib.release (objReceipt);
		}
	}
}
