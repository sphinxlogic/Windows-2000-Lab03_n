//
//
// VJSecuritySampleClass
//
//

import com.ms.mtx.*;

//import vjsecuritysampleclasslib.*;

/**
 * @com.register ( clsid=204FAAF9-A692-11D2-8F24-00C04F79D77B, typelib=204FAAF8-A692-11D2-8F24-00C04F79D77B )
 */
 /**
  * @com.register ( clsid=14D092F1-B545-11D2-ADA6-00C04F79D77B, typelib=14D092F0-B545-11D2-ADA6-00C04F79D77B )
  */
/*public  */ class VJSecuritySampleClass
 //  implements vjsecuritysampleclasslib.IVJSecuritySampleClass, vjsecuritysampleclasslib.IVJSecuritySampleClass
{
   private static final String CLSID = 
      "8cccc630-14f0-11d1-824c-00aa00a3f13e";
  
public int AmIAnAdministrator()
{
	try
	{
		if(Context.isSecurityEnabled())
			 //Return Error code
			 return 2;

		if(Context.isCallerInRole("Administrator"))
			 return 1;
		else
			 return 0;
	}
	catch(Exception e)
	{
		return 2;
	}

}

public String WhoAmI()
{
	 try {
		  if (Context.isSecurityEnabled())
				//Return Error code
				return null;

		  return Context.getDirectCallerName();
	 }
	 catch (Exception e){
		  return null;
	 }
}

}
