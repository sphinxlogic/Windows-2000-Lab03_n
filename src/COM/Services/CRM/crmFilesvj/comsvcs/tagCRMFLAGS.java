//
// Auto-generated using JActiveX.EXE 4.79.2337
//   (jactivex /nologo /d . /e /l "comsvcs.lst" C:\WINNT\System32\comsvcs.dll)
//
// WARNING: Do not remove the comments that include "@com" directives.
// This source file must be compiled by a @com-aware compiler.
// If you are using the Microsoft Visual J++ compiler, you must use
// version 1.02.3920 or later. Previous versions will not issue an error
// but will not generate COM-enabled class files.
//

package comsvcs;

import com.ms.com.*;
import com.ms.com.IUnknown;
import com.ms.com.Variant;

// Enum: tagCRMFLAGS

public interface tagCRMFLAGS
{
  public static final int CRMFLAG_FORGETTARGET = 1;
  public static final int CRMFLAG_WRITTENDURINGPREPARE = 2;
  public static final int CRMFLAG_WRITTENDURINGCOMMIT = 4;
  public static final int CRMFLAG_WRITTENDURINGABORT = 8;
  public static final int CRMFLAG_WRITTENDURINGRECOVERY = 16;
  public static final int CRMFLAG_WRITTENDURINGREPLAY = 32;
  public static final int CRMFLAG_REPLAYINPROGRESS = 64;
}
