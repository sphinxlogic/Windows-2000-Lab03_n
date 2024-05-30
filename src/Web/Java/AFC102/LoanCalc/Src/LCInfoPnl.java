//
// (c) 1997 Microsoft Corporation.	All rights reserved.
//
import java.awt.Event;
import java.awt.Insets;
import com.ms.ui.*;
import com.ms.fx.*;

class LCInfoPnl extends UIPanel implements LCConsts
{
	public boolean appmodal = false;
	private UIText pv, len, freq, intrst, pmnt;
	private UIPushButton modify;
	private LCCallbacks callback;
	private FxColor c_static, c_dynamic, c_changed;

	public LCInfoPnl(LCParams lp, LCCallbacks lc)
	{
		setLayout(new UIBorderLayout());
		callback = lc;

		UIGroup grp = new UIGroup("Loan Parameters");
		grp.setLayout(new UIVerticalFlowLayout(UIVerticalFlowLayout.FILL, 0));

		grp.add(new ComboPnl(IDX_PV, pv = new UIText("", UIText.RIGHT), 15));
		grp.add(new ComboPnl(IDX_INT, intrst = new UIText("", UIText.RIGHT), 15));
		grp.add(new ComboPnl(IDX_LEN, len = new UIText("", UIText.RIGHT), 15));
		grp.add(new ComboPnl(IDX_FREQ, freq = new UIText("", UIText.RIGHT), 15));
		grp.add(new ComboPnl(IDX_PMNT, pmnt = new UIText("", UIText.RIGHT), 20));
		grp.add(new BL(modify = new UIPushButton("Modify Parameters",
												UIPushButton.RAISED | UIPushButton.THICK),
												0,8,0,8));
		c_static = new FxColor(0,0,0);
		c_dynamic = new FxColor(0,0,255);
		c_changed = new FxColor(255,0,0);

		intrst.setForeground(BaseColor.getColor(c_static));
		freq.setForeground(BaseColor.getColor(c_static));
		setParams(lp);
		add(grp, "center");
	}

	public void setParams(LCParams lp)
	{
		pv.setName("" + new DLRS(lp.pv));
		len.setName("" + lp.len + " " + (lp.years ? "year(s)" : "month(s)"));
		intrst.setName("" + new PRCNT(lp.i));
		pmnt.setName("" + new DNC(lp.pmnt));
		freq.setName(FREQ_STR[lp.hz_idx]);

		int calc = callback.getCalc();

		switch ( calc ) {
		case BL_PV:
			pv.setForeground(BaseColor.getColor(c_changed));
			len.setForeground(BaseColor.getColor(c_dynamic));
			pmnt.setForeground(BaseColor.getColor(c_dynamic));
			break;
		case BL_LEN:
			pv.setForeground(BaseColor.getColor(c_dynamic));
			len.setForeground(BaseColor.getColor(c_changed));
			pmnt.setForeground(BaseColor.getColor(c_dynamic));
			break;
		case BL_PMNT:
			pv.setForeground(BaseColor.getColor(c_dynamic));
			len.setForeground(BaseColor.getColor(c_dynamic));
			pmnt.setForeground(BaseColor.getColor(c_changed));
			break;
		}
	}

	public boolean action (Event evt, Object arg)
	{
		if ( appmodal )
			return true;

		if ( arg instanceof UIButton ) {
			if ( arg == modify ) {
				WizThread wiz = new WizThread(callback, this);
				wiz.start();
			}
		}
		return super.action(evt, arg);
	}

	public Insets getInsets() { return new Insets(5, 5, 5, 10); }
}

class WizThread extends Thread
{
	private LCCallbacks callback;
	private LCInfoPnl app;

	public WizThread(LCCallbacks lc, LCInfoPnl ip)
	{
		callback = lc;
		app = ip;
	}
		
	public void run()
	{
		app.appmodal = true;
		callback.invokeWizard();
		app.appmodal = false;
	}
}

class ComboPnl extends UIPanel implements LCConsts
{
	private int b;

	public ComboPnl(int i, UIText data, int bottom)
	{
		UIGraphic grfc;
		UIText label;

		b = bottom;

		grfc = new UIGraphic(LCImages.get(IDX_IMG[i]));
		label = new UIText(IDX_STR[i], UIText.LEFT);

		setLayout(new UIBorderLayout());
		add(grfc, "west");
		UIPanel pnl = new UIPanel();
		pnl.setLayout(new UIBorderLayout());
		pnl.add(label, "north"); pnl.add(data, "south");
		add(pnl, "center");
	}

	public Insets getInsets() { return new Insets(0, 0, b, 0); }
}
