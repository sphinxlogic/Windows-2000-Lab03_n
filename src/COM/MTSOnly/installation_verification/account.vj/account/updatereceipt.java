// Filename: UpdateReceipt.java
//
// Description: Declaration of UpdateReceipt
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
import msado15.*;

import accountlib.*;


public class UpdateReceipt implements IUpdateReceipt {
	
	public static final String CLSID = "c25e3b4a-e902-11d0-b5be-00c04fb957d8";

	// Update() performs error handling for TrueUpdate().  If TrueUpdate() throws an 
	// exception, then Update() will call SetAbort() and pass the exception up 
	// to the caller.  Otherwise, Update() will simply call SetComplete() and return.

	public int Update () throws ComFailException {

		int result;
		boolean bSuccess = false;

		// First of all, get the object context
		IObjectContext ctxObject = MTx.GetObjectContext();

		try {
			// Call the true function
			result = trueUpdate ();

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


	// trueUpdate() is the function that performs the actual work for the Account class.
	// If an error occurs during execution, it will throw a ComFailException for Update()
	// to handle.
	private int trueUpdate () throws ComFailException {
		
		_Connection adoConn = null;
		_Recordset adoRsReceipt = null;
		Field pField = null;
		Fields pFields = null;

		try {
			// Create ADOConnection object and initialize the connection
			adoConn = (_Connection) new Connection();
			String vDSN = "FILEDSN=MTSSamples";
			adoConn.Open (vDSN, null, null, CommandTypeEnum.adCmdUnspecified);
			
			// Obtain the desired recordset with an SQL query
			Variant	vAdoNull = new Variant();

			String strSQL = "Update Receipt set NextReceipt = NextReceipt + 100";
			adoConn.Execute (strSQL, vAdoNull, - 1);

			strSQL = "Select NextReceipt from Receipt";
			adoRsReceipt = adoConn.Execute (strSQL, vAdoNull, - 1);
			
			// Get the appropriate fields
			pFields = adoRsReceipt.getFields();
			
			// Get the appropriate field
			Variant vField = new Variant();
			Variant lngNextReceipt = new Variant();
			vField.putString ("NextReceipt");
			
			pField = pFields.getItem(vField);
			lngNextReceipt = pField.getValue();
			
			return lngNextReceipt.getInt();
		}

		finally {
			// cleanup that needs to occur whether we leave via a return or an exception.
			if (adoRsReceipt != null) {
				if (adoRsReceipt.getState() == ObjectStateEnum.adStateOpen)
					adoRsReceipt.Close();
				ComLib.release (adoRsReceipt);
			}

			if (adoConn != null) {
				if (adoConn.getState() == ObjectStateEnum.adStateOpen)
					adoConn.Close();
				ComLib.release (adoConn);
			}
		}
	}
}
