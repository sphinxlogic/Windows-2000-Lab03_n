//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
//
//
// SettingsObject
//
// Class to encapsulate the file (or whatever) that is going to 
// store program settings.
// We keep everything in memory, so make sure you don't store
// TOO much stuff in here. :)
// 7/30/97 TJS

import java.io.*;
import java.util.*;
import com.ms.ui.*;
import com.ms.fx.FxToolkit;

public class SettingsObject 
{
	private Hashtable settingsTable;
	private String sFileName;
	
	public SettingsObject(String filename)
	{
		init(filename);
	}
	
	private void init(String filename)
	{
		sFileName = filename;
		settingsTable = new Hashtable(5);
	}
	
	protected void loadDefaults()
	{
	}
	
	// internal method to set an option
	private void setValue(String section, String key, String value)
	{
		Hashtable sectionTable = (Hashtable)settingsTable.get(section);
		if (sectionTable == null)
		{
			sectionTable = new Hashtable(11);
			settingsTable.put(section, sectionTable);					
		}
		
		sectionTable.put(key, value);		
	}
	
	// internal method to get an option. 
	private String getValue(String section, String key)
	{
		Hashtable sectionTable = (Hashtable)settingsTable.get(section);
		if (sectionTable == null)
		{
			return null;
		}
		
		return (String)sectionTable.get(key);
	}
	
	// public methods to set options. We overload the setOption
	// method to let you pass it strings, ints, or booleans. 
	// All are converted to strings and then saved using setValue()
	public void put(String section, String key, String value)
	{
		setValue(section, key, value);
	}
	
	public void put(String section, String key, int value)
	{
		setValue(section, key, String.valueOf(value));
	}
	
	public void put(String section, String key, boolean value)
	{
		setValue(section, key, String.valueOf(value));
	}
	
	// bunch of get() methods. Different methods allow you
	// to have data returned in String, int, or boolean format.
	// returns the last parameter passed if the key was not found.
	
	// get() is the default method to grab data from this table...
	// it returns a String. It's the same as getString()
	public String get(String section, String key, String def)
	{
		return getString(section, key, def);
	}
	
	public String getString(String section, String key, String def)
	{
		String s = getValue(section, key);
		
		if (s != null)
		{
			return s;
		}
		else
		{
			return def;
		}
	}	
	
	public int getInt(String section, String key, int def)
	{
		int i = 0;
		try
		{
			i = Integer.parseInt(getValue(section, key));
		}
		catch (NumberFormatException e)
		{
			i = def;
		}
		
		return i;
	}
	
	// getOptionBoolean() returns either false if the string
	// is not equal to "true", so there's no need to pass
	// a default value.
	public boolean getBoolean(String section, String key)
	{
		return Boolean.valueOf(getValue(section, key)).booleanValue();
	}	
	
	public Enumeration getKeys(String section)
	{
		Hashtable sectionTable = (Hashtable)settingsTable.get(section);
		if (sectionTable == null)
		{
			return null;
		}
		return sectionTable.keys();
	}
	
	public boolean load()
	{
		DataInputStream inputStream = null;
		
		try 
		{
			inputStream = new DataInputStream(new FileInputStream(sFileName));
		}
		catch (IOException e)
		{
			// error reading settings file, using default settings
			UIMessageBox _box_ = new UIMessageBox(new UIFrame(), 
				JNotePad.loadString(ResourceIDs.IDS_MSGTITLE),
				JNotePad.loadString(ResourceIDs.IDS_MSGNOSETTINGS),
				UIMessageBox.STOP, UIButtonBar.OK);
			_box_.doModal();
			
			return false;
		}
		
		boolean ret = true;
		
		try
		{
			readData(inputStream);
		}
		catch (IOException e)
		{
			// error reading settings
			UIMessageBox _box_ = new UIMessageBox(new UIFrame(), 
				JNotePad.loadString(ResourceIDs.IDS_MSGTITLE),
				JNotePad.loadString(ResourceIDs.IDS_MSGSETTINGSERR),
				UIMessageBox.STOP, UIButtonBar.OK);
			_box_.doModal();
			
			ret = false;
		}
		
		try
		{
			inputStream.close();
		}
		catch (IOException e)
		{
		}
		
		return ret;
	}
	
	public boolean save()
	{
		DataOutputStream outputStream = null;
		
		try 
		{
			outputStream = new DataOutputStream(new FileOutputStream(sFileName));
		}
		catch (IOException e)
		{
			// error saving settings
			UIMessageBox _box_ = new UIMessageBox(new UIFrame(), 
				JNotePad.loadString(ResourceIDs.IDS_MSGTITLE),
				JNotePad.loadString(ResourceIDs.IDS_MSGSETTINGSSAVEERR),
				UIMessageBox.STOP, UIButtonBar.OK);
			_box_.doModal();														
			
			return false;
		}
		
		boolean ret = true;
		
		try
		{
			writeData(outputStream);
		}
		catch (IOException e)
		{
			ret = false;
		}
		
		try
		{
			outputStream.close();
		}
		catch (IOException e)
		{
		}
		
		return ret;
	}
	
	private void writeData(DataOutputStream outputStream) throws IOException
	{
		Enumeration e = settingsTable.keys();
		while (e.hasMoreElements())
		{	
			String sectionName = (String)e.nextElement();
			Hashtable sectionTable = (Hashtable)settingsTable.get(sectionName);
			
			outputStream.writeBytes("\r\n["+sectionName+"]\r\n");
			
			Enumeration e2 = sectionTable.keys();
			while (e2.hasMoreElements())
			{
				String key = (String)e2.nextElement();
				String value = (String)sectionTable.get(key);
				// !! This should be an unnecessary test
				if (value == null)
				{
					return;
				}
				
				outputStream.writeBytes(key+"="+value+"\r\n");
			}				
		}
		
		return;
	}
	
	private void readData(DataInputStream inputStream) throws IOException
	{
		String s = null;
		String sectionName = null;
		String key = null;
		String value = null;
		
		clear();
		
		while ((s = inputStream.readLine()) != null)
		{		
			if (s.length() > 0)
			{
				if (s.charAt(0) == '[')
				{
					sectionName = s.substring(1, s.length()-1);
				}
				else
				{
					int iIndex = s.indexOf('=');
					if (iIndex < 0)
					{
						throw new IOException();
					}
					key = s.substring(0, iIndex);
					value = s.substring(iIndex+1);
					
					setValue(sectionName, key, value);
				}
			}
		}
	}
	
	public void clear()
	{
		Enumeration e = settingsTable.elements();
		
		while (e.hasMoreElements())
		{
			((Hashtable)e.nextElement()).clear();
		}
		
		settingsTable.clear();
	}		
	
}

