/*++
Copyright (c) 1997-2000  Microsoft Corporation
Module Name:
        medctrls.java
Abstract:

Author:

Notes:
Revision History:
--*/

//------------------------------------------------------------------------------
// medctrls.java:
//		Implementation for container control initialization class medctrls
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
//      import medctrls;
//
// 2) Create an instance of this class in your Applet's 'init' member, and call
//    CreateControls() through this object:
//
//      medctrls ctrls = new medctrls (this);
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

public class medctrls
{
	Container    m_Parent       = null;
	boolean      m_fInitialized = false;
	dlayout3 m_Layout;

	// Control definitions
	//--------------------------------------------------------------------------
	Button        btnOk;
	Button        btnCancel;
	Label         IDC_STATIC1;
	Label         IDC_STATIC2;
	Label         IDC_STATIC3;
	Label         IDC_STATIC4;
	TextField     tfCount;
	TextField     tfAddress;
	Choice        cmbFormat;
	Label         IDC_STATIC5;
	TextField     tfPort;
	TextField     tfName;
	Label         IDC_STATIC6;
	TextField     tfTTL;


	// Constructor
	//--------------------------------------------------------------------------
	public medctrls (Container parent)
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
		m_Layout = new dlayout3(m_Parent, 200, 128);
		m_Parent.setLayout(m_Layout);
		m_Parent.addNotify();

		Dimension size   = m_Layout.getDialogSize();
		Insets    insets = m_Parent.insets();
		
		m_Parent.resize(insets.left + size.width  + insets.right,
                        insets.top  + size.height + insets.bottom);

		// Control creation
		//----------------------------------------------------------------------
		btnOk = new Button ("OK");
		m_Parent.add(btnOk);
		m_Layout.setShape(btnOk, 47, 107, 50, 14);

		btnCancel = new Button ("Cancel");
		m_Parent.add(btnCancel);
		m_Layout.setShape(btnCancel, 102, 107, 50, 14);

		IDC_STATIC1 = new Label ("Media Name:", Label.LEFT);
		m_Parent.add(IDC_STATIC1);
		m_Layout.setShape(IDC_STATIC1, 7, 9, 43, 8);

		IDC_STATIC2 = new Label ("Format:", Label.LEFT);
		m_Parent.add(IDC_STATIC2);
		m_Layout.setShape(IDC_STATIC2, 7, 29, 24, 8);

		IDC_STATIC3 = new Label ("Start Address:", Label.LEFT);
		m_Parent.add(IDC_STATIC3);
		m_Layout.setShape(IDC_STATIC3, 7, 49, 45, 8);

		IDC_STATIC4 = new Label ("Count:", Label.LEFT);
		m_Parent.add(IDC_STATIC4);
		m_Layout.setShape(IDC_STATIC4, 127, 49, 22, 8);

		tfCount = new TextField ("");
		m_Parent.add(tfCount);
		m_Layout.setShape(tfCount, 153, 47, 40, 13);

		tfAddress = new TextField ("");
		m_Parent.add(tfAddress);
		m_Layout.setShape(tfAddress, 57, 47, 65, 13);

		cmbFormat = new Choice ();
		m_Parent.add(cmbFormat);
		m_Layout.setShape(cmbFormat, 57, 26, 48, 85);

		IDC_STATIC5 = new Label ("Port:", Label.LEFT);
		m_Parent.add(IDC_STATIC5);
		m_Layout.setShape(IDC_STATIC5, 7, 68, 16, 8);

		tfPort = new TextField ("");
		m_Parent.add(tfPort);
		m_Layout.setShape(tfPort, 57, 66, 40, 13);

		tfName = new TextField ("");
		m_Parent.add(tfName);
		m_Layout.setShape(tfName, 57, 7, 65, 13);

		IDC_STATIC6 = new Label ("TTL:", Label.LEFT);
		m_Parent.add(IDC_STATIC6);
		m_Layout.setShape(IDC_STATIC6, 7, 89, 16, 8);

		tfTTL = new TextField ("");
		m_Parent.add(tfTTL);
		m_Layout.setShape(tfTTL, 57, 87, 40, 13);

		m_fInitialized = true;
		return true;
	}
}
