//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import com.ms.ui.*;
import com.ms.ui.resource.*;
import java.awt.*;

/**
*	An extension of UIDialog which emulates, to a certain extent, a Windows
*	dialog box. Several helper functions have been added which are called at
*	certain stages in the dialog's creation and display. Inherit from this
*	class and override the helper functions.
*	
*	@version	1.0, 7/20/97
*/

public class JNoteDialog extends UIDialog implements IConstants
{
	/**
	*	Parent frame
	*/
	protected UIFrame parentFrame;
	
	/**
	*	Creates a new JNoteDialog
	*
	*	@param	parentframe	Parent frame 
	*	@param	title	Title of the dialog
	*	@param	isModal	true if the dialog is to be run as a modal dialog box, false if it is to be modeless
	*/
	public JNoteDialog(UIFrame parentframe, String title, boolean isModal)
	{
		super(parentframe, title, isModal);
		init(parentframe);
	}
	
	/**
	*	Private init function. Sets the parent frame variable.
	*/
	private void init(UIFrame parentframe)
	{
		parentFrame = parentframe;			
	}
	
	/**
	*	Loads the dialog from a resource file. Fills the current dialog
	*	box with the controls read in from a res file. Uses Win32ResourceDecoder.
	*
	*	@param	resFile	Name of resource file to load from
	*	@param	dialogID	integer identifier of the dialog resource to load
	*	@returns	true if the loading succeeded, false if it did not.
	*/
	public boolean loadDialog(String resFile, int dialogID)
	{
		Win32ResourceDecoder resdec;
		
		try
		{
			resdec = new Win32ResourceDecoder(resFile);
		}
		catch (Exception e) // !!!!!! Bad!
		{
			// dialog could not be loaded
			UIMessageBox box = new UIMessageBox(new UIFrame(), 
				JNotePad.loadString(ResourceIDs.IDS_MSGTITLE),
				JNotePad.loadString(ResourceIDs.IDS_MSGNODIALOG),
				box.STOP, UIButtonBar.OK);
			box.doModal();
			
			return false;
		}
		return loadDialog(resdec, dialogID);
	}
		
	public boolean loadDialog(Win32ResourceDecoder resFile, int dialogID)
	{
		try 
		{
			resFile.populateDialog(this, dialogID);
		}
		catch (Exception e)
		{
			// couldn't load dialog
			UIMessageBox box = new UIMessageBox(new UIFrame(), 
				JNotePad.loadString(ResourceIDs.IDS_MSGTITLE),
				JNotePad.loadString(ResourceIDs.IDS_MSGNODIALOG),
				box.STOP, UIButtonBar.OK);
			box.doModal();
			
			return false;
		}		
		
		return true;
	}
	
	/**
	*	Displays the dialog. Centers the dialog in the middle of the screen,
	*	calls initDialog(), and then shows it. Use this method, instead of show(),
	*	to display your dialog.
	*/
	public void display()
	{
		position(false);
		initDialog();
		show();
	}
	
	/**
	*	Called right before the dialog is to be displayed. Override this to
	*	perform pre-display initialization of the dialog.
	*/
	protected void initDialog()
	{
		// set focus to the OK button
		getComponentFromID(IDR_FILEOPTIONS_OK).requestFocus();
	}
	
	/**
	*	Called when the dialog is closed. Hides the dialog. Override this
	*	to add any cleanup that is necessary, but be sure to call the superclass's
	*	method too.
	*/
	protected void closeDialog()
	{
		setVisible(false);
	}
	
	/**
	*	Called when the OK button is clicked. Default action is to close the dialog
	*	by calling closeDialog(). Override this if custom functionality is needed.
	*/
	protected void onOK()
	{
		closeDialog();
	}
	
	/**
	*	Called when the Cancel button is clicked. Default action is to close the dialog
	*	by calling closeDialog(). Override this if custom functionality is needed.
	*/	 
	protected void onCancel()
	{
		closeDialog();
	}
	
	/**
	*	Called when a button is clicked. Default action is to do nothing. Override
	*	this to add custom functionality.
	*
	*	@param	buttonID	Resource ID of the button that was clicked.
	*	@param	buttonName	Name of button that was clicked.
	*/
	protected void onButton(int buttonID, String buttonName)
	{
	}
	
	/**
	*	Handles events that occur in the dialog box. Calls onOK() if OK is clicked,
	*	onCancel() if cancel is clicked, and onButton() if any other button is clicked.
	*
	*	@param	evt	Event which is being handled
	*	@returns	true if the event was handled, false if not
	*/
	public boolean handleEvent(Event evt)
	{			
		if ((evt.target instanceof UIButton) &&
			(evt.id == Event.ACTION_EVENT))
		{
			int buttonID = ((UIButton)evt.target).getID();
			if (buttonID == IDR_FILEOPTIONS_OK)
			{
				onOK();
			}
			else if (buttonID == IDR_FILEOPTIONS_CANCEL)
			{
				onCancel();
			}						
			else
			{
				onButton(buttonID, ((UIButton)evt.target).getName());
			}
			
			return true;
		}
		
		return super.handleEvent(evt);
	}
	
}

