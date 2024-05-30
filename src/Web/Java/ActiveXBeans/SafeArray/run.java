// 
// Copyright(C) 1997 Microsoft Corporation  All Rights Reserved
//
// This sample shows how to use SafeArrays in Java.
//
//
import com.ms.com.*;
import simpleobject.*;

public class run
{
    public static void main(String args[])
    {

        // Instantiate a COM object (which is implemented in Visual Basic)
        _SimpleObject obj = new SimpleObject();



        // Passing a SafeArray to COM object:
        //
        // Here we invoke the routine:
        //
        //    'Returns the sum of the elements of A
        //    Public Function ComputeSum(A() As Long) As Long
        //
        // with a 5-element array containing the elements {0,1,2,3,4}
        //
        // Remember: VB "Long" == Java "int".
        SafeArray sa = new SafeArray(Variant.VariantInt, 5);
        int ia[] = {0,1,2,3,4};
        sa.fromIntArray(ia);
        System.out.println("ComputeSum() returned " + obj.ComputeSum(sa));
        System.out.println();


        // Receiving a SafeArray from a COM object:
        //
        // Here we invoke the routine:
        //
        //    'Returns an array of the squares of 0..10.
        //    Public Function CreateSquares() As Variant
        //
        // (the returned Variant will contain a SafeArray of Long).
        //
        // Remember: VB "Long" == Java "int".
        Variant v = obj.CreateSquares();
        sa = v.toSafeArray();

        // We can extract elements one at a time...
        System.out.print("CreateSquares() returned {"); 
        for (int i = sa.getLBound(); i <= sa.getUBound(); i++) {
            System.out.print(" " + sa.getInt(i));
        }
        System.out.println(" }");

        System.out.print("Converting results to Java array: {"); 
        // ...or translate the entire SafeArray to a Java array.
        ia = sa.toIntArray();
        for (int i = 0; i < ia.length; i++) {
            System.out.print(" " + ia[i]);
        }
        System.out.println(" }");
    }
}
