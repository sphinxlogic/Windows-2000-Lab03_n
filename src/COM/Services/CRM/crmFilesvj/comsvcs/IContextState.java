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

// VTable-only interface IContextState
/** @com.interface(iid=3C05E54B-A42A-11D2-AFC4-00C04F8EE1C4, thread=AUTO) */
public interface IContextState extends IUnknown
{
  /** @com.method(vtoffset=0, addFlagsVtable=4)
      @com.parameters([in,type=BOOLEAN] bDeactivate) */
  public void SetDeactivateOnReturn(boolean bDeactivate);

  /** @com.method(vtoffset=1, addFlagsVtable=4)
      @com.parameters([out,size=1,type=ARRAY] pbDeactivate) */
  public void GetDeactivateOnReturn(boolean[] pbDeactivate);

  /** @com.method(vtoffset=2, addFlagsVtable=4)
      @com.parameters([in,type=I4] txVote) */
  public void SetMyTransactionVote(int txVote);

  /** @com.method(vtoffset=3, addFlagsVtable=4)
      @com.parameters([out,type=I4] ptxVote) */
  public void GetMyTransactionVote(int ptxVote);


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x3c05e54b, (short)0xa42a, (short)0x11d2, (byte)0xaf, (byte)0xc4, (byte)0x0, (byte)0xc0, (byte)0x4f, (byte)0x8e, (byte)0xe1, (byte)0xc4);
}
