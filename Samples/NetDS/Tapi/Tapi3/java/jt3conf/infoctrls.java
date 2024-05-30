/*++
Copyright (c) 1997-2000  Microsoft Corporation
Module Name:
        infoctrls.java
Abstract:

Author:

Notes:
Revision History:
--*/

//------------------------------------------------------------------------------
// cnfctrls.java:
//		Implementation for container control initialization class cnfctrls
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
//      import cnfctrls;
//
// 2) Create an instance of this class in your Applet's 'init' member, and call
//    CreateControls() through this object:
//
//      cnfctrls ctrls = new cnfctrls (this);
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

public class infoctrls
{
	Container    m_Parent       = null;
	boolean      m_fInitialized = false;
	dlayout3 m_Layout;

	// Control definitions
	//--------------------------------------------------------------------------
	Button        btnCreate;
	Button        btnClose;
	Label         IDC_STATIC1;
	TextField     tfConfName;
	Label         IDC_STATIC2;
	TextArea      taDesc;
	Label         IDC_STATIC3;
	TextField     tfUserName;
	Label         IDC_STATIC4;
	TextField     tfStartMonth;
	TextField     tfStartDay;
	TextField     tfStartYear;
	Label         IDC_STATIC5;
	Label         IDC_STATIC6;
	Label         IDC_STATIC7;
	Label         IDC_STATIC8;
	Label         IDC_STATIC9;
	Label         IDC_STATIC10;
	TextField     tfStopHour;
	TextField     tfStopMinute;
	Label         IDC_STATIC11;
	Label         IDC_STATIC12;
	TextField     tfStartHour;
	TextField     tfStartMinute;
	Label         IDC_STATIC13;
	Label         IDC_STATIC14;
	Label         IDC_STATIC15;
	TextField     tfStopYear;
	TextField     tfStopDay;
	TextField     tfStopMonth;
	List          lstMediaFormats;
	Label         IDC_STATIC16;
	Button        btnAdd;
	Button        btnDelete;
	Label         IDC_STATIC17;


	// Constructor
	//--------------------------------------------------------------------------
	public infoctrls (Container parent)
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
		m_Layout = new dlayout3(m_Parent, 334, 145);
		m_Parent.setLayout(m_Layout);
		m_Parent.addNotify();

		Dimension size   = m_Layout.getDialogSize();
		Insets    insets = m_Parent.insets();
		
		m_Parent.resize(insets.left + size.width  + insets.right,
                        insets.top  + size.height + insets.bottom);


		// Control creation
		//----------------------------------------------------------------------
		/*
		btnCreate = new Button ("Create");
		m_Parent.add(btnCreate);
		m_Layout.setShape(btnCreate, 222, 191, 50, 14);
		*/

		btnClose = new Button ("Close");
		m_Parent.add(btnClose);
		m_Layout.setShape(btnClose, 277, 120, 50, 14);

		IDC_STATIC1 = new Label ("Conference Name:", Label.LEFT);
		m_Parent.add(IDC_STATIC1);
		m_Layout.setShape(IDC_STATIC1, 7, 7, 60, 8);

		tfConfName = new TextField ("");
		m_Parent.add(tfConfName);
		m_Layout.setShape(tfConfName, 7, 17, 155, 13);
		tfConfName.setBackground(Color.white);

		IDC_STATIC2 = new Label ("Description:", Label.LEFT);
		m_Parent.add(IDC_STATIC2);
		m_Layout.setShape(IDC_STATIC2, 7, 37, 38, 8);

		taDesc = new TextArea ("");
		m_Parent.add(taDesc);
		m_Layout.setShape(taDesc, 7, 47, 155, 63);
		taDesc.setBackground(Color.white);

		IDC_STATIC3 = new Label ("Originator:", Label.LEFT);
		m_Parent.add(IDC_STATIC3);
		m_Layout.setShape(IDC_STATIC3, 172, 7, 33, 8);

		tfUserName = new TextField ("");
		m_Parent.add(tfUserName);
		m_Layout.setShape(tfUserName, 172, 17, 155, 13);
		tfUserName.setBackground(Color.white);

		IDC_STATIC4 = new Label ("Month:", Label.LEFT);
		m_Parent.add(IDC_STATIC4);
		m_Layout.setShape(IDC_STATIC4, 172, 47, 23, 8);

		tfStartMonth = new TextField ("");
		m_Parent.add(tfStartMonth);
		m_Layout.setShape(tfStartMonth, 173, 58, 55, 13);
		tfStartMonth.setBackground(Color.white);

		tfStartDay = new TextField ("");
		m_Parent.add(tfStartDay);
		m_Layout.setShape(tfStartDay, 232, 57, 20, 13);
		tfStartDay.setBackground(Color.white);

		tfStartYear = new TextField ("");
		m_Parent.add(tfStartYear);
		m_Layout.setShape(tfStartYear, 257, 57, 25, 13);
		tfStartYear.setBackground(Color.white);

		IDC_STATIC5 = new Label ("Day:", Label.LEFT);
		m_Parent.add(IDC_STATIC5);
		m_Layout.setShape(IDC_STATIC5, 232, 47, 16, 8);

		IDC_STATIC6 = new Label ("Year:", Label.LEFT);
		m_Parent.add(IDC_STATIC6);
		m_Layout.setShape(IDC_STATIC6, 257, 47, 18, 8);

		IDC_STATIC7 = new Label ("Start Time:", Label.LEFT);
		m_Parent.add(IDC_STATIC7);
		m_Layout.setShape(IDC_STATIC7, 172, 37, 35, 8);

		IDC_STATIC8 = new Label ("Stop Time:", Label.LEFT);
		m_Parent.add(IDC_STATIC8);
		m_Layout.setShape(IDC_STATIC8, 172, 77, 35, 8);

		IDC_STATIC9 = new Label ("Hr:", Label.LEFT);
		m_Parent.add(IDC_STATIC9);
		m_Layout.setShape(IDC_STATIC9, 287, 87, 10, 8);

		IDC_STATIC10 = new Label ("Min:", Label.LEFT);
		m_Parent.add(IDC_STATIC10);
		m_Layout.setShape(IDC_STATIC10, 312, 87, 14, 8);

		tfStopHour = new TextField ("");
		m_Parent.add(tfStopHour);
		m_Layout.setShape(tfStopHour, 287, 97, 20, 13);
		tfStopHour.setBackground(Color.white);

		tfStopMinute = new TextField ("");
		m_Parent.add(tfStopMinute);
		m_Layout.setShape(tfStopMinute, 312, 97, 15, 13);
		tfStopMinute.setBackground(Color.white);

		IDC_STATIC11 = new Label ("Hr:", Label.LEFT);
		m_Parent.add(IDC_STATIC11);
		m_Layout.setShape(IDC_STATIC11, 287, 47, 10, 8);

		IDC_STATIC12 = new Label ("Min:", Label.LEFT);
		m_Parent.add(IDC_STATIC12);
		m_Layout.setShape(IDC_STATIC12, 312, 47, 14, 8);

		tfStartHour = new TextField ("");
		m_Parent.add(tfStartHour);
		m_Layout.setShape(tfStartHour, 287, 57, 20, 13);
		tfStartHour.setBackground(Color.white);

		tfStartMinute = new TextField ("");
		m_Parent.add(tfStartMinute);
		m_Layout.setShape(tfStartMinute, 312, 57, 15, 13);
		tfStartMinute.setBackground(Color.white);

		IDC_STATIC13 = new Label ("Month:", Label.LEFT);
		m_Parent.add(IDC_STATIC13);
		m_Layout.setShape(IDC_STATIC13, 172, 87, 23, 8);

		IDC_STATIC14 = new Label ("Day:", Label.LEFT);
		m_Parent.add(IDC_STATIC14);
		m_Layout.setShape(IDC_STATIC14, 232, 87, 16, 8);

		IDC_STATIC15 = new Label ("Year:", Label.LEFT);
		m_Parent.add(IDC_STATIC15);
		m_Layout.setShape(IDC_STATIC15, 257, 87, 18, 8);

		tfStopYear = new TextField ("");
		m_Parent.add(tfStopYear);
		m_Layout.setShape(tfStopYear, 257, 97, 25, 13);
		tfStopYear.setBackground(Color.white);

		tfStopDay = new TextField ("");
		m_Parent.add(tfStopDay);
		m_Layout.setShape(tfStopDay, 232, 97, 20, 13);
		tfStopDay.setBackground(Color.white);

		tfStopMonth = new TextField ("");
		m_Parent.add(tfStopMonth);
		m_Layout.setShape(tfStopMonth, 173, 98, 55, 13);
		tfStopMonth.setBackground(Color.white);

		/*
		lstMediaFormats = new List (1, false);
		m_Parent.add(lstMediaFormats);
		m_Layout.setShape(lstMediaFormats, 7, 137, 320, 49);

		IDC_STATIC16 = new Label ("Media: (When creating conferences, leave this list blank for full-duplex Audio and Video) ", Label.LEFT);
		m_Parent.add(IDC_STATIC16);
		m_Layout.setShape(IDC_STATIC16, 7, 117, 279, 8);

		btnAdd = new Button ("Add...");
		m_Parent.add(btnAdd);
		m_Layout.setShape(btnAdd, 7, 191, 50, 14);

		btnDelete = new Button ("Delete");
		m_Parent.add(btnDelete);
		m_Layout.setShape(btnDelete, 57, 191, 50, 14);

		IDC_STATIC17 = new Label ("Name / StartPort / NumPorts / StartAddr / NumAddr / TTL ", Label.LEFT);
		m_Parent.add(IDC_STATIC17);
		m_Layout.setShape(IDC_STATIC17, 7, 127, 188, 8);

		*/

		m_fInitialized = true;
		return true;
	}
}
