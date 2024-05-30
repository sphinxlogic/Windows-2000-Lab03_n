// SamplePermission.java
//
// Created 09/10/97
//
// (C)Copyright 1997 Microsoft Corporation, All rights reserved.
//

package com.ms.samples.security.custom;

import com.ms.security.*;
import java.io.*;
import com.ms.util.ini.*;


/**
 * Determines access to a list of items identified by strings.
 */
public class SamplePermission implements IPermission,
                                         IEncodablePermission
{
    String[] items;
    
    public SamplePermission()
    {
    }


    // Defines the PermissionID for this permission object.

    public static final PermissionID id = PolicyEngine.permissionNameToID(SamplePermission.class.getName());


    // Methods to manipulate and inspect the permission

    /**
     * Adds an allowed item to the permission.
     */
    public void addItem (String newitem)
    {
        if (items == null)
        {
            items = new String[1];
        }
        else
        {
            String[] newitems = new String[items.length+1];
            System.arraycopy(items, 0, newitems, 0, items.length);
            items = newitems;
        }
        items[items.length-1] = newitem;
    }

    /**
     * Removes an item that may (or not) already be allowed by the permission.
     * @return true if the item existed before all occurrences were removed
     */
    public boolean removeItem (String remitem)
    {
        int nremoved = 0;
        for (int i = 0; i < items.length; i++)
        {
            if (items[i] == remitem)
            {
                items[i] = null;
                nremoved++;
            }
        }
        
        if (nremoved == 0)
            return false;

        if (items.length == nremoved)
        {
            items = null;
            return true;
        }
        
        String[] newitems = new String[items.length-nremoved];
        int ni = 0;
        for (int i = 0; i < items.length; i++)
        {
            if (items[i] != null)
                newitems[ni++] = items[i];
        }
        items = newitems;

        return true;
    }

    /**
     * Obtains the items that are permitted.  The list should <em>not</em> be
     * modified.
     * @return the permitted items, or null if there are none.
     */
    public String[] getAllowedItems ()
    {
        // Permissions of classes are only accessible to fully trusted
        // classes, so returning a reference to internal structures of
        // the permission is acceptable.
        return items;
    }


    // IEncodablePermission methods

    private void encodeText (PrintWriter w)
    {
        if (items == null)
        {
            w.println("empty");
        }
        else
        {
            w.println(items.length+" items:");
            for (int i = 0; i < items.length; i++)
            {
                w.println(items[i]);
            }
        }
    }

    static final String TAG_TEXT1 = "String Version 1";
    static final String TAG_INI1 = "INI Version 1";

    public boolean encode (String tag, OutputStream data)
    {
        try
        {
            DataOutputStream out = new DataOutputStream(data);

            // The format of the expected output is very rigid:
            // DISPLAY, DISPLAYNAME: unicode characters
            // TEXT: U2-length-prefixed utf8 string
            // INI: an IniSection written to a PrintStream wrapping 'data'

            if (TAG_INI1.equals(tag))
            {
                IniSection section = new IniSection();
                section.setName(this.getClass().getName());

                if (items != null && items.length > 0)
                {
                    StringBuffer sb = new StringBuffer();
                    int i = 0;
                    while (true)
                    {
                        sb.append(items[i]);
                        i++;
                        if (i >= items.length)
                            break;
                        sb.append(';');
                    }
                    section.addNamePair("Items", sb.toString());
                }

                PrintStream ps = new PrintStream(data);
                section.writeContents(ps);

                return !ps.checkError();
            }
            
            if (EncodeFormats.DISPLAYNAME.equals(tag))
            {
                out.writeChars("Sample Permission");
                return true;
            }

            StringWriter sw = new StringWriter();
            PrintWriter w = new PrintWriter(sw);
            boolean needutf = false;
            
            if (TAG_TEXT1.equals(tag))
            {
                needutf = true;
            }
            else if (EncodeFormats.DISPLAY.equals(tag))
            {
                w.println("Sample Permission:");
            }
            else
            {
                return false;
            }
            
            encodeText(w);
            
            w.flush();
            if (w.checkError())
                return false;

            String s = sw.toString();
            
            if (needutf)
                out.writeUTF(s);
            else
                out.writeChars(s);
            return true;
        }
        catch (IOException e)
        {
            return false;
        }
    }

    public boolean decode (String tag, InputStream data)
    {
        // See encode for the format of the input data

        if (TAG_TEXT1.equals(tag))
        {
            try
            {
                BufferedReader r = new BufferedReader(new StringReader((new DataInputStream(data)).readUTF()));
                String line = r.readLine();
                
                if (line.equals("empty"))
                {
                    items = null;
                    return true;
                }
                
                int sep = line.indexOf(' ');
                if (sep == -1)
                    return false;
                    
                int nitems = Integer.parseInt(line.substring(0, sep));
                
                String[] newitems = new String[nitems];
                for (int i = 0; i < newitems.length; i++)
                    newitems[i] = r.readLine();
                    
                items = newitems;
                return true;
            }
            catch (IOException e)
            {
            }
        }
        else if (TAG_INI1.equals(tag))
        {
            IniFile ini;
            try
            {
                ini = new IniFile(data);
            }
            catch (Exception e)
            {
                return false;
            }

            IniSection section = ini.getSection(this.getClass().getName());
            if (section != null)
            {
                String val = section.getValue("Items");
                items = PermissionUtils.parseStringIntoArray(val, ";");
                return true;
            }
        }
        
        return false;
    }
        
    public String mapFormat (String format)
    {
        if (format == null)
        {
            // The default format.  All permissions that wish to be encodable
            // into signatures should support this format.
            return TAG_TEXT1;
        }
        
        if (EncodeFormats.TEXT.equals(format))
            return TAG_TEXT1;
            
        if (EncodeFormats.INI.equals(format))
            return TAG_INI1;

        // The tag is an opaque value used internally by the permission.  These
        // formats are supported in encodings only, so version information in
        // the tag is not important.
        if (EncodeFormats.DISPLAYNAME.equals(format) || EncodeFormats.DISPLAY.equals(format))
            return format;
            
        return null;
    }

    public String[] supportedFormats()
    {
        String[] list = new String[4];
        list[0] = EncodeFormats.TEXT;
        list[1] = EncodeFormats.INI;
        list[2] = EncodeFormats.DISPLAY;
        list[3] = EncodeFormats.DISPLAYNAME;
        return list;
    }


    // IPermission methods

    public void check (Object request) throws SecurityException
    {
        // Validate the request object.
        if(!(request instanceof SampleRequest))
            throw new IllegalArgumentException();

        // Check that the request is allowed.  If it is allowed,
        // simply return.
        if (items != null)
        {
            String strrequest = ((SampleRequest)request).item;
            for (int i = 0; i < items.length; i++)
            {
                if (strrequest.equals(items[i]))
                    return;
            }
        }

        // Throwing SecurityExceptionEx will supply the caller of
        // checkPermission with the class/method that failed the check.
        // Anything derived from SecurityException indicates a failure.
        throw new SecurityExceptionEx("Insufficient priviledge to access " + request);
    }

    public IPermission copy ()
    {
        SamplePermission copy = new SamplePermission();

        if (this.items != null)
            copy.items = (String[])items.clone();
            
        return copy;
    }

    public IPermission combine (IPermission other)
    {
        if(!(other instanceof SamplePermission))
            throw new IllegalArgumentException();

        SamplePermission comb = new SamplePermission();

        comb.items = PermissionUtils.combineArraysOfStrings(this.items, ((SamplePermission)other).items);
        
        return comb;
    }

    public int compareSet (Object other)
    {
        if(!(other instanceof SamplePermission))
            throw new IllegalArgumentException();

        SamplePermission target = (SamplePermission)other;

        int cmp = EMPTY;

        cmp = PermissionUtils.compareArraysOfStrings(this.items, target.items, cmp);

        // Comparisons of additional aspects of the permission may be
        // chained together in a similar fashion.  Note that the initial
        // result is EMPTY, which conceptually means that up until the first
        // item of the permission, they are simply considered empty.
        // For example, to compare two extra booleans:
        //
        // cmp = PermissionUtils.compareBooleans(this.canDoSomething, target.canDoSomething, cmp);

        // For items of types that do not have predefined comparators in
        // PermissionUtils, you will need to implement your own comparator
        // that produces a SetComparison result.  The result is combined
        // with the results of the comparisons of the other aspects using
        // PermissionUtils.mergeComparisonResults, ex.:
        //
        // int complexcmp = compareComplexItems(this.complexitem, target.complexitem);
        // cmp = PermissionUtils.mergeComparisonResults(complexcmp, cmp);

        return cmp;
    }


    public String toString ()
    {
        return "SamplePermission: items="+PermissionUtils.ArraytoString(items);
    }
}

