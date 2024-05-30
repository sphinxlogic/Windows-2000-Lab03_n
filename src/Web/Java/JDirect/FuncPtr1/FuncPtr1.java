/* Copyright (C) 1997 Microsoft Corporation. All rights reserved.
 *
 * This example demonstrates the use of the Callback class to
 * simulate function pointers in Java. To create a function pointer
 * in Java requires the following steps:
 *
 *   1. Write a class that derives from Callback.
 *   2. Implement a public method named "callback" (all lowercase).
 *      The method must be non-static, accept only integers as parameters
 *      and return an integer, boolean, character, short or void.
 *   3. Create an instance of your new class. Pass that in as the
 *      function pointer argument.
 *
 * This particular example uses two classes: EnumWindowsProc which derives
 * directly from Callback, and SampleEnumWindowsProc which derives
 * from EnumWindowsProc. The parent class (EnumWindowsProc) is abstract
 * and serves only to define the method prototype for "callback."
 * The child class (SampleEnumWindowsProc) provides the actual implementation.
 * Different calls to EnumWindows() are likely to use different
 * child classes; however, they all derive from EnumWindowsProc so they
 * can use the common declaration of EnumWindows (which is prototyped
 * to accept an EnumWindowsProc.)
 *
 */

public class FuncPtr1
{
    public static void main(String args[])
    {
        boolean fSuccess = EnumWindows(new SampleEnumWindowsProc(), 0);
        if (!fSuccess) {
            System.err.println("EnumWindows failed.");
        }
    }


    /** @dll.import("USER32") */
    static native boolean EnumWindows(EnumWindowsProc wndenmprc, int lparam);


}



//==========================================================================
// An abstract parent class that describes all EnumWindowsProc's but does
// not provide any implementation. 
//==========================================================================
abstract class EnumWindowsProc extends com.ms.dll.Callback
{
    // It is required that this method be named "callback".
    public abstract boolean callback(int hwnd, int lparam);
}


//==========================================================================
// A specific EnumWindowsProc which simply prints out the window handle
// and title bar text.
//==========================================================================
class SampleEnumWindowsProc extends EnumWindowsProc
{
    public boolean callback(int hwnd, int lparam)
    {
        StringBuffer text = new StringBuffer(50);
        GetWindowText(hwnd, text, text.capacity()+1);
        if (text.length() != 0) {
            System.out.println("hwnd = " +
                               Integer.toHexString(hwnd) +
                               "h: " +
                               text);
        }
        return true;  // return TRUE to continue enumeration.
    }

    /** @dll.import("USER32") */
    static native int GetWindowText(int hwnd, StringBuffer text, int cch);

}

