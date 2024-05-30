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

// VTable-only interface ITransaction
/** @com.interface(iid=0FB15084-AF41-11CE-BD2B-204C4F4F5020, thread=AUTO) */
public interface ITransaction extends IUnknown
{
  /** @com.method(vtoffset=0, addFlagsVtable=4)
      @com.parameters([in,type=I4] fRetaining, [in,type=U4] grfTC, [in,type=U4] grfRM) */
  public void Commit(int fRetaining, int grfTC, int grfRM);

  /** @com.method(vtoffset=1, addFlagsVtable=4)
      @com.parameters([in,type=PTR] pboidReason, [in,type=I4] fRetaining, [in,type=I4] fAsync) */
  public void Abort(comsvcs.BOID pboidReason, int fRetaining, int fAsync);

  /** @com.method(vtoffset=2, addFlagsVtable=4)
      @com.parameters([out,type=PTR] pinfo) */
  public void GetTransactionInfo(comsvcs.XACTTRANSINFO pinfo);


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0xfb15084, (short)0xaf41, (short)0x11ce, (byte)0xbd, (byte)0x2b, (byte)0x20, (byte)0x4c, (byte)0x4f, (byte)0x4f, (byte)0x50, (byte)0x20);
}
