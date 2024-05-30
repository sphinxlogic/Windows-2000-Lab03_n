//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.io.*;

import com.ms.ui.*;
import com.ms.fx.*;

class JTreeNodeItem extends UIItem implements JTreeConsts
{
	public UIText prefix = null;
	private String pkg = new String("");

	public JTreeNodeItem(String name)
	{
		super(null, name);
	}

	public JTreeNodeItem(JTreeNodeInfo nodeinfo)
	{
		super(null, nodeinfo.name);

		if ( !((nodeinfo.type == HTI_CLS) || (nodeinfo.type == HTI_IFACE)) )
			return;

		pkg = nodeinfo.pkg;

		prefix = new UIText("Java");
		prefix.setFont(new FxFont("Helvetica", FxFont.BOLD, 12));
		prefix.setBackground(BaseColor.getColor(new FxColor(127,170,212)));
		prefix.setForeground(BaseColor.getColor(new FxColor(0,42,127)));

		int len = pkg.length();

		if ( len >= 9 ) {
			String str = pkg.substring(0,9);
			if (str.equalsIgnoreCase("java.awt.")) {
				prefix.setName("AWT");
				prefix.setForeground(BaseColor.getColor(new FxColor(127,153,0)));
			}
			else if ( len >= 10 ) {
				str = pkg.substring(0,10);
				if ( str.equalsIgnoreCase("com.ms.ui.") ) {
					prefix.setName("UI");
					prefix.setForeground(BaseColor.getColor(new FxColor(170,42,0)));
				}
				else if ( str.equalsIgnoreCase("com.ms.fx.") ) {
					prefix.setName("Fx");
					prefix.setForeground(BaseColor.getColor(new FxColor(212,127,0)));
				}
				else if ( len >= 11 ) {
					str = pkg.substring(0,11);
					if ( str.equalsIgnoreCase("com.ms.awt.") ) {
						prefix.setName("awt");
						prefix.setForeground(BaseColor.getColor(new FxColor(51,153,0)));
					}
					else if ( len >= 12 ) {
						str = pkg.substring(0,12);
						if ( str.equalsIgnoreCase("com.ms.util.") ) {
							prefix.setName("Util");
							prefix.setForeground(BaseColor.getColor(new FxColor(51,153,0)));
						}
					}
				}
			}
		}
	}

	public String getFullName() { return(pkg + super.getName()); }
}

