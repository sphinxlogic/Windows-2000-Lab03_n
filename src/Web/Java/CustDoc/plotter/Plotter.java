// Copyright (c) 1997  Microsoft Corporation.  All rights reserved.
//=========================================================================
// A simple Java console app that can be run using JVIEW. 
//=========================================================================



import java.awt.Point;






class Plotter
{
    public static void main(String[] args) {

        IPlotter plotter = (IPlotter) new CPlotter();

        plotter.DrawLine(new Point(1,2), new Point(3,4));


     }





}
