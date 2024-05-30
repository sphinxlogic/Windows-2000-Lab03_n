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

// VTable-only interface IComCRMEvents
/** @com.interface(iid=683130B5-2E50-11D2-98A5-00C04F8EE1C4, thread=AUTO) */
public interface IComCRMEvents extends IUnknown
{
  /** @com.method(vtoffset=0, addFlagsVtable=4)
      @com.parameters([in,type=PTR] pinfo, [in,size=16,type=STRUCT] guidApp) */
  public void OnCRMRecoveryStart(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidApp);

  /** @com.method(vtoffset=1, addFlagsVtable=4)
      @com.parameters([in,type=PTR] pinfo, [in,size=16,type=STRUCT] guidApp) */
  public void OnCRMRecoveryDone(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidApp);

  /** @com.method(vtoffset=2, addFlagsVtable=4)
      @com.parameters([in,type=PTR] pinfo, [in,size=16,type=STRUCT] guidApp) */
  public void OnCRMCheckpoint(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidApp);

  // szProgIdCompensator UNMAPPABLE: Untranslatable typelib object.
  // szDescription UNMAPPABLE: Untranslatable typelib object.
  //  public void OnCRMBegin(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidClerkCLSID, com.ms.com._Guid guidActivity, com.ms.com._Guid guidTx, UNMAPPABLE szProgIdCompensator, UNMAPPABLE szDescription);

  /** @com.method(vtoffset=4, addFlagsVtable=4)
      @com.parameters([in,type=PTR] pinfo, [in,size=16,type=STRUCT] guidClerkCLSID) */
  public void OnCRMPrepare(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidClerkCLSID);

  /** @com.method(vtoffset=5, addFlagsVtable=4)
      @com.parameters([in,type=PTR] pinfo, [in,size=16,type=STRUCT] guidClerkCLSID) */
  public void OnCRMCommit(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidClerkCLSID);

  /** @com.method(vtoffset=6, addFlagsVtable=4)
      @com.parameters([in,type=PTR] pinfo, [in,size=16,type=STRUCT] guidClerkCLSID) */
  public void OnCRMAbort(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidClerkCLSID);

  /** @com.method(vtoffset=7, addFlagsVtable=4)
      @com.parameters([in,type=PTR] pinfo, [in,size=16,type=STRUCT] guidClerkCLSID) */
  public void OnCRMIndoubt(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidClerkCLSID);

  /** @com.method(vtoffset=8, addFlagsVtable=4)
      @com.parameters([in,type=PTR] pinfo, [in,size=16,type=STRUCT] guidClerkCLSID) */
  public void OnCRMDone(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidClerkCLSID);

  /** @com.method(vtoffset=9, addFlagsVtable=4)
      @com.parameters([in,type=PTR] pinfo, [in,size=16,type=STRUCT] guidClerkCLSID) */
  public void OnCRMRelease(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidClerkCLSID);

  /** @com.method(vtoffset=10, addFlagsVtable=4)
      @com.parameters([in,type=PTR] pinfo, [in,size=16,type=STRUCT] guidClerkCLSID, [in,type=U4] dwCrmRecordType, [in,type=U4] dwRecordSize) */
  public void OnCRMAnalyze(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidClerkCLSID, int dwCrmRecordType, int dwRecordSize);

  /** @com.method(vtoffset=11, addFlagsVtable=4)
      @com.parameters([in,type=PTR] pinfo, [in,size=16,type=STRUCT] guidClerkCLSID, [in,type=I4] fVariants, [in,type=U4] dwRecordSize) */
  public void OnCRMWrite(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidClerkCLSID, int fVariants, int dwRecordSize);

  /** @com.method(vtoffset=12, addFlagsVtable=4)
      @com.parameters([in,type=PTR] pinfo, [in,size=16,type=STRUCT] guidClerkCLSID) */
  public void OnCRMForget(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidClerkCLSID);

  /** @com.method(vtoffset=13, addFlagsVtable=4)
      @com.parameters([in,type=PTR] pinfo, [in,size=16,type=STRUCT] guidClerkCLSID) */
  public void OnCRMForce(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidClerkCLSID);

  /** @com.method(vtoffset=14, addFlagsVtable=4)
      @com.parameters([in,type=PTR] pinfo, [in,size=16,type=STRUCT] guidClerkCLSID, [in,type=I4] fVariants, [in,type=U4] dwRecordSize) */
  public void OnCRMDeliver(comsvcs.__MIDL___MIDL_itf_autosvcs_0283_0001 pinfo, com.ms.com._Guid guidClerkCLSID, int fVariants, int dwRecordSize);


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x683130b5, (short)0x2e50, (short)0x11d2, (byte)0x98, (byte)0xa5, (byte)0x0, (byte)0xc0, (byte)0x4f, (byte)0x8e, (byte)0xe1, (byte)0xc4);
}
