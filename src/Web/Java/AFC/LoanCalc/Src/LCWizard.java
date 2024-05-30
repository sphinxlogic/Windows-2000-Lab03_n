//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.Event;
import com.ms.ui.*;
import com.ms.fx.*;

public class LCWizard extends UIWizard implements LCConsts
{
	private WZValue firststep;
	private LCCallbacks callback;
	private IUIWizardStep finish;

	public LCWizard(UIFrame frame, LCCallbacks callback, IUIWizardStep finish)
	{
		super(frame, "LoanCalc - A Loan Calculator");
		setFont(new FxFont("Dialog", FxFont.PLAIN, 14));
		firststep = null;
		this.callback = callback;
		this.finish = finish;
	}

	// This is the method that will be used to validate data at every step
	public IUIWizardStep getNextStep()
	{
		IUIWizardStep curstep = getVisibleStep();
		switch ( callback.getID(curstep) ) {
		case PVALUE:
			callback.processPV();
			return null;

		case NUMPERIODS:
			if ( !callback.isValidNumper() )
				return curstep;
			else {
				int calc = callback.getCalc();
				// do both PV and n have entered values? Yes? calculate pmnt; No? enter pmnt
				if ( (calc != BL_PV) && (calc != BL_LEN) ) {
					callback.setCalc(BL_PMNT);
					return finish; 
				}
				else
					return null;
			}
		case PAYMENT:
			return (callback.isValidPayment() ? null : curstep);
		}
		return null;
	}

	public void setFirstStep(WZValue firststep)
	{
		this.firststep = firststep;
	}

	// Override getFirstStep to skip over intro
	public IUIWizardStep getFirstStep()
	{
		if ( firststep == null )
			return super.getFirstStep();
		else
			return (IUIWizardStep)firststep;
	}
}