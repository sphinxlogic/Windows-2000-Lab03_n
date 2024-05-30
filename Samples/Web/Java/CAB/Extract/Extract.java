//
// Extract.java
//
// This application demonstrates how to use the CabDecoder class to extract
// files from, or list files in cabinets.
//
// Copyright (C) 1997 Microsoft Corporation
// All rights reserved 
//
import com.ms.util.cab.CabDecoder;
import com.ms.util.cab.CabDecoderInterface;
import com.ms.util.cab.CabFileEntry;
import com.ms.util.cab.CabFolderEntry;
import com.ms.util.cab.CabException;
import java.io.*;
import java.util.Enumeration;
import java.util.Date;


final class Extract implements CabDecoderInterface
{
    private String          cabinet_filename;
    private String          output_directory;
    private CabDecoder      cab_decoder;
    private FileInputStream input;


    private Extract(String filename)
    {
        cabinet_filename    = filename;
    }


    //
    // Entrypoint
    //
    public static void main(String args[])
    {
        Extract extractor;
        int     cab_filename_argnum;

        if (args.length < 1)
        {
            displayHelp();
        }
        else
        {
            String  cab_filename;
            String  specified_output_directory;
            boolean list_cabinet_only = false;

            if (args[0].equalsIgnoreCase("/V"))
            {
                if (args.length < 2)
                {
                    displayHelp();
                    return;
                }

                list_cabinet_only = true;
                cab_filename_argnum = 1;
            }
            else
            {
                cab_filename_argnum = 0;
            }

            cab_filename = args[cab_filename_argnum];

            if (args.length > cab_filename_argnum+1)
                specified_output_directory = args[cab_filename_argnum+1];
            else
                specified_output_directory = null;

            //
            // Need to create an object to pass to the CabDecoder class
            //
            extractor = new Extract(cab_filename);
            
            //
            // If cabinet opened successfully
            //
            if (extractor.openCabinetForReading() == true)
            {
                //
                // List cabinet contents, or extract, depending upon what
                // the user wanted
                //
                if (list_cabinet_only)
                    extractor.listCabinet();
                else
                    extractor.extractCabinet(specified_output_directory);
                
                //
                // Clean up
                //
                extractor.closeCabinet();
            }
        }
    }


    public InputStream openCabinet(String disk_name, String cabinet_name)
    {
        return null;
    }


    //
    // Open the cabinet
    //
    // Returns whether the cabinet was opened successfully
    //
    private boolean openCabinetForReading()
    {
        try
        {
            input = new FileInputStream(cabinet_filename);
        }
        catch (FileNotFoundException fnf)
        {
            System.out.println("Cabinet not found: "+cabinet_filename);
            return false;
        }

        //
        // If the cabinet header is corrupt, an exception will be thrown
        //
        try
        {
            cab_decoder = new CabDecoder(input, this);
        }
        catch (Exception e)
        {
            System.out.println("Error processing cabinet: "+e.getMessage());
            try { input.close(); } catch (IOException closing_ioe) {}
            return false;
        }

        return true; // success
    }


    //
    // Close the cabinet's input stream
    //
    private void closeCabinet()
    {
        try
        {
            input.close();
        }
        catch (IOException ioe)
        {
            System.out.println("IOException closing cabinet: "+ioe.getMessage());
        }
    }


    //
    // List the contents of the cabinet
    //
    private void listCabinet()
    {
        //
        // Assume an 80 column display
        //
        System.out.println();
        System.out.println("Listing files in cabinet '"+cabinet_filename+"':");
        System.out.println();
        System.out.println("File name                                 File size  Attr  File date");
        System.out.println("----------------------------------------  ---------  ----  -----------------");

        //
        // Enumerate the complete contents of the cabinet, including CabFolderEntry
        // objects
        //
        Enumeration cab_contents = cab_decoder.entries(true);

        while (cab_contents.hasMoreElements())
        {
            Object entry;
            
            entry = cab_contents.nextElement();

            if (entry instanceof CabFolderEntry)
            {
                CabFolderEntry folder = (CabFolderEntry) entry;

                System.out.println();
                System.out.println(
                    "FOLDER (" + folder.compressionToString() + " compression):"
                );
            }
            else if (entry instanceof CabFileEntry)
            {
                CabFileEntry file = (CabFileEntry) entry;

                //
                // Display file information in tabulated form.
                //
                // Use locale-specific date format
                //
                System.out.println(
                    StringPad.padPostfix(file.getName(),42) +
                    StringPad.padNumber(file.getSize(), 9) + "  " +
                    cabFileEntryAttributesToString(file) + "  " + 
                    file.getDate().toLocaleString()
                );
            }
            // ignore objects we don't know how to handle

        }
    }


    //
    // Extract the cabinet
    //
    private void extractCabinet(String new_output_directory)
    {
        output_directory = new_output_directory;

        System.out.println();
        System.out.println("Extracting files from cabinet '"+cabinet_filename+"':");

        //
        // If an error occurs, an exception will be thrown
        //
        try
        {
            cab_decoder.extract();
        }
        catch (Exception e)
        {
            System.out.println("Error extracting cabinet: "+e.getMessage());
        }
    }


    //
    // Convert file attributes to a string
    //
    private static String cabFileEntryAttributesToString(CabFileEntry cffile)
    {
        return  (cffile.isReadOnly() ? "r" : "-") +
                (cffile.isArchive()  ? "a" : "-") +
                (cffile.isHidden()   ? "h" : "-") +
                (cffile.isSystem()   ? "s" : "-");
    }

    
    //
    // Command-line help
    //
    private static void displayHelp()
    {
        System.out.println("Cabinet extract utility");
        System.out.println();
        System.out.println("Usage: extract [/V] <cabinet name>");
        System.out.println();
        System.out.println("       Use /V to list cabinet contents instead of extracting");
    }


    //
    // Converts a filename which uses the backslash as the separator character,
    // to use the local system's separator character
    //
    // This stage is necessary since cab files are stored using the backslash
    // as the separator.
    //
    static String convertFilenameToSystemSeparator(String filename)
    {
        if (File.separatorChar != '\\')
            return filename.replace('\\', File.separatorChar);
        else
            return filename;
    }

    

    //
    // Implements CabDecoderInterface
    //
    public boolean closeOutputStream(OutputStream output, CabFileEntry file, boolean success)
    {
        try
        {
            output.close();
        }
        catch (IOException ioe)
        {
            System.out.println("IOException closing output file "+file.getName());
        }

        return true;
    }


    //
    // Called for each file in the cabinet, when we're extracting
    //
    public OutputStream openOutputStream(CabFileEntry file)
    {
        File                output_file;
        FileOutputStream    output_stream;
        String              filename, complete_filename;

        // Convert filename to use local separator convention
        filename = convertFilenameToSystemSeparator(file.getName());

        output_file = new File(filename);
        
        if (false && output_file.isAbsolute())
        {
            System.out.println(
                "  ** Not extracting file with absolute pathname: " + filename
            );

            return null;
        }

        // Display the (converted) filename
        System.out.println("   " + file.getName());

        // Get the complete filename (with output directory prefix)
        if (output_directory != null)
            complete_filename = output_directory + File.separator + filename;
        else
            complete_filename = filename;

        // Open file for output
        output_file = new File(complete_filename);

        try
        {
            output_stream   = new FileOutputStream(output_file);
        }
        catch (IOException ioe)
        {
            //
            // Couldn't create the output stream; it could be that the
            // directories don't exist for it, so create them and try again
            //
            String parent_dir_name = output_file.getParent();

            if (parent_dir_name == null)
            {
                return null;
            }
            else
            {
                File parent_dir = new File(parent_dir_name);
                
                if (parent_dir != null)
                    parent_dir.mkdirs();
            }

            try
            {
                output_stream   = new FileOutputStream(output_file);
            }
            catch (IOException ioe2)
            {
                System.out.println(
                    "IOException opening output file " + complete_filename
                );

                return null;
            }
        }

        return output_stream;
    }


    //
    // For opening spanned cabinets
    //
    public InputStream openCabinet(String disk_name, String cabinet_name, int set_id)
    {
        return null;
    }


    //
    // Don't want any reserved areas
    //
    public boolean reservedAreaData(int type, byte[] reserved_data, int reserved_data_size, byte[] other_data, int other_data_size)
    {
        return false;
    }


    //
    // The cab decoder doesn't send any progress reports at this time
    //
    public Object progress(int progress_type, long val1, long val2, Object[] progress_data)
    {
        // return null for progress reports we don't know how to handle
        return null;
    }
}
