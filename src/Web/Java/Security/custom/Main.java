// Main.java
//
// Created 09/12/97
//
// (C)Copyright 1997 Microsoft Corporation, All rights reserved.
//

import com.ms.samples.security.custom.*;
import java.applet.*;
import com.ms.security.*;
import java.awt.*;


public class Main extends Applet
{
    TextArea text;

    public void start ()
    {
        setLayout(new BorderLayout());
        
        text = new TextArea();
        add("Center", text);

        msg("Accessing items from 'start':\n");
        // This will fail unless the page is in a low-security zone.
        go();

        msg("\nAccessing items from 'start' with SamplePermission asserted:\n");
        PolicyEngine.assertPermission(SamplePermission.id);
        go();
    }

    void msg (String s)
    {
        System.out.print(s);
        System.out.flush();
        text.appendText(s);
    }

    void tryitem (String item)
    {
        msg("trying item \""+item+"\": ");
        try
        {
            SampleLib.accessItem(item);
            msg("accessed\n");
        }
        catch (Throwable e)
        {
            msg(e+"\n");
        }
    }

    void go ()
    {
        tryitem("foo");
        tryitem("bar");
    }

    public static void main (String[] args)
    {
        (new Main()).go();
    }
}

