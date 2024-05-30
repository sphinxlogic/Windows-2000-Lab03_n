//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.Insets;
import java.awt.Event;
import java.awt.Image;
import java.awt.Dimension;
import com.ms.ui.*;
import com.ms.fx.*;

public class TexturePnl extends UIPanel implements SDKConsts
{
	private FxGraphics dragGraf;
	private int mode;
	private FxTexture cross;
	private FxRubberPen rubber;
	private int xprev, yprev, xcur, ycur;
	private boolean snapto;

	public TexturePnl()
	{
		setLayout(new UIBorderLayout());
		setBackground(new FxColor(180,135,148));
		xprev = 20; yprev = 20; xcur = 180; ycur = 220;
		snapto = false;

		//
		// Create FxRubberPen
		//
		rubber = new FxRubberPen(new FxColor(180,135,148));

		//
		// Create FxTexture for drawing
		//
		// L_LEFT, L_TOP, L_RIGHT, L_BOTTOM define partitioning of texture
		//
		cross = new FxTexture(SDKImages.get(CROSS), FxTexture.STRETCH_NONE, 
							  L_LEFT, L_TOP, L_RIGHT, L_BOTTOM, false);

		// set partial texture mode
		cross.setSnapDraw(snapto);
	}

	/*************************************************************************
	
	setMode() - method for setting texture stretch mode

	*************************************************************************/
	public void setMode(int mode)
	{
		cross.setStretch(mode);
		cross.setSnapDraw(snapto);
		repaint();
	}

	/*************************************************************************

	setSnapTo() - method for enabling/disabling drawing of partial textures

	*************************************************************************/
	public void setSnapTo(boolean set)
	{
		snapto = set;
		cross.setSnapDraw(set);
		repaint();
	}

	/*************************************************************************

	setTile() - method for enabling/disabling tiling

	*************************************************************************/
	public void setTile(boolean set)
	{
		cross.setPinOrigin(set);
		// don't need to repaint if Tiling is being deselected
		if ( set ) {
			cross.setSnapDraw(false);
			repaint();
		}
		else
			cross.setSnapDraw(snapto);
	}

	/*************************************************************************

	mouseDown(), mouseDrag() - uses FxRubberPen to draw outline of where
		FxTexture will be drawn, draws FxTexture on mouseUp()

	*************************************************************************/
	public boolean mouseDown(Event evt, int x, int y)
	{
		if ( (xprev != x) || (yprev != y) ) {
			xprev = x;
			yprev = y;
		}
		dragGraf = getGraphics();
		dragGraf.setColor(rubber);
		return true;
	}

	public boolean mouseDrag(Event evt, int x, int y)
	{
		SortPoints pt = new SortPoints(xprev, yprev, x, y);
		dragGraf.drawRect(pt.xStart, pt.yStart, pt.width, pt.height);
		return true;
	}
	
	public boolean mouseUp(Event evt, int x, int y)
	{
		if ( x < 0 ) x = 0;	if ( y < 0 ) y = 0;
		Dimension pnlsize = getSize();
		if ( x > pnlsize.width ) x = pnlsize.width;
		if ( y > pnlsize.height ) y = pnlsize.height;

        rubber.drawLast(dragGraf);
		dragGraf = null;
		
		if ( (xprev != x) || (yprev != y) ) {
			xcur = x;
			ycur = y;
		}
		repaint();
		return true;
	}

	/*************************************************************************

	paint() - draw FxTexture

	*************************************************************************/
	public void paint(FxGraphics fxg)
	{
		Dimension pnlsize = getSize();
		SortPoints pt;
		pt = new SortPoints(xprev, yprev, xcur, ycur);

		// Only draw minimum size
		if ( pt.width < 45 )
			pt.width = 45;
		if ( pt.height < 65 )
			pt.height = 65;

		// Don't draw passed panel boundary
		if ( (pt.xStart + pt.width) > pnlsize.width )
			pt.xStart = pnlsize.width - pt.width;
		if ( (pt.yStart + pt.height) > pnlsize.height )
			pt.yStart = pnlsize.height - pt.height;

		//
		// Draw FxTexture
		//
		fxg.setColor(cross);
		fxg.fillRect(pt.xStart, pt.yStart, pt.width, pt.height);
	}
}

class SortPoints
{
	public int xStart, yStart, width, height;

	public SortPoints(int xStart, int yStart, int xEnd, int yEnd)
	{
		width = Math.abs(xEnd - xStart);
		height = Math.abs(yEnd - yStart);

		// Assume Start < End
		this.xStart = xStart;
		this.yStart = yStart;
		if ( xStart > xEnd ) this.xStart = xEnd;
		if ( yStart > yEnd ) this.yStart = yEnd;
	}
}

