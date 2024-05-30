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

// VTable-only interface IComSecurityEvents
/** @com.interface(iid=683130AC-2E50-11D2-98A5-00C04F8EE1C4, thread=AUTO) */
public interface IComSecurityEvents extends IUnknown
{
  /** @com.method(vtoffset=0, addFlagsVtable=4)
      @com.parameters([in,type=PTR] pinfo, [in,type=PTR] guidActivity, [in,type=U8] ObjectID, [in,type=PTR] guidIID, [in,type=U4] iMeth, [in,type=U4] cbByteOrig, [in,size=1,type=ARRAY] pSidOriginalUser, [in,type=U4] cbByteCur, [in,size=1,type=ARRAY] pSidCurrentUser, [in,type=I4] bCurrentUserInpersonatingInProc) */
  public void OnAuthenticate(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidActivity, long ObjectID, com.ms.com._Guid guidIID, int iMeth, int cbByteOrig, byte[] pSidOriginalUser, int cbByteCur, byte[] pSidCurrentUser, int bCurrentUserInpersonatingInProc);

  /** @com.method(vtoffset=1, addFlagsVtable=4)
      @com.parameters([in,type=PTR] pinfo, [in,type=PTR] guidActivity, [in,type=U8] ObjectID, [in,type=PTR] guidIID, [in,type=U4] iMeth, [in,type=U4] cbByteOrig, [in,size=1,type=ARRAY] pSidOriginalUser, [in,type=U4] cbByteCur, [in,size=1,type=ARRAY] pSidCurrentUser, [in,type=I4] bCurrentUserInpersonatingInProc) */
  public void OnAuthenticateFail(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidActivity, long ObjectID, com.ms.com._Guid guidIID, int iMeth, int cbByteOrig, byte[] pSidOriginalUser, int cbByteCur, byte[] pSidCurrentUser, int bCurrentUserInpersonatingInProc);


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x683130ac, (short)0x2e50, (short)0x11d2, (byte)0x98, (byte)0xa5, (byte)0x0, (byte)0xc0, (byte)0x4f, (byte)0x8e, (byte)0xe1, (byte)0xc4);
}
