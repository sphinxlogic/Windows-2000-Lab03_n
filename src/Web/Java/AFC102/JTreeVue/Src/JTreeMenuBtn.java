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

	public boolean launch()
	{
		boolean ret = super.launch();
		list.setSelectedIndex(0);
		list.getSelectedItem().requestFocus();
		return(ret);
	}

	public void ended(Event evt)
	{
		super.ended(evt);
		if ( !node.justchangedfocus )
			node.requestFocus();
		node.justchangedfocus = false;
	}
}

