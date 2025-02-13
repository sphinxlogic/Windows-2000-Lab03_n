/*++
Copyright (c) 1997-2000  Microsoft Corporation
Module Name:
        newdlg.java
Abstract:

Author:

Notes:
Revision History:
--*/

import java.awt.*;
import java.util.*;
import com.ms.com.*;
import com.ms.ui.*;
import tapi3.*;
import quartz.*;
import rend.*;
import sdpblb.*;
import cnfctrls;
import svtime;


/////////////////////////////////////////////////////////////////////////
//  CLASS: newdlg
//
//  PURPOSE: Supporting class to JT3Conf
//  DATE:    July 24, 1997 - March 30, 1998
//
//  DESCRIPTION:
//      Dialog that allows the user to enter specifications for a
//      conference and then create it using the Rendezvous Controls.
//
/////////////////////////////////////////////////////////////////////////

public class newdlg extends Dialog
implements		DIRECTORY_TYPE,
				DIRECTORY_OBJECT_TYPE
{
    // Dialog title.
    public static final String DLG_TITLE = "New Conference";

    // Button ids.
    public static final int NONE   = 0;
    public static final int CREATE = 1;
    public static final int CLOSE  = 2;

    // Resource Wizard generated UI.
	private final cnfctrls ctrls =new cnfctrls(this);

    // Parent frame of the dlg.
    private Frame m_ParentFrame = null;

    // The conference directory component.
    private ITRendezvous m_Rend = null;

    // The conference that is created.
    private ITDirectoryObject m_Conference = null;

    // The ILS server
    private ITDirectory m_Dir = null;


    // Stores MediaInfo objects for media formats displayed in the media
    // listbox.
    private Vector m_MediaInfoList = new Vector();

    // The button that was use to close the dialog.
    private int m_ButtonId = NONE;

    // Conference data fields.
    public String m_strConfName = "";
    public String m_strDesc = "";
    public String m_strUserName = "";

    public short  m_nStartYear = 1998;
    public short  m_nStartMonth = 4;
    public short  m_nStartDay = 1;
    public short  m_nStartHour = 8;
    public short  m_nStartMinute = 0;

    public short  m_nStopYear = 2000;
    public short  m_nStopMonth = 4;
    public short  m_nStopDay = 1;
    public short  m_nStopHour = 8;
    public short  m_nStopMinute= 0;


    /////////////////////////////////////////////////////////////////////
    // Constructor
    /////////////////////////////////////////////////////////////////////
    public newdlg(Frame parent, ITRendezvous rendev) //, ITDirectory dir)
    {
        super(parent, DLG_TITLE, true);

	    

        // select a font to use (ctrls needs this)
        Font font = new Font("Dialog", Font.PLAIN, 8);
        this.setFont(font);
        this.setBackground(Color.cyan);

        // create the UI generated by the Resource Wizard
        ctrls.CreateControls();

        // initialize controls
        ctrls.cmbStartMonth.addItem("January");
        ctrls.cmbStartMonth.addItem("February");
        ctrls.cmbStartMonth.addItem("March");
        ctrls.cmbStartMonth.addItem("April");
        ctrls.cmbStartMonth.addItem("May");
        ctrls.cmbStartMonth.addItem("June");
        ctrls.cmbStartMonth.addItem("July");
        ctrls.cmbStartMonth.addItem("August");
        ctrls.cmbStartMonth.addItem("September");
        ctrls.cmbStartMonth.addItem("October");
        ctrls.cmbStartMonth.addItem("November");
        ctrls.cmbStartMonth.addItem("December");

        ctrls.cmbStopMonth.addItem("January");
        ctrls.cmbStopMonth.addItem("February");
        ctrls.cmbStopMonth.addItem("March");
        ctrls.cmbStopMonth.addItem("April");
        ctrls.cmbStopMonth.addItem("May");
        ctrls.cmbStopMonth.addItem("June");
        ctrls.cmbStopMonth.addItem("July");
        ctrls.cmbStopMonth.addItem("August");
        ctrls.cmbStopMonth.addItem("September");
        ctrls.cmbStopMonth.addItem("October");
        ctrls.cmbStopMonth.addItem("November");
        ctrls.cmbStopMonth.addItem("December");

        UpdateData(true);
 
        // get parent frame to use for message boxes
        m_ParentFrame = parent;

        // save rendezvous control
        m_Rend = rendev;

		// assign the ILS server
		//m_Dir = dir;
    }

    /////////////////////////////////////////////////////////////////////
    // action
    //
    // Event.ACTION_EVENT event handler.
    /////////////////////////////////////////////////////////////////////
    public boolean action(Event evt, Object arg)
    {
        if (arg.equals("Create")) {
            // create button pressed
            UpdateData(false);
            if (ValidateData()) 
			{
                m_Conference = CreateTheConference();
                m_ButtonId = CREATE;
				// force garbage collection
				System.gc();
                this.dispose();
            }
			else
			{
				DoMessage("Invalid Data - pls. try again");
			}
        }
        else if (arg.equals("Add...")) {
            // add button pressed
			// the media dialog functionality is not available
			// in this version
			/*
            MedDlg medDlg = new MedDlg(m_ParentFrame);
            medDlg.show();
            if (medDlg.GetButtonId() == medDlg.OK) {
                MediaInfo info = medDlg.GetMediaInfo();
                m_MediaInfoList.addElement(info);
                ctrls.lstMediaFormats.addItem(
                                             info.mediaName + " / " +
                                             info.startPort + " / " +
                                             info.numPorts + " / " +
                                             info.startAddr + " / " +
                                             info.numAddr + " / " +
                                             info.ttl
                                             );
            }
			*/
        }
        else if (arg.equals("Delete")) {
            // delete button pressed
			/*
            int index = ctrls.lstMediaFormats.getSelectedIndex();
            if (index != -1) {
                ctrls.lstMediaFormats.delItem(index);
                m_MediaInfoList.removeElementAt(index);
            }
            else {
                DoMessage("You must select a media first.");
            }
			*/
        }
        else if (arg.equals("Close")) {
            // close button pressed
            m_ButtonId = CLOSE;
            this.dispose();
        }
        else {
            return super.action(evt, arg);
        }
        return true;
    }

    /////////////////////////////////////////////////////////////////////
    // GetConference
    //
    // Returns the conference that was created or null if a conference
    // was not created.
    /////////////////////////////////////////////////////////////////////
    public ITDirectoryObject GetConference()
    {
        if (m_ButtonId == CREATE)
            return m_Conference;
        else
            return null;
    }

    /////////////////////////////////////////////////////////////////////
    // GetButtonId
    //
    // Returns the id of the button that was used to close the dialog.
    // May be NONE if the dialog is closed using the system menu, etc.
    /////////////////////////////////////////////////////////////////////
    public int GetButtonId()
    {
        return m_ButtonId;
    }

    /////////////////////////////////////////////////////////////////////
    // UpdateData
    //
    // If toControls is true, the values in the conference data fields
    // are put into the UI controls.  If toControls is false, data from
    // the dialog controls is collected and stored into the conference
    // data fields.
    /////////////////////////////////////////////////////////////////////
    public void UpdateData(boolean toControls)
    {
        if (toControls) {
            ctrls.tfConfName.setText(m_strConfName);
            ctrls.taDesc.setText(m_strDesc);
            //ctrls.tfUserName.setText(m_strUserName);

            ctrls.tfStartYear.setText(m_nStartYear + "");
            ctrls.cmbStartMonth.select(m_nStartMonth - 1);
            ctrls.tfStartDay.setText(m_nStartDay + "");
            ctrls.tfStartHour.setText(m_nStartHour + "");
            ctrls.tfStartMinute.setText(m_nStartMinute + "");

            ctrls.tfStopYear.setText(m_nStopYear + "");
            ctrls.cmbStopMonth.select(m_nStopMonth - 1);
            ctrls.tfStopDay.setText(m_nStopDay + "");
            ctrls.tfStopHour.setText(m_nStopHour + "");
            ctrls.tfStopMinute.setText(m_nStopMinute + "");
        }
        else {
            m_strConfName = ctrls.tfConfName.getText().trim();
            m_strDesc = ctrls.taDesc.getText().trim();
            //m_strUserName = ctrls.tfUserName.getText().trim();

            m_nStartYear = Short.parseShort(ctrls.tfStartYear.getText().trim());
            short si = (short) ctrls.cmbStartMonth.getSelectedIndex();
			si++;
			m_nStartMonth = si;
            //m_nStartMonth = (ctrls.cmbStartMonth.getSelectedIndex() + 1);
            m_nStartDay = Short.parseShort(ctrls.tfStartDay.getText().trim());
            m_nStartHour = Short.parseShort(ctrls.tfStartHour.getText().trim());
            m_nStartMinute = Short.parseShort(ctrls.tfStartMinute.getText().trim());

            m_nStopYear = Short.parseShort(ctrls.tfStopYear.getText().trim());
            short si1 = (short) ctrls.cmbStopMonth.getSelectedIndex();
			si1++;
			m_nStopMonth = si1;
            //m_nStopMonth = (ctrls.cmbStopMonth.getSelectedIndex() + 1);
            m_nStopDay = Short.parseShort(ctrls.tfStopDay.getText().trim());
            m_nStopHour = Short.parseShort(ctrls.tfStopHour.getText().trim());
            m_nStopMinute = Short.parseShort(ctrls.tfStopMinute.getText().trim());
        }
    }

    /////////////////////////////////////////////////////////////////////
    // ValidateData
    //
    // Returns true if the conference data fields contain valid data.
    // If any of the fields are incorrect, a message is displayed to the
    // user.
    /////////////////////////////////////////////////////////////////////
    public boolean ValidateData()
    {
        if (m_strConfName.equals("")) {
            DoMessage("The Conference Name field may not be blank");
            return false;
        }

        if (m_strDesc.equals("")) {
            DoMessage("The Description field may not be blank");
            return false;
        }

        //if (m_strUserName.equals("")) {
        //    DoMessage("The User Name field may not be blank");
        //    return false;
        //}

        if (m_nStartYear < 1970 || m_nStartYear > 3000) {
            DoMessage("The Start Year field must be from 1970 to 3000");
            return false;
        }

        if (m_nStartDay < 1 || m_nStartDay > DaysInMonth(m_nStartMonth)) {
            DoMessage("The Start Day field must be from 1 to " + DaysInMonth(m_nStartMonth));
            return false;
        }

        if (m_nStartHour < 1 || m_nStartHour > 23) {
            DoMessage("The Start Hour field must be from 1 to 23");
            return false;
        }

        if (m_nStartMinute < 0 || m_nStartMinute > 59) {
            DoMessage("The Start Minutes field must be from 0 to 59");
            return false;
        }

        if (m_nStopYear < 1970 || m_nStopYear > 3000) {
            DoMessage("The Stop Year field must be from 1900 to 3000");
            return false;
        }

        if (m_nStopDay < 1 || m_nStopDay > DaysInMonth(m_nStopMonth)) {
            DoMessage("The Stop Day field must be from 1 to " + DaysInMonth(m_nStopMonth));
            return false;
        }

        if (m_nStopHour < 1 || m_nStopHour > 23) {
            DoMessage("The Stop Hour field must be from 1 to 23");
            return false;
        }

        if (m_nStopMinute < 0 || m_nStopMinute > 59) {
            DoMessage("The Stop Minutes field must be from 0 to 59");
            return false;
        }

        return true;
    }


    /////////////////////////////////////////////////////////////////////
    // CreateTheConference
    //
    // Creates a conference using the data entered into the conference
    // data fields.  Returns the created conference or null if there
    // was an error.
    /////////////////////////////////////////////////////////////////////
    private ITDirectoryObject CreateTheConference()
    {
        ITDirectoryObject dobj= null;
        ITDirectoryObjectConference conf= null;
        ITConferenceBlob  confBlob;
        ITSdp             sdp;
        MediaInfo         info;
        SafeArray         sa;
		String            url;
		double stime, etime;
 
		ITMedia           media;
        ITConnection      conn;
        ITMediaCollection mediaCol;

        try {
            // create the conference
            dobj = m_Rend.CreateDirectoryObject(OT_CONFERENCE, m_strConfName);
        }
        catch (ComException e) {
            e.printStackTrace();
            DoMessage("The conference failed to be created");
            return null;
        }

        try {
            // modify its attributes
			conf = (ITDirectoryObjectConference) dobj;

            stime = svtime.getSTime(
                            m_nStartYear,
                            m_nStartMonth,
                            m_nStartDay,
                            m_nStartHour,
                            m_nStartMinute
                            );


            etime = svtime.getSTime(
                            m_nStopYear,
                            m_nStopMonth,
                            m_nStopDay,
                            m_nStopHour,
                            m_nStopMinute
                            );

			//stime=36000.041666666664;
			//etime=36154.041666666664;			
            conf.putStartTime(stime);
            conf.putStopTime(etime);

			//url = "http://www";
            //conf.putUrl(url);

			
			//conf.putOriginator(m_strUserName);
            
			confBlob = (ITConferenceBlob) conf;
            sdp = (ITSdp) confBlob;
            sdp.putDescription(m_strDesc);

			String blob = confBlob.getConferenceBlob();
			System.out.println("the BLOB");
			System.out.println(blob);

			/*

			// the media part is disabled in the current version
            mediaCol = sdp.getMediaCollection();
            
            // By default, conferences have full-duplex audio and video.
            // In this program, if the user specifies any media in the
            // media listbox, we remove the default media and use only
            // those specified by the user.

            if (m_MediaInfoList.size() > 0) {
                // remove default media
                for (int i=1; i < mediaCol.getCount(); i++) {
                    mediaCol.Delete(i);
                }

                // add user media
                for (int j=0; j < m_MediaInfoList.size(); j++) {
                    info = (MediaInfo) m_MediaInfoList.elementAt(j);
                
                    media = mediaCol.Create(j + 1);
                    media.putMediaName(info.mediaName);
					System.out.println("CTC: Added media = " + info.mediaName);
                    media.SetPortInfo(info.startPort, info.numPorts);
            
                    // set the format for this media.  It is possible to
                    // specify more than one format code for each media.
                    sa = new SafeArray(Variant.VariantByte, 1);
                    sa.setByte(0, info.format);
					System.out.println("CTC: Media format = " + info.format);
                    media.putFormatCodes(new Variant(sa, false));

                    conn = (ITConnection) media;
                            // BUGBUG: can't use 'media' (ITMedia i/f)
                            //         like t3conf!  Doesn't commit
                            //         conference! why does 'sdp' work?
                    conn.SetAddressInfo(
                                       info.startAddr,
                                       info.numAddr,
                                       info.ttl
                                       );
                }
            }
			*/

			// dobj = (ITDirectoryObject) conf;
			//sdp = null;
			//confBlob  = null;
			//conf = null;
			//System.gc();

			//m_Dir.AddDirectoryObject(dobj);
	        return dobj;
		}
        catch (ComException e) {
            e.printStackTrace();
            DoMessage("The conference was created but one or more of " +
                      "its attributes failed to be set");
			dobj = null;
			return dobj;
        }

    }


    /////////////////////////////////////////////////////////////////////
    // DaysInMonth
    //
    // Returns the number of days in the given month, where January is
    // month 1 and so on.  Does not account for leap-years.
    /////////////////////////////////////////////////////////////////////
    private int DaysInMonth(int month)
    {
        switch (month)
        {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return 31;
        case 2:
            return 28;  // leap-years not included!
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
        default:
            return 0;
        }
    }

    /////////////////////////////////////////////////////////////////////
    // DoMessage
    //
    // Displays messages in a message box.
    /////////////////////////////////////////////////////////////////////
    private void DoMessage(String msg)
    {
        AwtUIMessageBox msgbox = new AwtUIMessageBox(
                                            m_ParentFrame,
                                            DLG_TITLE,
                                            msg,
                                            AwtUIMessageBox.EXCLAMATION,
                                            UIButtonBar.OK
                                            );
        msgbox.doModal();
    }
}


/////////////////////////////////////////////////////////////////////////
// CLASS: MediaInfo
//
// DESCRIPTION:
//      Holds properties for media used in a conference.
/////////////////////////////////////////////////////////////////////////
class MediaInfo
{
    String mediaName;
    short  startPort;
    short  numPorts;
    String startAddr;   // dotted-decimal address
    int    numAddr;
    byte   ttl;         // time-to-live
    byte   format;      // format code for this media
}
