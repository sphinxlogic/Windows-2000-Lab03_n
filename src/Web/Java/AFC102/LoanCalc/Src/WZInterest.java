//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import com.ms.ui.*;
import com.ms.fx.*;
import java.awt.Event;
import java.awt.Insets;

public class WZInterest extends UIWizardStep implements LCConsts
{
	public InterestPnl pnl;

	public WZInterest()
	{
		super(new UIGraphic(LCImages.get(INTEREST)), new InterestPnl());
		pnl = (InterestPnl)getContent();
	}
}

class InterestPnl extends FocusUIPanel implements LCConsts, IFxTextConstants
{
	public UIEditChoice i_ec;

	public InterestPnl()
	{
		setLayout(new UIBorderLayout());

		// Main text
		UIDrawText intro = new UIDrawText(INTEREST_TXT);
		intro.setWordWrap(IFxTextConstants.wwKeepWordIntact);
		//UIText intro = new UIText(INTEREST_TXT, UIText.LEFT);

		// Interest Rate label
		UIText i_t = new UIText("Interest Rate:", UIText.RIGHT);

		// Create Interest Rate combobox
		i_ec = new UIEditChoice();

		for ( int j = 24; j <= 200; j++ )
			i_ec.add(new UIText("" + new PRCNT(j), UIText.LEFT));
		i_ec.setSelectedIndex(INIT_RATE - MIN_RATE);

		add(new HSL(intro, 
					new VSL(i_t, 
							new BL(i_ec, 35,10,35,0),
							180),
					45),
			"center");
	}

	public boolean action(Event e, Object arg)
	{
		// if user hits "enter" in UIEditChoice arg will equal null
		if ( (e.target == i_ec) && (arg == null) )
		{
			double eighths = 0.0;
			String value_str = i_ec.getValueText();
			if ( value_str.endsWith(" %") )
				i_ec.setSelectedIndex(i_ec.getSelectedIndex());
			else {
				// User can enter anything in the UIEditChoice edit control
				//   if entry is not well formed, make 3% selected
				try {
					eighths = (new Double(value_str)).doubleValue() * 8.0;
				}
				catch ( NumberFormatException nfe ) { } // do nothing, initialization
														//  will do correct thing.
				if ( eighths < 24.0 )
					i_ec.setSelectedIndex(0);
				else if ( eighths > 200.0 )
					i_ec.setSelectedIndex(176);
				else
					i_ec.setSelectedIndex((int)(Math.round(eighths) - MIN_RATE));
			}
		}
		return super.action(e, arg);
	}	

	public Insets getInsets() { return new Insets(10,0,0,0); }
}
