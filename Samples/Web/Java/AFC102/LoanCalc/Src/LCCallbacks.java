//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import com.ms.ui.*;

public interface LCCallbacks
{
	public void invokeWizard();
	public int getID(IUIWizardStep step);
	public int getCalc();
	public void setCalc(int id);
	public void processPV();
	public boolean isValidNumper();
	public boolean isValidPayment();
}
