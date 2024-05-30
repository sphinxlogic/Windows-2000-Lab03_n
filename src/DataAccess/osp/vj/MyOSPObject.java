//--------------------------------------------------------------------
// Microsoft OLE DB Sample OLEDB Simple Provider
// (C) Copyright 1997-8 Microsoft Corporation.  All Rights Reserved.
//
// module MyOSPObject.java | OLEDBSimpleProvider implementation
//
// Notes:
//
// 0.  For latest COM interfaces, install the Microsoft SDK for Java(tm)
//     2.0.
//
// 1.  For Java the function definitions are different than for C++.
//     Since there are no pointers, what would be the output argument
//     is the return value.


////////////////////////////////////////////////////////
// Imports
//
////////////////////////////////////////////////////////
import java.io.*;
import java.util.*;
import com.ms.com.*;
import com.ms.osp.*;


class MyOSPObject implements OLEDBSimpleProvider
{
	// data
	int				m_cRows;
	int				m_cColumns;
	String			m_sFilePath;
	Vector			m_vListeners;
	String[][]		m_rsTable;

	//constructors
	public MyOSPObject()
	{
		// The file name is not set until the DataSource object
		// does it:
		m_sFilePath		= null;
		m_cRows			= 0;
		m_cColumns		= 0;
		m_vListeners	= new Vector();
	}

	// Ancillary methods for loading and saving simple data

	public void setFile(String sFilePath)
	{
		m_sFilePath = sFilePath;
	}

	public void loadData()
	{
		int				i = 0, j = 0, iStart, iEnd;
		BufferedReader	rdr;
		FileReader		frdr;
		Integer			iToken;
		String			s, t;
		StringTokenizer	st;
		
		// Build the internal array by reading the file:
		try 
		{
			frdr = new FileReader(m_sFilePath);
			rdr = new BufferedReader(frdr);

			// Line 1 contains cRows ; cColumns
			s = new String(rdr.readLine());
			st = new StringTokenizer(s, ";");
			iToken = new Integer(st.nextToken());
			m_cRows = iToken.intValue();
			iToken = new Integer(st.nextToken());
			m_cColumns = iToken.intValue();

			// Create arrary of size cRows+1 X cColumns+1:
			m_rsTable = new String[m_cRows+1][m_cColumns+1];

			// Read the rest of the file and stuff each line into the next row:
			for (i = 0; i <= m_cRows; i++)
			{
				m_rsTable[i][0] = new String("");
				s = new String(rdr.readLine());
				iStart = 0;
				iEnd = s.indexOf(';');
				j = 1;
				while (iEnd != -1 & j <= m_cColumns)
				{
					t = new String(s.substring(0, iEnd));
					s = new String(s.substring(iEnd+1));
					iEnd = s.indexOf(';');
					//System.out.println("[j = " + j + "]: " + t);
					m_rsTable[i][j] = t;
					j++;
				}
				if (s != "" & j <= m_cColumns)
				{
					m_rsTable[i][j] = s;
					j++;
				}
			}
			rdr.close();
			frdr.close();
		}
		catch(NullPointerException npe)
		{
		}
		catch(Exception e)
		{
			System.out.println(e.toString() + "\n");
			throw new ComFailException();
		}
		return;
	}

	public void saveData()
	{
		int				i = 0, j = 0;
		BufferedWriter	bwtr = null;
		FileWriter		fwtr = null;
		PrintWriter		pwtr = null;

		try
		{
			// Prepare the file for output:
			fwtr = new FileWriter(m_sFilePath);
			bwtr = new BufferedWriter(fwtr);
			pwtr = new PrintWriter(bwtr);

			// Write out the first line
			pwtr.println(m_cRows + ";" + m_cColumns);

			// Write the columns of each row on a line:
			for (i = 0; i <= m_cRows; i++)
			{
				for (j = 1; j <= m_cColumns; j++)
				{
					if (m_rsTable[i][j].equals(""))
						pwtr.print(';');
					else
					    pwtr.print(m_rsTable[i][j] + ';');
				}
				pwtr.println();
			}

			// Close the Writers:
			pwtr.close();
		}
		catch(Exception e)
		{
			pwtr.close();
			System.out.println("Error in saveData() when i = " + i + ", j = " + j);
			System.out.println(e.toString() + "\n");
			throw new ComFailException();
		}
	}

	public boolean compareString(String s1, String s2, boolean fCaseSensitive, int findFlags)
	{
		if (fCaseSensitive)
		{
			switch (findFlags)
			{
			case OSPCOMP.OSPCOMP_EQ:
				return s1.equals(s2);
			case OSPCOMP.OSPCOMP_LT:
				return (s1.compareTo(s2) < 0) ? true : false;
			case OSPCOMP.OSPCOMP_LE:
				return (s1.compareTo(s2) <= 0) ? true : false;
			case OSPCOMP.OSPCOMP_GE:
				return (s1.compareTo(s2) >= 0) ? true : false;
			case OSPCOMP.OSPCOMP_GT:
				return (s1.compareTo(s2) > 0) ? true : false;
			};
		}
		else
		{
			if (findFlags == OSPCOMP.OSPCOMP_EQ)
				return s1.equalsIgnoreCase(s2);
			else
			{
				String ls1 = new String(s1.toLowerCase());
				String ls2 = new String(s2.toLowerCase());
				switch (findFlags)
				{
				case OSPCOMP.OSPCOMP_LT:
					return (ls1.compareTo(ls2) < 0) ? true : false;
				case OSPCOMP.OSPCOMP_LE:
					return (ls1.compareTo(ls2) <= 0) ? true : false;
				case OSPCOMP.OSPCOMP_GE:
					return (ls1.compareTo(ls2) >= 0) ? true : false;
				case OSPCOMP.OSPCOMP_GT:
					return (ls1.compareTo(ls2) > 0) ? true : false;
				};
			}
		}
		return false;
	}

	// OLEDBSimpleProvider methods

	public int deleteRows(int iRow, int cRows) throws ComException
	{
		if (iRow <= 0)
			throw new ComFailException();

		if (cRows < 1)
			throw new ComFailException();

		if (iRow > m_cRows)
			throw new ComFailException();

		// Adjust row count to stay within range:
		if (iRow + cRows > m_cRows + 1)
			cRows = m_cRows - iRow + 1;

		// Create new array with reduced rows; copy over remaining rows:
		int cNewRows = m_cRows - cRows;
		String[][] rsNewTable = new String[cNewRows+1][m_cColumns+1];
		int i, j, k = 0;
		for (i = 0; i <= m_cRows; i++)
		{
			if (i < iRow || i > (iRow + cRows - 1))
			{
				for (j = 1; j <= m_cColumns; j++)
					rsNewTable[k][j] = m_rsTable[i][j];
				k++;
			}
		}

		//  Refer to new table and adjust row count:
		for (Enumeration e = m_vListeners.elements(); e.hasMoreElements(); )
			((OLEDBSimpleProviderListener)e.nextElement()).aboutToDeleteRows(iRow, cRows);
		m_rsTable = rsNewTable;
		m_cRows = cNewRows;
		saveData();
		for (Enumeration e = m_vListeners.elements(); e.hasMoreElements(); )
			((OLEDBSimpleProviderListener)e.nextElement()).deletedRows(iRow, cRows);

		// Return the count of rows deleted:
		return cRows;
	}

	public int getColumnCount() throws ComException
	{
		return m_cColumns;
	}

	public String getLocale() throws ComException
	{
		Locale lc = Locale.US;
		return lc.getDisplayName(Locale.US);
	}

	public int getRowCount() throws ComException
	{
		return m_cRows;
	}

	public int getRWStatus(int iRow, int iColumn) throws ComException
	{
		if (iColumn == 1)
			return OSPRW.OSPRW_READONLY;
		else
			return OSPRW.OSPRW_READWRITE;
	}

	public Object getVariant(int iRow, int iColumn, int format) throws ComException
	{
		if (iRow < 0 || iColumn < 0 || iRow > m_cRows || iColumn > m_cColumns)
			throw new ComFailException();
		// Allocate a new object because the caller will free it when it wants
		// to:
		String s = new String(m_rsTable[iRow][iColumn]);
		return s;
	}

	public void setVariant(int iRow, int iColumn, int format, Object obj) throws ComException
	{
		if (iRow < 0 || iColumn < 0)
			throw new ComFailException();
		for (Enumeration e = m_vListeners.elements(); e.hasMoreElements(); )
			((OLEDBSimpleProviderListener)e.nextElement()).aboutToChangeCell(iRow, iColumn);
		m_rsTable[iRow][iColumn] = (String)obj;
		saveData();
		for (Enumeration e = m_vListeners.elements(); e.hasMoreElements(); )
			((OLEDBSimpleProviderListener)e.nextElement()).cellChanged(iRow, iColumn);
	}

	public int insertRows(int iRow, int cRows) throws ComException
	{
		//  Do not handle label or wildcard rows:
		if (iRow <= 0)
			throw new ComFailException();

		//  Count of rows to insert must be more than 0:
		if (cRows <= 0)
			throw new ComFailException();

		//  If called to insert after the end, adjust to insert at the end:
		if (iRow > m_cRows)
			iRow = m_cRows + 1;

		//  Create new array with additional rows:
		int cNewRows = m_cRows + cRows;
		String[][] rsNewTable = new String[cNewRows+1][m_cColumns+1];
		int i, j, k = 0;
		for (i = 0; i <= cNewRows; i++)
		{
			if (i < iRow || i > (iRow + cRows - 1))
			{
				for (j = 1; j <= m_cColumns; j++)
					rsNewTable[i][j] = m_rsTable[k][j];
				k++;
			}
			else
			{
				for (j = 1; j <= m_cColumns; j++)
				{
					rsNewTable[i][j] = new String("");
				}
			}
		}

		//  Refer to new table and adjust row count:
		for (Enumeration e = m_vListeners.elements(); e.hasMoreElements(); )
			((OLEDBSimpleProviderListener)e.nextElement()).aboutToInsertRows(iRow, cRows);
		m_rsTable = rsNewTable;
		m_cRows = cNewRows;
		saveData();
		for (Enumeration e = m_vListeners.elements(); e.hasMoreElements(); )
			((OLEDBSimpleProviderListener)e.nextElement()).insertedRows(iRow, cRows);

		// Return the count of rows inserted::
		return cRows;
	}

	public int find(int iRowStart, int iColumn, Object obj, int findFlags, int compType) throws ComException
	{
		// Check arguments:
		if (iRowStart <= 0 || iRowStart > m_cRows)
			throw new ComFailException();
		if (iColumn <= 0 || iColumn > m_cColumns)
			throw new ComFailException();

		// Determine search order:
		int		iRowStop = (findFlags == OSPFIND.OSPFIND_UP) ? 0 : m_cRows+1;
		boolean	fCaseSensitive = (compType == OSPFIND.OSPFIND_CASESENSITIVE);
		
		// Linear search through all rows:
		while (iRowStart != iRowStop)
		{
			if (compareString(m_rsTable[iRowStart][iColumn], (String)obj, fCaseSensitive, findFlags))
				return iRowStart;

			if(findFlags == OSPFIND.OSPFIND_UP)
				iRowStart--;
			else
				iRowStart++;
		}

		return 0;
	}

	public void addOLEDBSimpleProviderListener(OLEDBSimpleProviderListener rListener) throws ComException
	{
		// Add a listener:
		m_vListeners.addElement(rListener);
		return;
	}

	public void removeOLEDBSimpleProviderListener(OLEDBSimpleProviderListener rListener) throws ComException
	{
		// Remove a listener:
		m_vListeners.removeElement(rListener);
		return;
	}

	public int isAsync() throws ComException
	{
		// This function should return TRUE or FALSE.  But the interface definition
		// converts it to "int".  Return the equivalent of 'FALSE":
		return 0;
	}

	public int getEstimatedRows() throws ComException
	{
		return getRowCount();
	}

	public void stopTransfer() throws ComException
	{
		// Do nothing in this simple example.
		return;
	}

	public static void main(String args[])
	{
		// Test code:
		MyOSPObject osp = new MyOSPObject();
		System.out.println("Locale = " + osp.getLocale());
		osp.m_sFilePath = new String("C:\\Customer.txt");
		osp.loadData();
		osp.m_sFilePath = new String("C:\\Savedata.txt");
		Variant var;
		int i = 70, j = 3;
		var = (Variant)osp.getVariant(i, j, 0);
		System.out.println("Column[" + j + "] = {" + var.getString() + "}");
		//osp.deleteRows(1, 1);
		osp.insertRows(89, 1);
		var = null;
		var = (Variant)osp.getVariant(i, j, 0);
		System.out.println("Column[" + j + "] = {" + var.getString() + "}");
		//osp.saveData();
	}
}