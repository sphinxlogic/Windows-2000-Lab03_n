// Copyright(C) 1997 Microsoft Corporation All rights reserved.

import java.awt.*;
import java.awt.event.* ;
import com.ms.util.* ;
import com.ms.fx.* ;

/**
* SampleIMEWindow is the UI for SampleIME.
* SampleIMEWindow is a composition window. You can set the composition
* string, and SampleIMEWindow will display it.
* SampleIMEWindow also contains a button for activating/deactivating
* the SampleIME. 
*/
public class SampleIMEWindow extends Window
    implements MouseListener, MouseMotionListener
{
    Frame frame ;
        // The attached frame, used for creating Window.
    StringBuffer m_str ;
        // The composition string to be displayed.
    SampleIME m_ime ;
        // The attached SampleIME.
    Rectangle m_ButtonRect ;
    Font font ;
    FontMetrics fm ;

    int preferedWidth ;
    int preferedHeight ;

    int m_PressX ;
    int m_PressY ;

    String activatedStr ;
        // The string to be displayed on the button when
        // the attached IME is activated.
    String deactivatedStr ;
        // The string to be displayed on the button when
        // the attached IME is deactivated.
    /**
     * @param ime, the IME which attached to the SampleIMEWindow
     * @param c, the attached Frame.
     */
    public SampleIMEWindow( SampleIME ime, Frame c )
    {       
        super( c ) ;
        
        m_ime = ime ;
        this.frame = c ;
        addMouseListener( this ) ;
        addMouseMotionListener( this ) ;
        
        m_ButtonRect = new Rectangle( 4, 4, 21, 21 ) ;
        preferedWidth = 100 ;
        preferedHeight = 60 ;

        activatedStr = "U" ;    // stands for "Unicode"
        deactivatedStr = "E" ;  // stands for "English"
        setBackground( Color.lightGray ) ;
    }

    /**
     * Set the string to be displayed in the composition window.
     * @param str, the string to be displayed.
     */
    public void setCompositionString( StringBuffer str )
    {
        m_str = str ;
    }

    /**
     * Make the window a top-level one and show the window.
     */
    public void show()
    {
        IFxSystemInterface systemInterface = FxToolkit.getSystemInterface() ;
        systemInterface.setOnTop( this, true ) ;    
        super.show() ;
    }
    
    /**
     * Display the status of composition.
     */
    public void paint( Graphics g )
    {
        // Draw the background of the IME composition window.
        g.drawRect( 0,0, preferedWidth - 1, preferedHeight - 1 ) ;
        g.drawRect( 2,2, preferedWidth - 5, preferedHeight - 5 ) ;
        g.drawRect( 4,4, 21, 21 ) ;
        g.setColor( Color.white ) ;
        g.drawLine( 1,1, preferedWidth - 2, 1 ) ;
        g.drawLine( 1,1, 1, preferedHeight - 2 ) ;
        g.setColor( Color.gray ) ;
        g.drawLine( 1, preferedHeight - 2, preferedWidth-2, preferedHeight - 2 ) ;
        g.drawLine( preferedWidth - 2, 1, preferedWidth-2, preferedHeight - 2 ) ;

        // Draw the IME activate/deactivate button.
        g.setColor( Color.white ) ;
        g.drawLine( 4,4, 25, 4 ) ;
        g.drawLine( 4,4, 4, 25 ) ;
        g.setColor( Color.gray ) ;
        g.drawLine( 25, 4, 25, 25 ) ;
        g.drawLine( 4, 25, 25, 25 ) ;

        g.setColor( Color.red ) ;
        if ( m_ime.isActivated() )
            g.drawString( activatedStr, 10, 20 ) ;
        else
            g.drawString( deactivatedStr, 10, 20 ) ;
        g.setColor( Color.black ) ;
        if ( m_str != null )
            g.drawString( m_str.toString() , 30, 20 ) ;
    }

    /**
     * Set the position of the SampleIMEWindow.
     */
    public void setPos(int x, int y)
    {
        // If font information is available, we will make use of
        // it to position the window in the lower right corner
        // of the caret.
        if ( fm != null )
            setLocation( x + 10, y + fm.getHeight() * 3 / 2 ) ;
        else        
            setLocation( x, y ) ;
        resize( preferedWidth, preferedHeight ) ;
    }

    /**
    * Set the size of the SampleIMEWindow.
    */
    public void setSize( int width, int height )
    {
        preferedWidth = width ;
        preferedHeight = height ;
        resize( width, height ) ;
    }

    /**
    * Set the string to be displayed on the button when
    * the attached IME is activated. This should be
    * an one character string.
    */
    public void setActivatedStr( String str )
    {
        activatedStr = str ;
    }

    /**
    * Set the string to be displayed on the button when
    * the attached IME is deactivated. This should be
    * an one character string.
    */
    public void setDeactivatedStr( String str )
    {
        deactivatedStr = str ;
    }

    public void mouseClicked( MouseEvent event ) {}

    public void mouseEntered( MouseEvent event ) {}

    public void mouseExited( MouseEvent event ) {}

    public void mousePressed( MouseEvent event )
    {
        if ( m_ButtonRect.contains( event.getX(), event.getY() ) )
        {
            if ( m_ime.isActivated() )
                m_ime.deactivate() ;
            else
                m_ime.activate() ;
            repaint() ;
        } else
        {
            m_PressX = event.getX() ;
            m_PressY = event.getY() ;
        }
    }

    public void mouseReleased( MouseEvent event ) {}

    public void mouseDragged( MouseEvent event )
    {
        if ( m_ButtonRect.contains( event.getX(), event.getY() ) )
            return ;

        Point curPos = getLocation() ;
        setLocation( curPos.x + event.getX() - m_PressX , curPos.y + event.getY() - m_PressY ) ;
    }

    public void mouseMoved( MouseEvent event ) {}

    public void setFont( Graphics g, Font font )
    {
        this.font = font ;
        fm = g.getFontMetrics( font ) ;
    }    
}
