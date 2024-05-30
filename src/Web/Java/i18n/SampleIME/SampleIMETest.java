// Copyright(C) 1997 Microsoft Corporation All rights reserved.
//******************************************************************************
// SampelIMETest.java:  Applet
// When running this applet, click on the TextField, and type the hex value of
//   the unicode, the corresponding unicode character will go to
//   the TextField.
// The composition window could be dragged. When you click on the button on
//   the left of the composition window, you could enable/disable the IME.
//******************************************************************************
import java.applet.*;
import java.awt.*;
import java.awt.event.* ;
import SampleIMETestFrame;
import com.ms.util.InputMethod.* ;
//import com.ms.awt.peer.* ;

import com.ms.ui.* ;

//==============================================================================
// Main Class for applet SampleIMETest
//
//==============================================================================
public class SampleIMETest extends Applet implements ActionListener
{
    // STANDALONE APPLICATION SUPPORT:
    //      m_fStandAlone will be set to true if applet is run standalone
    //--------------------------------------------------------------------------
    boolean m_fStandAlone = false;

    private InputManagerListener imm ;
        // System Default InputMethod Manager.
    private InputMethodListener ime ;
        // Sample IME.
        
    // STANDALONE APPLICATION SUPPORT
    //  The main() method acts as the applet's entry point when it is run
    // as a standalone application. It is ignored if the applet is run from
    // within an HTML page.
    //--------------------------------------------------------------------------
    public static void main(String args[])
    {
        // Create Toplevel Window to contain applet UIInputMethod
        //----------------------------------------------------------------------
        SampleIMETestFrame frame = new SampleIMETestFrame("UIInputMethod");

        // Must show Frame before we size it so insets() will return valid values
        //----------------------------------------------------------------------
        frame.show();
        //frame.setVisible( false );
        frame.hide();
        frame.resize(frame.insets().left + frame.insets().right  + 400,
                     frame.insets().top  + frame.insets().bottom + 300);

        // The following code starts the applet running within the frame window.
        // It also calls GetParameters() to retrieve parameter values from the
        // command line, and sets m_fStandAlone to true to prevent init() from
        // trying to get them from the HTML page.
        //----------------------------------------------------------------------
        SampleIMETest applet_UIInputMethod = new SampleIMETest();

        frame.add("Center", applet_UIInputMethod);
        applet_UIInputMethod.m_fStandAlone = true;
        applet_UIInputMethod.init();
        applet_UIInputMethod.start();
        frame.show();
    }

    // UIInputMethod Class Constructor
    //--------------------------------------------------------------------------
    public SampleIMETest()
    {
        // TODO: Add constructor code here
    }

    // APPLET INFO SUPPORT:
    //      The getAppletInfo() method returns a string describing the applet's
    // author, copyright date, or miscellaneous information.
        //--------------------------------------------------------------------------
    public String getAppletInfo()
    {
        return "Name: UIInputMethod\r\n" +
               "Created with Microsoft Visual J++ Version 1.0";
    }


    // The init() method is called by the AWT when an applet is first loaded or
    // reloaded.  Override this method to perform whatever initialization your
    // applet needs, such as initializing data structures, loading images or
    // fonts, creating frame windows, setting the layout manager, or adding UI
    // components.
    //--------------------------------------------------------------------------
    public void init()
    {
        resize(320, 240);

        // Create TextField and TextArea.
        Panel panel1 = new Panel() ;
        TextField text = new TextField( 20 ) ;
        text.setFont( new Font( "Courier", Font.PLAIN, 20 ) ) ;
        panel1.add( new Label( "TextField:" ) ) ;
        panel1.add( text ) ;

        Panel panel2 = new Panel() ;
        TextArea textArea = new TextArea( 5, 20 ) ;
        panel2.add( new Label( "TextArea:" ) ) ;
        textArea.setFont( new Font( "Courier", Font.PLAIN, 20 ) ) ;
        panel2.add( textArea ) ;
        add( panel1 ) ; add( panel2 ) ;
        Button SampleIMEButton = new Button( "Click here to activate Sample IME" ) ;
        SampleIMEButton.addActionListener( this ) ;

        add( SampleIMEButton ) ;
    }

    // Place additional applet clean up code here.  destroy() is called when
    // when you applet is terminating and being unloaded.
    //-------------------------------------------------------------------------
    public void destroy()
    {
        // TODO: Place applet cleanup code here
    }

    // UIInputMethod Paint Handler
    //--------------------------------------------------------------------------
    public void paint(Graphics g)
    {
        //if ( ime != null )
        //    ime.activate() ;
    }

    //      The start() method is called when the page containing the applet
    // first appears on the screen. The AppletWizard's initial implementation
    // of this method starts execution of the applet's thread.
    //--------------------------------------------------------------------------
    public void start()
    {
        // TODO: Place additional applet start code here
    }
    
    //      The stop() method is called when the page containing the applet is
    // no longer on the screen. The AppletWizard's initial implementation of
    // this method stops execution of the applet's thread.
    //--------------------------------------------------------------------------
    public void stop()
    {
        if ( ime != null )
        {
            ime.deactivate() ;
            imm.setInputMethod( null ) ;
            imm.removeInputMethod( ime ) ;  
                // Remove the IME from the IMM maintained list. Otherwise
                // IME will be still available for other applets.
        }
    }
    // TODO: Place additional applet code here


    void activateIME()
    {
        System.out.println( "activateIME" ) ;
        if ( ime == null )
        {
            // Get DefaultInputManager.
            imm = com.ms.lang.SystemX.getDefaultInputManager() ;
            com.ms.lang.SystemX.setInputManager( imm, true ) ;
            
            if ( imm != null )
            {
                // Create a new IME.
                ime = new SampleIME() ;
                // Set the SampleIME as current IME.
                imm.setInputMethod( ime ) ;
                ime.activate() ;
            }
        } else
        {
            imm.setInputMethod( ime ) ;
            ime.activate() ;        
        }
    }
    
    public void actionPerformed(ActionEvent e)
    {
        activateIME() ;
    }
}

