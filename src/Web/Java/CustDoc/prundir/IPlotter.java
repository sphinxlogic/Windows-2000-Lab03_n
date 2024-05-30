//
// Auto-generated using JCOM.EXE 4.79.2035
//   (..\..\..\..\javatest\custdoc\tools\jcom.exe /jc Plotter -n..\Plotter)
//
// WARNING: Do not remove the comments that include "@com" directives.
// This source file must be compiled by a @com-aware compiler.
// If you are using the Microsoft Visual J++ compiler, you must use
// version 1.02.3920 or later. Previous versions will not issue an error
// but will not generate COM-enabled class files.
//

import com.ms.com.*;
import com.ms.com.IUnknown;
import com.ms.com.Variant;

// VTable-only interface IPlotter
/** @com.interface(iid=EFFA21E1-6928-11D0-BFFC-00AA003CFDFC, thread=NO) */
public interface IPlotter extends IUnknown
{
  /** @com.method(vtoffset=0)
      @com.parameters([in,customMarshal="PointMarshaler",type=CUSTOM] start, [in,customMarshal="PointMarshaler",type=CUSTOM] end) */
  public void DrawLine(java.awt.Point start, java.awt.Point end);


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0xeffa21e1, (short)0x6928, (short)0x11d0, (byte)0xbf, (byte)0xfc, (byte)0x0, (byte)0xaa, (byte)0x0, (byte)0x3c, (byte)0xfd, (byte)0xfc);
}
