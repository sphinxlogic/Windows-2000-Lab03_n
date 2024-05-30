// baseperms.java
//
// Created 09/12/97
//
// (C)Copyright 1997 Microsoft Corporation, All rights reserved.
//

import com.ms.security.*;
import com.ms.security.management.*;


public class baseperms
{
    public static void main (String[] args)
    {
        PermissionDataSet pds = ZonePermissions.createDefaultPermissionSet();
        String tag = pds.mapFormat(EncodeFormats.INI);
        if (tag == null)
        {
            System.err.println("Default applet permissions cannot be ini encoded. (?)");
            System.exit(1);
        }
        if (!pds.encode(tag, System.out))
        {
            System.err.println("Failed to encode applet permissions to ini form. (?)");
            System.exit(1);
        }
    }
}

