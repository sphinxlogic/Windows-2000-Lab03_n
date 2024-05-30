//
// Auto-generated using JCOM.EXE 4.79.2035
//   (..\..\..\..\javatest\custdoc\tools\jcom.exe /jc CustSample -n..\CustSample)
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

/** @com.class(classid=2BEBEC42-6499-11D0-BFFC-00AA003CFDFC,DynamicCasts)
*/
public final class CCustSample implements IUnknown,com.ms.com.NoAutoScripting,ICustSample
{
  /** @com.method() */
  public native void PassFixedPtIn(double fp);

  /** @com.method() */
  public native double PassPFixedPtOutRetVal();

  /** @com.method() */
  public native void PassPFixedPtIn(double pfp);

  /** @com.method() */
  public native void PassPFixedPtOut(double[] pfp);

  /** @com.method() */
  public native void PassPFixedPtInOut(double[] pfp);

  /** @com.method() */
  public native void PassFixedPtsFromComToJava(ICustSample pCustSample);

  /** @com.method() */
  public native void PassMyVariantIn(String v);

  /** @com.method() */
  public native String PassPMyVariantOutRetVal();

  /** @com.method() */
  public native void PassPMyVariantIn(String pv);

  /** @com.method() */
  public native void PassPMyVariantOut(String[] pv);

  /** @com.method() */
  public native void PassPMyVariantInOut(String[] pv);

  /** @com.method() */
  public native void PassMyVariantFromComToJava(ICustSample pCustSample);

  /** @com.method() */
  public native void PassPPointOut(java.awt.Point ppt);

  /** @com.method() */
  public native void PassPPointInOut(java.awt.Point ppt);

  /** @com.method() */
  public native void PassPointFromComToJava(ICustSample pCustSample);

  /** @com.method() */
  public native void PassRectIn(java.awt.Rectangle r);

  /** @com.method() */
  public native java.awt.Rectangle PassPRectOutRetVal();

  /** @com.method() */
  public native void PassPRectIn(java.awt.Rectangle pr);

  /** @com.method() */
  public native void PassPRectOut(java.awt.Rectangle[] pr);

  /** @com.method() */
  public native void PassPRectInOut(java.awt.Rectangle[] pr);

  /** @com.method() */
  public native java.awt.Rectangle PassPPRectOutRetVal();

  /** @com.method() */
  public native void PassPPRectIn(java.awt.Rectangle[] ppr);

  /** @com.method() */
  public native void PassPPRectOut(java.awt.Rectangle[] ppr);

  /** @com.method() */
  public native void PassPPRectInOut(java.awt.Rectangle[] ppr);

  /** @com.method() */
  public native void PassRectFromComToJava(ICustSample pCustSample);

  /** @com.method() */
  public native void PassPStrIn(String pstr);

  /** @com.method() */
  public native String PassPPStrOutRetVal();

  /** @com.method() */
  public native void PassPPStrIn(String[] ppstr);

  /** @com.method() */
  public native void PassPPStrOut(String[] ppstr);

  /** @com.method() */
  public native void PassPPStrInOut(String[] ppstr);

  /** @com.method() */
  public native void PassAnsiFromComToJava(ICustSample pCustSample);


  public static final com.ms.com._Guid clsid = new com.ms.com._Guid((int)0x2bebec42, (short)0x6499, (short)0x11d0, (byte)0xbf, (byte)0xfc, (byte)0x0, (byte)0xaa, (byte)0x0, (byte)0x3c, (byte)0xfd, (byte)0xfc);
}
