//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import FeatureTabFileViewer;

/**
*	JNoteTabFileViewer
*	
*	JNotepad specific implementation of FeatureTabFileViewer.
*	We extend this class and add JNotepad specific functionality.
*	The following functionality is added:
*		- Time/Date stamp
*		- Properties dialog
*		- About JNotepad dialog
*
*	@version	1.0, 8/17/97
*
*	@see	#FeatureTabFileViewer
*/

import com.ms.ui.*;
import com.ms.fx.*;
import com.ms.ui.event.*;
import java.util.*;
import java.awt.*;

public class JNoteTabFileViewer extends FeatureTabFileViewer
{	
	public JNoteTabFileViewer(UIFrame parFrame, ICommandFeedback feedback, IComponentFeature compfeature)
	{
		this(parFrame, null, feedback, compfeature);
	}
	
	public JNoteTabFileViewer(UIFrame parFrame, UIBand menubar, ICommandFeedback feedback, IComponentFeature compfeature)
	{
		super(parFrame, menubar, feedback, compfeature);
		setWindowAppearance("Default");
	}
	
	public boolean otherCommand(String command, UIActionEvent evt)
	{
		boolean ret = false;
		IUIComponent comp=evt.getActionItem();
		switch( comp.getID() )
		{ 
		case ResourceIDs.ID_HELP_ABOUT:
			ret = doHelpAbout();
			break;
		case ResourceIDs.ID_PROPERTIES:
			ret = doProperties();
			break;
		case ResourceIDs.ID_TIMEDATE:
			ret = doTimeDate();
			break;
		case ResourceIDs.ID_EMACS_CUT:
			ret = doEmacsCut();
			break;
		case ResourceIDs.ID_EMACS_PASTE:
			ret = doEmacsPaste();
			break;
		default:
			ret = super.otherCommand(command, evt);
		}
		return ret;
	}
	
	protected void insertTimeDate()
	{
		Date curDateObj = new Date(System.currentTimeMillis());
		String curDate = (curDateObj.getMonth()+1) + "/" + curDateObj.getDate() + 
			"/" + curDateObj.getYear();
		
		int iHours = curDateObj.getHours();
		String ampm = null;
		
		if (iHours > 11)
		{
			ampm = "PM";
		}
		else
		{
			ampm = "AM";
		}
		
		if (iHours > 12)
		{
			iHours -= 12;
		}
		
		String sMinutes = null;
		int iMinutes = curDateObj.getMinutes();
		if (iMinutes < 10)
		{
			sMinutes = "0" + iMinutes;
		}
		else
		{
			sMinutes = String.valueOf(iMinutes);
		}
		
		ITextOperationTargetExt edit = getFileTarget().getEditControl();
		
		String curTime = iHours + ":" + sMinutes + " " + ampm;
		String dateAndTime = curTime + " " + curDate;
		int iCaretIndex = edit.getCaretIndex();
		
		if (edit.getSelectionStart() == edit.getSelectionEnd())
		{
			edit.insertText(dateAndTime, iCaretIndex);
		}
		else
		{
			edit.paste(dateAndTime);
		}

		edit.moveTheCaret(iCaretIndex+dateAndTime.length());
	}
	
	public void emacsCut()
	{
		ITextOperationTargetExt edit = getFileTarget().getEditControl();
		String text = edit.getText()+"\n";
		
		int iPos = edit.getCaretIndex();
		int iEndOfLine = text.indexOf('\n', iPos);
		
		if (iEndOfLine >= 0)
		{
			edit.setSelection(iPos, iEndOfLine);
			cut();
		}
	}
	
	public void emacsPaste()
	{
	}
	
	protected void initNewTab()
	{			
		super.initNewTab();

		String sectionName = getFileTarget().getFileExtension();
		
		if ((sectionName == null) || (sectionName.length() == 0))
		{
			sectionName = "DEFAULT";
		}
		
		sectionName = sectionName.toUpperCase();
		
		setWindowAppearance(sectionName);
		
		loadFileFeatures(sectionName);
	}
	
	protected void updateColors()
	{
		ITextOperationTargetExt tTarget = getFileTarget().getEditControl();
		
		FxColor bgColor = tTarget.getBackColor();
		FxColor fgColor = tTarget.getTextColor();
		
		if (feedbackObj != null)
		{
			feedbackObj.notifyColorChange(tTarget, bgColor, 
				ICommandFeedback.COLORCHANGE_BACKGROUND);
			
			feedbackObj.notifyColorChange(tTarget, fgColor, 
				ICommandFeedback.COLORCHANGE_FOREGROUND);			
		}					
	}

	public void refreshCurrentTab()
	{					
		updateColors();
		super.refreshCurrentTab();
	}
	
	protected void setWindowAppearance(String sectionName)
	{
		JNoteSettings settingsObj = JNoteAppSettings.getSettingsObj();
		
		FxColor bgColor = settingsObj.getColorIndirect(sectionName, "Background", FxColor.getExtendedColor(Color.white));
		FxColor fgColor = settingsObj.getColorIndirect(sectionName, "Foreground", FxColor.getExtendedColor(Color.blue));
		FxFont font = settingsObj.getFont(sectionName, "Font", new FxFont("Arial", 0, 14));
		
		if(getFileTarget() == null )
		{
			System.out.println("No file");
			return;
		}

		ITextOperationTargetExt tTarget = getFileTarget().getEditControl();
		
		tTarget.setBackColor(bgColor);
		tTarget.setTextColor(fgColor);
		tTarget.changeFont(font);			

		tTarget.repaint();
	}
	
	protected boolean loadFileFeatures(String sectionName)
	{
		String features = JNoteAppSettings.getSettingsObj().get(sectionName, "Features", "");
		StringTokenizer st = new StringTokenizer(features);
		
		while (st.hasMoreTokens())
		{
			loadFeature(st.nextToken());					
		}
		
		return true;
	}
	
	protected boolean loadFeature(String featureName)
	{
		boolean ret = false;
		
		try 
		{					
			Class newFeatureClass = Class.forName(featureName);
			Object newFeatureInstance = newFeatureClass.newInstance();
			
			IFeature fl = (IFeature)newFeatureInstance;
			
			if (fl instanceof ITextFeature)
			{
				registerListener(fl);
				((ITextFeature)fl).init(getFileTarget().getEditControl());
				fl.register();									
			}
			
			ret = true;
		}
		catch (ClassNotFoundException e)
		{
			// plug in feature could not be found
			UIMessageBox _box_ = new UIMessageBox(new UIFrame(), 
				JNotePad.loadString(ResourceIDs.IDS_MSGTITLE),
				JNotePad.loadString(ResourceIDs.IDS_MSGNOFEATURE)+featureName,
				UIMessageBox.STOP, UIButtonBar.OK);
			_box_.doModal();
			
		}
		catch (InstantiationException e1)
		{
			// plug in feature could not be loaded/created
			UIMessageBox _box_ = new UIMessageBox(new UIFrame(), 
				JNotePad.loadString(ResourceIDs.IDS_MSGTITLE),
				JNotePad.loadString(ResourceIDs.IDS_MSGNOFEATUREINIT)+featureName,
				UIMessageBox.STOP, UIButtonBar.OK);
			_box_.doModal();
			
		}
		catch (IllegalAccessException e2)
		{
			// plug in feature could not be accessed
			UIMessageBox _box_ = new UIMessageBox(new UIFrame(), 
				JNotePad.loadString(ResourceIDs.IDS_MSGTITLE),
				JNotePad.loadString(ResourceIDs.IDS_MSGNOFEATUREINIT)+featureName,
				UIMessageBox.STOP, UIButtonBar.OK);
			_box_.doModal();
			
		}
		catch (NullPointerException e3)
		{
			// can't load/init plug in feature
			UIMessageBox _box_ = new UIMessageBox(new UIFrame(), 
				JNotePad.loadString(ResourceIDs.IDS_MSGTITLE),
				JNotePad.loadString(ResourceIDs.IDS_MSGNOFEATUREINIT)+featureName,
				UIMessageBox.STOP, UIButtonBar.OK);
			_box_.doModal();
			
		}
		
		return ret;
	}

	protected boolean doHelpAbout()
	{
		// Create an About JNotepad dialog.
		JNoteDialog dialog = new JNoteDialog(parentFrame, "JNotepad", true);
		// Load the dialog box from the resource file
		dialog.loadDialog( JNotePad.getResources(), IDR_DIALOG_ABOUT);
		dialog.display();
		return true;
	}

	protected boolean doProperties()
	{
		// Create and display a properties dialog, which displays file statistics.
		JNoteStatsDialog dialog = new JNoteStatsDialog(parentFrame, getFileTarget());
		dialog.display();
		return true;
	}

	protected boolean doTimeDate()
	{
		// insert a time/date stamp, just like Notepad does
		insertTimeDate();
		return true;
	}

	protected boolean doEmacsCut()
	{
		emacsCut();
		return true;
	}

	protected boolean doEmacsPaste()
	{
		emacsPaste();
		return true;
	}
}


