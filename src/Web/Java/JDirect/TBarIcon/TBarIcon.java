/* Copyright (C) 1997 Microsoft Corporation. All rights reserved.
 *
 * This example sets up a TaskBar icon and uses a WndProc
 * to capture mouse messages.
 *
 */


import com.ms.dll.*;


/** @dll.import(auto) */
public class TBarIcon
{

    public static void main(String args[])
    {

        System.out.println("TBarIcon sample. Bring up the system taskbar");
        System.out.println("to see the icon (an exclamation point) inserted");
        System.out.println("by this application. Click on the icon on to");
        System.out.println("send mouse messages to the application.");
        System.out.println();
        System.out.println("Press Ctrl-C in this window to quit.");


        int hicon = LoadIcon(0, IDI_EXCLAMATION);


        // Note: passing in a root address rather than BreakHandler itself.
        // That's to prevent BreakHandler from being garbage-collected
        // as soon as SetConsoleCtrlHandler returns.
        SetConsoleCtrlHandler(DllLib.addrOf(Root.alloc(new BreakHandler())),
                              true);
        

        WNDCLASS wndclass = new WNDCLASS();

        wndclass.lpfnWndProc   = DllLib.addrOf(TBarWndProcRoot);
        wndclass.lpszClassName = "MyWindow";

        if (0 == RegisterClass(wndclass)) {
            throw new RuntimeException("RegisterClass failed.");
        }

        m_hwnd = CreateWindow(wndclass.lpszClassName,
                              "MyWindow",
                              WS_OVERLAPPEDWINDOW,
                              0,0,
                              0,0,
                              0, 0, 0, 0);
        if (0 == m_hwnd) {
            throw new RuntimeException("CreateWindow failed.");
        }

        NOTIFYICONDATA nid = new NOTIFYICONDATA();
        nid.hWnd   = m_hwnd;
        nid.uID    = 1;
        nid.uFlags = nid.NIF_MESSAGE|nid.NIF_ICON|nid.NIF_TIP;
        nid.uCallbackMessage = WM_MYTBARICON;
        nid.hIcon  = hicon;
        nid.szTip  = "TBarIcon Java Sample. Hit Ctrl-C to quit.";

        if (!Shell_NotifyIcon(NIM_ADD, nid)) {
            throw new RuntimeException("Could not add taskbar icon.");
        }
        m_fTBarIconActive = true;


        MSG msg = new MSG();
        while (GetMessage(msg, 0, 0, 0)) {
            TranslateMessage(msg);
            DispatchMessage(msg);
        }

        




    }


    static int     m_hwnd;
    static boolean m_fTBarIconActive = false;

    static void destroyTBarIcon()
    {
        if (m_fTBarIconActive) {
            m_fTBarIconActive = false;
            NOTIFYICONDATA nid = new NOTIFYICONDATA();
            nid.hWnd = m_hwnd;
            nid.uID = 1;
            nid.uFlags = nid.NIF_ICON;
            Shell_NotifyIcon(NIM_DELETE, nid);
        }
    }


    static final int TBarWndProcRoot = Root.alloc(new TBarWndProc());

    static final int WM_MYTBARICON = 0x500;


    /** @dll.import("KERNEL32") */
    static native boolean SetConsoleCtrlHandler(int     pHandlerRoutine,
                                                boolean fAdd);


    /** @dll.import("SHELL32") */
    static native boolean Shell_NotifyIcon(int dwMsg, NOTIFYICONDATA pnid);

    static final int NIM_ADD    = 0x00000000;
    static final int NIM_MODIFY = 0x00000001;
    static final int NIM_DELETE = 0x00000002;





    /** @dll.import("USER32") */
    static native int LoadIcon(int hinstance, int iconid);

    static final int IDI_EXCLAMATION = 32515;



    /** @dll.import("USER32") */
    static native boolean GetMessage(MSG msg,
                                     int hwnd,
                                     int uMsgFilterMin,
                                     int uMsgFilterMax);
    /** @dll.import("USER32") */
    static native boolean TranslateMessage(MSG msg);
    /** @dll.import("USER32") */
    static native int     DispatchMessage(MSG msg);


    /** @dll.import("USER32") */
    static native int RegisterClass(WNDCLASS wc);


    /** @dll.import("USER32") */
    static native int CreateWindowEx(int  dwExStyle,
                                     String lpszClassName,
                                     String lpszWindowName,
                                     int    style,
                                     int    x,
                                     int    y,
                                     int    nWidth,
                                     int    nHeight,
                                     int    hwndParent,
                                     int    hMenu,
                                     int    hInst,
                                     int    pvParam);
    static int CreateWindow(String lpszClassName,
                            String lpszWindowName,
                            int    style,
                            int    x,
                            int    y,
                            int    nWidth,
                            int    nHeight,
                            int    hwndParent,
                            int    hMenu,
                            int    hInst,
                            int    pvParam)
    {
        return CreateWindowEx(0, lpszClassName, lpszWindowName, style,
                              x, y, nWidth, nHeight, hwndParent, hMenu, hInst,
                              pvParam);
    }


    static final int WS_OVERLAPPEDWINDOW = 0x00CF0000;

}


//===================================================================
// Callback to receive window messages from the Taskbar Icon.
//===================================================================

/** @dll.import(auto) */
class TBarWndProc extends Callback 
{

    static final int WM_DESTROY       = 0x0002;
    static final int WM_LBUTTONDOWN   = 0x0201;
    static final int WM_LBUTTONUP     = 0x0202;
    static final int WM_LBUTTONDBLCLK = 0x0203;
    static final int WM_RBUTTONDOWN   = 0x0204;
    static final int WM_RBUTTONUP     = 0x0205;
    static final int WM_RBUTTONDBLCLK = 0x0206;

    public int callback(int hwnd, int message, int wParam, int lParam)
    {
        switch (message)
        {
            case WM_DESTROY:
                System.out.println("Posting WM_QUIT.");
                PostQuitMessage(0);
                return 0;


            case TBarIcon.WM_MYTBARICON:
                {
                    switch (lParam) {
                        case WM_LBUTTONDOWN:
                            System.out.println("Left button clicked.");
                            break;

                        case WM_LBUTTONDBLCLK:
                            System.out.println("Left button double-clicked.");
                            break;

                        case WM_RBUTTONDOWN:
                            System.out.println("Right button clicked.");
                            break;

                        case WM_RBUTTONDBLCLK:
                            System.out.println("Right button double-clicked.");
                            break;

                    }
                }
                return 0;

        }
        
        return DefWindowProc(hwnd, message, wParam, lParam);
    }



    /** @dll.import("USER32") */
    static native void PostQuitMessage(int nExitCode);

    /** @dll.import("USER32") */
    static native int DefWindowProc(int hwnd, int msg, int wParam, int lParam);

}



//===================================================================
// Handler for ctrl-C.
//===================================================================

/** @dll.import(auto) */
class BreakHandler extends Callback
{

    static final int CTRL_C_EVENT     = 0;
    static final int CTRL_BREAK_EVENT = 1;

    public boolean callback(int ctrlType)
    {
        if (ctrlType == CTRL_C_EVENT || ctrlType == CTRL_BREAK_EVENT) {
            TBarIcon.destroyTBarIcon();
            return false;
        }

        return false;

    }

    /** @dll.import("USER32") */
    static native void PostQuitMessage(int nExitCode);

}



/** @dll.struct(auto) */
class NOTIFYICONDATA
{
    public int     cbSize = DllLib.sizeOf(getClass());
    public int     hWnd;
    public int     uID;
    public int     uFlags;
    public int     uCallbackMessage;
    public int     hIcon;
    /** @dll.structmap([type=TCHAR[64]]) */
    public String  szTip;


    static public final int NIF_MESSAGE = 0x00000001;
    static public final int NIF_ICON    = 0x00000002;
    static public final int NIF_TIP     = 0x00000004;

    
}



/** @dll.struct(auto) */
class WNDCLASS
{
    int        style;
    int        lpfnWndProc;
    int        cbClsExtra;
    int        cbWndExtra;
    int        hInstance;
    int        hIcon;
    int        hCursor;
    int        hbrBackground;
    String     lpszMenuName;
    String     lpszClassName;
}

/** @dll.struct(auto) */
class MSG
{
    int     hwnd;
    int     message;
    int     wParam;
    int     lParam;
    int     time;
    int     ptx;
    int     pty;
}



