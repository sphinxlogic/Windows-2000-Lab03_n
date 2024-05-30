//--------------------------------------------------------------------
// Microsoft OLE DB Sample OLEDB Simple Provider
// (C) Copyright 1997-8 Microsoft Corporation.  All Rights Reserved.
//
// module MyDataSource.java | msDataSourceObject implementation
//
//


////////////////////////////////////////////////////////
// Imports
//
////////////////////////////////////////////////////////
import java.util.*;
import com.ms.com.*;
import com.ms.osp.*;


////////////////////////////////////////////////////////
// MyDataSource
//
////////////////////////////////////////////////////////
/**
 * @com.register ( clsid=81C75D38-790A-11D2-8A61-0060088F441E, typelib=81C75D37-790A-11D2-8A61-0060088F441E )
 */
class MyDataSource implements DataSource
{
	// data
	String		m_sDataMember;	// Simple provider sample file name
	Vector		m_vListeners;	// List of DataSourceListeners
	MyOSPObject m_rOSPObject;	// Reference to the Simple Provider object
	
	//constructors
	public MyDataSource()
	{
		// Reference a new simple provider object:
		m_sDataMember = new String("Unitialized Sample");
		m_vListeners = new Vector();
		m_rOSPObject = new MyOSPObject();
	}

	/////////////////////////////////////////////////////////////////////////
	// DataSourceObject methods
	//
	/////////////////////////////////////////////////////////////////////////

	public IUnknown getDataMember(String sDataMember, _Guid riid) throws ComException
	{
		if (sDataMember == null)
			throw new ComFailException();

		// The DataMember string contains the file name.  Use it to prompt the
		// OSPObject to load its data.  Return the OSP Object:
		m_sDataMember = new String(sDataMember);
		m_rOSPObject.setFile(sDataMember);
		m_rOSPObject.loadData();
		return m_rOSPObject;
	}

	public String getDataMemberName(int lIndex)
	{
		if (lIndex != 0)
			throw new ComFailException();
		return new String(m_sDataMember);
	}

	public int getDataMemberCount()
	{
		// This sample DataSource has only one data member:
		return 1;
	}
		
	public void addDataSourceListener(DataSourceListener rDataSourceListener) throws ComException
	{
		if (rDataSourceListener == null)
			throw new ComFailException();

		// Add the listener:
		m_vListeners.addElement(rDataSourceListener);
	}

	public void removeDataSourceListener(DataSourceListener rDataSourceListener) throws ComException
	{
		if (rDataSourceListener == null)
			throw new ComFailException();

		// Find the Listener in the list and remove it:
		m_vListeners.removeElement(rDataSourceListener);
	}

	public static void main(String args[])
	{
		// Test code:
		MyDataSource dso = new MyDataSource();
		MyOSPObject osp = (MyOSPObject)dso.getDataMember("C:\\Customer.txt", OLEDBSimpleProvider.iid);
		System.out.println("Data Member = " + dso.getDataMemberName(0) + ".");
		int cRows = osp.getRowCount();
		int cColumns = osp.getColumnCount();
		System.out.println("Row count = " + cRows + ".");
		System.out.println("Column count = " + cColumns + ".");
	}
};

