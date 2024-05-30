/* Copyright (C) 1997 Microsoft Corporation. All rights reserved.
 *
 * This example shows how to obtain the SetLastError() error code from a
 * Win32 api. It is not safe to call GetLastError() yourself because the
 * Virtual Machine can make api calls itself that overwrite the error value.
 * Instead, you must use the "SetLastError" keyword (shown on the
 * declaration for FindNextFile) which will cause the Virtual Machine
 * to capture the error code and save it in a per-thread data block.
 * This error code can then be retrieved using the getLastWin32Error()
 * method.
 */

import com.ms.dll.DllLib;
import com.ms.dll.Win32Exception;


/** @dll.import("KERNEL32",auto) */
public class LastErr
{
    public static void main(String args[])
    {
        WIN32_FIND_DATA fd = new WIN32_FIND_DATA();
        String searchPattern;

        if (args.length < 1) {
            searchPattern = "*.*";
        } else {
            searchPattern = args[0];
        }

        System.out.println("Finding all files that match the pattern \"" +
                           searchPattern +
                           "\"");
        System.out.println("----------------------------------------------");

        int hFindFile = FindFirstFile(searchPattern, fd);
        if (hFindFile == -1) {
            System.err.println("FindFirstFile failed.");
            return;
        }
        try {
            do {
                System.out.println(fd.cFileName);
            } while (FindNextFile(hFindFile, fd));

            int errcode = DllLib.getLastWin32Error();
            if (errcode != ERROR_NO_MORE_FILES) {
                String errDescription;
                errDescription = Win32Exception.getErrorDescription(errcode);
                System.err.println("Unexpected FindNextFile() failure: " +
                                   errDescription);
            }


        } finally {
            FindClose(hFindFile);
        }

    }


    private static native int     FindFirstFile(String          searchPattern,
                                                WIN32_FIND_DATA pfd);
    /** @dll.import(setLastError) */
    private static native boolean FindNextFile(int             hFindFile,
                                               WIN32_FIND_DATA pfd);
    private static native boolean FindClose(int hFindFile);

    private static final int ERROR_NO_MORE_FILES = 18;

}

/** @dll.struct(auto) */
class WIN32_FIND_DATA
{

    int      dwFileAttributes;
    FILETIME ftCreation;
    FILETIME ftLastAccessTime;
    FILETIME ftLastWriteTime;
    int      nFileSizeHigh;
    int      nFileSizeLow;
    int      dwReserved0;
    int      dwReserved1;

    /** @dll.structmap([type=TCHAR[260]]) */
    String   cFileName;

    /** @dll.structmap([type=TCHAR[14]]) */
    String   cAlternateFileName;



}

/** @dll.struct(auto) */
class FILETIME
{
    int      dwLowDateTime;
    int      dwHighDateTime;

}

