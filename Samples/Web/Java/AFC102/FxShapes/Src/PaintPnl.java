//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.Insets;
import java.awt.Event;
import java.awt.Image;
import java.awt.Point;
import java.awt.Dimension;
import java.awt.Rectangle;
import java.awt.Color;
import com.ms.ui.*;
import com.ms.fx.*;

public class PaintPnl extends UIPanel implements SDKConsts, IFxTextConstants
{
        private FxGraphics dragGraf;
        private int drawmode;
        private FxRubberPen rubber;
        private int xprev, yprev, xcur, ycur, penwidth, penstyle;
        private int previdx, curidx, numpoints;
        private Point points[] = new Point[MAX_POINTS];
        private FxStyledPen dash, dot;
        private FxPen bpen, tpen;
        private FxTexture texture, bg;
        private FxFont efont, rfont;
        private FxFormattedText ft_right;

        public PaintPnl()
        {
                setLayout(new UIBorderLayout());

                xprev = 40; yprev = 40; xcur = 180; ycur = 220;
                penwidth = INIT_WIDTH; numpoints = MAX_POINTS;
                drawmode = ID_LINE; penstyle = ID_SOLID;
                previdx = 0; curidx = 1;

                efont = new FxFont("Times New Roman", 0, 28);
                rfont = new FxFont("Times New Roman", 0, 20);

                points[0] = new Point(175,190); points[1] = new Point(175,50);
                points[2] = new Point(225,50);  points[3] = new Point(225,215);
                points[4] = new Point(175,265); points[5] = new Point(100,265);
                points[6] = new Point(50,215);  points[7] = new Point(100,190);
                points[8] = new Point(125,215); points[9] = new Point(150,215);

                // Create background texture
                bg = new FxTexture(SDKImages.get(BACKGROUND), FxTexture.STRETCH_NONE,
                                                        0, 0, -1, -1, false, 207,178,148);
                setBackground(BaseColor.getColor(bg));

                // Create rubber pen
                 rubber = new FxRubberPen(BaseColor.getColor(bg));

                // Create texture for textured pen
                texture = new FxTexture(SDKImages.get(TEXTURE), FxTexture.STRETCH_NONE,
                                                                        0, 0, -1, -1, false, 237,207,39);

                // Create all the Pens
                FxColor blue = new FxColor(0,0,255);
                bpen = new FxPen(INIT_WIDTH, blue);
                dash = new FxStyledPen(FxStyledPen.DASH, 1, blue);
                dot = new FxStyledPen(FxStyledPen.DOT, 1, blue);
                tpen = new FxPen(INIT_WIDTH, texture);

                // Create Formatted Text
                ft_right = new FxFormattedText(FT_HELLO);
                ft_right.setTextDirection(tdTB_RL);
                ft_right.setHorizAlign(htaCenter);
                ft_right.setVertAlign(vtaCenter);
                ft_right.setFont(rfont);
        }

        public void setPenStyle(int style, boolean repaint)
        {
                penstyle = style;
                if ( repaint )
                        repaint();
        }

        public void setDrawMode(int mode) { drawmode = mode; repaint(); }

        public void setPenWidth(int width) { penwidth = width; repaint(); }

        public void setNumPoints(int num) { numpoints = num; repaint(); }

        public boolean mouseDown(Event evt, int x, int y)
        {
                // Make sure we are within bounds of panel
                Dimension pnlsize = getSize();
                x = bindToPanel(x, pnlsize.width); y = bindToPanel(y, pnlsize.height);

                if ( drawmode != ID_POLY ) {
                        if ( (xprev != x) || (yprev != y) ) {
                                xprev = x;
                                yprev = y;
                        }
                }
                dragGraf = getGraphics();
                dragGraf.setColor(rubber);
                return true;
        }

        public boolean mouseDrag(Event evt, int x, int y)
        {
                SortPoints pt;
                int xStart, yStart;

                if ( drawmode != ID_POLY ) {
                        xStart = xprev; yStart = yprev;
                }
                else {
                        xStart = points[previdx].x; yStart = points[previdx].y;
                }

                // Make sure we are within bounds of panel
                Dimension pnlsize = getSize();
                x = bindToPanel(x, pnlsize.width); y = bindToPanel(y, pnlsize.height);

                switch ( drawmode ) {
                case ID_LINE:
                        dragGraf.drawLine(xStart, yStart, x, y);
                        break;

                case ID_POLY:
                        points[curidx] = new Point(x,y);
                        dragGraf.drawPolygon(MakeArray.x(points), MakeArray.y(points), numpoints);
                        break;

                case ID_FORMAT_TEXT:
                case ID_ELLIPSE:
                case ID_LINE_ELLIPSE:
                        pt = new SortPoints(xStart, yStart, x, y);
                        dragGraf.drawOval(pt.xStart, pt.yStart, pt.width, pt.height);
                        break;

                case ID_RECT:
                        pt = new SortPoints(xStart, yStart, x, y);
                        dragGraf.drawRect(pt.xStart, pt.yStart, pt.width, pt.height);
                        break;

                case ID_ROUNDRECT:
                        pt = new SortPoints(xStart, yStart, x, y);
                        dragGraf.drawRoundRect(pt.xStart, pt.yStart,
                                                                   pt.width,  pt.height,
                                                                   pt.width/6,pt.height/6);
                        break;
                }
                return true;
        }

        public boolean mouseUp(Event evt, int x, int y)
        {
                // Erase last thing drawn by rubber pen
        rubber.drawLast(dragGraf); dragGraf = null;

                // Make sure we are within bounds of panel
                Dimension pnlsize = getSize();
                x = bindToPanel(x, pnlsize.width); y = bindToPanel(y, pnlsize.height);

                if ( drawmode != ID_POLY ) {
                        if ( (xprev != x) || (yprev != y) ) {
                                xcur = x;
                                ycur = y;
                        }
                }
                else {
                        if ( (points[previdx].x != x) || (points[previdx].y != y) ) {
                                points[curidx].x = x;
                                points[curidx].y = y;
                        }
                        previdx = curidx;
                        curidx = ((curidx+1) % numpoints);
                }
                repaint();
                return true;
        }

        private int bindToPanel(int coord, int size)
        {
                int inset;

                if ( drawmode == ID_FORMAT_TEXT )
                        inset = FT_INSET;
                else
                        inset = penwidth;

                if ( coord < inset )
                        return inset;
                else if ( coord > (size - inset) )
                        return size - inset;
                else
                        return coord;
        }

        public void paint(FxGraphics fxg)
        {
                SortPoints pt;
                FxEllipse oval;

                switch ( penstyle ) {
                case ID_SOLID: bpen.setWidth(penwidth); fxg.setColor(bpen); break;
                case ID_DASH: fxg.setColor(dash); break;
                case ID_DOT: fxg.setColor(dot); break;
                case ID_TEXTURE:
                        if ( penwidth == 2 )
                                tpen.setWidth(3);
                        else
                                tpen.setWidth(penwidth);
                        fxg.setColor(tpen); break;
                }

                switch ( drawmode ) {
                case ID_LINE:
                        fxg.drawLine(xprev, yprev, xcur, ycur);
                        break;

                case ID_POLY:
                        fxg.drawPolygon(MakeArray.x(points), MakeArray.y(points), numpoints);
                        break;

                case ID_ELLIPSE:
                        pt = new SortPoints(xprev, yprev, xcur, ycur);
                        fxg.drawOval(pt.xStart, pt.yStart, pt.width, pt.height);
                        break;

                case ID_RECT:
                        pt = new SortPoints(xprev, yprev, xcur, ycur);
                        fxg.drawRect(pt.xStart, pt.yStart, pt.width, pt.height);
                        break;

                case ID_ROUNDRECT:
                        pt = new SortPoints(xprev, yprev, xcur, ycur);
                        fxg.drawRoundRect(pt.xStart, pt.yStart, pt.width, pt.height,
                                              pt.width/6, pt.height/6);
                        break;

                case ID_FORMAT_TEXT:
                        Rectangle rect;
                        Dimension size = getSize();

                        pt = new SortPoints(xprev, yprev, xcur, ycur);

                        // Re-originate ellipse
                        pt.xStart -= 10; pt.yStart += 10;


                        if ( pt.width < FT_MIN_WIDTH ) {
                                pt.width = FT_MIN_WIDTH;
                                if ( (pt.xStart + FT_MIN_WIDTH + FT_INSET + 20) > size.width )
                                        pt.xStart = size.width - FT_MIN_WIDTH - FT_INSET - 20;
                        }

                        if ( pt.height < FT_MIN_HEIGHT ) {
                                pt.height = FT_MIN_HEIGHT;
                                if ( (pt.yStart + FT_MIN_HEIGHT + FT_INSET ) > (size.height + 10) )
                                        pt.yStart = size.height - FT_MIN_HEIGHT - FT_INSET + 10;
                        }

//                         fxg.setColor(FxColor.red);
                        fxg.setColor(Color.red);

                        // Center vertical text in ellipse
                        int xc = 2*(pt.xStart + pt.width/2);
                        int yc = 2*(pt.yStart + pt.height/2 - 10);
                        rect = new Rectangle(xc, yc);
                        ft_right.setBounding(rect, true);
                        ft_right.paint(fxg, 0, ft_right.getLength(), 0);

                        // Draw circular Formatted Text
                        fxg.setColor(Color.blue);
                        oval = new FxEllipse(pt.xStart, pt.yStart, pt.width, pt.height);
                        fxg.setFont(efont);
                        rect = new Rectangle(0, 0, size.width, size.height);
                        fxg.drawStringFormatted("Hello, World.", rect, htaStretch,
                                                                        vtaCenter, wwNone, true, 0, null, oval, false);
                        break;

                case ID_LINE_ELLIPSE:
                        pt = new SortPoints(xprev, yprev, xcur, ycur);

                        oval = new FxEllipse(pt.xStart, pt.yStart, pt.width, pt.height);

                        int nPoints = oval.getBorderLength();
                        FxColor cols[] = new FxColor[4];
                        cols[0] = new FxColor(255,255,0);       // yellow
                        cols[1] = new FxColor(0,0,0);           // black
                        cols[2] = new FxColor(255,255,255);     // white
                        cols[3] = new FxColor(0,255,255);       // cyan
                        for ( int j = 0; j < nPoints; j++ ) {
                                fxg.setColor(cols[j%4]);
                                Point p = oval.getPoint(j);
                                fxg.drawLine(p.x, p.y, p.x+10, p.y-10);
                        }
                        break;
                }
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

final class MakeArray implements SDKConsts
{
        public static final int[] x(Point[] points)
        {
                int[] elems = new int[MAX_POINTS];

                for ( int i = 0; i < MAX_POINTS; i++ )
                        elems[i] = points[i].x;

                return elems;
        }

        public static final int[] y(Point[] points)
        {
                int[] elems = new int[MAX_POINTS];

                for ( int i = 0; i < MAX_POINTS; i++ )
                        elems[i] = points[i].y;

                return elems;
        }
}