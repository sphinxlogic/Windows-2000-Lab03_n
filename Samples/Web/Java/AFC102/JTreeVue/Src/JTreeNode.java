//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.Event;
import java.io.StreamTokenizer;
import java.util.Vector;

import com.ms.ui.*;
import com.ms.fx.*;

public class JTreeNode extends UIPanel implements JTreeConsts
{
	public JTreeNodeInfo info;
	private JTreeNodeItem item;

	private JTCallbacks callback = null;
	private UIMenuList extimpl = null;
	private JTreeMenuBtn btn = null;
	public boolean justchangedfocus = false;

	public JTreeNode(String name)
	{
		setLayout(new UIBorderLayout(4,0));
		info = new JTreeNodeInfo(name);
		item = new JTreeNodeItem(name);
		add(item, "Center");
		setHeader(item);
	}

	public JTreeNode(StreamTokenizer tokstrm, JTCallbacks callback)
	{
		this.callback = callback;
		this.info = new JTreeNodeInfo(tokstrm);
		setLayout(new UIBorderLayout(4,0));
		item = new JTreeNodeItem(info);
		if ( item.prefix != null )
			add(item.prefix, "West");
		add(item, "Center");
		setHeader(item);
	}

	public void addExtImpl(JTreeNodeInfo info)
	{
		// First Time Through add "Implements..." or "Extends..." button
		if ( extimpl == null) {
			extimpl = new UIMenuList();
			
			btn = new JTreeMenuBtn("Implements...", extimpl, this);
			if ( info.type == HTI_IFACE )
				btn.setName("Extends...");
			btn.setBackground(BaseColor.getColor(new FxColor(202, 202, 212)));
			add(btn, "East");
		}
		extimpl.add(new UIMenuItem(info.name));
	}

	public void setSelected(boolean on)
	{
		super.setSelected(on);
		((JTreeNodeItem)getHeader()).setSelected(on);
	}

	public boolean action(Event e, Object arg)
	{
		UIMenuItem item;

		if ( arg instanceof UIMenuItem ) {
			item = (UIMenuItem)arg;
			JTreeNode node = (JTreeNode)callback.getHTable().get(item.getName());
			if ( node != null ) {
				callback.dispatchInfo(node);
				justchangedfocus = true;
			}
			else 
				System.out.println("Not in HashTable");
		}
		return super.action(e, arg);
	}

	public boolean keyDown(Event  evt, int  key)
	{
		switch(key) {
		// TAB KEY
		case 9:
			if ( btn != null )
				btn.launch();
			break;

		default:
			return super.keyDown(evt, key);
		}
		return true;
	}

	public String getFullName() { return item.getFullName(); }
	public String getName() { return item.getName(); }
}
