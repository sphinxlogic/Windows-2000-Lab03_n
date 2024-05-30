//--------------------------------------------------
// CONFDSN: trivial configure DSN for the trival
//            sample driver.
//
// Copyright (c) 1997 - 1998 by Microsoft Corporation.
//--------------------------------------------------
// This doesn't do anything interesting, the sample
// driver is really for testing the setup sample
//--------------------------------------------------

#include <windows.h>
#include <odbcinst.h>

BOOL INSTAPI ConfigDSN(HWND		hWnd,
			   WORD		fRequest,
			   LPCSTR	lpszDriver,
			   LPCSTR	lpszAttributes)
{
	switch (fRequest)
	{
		case ODBC_CONFIG_DSN:
		{
			MessageBox(hWnd,
						"This is a useless data source for the sample driver",
					    lpszDriver,
						MB_OK);
			break;
						
		}
		case ODBC_ADD_DSN:
		{

			// Normally here is where you would have some nice UI to select
			// a driver name and driver-specific options.   

			if ((hWnd == NULL) || (MessageBox(hWnd,
						   "Do you want to add a data source named 'Useless'?",
							lpszDriver,
							MB_YESNO) ==  IDYES))
			{
				SQLWriteDSNToIni("Useless",lpszDriver);
				
			}
			break;
		}
		case ODBC_REMOVE_DSN:
		{
			if ((hWnd == NULL) || (MessageBox(hWnd,
						   "Do you want to remove data source 'Useless'?",
							lpszDriver,
							MB_YESNO) ==  IDYES))
			{
				SQLRemoveDSNFromIni("Useless");
			}
		}
	}

	return TRUE;
}
