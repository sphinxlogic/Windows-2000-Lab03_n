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