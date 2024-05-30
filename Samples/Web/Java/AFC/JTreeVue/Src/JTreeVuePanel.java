//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.Event;
import java.io.InputStream;
import java.io.StreamTokenizer;
import java.io.BufferedReader;
import java.io.Reader;
import java.io.InputStreamReader;
import java.net.URL;
import java.net.MalformedURLException;
import java.util.Vector;
import java.util.Enumeration;
import java.util.Hashtable;

import com.ms.ui.*;
import com.ms.fx.*;

public class JTreeVuePanel extends UIPanel implements JTreeConsts, JTCallbacks
{
	public UITree objroot = null;		// "Object" class subtree of jtree
	private Hashtable htable;
	private UITree jtree = null;	// root to the whole shabang
	private UIStatus status;
	private UITree ifacelst = null;		// interface sublist(tree) of jtree 
	private FxColor ifacecolor, classcolor;

	public JTreeVuePanel(InputStream stream)
	{
		UITree curtree = null;		// current position in subtree
		int depth = 0;

		setLayout(new UIBorderLayout());
		setBackground(FxColor.lightGray);
		setFont(new FxFont("Helvetica", FxFont.PLAIN, 12));

		htable = new Hashtable(10000, (float).1);

		ifacecolor = new FxColor(225, 225, 225);
		classcolor = new FxColor(180, 180, 200);

		jtree = new UITree(new JTreeNode("Class Hierarchy"), 17);
		add(new UIScrollViewer(jtree), "Center");
		curtree = jtree;

		ifacelst = new UITree(new JTreeNode("Interfaces"), 17);
		status = new UIStatus();
		add(status, "South");

		try {
			// 1.1 Method
			Reader rdr = new BufferedReader(new InputStreamReader(stream));
			StreamTokenizer tokstrm = new StreamTokenizer(rdr);

			// 1.0.2 Method
			//BufferedInputStream buffer = new BufferedInputStream(stream);
			//StreamTokenizer tokstrm = new StreamTokenizer(buffer);
			
			tokstrm.ordinaryChars('0', '9'); tokstrm.wordChars('0', '9');
			tokstrm.ordinaryChar('/'); tokstrm.wordChars('/', '/');
			tokstrm.ordinaryChar('.'); tokstrm.wordChars('.', '.');
			tokstrm.ordinaryChar('-'); tokstrm.wordChars('-', '-');
			tokstrm.ordinaryChar('+'); tokstrm.wordChars('+', '+');
			tokstrm.eolIsSignificant(true);
			boolean more = true;
			boolean startLine = true;

			while (more) {
				switch(tokstrm.nextToken()) {
					case StreamTokenizer.TT_EOF: 
						more = false; 
						break;

					case StreamTokenizer.TT_NUMBER:
					case StreamTokenizer.TT_WORD:
					case StreamTokenizer.TT_EOL: 
						break;

					case '<':
						if ( (startLine == true) &&
							 (tokstrm.nextToken() == StreamTokenizer.TT_WORD) ) {
							if ( tokstrm.sval.equalsIgnoreCase("ul") ) {
								// first <ul>! Don't do anything, wait for first li
								if ( depth != 0 ) {
									int i = curtree.getComponentCount() - 1;
									IUIComponent comp = curtree.getComponent(i);
									curtree.remove(comp);

									UITree newtree = new UITree(comp, 17);
									curtree.add(newtree);
									if ( objroot == null ) {
										objroot = newtree;
										// Add Interfaces as a sibling branch
										//  to Object, we need to add it here 
										//  so it will be after Object on tree.
										curtree.add(ifacelst);
									}
									curtree = newtree;
								}
								depth++;
							}
							else if ( tokstrm.sval.equalsIgnoreCase("li") ) {
								// skip over '>'
								tokstrm.nextToken();
								// this will create new node
								newNode(tokstrm, curtree); 
							}
							else if ( tokstrm.sval.equalsIgnoreCase("/ul") ) {
								depth--;
								if ( depth == 0)
									more = false;
								else
									curtree = (UITree)curtree.getParent();
							}
						}
						break;

					default: 
						break;
				} // end switch
				startLine = (tokstrm.ttype == StreamTokenizer.TT_EOL);
			} // end while
		} catch (Exception e) {}

		jtree.setExpanded(true);
		objroot.setExpanded(true);
		dispatchInfo((JTreeNode)objroot.getHeader());
	}

	public void newNode(StreamTokenizer tokstrm, UITree curtree)
	{
		JTreeNode newnode = null;

		try {
			// Create node...
			newnode = new JTreeNode(tokstrm, this);
			// ... and add it to hash table using the name as key
			htable.put(newnode.info.name, newnode);

			if ( newnode.info.type == HTI_CLS ) {
				newnode.setBackground(classcolor);
				curtree.add(newnode);
			}
			else {
				newnode.setBackground(ifacecolor);
				ifacelst.add(newnode);
			}

			if ( (newnode.info.type == HTI_CLS) || (newnode.info.type == HTI_IFACE) ) {
				if ( tokstrm.nextToken() == '(' ) {
					JTreeNodeInfo extimpl = new JTreeNodeInfo(tokstrm);
					newnode.addExtImpl(extimpl);

					while ( tokstrm.nextToken() == ',' ) {
						tokstrm.pushBack();
						extimpl = new JTreeNodeInfo(tokstrm);
						newnode.addExtImpl(extimpl);
					}
					// Don't need to pushBack closing brace ')'
				}
				else // it must have been EOL push it back into stream
					tokstrm.pushBack();
			}
		} catch (Exception e) {}
	}

	public boolean handleEvent(Event e)
	{
		JTreeNode node;

		if (e.id == Event.WINDOW_DESTROY)
			// handle the app exit event
			System.exit(0);
		else if (e.id == Event.LIST_SELECT)
			dispatchInfo(getNode(e.arg));

		return(super.handleEvent(e));
	}

	public Hashtable getHTable() { return htable; }

	public void dispatchInfo(JTreeNode node)
	{
		if ( node == null )
			return;

		String clsname = node.getFullName();

		status.setName(clsname);

		// if node is not visible it must be in ifacelst tree
		if ( !node.isVisible() ) 
			ifacelst.setExpanded(true);

		jtree.setSelectedItem(node);
		node.requestFocus();
	}

	//
	// Override requestFocus to throw focus back to tree if user switches to another
	//  app and then returns to this one. This will also restore focus to node when 
	//  user cancels an Implements.../Extends... menu popup.
	//
	public void requestFocus()
	{
		JTreeNode node = getNode(jtree.getSelectedItem());
		if ( node != null )
			node.requestFocus();
		else
			super.requestFocus();
	}

	private JTreeNode getNode(Object obj)
	{
		if (obj instanceof JTreeNode)
			return (JTreeNode)obj;
		else if (obj instanceof UITree) {
			IUIComponent comp = ((UITree)obj).getHeader();
			if ( comp instanceof JTreeNode )
				return (JTreeNode)comp;
		}
		return null;
	}
}

interface JTCallbacks
{
	public Hashtable getHTable();
	public void dispatchInfo(JTreeNode node);
}
