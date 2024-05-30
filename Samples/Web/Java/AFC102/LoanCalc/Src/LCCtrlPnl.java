//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import com.ms.ui.*;
import com.ms.fx.*;
import java.awt.Dimension;

public class LCCtrlPnl extends UIPanel implements LCConsts, LCCallbacks, Runnable
{
	private LCWizard wiz;
	private WZIntro intro;
	private WZValue value;
	private WZInterest intrst;
	private WZNumPeriods numper;
	private WZPayment paymnt;
	private WZFinal wfinal;
	private LCParams lparms;
	private LCInfoPnl info;
	private LCDataPnl sched;
	private int calc;
	private UIMessageBox mbox;

	public LCCtrlPnl(UIApplet applet, UIFrame frame)
	{
		setLayout(new UISplitLayout(0, 167));

		// Initialize load on demand images
		LCImages.init(applet, frame);

		// Set default values for loan parameters
		lparms = new LCParams(INIT_PV, INIT_RATE, INIT_LEN, true, INIT_FREQ, 0);
		calc = BL_PMNT; // --------------------------------------------------^
		lparms.calc(BL_PMNT);

		// Create Loan parameter Display panel
		add(info = new LCInfoPnl(lparms, this), "nw");

		// Create Viewer showing loan data(payment schedule)
		add(sched = new LCDataPnl(lparms), "se");

		// Create wizard steps and wizard for specifying different loan parameters
		intro = new WZIntro(); value = new WZValue();
		intrst = new WZInterest(); numper = new WZNumPeriods();
		paymnt = new WZPayment(); wfinal = new WZFinal();

		//  Need UIFrame for wizard, if we are run as applet passed in frame is null
		if ( applet != null )
			frame = FxToolkit.getHelperUIFrame();

		wiz = new LCWizard(frame, this, wfinal);
		wiz.setForcedBounds("image", new Dimension(80, 80));
		wiz.setForcedBounds("content", new Dimension(270, 150));
		wiz.addStep(intro); wiz.addStep(value); wiz.addStep(intrst);
		wiz.addStep(numper); wiz.addStep(paymnt); wiz.addStep(wfinal);

		// Create OK Message Box which will be used by the wizard to indicate
		//  an error in entering a loan parameter
		mbox = new UIMessageBox(frame, "Parameter Entry Error!", "", LCImages.get(INTRO),
								new UIButtonBar(UIButtonBar.OK, UIButtonBar.RAISED));
		mbox.setFont(new FxFont("Dialog", FxFont.PLAIN, 14));
	}

	public void hideWizard()
	{
		if ( wiz != null )
			wiz.setVisible(false);
	}

	public void run()
	{
		invokeWizard();
		// After first time, do not need Intro page
		wiz.setFirstStep(value);
	}

	public void setInitialFocus()
	{
		Thread th = new Thread(this);
		th.start();
	}

	public void invokeWizard()
	{
		long t_pv;
		int t_i, t_len, t_fidx, t_pmnt, oldcalc = calc;

		// set parameter to calculate to NONE, the various validation
		//  steps will set it accordingly
		setCalc(BL_NONE);

		// Call wizard
		if ( wiz.doModal() != null ) {
			LCParams t_lp = getParamsFromWiz();

			// If nothing has changed don't recalculate
			if ( (oldcalc != calc) ||
				 ((calc != BL_PV) && (t_lp.pv != lparms.pv)) || 
				 (t_lp.i != lparms.i) || 
				 ((calc != BL_LEN) && (t_lp.len != lparms.len)) ||
				 (t_lp.years != lparms.years) || (t_lp.hz_idx != lparms.hz_idx) ||
				 ((calc != BL_PMNT) && (t_lp.pmnt != lparms.pmnt)) ) {
				lparms = t_lp;
				if ( lparms.calc(calc) )
					setWizParams(lparms, false);

				// Display loan information
				info.setParams(lparms);
				//info.setValid(true);

				// repaint panel after wizard disappears, putting up an hour glass
				//  would also be a good idea, as it may take a little time to
				//  calculate payment schedule.
				//setVisible(false); setValid(true); setVisible(true);

				// Calculate and display payment schedule
				sched.fillList(lparms, false);
			}
		}
		else { // user cancelled wizard reset any parameters user may have changed
			setCalc(oldcalc);
			setWizParams(lparms, true);
		}
	}

	// get/set parameter to be calculated
	public int getCalc() { return calc; }
	public void setCalc(int id) { calc = id; }

	public int getID(IUIWizardStep step)
	{
		if ( step instanceof WZValue ) return PVALUE;
		else if ( step instanceof WZInterest ) return INTEREST;
		else if ( step instanceof WZNumPeriods ) return NUMPERIODS;
		else if ( step instanceof WZPayment ) return PAYMENT;
		else return -1;
	}

	// ******************************
	// Validate Wizard steps section
	// ******************************
	public void processPV()
	{
		if ( getPVFromWiz() == 0 )
			setCalc(BL_PV);
		else
			setCalc(BL_NONE); // Reset in case user uses Back to get here
	}

	public boolean isValidNumper()
	{
		String error = new String("");
		int nummonths = getLenFromWiz();

		if ( nummonths == 0 ) {
			if ( calc != BL_PV )
				setCalc(BL_LEN);
			else if ( calc == BL_PV )
				error = LEN_CALC_PV;
		}
		else {
			if ( calc != BL_PV )
				setCalc(BL_NONE);
			if ( numper.pnl.years )
				nummonths *= 12;
			if ( nummonths > MAX_MONTHS )
				error = NUMPER_TOO_LARGE;
		}

		if ( error.length() != 0 ) {
			mbox.setText(error);
			mbox.doModal();
			return false;
		}
		else
			return true;
	}

	public boolean isValidPayment()
	{
		String error = "";

		// if we get here either pv or n is being calculated so the pmnt cannot be 0
		LCParams lp = getParamsFromWiz();

		if ( lp.pmnt == 0 ) {
			if ( calc == BL_PV )
				error = PMNT_CALC_PV;
			else // must be calculating LEN
				error = PMNT_CALC_LEN;
		}
		else { // a payment has been entered
			if ( calc == BL_LEN ) {
				if ( (lp.pmnt/100.0) <= (lp.pv * lp.ip) )
					error = PMNT_TOO_SMALL_INT + calcMinPmnt(lp);
				else {
					lp.calc(BL_LEN);
					int lmonths = (lp.years ? lp.len*12 : lp.len);
					if ( lmonths > MAX_MONTHS )
						error = PMNT_TOO_SMALL_LEN + calcMinPmnt(lp);
				}
			}
			else { // must be calculating PV
				lp.calc(BL_PV);
				if ( lp.pv > MAX_PV )
					error = PMNT_TOO_LARGE_PV;
			}
		}

		if ( error.length() != 0 ) {
			mbox.setText(error);
			mbox.doModal();
			return false;
		}
		else
			return true;
	}

	private String calcMinPmnt(LCParams lp)
	{
		LCParams lcp = new LCParams(lp);
		lcp.n = (MAX_MONTHS*FREQ_FACTOR[lcp.hz_idx])/12;
		lcp.calc(BL_PMNT);
		return "" + new DNC(lcp.pmnt+1) + ".";
	}

	// ******************************
	// Get Wizard Parameters section
	// ******************************
	private LCParams getParamsFromWiz()
	{
		return new LCParams(getPVFromWiz(), getIFromWiz(), getLenFromWiz(),
							numper.pnl.years, getFreqIdxFromWiz(), getPmntFromWiz());
	}


	private long getPVFromWiz()
	{
		String value_str = value.pnl.pv_e.getValueText();
		if ( value_str.length() == 0 )
			return 0;
		else
			return (new Integer(value_str)).longValue();
	}

	private int getIFromWiz()
	{
		return (intrst.pnl.i_ec.getSelectedIndex() + 24);
	}

	private int getLenFromWiz()
	{
		String value_str = numper.pnl.len_e.getValueText();
		if ( value_str.length() == 0 )
			return 0;
		else
			return (new Integer(value_str)).intValue();
	}

	private int getFreqIdxFromWiz()
	{
		return numper.pnl.hz_c.getSelectedIndex();
	}

	private int getPmntFromWiz()
	{ 
		String value_str = paymnt.pnl.pmnt_e.getValueText();
		if ( value_str.length() == 0 )
			return 0;
		else
			return (int)((new Double(value_str)).doubleValue()*100.0);
	}

	// ******************************
	// Set Wizard Parameters section
	// ******************************
	private void setWizParams(LCParams lp, boolean doall)
	{
		if ( doall || (calc != BL_PV) )
			setPV(lp.pv);
		else
			setPV(0);

		if ( doall || (calc != BL_LEN) ) {
			setLen(lp.len);
			setLenUnit(lp.years);
		}
		else
			setLen(0);

		if ( doall || (calc != BL_PMNT) )
			setPayment(lp.pmnt);
		else
			setPayment(0);

		setI(lp.i);
		setHz(lp.hz_idx);
	}

	private void setPV(long pv)
	{
		if ( pv == 0 )
			value.pnl.pv_e.setValueText("");
		else
			value.pnl.pv_e.setValueText("" + pv);
	}

	private void setLen(int len)
	{
		if ( len == 0 )
			numper.pnl.len_e.setValueText("");
		else
			numper.pnl.len_e.setValueText("" + len);
	}

	private void setLenUnit(boolean years)
	{
		if ( years ) {
			numper.pnl.btn_y.setChecked(true);
			numper.pnl.btn_m.setChecked(false);
		}
		else {
			numper.pnl.btn_y.setChecked(false);
			numper.pnl.btn_m.setChecked(true);
		}
	}

	// payment is stored as cents, so 100 = $1.00
	private void setPayment(int pmnt)
	{
		if ( pmnt == 0 )
			paymnt.pnl.pmnt_e.setValueText("");
		else
			paymnt.pnl.pmnt_e.setValueText("" + (pmnt/100) + "." + DLRS.mk2Digits(pmnt%100));
	}

	private void setI(int i) { intrst.pnl.i_ec.setSelectedIndex(i - MIN_RATE); }

	private void setHz(int idx) { numper.pnl.hz_c.setSelectedIndex(idx); }
}
