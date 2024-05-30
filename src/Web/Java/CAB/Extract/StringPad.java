//
// StringPad.java
//
// Performs string padding for outputting to the display
//
// Copyright (C) 1997 Microsoft Corporation
// All rights reserved 
//
final class StringPad
{
    // pads on the right of the string
    static String padPostfix(String string, int desired_length)
    {
        if (string.length() >= desired_length)
        {
            return string;
        }
        else
        {
            char temp[] = new char[desired_length - string.length()];

            for (int i = 0; i < temp.length; i++)
                temp[i] = ' ';

            return string + temp;
        }
    }

    // pads on the left of the string
    static String padPrefix(String string, int desired_length)
    {
        if (string.length() >= desired_length)
        {
            return string;
        }
        else
        {
            char temp[] = new char[desired_length - string.length()];

            for (int i = 0; i < temp.length; i++)
                temp[i] = ' ';

            return temp + string;
        }
    }

    // pads on the left of the string
    static String padNumber(int value, int desired_length)
    {
        return padPrefix(Integer.toString(value), desired_length);
    }

    // pads on the left of the string
    static String padNumber(long value, int desired_length)
    {
        return padPrefix(Long.toString(value), desired_length);
    }
}
