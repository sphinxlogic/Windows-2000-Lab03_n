//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
/**
*	JNoteSettings
*
*	JNotepad specific extension of the SettingsObject class. This only adds
*	a method to load the SettingsObject with default values for JNotepad.
*
*	@version	1.0, 7/31/97
*	@see		@SettingsObject
*/

import SettingsObject;
import java.util.*;
import com.ms.ui.*;
import com.ms.fx.*;

public class JNoteSettings extends SettingsObject
{
	Hashtable strToCharTable;					// table to convert key names into the characters they represent.
	
	/**
	*	JNoteSettings constructor. Creates a new blank JNoteSettings object
	*
	*	@param filename File to keep settings information in.
	*/
	public JNoteSettings(String filename)
	{
		super(filename);
		init();
	}
	
	/**
	*	Private init function. Loads the strToCharTable with string names for
	*	certain characters that cannot be easily represented in a text file.
	*/
	private void init()
	{
		strToCharTable = new Hashtable(1); // !!! expand?
		
		strToCharTable.put("tab", new Character('\t'));
	}
	
	/**
	*	Loads the JNoteSettingsObject from the INI file. If the file could not
	*	be loaded, load in the default settings.
	*
	*	@returns	true
	*/
	public boolean load()
	{
		if (!super.load())
		{
			loadDefaults();
		}
		
		return true;
	}
	
	/**
	*	Loads default JNotepad-specific values into the JNoteSettings object.
	*	This loads the toolbars, feature lists, accelerators, and everything
	*	else with factory defaults.
	*/
	protected void loadDefaults()
	{
		// define the toolbar
		put("Toolbar","0","CMD_New");
		put("Toolbar","1","CMD_Open");
		put("Toolbar","2","CMD_Save");
		put("Toolbar","3","CMD_Find");
		put("Toolbar","4","CMD_Cut");
		put("Toolbar","5","CMD_Copy");
		put("Toolbar","6","CMD_Paste");
		put("Toolbar","7","CMD_Undo");
		put("Toolbar","8","CMD_Redo");
				
		// definitions for each button on the toolbar
		put("CMD_New", "Image", "Images\\new.gif");
		put("CMD_New", "CMD", "4021");
		put("CMD_New", "Tip", "101");

		put("CMD_Open", "Image", "Images\\open.gif");
		put("CMD_Open", "CMD", "4022");
		put("CMD_Open", "Tip", "102");

		put("CMD_Save", "Image", "Images\\save.gif");
		put("CMD_Save", "CMD", "4023");
		put("CMD_Save", "Tip", "103");

		put("CMD_Find", "Image", "Images\\find.gif");
		put("CMD_Find", "CMD", "4017");
		put("CMD_Find", "Tip", "115");

		put("CMD_Cut", "Image", "Images\\cut.gif");
		put("CMD_Cut", "CMD", "1001");
		put("CMD_Cut", "Tip", "107");

		put("CMD_Copy", "Image", "Images\\copy.gif");
		put("CMD_Copy", "CMD", "1002");
		put("CMD_Copy", "Tip", "108");

		put("CMD_Paste", "Image", "Images\\paste.gif");
		put("CMD_Paste", "CMD", "1003");
		put("CMD_Paste", "Tip", "109");

		put("CMD_Undo", "Image", "Images\\undo.gif");
		put("CMD_Undo", "CMD", "4026");
		put("CMD_Undo", "Tip", "105");

		put("CMD_Redo", "Image", "Images\\redo.gif");
		put("CMD_Redo", "CMD", "4004");
		put("CMD_Redo", "Tip", "106");

		// we have no GIF for NextWindow, so we use the boring new.gif one
		// we shouldn't need any gifs for it
		put("CMD_NextWindow", "Image", "Images\\new.gif");
		put("CMD_NextWindow", "CMD", "4015");
		put("CMD_NextWindow", "Tip", "1");

		// we have no GIF for PrevWindow, so we use the boring new.gif one
		// we shouldn't need any gifs for it
		put("CMD_PrevWindow", "Image", "Images\\new.gif");
		put("CMD_PrevWindow", "CMD", "4027");
		put("CMD_PrevWindow", "Tip", "1");

		// we have no GIF for SelectAll, so we use the boring new.gif one
		// we shouldn't need any gifs for it
		put("CMD_SelectAll", "Image", "Images\\new.gif");
		put("CMD_SelectAll", "CMD", "4013");
		put("CMD_SelectAll", "Tip", "1");

		// we have no GIF for Replace, so we use the boring new.gif one		
		// we shouldn't need any gifs for it
		put("CMD_Replace", "Image", "Images\\new.gif");
		put("CMD_Replace", "CMD", "4019");
		put("CMD_Replace", "Tip", "1");

		// accelerator keys
		put("Accelerators","ctrl-f", "CMD_Find");
		put("Accelerators","ctrlshift-tab", "CMD_PrevWindow");
		put("Accelerators","ctrl-a", "CMD_SelectAll");
		put("Accelerators","ctrl-s", "CMD_Save");
		put("Accelerators","ctrl-tab", "CMD_NextWindow");
		put("Accelerators","ctrl-o", "CMD_Open");
		put("Accelerators","ctrl-n", "CMD_New");
		put("Accelerators","ctrl-h", "CMD_Replace");

		// colors
		put("Colors", "Bright Red", "255 0 0");
		put("Colors", "Red", "128 0 0");
		put("Colors", "Dark Red", "64 0 0");
		put("Colors", "Bright Blue", "0 0 255");
		put("Colors", "Blue", "0 0 128");
		put("Colors", "Dark Blue", "0 0 64");
		put("Colors", "Bright Green", "0 255 0");
		put("Colors", "Green", "0 128 0");
		put("Colors", "Dark Green", "0 128 0");
		put("Colors", "Yellow", "255 255 0");
		put("Colors", "White", "255 255 255");
		put("Colors", "Black", "0 0 0");
	
		// java files get these colors/fonts/features
		put("JAVA", "Background", "Blue");
		put("JAVA", "Foreground", "White");
		put("JAVA", "Features", "BraceMatchFeature");			
		
		put("INI", "Background", "White");
		put("INI", "Foreground", "Green");
		put("INI", "Font", "Courier PLAIN 12");

		put("INF", "Background", "White");
		put("INF", "Foreground", "Red");
		put("INF", "Font", "Courier PLAIN 12");

		put("TXT", "Background", "White");
		put("TXT", "Foreground", "Black");
		put("TXT", "Font", "Arial PLAIN 14");

		put("DEFAULT", "Background", "White");
		put("DEFAULT", "Foreground", "Black");
		put("DEFAULT", "Font", "Arial PLAIN 14");
		
	}
	
	/**
	*	Loads accelerators from the "Accelerators" section of the JNoteSettings
	*	object. Adds them to the passed <a href="AcceleratorFeature.htm">AcceleratorFeature</a>
	*
	*	@param accel AcceleratorFeature to load with accelerator keys.
	*/
	public void loadAccelerators(AcceleratorFeature accel)
	{
		Enumeration e = getKeys("Accelerators");
		
		if (e == null)
		{
			return;
		}
		
		while (e.hasMoreElements())
		{
			String keyStr = (String)e.nextElement();
			// grab the name of the section which holds the definition for this command
			String sectionName = get("Accelerators", keyStr, "");
	
			// pull out the command ID number from this section
			String valueStr = get(sectionName, "CMD", null);

			String accelType = null;
			char cAccelKey;
			
			keyStr.toLowerCase();
			
			int iIndex = keyStr.indexOf('-');
			if ((iIndex == -1) || (valueStr == null))
			{
				// ini accel error
				UIMessageBox box = new UIMessageBox(new UIFrame(), 
					JNotePad.loadString(ResourceIDs.IDS_MSGTITLE),
					JNotePad.loadString(ResourceIDs.IDS_MSGINIACCELERR),
					box.STOP, UIButtonBar.OK);
				box.doModal();
				
				return;
			}
			
			// parse out the type of accelerator key from the key itself
			accelType = keyStr.substring(0, iIndex);
			cAccelKey = keyStr.charAt(iIndex+1);
			
			if (iIndex != keyStr.length()-2)
			{
				Character c = (Character)strToCharTable.get(keyStr.substring(iIndex+1));
				if (c != null)
				{
					cAccelKey = c.charValue();
				}
				else
				{
					cAccelKey = 0;
				}
			}
			
			// check if we're using ctrl-key combos or ctrl-shift-key.
			boolean bUseShift = (accelType.equals("ctrlshift") ? true : false);
			
			accel.addAccelerator(cAccelKey, valueStr, bUseShift);
		}
	}
	
	/**
	*	Retrieves an FxColor from the JNoteSettings object. The FxColor is
	*	stored as a string of three integers separated by spaces which 
	*	encode the RGB value of the color. For example, bright blue 
	*	is "255 0 0". This function takes the name of a color, looks it up,
	*	and converts it to an FxColor.
	*
	*	@param	key	The key to retrieve
	*	@param	def	The default value to return if the key isn't present in
	*				the JNoteSettings object.
	*
	*	@returns	The FxColor of the color named in the string, or null
	*				if the key was not in the registry.
	*/
	public FxColor getColor(String key, FxColor def)
	{
		String colorValue = get("Colors", key, null);
		
		if (colorValue == null)
		{
			return def;
		}
		
		// grab the positions of the spaces that separate the
		// numbers. 
		int iFirstSpace = colorValue.indexOf(' ');
		int iSecondSpace = colorValue.lastIndexOf(' ');
		
		// quit if the string isn't correctly formatted
		if ((iFirstSpace == -1) || (iSecondSpace == -1))
		{
			return null;
		}
		
		// pull out color numbers and turn them into ints
		int iRed = Integer.parseInt(colorValue.substring(0, iFirstSpace));
		int iGreen = Integer.parseInt(colorValue.substring(iFirstSpace+1, iSecondSpace));
		int iBlue = Integer.parseInt(colorValue.substring(iSecondSpace+1));
		
		return new FxColor(iRed, iGreen, iBlue);
	}
	
	
	/**
	*	Retrieves an FxColor from the JNoteSettings object indirectly. 
	*	The value at the key will be looked up in the color section of
	*	the JNoteSettings object. The color there will be returned. This
	*	lets one put a color name into the JNoteSettings object and have
	*	an FxColor object returned.
	*	
	*
	*	@param	section	The name of the section to retrieve the key from
	*	@param	key	The key to retrieve
	*	@param	def	The default value to return if the key isn't present in
	*				the JNoteSettings object.
	*
	*	@returns	The FxColor of the color described in the string, or null
	*				if the key was not in the registry.
	*/
	public FxColor getColorIndirect(String section, String key, FxColor def)
	{
		String colorName = get(section, key, null);
		
		if (colorName == null)
		{
			return def;
		}
		
		return getColor(colorName, def);
	}
	
	
	/**
	*	Retrieves an FxFont from the JNoteSettings object. The FxFont is
	*	stored in a string with the name of the font, the style (BOLD,
	*	ITALIC, or PLAIN) and the size, separated by space. 
	*	For example, "Dialog PLAIN 12" is a 12 point plain Dialog font. 
	*	This function looks up a key in the JNoteSettings and converts 
	*	it to an FxFont.
	*
	*	@param	section	The name of the section to retrieve the key from
	*	@param	key	The key to retrieve
	*	@param	def	The default value to return if the key isn't present in
	*				the JNoteSettings object.
	*
	*	@returns	The FxFont of the font described in the string, or null
	*				if the key was not in the registry.
	*/
	public FxFont getFont(String section, String key, FxFont def)
	{
		String font = get(section, key, null);
		
		if (font == null)
		{
			return def;
		}
		
		// grab the positions of the spaces that separate the
		// numbers. 
		int iFirstSpace = font.indexOf(' ');
		int iSecondSpace = font.lastIndexOf(' ');
		
		// quit if the string isn't correctly formatted
		if ((iFirstSpace == -1) || (iSecondSpace == -1))
		{
			return null;
		}
		
		// pull out values from the string which we'll use to construct
		// an FxFont object,
		String fontName = font.substring(0, iFirstSpace);
		String style = font.substring(iFirstSpace+1, iSecondSpace).toUpperCase();
		int iSize = Integer.parseInt(font.substring(iSecondSpace+1));
		int iStyle = 0;
		
		if (style.equals("PLAIN"))
		{
			iStyle = FxFont.PLAIN;
		}
		else if (style.equals("BOLD"))
		{
			iStyle = FxFont.BOLD;
		}
		else if (style.equals("ITALIC"))
		{
			iStyle = FxFont.ITALIC;
		}
		else
		{
			// ini font error
			UIMessageBox _box_ = new UIMessageBox(new UIFrame(), 
				JNotePad.loadString(ResourceIDs.IDS_MSGTITLE),
				JNotePad.loadString(ResourceIDs.IDS_MSGINIFONTERR),
				UIMessageBox.STOP, UIButtonBar.OK);
			_box_.doModal();
			
		}
		
		return new FxFont(fontName, iStyle, iSize);
	}
	
}

