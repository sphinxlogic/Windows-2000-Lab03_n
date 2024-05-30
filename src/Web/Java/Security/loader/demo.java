// demo.java
//
// Created 09/10/97
//
// (C)Copyright 1997 Microsoft Corporation, All rights reserved.
//

import com.ms.security.*;
import com.ms.security.permissions.*;
import java.io.*;
import java.lang.reflect.*;


public class demo
{
    public static void main (String[] args)
    {
        if (args.length < 2)
        {
            System.err.println("usage: demo <permissions file> <class> <arguments ...>");
            return;
        }

        try
        {
            System.setErr(new PrintStream(new FileOutputStream("errors.txt"), true));
    
            SampleLoader loader = new SampleLoader("loaded", args[0]);

            Class c = loader.loadClass(args[1], true);

            System.out.print(c);
            PermissionDataSet pds = PolicyEngine.getPermissionsOfClass(c);
            if (pds.isFullyTrusted())
            {
                System.out.println(" is fully trusted");
            }
            else
            {
                FileIOPermission fileperm = (FileIOPermission)pds.find(PermissionID.FILEIO);
                if (fileperm == null)
                {
                    System.out.println(" cannot perform file i/o");
                }
                else
                {
                    System.out.println(" can read these files: "+fileperm.getReadableFiles(true));
                }
            }

            Method m = c.getMethodFromSignature("main", "([Ljava/lang/String;)V");
            String[] newargs = new String[args.length-2];
            System.arraycopy(args, 2, newargs, 0, newargs.length);
            Object[] invokeargs = new Object[1];
            invokeargs[0] = newargs;

            StandardSecurityManager.installStandardSecurity();

            m.invoke(null, invokeargs);
        }
        catch (Throwable e)
        {
            System.err.println("Unexpected error:");
            e.printStackTrace();
        }

        System.out.println("Errors have been redirected to 'errors.txt'.");
    }
}

