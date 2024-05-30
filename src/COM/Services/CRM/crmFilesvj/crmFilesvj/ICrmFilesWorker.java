package crmfilesvj;

/*+==========================================================================
File: crmfilesvj.ICrmFilesWorker.java

Summary: 
	This is a sample Compensating Resource Manager (CRM) that creates and 
	deletes files. The CRM Worker provides an interface for creating or 
	deleting files.The CRM Compensator implements ICrmCompensator to receive 
	transaction outcome notifications. The CRM Compensator also implements 
	ICrmFormatLogRecords to support monitoring.

	This CRM can be installed in a server application or in a library
	application. The CRM Worker requires a transaction. The CRM Compensator
	should not have a transaction.

----------------------------------------------------------------------------

This file is part of the Microsoft COM+ Samples.

Copyright (C) 1995-1998 Microsoft Corporation. All rights reserved.

This source code is intended only as a supplement to Microsoft
Development Tools and/or on-line documentation. See these other
materials for detailed information regarding Microsoft code samples.

THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

==========================================================================+*/


//
// Auto-generated using JActiveX.EXE 5.00.3167.1
//   ("C:\Program Files\Microsoft Visual Studio\VJ98\jactivex.exe" /javatlb /c2j /creg /b+ /xh  /w /xi /X:rkc /l "C:\DOCUME~1\Davidno\LOCALS~1\Temp\jvc1D3.tmp" /nologo /d "P:\COMPlus\SDK\samples\com\Services\CRM" "\\DAVIDNO-1\Visual Studio Projects\COMPlus\SDK\samples\com\Services\CRM\CrmFilesVJ\CrmFilesVJ.tlb")
//
// WARNING: Do not remove the comments that include "@com" directives.
// This source file must be compiled by a @com-aware compiler.
// If you are using the Microsoft Visual J++ compiler, you must use
// version 1.02.3920 or later. Previous versions will not issue an error
// but will not generate COM-enabled class files.
//

import com.ms.com.*;


//	Dual interface ICrmFilesWorker

/** @com.interface(
 *		iid=43A7D836-B492-11D1-82F1-00A0C91EEDE9, 
 *		thread=AUTO, 
 *		type=DUAL
 * ) */

public interface ICrmFilesWorker extends IUnknown
{
  /** @com.method(vtoffset=4, dispid=1610743808, type=METHOD, name="CreateFile", addFlagsVtable=4)
      @com.parameters([in,type=STRING] bstrFileName) */
  public void CreateFile(String bstrFileName);

  /** @com.method(vtoffset=5, dispid=1610743809, type=METHOD, name="DeleteFile", addFlagsVtable=4)
      @com.parameters([in,type=STRING] bstrFileName) */
  public void DeleteFile(String bstrFileName);


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x43a7d836, (short)0xb492, (short)0x11d1, (byte)0x82, (byte)0xf1, (byte)0x0, (byte)0xa0, (byte)0xc9, (byte)0x1e, (byte)0xed, (byte)0xe9);
}
