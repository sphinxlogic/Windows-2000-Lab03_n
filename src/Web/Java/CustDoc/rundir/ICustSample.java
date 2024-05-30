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

// VTable-only interface ICustSample
/** @com.interface(iid=2BEBEC41-6499-11D0-BFFC-00AA003CFDFC, thread=NO) */
public interface ICustSample extends IUnknown
{
  /** @com.method(vtoffset=0)
      @com.parameters([in,customMarshal="FixedPtMarshaler",type=CUSTOMBYVAL] fp) */
  public void PassFixedPtIn(double fp);

  /** @com.method(vtoffset=1)
      @com.parameters([customMarshal="FixedPtMarshaler",type=CUSTOMBYVAL] return) */
  public double PassPFixedPtOutRetVal();

  /** @com.method(vtoffset=2)
      @com.parameters([in,customMarshal="FixedPtMarshaler",type=CUSTOM] pfp) */
  public void PassPFixedPtIn(double pfp);

  /** @com.method(vtoffset=3)
      @com.parameters([out,customMarshal="FixedPtMarshaler",type=CUSTOM] pfp) */
  public void PassPFixedPtOut(double[] pfp);

  /** @com.method(vtoffset=4)
      @com.parameters([in,out,customMarshal="FixedPtMarshaler",type=CUSTOM] pfp) */
  public void PassPFixedPtInOut(double[] pfp);

  /** @com.method(vtoffset=5)
      @com.parameters([in,iid=2BEBEC41-6499-11D0-BFFC-00AA003CFDFC,thread=NO,type=OBJECT] pCustSample) */
  public void PassFixedPtsFromComToJava(ICustSample pCustSample);

  /** @com.method(vtoffset=6)
      @com.parameters([in,customMarshal="VarStrMarshaler",type=CUSTOMBYVAL] v) */
  public void PassMyVariantIn(String v);

  /** @com.method(vtoffset=7)
      @com.parameters([customMarshal="VarStrMarshaler",type=CUSTOMBYVAL] return) */
  public String PassPMyVariantOutRetVal();

  /** @com.method(vtoffset=8)
      @com.parameters([in,customMarshal="VarStrMarshaler",type=CUSTOM] pv) */
  public void PassPMyVariantIn(String pv);

  /** @com.method(vtoffset=9)
      @com.parameters([out,customMarshal="VarStrMarshaler",type=CUSTOM] pv) */
  public void PassPMyVariantOut(String[] pv);

  /** @com.method(vtoffset=10)
      @com.parameters([in,out,customMarshal="VarStrMarshaler",type=CUSTOM] pv) */
  public void PassPMyVariantInOut(String[] pv);

  /** @com.method(vtoffset=11)
      @com.parameters([in,iid=2BEBEC41-6499-11D0-BFFC-00AA003CFDFC,thread=NO,type=OBJECT] pCustSample) */
  public void PassMyVariantFromComToJava(ICustSample pCustSample);

  /** @com.method(vtoffset=12)
      @com.parameters([out,customMarshal="PointMarshaler",type=CUSTOM] ppt) */
  public void PassPPointOut(java.awt.Point ppt);

  /** @com.method(vtoffset=13)
      @com.parameters([in,out,customMarshal="PointMarshaler",type=CUSTOM] ppt) */
  public void PassPPointInOut(java.awt.Point ppt);

  /** @com.method(vtoffset=14)
      @com.parameters([in,iid=2BEBEC41-6499-11D0-BFFC-00AA003CFDFC,thread=NO,type=OBJECT] pCustSample) */
  public void PassPointFromComToJava(ICustSample pCustSample);

  /** @com.method(vtoffset=15)
      @com.parameters([in,customMarshal="RectMarshaler",type=CUSTOMBYVAL] r) */
  public void PassRectIn(java.awt.Rectangle r);

  /** @com.method(vtoffset=16)
      @com.parameters([customMarshal="RectMarshaler",type=CUSTOMBYVAL] return) */
  public java.awt.Rectangle PassPRectOutRetVal();

  /** @com.method(vtoffset=17)
      @com.parameters([in,customMarshal="RectMarshaler",type=CUSTOM] pr) */
  public void PassPRectIn(java.awt.Rectangle pr);

  /** @com.method(vtoffset=18)
      @com.parameters([out,customMarshal="RectMarshaler",type=CUSTOM] pr) */
  public void PassPRectOut(java.awt.Rectangle[] pr);

  /** @com.method(vtoffset=19)
      @com.parameters([in,out,customMarshal="RectMarshaler",type=CUSTOM] pr) */
  public void PassPRectInOut(java.awt.Rectangle[] pr);

  /** @com.method(vtoffset=20)
      @com.parameters([customMarshal="RectMarshaler",type=CUSTOM] return) */
  public java.awt.Rectangle PassPPRectOutRetVal();

  /** @com.method(vtoffset=21)
      @com.parameters([in,customMarshal="RectMarshaler",type=CUSTOMBYREF] ppr) */
  public void PassPPRectIn(java.awt.Rectangle[] ppr);

  /** @com.method(vtoffset=22)
      @com.parameters([out,customMarshal="RectMarshaler",type=CUSTOMBYREF] ppr) */
  public void PassPPRectOut(java.awt.Rectangle[] ppr);

  /** @com.method(vtoffset=23)
      @com.parameters([in,out,customMarshal="RectMarshaler",type=CUSTOMBYREF] ppr) */
  public void PassPPRectInOut(java.awt.Rectangle[] ppr);

  /** @com.method(vtoffset=24)
      @com.parameters([in,iid=2BEBEC41-6499-11D0-BFFC-00AA003CFDFC,thread=NO,type=OBJECT] pCustSample) */
  public void PassRectFromComToJava(ICustSample pCustSample);

  /** @com.method(vtoffset=25)
      @com.parameters([in,customMarshal="AnsiMarshaler",type=CUSTOM] pstr) */
  public void PassPStrIn(String pstr);

  /** @com.method(vtoffset=26)
      @com.parameters([customMarshal="AnsiMarshaler",type=CUSTOM] return) */
  public String PassPPStrOutRetVal();

  /** @com.method(vtoffset=27)
      @com.parameters([in,customMarshal="AnsiMarshaler",type=CUSTOMBYREF] ppstr) */
  public void PassPPStrIn(String[] ppstr);

  /** @com.method(vtoffset=28)
      @com.parameters([out,customMarshal="AnsiMarshaler",type=CUSTOMBYREF] ppstr) */
  public void PassPPStrOut(String[] ppstr);

  /** @com.method(vtoffset=29)
      @com.parameters([in,out,customMarshal="AnsiMarshaler",type=CUSTOMBYREF] ppstr) */
  public void PassPPStrInOut(String[] ppstr);

  /** @com.method(vtoffset=30)
      @com.parameters([in,iid=2BEBEC41-6499-11D0-BFFC-00AA003CFDFC,thread=NO,type=OBJECT] pCustSample) */
  public void PassAnsiFromComToJava(ICustSample pCustSample);


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0x2bebec41, (short)0x6499, (short)0x11d0, (byte)0xbf, (byte)0xfc, (byte)0x0, (byte)0xaa, (byte)0x0, (byte)0x3c, (byte)0xfd, (byte)0xfc);
}
