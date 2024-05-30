/*++
Copyright (c) 1997-2000  Microsoft Corporation
Module Name:
       appctrls2.java
Abstract:

Author:

Notes:
Revision History:
--*/
//------------------------------------------------------------------------------
// appctrls2.java:
//		Implementation for container control initialization class appctrls2
//
// WARNING: Do not modify this file.  This file is recreated each time its
//          associated .rct/.res file is sent through the Java Resource Wizard!
//
// This class can be use to create controls within any container, however, the
// following describes how to use this class with an Applet.  For addtional
// information on using Java Resource Wizard generated classes, refer to the
// Visual J++ 1.1 documention.
//
// 1) Import this class in the .java file for the Applet that will use it:
//
//      import appctrls2;
//
// 2) Create an instance of this class in your Applet's 'init' member, and call
//    CreateControls() through this object:
//
//      appctrls2 ctrls = new appctrls2 (this);
//      ctrls.CreateControls();
//
// 3) To process events generated from user action on these controls, implement
//    the 'handleEvent' member for your applet:
//
//      public boolean handleEvent (Event evt)
//      {
//
//      }
//
//------------------------------------------------------------------------------
import java.awt.*;
import dlayout2;

public class appctrls2
{
	Container    m_Parent       = null;
	boolean      m_fInitialized = false;
	dlayout2 m_Layout;

	// Control definitions
	//--------------------------------------------------------------------------
	Button        btnClose;
	Label         IDC_STATIC1;
	Button        btnListen;
	Button        btnStop;
	TextField     tfStatusBox;
	Label         IDC_STATIC2;
	Button        btnAnswer;
	Button        btnReject;
	Button        btnHangup;


	// Constructor
	//--------------------------------------------------------------------------
	public appctrls2 (Container parent)
	{
		m_Parent = parent;
	}

	// Initialization.
	//--------------------------------------------------------------------------
	public boolean CreateControls()
	{
		// Can only init controls once
		//----------------------------------------------------------------------
		if (m_fInitialized || m_Parent == null)
			return false;

		// Parent must be a derivation of the Container class
		//----------------------------------------------------------------------
		if (!(m_Parent instanceof Container))
			return false;

		// Since there is no way to know if a given font is supported from
		// platform to platform, we only change the size of the font, and not
		// type face name.  And, we only change the font if the dialog resource
		// specified a font.
		//----------------------------------------------------------------------
		Font OldFnt = m_Parent.getFont();
		
		if (OldFnt != null)
		{
			Font NewFnt = new Font(OldFnt.getName(), OldFnt.getStyle(), 8);

			m_Parent.setFont(NewFnt);
		}

		// All position and sizes are in Dialog Units, so, we use the
		// dlayout2 manager.
		//----------------------------------------------------------------------
		m_Layout = new dlayout2(m_Parent, 200, 118);
		m_Parent.setLayout(m_Layout);
		m_Parent.addNotify();

		Dimension size   = m_Layout.getDialogSize();
		Insets    insets = m_Parent.insets();
		
		m_Parent.resize(insets.left + size.width  + insets.right,
                        insets.top  + size.height + insets.bottom);

		// Control creation
		//----------------------------------------------------------------------
		btnClose = new Button ("Close");
		m_Parent.add(btnClose);
		m_Layout.setShape(btnClose, 125, 100, 50, 14);

		/*
		IDC_STATIC1 = new Label ("Mediatypes:", Label.LEFT);
		m_Parent.add(IDC_STATIC1);
		m_Layout.setShape(IDC_STATIC1, 7, 7, 39, 8);
		*/

		btnListen = new Button ("Listen");
		m_Parent.add(btnListen);
		m_Layout.setShape(btnListen, 10, 10, 50, 14);

		/*
		btnStop = new Button ("Stop");
		m_Parent.add(btnStop);
		m_Layout.setShape(btnStop, 133, 17, 50, 14);
		*/

		tfStatusBox = new TextField ("");
		m_Parent.add(tfStatusBox);
		m_Layout.setShape(tfStatusBox, 15, 75, 165, 14);

		IDC_STATIC2 = new Label ("Status:", Label.LEFT);
		m_Parent.add(IDC_STATIC2);
		m_Layout.setShape(IDC_STATIC2, 15, 62, 23, 8);

		/*
		btnAnswer = new Button ("Answer");
		m_Parent.add(btnAnswer);
		m_Layout.setShape(btnAnswer, 83, 42, 50, 14);
		*/

		/*
		btnReject = new Button ("Reject");
		m_Parent.add(btnReject);
		m_Layout.setShape(btnReject, 133, 42, 50, 14);
		*/

		btnHangup = new Button ("Hangup");
		m_Parent.add(btnHangup);
		m_Layout.setShape(btnHangup, 10, 35, 50, 14);

		m_fInitialized = true;
		return true;
	}
}
