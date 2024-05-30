/**
 * Copyright (C) 1997 Microsoft Corporation
 *
 * Simple #define scanner.  Reads files of #defines and converts them into Java.
 * Handles most of them, although it can't process macros.  Output files are Java
 * interfaces broken down alphabetically.
 *
 * Currently Strings are left out - they require constructors to run.  That might
 * slow down our code.
 *
 * Note: You must look for unterminated C-style comments in #define files.  Run this
 * command over your def files and fix up any lines in the output:
 * grep \/\* *.def | grep -v \*\/
 *
 */

import java.io.*;
import java.util.*;

class symbol {
	public String name;
	public int type;
	public boolean isBool;
	public boolean isChar;
	public boolean isString;
	public boolean isInt;
	public boolean isLong;
	public boolean isDouble;
	public boolean isComplex;  // True if its something non-trivial, like (0x1|CONSTANT)
	public String text;
	public String undefined_tokens;

	public symbol()
	{
		name = null;
		text = null;
		undefined_tokens = null;
		isBool = false;
		isChar = false;
		isString = false;
		isInt = false;
		isLong = false;
		isDouble = false;
		isComplex = false;
	}

	public void setTypes(boolean isBool, boolean isInt, boolean isLong, boolean isDouble, boolean isChar, boolean isString, boolean isComplex)
	{
		this.isBool = isBool;
		this.isChar = isChar;
		this.isString = isString;
		this.isInt = isInt;
		this.isLong = isLong;
		this.isDouble = isDouble;
		this.isComplex = isComplex;
	}

	public void addTypes(boolean isBool, boolean isInt, boolean isLong, boolean isDouble, boolean isChar, boolean isString, boolean isComplex)
	{
		this.isBool = this.isBool | isBool;
		this.isChar = this.isChar | isChar;
		this.isString = this.isString | isString;
		this.isInt = this.isInt | isInt;
		this.isLong = this.isLong | isLong;
		this.isDouble = this.isDouble | isDouble;
		this.isComplex = this.isComplex | isComplex;
	}

	public void addUndefToken(String token)
	{
		if(undefined_tokens == null)
			undefined_tokens = token;
		else
			undefined_tokens = undefined_tokens + " " + token;
	}

	public boolean hasUndefinedTokens()
	{
		return undefined_tokens != null;
	}
}


class FileWrapper 
{
	public PrintWriter stream;
	public String name;
	public int numEntries;
	public boolean lastWasBool;
	public boolean lastWasInt;
	public boolean lastWasLong;
	public boolean lastWasDouble;
	public boolean lastWasString;
	public boolean lastWasChar;
	public boolean veryFirstLine;

	/**
	 * Pass in the relative path, using \\ to separate directories.
	 * @param path relative path of file
	 * @param name name of the file.
	 */
	public FileWrapper(String path, String name) throws IOException
	{
		this.name = name;
		if(path!=null && !path.endsWith("\\"))
			path = path+"\\";
		OutputStreamWriter osw = new OutputStreamWriter(new FileOutputStream(path+name));
		stream = new PrintWriter(osw, true);
		lastWasBool = false;
		lastWasInt = false;
		lastWasLong = false;
		lastWasDouble = false;
		lastWasString = false;
		lastWasChar = false;
		veryFirstLine = true;
		numEntries = 0;
	}

	public void finalizer()
	{
		stream.close();
		stream = null;
	}
}


public class defscan
{
	// Strings can be put in a separate interface.  May help performance a little, since 
	// you'd have to run constructors for all strings when you used the interfaces otherwise.
	private static final boolean SeparateStrings = true;

	// Change this location.  Sample value: "com\\ms\\win32"
	private static final String outputdir = "com\\ms\\win32";

	// Change this too, or set to null if you don't want this in a package
	// Sample value: "com.ms.win32"
	private static final String PackageName = "com.ms.win32";

	private PrintWriter out;
	private Hashtable Symbols;
	public int skippedMacros;
	public int skippedAliases;
	public int skippedSymbols;
	public int skippedNoValue;
	public int skippedRedefined;
	public int skippedStrings;
	public int skippedUnterminatedExpressions;
	public int skippedUnparsible;
	public int resolvedLater;
	public int unifiedSymbols;
	public int outputted;
	public int total;
	protected Vector Files;
	protected Vector UnrecognizedSymbols;

	// Magic numbers detailing place in Files vector for a global output and miscellaneous
	// output files.  DO NOT EDIT WITHOUT GOOD REASON UNLESS YOU KNOW WHAT YOU'RE DOING.
	// (such as you're adding numbers or upper&lower case interface files).
	// global_output is supposed to be the highest number and they should all be consecutive and start at 26.
	private static final int misc_output = 26;
	private static final int string_output = 27;
	private static final int global_output = 28;

	public defscan()
	{
		Symbols = new Hashtable();
		UnrecognizedSymbols = new Vector();
		skippedMacros = 0;
		skippedAliases = 0;
		skippedSymbols = 0;
		skippedNoValue = 0;
		skippedRedefined = 0;
		skippedStrings = 0;
		skippedUnterminatedExpressions = 0;
		skippedUnparsible = 0;
		resolvedLater = 0;
		unifiedSymbols = 0;
		outputted = 0;
		total = 0;
		SetupInterfaceFiles();
	}

	public void finalizer() {
		Symbols = null;
		CloseInterfaceFiles();
	}

	/**
	 * Create FileWrappers for all of the interface files.  Depends heavily on the magic
	 * numbers for global, misc, and string output from above.
	 * @return No return value.
	 */
	protected void SetupInterfaceFiles() {
		Files = new Vector(global_output+1);  // Use the magic number from above.
		// Files should hold files for A-Z, a miscellaneous file, and a global output.
		String path = outputdir;
		String packageString = null;
		if(PackageName!=null)
			packageString = "\r\npackage "+PackageName+";\r\n";
		try {
			for(char c = 'a'; c <= 'z'; c++) {
				FileWrapper f = new FileWrapper(path, "win"+c+".java");
				Files.addElement(f);
				if(packageString != null)
					f.stream.print(packageString);
				f.stream.print("\r\npublic interface win"+c+" {\r\n");
			}
			
			// Make a file for miscellaneous constants...
			FileWrapper f = new FileWrapper(path, "winmisc.java");
			Files.addElement(f);
			if(packageString != null)
				f.stream.print(packageString);
			f.stream.print("\r\npublic interface winmisc {\r\n");

			// Make a file for string constants...
			f = new FileWrapper(path, "winstrings.java");
			Files.addElement(f);
			if(packageString != null)
				f.stream.print(packageString);
			f.stream.print("\r\npublic interface winstrings {\r\n");

			// Add global file.  It should be the last one.
			f = new FileWrapper(path, "win.java");
			Files.addElement(f);
			if(packageString != null)
				f.stream.print(packageString);
			f.stream.print("\r\npublic interface win {\r\n");
		}
		catch (IOException e) {
			System.out.println(e);
			e.printStackTrace();
			Files = null;
		}
	}

	/**
	 * Close win*.java after writing out all terminating info necessary.
	 * @return No return value.
	 */
	protected void CloseInterfaceFiles() {
		if(Files == null)
			return;
		System.out.println("Closing files...");
		for(int i=0; i<Files.size(); i++) {
			//PrintStream s = (PrintStream) Files.elementAt(i);
			FileWrapper f = (FileWrapper) Files.elementAt(i);
			if(!f.veryFirstLine)
				f.stream.print(";\r\n");
			f.stream.print("\r\n}\r\n");
			//System.out.println(f.name+" contained "+f.numEntries+" constants.");
			f.finalizer();
			f = null;
		}
		Files = null;
	}

	/**
	 * Mainly useful if you scan the header files in the wrong order or if you have circular
	 * dependencies in your headers.  Resolves all unresolved symbols, or at least as much as
	 * it can.
	 */
	protected void HandleUnrecognizedSymbols() throws IOException {
		boolean converged = false;
		Vector removeList = new Vector();  // Remove from UnrecognizedSymbols at end of pass.
		int passes = 1;
		System.out.print("\n\nLooking up "+UnrecognizedSymbols.size()+" unrecognized symbols... ");
		do {
			removeList = new Vector();
			System.out.print("pass "+(passes++)+"... ");
			for(int i=0; i<UnrecognizedSymbols.size(); i++) {
				symbol unrec = (symbol) UnrecognizedSymbols.elementAt(i);
				symbol sym = (symbol) Symbols.get(unrec.text);
				if(Symbols.containsKey(unrec.name)) {
					System.out.println("HandleUnrecognizedSymbols won't deal with unparsed redefinition of "+unrec.name);
					removeList.addElement(unrec);
					skippedRedefined++;
					skippedSymbols--;
					continue;
				}
				
				//System.out.println("Symbol "+unrec.name+" has unrecognized text "+unrec.text+"... ");
				
				boolean cont = false;
				if(sym==null)  // Try to save something... (Parse complex strings)
					cont = jitParse(unrec);
				if(sym != null || cont) {
					resolvedLater++;
					if(sym!=null) {
//						System.out.println("late lookup succeeded for "+unrec.name+": "+unrec.text+" -> "+sym.text);
						unrec.text = sym.text;
						unrec.setTypes(sym.isBool, sym.isInt, sym.isLong, sym.isDouble, sym.isChar, sym.isString, sym.isComplex|unrec.isComplex);
					}
					Symbols.put(unrec.name, unrec);
					OutputToFile(unrec, false, false);
					OutputToFile(unrec, false, true);
					outputted++;
					removeList.addElement(unrec);
				}
			}

			// Must remove after finishing for loop, or add some slightly complex logic
			// to for loop for incrementing i.  But this gives us our convergence test, so...
			if(removeList.size() == 0)
				converged = true;
			else {
				System.out.println("removed "+removeList.size());
				for(int j=0; j<removeList.size(); j++) {
					symbol sym = (symbol) removeList.elementAt(j);
					UnrecognizedSymbols.removeElement(sym);
				}
			}
			removeList = null;
		} while(!converged);

		System.out.println("\nDone resolving unresolved symbols.");
		System.out.println("Resolved "+resolvedLater+" symbols, converging after "+(passes-2)+" passes.");
	}

	/**
	 * jitParse is a magic last-minute attempt at parsing complex symbol 
	 * expressions, looking for undefined symbols that might be defined now.  Employ
	 * whatever algorithms you want here, this is your last chance.  Changes sym.
	 * @param symbol to fix up.
	 * @return true if it fixed the problem, else false
	 */
	public boolean jitParse(symbol sym)
	{
		if(!sym.hasUndefinedTokens())
			return false;
		if(sym.text == null) {
			System.out.println("Ack! Won't JIT parse a symbol with null text! "+sym.name);
			return false;
		}
//		System.out.print("JIT parsing "+sym.name+"... ");
//		System.out.print("undef_tokens: "+sym.undefined_tokens+"  text: "+sym.text);
		StringTokenizer unrec_strings = new StringTokenizer(sym.undefined_tokens);
		do {
			String replace = unrec_strings.nextToken();
			symbol repsym = (symbol) Symbols.get(replace);
			if(repsym == null) {
				//System.out.println("failed.");
				return false;
			}
			//System.out.println(replace +" -> "+repsym.text);
			sym.addTypes(repsym.isBool, repsym.isInt, repsym.isLong, repsym.isDouble, repsym.isChar, repsym.isString, repsym.isComplex);

			StringTokenizer st = new StringTokenizer(sym.text, "() \t\r\n+-*\\/#&|~^", true);
			String token;
			String text = "";
			do {
				token = st.nextToken();
				String append;
				if(token.equals(replace)) {
					append = repsym.text;
					//System.out.print("replaced "+replace+" with "+repsym.text+"  ");
				}
				else
					append = token;
				text = text + append;
			} while(st.hasMoreTokens());
			sym.text = text;
		} while(unrec_strings.hasMoreTokens());
		sym.undefined_tokens = null;
//		System.out.println("JIT parsing succeeded for "+sym.name);
		return true;
	}

	/**
	 * Parses a C number and returns a symbol containing it.  Don't try editing
	 * without a spatula.
	 * @param st StreamTokenizer positioned on a number or a '-'.
	 * @return symbol holding the int, long, or double.
	 */
	protected symbol parseNum(StreamTokenizer st) throws IOException
	{
		if(st.ttype != st.TT_NUMBER && st.ttype != '-') {
			System.out.println("Invalid StreamTokenizer in parseNum!");
			System.exit(6);
		}
		symbol sym = new symbol();
		String text = "";
		boolean negative = false;
		boolean doULcheck = true;
		if(st.ttype=='-') {
			st.nextToken();
			negative = true;
		}
		sym.isInt = true;
		Double d = new Double(st.nval);  // we never have float values in #defines.
		text = text+d.intValue();
		if(st.nval==0.0) { // check for hex.
			st.nextToken();
			if(st.ttype == st.TT_WORD && st.sval.toLowerCase().startsWith("x")) {
				String append = "";
				if(st.sval.toUpperCase().endsWith("UL"))
					append="0"+st.sval.substring(0, st.sval.length()-2);
				else if(st.sval.toUpperCase().endsWith("L") || st.sval.toUpperCase().endsWith("U"))
					append="0"+st.sval.substring(0, st.sval.length()-1);
				else
					append = "0"+st.sval;
				if(append.length()>10) {
					sym.isLong = true;
					append = append+"L";
				}
				text = append;
				doULcheck = false;
			}
			else {
				st.pushBack();
				doULcheck = true;
			}
		}

		if(doULcheck) { // Do U & L check, plus E
			// U - unsigned   L - long   E - 10^x
			st.nextToken();
			if(st.ttype == st.TT_WORD) {
				if(st.sval.toUpperCase().equals("L") || st.sval.toUpperCase().equals("U")
					|| st.sval.toUpperCase().equals("UL")) {
					//System.out.println("Found a long...");
					//sym.isLong = true;
					//text = text+"L";
				}
				else if(st.sval.toUpperCase().startsWith("E")) {
					sym.isDouble = true;
					sym.isInt = false;
					text = text+st.sval.toUpperCase();
				}
				else  // Should never be called?
					st.pushBack();
			}
			else
				st.pushBack();
		}

		if(negative)
			text = "-"+text;
		sym.name = "Integer";
		sym.text = text;
		return sym;
	}  // end parseNum


	/**
	 * Parse a string of words, trying to unroll known symbols if possible.
	 * terminator should usually be StreamTokenizer.TT_EOL or ')'.
	 * <p>Ideally, parseWords will leave st on the terminator, but occasionally it will be
	 * on the EOL character.  It will add the symbol to UnrecognizedSymbols if appropriate,
	 * but not Symbols table.</p>
	 * <p>Currently it puts undefined symbols into the symbol once per occurrence!
	 * So something like: #define foo (x+x)  contains x twice.  JIT test takes slightly longer.
	 * Not very serious.</p>
	 * <p>BUGBUG: Casting doesn't work.</p>
	 * @param st StreamTokenizer positioned at the start of a word or expression [like a '('].
	 * @param terminator char to use as a token to end this expression (often ';' or ')')
	 * @param moreThanOneWord whether this expression can be longer than one word
	 * @param nested true if this is a recursive call to parseWords, else false.
	 * @param name Name of the symbol to return (ie, #define FOO 1  would have FOO as the name)
	 * @param pretext String to append before symbol text (used for casting)
	 * @param posttext String to append after symbol text (used for casting)
	 * @return symbol containing the parsed expression
	 * @exception IOException if st hits a problem
	 */
	protected symbol parseWords(StreamTokenizer st, char terminator, boolean moreThanOneWord, boolean nested, String name, String pretext, String posttext) throws IOException {
		// Booleans will be set here, but should also be set externally too.
		boolean isBool = false;
		boolean isChar = false;
		boolean isString = false;
		boolean isInt = false;
		boolean isLong = false;
		boolean isDouble = false;
		boolean isComplex = false;  // True if its something non-trivial, like (0x1|CONSTANT)
		boolean unknown = false;
		boolean firstTime = true;
		symbol retsym = new symbol();
		retsym.name = name;
		String text = pretext;
		if(st.ttype == terminator || st.ttype==st.TT_EOL || st.ttype==st.TT_EOF)
			return null;
		do {
			if(!firstTime)
				isComplex = true;
			String append = "";
			// Must eventually add in handling for ' and ".
			// Handle Unicode strings and characters.
			if(st.ttype==st.TT_WORD && st.sval.toUpperCase().equals("L")) {
				st.nextToken();
				// Normal characters are ' and ", but , and ) are common wrong cases...
				if(st.ttype == ',' || st.ttype==')')
					st.pushBack();
				else if(st.ttype != '\'' && st.ttype != '\"')
					System.out.println("Odd syntax: in "+name+", found L then not a string or char literal!");
			}
			if(st.ttype == '\'') {
				// When hitting a \', StreamTokenizer puts the character into sval.
				isChar = true;
				append = "\'"+st.sval+"\'";
				//System.out.println("Char "+name+" defined as "+text);
			}
			else if(st.ttype == '\"') {
				isString = true;
				append = '\"' + st.sval + '\"';
			}
			else if(st.ttype == st.TT_WORD && (st.sval.equals("MAKEINTRESOURCE") ||
				st.sval.equals("_HRESULT_TYPEDEF_") || st.sval.equals("TEXT"))) {
				// MAKEINTRESOURCE is used frequently in winuser.h.  It does some odd casting.
				// _HRESULT_TYPEDEF_ just returns the symbol.  Does nothing basically.
				String macroname = st.sval;
				st.nextToken();  // Read in '('
				st.nextToken();  // position right after '('
				if(st.ttype == '(') {
					System.out.println("Found a cast inside a "+macroname+" call.");
					st.nextToken();  // st = cast_type
					st.nextToken();  // st = ')'
					st.nextToken();  // position after trailing ')'
				}
				isInt = true;
				retsym = parseWords(st, ')', true, true, name, "", "");
				if(retsym.hasUndefinedTokens()) {
					System.out.println(macroname+" handler: "+name+" has unrecognized tokens!");
					System.out.println(retsym.undefined_tokens);
				}
				return retsym;
			}
			else if(st.ttype==st.TT_WORD && (st.sval.toUpperCase().equals("TRUE") || st.sval.toUpperCase().equals("FALSE"))) {
				// Boolean handler.
				isBool = true;
				System.out.println("Handling boolean "+name);
				if(st.sval.toUpperCase().equals("TRUE"))
					append = "true";
				else
					append = "false";
			}
			else if(st.ttype == st.TT_WORD) {
				//System.out.println("in parsewords on "+name+", found a string "+st.sval);
				// Necessary Function Alias check.
				if(firstTime && st.sval.startsWith(name) && st.sval.length() == name.length()+1) {
					//System.out.println("Skipping definition of function alias for "+name);
					skippedAliases++;
					retsym = null;
					return retsym;
				}

				// If possible, substitute the value for this symbol
				symbol value = (symbol) Symbols.get(st.sval);
				if(value==null) {
					//System.out.println("in parseWords, expression has unknown symbol in it! "+name+" text: "+text+" symbol: "+st.sval);
					unknown = true;
					append = st.sval;
					retsym.addUndefToken(st.sval);
				}
				else {
					//System.out.println(st.sval+" -> "+value.text);
					append = value.text;
					if(value.isInt)
						isInt = true;
				}
			}
			else if(st.ttype == st.TT_NUMBER) { // Don't put '-' here.  More flexible this way.
				symbol sym = parseNum(st);
				if(sym == null) {
					System.out.println("Ack! Unparsible int-like number.  name: "+name);
					retsym = null;
					skippedUnparsible++;
					return retsym;
				}
				append = sym.text;
				isInt = sym.isInt;
				isLong = sym.isLong;
				//System.out.println("Read an integer. "+append+" isInt: "+isInt+" isLong: "+isLong);
			}							
			else if(st.ttype == '(') {
				// This section is mostly for ignoring parenthesized casts, like:
				// #define x ((int) y)
				st.nextToken();
				if(st.ttype == st.TT_WORD && (st.sval.equals("int") || st.sval.equals("DWORD")
					  || st.sval.equals("WORD") || st.sval.equals("HTREEITEM"))) {
					st.nextToken();
					//System.out.println("Found something like a int cast in "+name);
					if(st.ttype == ')') {
						//System.out.println("For "+name+", found an int cast.");
						isInt = true;
						// Let loop test handle positioning issues.
						continue;
					}
					else
						st.pushBack();
				}
				else if(st.ttype == st.TT_WORD && st.sval.toUpperCase().equals("BYTE")) {
					st.nextToken();
					if(st.ttype == ')') {
						//System.out.println("For "+name+", found a BYTE cast.");
						isInt = true;
						// Let loop test handle positioning issues.
						continue;
					}
					else
						st.pushBack();
				}
				else {  // Normal parenthesized expression case.
					symbol trash = parseWords(st, ')', true, true, "embedded from "+name, "", "");
					if(trash == null) { // the normal case
						System.out.println(name+" had an unrecognized parenthesized expression! Guessing it was a parenthesized cast.");
						skippedUnparsible++;
						if(st.ttype != st.TT_EOL)
							while(st.nextToken() != st.TT_EOL && st.ttype != st.TT_EOF);
						unknown = true;
						retsym = null;
						return retsym;
					}
					else {
						//System.out.println("Wow.  Got embedded expression from "+name+".  text was "+trash.text);
						append = '('+trash.text+')';
						isBool = isBool | trash.isBool;
						isInt = isInt | trash.isInt;
						isLong = isLong | trash.isLong;
						isDouble = isDouble | trash.isDouble;
						isChar = isChar | trash.isChar;
						isString = isString | trash.isString;
						isComplex = true;
					}
				}
			}
			else if(st.ttype == '+' || st.ttype == '-' || st.ttype == '/' || st.ttype == '&' ||
					  st.ttype == '|' || st.ttype == '~' || st.ttype == '<' || st.ttype == '>' ||
					  st.ttype == '#')
			{
				//System.out.println("Appending operator "+(char)st.ttype);
				append = ""+(char)st.ttype;
				if(st.ttype=='#') {
					System.out.println("General interest note: Added operator \'#\' to "+name+", thinking I\'ve found string##string");
				}
			}
			else {
				//System.out.println("Appending unrecognized token "+(char)st.ttype);
				append = ""+(char)st.ttype;
			}

			text = text + append;
			firstTime = false;			
		} while(st.nextToken() != st.TT_EOL && st.ttype != terminator && moreThanOneWord && st.ttype != st.TT_EOF);

		if(!moreThanOneWord) {
			if(st.ttype != terminator && st.ttype != st.TT_EOF) {
				System.out.println("Ack!  Serious error in parseWords.  Expected one word, got multiple. name: "+name+"  text: "+text);
			}
		}

		if(st.ttype != terminator || retsym == null) {
			if(!nested) {
				while(st.ttype != st.TT_EOL && st.ttype != st.TT_EOF)
					st.nextToken();
				skippedUnterminatedExpressions++;
				//System.out.println("parseWords ignoring unterminated expression "+name);
			}
			return null;
		}
		retsym.text = text + posttext;
		retsym.setTypes(isBool, isInt, isLong, isDouble, isChar, isString, isComplex);

		if(isBool)
			System.out.println("Found boolean "+name);

		if(st.ttype != terminator && st.ttype != st.TT_EOL) {
			System.out.println("Ack!!! st not positioned properly while reading "+name+"! st.ttype: "+(char)st.ttype+" sval: "+st.sval);
			System.exit(12);
		}

		// Macro and cast check
		if(!nested && terminator == ')' && st.ttype == terminator) {
			st.nextToken();
			if(st.ttype != st.TT_EOL) {
				//System.out.println("Found macro or unparenthesized cast "+name);
				skippedMacros++;
				while(st.nextToken() != st.TT_EOL && st.ttype != st.TT_EOF);
				return null;
			}
		}

		if(unknown) {
			if(!nested) {
				//System.out.println("parseWords punted on unknown "+retsym.name+" = "+retsym.text);
				skippedSymbols++;
				UnrecognizedSymbols.addElement(retsym);
			}
			return null;
		}
		else {
			//System.out.println("parseWords returning "+retsym.name+" = "+retsym.text);
			return retsym;
		}
	}
	

	public void scan(String infile) throws IOException
	{
		InputStreamReader isr = new InputStreamReader(new FileInputStream(infile));
		StreamTokenizer st = new StreamTokenizer(isr);
		st.eolIsSignificant(true);
		st.wordChars('_', '_');
		st.wordChars(':', ':');
		st.ordinaryChar('/');
		st.ordinaryChar('-');
		st.ordinaryChar('+');
		st.ordinaryChar('*');
		st.slashSlashComments(true);
		st.slashStarComments(true);
	//	st.wordChars('0', '9');
		boolean lastWasInt = false;
		boolean lastWasString = false;

		st.nextToken();

		// Must use labelled while loop here to more easily exit out of function.
		// Loop invariant - if this is a valid line, then st is positioned on the # at
		// the beginning of this loop.  And the second token after # is name.
		// However, we do have lines like:  * some comment text mentioning #define foo
lineproc: while(st.ttype != st.TT_EOF) {
			total++;
			st.nextToken(); // read define
			st.nextToken(); // read name
			if(st.ttype != st.TT_WORD) {
				System.out.println("Ack!  not good!");
				System.out.println("Instead of a name, we found "+(char)st.ttype+" sval: "+st.sval);
				System.out.println("Loop invariant broken in file "+infile+", or data file in unrecognized format.");
				System.exit(8);
			}
			String name = st.sval;
			//System.out.println("name: "+name);
			if(name.equals("define")) {
				System.out.println("Critical error: name was define.  Loop invariant broken.");
				System.exit(13);
			}
			st.nextToken();
			String text = "";
			boolean isBool = false;
			boolean isChar = false;
			boolean isString = false;
			boolean isInt = false;
			boolean isLong = false;
			boolean isDouble = false;
			boolean isComplex = false;  // True if its something non-trivial, like (0x1|CONSTANT)
			boolean CommentOut = false;

			if(st.ttype == st.TT_WORD && st.sval.toUpperCase().equals("L")) {
				// What we have next is a Unicode character or string, I think...
				st.nextToken();
				if(st.ttype != '\'' && st.ttype != '\"') {
					System.out.println("Error: Found L followed by something other than a \' or \"! token: "+(char)st.ttype);
					System.exit(14);
				}
			}

			if(st.ttype == '\\' || st.ttype == '{' || st.ttype == '&') {
				total--;
				while(st.nextToken() != st.TT_EOL && st.ttype!=st.TT_EOF);
				st.nextToken();
				continue;
			}
			else if(st.ttype == '\'') {
				// When hitting a \', StreamTokenizer puts the character into sval.
				isChar = true;
				//st.nextToken();
				text = "\'"+st.sval+"\'";
				//System.out.println("Char "+name+" defined as "+text);
				st.nextToken();
			}
			else if(st.ttype == '(') {
				// Skip macros.  But check for something like #define FLAG (-1)
				// And try to parse complex expressions like #define z (y+1)
				st.nextToken();
				text = "(";

				if(st.ttype != ')') {
					symbol blah = parseWords(st, ')', true, false, name, text, ")");
					if(st.ttype == ')')
						st.nextToken();
					if(blah == null) {
						// Macros will go through this part of the code.  So will 
						// unparenthesized casts, like #define x (int)y
						if(st.ttype != st.TT_EOL) {
							// Found a macro.
							//skippedMacros++;
							//skippedSymbols--;
							System.out.println("Skipping macro "+name+"... ");
							removeSymbol(name, UnrecognizedSymbols);
							while(st.nextToken() != st.TT_EOL && st.ttype != st.TT_EOF);
							st.nextToken();
							continue lineproc;
						}
						System.out.println("parsewords gave up on expression starting with '(' "+name);
						if(st.ttype != st.TT_EOL)
							while(st.nextToken() != st.TT_EOL && st.ttype != st.TT_EOF);
						st.nextToken();
						continue lineproc;
					}
					else {
						//blah.text = blah.text + ')';
						isComplex = blah.isComplex;
						isBool = blah.isBool;
						isInt = blah.isInt;
						isLong = blah.isLong;
						isDouble = blah.isDouble;
						isChar = blah.isChar;
						isString = blah.isString;
						text = blah.text;
//						Symbols.put(blah.name, blah);
						// If we get here and st isn't at EOL, freak below in loop invariant check.
					}
				}
				else {
					System.out.println("Weird case: found "+name+" ( ) and I don't know what to do with it.");
					System.out.println("Punting "+name+" as a macro...");
					skippedMacros++;
					while(st.nextToken() != st.TT_EOL && st.ttype != st.TT_EOF);
					st.nextToken();
					continue lineproc;
				}
			} // End '(' handler
			else if(st.ttype == '\"') {
				// When finding a quoteChar, StreamTokenizer puts the string in the sval field
				// But that's the wrong approach because that way strings could span lines,
				// or at least that's what I think...  Not sure.  Very odd results.

				// For now ignore strings.
				//System.out.println("Skipping string "+name);
				//skippedStrings++;
				/*
				while(st.nextToken() != st.TT_EOL && st.ttype != st.TT_EOF);
				st.nextToken();
				continue;
*/

				isString = true;
				text = "\""+st.sval+"\"";
				st.nextToken();
				if(st.ttype != st.TT_EOL) {
					System.out.println("Ack!  Found non-EOL token "+(char)st.ttype+" after string!");
					System.exit(9);
				}

				if(st.ttype != st.TT_EOL)
					st.nextToken();
				//System.out.println("String "+name+" defined as "+text);

			}
			else if(st.ttype == st.TT_NUMBER || st.ttype=='-') {
				// Normal number handler.
				symbol sym = parseNum(st);
				if(sym == null)
					continue;
				text = sym.text;
				isInt = sym.isInt;
				isLong = sym.isLong;
				isDouble = sym.isDouble;
				//System.out.println("Read an integer. "+text+" isInt: "+isInt+" isLong: "+isLong);

				st.nextToken(); // read in TT_EOL.  If not here, we should freak in loop invariant.
			}
			else if(st.ttype == st.TT_WORD) {
				// Something like:  #define SOMEINT 1     #define FOO SOMEINT
				// or could be #define CreateWindow CreateWindowW

				// More special parseWords code
				symbol value = parseWords(st, (char)st.TT_EOL, false, false, name, "", "");
				if(value == null) {
					//System.out.println("while reading a word, parseWords gave up on "+name);
					if(st.ttype != st.TT_EOL)
						while(st.nextToken() != st.TT_EOL && st.ttype != st.TT_EOF);
					st.nextToken();
					continue lineproc;
				}
				else {
					isBool = value.isBool;
					isChar = value.isChar;
					isString = value.isString;
					isLong = value.isLong;
					isDouble = value.isDouble;
					isInt = value.isInt;
					isComplex = value.isComplex;
					text = value.text;
					if(st.ttype != st.TT_EOL)
						st.nextToken();
					if(st.ttype != st.TT_EOL) {
						System.out.println("Not at end of line.  macro? "+name);
						while(st.nextToken() != st.TT_EOL && st.ttype != st.TT_EOF);
					}
				}

				/*
				// Necessary Function Alias check.
				if(text.startsWith(name) && text.length() == name.length()+1) {
					System.out.println("Skipping definition of function alias for "+text);
					skippedAliases++;
					if(st.ttype != st.TT_EOL)  // This will almost never be true.
						while(st.nextToken() != st.TT_EOL && st.ttype != st.TT_EOF);
					if(st.ttype !=st.TT_EOF)
						st.nextToken();
					continue;
				}
				*/
			}  // end Word handler. (plus function alias handler)
			else if(st.ttype == st.TT_EOL) {
				// Found a defined symbol, but with no value assigned to it.
				//isInt = true;
				//text = "1";
				st.nextToken();
				skippedNoValue++;
				continue lineproc;
			}


			// Now handle symbol lookup rules.

			// If this is a redefinition, comment this out.
			if(Symbols.containsKey(name)) {
				//System.out.println("Not redefining "+name);
				CommentOut = true;
				skippedRedefined++;
				symbol s = (symbol) Symbols.get(name);
				if(s.text.equals(text)) {
					if(st.ttype!=st.TT_EOF)
						st.nextToken();
					continue;
				}
			}

			// If it's a String or a Character or a complex blob of tokens, don't expect
			// it to appear in the symbol table.  If it's an int, its shaky.  That's because
			// while an int could be something like (-1), an int could also be something 
			// like #define FOO 1   then #define THIS_IS_AN_INT FOO
			if(!isBool && !isString && !isChar && !isLong && !isComplex) {
				//StringTokenizer str = new StringTokenizer(text);
				if(text.length()==0)
					System.out.println("Ack!  for "+name+", text was length 0!");
				char c = text.charAt(0);
				if(!Character.isDigit(c) && c != '-'  & c!='(') {
					symbol s = (symbol) Symbols.get(text);
					// Extremely simple and underpowered parse attempt. look at jitParse...
					if(s == null) {
						//System.out.println("Symbol "+text+" not found.  Will try "+name+" later.");
						symbol unrec_sym = new symbol();
						unrec_sym.name = name;
						unrec_sym.text = text;
						unrec_sym.setTypes(isBool, isInt, isLong, isDouble, isChar, isString, isComplex);
						UnrecognizedSymbols.addElement(unrec_sym);
						st.nextToken();
						skippedSymbols++;
						continue lineproc;
					}
					else
						text = s.text;
				}
			}

			// Create a symbol and insert into Symbol table.
			symbol sym = null;
			sym = new symbol();
			sym.name = name;
			sym.text = text;
			sym.setTypes(isBool, isInt, isLong, isDouble, isChar, isString, isComplex);
			if(!CommentOut) {
				Symbols.put(name, sym);

// This is a deprecated check.
//				if(sym.isString && !SuppressStrings) // Skip strings for now.
//					skippedStrings++;
//				else
					outputted++;
			}

			// Call first to output to alphabetical file
			OutputToFile(sym, CommentOut, false);
			// Call a second time to output to global output file.
			OutputToFile(sym, CommentOut, true);
			
			if(!isBool && !isString && !isInt && !isChar && !isDouble) {
				System.out.println("Neither isBool nor isString nor isInt nor isChar nor isDouble were true! name: "+name+" text: "+text);
			}

			// Loop invariant check and preservation code.  This is probably the
			// only safe place for this test, sadly.  Plus it can't get much fancier.
			if(st.ttype != st.TT_EOL) {
				System.out.println("loop invariant broken file: "+infile+".  name&text: "+name+"\t"+text+". st.ttype="+(char)st.ttype+"  Quitting.");
				System.exit(1);
			}
			st.nextToken();  // Must move past EOL to # or possibly EOF
		}
		isr.close();
		isr = null;
		st = null;
	}

	public void scanfromFile(String filename) throws IOException
	{
		try {
		InputStreamReader isr = new InputStreamReader(new FileInputStream(filename));
		StreamTokenizer st = new StreamTokenizer(isr);
		st.eolIsSignificant(false);
		while(st.nextToken() != st.TT_EOF) {
			scan("defs/"+st.sval);
		}
		isr.close();
		isr = null;
		st = null;
		}
		catch (IOException e) {
			System.out.println("Problem: "+e+" while opening "+filename);
			throw e;
		}
	}

	/**
	 * Generates output from symbol, writing output to either the proper alphabetical
	 * file or to the global output file.  Handles cases such as first line in file and
	 * the type being the same as the last type in the file, removing type declarations.
	 * This is pretty slick.
	 * @param sym #symbol to output
	 * @param CommentOut whether this line should be commented out or not
	 * @param globalOutput should we send this to the global output file OR the proper alphabetical file
	 * @return No return value.
	 */
	public void OutputToFile(symbol sym, boolean CommentOut, boolean globalOutput) throws IOException
	{
		if(sym == null) {
			System.err.println("Not going to deal with null symbols in OutputToFile!");
			System.exit(7);
		}

		// Select the correct file to output in.
		FileWrapper f=null;
		if(globalOutput)
			f = (FileWrapper) Files.elementAt(global_output);
		else if(sym.isString && SeparateStrings)
			f = (FileWrapper) Files.elementAt(string_output);
		else {
			// Name tells us which file to put output in.
			char first = Character.toLowerCase(sym.name.charAt(0));
			if(first >= 'a' && first <= 'z')
				f = (FileWrapper) Files.elementAt(first - 'a');
			else
				f = (FileWrapper) Files.elementAt(misc_output);
		}

		// Now set all the necessary output strings which depend on this symbol and this file.
		String header = ";\r\n\t";  // normal case
		if(f.veryFirstLine) {
			header = "\t";
			f.veryFirstLine = false;
		}
		boolean isSameType = false;
		// Check to see whether this type is the same as the last type.
		if((sym.isString && f.lastWasString) || (sym.isInt && f.lastWasInt && !sym.isLong) ||
			(f.lastWasLong && sym.isLong) || (sym.isChar && f.lastWasChar) ||
			(sym.isDouble && f.lastWasDouble) || (sym.isBool && f.lastWasBool)) 
		{
			header = ",\r\n\t\t";
			isSameType = true;
		}

		if(CommentOut)
			header = ";\r\n\t// ";

		String output = header;
		if(!isSameType) {
			if(sym.isInt) {
				if((f.lastWasInt && !sym.isLong) || (f.lastWasLong && sym.isLong))
					output = header;
				else {
					if(sym.isLong)
						output = header+"long ";
					else
						output = header+"int ";
				}
			}
			else if(sym.isDouble) {
				output = header+"double ";
			}
			else if(sym.isString) {
				output = header+"String ";
			}
			else if(sym.isChar) {
				output = header+"char ";
			}
			else if(sym.isBool) {
				output = header+"boolean ";
			}
			else if(sym.isComplex) {
				output = header+"int ";
			}
			else
				output = "\r\n\r\nAck!  Unknown type!";
		}

		output = output + sym.name + " = " + sym.text;

		if(CommentOut) { // set everything to false
			f.lastWasBool = false;
			f.lastWasInt = false;
			f.lastWasLong = false;
			f.lastWasChar = false;
			f.lastWasString = false;
		}
		else {
			f.lastWasBool = sym.isBool;
			f.lastWasInt = sym.isInt && !sym.isLong;
			f.lastWasLong = sym.isLong;
			f.lastWasChar = sym.isChar;
			f.lastWasString = sym.isString;
		}
		
		if(!sym.isBool && !sym.isString && !sym.isInt && !sym.isChar && !sym.isDouble) {
			System.out.println("Neither isBool nor isString nor isInt nor isChar nor isDouble were true! name: "+sym.name+" text: "+sym.text);
		}

		if(!CommentOut)
			f.numEntries++;
		f.stream.print(output);
	}

	protected void removeSymbol(String name, Vector search)
	{
		for(int i=0; i<search.size(); i++) {
			symbol s = (symbol) search.elementAt(i);
			if(s.name.equals(name)) {
				search.removeElementAt(i);
				System.out.println("Removed "+name);
			}
		}
	}

	/**
	 * Scans through all symbols, looking for pairs that end in A and W 
	 * (ASCII and Unicode versions) and creates a new one using the ASCII
	 * value without the A or W.
	 * @return No return value.
	 */
	protected void UnifyAWSymbols()
	{
		// Make enumeration from hashtable Symbols.  Don't forget to check in UndefinedSymbols too...?
		symbol sym;
		System.out.print("Unifying symbols... ");
		Enumeration e = Symbols.elements();
		unifySymbolsHelper(e, true);
		e = UnrecognizedSymbols.elements();
		unifySymbolsHelper(e, false);
		System.out.println("Done unifying symbols.");
	}

	/**
	 * Scans an enumeration for symbols to be unified, unifys them, then puts them
	 * in either the Symbols or UnrecognizedSymbols table.
	 * @param e Enumeration to scan.
	 * @param recognized true if this e contains recognized symbols, false if it has unrecognized ones.
	 */
	protected void unifySymbolsHelper(Enumeration e, boolean recognized)
	{
		symbol sym;
		while(e.hasMoreElements()) {
			String rootname = null;
			symbol ASCIIsym = null;
			symbol Unicodesym = null;
			sym = (symbol) e.nextElement();
			if(sym.name.endsWith("A")) {
				ASCIIsym = sym;
				rootname = sym.name.substring(0, sym.name.length()-1);
				if(!Symbols.containsKey(rootname))
					Unicodesym = (symbol) Symbols.get(rootname+"W");
			}
			else if(sym.name.endsWith("W")) {
				Unicodesym = sym;
				rootname = sym.name.substring(0, sym.name.length()-1);
				if(!Symbols.containsKey(rootname))
					ASCIIsym = (symbol) Symbols.get(rootname+"A");
			}
			if(Unicodesym != null && ASCIIsym != null) {
				if(Unicodesym == ASCIIsym) {
					System.out.println("For "+sym.name+", two symbol structures were exactly equal!");
					continue;
				}
				System.out.println("Unifying symbols to "+rootname+"... ");
				// For now, we always use the ASCII value, which is depressing.
				// But its the only thing that will work on both 95 & NT.
				symbol ins = new symbol();
				ins.name = rootname;
				ins.type = ASCIIsym.type;
				ins.isBool = ASCIIsym.isBool;
				ins.isChar = ASCIIsym.isChar;
				ins.isString = ASCIIsym.isString;
				ins.isInt = ASCIIsym.isInt;
				ins.isLong = ASCIIsym.isLong;
				ins.isDouble = ASCIIsym.isDouble;
				ins.isComplex = ASCIIsym.isComplex;
				ins.text = new String(ASCIIsym.text);
				if(ASCIIsym.undefined_tokens != null)
					ins.undefined_tokens = new String(ASCIIsym.undefined_tokens);

				// Add to appropriate symbol storage and output to files.
				if(recognized)
					Symbols.put(rootname, ins);
				else
					UnrecognizedSymbols.addElement(ins);
				try {
					OutputToFile(ins, false, false);
					OutputToFile(ins, false, true);
					unifiedSymbols++;
					total++;
				}
				catch(IOException ioe) {
					System.out.println("Ack! Caught "+ioe+" while trying to output unified file name!");
				}
			}
		}
	}

	public static void main(String args[])
	{
		try {
			defscan read = new defscan();
			read.out = new PrintWriter(new FileOutputStream("win.java"));
			read.out.print("\r\ninterface Constants\r\n{\r\n");

			if(args.length == 0) {
				/*
				System.out.println("Usage: defscan <file of #defines> [<more files>]");
				System.exit(5);
				*/
				System.out.println("Using file list \"files.txt\" as input files to search through.");
				read.scanfromFile("files.txt");
			}
			else {
				for(int i=0; i<args.length; i++) {
					System.out.println("Processing "+args[i]+"... ");
					read.scan(args[i]);
				}
			}

			read.UnifyAWSymbols();

			read.HandleUnrecognizedSymbols();

			read.out.print(";\r\n\r\n}\r\n");
			read.out.close();
			read.CloseInterfaceFiles();
			float precentUnparsed = (float) (read.skippedUnterminatedExpressions + 
				(read.skippedSymbols-read.resolvedLater) + read.skippedUnparsible) 
				/ (read.total - read.unifiedSymbols);
			System.out.println("Skipped "+read.skippedMacros+" macros and unparenthesized casts [example: #define x (int)y ]");
			System.out.println("Skipped "+read.skippedAliases+" function and structure aliases.");
			System.out.println("Skipped "+read.skippedSymbols+" unrecognized symbols, but "+read.resolvedLater+" were resolved later, leaving "+(read.skippedSymbols-read.resolvedLater)+".");
			System.out.println("Skipped "+read.skippedNoValue+" symbols defined without a value.");
			System.out.println("Skipped "+read.skippedRedefined+" redefined symbols.");
//			System.out.println("Read "+read.skippedStrings+" strings.");
			System.out.println("Skipped "+read.skippedUnterminatedExpressions+" unterminated expressions.");
			System.out.println("Skipped "+read.skippedUnparsible+" unparsible expressions (including parenthesized casts & pointers)");
			System.out.println("Read through "+read.total+" symbols.");
			System.out.println("Unified "+read.unifiedSymbols+" ASCII & Unicode redefined symbols.");
			System.out.println("Outputted "+read.outputted+" symbols.");
			System.out.println("Percentage unparsible: "+precentUnparsed*100.0);

			int diff = read.total - read.outputted - read.skippedAliases 
				- read.skippedSymbols - read.skippedNoValue - read.skippedRedefined 
				- read.skippedStrings
				- read.skippedMacros - read.skippedUnterminatedExpressions - read.skippedUnparsible
				+ read.resolvedLater - read.unifiedSymbols;
			if(diff != 0)
				System.out.println("I lost "+diff+" symbols!");
		}
		catch (IOException e)
		{
			System.out.println("IOException caught: "+e);
			for(int i=0; i<1000000; i++);
		}
		catch (Exception e)
		{
			System.out.println(e);
			e.printStackTrace();
		}
	}
}
