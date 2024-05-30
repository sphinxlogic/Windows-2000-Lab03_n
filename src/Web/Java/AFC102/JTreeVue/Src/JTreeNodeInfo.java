//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.io.StreamTokenizer;
import java.io.IOException;

public class JTreeNodeInfo implements JTreeConsts
{ 
	public String name;
	public int type;
	public String pkg;

	private static int prevtype;

	public JTreeNodeInfo(String name)
	{
		this.name = name;
	}

	//
	// line from html will have following format:
	//    <li> class thepkg.subpkg.<a href="thepkg.subpkg.theclass#tag">TheClass</a>
	//
	//    will also be called for extends/implements
	//
	public JTreeNodeInfo(StreamTokenizer tokstrm)
	{
		// On entry tokstrm.nextToken is token after closing bracket of <li>
		try {
			if ( tokstrm.nextToken() == StreamTokenizer.TT_WORD ) {
				if ( tokstrm.sval.equalsIgnoreCase("class") )
					type = HTI_CLS;
				else if ( tokstrm.sval.equalsIgnoreCase("interface") )
					type = HTI_IFACE;
				else if ( tokstrm.sval.equalsIgnoreCase("extends") ||
						  tokstrm.sval.equalsIgnoreCase("implements") )
				{
					if ( tokstrm.sval.equalsIgnoreCase("implements") )
						// if it implements it must be a class
						type = HTI_CLS;
					else 
						// if it extends it must be an interface (which b.t.w.
						//  can extend more than one interface).
						type = HTI_IFACE;

					prevtype = type;

					// Skip over pkg
					if ( tokstrm.nextToken() != StreamTokenizer.TT_WORD )
						return; // Let's get out of here

					fillInfo(tokstrm);
					return; // Normal return
				}
				else 
					return; // Let's get out of here

				if ( tokstrm.nextToken() == StreamTokenizer.TT_WORD )
					pkg = tokstrm.sval;
					// FALL OUT OF IF out to fillInfo()	call
				else 
					return; // Let's get out of here
			}
			else if ( tokstrm.ttype == ',' ) {
				if ( tokstrm.nextToken() == StreamTokenizer.TT_WORD ) {
					// found pkg
					type = prevtype;
					fillInfo(tokstrm);
					return; // Normal return;
				}
				else {
					tokstrm.pushBack();
					return; // Let's get out of here
				}
			}
			else return; // Let's get out of here

			fillInfo(tokstrm);
		} catch (Exception e) {}
	}

	private void fillInfo(StreamTokenizer tokstrm)
	{
		try {
			// tokstrm.nextToken() will be beginning of anchor ("<a")upon entry; 
			//  look for closing brace '>', name will be right after
			while ( tokstrm.nextToken() != '>' ) 
				;
			// Extract name - This is the text part of the anchor that is underlined
			if ( tokstrm.nextToken() == StreamTokenizer.TT_WORD )
				name = tokstrm.sval;

			// Skip over '</a>'
			tokstrm.nextToken(); tokstrm.nextToken(); tokstrm.nextToken();
		} catch ( IOException e ) { e.printStackTrace(); }
	}
}
