//
// Auto-generated using JActiveX.EXE 4.79.2228
//   (..\..\..\Bin\jactivex /javatlb /xc /d retail retail\comsamp.tlb)
//
// WARNING: Do not remove the comments that include "@com" directives.
// This source file must be compiled by a @com-aware compiler.
// If you are using the Microsoft Visual J++ compiler, you must use
// version 1.02.3920 or later. Previous versions will not issue an error
// but will not generate COM-enabled class files.
//

package comsamp;

import com.ms.com.*;
import com.ms.com.IUnknown;
import com.ms.com.Variant;

// VTable-only interface IMyInterface
/** @com.interface(iid=8EACC4B1-289A-11D1-BA1D-006008039BF0, thread=AUTO) */
public interface IMyInterface extends IUnknown
{
  /** @com.method(vtoffset=0)
      @com.parameters([in,type=STRING] filename, [out,size=1,type=ARRAY] buffer, [in,out,size=1,type=ARRAY] bufsize) */
  public void COMCheckedLoad(String filename, byte[] buffer, int[] bufsize);

  /** @com.method(vtoffset=1)
      @com.parameters([in,type=STRING] filename, [out,size=1,type=ARRAY] buffer, [in,out,size=1,type=ARRAY] bufsize) */
  public void JavaCheckedLoad(String filename, byte[] buffer, int[] bufsize);


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x8eacc4b1, (short)0x289a, (short)0x11d1, (byte)0xba, (byte)0x1d, (byte)0x0, (byte)0x60, (byte)0x8, (byte)0x3, (byte)0x9b, (byte)0xf0);
}
