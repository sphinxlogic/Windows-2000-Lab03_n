//
// CabMaker.java
//
// Copyright (C) 1997 Microsoft Corporation
// All rights reserved 
//
import com.ms.util.cab.*;
import java.io.*;

final class CabMaker implements CabConstants, CabProgressInterface
{
    // name of cabinet to create
    String      cabinet_name;

    // command line argument list
    String[]    file_list;

    // location of first file in command line argument list
    int         file_list_begin_index;

    // CabCreator object for creating the cabinets
    CabCreator  cab_creator;

    // compression method and window to use
    int         compression_method, compression_window;

    // recurse into subdirectories?
    boolean     can_recurse;

    // output stream of the cabinet we are creating
    FileOutputStream    output_cabinet;


    // constructor
    CabMaker(
        String      new_cabinet_name, 
        String[]    new_file_list, 
        int         new_file_list_begin_index,
        int         new_compression_method,
        int         new_compression_window,
        boolean     new_can_recurse
    )
    {
        cabinet_name            = new_cabinet_name;
        file_list               = new_file_list;
        file_list_begin_index   = new_file_list_begin_index;
        can_recurse             = new_can_recurse;
        compression_method      = new_compression_method;
        compression_window      = new_compression_window;
    }


    //
    // Create the cabinet
    //
    // Returns whether cabinet creation was successful
    //
    boolean create()
    {
        CabFolderEntry folder;

        System.out.println("Creating new cabinet: "+cabinet_name);

        try
        {
            output_cabinet = new FileOutputStream(cabinet_name);
        }
        catch (IOException ioe)
        {
            System.out.println("Error opening " + cabinet_name + " for output");
            return false;
        }

        //
        // Create a new CabCreator object, and pass ourselves in as the
        // CabProgressInterface.
        //
        cab_creator = new CabCreator(this);

        try
        {
            cab_creator.create(output_cabinet);
        }
        catch (Exception e)
        {
            closeAndDeleteCabinet();
            System.out.println("Error initializing cabinet creation: "+e.getMessage());
            return false;
        }

        //
        // Start a new folder, select compression method
        //
        folder = new CabFolderEntry();

        try
        {
            folder.setCompression(compression_method, compression_window);
            cab_creator.newFolder(folder);
        }
        catch (Exception e)
        {
            closeAndDeleteCabinet();
            System.out.println("Error starting new folder: "+e.getMessage());
        }

        //
        // Add the specified files to the cabinet.
        //
        // Read the file names from the command line argument list.
        //
        for (int i = file_list_begin_index; i < file_list.length; i++)
        {
            File file_to_add;

            file_to_add = new File(file_list[i]);

            if (file_to_add.isDirectory())
            {
                addDirectoryTree(file_list[i]);
            }
            else
            {
                addFile(file_list[i]);
            }
        }           

        //
        // Add files added; now complete cabinet creation
        //
        try
        {
            cab_creator.complete();
        }
        catch (Exception e)
        {
            closeAndDeleteCabinet();
            System.out.println("Cabinet creation failed: "+e.getMessage());
            return false;
        }

        //
        // Close the output stream we have been writing the cabinet to
        //
        try
        { 
            output_cabinet.close(); 
        } 
        catch (IOException ioe) 
        {
            System.out.println("Error closing cabinet: "+ioe.getMessage());
            return false;
        }

        return true;
    }


    //
    // This method is called if an error occurs; we close the cabinet we were
    // creating, and delete it
    //
    private void closeAndDeleteCabinet()
    {
        try
        { 
            output_cabinet.close(); 

            File file = new File(cabinet_name);
            file.delete();
        } 
        catch (Exception e) 
        {
            // ignore
        }
    }


    //
    // Implements CabProgressInterface
    //
    public Object progress(
        int             progress_type,
        long            val1,
        long            val2,
        Object[]        progress_data
    )
    {
        if (progress_type == CAB_PROGRESS_INPUT)
        {
            System.out.print(".");
            System.out.flush();
        }
        // ignore messages we don't know how to handle

        return null;
    }


    //
    // Adds a file to the cabinet
    //
    private void addFile(String filename)
    {
        CabFileEntry    cab_file_entry;
        File            file;
        FileInputStream input;

        System.out.print("  " + filename + " ");

        file = new File(filename);

        cab_file_entry = new CabFileEntry();

        // determine the name under which to store the file in the cabinet
        
        if (file.isAbsolute())
        {
            // if this is an absolute path, then don't store any of the path data
            cab_file_entry.setName(file.getName());
        }
        else
        {
            // if this is a relative path, store the path data
            cab_file_entry.setName(filename);
        }

        try
        {
            input = new FileInputStream(file);
        }
        catch (IOException ioe)
        {
            System.out.println("Error, cannot open " + filename + " for input");
            return;
        }

        // set file attributes
        if (file.canWrite() == false)
            cab_file_entry.setReadOnly(true);

        try
        {
            cab_creator.addStream(input, cab_file_entry);
        }
        catch (Exception e)
        {
            System.out.println();
            System.out.println("Error adding file: "+e.getMessage());
        }

        System.out.println();
    }


    //
    // Adds a directory tree to the cabinet
    //
    private void addDirectoryTree(String path)
    {
        String[]    list;
        File        current_dir;

        current_dir = new File(path);

        // get a list of files in this directory
        list = current_dir.list();

        if (list != null)
        {
            for (int i = 0; i < list.length; i++)
            {
                String  full_name;
                File    current_file;
            
                // the full name of this file
                full_name       = path + File.separator + list[i];

                // get a handle on this file
                current_file    = new File(full_name);

                if (current_file.isFile())
                {
                    //  it's a file, so add it
                    addFile(full_name);
                }
                else if (current_file.isDirectory())
                {
                    // it's a directory, so recurse into it if the recurse
                    // into subdirs command-line option was selected
                    if (can_recurse)
                        addDirectoryTree(full_name);
                }
            }
        }
    }
}
