//
// Create.java
//
// This application demonstrates how to use the CabCreate class to create
// cabinets
//
// Copyright (C) 1997 Microsoft Corporation
// All rights reserved 
//
import com.ms.util.cab.CabCreator;
import com.ms.util.cab.CabConstants;


final class Create implements CabConstants
{
    // the default compression mode
    static int compression_method = COMPRESSION_MSZIP;
    static int compression_window = 16;

    // recurse into subdirectories when given a directory name?
    static boolean recurse_into_subdirs = false;

    //
    // Entrypoint
    //
    public static void main(String args[])
    {
        if (args.length < 2)
        {
            displayHelp();
        }
        else
        {
            int cab_filename_arg;

            // if this returns -1, it means invalid arguments
            cab_filename_arg = parseArgs(args);

            if (cab_filename_arg != -1)
            {
                CabMaker creator;

                // Need a non-static class object to pass to the CabCreator class
                creator = new CabMaker(
                    args[cab_filename_arg], // cabinet name
                    args,                   // file list
                    cab_filename_arg + 1,   // where file list starts in args[] 
                    compression_method,
                    compression_window,
                    recurse_into_subdirs
                );

                creator.create();
            }
        }
    }


    //
    // Argument parsing
    //
    static int parseArgs(String args[])
    {
        int arg;

        for (arg = 0; arg < args.length; arg++)
        {
            // look for command-line switches
            if (args[arg].charAt(0) == '/' || args[arg].charAt(0) == '-')
            {
                if (args[arg].length() < 2)
                {
                    System.out.println("Invalid arguments");
                    return -1;
                }

                switch (args[arg].charAt(1))
                {
                    default:
                    {
                        System.out.println("Unknown option "+args[arg]);
                        return -1;
                    }

                    case 'h':
                    case '?':
                    {
                        displayHelp();
                        return -1;
                    }

                    case 'r':
                    {
                        recurse_into_subdirs = true;
                        break;
                    }

                    case 'm':
                    {
                        String compression_mode_name;

                        if (arg + 1 >= args.length)
                        {
                            System.out.println("-m option must be followed by compression method");
                            return -1;
                        }

                        compression_mode_name = args[arg+1];

                        if (compression_mode_name.equals("NONE"))
                        {
                            compression_method = COMPRESSION_NONE;
                            compression_window = 0;
                        }
                        else if (compression_mode_name.equals("MSZIP"))
                        {
                            compression_method = COMPRESSION_MSZIP;
                            compression_window = 16;
                        }
                        else if (compression_mode_name.startsWith("LZX"))
                        {
                            compression_method = COMPRESSION_LZX;

                            // catch string out-of-bounds and integer conversion
                            // exceptions
                            try
                            {
                                compression_window = Integer.valueOf(compression_mode_name.substring(4)).intValue();
                            }
                            catch (Exception e)
                            {
                                System.out.println("LZX compression requires a window size parameter");
                                return -1;
                            }

                            if (compression_window < 15 || compression_window > 21)
                            {
                                System.out.println("LZX compression window must be in 15..21 range");
                                return -1;
                            }
                        }
                        else
                        {
                            System.out.println("Unknown compression method "+compression_mode_name);
                            return -1;
                        }

                        arg++;
                        break;
                    }
                }
            }
            else
            {
                break;
            }
        }

        return arg;
    }


    //
    // Command-line help
    //
    private static void displayHelp()
    {
        System.out.println("Cabinet creation utility");
        System.out.println();
        System.out.println("Usage: Create <options> <cabinet name> [<files>]");
        System.out.println();
        System.out.println("Options:");
        System.out.println("  /m <mode>  Set compression mode [LZX:<15..21>|MSZIP|NONE]");
        System.out.println("  /r         Recurse into subdirectories");
    }
}
