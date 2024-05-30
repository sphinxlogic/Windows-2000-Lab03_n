//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
/**
*	JNoteToolbar
*
*	Toolbar class. Operates on objects that implement the IFileOperationTarget
*	interface, which contains common file operations. Also implements changing
*	application settings.
*
*	The IFileOperationTarget will have certain methods called when the user
*	clicks file-related buttons on the toolbar.
*
*	@version	1.0, 7/10/97
*	@see		IFileOperationTarget
*	@see		SettingsObject
*/

import com.ms.ui.*;
import java.awt.*;
import com.ms.fx.*;
import java.io.File;
import java.io.*;
import java.util.*;
import java.awt.image.*;
import java.net.URL;
import com.ms.ui.resource.*;
import com.ms.util.*;
import com.ms.awt.image.StreamedImageSource;

public class JNoteToolbar extends UIBand implements ICommandFeedback
{
	/**
	*	The hashtable that holds the buttons in the toolbar
	*/
	protected Hashtable buttonTable;
	
	/**
	*	Foreground color chooser control.	
	*/
	JNoteColorChoice colorChoiceFg;
	
	/**
	*	The applet that we're running from. If we're in standalone mode, this
	*	is null.
	*/
	UIApplet theApplet;
	
	/**
	*	Background color chooser control.
	*/
	JNoteColorChoice colorChoiceBg;
	
	/**
	*	Creates a JNoteToolbar.		
	*/
	
	/**
	*	Creates a JNoteToolbar.		
	*
	*	@param applet The applet which this is running from. This is null if we're running standalone
	*/
	public JNoteToolbar(UIApplet applet)
	{
		//super(IFxGraphicsConstants.EDGE_RAISED);
		super("", BREAK);
		colorChoiceFg=null;
		colorChoiceBg=null;
		
		init(applet);
	}
	
	/**
	*	Private init function. Initializes the button hash table and other
	*	variables.
	*
	*	@param applet The applet which this is running from. This is null if we're running standalone.
	*/
	private void init(UIApplet applet)
	{			
		theApplet = applet;
		buttonTable = new Hashtable(11);
	}
				
	
	/**
	*	Loads buttons and their from the settings object
	*	and places the button objects into the button table. Also adds JNoteColorChoice
	*	controls to the toolbar.
	*
	*	@param	 settings	Object which holds application settings information
	*/
	public void loadButtons(Win32ResourceDecoder res)
	{
		int i = 0;
		boolean bLoadedOK = true;
		
		MediaTracker mt = new MediaTracker(FxToolkit.getHelperFrame());
		MediaTracker grayMT = new MediaTracker(FxToolkit.getHelperFrame());
		
		JNoteSettings settings = JNoteAppSettings.getSettingsObj();
		
		String cmdSection=null;
		while ((cmdSection = settings.get("Toolbar", String.valueOf(i), null)) != null)
		{					
			if (cmdSection.length() == 0)
			{
				// toolbar load error
				UIMessageBox _box_ = new UIMessageBox(new UIFrame(), 
					JNotePad.loadString(ResourceIDs.IDS_MSGTITLE),
					JNotePad.loadString(ResourceIDs.IDS_MSGINITOOLBARERR),
					UIMessageBox.STOP, UIButtonBar.OK);
				_box_.doModal();
				
				cmdSection = "Default";
			}

			//
			// get the filename for the image
			// Get the resource ID for the tooltip
			// get the CMD id for the button.
			//
			String imageName = settings.get(cmdSection, "Image", "");
			String nameID = settings.get(cmdSection, "Tip", "");
			String name=null;

			try
			{
				name = res.getString( Integer.parseInt(nameID));
			}
			catch (Exception e)
			{
				name="";
			}
			String cmd = settings.get(cmdSection,"CMD","");
			int cmdID= Integer.parseInt(cmd);
			
			JNotePushButton button = null;
			Image im = null;
			UIGraphic grayGraphic = null;
			
			if (imageName != null)
			{
				im = loadImage(imageName);							
			}

			if ((imageName == null) || (im == null))
			{
				// if button image doesn't exist, pop up an error
				// box at the end of the button loading.
				button = new JNotePushButton(name);

				bLoadedOK = false;
			}
			else
			{
				//
				//
				//
				int iIndex = imageName.indexOf('.');
				if (iIndex > -1)
				{
					// the grayed out bitmap has a _ appended to the end of the normal bitmap's name
					String grayImageName = imageName.substring(0, iIndex)+"_"+imageName.substring(iIndex);
					
					File grayFile = new File(grayImageName);
					if (grayFile.exists())
					{
						Image grayIm;
						
						grayIm = loadImage(grayImageName);
						grayGraphic = new UIGraphic(grayIm);
						grayMT.addImage(grayIm, i);
					}
				}
				
				button = new JNotePushButton(new UIGraphic(im), grayGraphic, 0);
				button.setName(name);
				
				mt.addImage(im, i);
			}
			
			button.setID(cmdID);
			add(button);
			buttonTable.put(name, button);

			i++;
		}
		
		try
		{
			mt.waitForAll();
			grayMT.waitForAll();
		}
		catch (InterruptedException e)
		{
		}

		// add a color choice dropdown for selecting the text color
		UIPanel panel = new UIPanel();
		colorChoiceFg = new JNoteColorChoice(JNoteColorChoice.TEXTCOLOR);
		panel.add(colorChoiceFg);
		add(panel);

		// add a color choice dropdown for selecting the background color
		panel = new UIPanel();
		colorChoiceBg = new JNoteColorChoice(JNoteColorChoice.BACKCOLOR);
		panel.add(colorChoiceBg);
		add(panel);
			
		if (!bLoadedOK)
		{
			// ini graphic load error
			UIMessageBox _box_ = new UIMessageBox(new UIFrame(), 
				JNotePad.loadString(ResourceIDs.IDS_MSGTITLE),
				JNotePad.loadString(ResourceIDs.IDS_MSGINITIMGERR),
				UIMessageBox.STOP, UIButtonBar.OK);
			_box_.doModal();
			
		}
		
		repaint();
	}
	
	
	// ICommandFeedback methods
	
	/**
	*	Part of ICommandFeedback. Called when a command button needs to be enabled or disabled.
	*	Disables the button and grays it out.
	*	
	*	@see	ICommandFeedback
	*	@param	command	Name of button to enable or disable
	*	@param	on	true if button is to be enabled, false if it is to be disabled.
	*/
	public void enableCommand(String command, boolean on)
	{
		JNotePushButton button = (JNotePushButton)buttonTable.get(command);
		
		if (button != null)
		{
			button.setEnabled(on);
			button.repaint();
		}
	}
	
	/**
	*	Part of ICommandFeedback. Checks the enabled state of a button.
	*
	*	@param	command	Name of button to check
	*	@returns	true if button is enabled, false if it is not.
	*/
	public boolean isEnabled(String command)
	{
		JNotePushButton button = (JNotePushButton)buttonTable.get(command);
		
		if (button != null)
		{
			return button.isEnabled();					
		}
		else
		{
			return true;
		}
	}
	
	
	
	/**
	*	Part of ICommandFeedback. Called when a command button needs to be checked or unchecked.
	*	Sets the checkmark accordingly. This works only on UICheckButtons -- it has no effect
	*	on other buttons.
	*	
	*	@see	ICommandFeedback
	*	@param	command	Name of button to set the check on
	*	@param	on	true if button is to be checked, false if it is to be unchecked.
	*/
	public void setChecked(String command, boolean on)
	{
		Object obj = buttonTable.get(command);
		
		if ((obj != null) && (obj instanceof UICheckButton))
		{
			UICheckButton button = (UICheckButton)obj;
			
			button.setChecked(on);
			button.repaint();
		}
	}
	
	
	/**
	*	Called when a file is loaded. Adds filename to Most Recently Used (MRU) list.
	*	Part of ICommandFeedback. Does nothing in this class cause there's no 
	*	MRU list to add to.
	*
	*	@param	command	Name of file to add to MRU list
	*	@see	ICommandFeedback
	*/
	public void addToMRUList(String filename)
	{
	}
	
	/**
	*	Called when a control in the system changes color. Changes the colors
	*	in the JNoteColorChoice controls to reflect this change if the component
	*	being changed is the edit control.
	*
	*	@param	comp	Component who had a color change
	*	@param	color	Color that the component was changed to
	*	@param	whichPart	Which part of the component had a color change. This can
	*						be either FOREGROUND or BACKGROUND.
	*/		
	public void	notifyColorChange(Object comp, FxColor color, int whichPart)
	{			

		if (!(comp instanceof ITextOperationTargetExt))
		{
			return;
		}
		
		JNoteColorChoice colorChooser = null;
		if (whichPart == COLORCHANGE_FOREGROUND)
		{
			colorChooser = colorChoiceFg;
		}
		else
		{
			colorChooser = colorChoiceBg;
		}
		
		colorChooser.setSelectedColor(color);			
	}
	
	/**
	*	Loads an image file. Loads from the Toolkit if we're standalone or over
	*	the net if we're an applet.
	*	
	*	@param	imageName	Name of image to load
	*/
	protected Image loadImage(String imageName)
	{
		if (!JNoteAppletObject.isApplet())
		{
			// standalone
			ClassLoader cl=this.getClass().getClassLoader();

			InputStream is;
			if(cl!=null)
				is=cl.getResourceAsStream(imageName);
			else
				is=ClassLoader.getSystemResourceAsStream(imageName);
			if(is!=null)
				return Toolkit.getDefaultToolkit().createImage(new StreamedImageSource(is));
			return null;
		}
		else
		{
			// applet
			URL url = theApplet.getCodeBase();
			return theApplet.getImage(url, imageName);
		}
	}
	
	
}


/**
*	JNotePushButton
*
*  JNoteToolbar private class. This implements Tooltips in a standard UIPushButton.
*  The Tooltip displayed is the name of the control.
*
*	@version	1.0, 7/31/97
*	@see		JNoteToolbar
*/

class JNotePushButton extends UIPushButton
{
	private UIGraphic grayedImage = null;
	private UIGraphic normalImage = null;
	
	/**
	*	Creates a JNotePushButton with a text field.
	*
	*	@param text Text to display on button.
	*/
	public JNotePushButton(String text)
	{
		super(text);
		normalImage = null;
		grayedImage = null;		
	}
	/**
	*	Creates a JNotePushButton with a particular style and text.
	*
	*	@param text Text to display on button
	*	@param style Button style -- constants in <a href="com.ms.ui.UIPushButton">UIPushButton</a>.
	*/
	public JNotePushButton(String text, int style)
	{
		super(text, style);
		normalImage = null;
		grayedImage = null;
	}
	
	
	/**
	*	Creates a JNotePushButton which displays a IUIComponent, such as UIGraphic
	*	or UIStatic.
	*
	*	@param comp IUIComponent to display on button
	*/
	public JNotePushButton(IUIComponent comp)
	{
		super(comp);
		init(comp, null);
	}
	
	
	/**
	*	Creates JNotePushButton with a particular style and displaying a given IUIComponent.
	*
	*	@param comp IUIComponent to display
	*	@param style Style of button - constants in <a href="com.ms.ui.UIPushButton">UIPushButton</a>.
	*/
	public JNotePushButton(IUIComponent comp, int style)
	{
		super(comp, style);
		init(comp, null);
	}
	
	
	/**
	*	Creates JNotePushButton with a particular style and displaying a given IUIComponent.
	*	When disabled, the button displays the given image.
	*
	*	@param comp IUIComponent to display
	*	@param grayComp	IUIComponent to display when grayed out (disabled)
	*	@param style Style of button - constants in <a href="com.ms.ui.UIPushButton">UIPushButton</a>.
	*/
	public JNotePushButton(IUIComponent comp, IUIComponent grayComp, int style)
	{
		super(comp, style);
		init(comp, grayComp);
	}
	
	
	
	/**
	*	Private init method. Initializes the button with the given
	*	component and style. Also constructs a grayed out image for display
	*	when the button is disabled.
	*	
	*	@param	comp	Component to display on button
	*	@param	style	Style of button - constants constants in <a href="com.ms.ui.UIPushButton">UIPushButton</a>
	*/
	private void init(IUIComponent comp, IUIComponent grayComp)
	{
		if (comp instanceof UIGraphic)
		{
			normalImage = (UIGraphic)comp;
			
			if ((grayComp != null) && (grayComp instanceof UIGraphic))
			{
				grayedImage = (UIGraphic)grayComp;
			}
			else
			{
				makeGrayedImage(normalImage);
			}
		}
	}			
	
	/**
	*	Implements the getHelp() method for Tooltips. The text displayed
	*	by a Tooltip is whatever is returned from the getHelp() method.
	*	JNotePushButtons return the name of the button (getName()).
	*/
	public String getHelp()
	{
		return getName();
	}
	
	/**
	*	enables or disables the button. If there's an image, changes it to
	*	a grayed out version.
	*
	*	@param	on	true if the button is to be enabled, false if it is to be disabled.
	*	@returns	true
	*/
	public void setEnabled(boolean on)
	{
		if (isEnabled() == on)
		{
			return;
		}
		
		super.setEnabled(on);
		
		if (normalImage != null)
		{					
			UIGraphic image = null;
			
			if (on == false)
			{
				// set the current image to a grayed out image.
				image = grayedImage;
			}
			else
			{
				// reset the original image
				image = normalImage;						
			}
			
			replace(image, 0);
			
			repaint();
		}
	} 
	
	
	/**
	*	Private method to create a grayed version of the component and store
	*	it in grayedImage. Currently works only with UIGraphic objects. 
	*	Text strings gray automatically when disabled.
	*
	*	@param	comp	Component to gray out
	*/ 	
	private void makeGrayedImage(UIGraphic image)
	{
		// use a gray filter to gray out the image
		grayedImage = new UIGraphic( createImage(new FilteredImageSource(image.getImage().getSource(),
			new GrayImageFilter())) );
		
		
	}
	
}


/**
*	JNoteColorChoice
*
*	This is a private class to JNoteToolbar. It creates a dropdown color choice
*	list.
*
*	@version	1.0, 8/12/97
*
*	@see	JNoteToolbar
*/

class JNoteColorChoice extends UIChoice
{		
/**
*	Maps colors to items in the list
	*/
	private Hashtable colorTable;				
	
	/**
	*	whether this control displays foreground or background colors		
	*/
	private int iStyle;				
	
	/**
	*	foreground color style
	*/
	public static final int TEXTCOLOR = 1;
	
	/**
	*	background color style	
	*/
	public static final int BACKCOLOR = 2;
	
	/**
	*	Creates a new JNoteColorChoice.
	*
	*	@param	style	Style of the control. TEXTCOLOR indicates the control will
	*					display foreground colors, and BACKCOLOR indicates it will 
	*					display background colors.
	*/
	public JNoteColorChoice(int style)
	{
		colorTable = new Hashtable(10);
		init(style);
	}
	
	/**
	*	Private init method. Creates the UIChoice control and adds color bars to it.
	*
	*	@param	style	Style of the control. See <a href="JNoteColorChoice">JNoteColorChoice</a> 
	*					for details.
	*/
	private void init(int style)
	{
		iStyle = style;
		
		// grab settings object
		JNoteSettings settings = JNoteAppSettings.getSettingsObj();
		
		// fill vector with the color names
		Vector svector = new Vector(10);
		Enumeration e = settings.getKeys("Colors");
		
		while (e.hasMoreElements())
		{
			svector.addElement(e.nextElement());
		}
				
		// sort the vector so we get the colors in alpha order
		VectorSort.sort(svector, new StringComparison());

		e = svector.elements();
		
		while (e.hasMoreElements())
		{
			String colorName = (String)e.nextElement();
			FxColor color = settings.getColor(colorName, null);
			
			if (color == null)
			{
				// ini color load error
				UIMessageBox _box_ = new UIMessageBox(new UIFrame(), 
					JNotePad.loadString(ResourceIDs.IDS_MSGTITLE),
					JNotePad.loadString(ResourceIDs.IDS_MSGINICOLORERR),
					UIMessageBox.STOP, UIButtonBar.OK);
				_box_.doModal();
				
				return;
			}
			
			addColorBar(colorName, color);						
		}
		
		
		// add a box for custom color. This usually launches a color dialog.
		
		UIStatic custom;
		
		if (iStyle == TEXTCOLOR)
		{
			custom = new UIText("Custom...", UIText.LEFT);
			custom.setForeground(FxColor.getExtendedColor(Color.black));
		}
		else
		{
			custom = new UIText("Custom...", UIText.LEFT);
			custom.setBackground(FxColor.getExtendedColor(Color.lightGray));
		}
		
		//choiceControl.add(custom);
		add(custom);
		
		//add(choiceControl);
		
		//choiceControl.repaint();
		repaint();
	}
	
	/**
	*	Adds a component to the end of the list. Also adds its color value
	*	to the hashtable so you can do a lookup of components by color.
	*
	*	@param	comp	Component to be added
	*/
	public IUIComponent add(IUIComponent comp)
	{
		super.add(comp);
		FxColor color = null;
		
		if (iStyle == TEXTCOLOR)
		{
			color = FxColor.getExtendedColor(comp.getForeground());
		}
		else
		{
			color = FxColor.getExtendedColor(comp.getBackground());
		}				
		
		// if the item we're adding is the Custom... item (which isn't
		// really a color - it launches a color menu), add its name
		// as the key instead of its color. We use this later.
		if (!(comp.getName().equals("Custom...")))
		{
			colorTable.put(color, comp);						
		}
		else
		{
			colorTable.put(comp.getName(), comp);
		}
		
		return comp;
	}
	
	/**
	*	adds a color bar. 
	*
	*	@param	colorname	Name of the color
	*	@param	color	Color object
	*/
	public void addColorBar(String colorname, FxColor color)
	{	
		UIStatic s = new UIText(colorname, UIText.LEFT);
		
		// create an inverse color
		int red = color.getRed() - 255;
		int green = color.getGreen() - 255;
		int blue = color.getBlue() - 255;
		
		if (red < 0) red = -red;
		if (green < 0) green = -green;
		if (blue < 0) blue = -blue;	
		
		FxColor inverse = new FxColor((red << 16) | (green << 8) | (blue));
		
		if (iStyle == TEXTCOLOR)
		{
			s.setForeground(color);							
			//s.setForeground(color.getShadow());
		}
		else
		{
			s.setBackground(color);
			//s.setForeground(color.getDarkShadow());
			s.setForeground(inverse);
		}
		
		//choiceControl.add(s);
		add(s);
	}	
	
	/**
	*	Sets the selection to an element in the list which is of the
	*	given color.
	*
	*	@param	color	Color to set the UIChoice to
	*/
	public void setSelectedColor(FxColor color)
	{				
		IUIComponent comp = (IUIComponent)colorTable.get(color);
		
		if (comp != null)
		{
			setSelectedItem(comp);
		}
		else
		{
			comp = (IUIComponent)colorTable.get("Custom...");
			if (comp != null)
			{
				setSelectedItem(comp);
			}
		}
	}
	
	public String getHelp()
	{
		if (iStyle == TEXTCOLOR)
		{
			return "Change Text Color";
		}
		else
		{
			return "Change Background Color";
		}
		
	}
}

/**
*	Private class to be used with SortedVectors. Compares two colors
*	
*	@version	1.0, 7/28/97
*/
class StringComparison implements Comparison
{
	/**
	*	Compares two objects.	
	*
	*	@returns	negative if a < b, 0 if a == b, positive if a > b
	*/
	public int compare(Object p, Object q)
	{
		if ((p instanceof String) || (q instanceof String))
		{
			return ((String)p).compareTo((String)q);
		}
		return 0;
	}
}

