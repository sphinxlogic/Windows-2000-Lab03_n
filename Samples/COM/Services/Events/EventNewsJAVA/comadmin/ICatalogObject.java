//
// Auto-generated using JActiveX.EXE 5.00.2918
//   ("C:\Program Files\Microsoft Visual Studio\VJ98\jactivex.exe" /wfc  /w /xi /X:rkc /l "C:\DOCUME~1\a-sunilc\LOCALS~1\Temp\jvc131.tmp" /nologo /d "D:\ComPlusSamples\Source\LCE\NewsFlash" "C:\WINNT\system32\Com\comadmin.dll")
//
// WARNING: Do not remove the comments that include "@com" directives.
// This source file must be compiled by a @com-aware compiler.
// If you are using the Microsoft Visual J++ compiler, you must use
// version 1.02.3920 or later. Previous versions will not issue an error
// but will not generate COM-enabled class files.
//

package comadmin;

import com.ms.com.*;
import com.ms.com.IUnknown;
import com.ms.com.Variant;

// Dual interface ICatalogObject
/** @com.interface(iid=6EB22871-8A19-11D0-81B6-00A0C9231C29, thread=AUTO, type=DUAL) */
public interface ICatalogObject extends IUnknown
{
  /** @com.method(vtoffset=4, dispid=1, type=PROPGET, name="Value", name2="getValue", addFlagsVtable=4)
      @com.parameters([in,type=STRING] bstrPropName, [type=VARIANT] return) */
  public Variant getValue(String bstrPropName);

  /** @com.method(vtoffset=5, dispid=1, type=PROPPUT, name="Value", name2="putValue", addFlagsVtable=4)
      @com.parameters([in,type=STRING] bstrPropName, [in,type=VARIANT] retval) */
  public void setValue(String bstrPropName, Variant retval);

  /** @com.method(vtoffset=6, dispid=2, type=PROPGET, name="Key", name2="getKey", addFlagsVtable=4)
      @com.parameters([type=VARIANT] return) */
  public Variant getKey();

  /** @com.method(vtoffset=7, dispid=3, type=PROPGET, name="Name", name2="getName", addFlagsVtable=4)
      @com.parameters([type=VARIANT] return) */
  public Variant getName();

  /** @com.method(vtoffset=8, dispid=4, type=METHOD, name="IsPropertyReadOnly", addFlagsVtable=4)
      @com.parameters([in,type=STRING] bstrPropName, [type=BOOLEAN] return) */
  public boolean IsPropertyReadOnly(String bstrPropName);

  /** @com.method(vtoffset=9, dispid=5, type=PROPGET, name="Valid", name2="getValid", addFlagsVtable=4)
      @com.parameters([type=BOOLEAN] return) */
  public boolean getValid();

  /** @com.method(vtoffset=10, dispid=6, type=METHOD, name="IsPropertyWriteOnly", addFlagsVtable=4)
      @com.parameters([in,type=STRING] bstrPropName, [type=BOOLEAN] return) */
  public boolean IsPropertyWriteOnly(String bstrPropName);


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x6eb22871, (short)0x8a19, (short)0x11d0, (byte)0x81, (byte)0xb6, (byte)0x0, (byte)0xa0, (byte)0xc9, (byte)0x23, (byte)0x1c, (byte)0x29);
}
