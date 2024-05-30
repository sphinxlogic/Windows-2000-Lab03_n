// SampleLoader.java
//
// Created 09/10/97
//
// (C)Copyright 1997 Microsoft Corporation, All rights reserved.
//

import com.ms.security.*;
import com.ms.security.permissions.*;
import java.io.*;
import java.util.*;


public class SampleLoader extends SecurityClassLoader
{
    String dir;

    PermissionSet perms;


    public SampleLoader (String dir, String permfilename) throws IOException
    {
        if (!dir.endsWith(File.separator))
            dir = dir.concat(File.separator);
        this.dir = dir;

        if (permfilename == null)
        {
            // Populate the defaults with what is normally accessible to applets, plus
            // the ability to read files from the current directory.
            PermissionDataSet pds = com.ms.security.management.ZonePermissions.createDefaultPermissionSet();
            FileIOPermission fileperm = (FileIOPermission)pds.find(PermissionID.FILEIO);
            if (fileperm == null)
                fileperm = new FileIOPermission();
            fileperm.addReadableFiles(System.getProperty("user.dir")+File.separator+"*", true);
            perms = pds.toPermissionSet();
        }
        else
        {
            perms = decodePermissionsFromFile(permfilename);
        }
    }

    private static PermissionSet decodePermissionsFromFile (String filename) throws IOException
    {
        PermissionDataSet pds = new PermissionDataSet();
        String fmt;
        if (filename.toLowerCase().endsWith(".ini"))
            fmt = EncodeFormats.INI;
        else
            fmt = EncodeFormats.ASN1;
        String tag = pds.mapFormat(fmt);
        if (tag == null)
            throw new Error("PermissionDataSet does not support format \""+fmt+"\"");
        if (!pds.decode(tag, new FileInputStream(filename)))
            throw new Error("failed to decode permissions from "+filename);
        return pds.toPermissionSet();
    }


    // ClassLoader methods

    protected Class loadClass (String name, boolean resolve) throws ClassNotFoundException
    {
        Class c = findLoadedClass(name);
        if (c == null)
        {
            try
            {
                c = findSystemClass(name);
            }
            catch (ClassNotFoundException e)
            {
                String filename = dir + name.replace('.', File.separatorChar) + ".class";
                File f = new File(filename);
                try
                {
                    long len = f.length();
                    byte[] data = new byte[(int)len];
                    InputStream is = new FileInputStream(f);
                    is.read(data);
                    is.close();

                    c = defineClass(name, data, 0, data.length, perms, new URLPrincipal(new java.net.URL("file:"+dir)));
                }
                catch (IOException ioe)
                {
                    throw new ClassNotFoundException(name+": "+ioe.toString());
                }
            }
        }

        if (resolve)
            resolveClass(c);

        return c;
    }
}

