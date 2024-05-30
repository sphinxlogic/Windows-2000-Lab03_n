/**
 *
 *  OrgTreeNode.java
 *
 *      This object represents one individual in the org tree.
 *
 *  (C) Copyright 1997 by Microsoft Corporation. All rights reserved.
 * 
 */
import java.awt.*;                      // standard java
import java.applet.*;
import com.ms.ui.*;                     // microsoft afc

public class OrgTreeNode extends UITree
{
    transient private static Image   empImage = null;
    transient private static Image   mgrImage = null;

    transient private String name;
    transient private String manager;
    transient private String title;
    transient private int    row;

    public static void oneTimeInit( Applet host)
    {
		MediaTracker mt = new MediaTracker(host);			// track the images being loaded

        empImage = host.getImage(host.getCodeBase(), "employee.gif");
		mt.addImage(empImage, 0);

        mgrImage = host.getImage(host.getCodeBase(), "manager.gif");
		mt.addImage(mgrImage, 0);

		// wait for all the images to be loaded
        try 
		{
			mt.waitForAll();
		} 
		catch (InterruptedException e) 
		{
			e.printStackTrace();
		}

	}

    public OrgTreeNode(String empName, String empTitle, String empManager, int dbRow)
    {
        super( empImage, empName+" - "+empTitle );

        setSelectionMode(UITree.SINGLESELECT);

        name        = empName;
        title       = empTitle;
        manager     = empManager;
        row         = dbRow;
    }

    /**
     *  Returns the name of this employee
     */
    public String getName()
    {
        return (name);
    }

    /**
     *  Returns the title of this employee
     */
    public String getTitle()
    {
        return (title);
    }

    /**
     *  Return the row of this employee
     */
    public int getRow()
    {
        return (row);
    }

    /**
     *  Returns the OrgTreeNode which is the manager
     */
    public OrgTreeNode getManagerNode()
    {
        if (getParent() instanceof OrgTreeNode)
        {
            return (OrgTreeNode)getParent();
        } else
        {
            return null;
        }
    }

    /**
     *  Returns the name of the employee's manager
     */
    public String getManagerName()
    {
        return manager;
    }

	/**
	 * This sets the current tree node to be a manager tree node. i.e. it
	 * changes his image
	 *
	 * @param	boolean	is this guy a manager or not
	 */
	public void setManager(boolean isManager)
	{
		if( isManager)
		{
            ((UIItem)getHeader()).setImage(mgrImage);
		}
		else
		{
            ((UIItem)getHeader()).setImage(empImage);
		}
	}

    /**
     *  If this OrgTreeNode represents the specified node's manager,
     *  this adds it to this OrgTreeNode, and returns true.
     *  Otherwise, it returns false.
     */
    public boolean addTeamMember( OrgTreeNode otn )
    {
        int i,c;
        boolean found = false;

        // if our name matches the manager of this node,
        // add it to us
        if (otn.getManagerName().equalsIgnoreCase( getName() ))
        {
            // add to us
            add( otn );
            
			// we're now a manager
			setManager(true);

            found = true;
        } else
        {
            UIComponent cmp;

            // look for our team in the subordinates and add us to it if found
            c = getComponentCount();

            // loop through all our components and put us in the proper team
            for ( i = 0; i < c; i++ )
            {
                cmp = (UIComponent) getComponent(i);

                // if we find our team, we're done
                if ( (cmp instanceof OrgTreeNode) &&
                     ((OrgTreeNode)(getComponent(i))).addTeamMember( otn ) )
                {
                    found = true;
                    break;
                }
            }
        }
        return found;
    }
}
