//
// Auto-generated using JCOM.EXE 4.79.2035
//   (C:\SDK-JAVA.20\BIN\JCOM.EXE simpleobject.dll)
//
// WARNING: Do not remove the comments that include "@com" directives.
// This source file must be compiled by a @com-aware compiler.
// If you are using the Microsoft Visual J++ compiler, you must use
// version 1.02.3920 or later. Previous versions will not issue an error
// but will not generate COM-enabled class files.
//

package simpleobject;

import com.ms.com.*;
import com.ms.com.IUnknown;
import com.ms.com.Variant;

// Dual interface _SimpleObject
/** @com.interface(iid=B2CD9D14-BD00-11D0-B5B3-00A0C913D22B, thread=AUTO, type=DUAL) */
public interface _SimpleObject extends IUnknown
{
  /** @com.method(vtoffset=4, dispid=1610809344, type=METHOD, name="ComputeSum")
      @com.parameters([in,out,vt=16387,type=SAFEARRAY] A, [type=VARIANT] return) */
  public Variant ComputeSum(com.ms.com.SafeArray A);

  /** @com.method(vtoffset=5, dispid=1610809345, type=METHOD, name="CreateSquares")
      @com.parameters([type=VARIANT] return) */
  public Variant CreateSquares();


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0xb2cd9d14, (short)0xbd00, (short)0x11d0, (byte)0xb5, (byte)0xb3, (byte)0x0, (byte)0xa0, (byte)0xc9, (byte)0x13, (byte)0xd2, (byte)0x2b);
}