/* Copyright (C) 1997 Microsoft Corporation. All rights reserved.
 *
 * This example shows how to use the Reflection api along with
 * DllLib to examine the physical layout of a class declared
 * with "@dll.struct".
 *
 */


import com.ms.dll.*;
import java.lang.reflect.*;

public class SDump
{
    public static void main(String args[])
    {
        Class c;
        if (args.length == 0) {
            System.err.println("Must give name of class as argument.");
            return;
        }

        String name = args[0];


        if (name.length() >= 6 &&
            name.substring(name.length()-6).equals(".class")) {
            name = name.substring(0, name.length()-6);
        }

        try {
            c = Class.forName(name);
        } catch (Exception e) {
            System.err.println("Could not load class named \"" +
                                name +
                                "\"");
            return;
        }

        if (!DllLib.isStruct(c)) {
            System.err.println("Class \"" +
                               c.getName() +
                               "\" not declared with @dll.struct.");
            return;
        }

        System.out.println("Layout of class \"" + c.getName() + "\"");

        Field fields[] = c.getDeclaredFields();
        for (int i = 0; i < fields.length; i++) {
            Field f = fields[i];
            if (DllLib.isStruct(f)) {
                int offset = DllLib.offsetOf(f);
                System.out.println("+" + offset + ": " + " " + f.getName());
            }
        }
        System.out.println();
        System.out.println("  Total size = " + DllLib.sizeOf(c) + " bytes.");
    }
}



/** @dll.struct() */
class SampleStruct
{
    int     a;
    int     b;
    int     c;
    int     d;

}

