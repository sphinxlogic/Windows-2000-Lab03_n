/*++
Copyright (c) 1997-2000  Microsoft Corporation
Module Name:
        appctrls3.java
Abstract:

Author:

Notes:
Revision History:
--*/

//------------------------------------------------------------------------------
// appctrls3.java:
//		Implementation for container control initialization class appctrls3
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
//      import appctrls3;
//
// 2) Create an instance of this class in your Applet's 'init' member, and call
//    CreateControls() through this object:
//
//      appctrls3 ctrls = new appctrls3 (this);
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
import dlayout3;

public class appctrls3
{
	Container    m_Parent       = null;
	boolean      m_fInitialized = false;
	dlayout3  m_Layout;

	// Control definitions
	//--------------------------------------------------------------------------
	Label         IDC_STATIC1;
	List          lstConferences;
	Button        btnInfo;
	Button        btnRefresh;
	Button        btnNew;
	Button        btnDelete;
	Label         IDC_STATIC2;
	Label         IDC_STATIC3;
	TextField     tfVideoWnds;
	Label         IDC_STATIC4;
	TextField     tfStatusBox;
	Button        btnJoin;
	Button        btnHangup;
	Button        btnClose;


	// Constructor
	//--------------------------------------------------------------------------
	public appctrls3 (Container parent)
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
		// dlayout3 manager.
		//----------------------------------------------------------------------
		m_Layout = new dlayout3(m_Parent, 284, 178);
		m_Parent.setLayout(m_Layout);
		m_Parent.addNotify();

		Dimension size   = m_Layout.getDialogSize();
		Insets    insets = m_Parent.insets();
		
		m_Parent.resize(insets.left + size.width  + insets.right,
                        insets.top  + size.height + insets.bottom);

		// Control creation
		//----------------------------------------------------------------------
		IDC_STATIC1 = new Label ("Conference Name:", Label.LEFT);
		m_Parent.add(IDC_STATIC1);
		m_Layout.setShape(IDC_STATIC1, 7, 7, 60, 8);

		lstConferences = new List (1, false);
		m_Parent.add(lstConferences);
		m_Layout.setShape(lstConferences, 7, 17, 215, 106);

		btnInfo = new Button ("Info...");
		m_Parent.add(btnInfo);
		m_Layout.setShape(btnInfo, 227, 17, 50, 14);

		btnRefresh = new Button ("Refresh");
		m_Parent.add(btnRefresh);
		m_Layout.setShape(btnRefresh, 227, 31, 50, 14);

		btnNew = new Button ("New...");
		m_Parent.add(btnNew);
		m_Layout.setShape(btnNew, 227, 52, 50, 14);

		btnDelete = new Button ("Delete");
		m_Parent.add(btnDelete);
		m_Layout.setShape(btnDelete, 227, 66, 50, 14);

		IDC_STATIC2 = new Label ("Number of", Label.LEFT);
		m_Parent.add(IDC_STATIC2);
		m_Layout.setShape(IDC_STATIC2, 235, 89, 34, 8);

		IDC_STATIC3 = new Label ("Video Wnds:", Label.LEFT);
		m_Parent.add(IDC_STATIC3);
		m_Layout.setShape(IDC_STATIC3, 231, 98, 42, 8);

		tfVideoWnds = new TextField ("");
		m_Parent.add(tfVideoWnds);
		m_Layout.setShape(tfVideoWnds, 239, 110, 25, 13);
		tfVideoWnds.setBackground(Color.white);

		IDC_STATIC4 = new Label ("Status:", Label.LEFT);
		m_Parent.add(IDC_STATIC4);
		m_Layout.setShape(IDC_STATIC4, 7, 127, 23, 8);

		tfStatusBox = new TextField ("");
		m_Parent.add(tfStatusBox);
		m_Layout.setShape(tfStatusBox, 7, 137, 270, 13);
		tfStatusBox.setBackground(Color.white);

		btnJoin = new Button ("Join");
		m_Parent.add(btnJoin);
		m_Layout.setShape(btnJoin, 7, 157, 50, 14);

		btnHangup = new Button ("Hangup");
		m_Parent.add(btnHangup);
		m_Layout.setShape(btnHangup, 57, 157, 50, 14);

		btnClose = new Button ("Close");
		m_Parent.add(btnClose);
		m_Layout.setShape(btnClose, 227, 157, 50, 14);

		m_fInitialized = true;
		return true;
	}
}
