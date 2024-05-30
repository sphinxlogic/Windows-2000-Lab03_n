/**
 * UseTableStream: Hook up the HTMLTableStream object to the Framework's Response
 * object, which is an OutputStream.
 */

package IISSample;

import java.io.*;
import aspcomp.*;


public class UseTableStream 
{

    static byte[] byteArray = {
            (byte)'1', (byte)' ', (byte)'2', (byte)' ', (byte)'3', 
            (byte)' ', (byte)'4', (byte)' ', (byte)'\n', (byte)' ', 
            (byte)'5', (byte)' ', (byte)'6', (byte)' ', (byte)'7', 
            (byte)' ', (byte)'8', (byte)' ', (byte)'\n', (byte) ' ',
            (byte)'9', (byte)' ', (byte)'1', (byte)'0', (byte)' ', 
            (byte)'1', (byte)'1', (byte)' ', (byte)'1', (byte)'2', 
            (byte) ' ',(byte) '\n'
    };

    // Create a byte stream, and use it as input to the HTML table stream processor
    public void makeTable()
    {
        Response response = AspContext.getResponse();

        ByteArrayInputStream inputStream = new ByteArrayInputStream(byteArray);

        HTMLTableStream ts = new HTMLTableStream(inputStream);

        ts.setCols(4);
        ts.setBorderWidth(2);
        ts.setCellSpacing(3);
        ts.setBorderColor("Green");

        ts.OutputTable(response);
    }

}
