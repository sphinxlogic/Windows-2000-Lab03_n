/* Copyright (C) 1997 Microsoft Corporation. All rights reserved.
 *
 * This example shows how to use the "auto" keyword for calling Win32 system
 * apis. The "auto" keyword instructs the VM to use the GetVersion()
 * api to determine whether the Ansi MessageBox (MessageBoxA) or the
 * Unicode MessageBox (MessageBoxW) is to be called.
 *
 * If the running platform is Windows 95, the ansi api is called.
 * If the running platform is Windows NT, the unicode api is called.
 *
 * This algorithm can also be overridden by setting the registry key
 *  
 *    HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Java VM\DllImportDefaultType
 *
 * to one of the following DWORD values:
 *
 *    2:        select Ansi
 *    3:        select Unicode
 *    4:        perform the check as described above
 *
 * This key is normally set only by the installation program.
 *
 * In addition, this sample shows how to learn programmatically whether
 * the "auto" mode will choose Ansi or Unicode. All it does is query
 * the com.ms.dll.DllLib.systemDefaultCharSize field.
 */



import com.ms.dll.*;

public class AutoMode
{
    public static void main(String args[])
    {
        int charsize = DllLib.systemDefaultCharSize;
        String message;
        switch (charsize) {
            case 1:
                message = "The \"auto\" keyword will select ANSI.";
                break;
            case 2:
                message = "The \"auto\" keyword will select UNICODE.";
                break;

            default:
                System.err.println("DllLib.systemDefaultCharSize set to illegal value (" + charsize + ")");
                return;
        }

        try {

            MessageBox(0, message, "ShowAutoMode", 0);

        } catch (UnsatisfiedLinkError ule) {
            System.err.println("Caught exception: " + ule);
            System.err.println("Probably wrong version of Java compiler.");
        }
    }

    /** @dll.import("USER32", auto) */
    static native int
    MessageBox(int hwndOwner, String text, String title, int style);


}


