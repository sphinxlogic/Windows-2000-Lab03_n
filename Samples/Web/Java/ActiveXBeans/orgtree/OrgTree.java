/**
 *  OrgTree.java
 *
 *      This component builds a tree control out of a list of employees
 *      and their titles and managers.
 *
 *  (C) Copyright 1997, Microsoft Corporation. All rights reserved.
 *
 */

import java.awt.*;                  // standard java
import java.applet.*;               // standard java
import java.util.*;                 // standard java
import com.ms.ui.*;                 // microsoft afc
import com.ms.ui.event.*;
import java.io.*;

public class OrgTree extends AwtUIApplet
{
    OrgTreeImpl inner;

    public OrgTree()
    {
	super(new OrgTreeImpl());   
        
        inner = (OrgTreeImpl) getUIApplet();
    }

    public void addOrgTreeEventListener(OrgTreeEventListener l)
    {
        inner.addOrgTreeEventListener(l);     
    }

    public void removeOrgTreeEventListener(OrgTreeEventListener l)
    {
        inner.removeOrgTreeEventListener(l);     
    }

    public OrgTreeNode addEmployee( String empName,
                                    String empTitle,
                                    String empManager,
                                    int dbRow)
    {
        return inner.addEmployee(empName, empTitle, empManager, dbRow);
    }
}

class OrgTreeImpl extends UIApplet implements IUIItemListener, Serializable
{

    // base of the org chart
    private UITree root;

    // listeners for node clicks
    transient Vector listeners = new Vector();

	public void init()
	{
        // initialize our node class
        OrgTreeNode.oneTimeInit( getApplet() );

        root = new UITree("Organization");
        root.setExpanded(true);

        setLayout(new UIBorderLayout());
        setFont(new Font("Helvetica", 0, 12));
		setSize(400,200);
		root.addItemListener(this);
		add(new UIScrollViewer(root), "center" );
	}

    // done once on applet init
    public OrgTreeImpl()
    {
    }


    public void itemStateChanged(UIItemEvent evt)
    {
        if ((evt.getStateChange() == UIItemEvent.SELECTED) && (evt.getItem() instanceof OrgTreeNode) )
        {
            System.out.println("Tree node selected" );
            OrgTreeNode emp = (OrgTreeNode)evt.getItem();
            String empName  = emp.getName();
            String empTitle = emp.getTitle();
            String empMgr   = (emp.getManagerNode() == null) ? null : emp.getManagerNode().getName();
            int r           = emp.getRow();

            // get a picture of the listeners in an array
            OrgTreeEventListener otl[];
            synchronized(listeners)
            {
                otl = new OrgTreeEventListener[listeners.size()];
                listeners.copyInto(otl);
            }

            for (int i=0; i<otl.length; i++)
            {
                System.out.println( "Sending employee "+empName );

                // notify that an employee was selected
                otl[i].employeeSelected(empName, empTitle, empMgr, r);
            }
        }
        
    }

    /**
     *  Adds a listener for org tree selection events
     */
    public void addOrgTreeEventListener(OrgTreeEventListener l)
    {
        System.out.println("Adding an event listener");
        listeners.addElement(l);    
    }

    /**
     *  Removes a listener for org tree selection events
     */
    public void removeOrgTreeEventListener(OrgTreeEventListener l)
    {
        listeners.removeElement(l);
    }

    /** 
     *  Adds an employee to the org tree
     *  it first finds the employee's manager in the existing tree and then
     *  adds the employee to the tree in the appropriate place.
     */ 
    public OrgTreeNode addEmployee( String empName,
                                    String empTitle,
                                    String empManager,
                                    int dbRow)
    {
        // if the employee has a manager,
        // look for them in the existing tree, also look for any
        // employees in the existing tree with this employee as their
        // manager

        System.out.println("Adding "+empName );

        // this will hold the parent (root or manager)
        int         i;
        int         c;
        UIComponent   cmp;

        // create a node
        OrgTreeNode emp = new OrgTreeNode(empName,empTitle,empManager,dbRow);

        // look for any employees which work for this employee &
        // remove them from the root and add them to this one
        // the only possible candidates are nodes on the root which have
        // a manager. We don't synchronize this, but we should. 
        c = root.getComponentCount();

        // loop through all root components and put this mgr's team members in the node
        for ( i = 0; i < c; i++ )
        {
            String mn;

            cmp = (UIComponent) root.getComponent(i);

            // if we are this employee's manager, add them to our tree
            if ((cmp instanceof OrgTreeNode) &&
                (mn = ((OrgTreeNode)cmp).getManagerName()) != null &&
                mn.equalsIgnoreCase( empName ))
            {
                // remove this one, reduce our count and our total
                root.remove( i );
                i--;
                c--;
                // add this component to our tree
                emp.add( cmp );
				emp.setManager(true);
            }
        }

        // look for our team and add us to it
        c = root.getComponentCount();

        // loop through all root components and put us in the proper team
        for ( i = 0; i < c; i++ )
        {
            cmp = (UIComponent) root.getComponent(i);

            // if we find our team, we're done
            if ((cmp instanceof OrgTreeNode) &&
                ((OrgTreeNode)(cmp)).addTeamMember( emp ) )
            {
                break;
            }
        }

        // if we didn't find a team, we're a root
        if ( i == c )
        {
            root.add( emp );
        }

        setValid(true);
        return (emp);
    }
}
