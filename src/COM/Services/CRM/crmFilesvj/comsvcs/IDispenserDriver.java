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

// VTable-only interface IDispenserDriver
/** @com.interface(iid=208B3651-2B48-11CF-BE10-00AA00A2FA25, thread=AUTO) */
public interface IDispenserDriver extends IUnknown
{
  /** @com.method(vtoffset=0, addFlagsVtable=4)
      @com.parameters([in,type=U4] ResTypId, [out,size=1,type=ARRAY] pResId, [out,size=1,type=ARRAY] pSecsFreeBeforeDestroy) */
  public void CreateResource(int ResTypId, int[] pResId, int[] pSecsFreeBeforeDestroy);

  /** @com.method(vtoffset=1, addFlagsVtable=4)
      @com.parameters([in,type=U4] ResTypId, [in,type=U4] resId, [in,type=I4] fRequiresTransactionEnlistment, [out,size=1,type=ARRAY] pRating) */
  public void RateResource(int ResTypId, int resId, int fRequiresTransactionEnlistment, int[] pRating);

  /** @com.method(vtoffset=2, addFlagsVtable=4)
      @com.parameters([in,type=U4] resId, [in,type=U4] TransId) */
  public void EnlistResource(int resId, int TransId);

  /** @com.method(vtoffset=3, addFlagsVtable=4)
      @com.parameters([in,type=U4] resId) */
  public void ResetResource(int resId);

  /** @com.method(vtoffset=4, addFlagsVtable=4)
      @com.parameters([in,type=U4] resId) */
  public void DestroyResource(int resId);

  /** @com.method(vtoffset=5, addFlagsVtable=4)
      @com.parameters([in,customMarshal="com.ms.com.UniStringMarshaller",type=CUSTOM] resId) */
  public void DestroyResourceS(String resId);


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x208b3651, (short)0x2b48, (short)0x11cf, (byte)0xbe, (byte)0x10, (byte)0x0, (byte)0xaa, (byte)0x0, (byte)0xa2, (byte)0xfa, (byte)0x25);
}
