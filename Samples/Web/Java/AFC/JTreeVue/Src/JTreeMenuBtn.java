//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.*;
import java.io.*;
import java.util.Enumeration;

import com.ms.ui.*;

class JTreeMenuBtn extends UIMenuButton
{
	private UIMenuList list;
	private JTreeNode node;

	public JTreeMenuBtn(String str, UIMenuList list, JTreeNode node)
	{
		super(str, 0, list);
		this.list = list;
		this.node = node;
	}

	//
	// override launch so the first item in the menu can show as selected,
	//  so user can use keyboard (enter or space) to generate action.
	//
	public boolean launch()
	{
		boolean ret = super.launch();
		list.setSelectedIndex(0);
		return ret;
	}
}

