//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//

import com.ms.util.SystemVersionManager;
import java.util.Properties;

/**
 *	Version Mananger class for AFC. This class will obtain version information
 *	about AFC through the getAFCVersion() method.
 *
 *	@version	1.0, 8/19/97
 */

public final class AFCVersionManager
{
	/**
	 *	Creates a new Properties object with the keys necessary for extracting
	 *	version information. Uses the passed values as the version number.
	 *
	 *	@param	major	Major version number	
	 *	@param	minor	Minor version number	
	 *	@param	buildnum	Build number
	 *	@param	buildinc	Build increment number
	 *	@param	description	Description of the version		 
	 *	@returns	A Properties object which holds the version information
	 */
	public static Properties createVersion (int major, int minor, int buildnum, int buildinc, String description)
		{
			// from the VersionManager sample from SDK 1.5 Samples.

			Properties info = new Properties();

			// These properties should be present on all version objects.
        
			info.put("MajorVersion", Integer.toString(major));
			info.put("MinorVersion", Integer.toString(minor));
			info.put("Description", new String(description));
        			
			return info;
		}

	/**
	 *	Find version information for the specified package. Returns this
	 *	information in a Properties object. See the com.util.SystemVersionManager
	 *	class for the keys to expect in the returned Properties object.
	 *
	 *	@param	pkgname	Name of package to retrieve version information
	 *	@returns	A Properties object which holds the version information
	 */
	public static Properties getPackageVersion (String pkgname)
		{
			// from the VersionManager sample from SDK 1.5 Samples.

	        Properties info = null;
        
		    try
				{
					info = SystemVersionManager.getPackageVersion(pkgname);

					if (info != null)
						return info;
				}
			catch (Throwable e)
				{
					// No system version manager installed.
				}
			
			if (pkgname == null)
				return null;
            
    
			// Attempt to locate a 'Version' class within the specified package.
			// If not found, try the parent package.
        
			try
				{
					Class c = Class.forName((pkgname.length() > 0) ? (pkgname+".Version") : "Version");
					Object o = c.newInstance();
					//info = ((Version)o).getVersion();						
					info = (Properties)o;
				}
			catch (ClassNotFoundException e)
				{
					int i = pkgname.lastIndexOf('.');
		
				    if (i != -1)
						info = getPackageVersion(pkgname.substring(0,i));
				}
			catch (Throwable e)
				{					
				}
				
			return info;
	    }

	/**
	 *	Retrieves the full dot-separated version number (major, minor, build number, build increment) of the package
	 *	
	 *	@param	pkgname	Name of package to retrieve version information
	 *	@returns	A string which holds the version information
	 */
	static public String getPackageVersionFull(String packageName)
		{
			Properties prop = AFCVersionManager.getPackageVersion(packageName);

			if (prop == null)
				{
					return null;
				}

			return	(String)prop.get("MajorVersion")+"."+
					(String)prop.get("MinorVersion");					
		}
	
	/**
	 *	Retrieves the major version number of the package.
	 *	
	 *	@param	pkgname	Name of package to retrieve version information
	 *	@returns	The major version number of the package
	 */
	static public int getPackageVersionMajor(String packageName)
		{
			Properties prop = getPackageVersion(packageName);
			
			if (prop == null)
				{
					return -1;
				}

			return Integer.parseInt((String)prop.get("MajorVersion"));
		}

	/**
	 *	Retrieves the minor version number of the package.
	 *	
	 *	@param	pkgname	Name of package to retrieve version information
	 *	@returns	The minor version number of the package
	 */	
	static public int getPackageVersionMinor(String packageName)
		{
			Properties prop = getPackageVersion(packageName);

			if (prop == null)
				{
					return -1;
				}

			return Integer.parseInt((String)prop.get("MinorVersion"));
		}
		
	/**
	 *	Retrieves the version description string from package.
	 *	
	 *	@param	pkgname	Name of package to retrieve version information
	 *	@returns	The description string of the package
	 */		
	
	static public String getPackageVersionDescription(String packageName)
		{
			Properties prop = getPackageVersion(packageName);

			if (prop == null)
				{
					return null;
				}

			return (String)prop.get("Description");
		}	
}	



