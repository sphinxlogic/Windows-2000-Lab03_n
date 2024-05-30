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

// Dual interface IMessageMover
/** @com.interface(iid=588A085A-B795-11D1-8054-00C04FC340EE, thread=AUTO, type=DUAL) */
public interface IMessageMover extends IUnknown
{
  /** @com.method(vtoffset=4, dispid=1, type=PROPGET, name="SourcePath", addFlagsVtable=4)
      @com.parameters([type=STRING] return) */
  public String getSourcePath();

  /** @com.method(vtoffset=5, dispid=1, type=PROPPUT, name="SourcePath", addFlagsVtable=4)
      @com.parameters([in,type=STRING] pVal) */
  public void setSourcePath(String pVal);

  /** @com.method(vtoffset=6, dispid=2, type=PROPGET, name="DestPath", addFlagsVtable=4)
      @com.parameters([type=STRING] return) */
  public String getDestPath();

  /** @com.method(vtoffset=7, dispid=2, type=PROPPUT, name="DestPath", addFlagsVtable=4)
      @com.parameters([in,type=STRING] pVal) */
  public void setDestPath(String pVal);

  /** @com.method(vtoffset=8, dispid=3, type=PROPGET, name="CommitBatchSize", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public int getCommitBatchSize();

  /** @com.method(vtoffset=9, dispid=3, type=PROPPUT, name="CommitBatchSize", addFlagsVtable=4)
      @com.parameters([in,type=I4] pVal) */
  public void setCommitBatchSize(int pVal);

  /** @com.method(vtoffset=10, dispid=4, type=METHOD, name="MoveMessages", addFlagsVtable=4)
      @com.parameters([type=I4] return) */
  public int MoveMessages();


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x588a085a, (short)0xb795, (short)0x11d1, (byte)0x80, (byte)0x54, (byte)0x0, (byte)0xc0, (byte)0x4f, (byte)0xc3, (byte)0x40, (byte)0xee);
}
