//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.Dimension;
import java.awt.Event;
import com.ms.ui.*;
import com.ms.fx.*;

public class Pz15PropNav extends UIPropertyPage implements Pz15Consts
{
	private Pz15Options props;
	private UIRadioButton blank, btn, select;

	Pz15PropNav(Pz15Options props) 
	{ 
		super(props);
		this.props = props;
	}

	public boolean addContent()
	{
		UIGroup navmode = new UIGroup("Use arrow keys to ...");
		navmode.setLayout(new UIGridLayout(0,1));
		btn = new UIRadioButton("... move buttons, or"); btn.setID(M_BUTTON);
		blank = new UIRadioButton("... move the blank space, or"); blank.setID(M_BLANK);
		select = new UIRadioButton("... select buttons"); select.setID(M_SELECT);
		navmode.add(btn); navmode.add(blank); navmode.add(select);

		// Set initial state according to props
		switch ( props.navmode ) {
		case M_BUTTON: btn.setChecked(true); break;
		case M_BLANK: blank.setChecked(true); break;
		case M_SELECT: select.setChecked(true); break;
		}
		addAt(navmode, 6, 10, new Dimension(189, 86));
		return true;
	}

	public boolean action(Event e, Object arg)
	{
		if ( arg instanceof UIRadioButton ) {
			int id = ((UIRadioButton)arg).getID();
			switch ( id ) {
			case M_BUTTON:
				btn.setChecked(true); blank.setChecked(false); select.setChecked(false);
				setApplyable(true);
				break;
			case M_BLANK:
				btn.setChecked(false); blank.setChecked(true); select.setChecked(false);
				setApplyable(true);
				break;
			case M_SELECT:
				btn.setChecked(false); blank.setChecked(false); select.setChecked(true);
				setApplyable(true);
				break;
			}
		}
		return super.action(e, arg);
	}	

	public boolean doApplyAction()
	{
		if ( btn.isChecked() )
			props.navmode = M_BUTTON;
		else if ( blank.isChecked() )
			props.navmode = M_BLANK;
		else if ( select.isChecked() )
			props.navmode = M_SELECT;
		return true;
	}
}