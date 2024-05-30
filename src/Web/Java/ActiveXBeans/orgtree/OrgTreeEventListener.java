/**
 *  OrgTree.java
 *
 *      This component builds a tree control out of a list of employees
 *      and their titles and managers.
 *
 *  (C) Copyright 1997, Microsoft Corporation. All rights reserved.
 *
 */

import java.util.*;

public interface OrgTreeEventListener extends java.util.EventListener
{
    void employeeSelected( String empName, String empTitle, String empMgr, int i );
}

