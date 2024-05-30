/* Copyright (C) 1997 Microsoft Corporation. All rights reserved.
 *
 * This example calls the MessageBox api using the new @dll.import
 * directive.
 *
 */

public class Simple
{
    public static void main(String args[])
    {
        try {

            MessageBox(0, "MessageBox successfully called.", "Java", 0);

        } catch (UnsatisfiedLinkError ule) {
            System.err.println("Caught exception: " + ule);
            System.err.println("Probably wrong version of Java compiler.");
        }
    }


    /** @dll.import("USER32") */
    static native int MessageBox(int    hwndOwner,
                                 String text,
                                 String title,
                                 int    style);
}
