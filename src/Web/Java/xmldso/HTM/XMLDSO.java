package com.ms.xml.dso;

import java.util.*;
import java.applet.*;
import java.awt.*;
import java.net.*;
import java.io.*;

import netscape.javascript.JSObject;
import com.ms.osp.*;
import com.ms.xml.parser.*;
import com.ms.xml.om.*;
import com.ms.xml.util.Name;
import com.ms.xml.util.XMLOutputStream;
import com.ms.xml.util.Attribute;

/**
 * An XMLDSO is an applet that can be used in an APPLET tag to
 * load XML files and provide that data to for data binding.
 * See IE 4.0 documentation for more information on data binding.
 *
 * @version 1.0, 8/14/97
 * @see Document
 * @see Element
 */
public class XMLDSO extends Applet
{
    /**
     * Construct a new XMLDSO object with an empty document.
     */
    public XMLDSO()
    {
        document = new Document(); 
        inlineXML = false;
    }

    /**
     * The init method looks for a URL PARAM and loads this
     * url if specified.  Otherwise it looks for inline XML 
     * from inside the APPLET tag that created this XMLDSO
     * object.  It does this using the ID parameter of the 
     * APPLET tag to lookup the actual applet object in 
     * the page, using JSObject, an then getting the altHtml 
     * member of this object.   Note: it is ok to not have
     * a URL or any inline XML.
     */
    public void init()
    {   
        super.init();
        String arg = getParameter("URL");
        if (arg != null && arg.length() > 0) {
            load(arg);
        }
		else
		{
            // Or we can get the XML data inline from inside the
            // <APPLET> tag using the JavaScript object model.
			arg = getParameter("ID");
			if (arg != null && arg.length() > 0) 
            {
                JSObject appl = null;
                try {
    			    appl = (JSObject)((JSObject)JSObject.getWindow(this).getMember("document")).getMember(arg);
                } catch (Exception e) {
                    setError("Error finding <APPLET> with ID=" + arg + ": " + e.toString());
                    return;
                }
				if (appl != null)
				{
					String data = (String)appl.getMember("altHtml");
					if (data != null && data.length() > 0)
					{
						try {
							document.load(new StringBufferInputStream(data));
                            inlineXML = true;
						} catch (Exception e) {
							setError("Error parsing inline XML: " + e.toString());
							document = null;
						}
					}
				}
				else
				{
                    setError("Error finding <APPLET> with ID=" + arg);
				}
            } else {
                setError("Your applet must have a <PARAM NAME=\"APPLET\" VALUE=\"xmldso\">" +
                         " where the value matches the ID of your APPLET tag.");
            }
		}
        updateSchema();
    }

    /**
     * This method is called whenever the document is changed,
     * that is, from the load and setroot methods.  You can
     * also call this method if you have manually changed the 
     * document or the SCHEMA <PARAM>.
     */
    public void updateSchema()
    {
        schema = new Document();
        // the SCHEMA <PARAM> is used to define a subset of data
        // that is visible through the DSO.  This method can be
        // called to update the schema when the PARAM is changed
        // programatically or the document has changed through
        // scripting and the schema needs to be updated.
        String arg = getParameter("SCHEMA");
        if (arg != null && arg.length() > 0) {
            try {
                schema.load(new StringBufferInputStream(arg));
				schemaRoot = schema.getRoot();
            } catch (Exception e) {
                setError(e.toString());
                schema = null;
            }
        } else {
			// Generate schema from the data.
			if (document != null && document.getRoot() != null)
			{
				Element root = document.getRoot();
                SchemaNode n = new SchemaNode(schema, schema, root.getTagName());
				generateSchema(root, n);
				// remember only first entry below root
				ElementEnumeration iter = new ElementEnumeration(schema.getRoot(), 
                    XMLRowsetProvider.nameROWSET,Element.ELEMENT);	
				schemaRoot = (Element)iter.nextElement();
			}
        }
        notifyListeners();        
    }

    /**
     * Function to provide the OLE-DB simple provider interface to callers.
     * The qualifier parameter is ignored at this point, but is available
     * to allow the applet to serve up more than one data set
     */
    public OLEDBSimpleProvider msDataSourceObject(String qualifier)
    {
        if (document != null && document.getRoot() != null && schemaRoot != null) {          
            // This is a smarter provider that supports a hierarchy
            // of XMLRowsetProviders based on the given schema information.
            myProvider = new XMLRowsetProvider (document.getRoot(), schemaRoot, null);
        } else {
            myProvider = null;
        }
        return myProvider;
    }

    /**
     * This is a standard method for DSO's.
     */
    public void addDataSourceListener(DataSourceListener  listener)
        throws java.util.TooManyListenersException
    {
        if (myDSL != null)
            com.ms.com.ComLib.release(myDSL);
        
        myDSL = listener;
    }

    /**
     * This is a standard method for DSO's.
     */
    public void removeDataSourceListener( DataSourceListener   listener)
    {
        // BUGBUG: Shouldn't have to call release here. This is a
        //         bug in the VM implementation.

        com.ms.com.ComLib.release(myDSL);
        myDSL = null;
    }

    /**
     * Notify current DataSouceListener that data has changed.
     */
    public void notifyListeners()
    {
        if (myDSL != null)
            myDSL.dataMemberChanged("");
    }

    /**
     * Return the loaded document.
     */
	public Object getDocument()
	{
		// return document to allow scripting
		return document;
	}

    /**
     * This method is called to set the root of the document
     * for this XMLDSO object.  This is useful when you want to
     * link multiple DSO's together.
     */
    public void setRoot(Element e)
    {
        document = new Document();
        document.addChild(e,null);
        updateSchema();
    }

    public void clear()
    {
        document = new Document();
        updateSchema();
    }

    /**
     * Reload the document using the given URL.  Relative URL's
     * are resolved using the HTML document as a base URL.
     */
    public void load(String arg)
    {
        // Resolve this URL using the Document's URL as the base URL.
        URL base = getDocumentBase();

        // We can get the XML data from a remote URL
        try {
            if (base == null) {
                url = new URL(arg);
            } else {
                url = new URL(base,arg);
            }
            document.load(url);
        } catch (Exception e) {
            setError("Error loading XML document '" + arg + "'.  " + e.toString());            
        }
        if (schema != null) {
            updateSchema();
        }
    }

    /**
     * Return the XML for the loaded document as a big string.
     */
    public Object getXML()
	{
		// return XML as long string
        if (document != null) 
        {
            ByteArrayOutputStream out = new ByteArrayOutputStream();
            try {
                document.save(new XMLOutputStream(out));
            } catch (Exception e) {
                setError(e.toString());
            }
            return out.toString();
        }
        return null;
	}

    /**
     * Return string containing last error encountered by the XMLDSO.
     */
    public String getError()
    {
        return error;
    }

    /**
     * Save the schema to the given file.
     */
	public void saveSchema(String filename)
    {
        if (schema != null)
        {
            try
            {
                FileOutputStream out = new FileOutputStream(filename);
                schema.save(new XMLOutputStream(out));
            }
            catch(Exception e)
            {
                setError(e.toString());
            }
        }
    }

    /**
     * Return the schema as a string.
     */
    public Object getSchema()
	{
		// return Schema as long string
        if (schema != null) 
        {
            ByteArrayOutputStream out = new ByteArrayOutputStream();
            try {
                schema.save(new XMLOutputStream(out));
            } catch (Exception e) {
                setError(e.toString());
            }
            return out.toString();
        }
        return null;
	}

    /**
     * Save the XML document to the given file.
     */
	public void save(String filename)
    {
        if (document != null)
        {
            try
            {
                FileOutputStream out = new FileOutputStream(filename);
                document.save(document.createOutputStream(out));
            }
            catch(Exception e)
            {
                setError(e.toString());
            }
        }
    }

    private void setError(String e)
    {
        error = e;
        repaint();
    }

	void generateSchema(Element source, SchemaNode n)
	{
//        System.out.println("Processing node:" + source.getTagName());
		// go thru the children of source and generate schema
		// nodes added later to parent.
		for (ElementEnumeration en = new ElementEnumeration(source); en.hasMoreElements(); )
		{
			Element e = (Element)en.nextElement();
			int t = e.getType();
            Name name = e.getTagName();
//            System.out.println("Found: " + name + "," + t);
			if (t == Element.ELEMENT)
			{
                // now we know that parent is a rowset...
                SchemaNode sn = n.setRow(name);
                generateSchema(e, sn);
			}
		}

        // if children didn't create element it means it is a column...
        // (at least for now.  If we find that it is supposed to be
        // a ROWSET later in the document, then setRow() will fix it up).
        if (n.e == null)
        {
            n.createElement(false);
        }
	}

    /**
     * When the APPLET containing this XMLDSO is given a non-zero bounds
     * this paint methods displays diagnostic information that helps the
     * page author debug the page.
     */
    public void paint(Graphics g)
    {
        Dimension d = size();
        if (d.width > 0 && d.height > 0)
        {
            if (error == null) {
                g.setColor(Color.green);
            } else {
                g.setColor(Color.red);
            }
            g.fillRect(0,0,d.width,d.height);
            String text = error;
            if (text == null) {
                if (url != null) {
                    text = "Successfully loaded XML from \"" + url.toString() + "\"";
                } else if (inlineXML) {
                    text = "Successfully loaded inline XML";
                } else if (document.getRoot() != null) {
                    text = "Successfully loaded document.";
                } else {
                    text = "Empty";
                }
            }
            g.setColor(Color.black);
            drawText(g,text,5,5,d.width-10,true,0);
        }
    }

    /**
     * Draw a text string within the given bounds.
     */
    private int drawText(Graphics g, String text, int x, int y, int max, 
                        boolean skipWhiteSpace, int length)
    {
        if( text == null || text.length() == 0 )
            return y;
        if (max < 5) // make sure we have room to draw text.
            return y;
        int i = 0;
        int len;
        int w = 0;

        if( length == 0 )
            len = text.length();
        else
            len = length;
        
        // skip leading white space.
        while (i < len && skipWhiteSpace && isWhiteSpace(text.charAt(i)))
            i++;
        
        FontMetrics fm = g.getFontMetrics();
        int j = i;
        int k = i;
        while (i < len) {
            char ch = text.charAt(i);
            int cw = fm.charWidth(ch);
            w += cw;
            if (w > max || ch == '\n') {
                if( ch == '\n' && text.charAt(i-1) == 0x0D )
                    j = i-1;
                else if (k == j)
                    j = i;
                String sub = text.substring(k,j);
                g.drawString(sub,x,y+fm.getMaxAscent());
                y += fm.getHeight();
                // skip white space.
                if( ch == '\n' && text.charAt(i-1) == 0x0D )
                    j = i+1;
                while (skipWhiteSpace && j < len && isWhiteSpace(text.charAt(j)))
                    j++;
                i = j;
                k = j;
                w = 0;
            } else {
                if (skipWhiteSpace && isWhiteSpace(ch)) {
                    j = i;
                }
                i++;
            }
        }
        String remaining = text.substring(k);
        g.drawString(remaining,x,y+fm.getMaxAscent());
        return y;
    }

    private boolean isWhiteSpace(char ch)
    {
        return Character.isSpace(ch) || ch == 13;
    }

    private OLEDBSimpleProvider  myProvider;
    private DataSourceListener myDSL;
    private Document           document;
    private Document           schema;
	private Element				schemaRoot;
    private String              error;
    private URL                 url;
    private boolean             inlineXML;
}

class SchemaNode
{
    Element e;
    Hashtable rows;
    Name name;
    Element parent;
    ElementFactory factory;

    SchemaNode(Element parent, ElementFactory factory, Name name)
    {
        this.parent = parent;
        this.name = name;
        this.factory = factory;
    }

    void createElement(boolean rowset)
    {
        if (rowset)
        {
            e = factory.createElement(Element.ELEMENT, XMLRowsetProvider.nameROWSET);
        }
        else
        {
            e = factory.createElement(Element.ELEMENT, XMLRowsetProvider.nameCOLUMN);
        }
        parent.addChild(e, null);
        e.setAttribute(XMLRowsetProvider.nameNAME, name.toString());
    }

    SchemaNode setRow(Name name)
    {
        if (e == null)
        {
            createElement(true);
        } 
        else if (e.getTagName() != XMLRowsetProvider.nameROWSET) 
        {
            // We have now discovered that node is supposed to
            // be a ROWSET not a COLUMN.
            parent.removeChild(e);
            createElement(true);
        }

        SchemaNode sn = getRow(name);
        // add new subnode if new or was added as text
        if (sn == null)
        {
            sn = new SchemaNode(e, factory, name);
            addRow(name, sn);
        }
        return sn;
    }

    void addRow(Name name, SchemaNode n)
    {
        if (rows == null) 
            rows = new Hashtable(13);
        rows.put(name, n);
    }

    SchemaNode getRow(Name n)
    {
        if (rows == null)
            return null;
        return (SchemaNode)rows.get(n);
    }
}

//------------------------------------------------------------------
class XMLRowsetProvider  implements OLEDBSimpleProvider  
{    
    public XMLRowsetProvider (Element e, Element schema, XMLRowsetProvider parent)
    {
        root = e;
        this.schema = schema;
        this.parent = parent;
        // This provider iterates over nodes in root that match
        // ROWSET name defined in schema.
        rowset = Name.create((String)schema.getAttribute(nameNAME));
        iter = new ElementEnumeration(root,rowset,Element.ELEMENT);
        row = (Element)iter.nextElement();
        rowindex = 0;
    }

    public int getRowCount() 
    {
        // Return number of children in root that match the
        // ROWSET name.
        int result = 0;
        iter.reset();
        while (iter.nextElement() != null)
            result++;
        iter.reset();
        row = (Element)iter.nextElement();
        rowindex = 0;
        return result;
    }

    public int getEstimatedRows() 
    {
        return getRowCount();
    }

    public int getColumnCount() 
    {
        // Simply return the number of elements in the schema.
        int columns = schema.numElements();
        return columns;
    }

    public int getRWStatus(int iRow,int iColumn) 
    {
        return 1;
    }

    public void addOLEDBSimpleProviderListener(OLEDBSimpleProviderListener l)
    {
    }

    public void removeOLEDBSimpleProviderListener(OLEDBSimpleProviderListener l)
    {
    }

    public int find(int iStartRow, int iColumn, Object varSearchVal,
                    int findFlags, int compType)
    {
        return 0;
    }

    public int deleteRows(int iRow,int cRows)
    {
        return 0;
    }

    public int insertRows(int iRow,int cRows)
    {
        return 0;
    }

    public Object getVariant(int iRow, int iColumn,int formatType )  
    {
        Object retVal = null;
        if (iRow == 0)
        {
            // return the column information.
            if (iColumn <= getColumnCount()) {
                Element e = schema.getChild(iColumn-1);
                String name = (String)e.getAttribute(nameNAME);
                if (name != null) {
					if (e.getTagName() != nameCOLUMN) {
						// HACK to mark the column as rowset for the OSP...
						retVal = "^" + name + "^";
					} else {
						retVal = name;
					}
                }
            }
        }
        else
        {
            getRow(iRow); // update current row.
            retVal = getColumn(row,iColumn-1);
        }
//		System.out.println(rowset + " " + iRow + " " + iColumn + " " + retVal);
        return retVal;
    }

    Element getRow(int iRow)
    {
        // The current row is cached for performance reasons.
        if (rowindex != iRow - 1) {
            if (rowindex == iRow - 2) {
                // next row in sequence.
                rowindex++;
                row = (Element)iter.nextElement();
            } else {
                // caller just did a random jump, so we need to resync
                // the iterator.
                iter.reset();
                row = (Element)iter.nextElement();
                rowindex = 0;
                for (int i = 0; i < iRow - 1; i++) {
                    row = (Element)iter.nextElement();
                    rowindex++;
                }
            }
        }
        return row;
    }

    public Object getColumn(Element row, int col)
    {
        Element se = schema.getChild(col);
        Name name = Name.create((String)se.getAttribute(nameNAME));  
        if (se.getTagName() == nameCOLUMN) {
            Element child = findChild(row,name);
            if (child != null) {
                String text = child.getText();
                return text;
            }
            return null;
        } else {
            // Must be a rowset, so return a rowset provider.
            XMLRowsetProvider value = (XMLRowsetProvider)row.getAttribute(nameOSP);
            if (value == null) {
                // Time to create a new one.
                value = new XMLRowsetProvider(row,se,this);
                row.setAttribute(nameOSP,value);
            }
            return value;
        }
    }

    /**
     * Recurrsively search given row for first child or grand-child 
     * node with matching tag name.
     */
    public Element findChild(Element row, Name tag)
    {
        for (ElementEnumeration en = new ElementEnumeration(row);
                en.hasMoreElements(); )
        {
            Element child = (Element)en.nextElement();
            if (child.getType() == Element.ELEMENT && child.getTagName() == tag) {
                return child;
            } else if (child.numElements() > 0) {
			    child = findChild(child,tag);
			    if (child != null)
				    return child;
		    }
        }
        return null;
    }

    public void setVariant(int iRow,int iColumn, int formatType, Object var) 
    {
        getRow(iRow); // update current row.
        Element se = schema.getChild(iColumn-1);
        if (se.getTagName() == nameCOLUMN) {
            String attr = (String)se.getAttribute(nameNAME);
            if (attr != null) 
            {
                Name name = Name.create(attr);
                Element child = findChild(row,name);
                if (child != null) {
                    if (child.numElements() == 1 &&
                        child.getChild(0).getType() == Element.PCDATA)
                    {
                        Element pcdata = child.getChild(0);
                        String text = (String)var;
                        pcdata.setText(text);
                    }
                    // otherwise ignore the setVariant !
                }
            }
        }
    }

    public String getLocale()
    {
        // nothing special here. Return the default locale, ie. US
        return "";
    }

    public int isAsync()
    {
        return 0;
    }

    public void stopTransfer()
    {
    }
    
    Element root;
    Element schema;
    Element row;
    ElementEnumeration iter;
    int     rowindex;
    Name    rowset;
    XMLRowsetProvider parent;

    static Name nameCOLUMN = Name.create("COLUMN");
    static Name nameROWSET = Name.create("ROWSET");
    static Name nameNAME = Name.create("NAME");
    static Name nameATTRIBUTE = Name.create("ATTRIBUTE");
    static Name nameVALUE = Name.create("VALUE");
    static Name nameOSP = Name.create("OSP");
}

