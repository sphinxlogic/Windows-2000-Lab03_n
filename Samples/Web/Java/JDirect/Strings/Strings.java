import com.ms.dll.DllLib;


/* Copyright (C) 1997 Microsoft Corporation. All rights reserved.
 *
 * This example shows how to pass strings using the String class and
 * receive strings using the StringBuffer class. It also demonstrates
 * the use of the DllLib.ptrToStringAnsi method. This method is used
 * to extract strings out of a series of catenated strings.
 */
public class Strings
{

    public static void main(String args[])
    {
        // Print out some common environment variables.
        System.out.println("PATH = " + getEnvironmentVariable("PATH"));
        System.out.println("TMP  = " + getEnvironmentVariable("TMP"));
        System.out.println("TEMP = " + getEnvironmentVariable("TEMP"));


        // Now, list all defined environment variables.
        System.out.println();
        System.out.println("Printing out all environment strings:");
        System.out.println("-------------------------------------\n");
        String env[] = getEnvironmentStrings();
        for (int i = 0; i < env.length; i++) {
            System.out.println(env[i]);
        }
    }





    //-------------------------------------------------------------
    // This method returns the value of the named environment variable,
    // or null if the environment variable is not defined. Note how
    // this method always sets the StringBuffer "value"'s capacity
    // prior to passing it to GetEnvironmentVariable. This step is crucial
    // because it ensures that enough buffer space is allocated to
    // accommodate the largest possible output.
    //-------------------------------------------------------------
    static String getEnvironmentVariable(String name)
    {
        final int MAXLENGTH=80;

        StringBuffer value;    
        int          numchars;

        value    = new StringBuffer(MAXLENGTH);
        numchars = GetEnvironmentVariable(name, value, MAXLENGTH+1);
        if (numchars == 0) {
            return null;   // Environment variable not defined.
        }
        if (numchars > MAXLENGTH+1) {
            // If we got here, our initial buffer was too small. Expand it
            // and try again.
            value.ensureCapacity(numchars-1);
            GetEnvironmentVariable(name, value, numchars);
        }
        return value.toString();
    }


    //-------------------------------------------------------------
    // This declaration gives us direct access to the GetEnvironmentVariable
    // api. Note that the "name" parameter is declared as a String, but
    // that "value" is declared as a StringBuffer. This is because "name"
    // is used for input while "value" is used for output.
    // 
    //-------------------------------------------------------------
    /** @dll.import("KERNEL32") */
    static native int GetEnvironmentVariable(String       name,
                                             StringBuffer value,
                                             int          valueSize);





    //-------------------------------------------------------------
    // This method returns the entire environment, as an array of
    // strings where each string has the form "name=value".
    //
    //
    //-------------------------------------------------------------
    static String[] getEnvironmentStrings()
    {
        int env = GetEnvironmentStrings();
        try {

            int walk  = env;
            int count = 0;
            int len;
            String s;

            // GetEnvironmentStrings returns a single memory block which
            // holds all the environment strings concatenated together: i.e.
            //
            //  A=1\0B=2\0C=3\0\0
            //
            // The block is terminated by an empty string.
            //
            // To turn this into a String array, we walk through
            // the memory block and extract one string at a time.

            // First, make one pass to count the number of environment
            // strings.
            do {
                s = DllLib.ptrToStringAnsi(walk);
                walk += s.length() + 1;
                count++;
            } while(s.length() != 0);
            count--;

            // Now that we know the count, allocate a String array of
            // that size.
            String envStrings[] = new String[count];

            // Now, do a second pass to extract each string.
            walk = env;
            for (int i = 0; i < count; i++) {
                envStrings[i] = DllLib.ptrToStringAnsi(walk);
                walk += envStrings[i].length() + 1;
            }
            return envStrings;

        } finally {
            FreeEnvironmentStrings(env);
        }
    }

    /** @dll.import("KERNEL32") */
    static native int     GetEnvironmentStrings();
    /** @dll.import("KERNEL32") */
    static native boolean FreeEnvironmentStrings(int env);
}




