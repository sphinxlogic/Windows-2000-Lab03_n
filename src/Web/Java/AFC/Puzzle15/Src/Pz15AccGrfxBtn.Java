//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.Image;
import java.awt.Event;
import com.ms.ui.*;

public class Pz15AccGrfxBtn extends UIPushButton implements Pz15Consts
{
	public HotTrkGrfx grfx;
	private Pz15Callbacks pzctrl;
	private String name;

	public Pz15AccGrfxBtn(int i, Pz15Callbacks pzctrl)
	{
		super(new HotTrkGrfx(Pz15Images.get(i), Pz15Images.getHot(i), UIStatic.CENTERED),
				UIPushButton.RAISED | UIPushButton.THICK);
		IUIComponent comp = getHeader();

		if ( comp instanceof HotTrkGrfx )
			grfx = (HotTrkGrfx)comp;

		name = "Button #" + (i+1);
		this.pzctrl = pzctrl;
	}

	public Pz15AccGrfxBtn()
	{
		super("");
		name = "Blank Space";
	}

	public String getName()
	{
		return(name);
	}

	public void setFocused(boolean on)
	{
		if ( pzctrl.getNavMode() == M_SELECT )
			grfx.setImage(on ? grfx.hot : grfx.def);
		super.setFocused(on);
	}
}

class HotTrkGrfx extends UIGraphic implements Pz15Consts
{
	public Image def,hot;

	public HotTrkGrfx(Image def, Image hot, int style)
	{
		super(def, style);
		this.def = def;	this.hot = hot;
	}
}
