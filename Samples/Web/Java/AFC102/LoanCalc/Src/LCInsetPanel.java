//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.Insets;
import com.ms.ui.*;

public class LCInsetPanel extends UIPanel
{
	private int t,l,b,r;

	public LCInsetPanel() { this(0,0,0,0); }

	public LCInsetPanel(int t, int l, int b, int r)
	{ 
		super();
		this.t = t; this.l = l; this.b = b; this.r = r;
	}

	public Insets getInsets() { return new Insets(t,l,b,r); }
}

class BL extends LCInsetPanel
{
	public BL() { this(0,0,0,0); }

	public BL(IUIComponent comp) { this(comp,0,0,0,0); }

	public BL(IUIComponent comp, int t, int l, int b, int r)
	{ 
		this(t,l,b,r);
		add(comp, "center");
	}

	public BL(int t, int l, int b, int r)
	{ 
		super(t,l,b,r);
		setLayout(new UIBorderLayout());
	}
}

class HSL extends LCInsetPanel
{
	public HSL() { this(100, 0,0,0,0); }

	public HSL(IUIComponent compnw, IUIComponent compse)
	{
		this(compnw, compse, 100, 0,0,0,0);
	}

	public HSL(IUIComponent compnw, IUIComponent compse, int split)
	{
		this(compnw, compse, split, 0,0,0,0);
	}

	public HSL(IUIComponent compnw, IUIComponent compse,
								int split, int t, int l, int b, int r)
	{ 
		this(split, t,l,b,r);
		add(compnw, "nw");
		add(compse, "se");
	}

	public HSL(int split, int t, int l, int b, int r)
	{ 
		super(t,l,b,r);
		setLayout(new UISplitLayout(UISplitLayout.HORIZONTAL, split));
	}
}

class VSL extends LCInsetPanel
{
	public VSL() { this(100, 0,0,0,0); }

	public VSL(IUIComponent compnw, IUIComponent compse)
	{
		this(compnw, compse, 100, 0,0,0,0);
	}

	public VSL(IUIComponent compnw, IUIComponent compse, int split)
	{
		this(compnw, compse, split, 0,0,0,0);
	}

	public VSL(IUIComponent compnw, IUIComponent compse,
								int split, int t, int l, int b, int r)
	{ 
		this(split, t,l,b,r);
		add(compnw, "nw");
		add(compse, "se");
	}

	public VSL(int split, int t, int l, int b, int r)
	{ 
		super(t,l,b,r);
		setLayout(new UISplitLayout(0, split));
	}
}

class FocusUIPanel extends UIPanel
{
	private boolean firsttime;
	private LCCallbacks callback;

	public FocusUIPanel() { super(); firsttime = true; }

	public void addNotify()
	{
		super.addNotify();
		if( firsttime ) { firsttime = false; setFocus(); }
	}

	// This method will be overridden by subclasses of FocusUIPanel who desire 
	//  setting focus
	public void setFocus() { }
}
