//
//  Sieve.java
//
//  Copyright (c) 1997, Microsoft Corporation.  All rights reserved.
//

class Sieve
{
    native static int CountPrimes(byte[] abFlags);
    static final double F = 3.2;
    
    static
    {
        System.loadLibrary("SieveDemo");
    }
}

