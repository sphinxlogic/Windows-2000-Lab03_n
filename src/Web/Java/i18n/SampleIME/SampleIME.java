// Copyright(C) 1997 Microsoft Corporation All rights reserved.

import java.awt.*;
import com.ms.lang.SystemX ;
import com.ms.util.* ;
import java.awt.event.KeyEvent ;

import com.ms.util.InputMethod.*;
import com.ms.ui.* ;
import com.ms.fx.* ;

// This is a sample IME which allows user to input unicode characters
// by typing the hex value of unicode characters.
//
// It demostrate that how to use the InputMethodCallback.handleIMEChar()
// to put a converted unicode character( composition character )
// back into the Java side and InputMethodCallback.handleIMEMessage() to
// send IME message to the system.
//
// This SampleIME also demostrates how to write a level-2 IME, whose composition
// window will be shown near the position of input caret.

public class SampleIME implements com.ms.util.InputMethod.InputMethodListener
{
    SampleIMEWindow m_uiInput ;
        // UI window for Sample IME.
    StringBuffer m_CompStr ;
        // Composition string.
    boolean m_bActivate = false ;
        // the flag to indicate if the IME is activated or not.
        
    IUIComponent   uiComp ;
        // Visible componet for UI.
    Component       awtComp ;
        // Visible componet for AWT.
    Component topContainer ;
        // The top container in the hierarchy of the visible component.
        // We will use this as a parent when we create the composition window.
    Font font ;        
        // Font used in the composition window.
        
    public SampleIME()
    {
        m_CompStr = new StringBuffer( 20 ) ;
    }

    protected void finalize() throws Throwable
    {
        if ( m_uiInput != null )
            m_uiInput.dispose() ;
    }

    /**
     * This will be called by InputManagerListener.handledKey(). When activated,
     * Java IME should use this method to take keystroke from system, and decides 
     * if it wants to take this keystroke.
     */
    public boolean handledKey( InputMethodCallback imeCallback, long when, int keyCode, int keyChar, int state )
    {
        if ( !m_bActivate || ( ( state & InputManagerListener.DOWN ) != InputManagerListener.DOWN ) )
        {
            // If not activated or this is a KeyUp, just return.
            return false ;
        }

        char ch = (char)keyChar ;
            // Get the input from user.

        if ( ( m_CompStr.length() > 0 ) && ( keyCode == KeyEvent.VK_BACK_SPACE ) )
        {
            // Processing of BackSpace.
            StringBuffer newCompStr = new StringBuffer();

            // Delete the last character.
            for ( int i = 0 ; i < m_CompStr.length() - 1 ; i++ )
                newCompStr.append( m_CompStr.charAt( i ) ) ;
            m_CompStr = newCompStr ;
            
            if ( m_uiInput != null )
                m_uiInput.setCompositionString( m_CompStr ) ;

            // Generate an IMECompositionMessage to inform imeCallback that
            // the composition is changed.
            imeCallback.handleIMEMessage( 
                new IMECompositionMessage( IMECompositionMessage.CHANGE_COMPOSITION, keyCode, keyChar, m_CompStr.toString() ) ) ;
            return true ;   
                // Return true to tell InputManagerListener not to pass this keystroke
                // back to system.                
        }

        if ( ( m_CompStr.length() > 0 ) && ( keyCode == KeyEvent.VK_ENTER ) )
        {
            // When there are characters in m_CompStr, and the user hits
            // the Enter key, it means that a composition is completed.

            // Converted the composition string into a unicode character.
            int unicode = Integer.valueOf( m_CompStr.toString(), 16 ).intValue() ;
            char unicodeChar = ( char ) unicode ;

            // Pass the composed character back to the system.
            imeCallback.handleIMEChar( when, unicodeChar, state ) ;

            // Redraw the composition window.
            m_CompStr = new StringBuffer() ;
            if ( m_uiInput != null )
                m_uiInput.setCompositionString( m_CompStr ) ;
                
            // Composition is completed.
            imeCallback.handleIMEMessage( 
                new IMECompositionMessage( IMECompositionMessage.END_COMPOSITION ) ) ;

            return true ;
                // Return true to tell InputManagerListener not to pass this keystroke
                // back to system.                            
        }
                
        if ( ( ch >= 'a' && ch <= 'f' ) ||  
             ( ch >= 'A' && ch <= 'F' ) || 
             ( ch >= '0' && ch <= '9' ) )
        {
            if ( m_CompStr.length() == 0 )
            {
                // Generate an IMECompositionMessage to inform imeCallback that a new
                // composition is started.
                imeCallback.handleIMEMessage( new IMECompositionMessage( IMECompositionMessage.START_COMPOSITION ) ) ;
            }
            // Update the composition string and the display of compositon window.
            if ( m_CompStr.length() < 4 )
            {
                m_CompStr.append( ch ) ;
                // Generate an IMECompositionMessage to inform imeCallback that
                // the composition is changed. Note that we pass the composition string
                // in the last parameter of IMECompositionMessage.
                imeCallback.handleIMEMessage( 
                    new IMECompositionMessage( IMECompositionMessage.CHANGE_COMPOSITION, keyCode, keyChar, m_CompStr.toString() ) ) ;
            }           
            return true ;   // End of processing.
        }
        // SampleIME is not interested in this keystroke, just return it to the system
        // as a normal keyboard input.
        return false ;  // Pass it back to component.
    }

    // Handle InputMethodMessage: to draw default IME UI.
    // When we use InputMethodCallback.handleIMEMessage() to pass the IME messages to
    // the system, and the target application is not interested in IME messages( either
    // by not implementing InputMethodMessageListener, or return false in 
    // InputMethodMessageListener.handleIMEMessage() ), all of the IME messages 
    // will fall back here.
    public void handleIMEMessage( InputMethodMessage IMEMessage )
    {
        if ( m_uiInput != null )
           m_uiInput.repaint() ;
    }

    public void paint(Graphics g)
    {
        // Don't worry about this right now.
        // This is intended to support inline IME.
    }

    public void setVisibleComponent(Component c)
    {    
        awtComp = c ;

        topContainer = c ;
        
        Component temp = topContainer ;
        while ( temp != null )
        {
            topContainer = temp ;
            temp = temp.getParent() ;
        }
        
        if ( topContainer instanceof Frame )
            if ( m_uiInput == null )
            {
                m_uiInput = new SampleIMEWindow( this, ( Frame ) topContainer ) ;
                m_uiInput.setCompositionString( m_CompStr ) ;
                m_uiInput.show() ;
                m_uiInput.resize( 200, 100 ) ;
                m_uiInput.setActivatedStr( "U" ) ;
                    // Create the UI for this IME.
            }
    }

    // Sets the component c as the component where the IME is seen on the 
    // screen. In Microsoft's VM implementation, java.awt.TextField and 
    // java.awt.TextArea will make use of this to provide IME level 2 support.
    public void setVisibleComponent( IUIComponent c)
    {
        uiComp = c ;
        
        topContainer = c.getRoot().getHost() ;  // Get the host in the AWT side.

        // Calcuate the insets of the top level guy in AWT.

        // Find the top container.
        Component temp = topContainer ;
        while ( temp != null )
        {
            topContainer = temp ;
            temp = temp.getParent() ;
        }

        if ( m_uiInput == null )
            if ( topContainer instanceof Container )
            {
                // Create an IME composition window, which will be a child of
                // the topContainer.
                m_uiInput = new SampleIMEWindow( this, ( Frame ) topContainer ) ;
                m_uiInput.setCompositionString( m_CompStr ) ;
                m_uiInput.show() ;
                m_uiInput.resize( 200, 100 ) ;
                m_uiInput.setActivatedStr( "U" ) ;
            }               
    }    

    // Set the position of composition window.
    // In Microsoft's VM implementation, java.awt.TextField and 
    // java.awt.TextArea will make use of this to provide IME level 2 support.
    public void setPos(int x, int y)
    {
        if ( m_uiInput == null )
            return ;
            
        Point scrnPos ;
        if ( uiComp != null )
        {           
            // We have a visible component, set the composition window
            // near the visible component( IME level 2 support ).
            scrnPos = uiComp.getLocationOnScreen() ;
                // Get the screen position of the current component.                
            m_uiInput.setPos( x + scrnPos.x , y + scrnPos.y ) ;
                // Before we pass the position to IME, we have to translate
                // the ( x,y ) position into the client area of the top container.
        } 
        else if ( awtComp != null )
        {
            scrnPos = awtComp.getLocationOnScreen() ;
            m_uiInput.setPos( x, y ) ;
        }
        else
            m_uiInput.setPos( x, y ) ;
        
    }

    public Dimension size(Graphics g)
    {
        // Don't worry about this right now.
        // This is intended to support inline IME.
        return null ;
    }
    
    // Acticate the IME.
    public void activate()
    {
        show() ;
        m_bActivate = true ;
    }

    // Deactivate the IME.
    public void deactivate()
    {
        hide() ;
        m_bActivate = false ;
    }        

    // Show the IME UI.
    public void show()
    {
        if ( m_uiInput != null )
            m_uiInput.show() ;
    }

    // Hide the IME UI.
    public void hide()
    {
        if ( m_uiInput != null )
            //m_uiInput.setVisible( false ) ;
            m_uiInput.hide() ;
    }

    // Return true if the IME is activated.
    public boolean isActivated()
    {
        return m_bActivate ;
    }

    // Return the name of this IME.
    public String getName()
    {
        return "Sample IME" ;
    }

    // Set the font used in the composition window.
    public void setFont( Font font )
    {
        if ( this.font == font )
            return ;
        this.font = font ;
        if ( m_uiInput != null )
        {
            if ( uiComp != null )
                m_uiInput.setFont( uiComp.getGraphics().getBaseGraphics(), font ) ;
        }
    }
}
