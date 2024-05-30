// demo.java
//
// Created 09/09/97
//
// (C)Copyright 1997 Microsoft Corporation, All rights reserved.
//

package demo;

import java.applet.*;
import java.io.PrintStream;
import rnisamp.*;
import java.io.ByteArrayOutputStream;
import java.awt.TextArea;
import java.awt.BorderLayout;
import com.ms.security.PolicyEngine;
import com.ms.security.PermissionID;
import com.ms.security.SecurityExceptionEx;
import com.ms.com.ComFailException;


public class Main extends Applet implements Runnable
{
    static PrintStream out;
    static String untrustedcaller;
    

    public void init ()
    {
        TextArea ta = new TextArea();
        setLayout(new BorderLayout());
        add("Center", ta);
        out = new PrintStream(new TextAreaOutputStream(ta), true);
    }

    boolean isAppletFullyTrusted ()
    {
        try
        {
            PolicyEngine.checkCallerForAllPermissions(null);
            return true;
        }
        catch (SecurityException e)
        {
            return false;
        }
    }

    boolean isPageFullyTrusted ()
    {
        Class[] skip = { Main.class };
        try
        {
            PolicyEngine.checkCallerForAllPermissions(skip);
            return true;
        }
        catch (SecurityException e)
        {
            return false;
        }
    }

    public void start ()
    {
        boolean applettrusted = isAppletFullyTrusted();
        boolean pagetrusted = isPageFullyTrusted();

        out.print("Applet is ");
        if (!applettrusted)
            out.print("not ");
        out.println("fully trusted.");

        out.print("Page is ");
        if (!pagetrusted)
            out.print("not ");
        out.println("fully trusted.");
        
        out.println();

        if (!applettrusted)
            untrustedcaller = "applet is not trusted";
        else if (!pagetrusted)
            untrustedcaller = "docbase is not trusted";
            
        // start is 'called' from the HTML page containing the applet,
        // so there is an extra frame above start with the privileges
        // of the zone of the containing page.  This may cause the
        // applet to fail even if it has file permissions.
        out.println("-----------------------------------------------------");
        out.println("Performing checks from 'start':");
        out.println();
        run();

        // The HTML page frame is not at the top of the threads created
        // by the applet, so if the applet has file permissions, the
        // access will succeed regardless of the permissions of the
        // containing page.
        out.println();
        out.println("-----------------------------------------------------");
        out.println("Performing checks from a new thread:");
        out.println();
        if (applettrusted)
            untrustedcaller = null;
        else
            untrustedcaller = "applet is not trusted";
        (new Thread(this)).start();
    }

    public void run ()
    {
        go(untrustedcaller);
    }

    static void dumpData (byte[] data, int len)
    {
        if (len > 50)
            len = 50;
        StringBuffer line = new StringBuffer();
        for (int i = 0; i < len; i++)
        {
            char ch = (char)(data[i] & 0xff);
            if (ch == '\r' || ch == '\n')
                break;
            if (ch < 32 || ch > 127)
                ch = '.';
            line.append(ch);
        }
        out.println(line);
    }

    public static void main (String[] args)
    {
        out = System.out;

        go(null);
    }

    static void go (String untrustedcaller)
    {
        tryfile("c:\\autoexec.bat", untrustedcaller);
        tryfile("rnisamp.dll",      untrustedcaller);
    }

    static void tryfile (String filename, String untrustedcaller)
    {
        MyRNIObject rniobj;
        try
        {
            rniobj = new MyRNIObject();
        }
        catch (Throwable e)
        {
            out.println("Could not instantiate RNI object MyRNIObject. Is rnisamp.dll on the path?");
            e.printStackTrace();
            return;
        }
        
        loadfile(rniobj, filename, false, untrustedcaller);
        loadfile(rniobj, filename, true,  untrustedcaller);
    }

    static void loadfile (MyRNIObject rniobj, String filename, boolean rnichecked, String untrustedcaller)
    {
        boolean isaccessible;
        SecurityManager sm = System.getSecurityManager();
        boolean havesm = sm != null;
        try
        {
            if (sm != null)
                sm.checkRead(filename);
            isaccessible = true;
        }
        catch (SecurityException e)
        {
            isaccessible = false;
        }
    
        try
        {
            out.println("Loading file \""+filename+"\".");
            if (havesm)
                out.println("Security check made by "
                        +(rnichecked ? "RNI" : "Java")+"CheckedLoad should "
                        +(isaccessible ? "" : "not ")+"succeed");
            else
                out.println("No security check should be made.");
            
            byte[] data;
            if (rnichecked)
                data = rniobj.RNICheckedLoad(filename);
            else
                data = rniobj.JavaCheckedLoad(filename);
                
            if (!isaccessible)
                out.println("Call should not have succeeded because "+untrustedcaller+"!");
            else
                out.print("Call succeeded.  ");
                
            out.print("First line:");
            dumpData(data, data.length);
        }
        catch (Throwable e)
        {
            if (e instanceof SecurityException)
            {
                if (!isaccessible)
                    out.println("Caught security exception as expected - "+untrustedcaller+".");
                else
                    out.println("Unexpected security exception!");
            }
            else
            {
                out.println("Load failed: "+e);
            }
            e.printStackTrace();
        }

        out.println();
    }
}


class TextAreaOutputStream extends ByteArrayOutputStream
{
    TextArea ta;


    TextAreaOutputStream (TextArea i_ta)
    {
        ta = i_ta;
    }


    public void flush ()
    {
        String s = toString();
        ta.appendText(s);
        System.out.print(s);
        reset();
    }
}

