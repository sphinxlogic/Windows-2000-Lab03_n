//
// Auto-generated using JActiveX.EXE 5.00.2918
//   ("D:\Program Files\Microsoft Visual Studio\VJ98\jactivex.exe" /wfc  /w /xi /X:rkc /l "D:\DOCUME~1\erica\LOCALS~1\Temp\jvc22.tmp" /nologo /d "D:\mssdk\samples\Com\Services\Transaction\SampleBank\vjacct" "D:\Program Files\Common Files\System\ado\msado15.dll")
//
// WARNING: Do not remove the comments that include "@com" directives.
// This source file must be compiled by a @com-aware compiler.
// If you are using the Microsoft Visual J++ compiler, you must use
// version 1.02.3920 or later. Previous versions will not issue an error
// but will not generate COM-enabled class files.
//

package msado15;

import com.ms.com.*;
import com.ms.com.IUnknown;
import com.ms.com.Variant;

// Enum: CommandTypeEnum

public class CommandTypeEnum extends com.ms.wfc.core.Enum
{
  public static final short adCmdUnspecified = -1;
  public static final short adCmdUnknown = 8;
  public static final short adCmdText = 1;
  public static final short adCmdTable = 2;
  public static final short adCmdStoredProc = 4;
  public static final short adCmdFile = 256;
  public static final short adCmdTableDirect = 512;
  public static final short adCmdURLBind = 1024;
}