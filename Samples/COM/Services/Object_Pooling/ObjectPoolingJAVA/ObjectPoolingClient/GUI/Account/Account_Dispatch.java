//
// Auto-generated using JActiveX.EXE 5.00.2918
//   ("C:\Program Files\Microsoft Visual Studio\VJ98\jactivex.exe" /wfc  /w /xi /X:rkc /l "C:\DOCUME~1\a-sunilc\LOCALS~1\Temp\jvc220.tmp" /nologo /d "D:\ComPlusSamples\Test\ObjectPoolingClient\GUI" "D:\ComPlusSamples\Source\Object Pooling\Account\Account.dll")
//
// WARNING: Do not remove the comments that include "@com" directives.
// This source file must be compiled by a @com-aware compiler.
// If you are using the Microsoft Visual J++ compiler, you must use
// version 1.02.3920 or later. Previous versions will not issue an error
// but will not generate COM-enabled class files.
//

package account;

import com.ms.com.*;
import com.ms.com.IUnknown;
import com.ms.com.Variant;

// Dispatch-only interface Account_Dispatch
/** @com.interface(iid=F9AC9894-403E-416E-9E94-C7ECFB921128, thread=AUTO, type=DISPATCH) */
public interface Account_Dispatch extends IUnknown
{
  /** @com.method(dispid=100, type=METHOD, name="wait", returntype=VOID)
      @com.parameters([in,out,elementType=VARIANT,type=PTR] Parameter0, [in,out,elementType=VARIANT,type=PTR] Parameter1, [type=VARIANT] return) */
  public Variant wait(Variant Parameter0, Variant Parameter1);

  /** @com.method(dispid=101, type=METHOD, name="debit", returntype=VOID)
      @com.parameters([in,type=STRING] Parameter0, [in,type=I4] Parameter1) */
  public void debit(String Parameter0, int Parameter1);

  // hashCode UNMAPPABLE: Name is a keyword or conflicts with another member.
  //  public int hashCode();

  /** @com.method(dispid=103, type=METHOD, name="checkBalance", returntype=VOID)
      @com.parameters([in,type=STRING] Parameter0, [type=I4] return) */
  public int checkBalance(String Parameter0);

  /** @com.method(dispid=104, type=METHOD, name="credit", returntype=VOID)
      @com.parameters([in,type=STRING] Parameter0, [in,type=I4] Parameter1) */
  public void credit(String Parameter0, int Parameter1);

  /** @com.method(dispid=105, type=METHOD, name="transfer", returntype=VOID)
      @com.parameters([in,type=STRING] Parameter0, [in,type=STRING] Parameter1, [in,type=I4] Parameter2) */
  public void transfer(String Parameter0, String Parameter1, int Parameter2);

  // toString UNMAPPABLE: Name is a keyword or conflicts with another member.
  //  public String toString();

  // equals UNMAPPABLE: Name is a keyword or conflicts with another member.
  //  public boolean equals(Object Parameter0);

  // notify UNMAPPABLE: Name is a keyword or conflicts with another member.
  //  public void notify();

  // getClass UNMAPPABLE: Name is a keyword or conflicts with another member.
  //  public Object getClass();

  // notifyAll UNMAPPABLE: Name is a keyword or conflicts with another member.
  //  public void notifyAll();


  public static final com.ms.com._Guid iid = new com.ms.com._Guid((int)0xf9ac9894, (short)0x403e, (short)0x416e, (byte)0x9e, (byte)0x94, (byte)0xc7, (byte)0xec, (byte)0xfb, (byte)0x92, (byte)0x11, (byte)0x28);
}
