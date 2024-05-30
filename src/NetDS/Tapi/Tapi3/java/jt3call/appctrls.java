/*++
Copyright (c) 1997-2000  Microsoft Corporation
Module Name:
  	appctrls.java
Abstract:

Author:

Notes:
Revision History:
--*/

//------------------------------------------------------------------------------
// appctrls.java:
//		Implementation for container control initialization class appctrls
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
//      import appctrls;
//
// 2) Create an instance of this class in your Applet's 'init' member, and call
//    CreateControls() through this object:
//
//      appctrls ctrls = new appctrls (this);
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
import dialoglayout;

/**
 * @com.register ( clsid=BA536136-308A-11D2-8E54-00A0C9AC4B3A, typelib=BA536135-308A-11D2-8E54-00A0C9AC4B3A )
 */
public class appctrls
{
	Container    m_Parent       = null;
	boolean      m_fInitialized = false;
	dialoglayout m_Layout;

	// Control definitions
	//--------------------------------------------------------------------------
	Button        btnClose;
	Label         IDC_STATIC1;
	Label         IDC_STATIC2;
	Choice      cmbSrcAddr;
	TextField  tfDestAddr;
	Button        btnConnect;
	Button        btnDisconnect;
	List             lstStaticTerms;
	Label         IDC_STATIC3;
	TextField     tfStatusBox;
	Label         IDC_STATIC4;
	Label         IDC_STATIC5;
	TextField     tfVideoWnds;
	Choice        cmbDstAddr;
	Label         IDC_STATIC6;


	// Constructor
	//--------------------------------------------------------------------------
	public appctrls (Container parent)
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
		// dialoglayout manager.
		//----------------------------------------------------------------------
		m_Layout = new dialoglayout(m_Parent, 394, 250);
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
		m_Layout.setShape(btnClose, 207, 116, 50, 14);

		IDC_STATIC1 = new Label ("Destination Address:", Label.LEFT);
		m_Parent.add(IDC_STATIC1);
		m_Layout.setShape(IDC_STATIC1, 7, 35, 66, 8);

		IDC_STATIC2 = new Label ("Source Address:", Label.LEFT);
		m_Parent.add(IDC_STATIC2);
		m_Layout.setShape(IDC_STATIC2, 7, 7, 53, 8);

		cmbSrcAddr = new Choice ();
		m_Parent.add(cmbSrcAddr);
		m_Layout.setShape(cmbSrcAddr, 7, 20, 105, 40);

		tfDestAddr = new TextField ("");
		m_Parent.add(tfDestAddr);
		m_Layout.setShape(tfDestAddr, 7, 47, 105, 13);

		btnConnect = new Button ("Connect");
		m_Parent.add(btnConnect);
		m_Layout.setShape(btnConnect, 7, 66, 50, 14);

		btnDisconnect = new Button ("Disconnect");
		m_Parent.add(btnDisconnect);
		m_Layout.setShape(btnDisconnect, 62, 66, 50, 14);

		lstStaticTerms = new List (1, false);
		m_Parent.add(lstStaticTerms);
		m_Layout.setShape(lstStaticTerms, 122, 17, 135, 75);

		IDC_STATIC3 = new Label ("Static Terminals:", Label.LEFT);
		m_Parent.add(IDC_STATIC3);
		m_Layout.setShape(IDC_STATIC3, 122, 7, 53, 8);

		tfStatusBox = new TextField ("");
		m_Parent.add(tfStatusBox);
		m_Layout.setShape(tfStatusBox, 7, 97, 105, 13);

		IDC_STATIC4 = new Label ("Status:", Label.LEFT);
		m_Parent.add(IDC_STATIC4);
		m_Layout.setShape(IDC_STATIC4, 7, 87, 23, 8);

		IDC_STATIC5 = new Label ("Number of Video Wnds:", Label.LEFT);
		m_Parent.add(IDC_STATIC5);
		m_Layout.setShape(IDC_STATIC5, 152, 98, 76, 8);

		tfVideoWnds = new TextField ("");
		m_Parent.add(tfVideoWnds);
		m_Layout.setShape(tfVideoWnds, 232, 97, 25, 13);

/*
		IDC_STATIC6 = new Label ("Destination Address Type :", Label.LEFT);
		m_Parent.add(IDC_STATIC6);
		m_Layout.setShape(IDC_STATIC6, 7, 135, 53, 8);
*/
		cmbDstAddr = new Choice ();
		m_Parent.add(cmbDstAddr);
		m_Layout.setShape(cmbDstAddr, 7, 150, 105, 80);
		m_fInitialized = true;
		return true;
	}
}
