import java.applet.*;
import com.ms.com.* ;

public class JavaTest extends Applet
{
    public void JavaSetCaption(String sOld, Variant vtJScriptHelper)
	{
        Dispatch.call(vtJScriptHelper.toDispatch(), "JScriptSetCaption", sOld.equals("Hello") ? "Goodbye" : "Hello");
	}
}

