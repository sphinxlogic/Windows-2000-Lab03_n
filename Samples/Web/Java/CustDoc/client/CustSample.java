//=========================================================================
// A simple Java console app that can be run using JVIEW. This app
// exercises the sample hook classes by passing them down to COM and
// from COM back to Java, in various ways.
//
// Copyright (c) 1997  Microsoft Corporation.  All rights reserved.
//
//=========================================================================



import java.awt.Point;
import java.awt.Rectangle;






class CustSample
{
    static ICustSample obj;



    public static void main(String[] args) {

        CCustSample cobj;

        startuptests();

        try {
            cobj = new CCustSample();
        } catch (Throwable t) {
            System.out.println(t);
            System.out.println("Could not instantiate CCustSample(). Likely causes:");
            System.out.println("  1. CustSample.dll not registered. Try \"regsvr32 CustSample.dll\".");
            System.out.println("  2. CCustSample.class not found. Check classpath.");
            throw new RuntimeException("Quitting.");
        }

        try {
          obj = (ICustSample) cobj;
        } catch (Throwable t) {
            System.out.println(t);
            System.out.println("Could not cast to ICustSample. Likely causes:");
            System.out.println("  1. ICustSample.class not found. Check classpath.");
            System.out.println("  2. One or more *Marshaler.class's not found. Check classpath.");
            System.out.println("  3. One or more *Marshaler.dll's not found. Check path.");
            System.out.println("  4. Installed version of MSJAVA does not support custom type marshaling.");

            throw new RuntimeException("Quitting.");
        }


        DoFixedPt_JavaToCom();
        obj.PassFixedPtsFromComToJava(new callbacks());

        DoMyVariant_JavaToCom();
        obj.PassMyVariantFromComToJava(new callbacks());


        DoPoint_JavaToCom();
        obj.PassPointFromComToJava(new callbacks());

        DoRect_JavaToCom();
        obj.PassRectFromComToJava(new callbacks());

        DoAnsi_JavaToCom();
        obj.PassAnsiFromComToJava(new callbacks());
     }



    public static void DoAnsi_JavaToCom()
    {
        {
            obj.PassPStrIn("If you can read this, C PassPStrIn works.");
        }
        {
            String s = obj.PassPPStrOutRetVal();
            println(s);
        }
        {
            String as[] = {"If you can read this, C PassPPStrIn works."};
            obj.PassPPStrIn(as);
        }
        {
            String as[] = {null};
            obj.PassPPStrOut(as);
            println(as[0]);
        }
        {
            String as[] = {"If you can read this, 'in' of C pass PPStrInOut works"};
            obj.PassPPStrInOut(as);
            println(as[0]);
        }
    }

    public static void DoRect_JavaToCom()
    {

        {
           Rectangle r = new Rectangle(5,6,7,8);
           println(r);
           obj.PassRectIn(r);
        }

        {
            Rectangle r = obj.PassPRectOutRetVal();
            println(r);
        }

        {
           Rectangle r = new Rectangle(20,30,40,50);
           println(r);
           obj.PassPRectIn(r);
        }

        {
            Rectangle ar[] = {null};
            obj.PassPRectOut(ar);
            println(ar[0]);
        }

        {
            Rectangle ar[] = {new Rectangle(1,1,1,1)};
            println(ar[0]);
            obj.PassPRectInOut(ar);
            println(ar[0]);
        }

        {
            Rectangle r = obj.PassPPRectOutRetVal();
            println(r);
        }

        {
            Rectangle ar[] = {new Rectangle(5,5,5,5)};
            println(ar[0]);
            obj.PassPPRectIn(ar);
        }
        {
            Rectangle ar[] = {null};
            obj.PassPPRectOut(ar);
            println(ar[0]);
        }
        {
           Rectangle ar[] = {new Rectangle(7,7,7,7)};
           obj.PassPPRectInOut(ar);
           println(ar[0]);
        }
    }


    public static void DoPoint_JavaToCom()
    {
        {
            Point p = new Point(-1,-1);
            obj.PassPPointOut(p);
            println(p);
        }
        {
           Point p = new Point(10,11);
           obj.PassPPointInOut(p);
           println(p);
        }
    }

    public static void DoFixedPt_JavaToCom()
    {

        //HRESULT PassFixedPtIn([in] FIXED fp);
        obj.PassFixedPtIn(4.5);

        //HRESULT PassPFixedPtOutRetVal([out,retval] FIXED *pfp);
        System.out.println(obj.PassPFixedPtOutRetVal());

        //HRESULT PassPFixedPtIn([in] FIXED *pfp);
        obj.PassPFixedPtIn(8.5);


        //HRESULT PassPFixedPtOut([out] FIXED *pfp);
        {
            double ad[] = {0.0};
            obj.PassPFixedPtOut(ad);
            System.out.println(ad[0]);
        }

        //HRESULT PassPFixedPtInOut([out] FIXED *pfp);
        {
            double ad[] = {8.7};
            System.out.println("Before: " + ad[0]);
            obj.PassPFixedPtInOut(ad);
            System.out.println("After:  " + ad[0]);
        }


    }

    public static void DoMyVariant_JavaToCom()
    {
        obj.PassMyVariantIn("If you can read this, PassMyVariantIn succeeded.");

        System.out.println(obj.PassPMyVariantOutRetVal());

        obj.PassPMyVariantIn("If you can read this, PassPMyVariantIn succeeded.");

        {
            String as[] = {null};
            obj.PassPMyVariantOut(as);
            System.out.println(as[0]);
        }

        {
            String as[] = {"If you can read this, the 'in' part of PassPMyVariantInOut works."};
            obj.PassPMyVariantInOut(as);
            System.out.println(as[0]);
        }
    }

    private static void println(Object o) { System.out.println(o); }
    private static void println(double o) { System.out.println(o); }
    private static void println(int o)    { System.out.println(o); }

    private static void startuptests()
    {
    }



}



class callbacks implements ICustSample
{


    public void PassFixedPtIn(double fp)
    {
        println("Java PassFixedPtIn called: " + fp);
    }
  
    public double PassPFixedPtOutRetVal()
    {
        println("Java PassPFixedPtOutRetVal called. Returning 8.5");
        return 8.5;
    }

    public void PassPFixedPtIn(double pfp)
    {
        println("Java PassFixedPtIn called: " + pfp);
    }
  
    public void PassPFixedPtOut(double[] pfp)
    {
        pfp[0] = 3.25;
        println("Java PassPFixedPtOut called. Returning " + pfp[0]);
    }

    public void PassPFixedPtInOut(double[] pfp)
    {
        println("Java PassPFixedPtInOut called. Got " + pfp[0] + ". Adding 2.0");
        pfp[0] += 2.0;
    }
  
    public void PassFixedPtsFromComToJava(ICustSample pCustSample)
    {
        throw new RuntimeException("Don't call me.");
    }

    public void PassMyVariantIn(String v)
    {
        println("Java PassMyVariantIn called: " + v);
    }

    public String PassPMyVariantOutRetVal()
    {
        println("Java PassPMyVariantOutRetVal called.");
        return "If you can read this, Java PassPMyVariantOutRetVal worked."; 
    }
  
    public void PassPMyVariantIn(String pv)
    {
        println("Java PassPMyVariantIn called: " + pv);
    }
  
    public void PassPMyVariantOut(String[] pv)
    {
        println("Java PassPMyVariantOut called.");
        pv[0] = "If you can read this, Java PassPMyVariantOut worked."; 
    }
  
    public void PassPMyVariantInOut(String[] pv)
    {
        println("Java PassPMyVariantInOut called: " + pv[0]);
        pv[0] = "If you can read this, the 'out' part of Java PassPMyVariantInOut worked."; 
    }

    public void PassMyVariantFromComToJava(ICustSample pCustSample)
    {
        throw new RuntimeException("Don't call me.");
    }

    public void PassPPointOut(Point p)
    {
        println("Java PassPPointOut called. Returning [5,6].");
        p.x = 5;
        p.y = 6;
    }

    public void PassPPointInOut(Point p)
    {
        println("Java PassPPointInOut called (" + p + "). Translating x&y by 3.");
        p.x += 3;
        p.y += 3;
    }

    public void PassPointFromComToJava(ICustSample pCustSample)
    {
        throw new RuntimeException("Don't call me.");
    }

    public void PassRectIn(java.awt.Rectangle r)
    {
        println("Java PassRectIn called: " + r);
    }

  
    public java.awt.Rectangle PassPRectOutRetVal()
    {
        Rectangle r = new Rectangle(6,7,8,9);
        println("Java PassPRectOutRetVal called. Returning " + r);
        return r;
    }
  
    public void PassPRectIn(java.awt.Rectangle pr)
    {
       println("Java PassPRectIn called: " + pr);
    }

    public void PassPRectOut(java.awt.Rectangle[] pr)
    {
        Rectangle r = new Rectangle(16,17,18,19);
        println("Java PassPRectOut called. Returning " + r);
        pr[0] = r;
    }
  
    public void PassPRectInOut(java.awt.Rectangle[] pr)
    {
        println("Java PassPRectInOut called: " + pr[0]);
        Rectangle r = new Rectangle(26,27,28,29);
        println("Returning " + r);
        pr[0] = r;
    }
  
    public java.awt.Rectangle PassPPRectOutRetVal()
    {
        Rectangle r = new Rectangle(36,37,38,39);
        println("Java PassPPRectOutRetVal called. Returning " + r);
        return r;
    }
  
    public void PassPPRectIn(java.awt.Rectangle[] ppr)
    {
        println("Java PassPPRectIn called: " + ppr[0]);
    }
  
    public void PassPPRectOut(java.awt.Rectangle[] ppr)
    {
        Rectangle r = new Rectangle(46,47,48,49);
        println("Java PassPPRectOut called. Returning " + r);
        ppr[0] = r;
    }
    public void PassPPRectInOut(java.awt.Rectangle[] ppr)
    {
        println("Java PassPPRectInOut called: + " + ppr[0]);
        Rectangle r = new Rectangle(56,57,58,59);
        println("Returning " + r);
        ppr[0] = r;

    }

    public void PassRectFromComToJava(ICustSample pCustSample)
    {
        throw new RuntimeException("Don't call me.");
    }

    public void PassPStrIn(String pstr)
    {
        println("Java PassPStrIn called: " + pstr);
    }

    public String PassPPStrOutRetVal()
    {
        return "If you can read this, Java PassPStrOutRetVal worked.";
    }

    public void PassPPStrIn(String[] ppstr)
    {
        println("Java PassPPStrIn called: " + ppstr[0]);
    }

    public void PassPPStrOut(String[] ppstr)
    {
        ppstr[0] = "If you can read this, Java PassPStrOut worked.";
    }

    public void PassPPStrInOut(String[] ppstr)
    {
        println("Java PassPPStrInOut called: " + ppstr[0]);
        ppstr[0] = "If you can read this, 'out' part of Java PassPStrInOut worked.";
    }


    public void PassAnsiFromComToJava(ICustSample pCustSample)
    {
        throw new RuntimeException("Don't call me.");
    }

    private void println(Object o) { System.out.println(o); }
    private void println(double o) { System.out.println(o); }
    private void println(int o)    { System.out.println(o); }


}
