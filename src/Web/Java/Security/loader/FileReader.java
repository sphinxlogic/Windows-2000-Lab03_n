// FileReader.java
//
// Created 09/12/97
//
// (C)Copyright 1997 Microsoft Corporation, All rights reserved.
//

import java.io.*;


public class FileReader
{
    public static void main (String[] args)
    {
        for (int i = 0; i < args.length; i++)
        {
            tryfile(args[i]);
        }
    }

    static void tryfile (String filename)
    {
        System.out.print(filename+": "); System.out.flush();
        try
        {
            FileInputStream fis = new FileInputStream(filename);
            System.out.print("opened: "); System.out.flush();
            DataInputStream dis = new DataInputStream(fis);
            String line = dis.readLine();
            System.out.println(line);
        }
        catch (Throwable e)
        {
            System.out.println(e);
        }
    }
}


