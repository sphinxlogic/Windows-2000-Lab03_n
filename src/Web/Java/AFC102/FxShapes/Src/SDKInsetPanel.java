//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.Insets;
import com.ms.ui.*;

public class SDKInsetPanel extends UIPanel
{
	private int t,l,b,r;

	public SDKInsetPanel() { this(0,0,0,0); }

	public SDKInsetPanel(int t, int l, int b, int r)
	{ 
		super();
		this.t = t; this.l = l; this.b = b; this.r = r;
	}

	public Insets getInsets() { return new Insets(t,l,b,r); }
}

class SDKInsetPanelVFL extends SDKInsetPanel
{
	public SDKInsetPanelVFL(int t, int l, int b, int r)
	{ 
		super(t,l,b,r);
		setLayout(new UIVerticalFlowLayout(UIVerticalFlowLayout.FILL, 0));
	}
}

class SDKInsetPanelGL extends SDKInsetPanel
{
	public SDKInsetPanelGL(int t, int l, int b, int r)
	{ 
		super(t,l,b,r);
		setLayout(new UIGridLayout(0, 1, 0, 1));
	}
}

class SDKInsetPanelBL extends SDKInsetPanel
{
	public SDKInsetPanelBL() { this(0,0,0,0); }

	public SDKInsetPanelBL(IUIComponent comp) { this(comp,0,0,0,0); }

	public SDKInsetPanelBL(IUIComponent comp, int t, int l, int b, int r)
	{ 
		this(t,l,b,r);
		add(comp, "center");
	}

	public SDKInsetPanelBL(int t, int l, int b, int r)
	{ 
		super(t,l,b,r);
		setLayout(new UIBorderLayout());
	}
}

class SDKInsetPanelHSL extends SDKInsetPanel
{
	public SDKInsetPanelHSL() { this(100, 0,0,0,0); }

	public SDKInsetPanelHSL(IUIComponent compnw, IUIComponent compse)
	{
		this(compnw, compse, 100, 0,0,0,0);
	}

	public SDKInsetPanelHSL(IUIComponent compnw, IUIComponent compse, int split)
	{
		this(compnw, compse, split, 0,0,0,0);
	}

	public SDKInsetPanelHSL(IUIComponent compnw, IUIComponent compse,
								int split, int t, int l, int b, int r)
	{ 
		this(split, t,l,b,r);
		add(compnw, "nw");
		add(compse, "se");
	}

	public SDKInsetPanelHSL(int split, int t, int l, int b, int r)
	{ 
		super(t,l,b,r);
		setLayout(new UISplitLayout(UISplitLayout.HORIZONTAL, split));
	}
}

class SDKInsetGroup extends UIGroup
{
	private int t, l, b, r;

	public SDKInsetGroup(String title, int t, int l, int b, int r)
	{
		super(title);
		this.t = t; this.l = l; this.b = b; this.r = r;
	}

	public Insets getInsets() { return new Insets(t, l, b, r); }
}