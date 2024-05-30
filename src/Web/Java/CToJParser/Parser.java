/** 
 * Parser for Win32 API header files
 *
 * Copyright (C) 1997 Microsoft Corporation
 *
 * This tool was used to generate a significant portion of the Win32 API classes. 
 * It is being included for you to use and modify to fit your specific needs. Remember 
 * that C header files were not designed to be language-independent descriptions, and 
 * that there is more than one correct way to represent some data types in Java. Thus,
 * some functions will require hand-translation. For information on how to do this, 
 * see the J/Direct documentation.
 *
 *
 */

import java.io.*;
import java.util.*;

import com.ms.util.Comparison;  // For Sorting.


class UnrecognizedCodeException extends Throwable
{
	public String BadFragment;
	public String Description;

	/**
	 * Used to signal unparsible code segments.
	 */
	UnrecognizedCodeException()
	{
		super();
		BadFragment = "Unspecified UnrecognizedCodeException - programmer messed up.";
	}

	/**
	 * Used to signal unparsible code segments and give a rough idea what the
	 * problem was.
	 * @param bad_code The reason for failure and the code that couldn't be parsed.
	 */
	UnrecognizedCodeException(String bad_code)
	{
		super();
		BadFragment = new String(bad_code);
	}

	/**
	 * Used to signal unparsible code segments and give a rough idea what the
	 * problem was.
	 * @param reason Reason why this code failed.
	 * @param bad_code The reason for failure and the code that couldn't be parsed.
	 */
	UnrecognizedCodeException(String reason, String bad_code)
	{
		super();
		BadFragment = bad_code;
		Description = reason;
	}
}

class ExprSyntaxError extends UnrecognizedCodeException
{
	public ExprSyntaxError(String reason, String bad_code)
	{
		super(reason, bad_code);
	}

	public String toString()
	{
		return "Expression syntax error: "+Description+"  bad code: "+BadFragment;
	}
}

class NumExprSyntaxError extends ExprSyntaxError
{
	public NumExprSyntaxError(String reason, String bad_code)
	{
		super(reason, bad_code);
	}

	public NumExprSyntaxError(String reason, char bad_code)
	{
		super(reason, ""+bad_code);
	}

	public String toString()
	{
		return "NumExpression syntax error: "+Description+"  bad code: "+BadFragment;
	}
}

/**
 * Used only to move control around.
 */
class DoneException extends Throwable
{
}

/**
 * Punt exceptions are used to give up on certain data types.
 */
class PuntException extends Throwable
{
	public String Reason;
	public String Name;

	/**
	 * Build a PuntException with a reason and the name of the punted item.
	 * @param reason Why we punted
	 * @param name What we punted
	 */
	public PuntException(String reason, String name)
	{
		Reason = reason;
		Name = name;
	}
}

/**
 * Used to signal a corrupt or missing input file.
 */
class BadInputFileException extends Throwable
{
	public String BadFile;

	BadInputFileException()
	{
		super();
		BadFile = "<Unknown File>";
	}

	BadInputFileException(String bad_file)
	{
		super();
		BadFile = new String(bad_file);
	}
}


/**
 * Used to signal an error in the input to a function.  A number was out of range,
 * a parameter was null, or a file didn't exist.
 */
class InvalidParameterException extends Throwable
{
	public String Description;

	InvalidParameterException()
	{
		Description = "<Unknown failure>";
	}

	InvalidParameterException(String problem)
	{
		Description = problem;
	}
}

/**
 * Used to signal a bad operation, such as an operator that doesn't have a corresponding
 * Operator class.  An example might be the sizeof() operator, which I don't represent.
 */
class BadOperationException extends InvalidParameterException
{
	BadOperationException()
	{
		super("<Unknown bad operation>");
	}

	BadOperationException(String problem)
	{
		super(problem);
	}
}


/**
 * Need an Operator class for precedence lookup.  Maintains data to identify how this
 * operator is used.  Is it a prefix operator vs. postfix or infix?  Is it a unary
 * or binary operator?  What is its precedence?
 * @see Parser.html#SetupPrecedenceTable
 */
class Operator 
{
	protected String op;
	protected boolean unary;
	protected boolean prefix;
	protected int precedence;

	/**
	 * Build an Operator object.
	 * @param newop String containing operator
	 * @param isUnaryOperator true if it's a unary operator (ie x++), false if it's a binary operator (ie x + y)
	 * @param isPrefixOperator true if operator precedes its operand (++x), false if it follows operand (x++)
	 * @param precedent int describing order of operations.  Higher numbers go first.
	 */
	Operator(String newop, boolean isUnaryOperator, boolean isPrefixOperator, int precedent)
	{
		op = newop;
		unary = isUnaryOperator;
		prefix = isPrefixOperator;
		precedence = precedent;
	}

	/**
	 * Clean up fields.
	 */
	public void finalizer()
	{
		op = null;
	}

	/**
	 * Get operator.
	 * @return String containing operator
	 */
	String getOp()
	{
		return op;
	}

	/**
	 * Is this a unary operator?
	 * @return true if its unary (ie x++), false if its binary (ie x+y)
	 */
	boolean isUnaryOperator()
	{
		return unary;
	}

	/**
	 * Is this a prefix operator instead of an infix (in the case of binary operators) or
	 * postfix (in the case of unary operators) operator?
	 * @return true if its prefix (ie ++x), false if its infix or postfix (ie x+y and x++)
	 */
	boolean isPrefixOperator()
	{
		return prefix;
	}

	/**
	 * Get integer describing operator's precedence.  Higher numbers go first in order of
	 * operations.
	 * @return precedence
	 */
	int getPrecedent()
	{
		return precedence;
	}

	/**
	 * Convert to string for output.  It's the caller's responsibility to worry about
	 * context and multiple versions of an operator.
	 * @return Operator in C.
	 */
	public String toString()
	{
		return op;
	}
}


/**
 * A real expression class, for handling expressions.
 */
class Expression {
	public String name;
	public String text;

	public Expression(String expr_name)
	{
		name = expr_name;
	}

	public Expression(String expr_name, String expr_text)
	{
		name = expr_name;
		text = expr_text;
	}

	public void finalizer()
	{
		name = null;
		text = null;
	}

	public String toString()
	{
		return text;
	}
}


abstract class NumExpression extends Expression {
	int bits;    // number of bits in this number.
	NumExpression a, b;
	String op;
	boolean prefix;
	boolean unary;

	public NumExpression()
	{
		super("num expression");
		bits = 32;
	}

	public NumExpression(String expr_text)
	{
		super("num expression", expr_text);
		bits = 32;
	}

	/**
	 * Build an integer expression out of a prefix unary operator applied to an 
	 * integer expression.
	 * @param operation String containing operator
	 * @param expr NumExpression to apply operator to.
	 */
	public NumExpression(String operation, NumExpression expr)
	{
		super("num expression", operation+expr.toString());
		prefix = true;
		unary = true;
		op = operation;
		a = expr;
		b = null;
		bits = expr.getLength();
	}

	/**
	 * Build an integer expression out of a postfix unary operator applied to an 
	 * integer expression.
	 * @param operation String containing operator
	 * @param expr NumExpression to apply operator to.
	 */
	public NumExpression(NumExpression expr, String operation)
	{
		super("num expression", expr.toString()+operation);
		prefix = false;
		unary = true;
		op = operation;
		a = expr;
		b = null;
		bits = expr.getLength();
	}

	/**
	 * Evaluate a NumExpression and return its results as a 64-bit quantity.
	 * @return Value of the exception
	 * @exception BadOperationException if we couldn't parse an operator
	 */
	abstract long eval() throws BadOperationException;

	/**
	 * Used to get the length of an integer expression representation in bits.
	 * @return Number of bits.
	 */
	public int getLength()
	{
		return bits;
	}

	/**
	 * Return a string representation of this NumExpression.  Should add parentheses as
	 * needed for order of operations.
	 * @return String containing NumExpression.
	 */
	abstract public String toString();
}

class IntExpression extends NumExpression {
	long intval;
	boolean evaluated;
	boolean complex;

	/**
	 * Build an integer expression out of two other integer expressions and an
	 * operation to be applied to them.  Mathematically, this wraps:<p>
	 * (Integer_Expression Op Integer_Expression)<p>
	 * Example: IntExpression(5, "+", 4)  =>  (5+4)<p>
	 * We try to preserve the bitdepth in the first expression, just as C would.
	 * @param first First integer expression
	 * @param operation String containing operator
	 * @param second Second integer expression
	 */
	public IntExpression(NumExpression first, String operation, NumExpression second)
	{
		a = first;
		op = operation;
		b = second;
		bits = first.getLength();
		complex = true;
		evaluated = false;
		unary = false;
	}

	/**
	 * Build an integer expression out of a prefix unary operator applied to an 
	 * integer expression.
	 * @param operation String containing operator
	 * @param expr IntExpression to apply operator to.
	 */
	public IntExpression(String operation, NumExpression expr)
	{
		super(operation, expr);
	}

	/**
	 * Build an integer expression out of a postfix unary operator applied to an 
	 * integer expression.
	 * @param operation String containing operator
	 * @param expr IntExpression to apply operator to.
	 */
	public IntExpression(NumExpression expr, String operation)
	{
		super(expr, operation);
	}

	/**
	 * Build an integer expression out of a short int number.
	 * @param value short int to represent
	 */
	public IntExpression(short value)
	{
		intval = value;
		bits = 16;
		complex = false;
		a = null;
		b = null;
		op = null;
		evaluated = true;
		unary = false;
	}
	
	/**
	 * Build an integer expression out of an integer.
	 * @param value int to represent
	 */
	public IntExpression(int value)
	{
		intval = value;
		bits = 32;
		complex = false;
		a = null;
		b = null;
		op = null;
		evaluated = true;
		unary = false;
	}

	/**
	 * Build an integer expression out of a long integer.
	 * @param value long int to represent
	 */
	public IntExpression(long value)
	{
		intval = value;
		bits = 64;
		complex = false;
		a = null;
		b = null;
		op = null;
		evaluated = true;
		unary = false;
	}

	/**
	 * Evaluates an IntExpression.  If this was assigned an integer 
	 * value, return that integer.  If it was an operation performed
	 * on one or two IntExpressions, evaluate those then perform the
	 * operation.  Store result for lazy evaluation.
	 * @return int containing value of expression after evaluation
	 * @exception BadOperationException thrown if eval doesn't understand the operation.
	 */
	public long eval() throws BadOperationException
	{
		if(evaluated)
			return intval;

		if(unary) {
			if(a==null) {
				System.out.println("Ack!  In IntExpression::eval of a unary operator, a was null!");
				System.exit(1);
			}
			long val = (long) a.eval();
			if(op.equals("-"))
				intval = -val;
			else if(op.equals("~"))
				intval = ~val;
			else if(op.equals("++"))
				intval = val + 1;
			else if(op.equals("--"))
				intval = val - 1;
			else if(op.equals("+"))
				intval = val;
			else if(op.equals("!"))
				intval = (val==0 ? 1 : 0);
			else
				throw new BadOperationException("Unknown unary operation \""+op+"\" in NumExpression::eval()!");
		}
		else if(a != null) {
			long aval = a.eval();
			if(b==null) {
				System.out.println("Ack!  In IntExpression::eval of a binary operator, b was null!");
				System.exit(1);
			}
			long bval = b.eval();
			if(op.equals("+"))      // Arrange by perceived frequency
				intval = aval + bval;
			else if(op.equals("<<"))
				intval = aval << bval;
			else if(op.equals("|"))
				intval = aval | bval;
			else if(op.equals("&"))
				intval = aval & bval;
			else if(op.equals(">>"))
				intval = aval >> bval;
			else if(op.equals("-"))
				intval = aval - bval;
			else if(op.equals("*"))
				intval = aval * bval;
			else if(op.equals("/"))
				intval = aval / bval;
			else if(op.equals("%"))
				intval = aval % bval;
			else if(op.equals("<"))
				intval = (aval < bval ? 1 : 0);
			else if(op.equals(">"))
				intval = (aval > bval ? 1 : 0);
			else if(op.equals("<="))
				intval = (aval <= bval ? 1 : 0);
			else if(op.equals(">="))
				intval = (aval >= bval ? 1 : 0);
			else if(op.equals("=="))
				intval = (aval == bval ? 1 : 0);
			else if(op.equals("!="))
				intval = (aval != bval ? 1 : 0);
			else if(op.equals("^"))
				intval = aval ^ bval;
			else
				throw new BadOperationException("Unknown binary operation \""+op+"\" in NumExpression::eval()!");
		}

		// Apply appropriate bitmask to ensure range.
		long bitmask = 0xFFFFFFFFFFFFFFFFL;
		intval = intval & (bitmask >> (64-bits));

		evaluated = true;
		return intval;
	}

	/**
	 * Return a string representation of this IntExpression.  Should add parentheses as
	 * needed for order of operations.
	 * @return String containing IntExpression.
	 */
	public String toString()
	{
		if(prefix)
			return op+intval;
		if(unary)
			return "("+a.toString()+op+")";
		if(!complex)
			return ""+intval;
		else
			return " ( "+a.toString()+op+b.toString()+" ) ";
	}
}


/**
 * Need an object to store packsize (alignment) info in.
 */
class PackContainer
{
	protected Integer packsize;
	protected String label;

	/**
	 * Make a PackContainer knowing only the size.
	 * @param ps Alignment in bytes.  Can be 1, 2, 4, or 8.
	 * @exception InvalidParameterException if ps isn't a valid alignment
	 */
	PackContainer(int ps) throws InvalidParameterException
	{
		if(ps != 1 && ps != 2 && ps != 4 && ps != 8)
			throw new InvalidParameterException("Ack!  PackContainer refuses to take alignment values other than 1, 2, 4, and 8!  ps: "+ps);
		packsize = new Integer(ps);
		label = null;
	}

	/**
	 * Make a PackContainer knowing the size and a unique label.  For lines like this: 
	 * <code>#pragma pack(push, wininet, 4)</code>
	 * @param ps Alignment in bytes.  Can be 1, 2, 4, or 8.
	 * @param Label Text associated with this pack size.
	 * @exception InvalidParameterException if ps isn't a valid alignment
	 */
	PackContainer(int ps, String Label) throws InvalidParameterException
	{
		if(ps != 1 && ps != 2 && ps != 4 && ps != 8)
			throw new InvalidParameterException("Ack!  PackContainer refuses to take alignment values other than 1, 2, 4, and 8!  ps: "+ps+"  label: "+Label);
		packsize = new Integer(ps);
		label = Label;
	}

	/**
	 * Return pack size.
	 * @return int containing pack size.
	 */
	int getPackSize()
	{
		return packsize.intValue();
	}

	/**
	 * Return label for this pack size.
	 * @return label
	 */
	String getLabel()
	{
		return label;
	}

	/**
	 * Return whether this container has a label
	 * @return true if a label is present, else false;
	 */
	boolean hasLabel()
	{
		return label==null;
	}
}


/** 
 * Variable is a class to store the name and type of an argument to 
 * a function, as well as any modifiers that might apply.  This is strictly for storage.
 * I added support for some interesting keywords, but not support in the
 * output for all of them.
 * The idea is maybe users can add special rules for any special types they have
 * in toJavaString().
 */
class Variable
{
	public String Type;
	public String Name;
   protected Function ptrFunc;
	protected multiFieldDataStructure ptrData;
	protected Array ptrArray;
	protected static Hashtable TypeLUT;
	protected static Hashtable StructureLUT;
	protected static Hashtable StringTypes;
	protected NumExpression InitialValue;
	protected boolean is_var_arg;

	protected boolean is_Const;
	protected boolean is_Volatile;
	protected boolean is_Pointer;
	protected boolean is_Handle;
	protected boolean is_Reference;

	/**
	 * Construct a variable with a certain type and name.  Use for something like:
	 * <code>int x;</code>
	 * @param Type String containing the C type
	 * @param Name Name of this variable, if known.
	 */
	public Variable(String Type, String Name)
	{
		this.Type = Type;
		this.Name = Name;
		ptrFunc = null;
		ptrData = null;
		ptrArray = null;
		InitialValue = null;
		is_var_arg = false;
		if(Type == null) {
			System.out.println("Ack! Variable(Type,Name) doesn't want a null type!");
		}
		if(Type.startsWith("va_list") || Type.startsWith("Old-style vararg list")) {
			System.out.println("Found vararg type.");
			is_var_arg = true;
		}
		is_Const = false;
		is_Volatile = false;
		is_Pointer = false;
		is_Handle = false;
		is_Reference = false;
	}

	/**
	 * Make a Variable that wraps a pointer to a function.  Useful for members of a struct
	 * and function arguments.
	 * @param pfunc Function object.
	 */
	public Variable(Function pfunc)
	{
		StringBuffer type = new StringBuffer(pfunc.getReturnType() + " (" + pfunc.getName() + ") (");
		type.append(pfunc.argsToString());
		type.append(")");
		this.Type = type.toString();
		this.Name = "ptrToFunc";
		type = null;
		ptrFunc = pfunc;
		ptrData = null;
		ptrArray = null;
		InitialValue = null;
		is_var_arg = false;
		is_Const = false;
		is_Volatile = false;
		is_Pointer = true;		// A safe assumption here.
		is_Handle = false;
		is_Reference = false;
	}

	/**
	 * Make a Variable storing a multiFieldDataStructure.  Use this to represent structs
	 * and unions as members of structs or unions.
	 * @param s multiFieldDataStructure to use as source.
	 * @param name Name of the field or variable
	 */
	public Variable(multiFieldDataStructure s, String name)
	{
		Type = s.toString();
		Name = name;
		ptrFunc = null;
		ptrData = s;
		ptrArray = null;
		InitialValue = null;
		is_var_arg = false;
		is_Const = false;
		is_Volatile = false;
		is_Pointer = false;   // Could be a by-ref struct passed in...
		is_Handle = false;
		is_Reference = false;
	}

	/**
	 * Make a Variable storing an Array.  Use this to represent arrays as 
	 * members of structs or unions.
	 * @param a Array to use as source.
	 */
	public Variable(Array a)
	{
		Type = a.toString();
		this.Name = a.getName();
		ptrFunc = null;
		ptrData = null;
		ptrArray = a;
		InitialValue = null;
		is_var_arg = false;
		is_Const = false;
		is_Volatile = false;
		is_Pointer = true;	// Guess?
		is_Handle = false;
		is_Reference = false;
	}

	/**
	 * Clean up fields.
	 * @return No return value.
	 */
	public void finalizer()
	{
		Name = null;
		Type = null;
		ptrFunc = null;
		ptrData = null;
		ptrArray = null;
		InitialValue = null;
	}

	/**
	 * Is this Variable a wrapper for a Function?
	 * @return true if this wraps a Function; else false.
	 */
	public boolean isFunction()
	{
		return ptrFunc != null;
	}

	/**
	 * Is this Variable a wrapper for a multiFieldDataStructure?
	 * @return true if this wraps a multiFieldDataStructure; else false.
	 */
	public boolean ismultiFieldDataStructure()
	{
		return ptrData != null;
	}

	/**
	 * Is this Variable a wrapper for an Array?
	 * @return true if this wraps an Array; else false.
	 */
	public boolean isArray()
	{
		return ptrArray != null;
	}

	/**
	 * Is this Variable a wrapper for an Array?
	 * @return true if this wraps an Array; else false.
	 */
	public boolean isCharArray() throws InvalidParameterException
	{
		if(ptrArray != null) {
			if(!ptrArray.isString())
				return false;
			CharArray a = (CharArray) ptrArray;
			if(a==null)
				return false;
			else
				return true;
		}
		else
			return false;
	}

	/**
	 * Is this Variable a variable arguments list?  Should support both the "..." syntax
	 * as well as the va_list.
	 * @return true if this is a vararg parameter; else false
	 */
	public boolean isVarArg()
	{
		return is_var_arg;
	}

	/**
	 * Is this a const parameter or field?
	 * @return true if this variable is constant; else false.
	 */
	public boolean isConst()
	{
		return is_Const;
	}

	/**
	 * Is this a volatile variable or field?
	 * @return true if this Variable is volatile; else false.
	 */
	public boolean isVolatile()
	{
		return is_Volatile;
	}

	/**
	 * Is this a pointer parameter or field?
	 * @return true if this variable is a pointer; else false.
	 */
	public boolean isPointer()
	{
		return is_Pointer;
	}

	/**
	 * Is this a handle parameter or field?
	 * @return true if this variable is a handle; else false.
	 */
	public boolean isHandle()
	{
		return is_Handle;
	}

	/**
	 * Is this parameter passed by reference?  Or is this structure embedded into another structure?
	 * <p>Examples:  Both <code>void func(int & x_byref);</code> and <code>struct { POINT pt; };</code> 
	 * should have this flag set to true.
	 * @return true if this variable is passed by reference or if this structure is embedded in another; else false.
	 */
	public boolean isReference()
	{
		return is_Reference;
	}

	/**
	 * Set const flag to a value.
	 * @param v What to set the const flag to.
	 * @return No return value.
	 * @exception InvalidParameterException if variable is set as both const and volatile
	 */
	public void setConst(boolean v) throws InvalidParameterException
	{
		if(is_Volatile && v)
			throw new InvalidParameterException("Variables can't be both const and volatile!");
		is_Const = v;
	}

	/**
	 * Set volatile flag to a value.
	 * @param v What to set the volatile flag to.
	 * @return No return value.
	 * @exception InvalidParameterException if variable is set as both const and volatile
	 */
	public void setVolatile(boolean v) throws InvalidParameterException
	{
		if(is_Const && v)
			throw new InvalidParameterException("Variables can't be both const and volatile!");
		is_Volatile = v;
	}

	/**
	 * Set pointer flag to a value.
	 * @param v What to set the pointer flag to.
	 * @return No return value.
	 */
	public void setPointer(boolean v)
	{
		is_Pointer = v;
	}

	/**
	 * Set handle flag to a value.
	 * @param v What to set the handle flag to.
	 * @return No return value.
	 */
	public void setHandle(boolean v)
	{
		is_Handle = v;
	}
	
	/**
	 * Set reference flag to a value.
	 * @param v What to set the reference flag to.
	 * @return No return value.
	 */
	public void setReference(boolean v)
	{
		is_Reference = v;
	}

	/**
	 * Set the Initial value of this variable.  Useful for default arguments or member 
	 * initialization within a struct or class.
	 * @param expr NumExpression to set initial value to.
	 * @return No return value.
	 */
	public void setInitialValue(NumExpression expr)
	{
		InitialValue = expr;
	}

	/**
	 * Get the Function this Variable wraps.
	 * @return This Variable's Function.
	 * @exception InvalidParameterException if it wasn't a function wrapper.
	 */
	public Function getFunction() throws InvalidParameterException
	{
		if(ptrFunc == null)
			throw new InvalidParameterException("Variable wasn't a function wrapper!");
		return ptrFunc;
	}

	/**
	 * Get the data structure this Variable wraps.
	 * @return This Variable's multiFieldDataStructure.
	 * @exception InvalidParameterException if it wasn't a data structure wrapper.
	 */
	public multiFieldDataStructure getmultiFieldDataStructure() throws InvalidParameterException
	{
		if(ptrData == null)
			throw new InvalidParameterException("Variable wasn't a multiFieldDataStructure wrapper!");
		return ptrData;
	}

	/**
	 * Get the Array this Variable wraps.
	 * @return This Variable's Array.
	 */
	public Array getArray()
	{
		return ptrArray;
	}

	/**
	 * Convert this Variable into a String containing a C representation.
	 * @return String containing C representation of this parameter.
	 */
	public String toString()
	{
		if(ptrFunc != null)
			return ptrFunc.toString();
		if(ptrData != null)
			return ptrData.toString();
		if(ptrArray != null)
			return ptrArray.toString();
		return Type + " " + Name;
	}

	/**
	 * Convert this Variable to Java and return it as a String.  This one is for converting
	 * types in function prototypes into Java.  See the Field.toJavaString() for members
	 * of structures.
	 * @return String containing Java representation.
	 * @see Field#toJavaString()
	 */
	public String toJavaString() throws InvalidParameterException
	{
		if(TypeLUT == null)
			throw new InvalidParameterException("TypeLUT was null in toJavaString!");
		if(StructureLUT == null)
			throw new InvalidParameterException("StructureLUT was null in toJavaString!");

		if(ptrFunc != null) {
			System.out.println("Ack! Functions won't convert to Java strings automatically!");
			return ptrFunc.toString();
		}
		if(ptrData != null) {
			// This code needs to be fixed up for function-only usage...
			String out;
			String dataname = ptrData.getName();
			String mods = ptrData.getModifiers()!=null ? " /* " + ptrData.getModifiers() + " */" : "";
			if(dataname.equals(ptrData.anonymous)) {
				out = "// anonymous " + (ptrData.isStruct() ? "struct" : "union") + " {\r\n";
				for(int i=0; i<ptrData.numFields(); i++)
					out = out + "\t\t// " + ptrData.getField(i).toJavaString() + ";\r\n";
				out = out + "\t//} " + Name;
			} else
				out = "public " + dataname + mods + "\t" + Name;
			return out;
		}
		if(ptrArray != null)
			return ptrArray.toJavaString(false);

		String jType = (String) TypeLUT.get(Type);
		if(jType == null) {
			multiFieldDataStructure data = (multiFieldDataStructure) StructureLUT.get(Type);
			if(data!=null)
				jType = data.toJavaString(false);
		}
		// Sometimes spaces appear in type names...
		if(jType == null) {
			StringTokenizer st = new StringTokenizer(Type);
			String word = st.nextToken();
			jType = (String) TypeLUT.get(word);
			if(st.hasMoreElements()) {
				word = st.nextToken();
				if(word.equals("*")) {
					is_Pointer = true;
					System.out.println("Ack!  Special Variable.toJavaString array hack!");
				}
			}
			if(is_Pointer)
				jType = jType + "[]";
		}

		if(jType == null) {
			System.out.println("Unparsible C type: " + Type + " \tTypeLUT size was "+TypeLUT.size());
			System.out.println("TypeLUT.get("+Type+") = "+(String) TypeLUT.get(Type));
			jType = Type;
		}
		String header = "public ";
		if(isVarArg())
			header = "// "+header;

		return header + jType + "\t" + Name;
	}

	/**
	 * Set static Type Lookup Table parameter.  Necessary to convert from C to Java.
	 * Also sets TypeLUT for Arrays and multiFieldDataStructures.
	 * @param TypeTable Primitive Hashtable.
	 * @see Parser.html#PopulateTypeLUT
	 */
	public static void setPrimitiveTable(Hashtable TypeTable)
	{
		TypeLUT = TypeTable;
		Array.setPrimitiveTable(TypeTable);
		multiFieldDataStructure.setPrimitiveTable(TypeTable);
	}

	/**
	 * Set static Structure Lookup Table parameter.  Necessary to convert from C to Java.
	 * Also sets StructureLUT for Arrays and multiFieldDataStructures.
	 * @param StructureTable Structure Lookup Table from Parser.
	 */
	public static void setStructureTable(Hashtable StructureTable)
	{
		StructureLUT = StructureTable;
		Array.setStructureTable(StructureTable);
		multiFieldDataStructure.setStructureTable(StructureTable);
	}

	/**
	 * Set static String Lookup Table parameter.  Necessary to convert from C to Java.
	 * Also sets StringTypes for Arrays.
	 * @param StringTable String types Hashtable.
	 * @see Parser.html#SetStringTypes
	 */
	public static void setStringTable(Hashtable StringTable)
	{
		StringTypes = StringTable;
		Array.setStringTable(StringTable);
	}
}


/**
 * This class is used to wrap fields of structs, classes, and unions.  There need to be a few extra
 * settings for protection and obscure C++ keywords.
 */
class Field extends Variable
{
	protected int protection;
	protected boolean is_Static;
	protected boolean is_Virtual;
	protected boolean is_Mutable;

	public static final int PUBLIC = 1;
	public static final int PROTECTED = 2;
	public static final int PRIVATE = 3;

	/**
	 * Construct a Field with a certain type and name within a structure.  Use for something like:
	 * <code>struct { int x; }</code>
	 * @param Type String containing the C type
	 * @param Name Name of this variable, if known.
	 */
	public Field(String fieldtype, String fieldname)
	{
		super(fieldtype, fieldname);
		is_Static = false;
		is_Virtual = false;
		is_Mutable = false;
	}

	/**
	 * Make a Field that wraps a pointer to a function.  Useful for members of a struct
	 * and function arguments.
	 * @param pfunc Function object.
	 */
	public Field(Function pfunc)
	{
		super(pfunc);
		is_Static = false;
		is_Virtual = false;
		is_Mutable = false;
	}

	/**
	 * Make a Field storing an Array.  Use this to represent arrays inside structs or unions.
	 * @param a Array to use as source.
	 */
	public Field(Array a)
	{
		super(a);
		is_Static = false;
		is_Virtual = false;
		is_Mutable = false;
	}
	
	/**
	 * Make a Field storing a multiFieldDataStructure.  Use this to represent structs
	 * and unions as members of structs or unions.
	 * @param s multiFieldDataStructure to use as source.
	 * @param name Name of this field.
	 */
	public Field(multiFieldDataStructure s, String name)
	{
		super(s, name);
		is_Static = false;
		is_Virtual = false;
		is_Mutable = false;
	}

	/**
	 * Is this a static member?
	 * @return true if this member is static; else false
	 */
	public boolean isStatic()
	{
		return is_Static;
	}

	/**
	 * Is this a virtual member function?
	 * @return true if this is a virtual function; else false
	 */
	public boolean isVirtual()
	{
		return is_Virtual;
	}

	/**
	 * Is this a mutable member?
	 * @return true if this member is mutable; else false
	 */
	public boolean isMutable()
	{
		return is_Mutable;
	}

	/**
	 * Set static flag to a value.
	 * @param v What to set the static flag to.
	 * @return No return value.
	 */
	public void setStatic(boolean v)
	{
		is_Static = v;
	}

	/**
	 * Set virtual flag to a value.  Only works for virtual functions!
	 * @param v What to set the static flag to.
	 * @return No return value.
	 * @exception InvalidParameterException if this isn't a member function, since virtual only applies to functions.
	 */
	public void setVirtual(boolean v) throws InvalidParameterException
	{
		if(v==true && !ismultiFieldDataStructure())
			throw new InvalidParameterException("Only functions can be virtual!");
		is_Virtual = v;
	}

	/**
	 * Set mutable flag to a value.
	 * @param v What to set the mutable flag to.
	 * @return No return value.
	 */
	public void setMutable(boolean v)
	{
		is_Mutable = v;
	}

	/**
	 * Set the protection of this Field.
	 * @param newprot What to set the protection to.
	 * @return No return value.
	 * @exception InvalidParameterException if newprot isn't PUBLIC, PRIVATE, or PROTECTED.
	 */
	public void setProtection(int newprot) throws InvalidParameterException
	{
		if(newprot != PUBLIC && newprot != PRIVATE && newprot != PROTECTED)
			throw new InvalidParameterException("Invalid protection sent to Field.setProtection("+newprot+")!");
		protection = newprot;
	}

	/**
	 * Returns Java protection string for corresponding C protection.
	 * @param CAccess C protection (ie, Variable.PUBLIC)
	 * @return string containing Java access permissions
	 * @exception InvalidParameterException if CAccess isn't PUBLIC, PRIVATE, or PROTECTED
	 */
	public static final String getJavaAccess(int CAccess) throws InvalidParameterException
	{
		if(CAccess == PUBLIC)
			return "public ";
		else if(CAccess == PROTECTED)
			return "protected ";
		else if(CAccess == PRIVATE)
			return "private ";
		else
			throw new InvalidParameterException("Unknown access permissions in Variable.getJavaAccess("+CAccess+")");
	}

	/**
	 * Convert this Field to Java and returns it as a String.  Will apply special 
	 * J/Direct rules for what can and can't be inside a struct or union.  Used for
	 * members of structures - Variable.toJavaString() handles function prototypes.
	 * @return String containing Java representation.
	 * @see Variable#toJavaString()
	 */
	public String toJavaString() throws InvalidParameterException
	{
		if(TypeLUT == null)
			throw new InvalidParameterException("TypeLUT was null in toJavaString!");
		if(StructureLUT == null)
			throw new InvalidParameterException("StructureLUT was null in toJavaString!");

		if(ptrFunc != null) {
			System.out.println("Ack! Functions won't convert to Java strings automatically!  Call ConvertFunction!");
			return ptrFunc.toString();
		}
		if(ptrData != null) {
			// Need to print a one-line summary here.
			String out;
			String dataname = ptrData.getName();
			String mods = ptrData.getModifiers()!=null ? " /* " + ptrData.getModifiers() + " */" : "";
			if(dataname.equals(ptrData.anonymous)) {
				out = "// anonymous " + (ptrData.isStruct() ? "struct" : "union") + " {\r\n";
				for(int i=0; i<ptrData.numFields(); i++)
					out = out + "\t\t// " + ptrData.getField(i).toJavaString() + ";\r\n";
				out = out + "\t//} " + Name;
			} 
			else if(is_Pointer)
				out = getJavaAccess(protection) + dataname + mods + "\t" + Name;
			else
				out = "// BUGBUG: by-val structure!  "+getJavaAccess(protection) + dataname + mods + "\t" + Name;
			return out;
		}
		if(ptrArray != null)
			return ptrArray.toJavaString(true);

		// Kludge for bitfields.  Don't print them.
		if(Name==null) {
			return "// "+Type+" bitfield. BUGBUG";
		}

		String jType = (String) TypeLUT.get(Type);
		if(jType == null) {
			multiFieldDataStructure data = (multiFieldDataStructure) StructureLUT.get(Type);
			if(data!=null)
				jType = data.toJavaString(true);
		}
		// Sometimes spaces appear in type names...
		if(jType == null) {
			StringTokenizer st = new StringTokenizer(Type);
			String word = st.nextToken();
			jType = (String) TypeLUT.get(word);
			if(st.hasMoreElements()) {
				word = st.nextToken();
				if(word.equals("*")) {
					is_Pointer = true;
					System.out.println("Ack!  Special Field.toJavaString array hack!");
				}
			}
			if(is_Pointer)
				jType = jType + "[]";
		}

		if(jType == null) {
			System.out.println("Unparsible C type: " + Type + " \tTypeLUT size was "+TypeLUT.size());
			System.out.println("TypeLUT.get("+Type+") = "+(String) TypeLUT.get(Type));
			jType = Type;
		}
		String header = getJavaAccess(protection);
		if(isVarArg())
			header = "// "+header;
		// Handle field modifiers
		if(is_Static)
			header = header+"static ";
		if(is_Const)
			header = header+"final ";
		if(is_Volatile)
			header = header+"volatile ";

		// Three rules for being inside structures, then a special case.
		// Convert callbacks to ints.  We tell users to do this, so we should do it.
		// StringBuffers must be converted to Strings.
		// Strings should be converted to ints for now, but put C type in comments.
		// LPBYTE -> int.  No non-embedded byte[]   We don't know what they represent - 
		//      usually structs or a variant type.
		if(jType.equals(Parser.CallbackString))
			jType = "int /* BUGBUG: Callback */";
		else if(jType.equals("StringBuffer"))
			jType = "String";
		else if(Parser.Comment_Variant_Types && Type.equals("LPBYTE"))
			jType = "int /* BUGBUG: LPBYTE */";

		if(jType.equals("String"))
			jType = "int /* "+Type+" */";

		// Handle an initial value (or default argument)
		String trailer = "";
		if(InitialValue != null)
			trailer = " = "+InitialValue.eval();

		return header + jType + "\t" + Name + trailer;
	}
}


/**
 * Represents an Array of some type, with any length.  A CharArray is a special case 
 * (a subclass) of this Array class because of the special String handling rules.
 * @see CharArray
 */
class Array
{
	protected boolean lengthknown;
	protected int length;
	protected String Type;
	protected String name;
	protected Array ptrArray;
	protected static Hashtable TypeLUT;
	protected static Hashtable StructureLUT;
	protected static Hashtable StringTypes;

	/**
	 * Makes an array of unknown length
	 * @param name Name of the Array
	 */
	public Array(String name)
	{
		this.name = name;
		lengthknown = false;
		Type = null;
		length = 0;
		ptrArray = null;
	}

	/**
	 * Makes an array of fixed length.
	 * @param name Name of the Array
	 * @param numElements Number of elements in the array.
	 */
	public Array(String name, int numElements)
	{
		this.name = name;
		lengthknown = true;
		Type = null;
		length = numElements;
		ptrArray = null;
	}

	/**
	 * Makes an array of arrays
	 * @param nestedArray array to make an array of.
	 */
	public Array(Array nestedArray)
	{
		this.name = "<wrapping array "+nestedArray.getName()+">";
		lengthknown = false;
		Type = nestedArray.getType()+"[]";
		length = 0;
		ptrArray = nestedArray;
	}

	/**
	 * Makes an array of arrays, knowing this dimension.
	 * @param nestedArray array to make an array of.
	 * @param len number of elements in this array.
	 */
	public Array(Array nestedArray, int len)
	{
		this.name = "<wrapping array "+nestedArray.getName()+">";
		lengthknown = false;
		Type = nestedArray.getType()+"[]";
		length = len;
		ptrArray = nestedArray;
	}

	/**
	 * Clean up fields.
	 * @return No return value.
	 */
	public void finalizer()
	{
		Type = null;
		name = null;
		ptrArray = null;
	}

	/**
	 * Get the Array's name.
	 * @return String containing name of this Array.
	 */
	public String getName()
	{
		return name;
	}

	/**
	 * Sets the name of a Array.
	 * @param newName new name for this Array.
	 * @return No return value.
	 */
	public void setName(String newName)
	{
		name = new String(newName);
	}

	/**
	 * Get this Array's type.
	 * @return String containing Type.
	 */
	public String getType()
	{
		return Type;
	}

	/**
	 * Set this Array's type.
	 * @param newType new type of this Array.
	 * @return No return value.
	 * @exception InvalidParameterException if StringTypes isn't set yet and you call CharArray.setType
	 */
	public void setType(String newType) throws InvalidParameterException
	{
		Type = newType;
	}

	/**
	 * Get the number of elements in this array.
	 * @return length as number of elements.
	 */
	public int getLength()
	{
		if(!lengthknown)
			return -1;
		else
			return length;
	}

	/**
	 * Is this Array a String array, or one dealing with Strings?
	 * @return true if its type involves strings at all.
	 */
	public boolean isString() throws InvalidParameterException
	{
		if(StringTypes == null)
			throw new InvalidParameterException("You must set Array::StringTypes before calling isString()!");
		if(Type == null)
			throw new InvalidParameterException("You must set Array::Type before calling Array::isString()!");

		if(ptrArray != null)
			return ptrArray.isString();
		else
			return StringTypes.containsKey(Type);
	}

	public String toString()
	{
		return Type + "\t" + name + "[" + length + "];";
	}

	public String toJavaString(boolean isInsideStruct) throws InvalidParameterException
	{
		boolean printBrackets = true;
		String jType = (String) TypeLUT.get(Type);

		if(ptrArray != null) {
			jType = ptrArray.toJavaString(isInsideStruct);
		}

		if(jType == null) {
			multiFieldDataStructure data = (multiFieldDataStructure) StructureLUT.get(Type);
			if(data!=null)
				jType = data.toJavaString(true);
		}
		if(jType == null) {
			System.out.println("Unparsible C type: " + Type);
			jType = Type;
		}

		// Last-ditch convert from char[] to String...
		if(jType.equals("char")) {
			jType = "StringBuffer";
			printBrackets = false;
		}

		// In Java, the length of the array isn't part of the array type.  We always
		// store references.  But if this is an embedded array of size greater than
		// one, we want to use @dll.structmap().  
		String out = "";
		if(isInsideStruct) {
			if(jType.equals("StringBuffer"))
				jType = "String";
			if(lengthknown) {
				if(jType.equals("String"))
					out = "/** @dll.structmap([type=TCHAR["+length+"]]) */\r\n\t";
				else
					out = "/** @dll.structmap([type=FIXEDARRAY, size="+length+"]) */\r\n\t";
			}
		}

		// One last thing... Don't print out int[][].  Doesn't work in Java.  (void** in C)
		if(jType.equals("int[][]"))
			jType = "int";

		// Should probably be changed to handle access permissions sometime...
		out = out + "public "+jType + "\t" + name;
		if(printBrackets)
			out = out + "[]";
		return out;
	}

	/**
	 * Set static Type Lookup Table parameter.  Necessary to convert from C to Java.
	 * @param TypeTable Primitive Hashtable.
	 * @see Parser.html#PopulateTypeLUT
	 */
	public static void setPrimitiveTable(Hashtable t)
	{
		TypeLUT = t;
	}

	/**
	 * Set static Structure Lookup Table parameter.  Necessary to convert from C to Java.
	 * @param StructureTable Structure Lookup Table from Parser.
	 */
	public static void setStructureTable(Hashtable s)
	{
		StructureLUT = s;
	}

	/**
	 * Set static String Lookup Table parameter.  Necessary to convert from C to Java.
	 * @param StringTable String types Hashtable.
	 * @see Parser.html#SetStringTypes
	 */
	public static void setStringTable(Hashtable s)
	{
		StringTypes = s;
	}
}


/**
 * Used to represent Strings, which are always difficult because they can be Unicode or
 * ASCII strings.  There are additional rules for outputting them when their length is
 * known and they're embedded in a struct, etc.
 */
class CharArray extends Array {
	protected boolean is_Unicode_String;

	/**
	 * Build a character array of fixed length.
	 * @param name Name of this char array.
	 * @param length number of characters in array.
	 */
	public CharArray (String name, int length)
	{
		super(name, length);
		is_Unicode_String = true;
	}

	/**
	 * Build a character array of unknown length.
	 * @param name Name of this char array.
	 */
	public CharArray (String name)
	{
		super(name);
		is_Unicode_String = true;
	}

	/**
	 * Is this an array of characters?
	 * @return true if this is a C string, else false.
	 */
	public boolean isString() throws InvalidParameterException
	{
		return true;
	}

	/**
	 * Set the type of this string and determine character width.
	 * @param newType new type for this Char array.
	 * @return No return value.
	 * @exception InvalidParameterException if StringTypes isn't set yet.
	 */
	public void setType(String newType) throws InvalidParameterException
	{
		Type = newType;
		if(StringTypes==null)
			throw new InvalidParameterException("Cannot modify Char array type without setting Array.StringTypes first!");
		String width = (String) StringTypes.get(Type);
		if(width.equals("unicode"))
			is_Unicode_String = true;
		else if(width.equals("ansi"))
			is_Unicode_String = false;
	}

	/**
	 * Is this string a Unicode String (char width is 2 bytes)
	 * @return true if type is a Unicode type; else false
	 */
	public boolean isUnicode()
	{
		return is_Unicode_String;
	}

	/**
	 * Is this string an ASCII String (char width is 1 byte)
	 * @return true if type is an ASCII type; else false
	 */
	public boolean isASCII()
	{
		return !is_Unicode_String;
	}

	/**
	 * Convert CharArray to Java.
	 * @param isInsideStruct is this a member of a structure?
	 * @return String containing Java representation of this array.
	 * @exception InvalidParameterException if CharArray isn't set up properly.
	 */
	public String toJavaString(boolean isInsideStruct) throws InvalidParameterException {
		if(Type == null)
			throw new InvalidParameterException("Must set a CharArray's type before converting to a Java string!");

		String jType = (String) TypeLUT.get(Type);
		if(jType==null)
			jType = ptrArray.toJavaString(isInsideStruct);

//		StringTypes.get(Type);

		// Should probably be changed to handle access permissions sometime...
		String header="\tpublic ";

		// We can only have Strings inside a struct, no StringBuffers. 
		// Strings have a special @dll.structmap syntax.
		if(isInsideStruct) {
			jType = "String";
			if(lengthknown)
				header = "/** @dll.structmap([type=TCHAR["+length+"]]) */\r\n"+header;
		}

		return header + jType + "\t" + name;
	}
}


/**
 * base class for Struct and Union
 */
abstract class multiFieldDataStructure
{
	protected String name;         // struct's primary typedef'ed name
	protected Vector otherNames;   // typedef'ed names.
	protected Vector fields;       // holds Variables.
	protected int packsize;        // Alignment setting.  { 1, 2, 4, 8 }
	protected boolean hasUnion;    // whether there's a union in this data structure
	protected boolean hasStruct;   // whether there's an embedded struct in this data structure
	protected boolean hasArray;    // whether there's an array in this data structure.
	protected boolean merged;		 // whether this has been merged with its ASCII or Unicode equivalent.
	protected boolean used;        // whether a function actually uses this structure.
	protected boolean notComplete; // Need to add to StructureLUT while incomplete to handle recursive structs.
	protected String modifiers;    // modifiers like volatile
	public static String anonymous = "anonymous_data_structure";
	protected static Hashtable TypeLUT;
	protected static Hashtable StructureLUT;
	protected static final int JavaDefaultPackSize = 8;
	protected static final int CDefaultPackSize = 8;   	// VC++ defaults to 8
	
	/** 
	 * Make a new multiFieldDataStructure object, giving it a name.
	 * @param name Primary name of the struct or null if not named.
	 * @return a new Struct.
	 */
	public multiFieldDataStructure(String name)
	{
		if(name == null)
			this.name = anonymous;
		else
			this.name = name;
		otherNames = null;
		fields = new Vector(4, 4);
		packsize = CDefaultPackSize;
		hasUnion = false;
		hasStruct = false;
		hasArray = false;
		merged = false;
		notComplete = false;
		modifiers = null;
		used = false;
	}

	public void finalizer()
	{
		fields = null;
		otherNames = null;
		name = null;
		modifiers = null;
	}

	/**
	 * Tells whether this is a union or not.
	 * @return true if this multiFieldDataStructure is a union; else false
	 */
	abstract public boolean isUnion();

	/**
	 * Tells whether this is a struct or not.
	 * @return true if this multiFieldDataStructure is a struct; else false
	 */
	abstract public boolean isStruct();

	/**
	 * Converts this to its string representation in C syntax.  Must be overridden.
	 * @return String containing the C representation of this data structure.
	 */
	abstract public String toString();

	/**
	 * Converts this to its string representation in Java syntax.  Must be overridden.
	 * @param isInsideStruct if this is inside a struct or a union
	 * @return String containing the Java representation of this data structure.
	 * @throws InvalidParameterException if TypeLUT or StructureLUT haven't been set.
	 */
	abstract public String toJavaString(boolean isInsideStruct) throws InvalidParameterException;

	/**
	 * Get the multiFieldDataStructure's name.
	 * @return String containing name of this multiFieldDataStructure.
	 */
	public final String getName()
	{
		return name;
	}

	/**
	 * Sets the name of a multiFieldDataStructure.
	 * @param newName new name for this multiFieldDataStructure.
	 * @return No return value.
	 */
	public final void setName(String newName)
	{
		name = newName;
	}

	/**
	 * Set whether this structure has been merged with its ASCII or Unicode counterpart.
	 * Will stick "auto" in the @dll.struct line.
	 * @param val true if this is the structure that survived the merge
	 * @return No return value.
	 */
	public void setMerged(boolean val)
	{
		merged = val;
	}

	/**
	 * whether this structure is used anywhere.
	 * @return true if its used, false if not.
	 */
	public boolean isUsed()
	{
		return used;
	}

	/**
	 * Tell this structure its being used.
	 * @return No return value.
	 */
	public void Use()
	{
		if(!used) {
			used = true;
			for(int i=0; i<fields.size(); i++) {
				Variable v = (Variable) fields.elementAt(i);
				if(v!=null && v.ismultiFieldDataStructure()) {
					try {
						multiFieldDataStructure data = (multiFieldDataStructure) v.getmultiFieldDataStructure();
						data.Use();
					}
					catch (InvalidParameterException e) {}
				}
			}
		}
	}

	/**
	 * Gets the modifiers for this data structure
	 * @return String of modifiers for this structure.
	 */
	public String getModifiers()
	{
		return modifiers;
	}

	/**
	 * Sets the modifiers for this data structure
	 * @param mod new string of modifiers.
	 * @return No return value.
	 */
	public void setModifiers(String newMods)
	{
		modifiers = newMods;
	}

	/**
	 * Adds the modifier to the other modifiers already set for this data structure
	 * @param mod new modifier.
	 * @return No return value.
	 */
	public void addModifier(String newMod)
	{
		if(modifiers == null)
			modifiers = newMod;
		else
			modifiers = modifiers + " " + newMod;
	}

	/**
	 * Get the multiFieldDataStructure's pack size.
	 * @return Pack size of this multiFieldDataStructure.
	 */
	public int getPackSize()
	{
		return packsize;
	}

	/**
	 * Sets the packing size of a multiFieldDataStructure.  Says that the alignment 
	 * should be 1, 2, 4 or 8 bytes.
	 * @param newPackSize new alignment for this multiFieldDataStructure.
	 * @return No return value.
	 * @exception InvalidParameterException if newPackSize isn't 1, 2, 4, or 8 bytes.
	 */
	public void setPackSize(int newPackSize) throws InvalidParameterException
	{
		if(newPackSize != 1 && newPackSize != 2 && newPackSize != 4 && newPackSize != 8)
			throw new InvalidParameterException("setPackSize accepts only 1, 2, 4, or 8 bytes, not " + newPackSize);
		packsize = newPackSize;
	}

	/**
	 * Tell whether we have the complete definition of the structure or if we only have 
	 * a reference to the structure existing.  Specifically, an incomplete struct would
	 * look like this:
	 * <code struct An_Incomplete_Struct;</code>
	 * @return No return value.
	 */
	public boolean isComplete()
	{
		return !notComplete;
	}

	/**
	 * Set the flag telling whether this structure is completely defined or not.
	 * For structs that only have prototypes but no actual definition, it should
	 * not be complete.  Code I'm thinking of specifically:
	 * <code>struct An_Incomplete_Struct;</code>
	 * @param val true if this is a complete struct, else false.
	 * @return No return value.
	 */
	public void setComplete(boolean val)
	{
		notComplete = !val;
	}

	/**
	 * Returns whether the multiFieldDataStructure has a union in it, being 
	 * harder to convert.
	 * @return true if a union field exists; else false
	 */
	public boolean containsUnion()
	{
		return hasUnion;
	}

	/**
	 * Returns whether the multiFieldDataStructure has an embedded struct in it, 
	 * being harder to convert.
	 * @return true if at least one field is a struct; else false
	 */
	public boolean containsStruct()
	{
		return hasStruct;
	}

	/**
	 * Returns whether the multiFieldDataStructure has a union in it, being 
	 * harder to convert.
	 * @return true if at least one field is an array; else false
	 */
	public boolean containsArray()
	{
		return hasArray;
	}

	/**
	 * Determine if there's a unicode string in this multiFieldDataStructure.
	 * @return true if there is a Unicode string, else false.
	 */
	public boolean containsUnicodeString()
	{
		boolean val = false;
		for(int i=0; i<fields.size() && !val; i++) {
			try {
			Variable v = (Variable) fields.elementAt(i);
			if(v.isCharArray()) {
				CharArray a = (CharArray) v.getArray();
				if(a.isUnicode())
					val = true;
			}
			}
			catch (InvalidParameterException ipe) {
				System.out.println("Caught InvalidParameterException: "+ipe);
				ipe.printStackTrace();
			}
		}
		return val;
	}

	/**
	 * Adds another name for the data structure.  Simulates typedef's.  Creates otherNames
	 * vector if it doesn't already exist.
	 * @param altName An alternate name for this multiFieldDataStructure.
	 * @return No return value.
	 */
	public void addAltName(String altName)
	{
		if(otherNames == null)
			otherNames = new Vector(2, 2);
		otherNames.addElement(altName);
	}

	/**
	 * Returns the number of alternate names for this data structure.
	 * @return Number of alternate names for this multiFieldDataStructure.
	 */
	public int numAltNames()
	{
		if(otherNames == null)
			return 0;
		return otherNames.size();
	}
	
	/**
	 * Returns the alternate name you ask for.
	 * @param which Which alternate name you want.
	 * @return The which'th alternate name.
	 */
	public String getAltName(int which)
	{
		return (String) otherNames.elementAt(which);
	}

	/**
	 * Adds a Field to the multiFieldDataStructure.  Call in order fields appear in 
	 * the C data type.
	 * @param field Field holding the type and name of a new field.
	 * @return No return value.
	 * @exception InvalidParameterException if field is null.
	 */
	public void addField(Field field) throws InvalidParameterException
	{
		if(field==null)
			throw new InvalidParameterException("addField(Variable) won't accept null Variables!");
		if(field.ismultiFieldDataStructure()) {
			multiFieldDataStructure data = field.getmultiFieldDataStructure();
			if(data == null)
				throw new InvalidParameterException("addField(Variable) was passed an invalid data structure wrapper!");
			hasUnion = hasUnion | data.isUnion() | data.containsUnion();
			hasStruct = hasStruct | data.isStruct() | data.containsStruct();
			hasArray = hasArray | data.containsArray();
		}
		if(field.isArray()) {
			Array a = field.getArray();
			if(a == null)
				throw new InvalidParameterException("addField(Variable) was passed an invalid array wrapper!");
			hasArray = true;
		}
		fields.addElement(field);
	}

	/**
	 * Adds a complex field to the multiFieldDataStructure.  Call in order fields appear in 
	 * the C data type.
	 * @param field multiFieldDataStructure to be added into data structure.
	 * @return No return value.
	 * @exception InvalidParameterException if field is null
	 */
	public void addField(multiFieldDataStructure field, String fname) throws InvalidParameterException
	{
		if(field == null)
			throw new InvalidParameterException("addField(multiFieldDataStructure) won't accept a null field!");
		hasUnion = hasUnion | field.isUnion() | field.containsUnion();
		hasStruct = hasStruct | field.isStruct() | field.containsStruct();
		hasArray = hasArray | field.containsArray();
		fields.addElement(new Field(field, fname));
	}

	/**
	 * Returns the number of fields in this multiFieldDataStructure.
	 * @return Number of fields in this multiFieldDataStructure.
	 */
	public int numFields()
	{
		return fields.size();
	}

	/**
	 * Returns a Field holding the nth field of this multiFieldDataStructure
	 * @param n Number of field to return.
	 * @return Field containing nth field of the multiFieldDataStructure.
	 * @exception InvalidParameterException if n is larger than the number of fields.
	 */
	public Field getField(int n) throws InvalidParameterException
	{
		if(n > fields.size())
			throw new InvalidParameterException("getField called with out of range index!  There aren't that many fields!");
		Field f = (Field) fields.elementAt(n);
		return f;
	}

	/**
	 * Set static Type Lookup Table parameter.  Necessary to convert from C to Java.
	 * @param TypeTable Primitive Hashtable.
	 * @see Parser.html#PopulateTypeLUT
	 */
	public static void setPrimitiveTable(Hashtable t)
	{
		TypeLUT = t;
	}

	/**
	 * Set static Structure Lookup Table parameter.  Necessary to convert from C to Java.
	 * @param StructureTable Structure Lookup Table from Parser.
	 */
	public static void setStructureTable(Hashtable s)
	{
		StructureLUT = s;
	}
}


class multiFieldDataStructureCompare implements Comparison
{
	/**
	 * Compares two objects that hopefully are multiFieldDataStructures.  Compares based on
	 * name of the struct, then by some collection of other rules if there are two structs
	 * with the same name.
	 * @param a A multiFieldDataStructure to compare
	 * @param b A multiFieldDataStructure to compare
	 * @return 0 if they're exactly equal, a negative value if a < b, and a positive value if a > b
	 */
	public int compare(Object a, Object b)
	{
		multiFieldDataStructure ma = (multiFieldDataStructure) a;
		multiFieldDataStructure mb = (multiFieldDataStructure) b;
		int res = ma.getName().compareTo(mb.getName());
		if(res == 0) { // give preference to struct over union if they have same name.
			if(ma.isStruct() && mb.isStruct())
				return res;
			else if(ma.isStruct())
				return -1;
			else if(mb.isStruct())
				return +1;
		}
		return res;
	}
}


class Struct extends multiFieldDataStructure
{
	/** 
	 * Make a new Struct object, giving it a name.
	 * @param name Primary name of the struct
	 * @return a new Struct.
	 */
	public Struct(String name)
	{
		super(name);
	}

	/**
	 * Tells whether this is a union or not.
	 * @return true if this multiFieldDataStructure is a union; else false
	 */
	public boolean isUnion()
	{
		return false;
	}

	/**
	 * Tells whether this is a struct or not.
	 * @return true if this multiFieldDataStructure is a struct; else false
	 */
	public final boolean isStruct()
	{
		return true;
	}

	/**
	 * Converts Struct to its string representation in C syntax.  Must be overridden.
	 * @return String containing the C representation of this data structure.
	 */
	public String toString()
	{
		String str = "struct " + name + (modifiers!=null ? " "+modifiers : "") + " {\r\n";
		for(int i=0; i<fields.size(); i++) {
			Variable var = (Variable) fields.elementAt(i);
			str = str + "\t" + var.Type + "\t" + var.Name + ";\r\n";
		}
		return str;
	}

	/**
	 * Converts Struct to its string representation in Java syntax.  Must be overridden.
	 * @param isInsideStruct if this is inside a struct or a union
	 * @return String containing the Java representation of this data structure.
	 */
	public String toJavaString(boolean isInsideStruct) throws InvalidParameterException
	{
		if(TypeLUT == null)
			throw new InvalidParameterException("TypeLUT was null in toJavaString!");
		if(StructureLUT == null)
			throw new InvalidParameterException("StructureLUT was null in toJavaString!");

		String mods = "";
		if(modifiers!=null)
			mods = " /* "+modifiers+" */";
		String args = "";
		if(packsize != JavaDefaultPackSize)
			args = "pack="+packsize;

		// If we've merged this structure with an ASCII one, use the auto keyword.
		// If not, check for using embedded unicode strings and use unicode keyword.
		if(merged) {  // if merged, you must append this.
			if(args.equals(""))
				args = "auto";
			else
				args = args + ", auto";
		}
		else if(containsUnicodeString()) {
			if(args.equals(""))
				args = "unicode";
			else
				args = args + ", unicode";
		}

		String str = "/** @dll.struct("+args+") */\r\npublic class " + name + mods + " {\r\n";
		try {
			for(int i=0; i<fields.size(); i++) {
				Variable var = (Variable) fields.elementAt(i);
				if(var == null)
					System.out.println("Ack! Invalid null field in struct "+name);
				String javaType = null;
				boolean append_semicolon = true;
				// For embedded structs, do something meaningful.  Expand them and add on the
				// field name of the struct to the fields.  So a struct containing a POINT named pt
				// now has two extra fields - int pt_x; and int pt_y;
				if(var.ismultiFieldDataStructure()) {
					append_semicolon = false;
					multiFieldDataStructure data = var.getmultiFieldDataStructure();
					javaType = "// "+var.Name+" was a by-value "+data.getName()+" structure\r\n";
					for(int j=0; j<data.numFields(); j++) {
						Field f = (Field) data.getField(j);
						// Insert name_ before name of the field...
						StringTokenizer st = new StringTokenizer(f.toJavaString(), " \t", true);
						String mungedfield="\t";
						String append = null;
						do {
							String token = st.nextToken();
							if(token.equals("\t")) {
								append = "\t"+var.Name+"_";
								//mungedfield = mungedfield+"\t"+var.Name+"_";
							}
							else {
								if(append != null && !(token.equals("public") || token.equals("private") || token.equals("protected")))
									mungedfield = mungedfield + append + token;
								else {
									if(append != null)
										mungedfield = mungedfield + "\t" + token;
									else
										mungedfield = mungedfield + token;
								}
								append = null;
							}
						} while(st.hasMoreTokens());
						if(javaType==null)
							javaType = mungedfield;
						else
							javaType = javaType + mungedfield+";\r\n";
					}
				}
				else
					javaType = var.toJavaString();
				// StringBuffers never exist inside structs.
				if(javaType.equals("StringBuffer"))
					javaType = "String";
				str = str + "\t" + javaType + (append_semicolon ? ";\r\n" : "");
				//str = str + "\t" + var.Type + "\t" + var.Name + ";\r\n";
			}
		}
		catch (InvalidParameterException e) {
			System.out.println("Ack!  InvalidParameterException went through Struct::toJavaString for " + name);
			throw e;
		}
		str = str + "}\r\n";
		return str;
	}
}

/** This class is for structures that aren't ever defined in a header file explicitly,
 * but pointers to it are used frequently.  Examples are GLUtesselator and CommCtrl's
 * _IMAGELIST.  
 * 
 * I'm still debating how, or whether, to use this.
 */
class OpaqueStruct extends Struct
{
	/**
	 * Make an opaque structure, a struct that is never explicitly defined in a header file.
	 * @param my_name Name of the struct
	 */
	public OpaqueStruct(String my_name) {
		super(my_name);
	}

	/**
	 * Converts Struct to its string representation in C syntax.  Must be overridden.
	 * @return String containing the C representation of this data structure.
	 */
	public String toString()
	{
		return "struct "+name+";";
	}

	/**
	 * Converts Struct to its string representation in Java syntax.  Must be overridden.
	 * @param isInsideStruct if this is inside a struct or a union
	 * @return String containing the Java representation of this data structure.
	 */
	public String toJavaString(boolean isInsideStruct) throws InvalidParameterException
	{
		if(TypeLUT == null)
			throw new InvalidParameterException("TypeLUT was null in toJavaString!");
		if(StructureLUT == null)
			throw new InvalidParameterException("StructureLUT was null in toJavaString!");

		String mods = "";
		if(modifiers!=null)
			mods = " /* "+modifiers+" */";
		String args = "";
		if(packsize != JavaDefaultPackSize)
			args = "pack="+packsize;

		// If we've merged this structure with an ASCII one, use the auto keyword.
		// If not, check for using embedded unicode strings and use unicode keyword.
		if(merged) {  // if merged, you must append this.
			if(args.equals(""))
				args = "auto";
			else
				args = args + ", auto";
		}
		else if(containsUnicodeString()) {
			if(args.equals(""))
				args = "unicode";
			else
				args = args + ", unicode";
		}

		String str = "/** @dll.struct("+args+") */\r\npublic class " + name + mods + " {\r\n";
		str = str + "}\r\n";
		return str;
	}
}


class Union extends multiFieldDataStructure
{
	/** 
	 * Make a new Union object, giving it a name.
	 * @param name Primary name of the union
	 * @return a new Union.
	 */
	public Union(String name)
	{
		super(name);
	}

	/**
	 * Tells whether this is a union or not.
	 * @return true if this multiFieldDataStructure is a union; else false
	 */
	public final boolean isUnion()
	{
		return true;
	}

	/**
	 * Tells whether this is a struct or not.
	 * @return true if this multiFieldDataStructure is a struct; else false
	 */
	public boolean isStruct()
	{
		return false;
	}

	/**
	 * Converts union to its string representation in C syntax.  Must be overridden.
	 * @return String containing the C representation of this data structure.
	 */
	public String toString()
	{
		String str = "union " + name + (modifiers!=null ? " "+modifiers : "") + " {\r\n";
		for(int i=0; i<fields.size(); i++) {
			Variable var = (Variable) fields.elementAt(i);
			str = str + "\t" + var.Type + "\t" + var.Name + ";\r\n";
		}
		return str;
	}

	/**
	 * Converts Union to java representation.  This really needs work.
	 * @param isInsideStruct if this is inside a struct or a union
	 * @return String containing Java representation of union.
	 */
	public String toJavaString(boolean isInsideStruct) throws InvalidParameterException
	{
		if(TypeLUT == null)
			throw new InvalidParameterException("TypeLUT was null in toJavaString!");
		if(StructureLUT == null)
			throw new InvalidParameterException("StructureLUT was null in toJavaString!");

		String args = "";
		if(packsize != JavaDefaultPackSize)
			args = "pack="+packsize;
		if(merged) {
			if(args.equals(""))
				args = "auto";
			else
				args = args + ", auto";
		}

		String header = "/** @dll.struct("+args+") */\r\n";
		String str = "";
		str = "// stub for compilability.  Must be replaced.\r\n"+header+"public class "+name+" {}\r\n\r\n";
		str = str + "// UNION\r\n"+header+"/*\r\npublic class " + name + " {\r\n";
		// This isn't right.
		for(int i=0; i<fields.size(); i++) {
			Variable var = (Variable) fields.elementAt(i);
			str = str + "\t" + var.toJavaString() + ";\r\n";
		}
		str = str + "}\r\n*/\r\n";
		return str;
	}
}


class Function
{
	protected String return_type;
	protected Vector arguments;
	protected String name;
	protected int stringformat;		// Conversion mode for strings
	protected String library;			// What library this function occurs in
	protected boolean is_Inline;
	protected boolean is_Abstract;

	protected static final String DefaultLib = Parser.UnknownLibraryString;

	public static final int StrFmt_Unknown = 0;
	public static final int StrFmt_ANSI = 1;
	public static final int StrFmt_Unicode = 2;
	public static final int StrFmt_Auto = 3;

	public Function()
	{
		name = "<Unnamed Function>";
		return_type = new String("<Unknown return type>");
		arguments = new Vector();
		stringformat = StrFmt_Unknown;
		library = DefaultLib;
		is_Inline = false;
		is_Abstract = false;
	}

	public Function(String name)
	{
		this.name = name;
		return_type = new String("<Unknown return type>");
		arguments = new Vector();
		stringformat = StrFmt_Unknown;
		library = DefaultLib;
		is_Inline = false;
		is_Abstract = false;
	}

	public void finalize()
	{
		name = null;
		return_type = null;
		arguments = null;
	}

	/**
	 * Compares two function names, returning true if they're identical.  Works on
	 * the assumption that there's no polymorphism in the Win32 API (which was written 
	 * in C).
	 * @param f An Object to compare this one to.
	 * @return true if Object is a function and names are identical; otherwise false.
	 */
	public boolean equals(Object obj)
	{
		if(!(obj instanceof Function))
			return false;
		return name.equals(((Function) obj).getName());
	}

	/**
	 * Get the Function's name.
	 * @return String containing name of this Function.
	 */
	public String getName()
	{
		return name;
	}

	/**
	 * Sets the name of a Function.
	 * @param newName new name for this Function.
	 * @return No return value.
	 */
	public void setName(String newName)
	{
		name = new String(newName);
	}

	/**
	 * Get a function's return type in C
	 * @return String containing C return type.
	 */
	public String getReturnType()
	{
		return return_type;
	}

	/**
	 * Set the return type of this function.
	 * @param r New return type in C
	 * @return No return value.
	 */
	public void setReturnType(String r)
	{
		return_type = r;
	}

	/**
	 * Returns current format of any string parameters to this function, 
	 * ie Unknown, ANSI, Unicode, or Auto.  Exact return
	 * value is Function.StrFmt_x, where x is one of the 4 modes just mentioned.
	 * @return Format of string parameters to this function.
	 */
	public int getStringFormat()
	{
		return stringformat;
	}

	/**
	 * Sets the current string format to one passed in.
	 * @param fmt New format for all string parameters to this function.
	 * @return No return value.
	 */
	public void setStringFormat(int fmt)
	{
		/*
		if(fmt < StrFmt_Unknown || fmt > StrFmt_Auto)
			throw new InvalidParameterException("New string format out of valid range.");
		*/
		stringformat = fmt;
	}

	/**
	 * Returns a string saying what library this function occurs in.  If uninitialized,
	 * then returns the value of Function.DefaultLib, USER32.
	 * @return Library this function occurs in, or value of DefaultLib.
	 */
	public String getLibrary()
	{
		return library;
	}

	/** 
	 * Used to set the library this function occurs in.  Defaults to 
	 * Function.DefaultLib, or USER32 if not set.
	 * @param LibName Library name this function occurs in, ie USER32.
	 * @return No return value.
	 * @exception InvalidParameterException if LibName is null.
	 */
	public void setLibrary(String LibName) throws InvalidParameterException
	{
		if(LibName==null)
			throw new InvalidParameterException("Function::setLibrary won't take a null library name!");
		library = LibName;
	}

	/**
	 * Is this Function inline?  Not quite sure how useful this is, but its supported.
	 * @return true if this is an inline function; else false
	 */
	public boolean isInline()
	{
		return is_Inline;
	}

	/**
	 * Is this an abstract Function?  Not quite sure how useful this is, but its supported.
	 * @return true if this is an abstract function; else false
	 */
	public boolean isAbstract()
	{
		return is_Inline;
	}

	/**
	 * Sets inline flag to a value.
	 * @param v Value to set inline flag to.
	 * @return No return value.
	 */
	public void setInline(boolean v)
	{
		is_Inline = v;
	}

	/**
	 * Sets abstract flag to a value.
	 * @param v Value to set abstract flag to.
	 * @return No return value.
	 */
	public void setAbstract(boolean v)
	{
		is_Abstract = v;
	}

	/**
	 * Adds a parameter name and the type of that parameter to a function's representation.
	 * Add arguments in the order addArgument is called.
	 * @param Type The type of the argument.
	 * @param Param The parameter name.
	 * @return No return value.
	 */
	public void addArgument(String Type, String Name)
	{
		if(Type.toLowerCase().equals("void"))
			return;
		Variable var = new Variable(Type, Name);
		arguments.addElement(var);
	}

	/**
	 * Adds a Function parameter to a function's representation.
	 * Add arguments in the order addArgument is called.
	 * @param pfunc A Function object to add as an argument to a function.
	 * @return No return value.
	 */
	public void addArgument(Function pfunc)
	{
		Variable var = new Variable(pfunc);
		arguments.addElement(var);
	}

	/**
	 * Adds a preprocessed Variable to a function's representation.
	 * Add arguments in the order addArgument is called.
	 * @param var A Variable containing an element to use as a parameter.
	 * @return No return value.
	 */
	public void addArgument(Variable var)
	{
		arguments.addElement(var);
	}

	/**
	 * Use this to return argument i of a function.  Numbering starts at 0.
	 * @param numArg number of argument to return, starting at 0.
	 * @return The specified Variable object.
	 * @exception ArrayIndexOutOfBoundsException if numArg is greater than the number of function arguments.
	 */
	public Variable getArgument(int numArg)
	{
		return (Variable) arguments.elementAt(numArg);
	}

	/**
	 * Returns the number of Variables added to this Function.
    * @return The number of arguments to this function.
	 */
	public int getNumArgs()
	{
		return arguments.size();
	}

	/**
	 * Print out this function in the special format for documenting functions.
	 * Useful only for our internal testing tools, which may no longer exist.
	 * @deprecated This function itself isn't deprecated, but its behavior is.
	 * @return String representing this function.
	 */
	public String toString()
	{
		String output = name + "\t" + return_type + "\r\n";
		for(int i=0; i<arguments.size(); i++) {
			Variable var = (Variable) arguments.elementAt(i);
			output = output + name + "\t" + var.Type + "\t" + var.Name + "\r\n";
		}
		return output;
	}

	/**
	 * Converts each of the arguments into a string representation, producing a comma
	 * separated list like a function prototype.
	 * @return String holding all of the function's arguments and types.
	 */
	protected String argsToString()
	{
		StringBuffer output = new StringBuffer("");
		for(int i=0; i<arguments.size(); i++) {
			Variable var = (Variable) arguments.elementAt(i);
			output.append(var.Type + "  " + var.Name);
			if(arguments.size()-1 != i)
				output.append(", ");
		}
		return output.toString();
	}
}


/** 
 * Used to compare two Function objects for sorting.
 * @see com.ms.util.Comparison
 */
class FunctionCompare implements Comparison
{
	// I only need to override compare(Object, Object), but I thought I'd do this too.
	public int compare(Function a, Function b)
	{
		return a.getName().compareTo(b.getName());
	}

	/**
	 * Compares two Function objects by calling String::compareTo on the function names.
	 * @param a first Function
	 * @param b second Function
	 * @return a positive number if a > b, 0 if a == b, and a negative number if a < b.
	 */
	public int compare(Object a, Object b)
	{
		if(!(a instanceof Function))
			return -1;
		if(!(b instanceof Function))
			return +1;
		return ((Function) a).getName().compareTo(((Function) b).getName());
	}
}


/** 
 * <p>Parser for Win32 API header files</p>
 *
 * <p>This tool was used to generate a significant portion of the Win32 API classes. 
 * It is being included for you to use and modify to fit your specific needs. Remember 
 * that C header files were not designed to be language-independent descriptions, and 
 * that there is more than one correct way to represent some data types in Java. Thus,
 * some functions will require hand-translation. For information on how to do this, 
 * see the J/Direct documentation.</p>
 *
 * <p>Notes:</p>
 * <ul>
 * <li>Currently we prefer the Unicode version of functions if possible.  This avoids the
 * overhead on NT of converting the Java string to ASCII then the ASCII wrapper 
 * converting the string back to Unicode internally.  But most of the time we will
 * output the auto keyword on structs and functions.</li>
 *
 * <li>We can't process COM libraries.  COM uses an entirely different object and 
 * function handling method.</li>
 *
 * <li>Classes and many class-like features of structs were added as an afterthought.</li>
 *
 * <li>Another thing: functions that take structs by value (not pointers to structs) will
 * be a problem.  I will have to write wrappers for them manually.  Plus I don't have a
 * good representation for them - currently, I output them incorrectly.</li>
 *
 * <li>Inside structs, we never output StringBuffers, only strings.  (required by J/Direct)</li>
 * </ul>
 *
 * @version	0.963
 */
public class Parser
{
	// EDIT THIS LINE - put your package name here.
	protected static final String PackageName = "com.ms.win32";

	private static final String version = "0.963";
	protected PrintWriter PuntOutput;  // Record of what we punted on.
	protected Vector Functions;		  // Functions read from the header files.
	protected Vector Symbols;			  // Symbols read from the DLLs.
	protected Hashtable TypeLUT;		  // Translation table from C types to Java types.
	protected Hashtable StringTypes;   // String types and their conversion format.
	protected Hashtable OutputClasses; // Based on input library, determine output package.
	protected Hashtable StructureLUT;  // user-defined datatype conversion table
	protected Hashtable Precedence;    // table of C++ operator precedence.
	protected Vector IncludeHeaders;   // Do parse these files if found.
	protected Vector ExcludeHeaders;   // Do not parse these files.
	protected Vector ExcludeFunctions; // Exclude these functions from parsing.

	// These control a few options, like #define's might in C.
	// Look for functions in symbol files but not header files and vice versa.
	protected static final boolean ReadSymbols = true;

	// When true, symbols in unknown libraries aren't printed to any Java file.
	// If we don't read in the symbol files & this is true, expect empty output files.
	// If you don't read in symbols (or don't have a symbol file), this should be false.
	protected static final boolean Suppress_UnknownLib_Functions = (ReadSymbols ? true : false);

	// When true, output unused structures to the com.ms.win32.dead directory.
	// (An unused structure is one that never is passed to or returned by a function)
	protected static final boolean Suppress_Unused_Structures = true;

	// When converting odd types like void* to int, put a greppable tag in file.
	protected static final boolean Comment_Variant_Types = true;

	// Debug level - to prune some of the output
	protected static final int DEBUG = 2;

	// Use this for all anonymous function parameters, like:
	// void foo(int);   Defined in one place for customizability.
	protected static final String AnonymousString = "<anonymous>";

	// Use this when we don't know what file portion of the preprocessed file we're
	// currently in.
	protected static final String UnknownFileString = "<Unknown file>";
	protected static final String UnknownLibraryString = "<unknown_library>";
	protected static final String ExcludeFunctionFile = "exclude.txt";
	public static final String CallbackString = "com.ms.dll.Callback";
	protected static String CopyrightNotice = "// Copyright (C) 1997 Microsoft Corporation  All Rights Reserved\r\n"+
"//\r\n"+
"// This software is a preview release of the Windows API Access\r\n"+
"// classes for Java. These classes provide direct, low-overhead access\r\n"+
"// to commonly used Windows API functions. These classes use the new J/Direct\r\n"+
"// feature and therefore require either Internet Explorer 4.0 beta-2, or the\r\n"+
"// Microsoft SDK for Java 2.0.\r\n"+
"//\r\n"+
"// WARNING: These classes are still in development and are incomplete. \r\n"+
"// This preview release is being provided as-is in order to solicit feedback\r\n"+
"// and to assist developers in the use of J/Direct by providing a library\r\n"+
"// of prewritten declarations for the most common Win32 API functions. As with\r\n"+
"// all prerelease software, it is subject to significant change without notice\r\n"+
"// before shipping. \r\n"+
"//\r\n"+
"// Information on how to use J/Direct to write your own declarations\r\n"+
"// can be found in the Microsoft SDK for Java 2.0.";

	public Parser()
	{
		PopulateTypeLUT();
		SetupFileFilters();
		SetStringTypes();
		SetupOutputClasses();
		SetupPrecedenceTable();
		StructureLUT = new Hashtable();  // empty - filled by program.
		Variable.setStructureTable(StructureLUT);
		ExcludeFunctions = new Vector();
		ReadExcludeFunctions();
	}

	public void finalizer()
	{
		Functions = null;
		Symbols = null;
		TypeLUT = null;
		StructureLUT = null;
		Precedence = null;
		StringTypes = null;
		ExcludeHeaders = null;
		IncludeHeaders = null;
		ExcludeFunctions = null;

		// Write out closing '}' to all files in output classes.
		Enumeration enum = OutputClasses.elements();
		while(enum.hasMoreElements()) {
			PrintWriter s = (PrintWriter) enum.nextElement();
			s.print("\r\n}\r\n\r\n");
			s.close();
		}
		OutputClasses = null;
		PuntOutput.close();
		PuntOutput = null;
	}

	/**
	 * Reads through list of functions to exclude, in the file described by 
	 * ExcludeFunctionFile.
	 * @return No return value.
	 */
	protected void ReadExcludeFunctions()
	{
		try { 
			PuntOutput = new PrintWriter(new FileOutputStream("punt.txt")); 
			StreamTokenizer st = new StreamTokenizer(new InputStreamReader(new FileInputStream(ExcludeFunctionFile)));
			st.eolIsSignificant(false);
			st.wordChars('_', '_');
			while(st.nextToken() != st.TT_EOF) {
				if(st.ttype == st.TT_WORD)
					ExcludeFunctions.addElement(st.sval);
			}
			st = null;
		}
		catch (FileNotFoundException e)
		{
			System.out.println("Can't find exclude functions file "+ExcludeFunctionFile);
			System.out.println(e);
		}
		catch (IOException e)
		{
			System.out.println(e);
			e.printStackTrace();
		}
	}


	/**
	 * Prints the command line syntax to stdout.
	 * @return No return value.
	 */
	public static final void usage()
	{
		System.out.println("This program takes a preprocessed Win32 API header file and creates");
		System.out.println("another file storing the functions and all of their argument");
		System.out.println("types and variable names.  It also converts the structs into Java");
		System.out.println("classes, for moderately complex types.  It would be very useful if");
		System.out.println("you ran dumpbin /exports on your DLL and listed the name of that");
		System.out.println("symbol file in symbolfiles.txt in this directory.");
		System.out.println("Output files include the original plus a .parse extention and many");
		System.out.println("files in .\\com\\ms\\win32, as well as a few .txt files in this dir.");
		System.out.println("");
		System.out.println("Usage:");
		System.out.println("Parser <file1> [<file2> .. <fileN>]\r\n");
	}


	/** 
	 * Inserts C type names and their corresponding Java types into TypeLUT, this class's
	 * internal hashtable.  Edit this function if you want to handle another type name
	 * in a different way.
	 * <p>
	 * Tricky types are handled by leaving their type names as they were.  Then you
	 * are forced to deal with them yourself when you try to compile the resulting file.
	 * <p>
	 * Took out most pointer to function types, hoping to recognize those at runtime.  
	 * They need some special case handling anyway that I don't think we can do easily.
	 * @return No return value.
	 */
	protected void PopulateTypeLUT()
	{
		TypeLUT = new Hashtable();
		Variable.setPrimitiveTable(TypeLUT);
		TypeLUT.put("ATOM", "short");
		TypeLUT.put("ALG_ID", "int");
		TypeLUT.put("BOOL", "boolean");      // 32-bit - This is a Java boolean
		TypeLUT.put("BOOLEAN", "byte");		 // 8-bit    This should be a byte.
		TypeLUT.put("BYTE", "byte");
		TypeLUT.put("Callback", CallbackString);   // to handle some bugs?
		TypeLUT.put(CallbackString, CallbackString);   // to handle some bugs?
		TypeLUT.put("CALID", "int");
		TypeLUT.put("CALTYPE", "int");
		TypeLUT.put("CCHAR", "byte");
		TypeLUT.put("CHAR", "byte");
		TypeLUT.put("COLORREF", "int");
		TypeLUT.put("CTRYID", "short");
		TypeLUT.put("DWORD", "int");
		TypeLUT.put("DWORDLONG", "long");
		TypeLUT.put("FLOAT", "float");
		TypeLUT.put("FOURCC", "int");

		// OpenGL headers have prototypes for these few structs, but never actually 
		// use the structs themselves, always passing pointers.  Declare as ints?
		TypeLUT.put("GLUnurbs", "int");
		TypeLUT.put("GLUquadric", "int");
		TypeLUT.put("GLUtesselator", "int");
		TypeLUT.put("GLUtriangulatorObj", "int");
		TypeLUT.put("GLUnurbs * ", "int");
		TypeLUT.put("GLUquadric * ", "int");
		TypeLUT.put("GLUtesselator * ", "int");
		TypeLUT.put("GLUtriangulatorObj * ", "int");

		TypeLUT.put("GLbitfield", "int");
		TypeLUT.put("GLbyte", "byte");
		TypeLUT.put("GLboolean", "byte");
		TypeLUT.put("GLclampd", "double");
		TypeLUT.put("GLclampf", "float");
		TypeLUT.put("GLdouble", "double");
		TypeLUT.put("GLfloat", "float");
		TypeLUT.put("GLint", "int");
		TypeLUT.put("GLsizei", "int");
		TypeLUT.put("GLshort", "short");
		TypeLUT.put("GLubyte", "byte");
		TypeLUT.put("GLuint", "int");
		TypeLUT.put("GLushort", "short");
		TypeLUT.put("GLint", "int");
		TypeLUT.put("GLvoid", "void");
//		TypeLUT.put("GOBJENUMPROC", CallbackString);
//		TypeLUT.put("GRAYSTRINGPROC", CallbackString);
		TypeLUT.put("GUID", "com.ms.com._Guid");    // Special case.
		TypeLUT.put("HACCEL", "int");
		TypeLUT.put("HANDLE", "int");
		TypeLUT.put("HBITMAP", "int");
		TypeLUT.put("HBRUSH", "int");
		TypeLUT.put("HCOLORSPACE", "int");
		TypeLUT.put("HCONV", "int");
		TypeLUT.put("HCONVLIST", "int");
		TypeLUT.put("HCURSOR", "int");
		TypeLUT.put("HDC", "int");
		TypeLUT.put("HDDEDATA", "int");
		TypeLUT.put("HDESK", "int");
		TypeLUT.put("HDRVR", "int");
		TypeLUT.put("HDWP", "int");
		TypeLUT.put("HENHMETAFILE", "int");
		TypeLUT.put("HFILE", "int");
		TypeLUT.put("HFONT", "int");
		TypeLUT.put("HGDIOBJ", "int");
		TypeLUT.put("HGLOBAL", "int");
		TypeLUT.put("HGLRC", "int");
		TypeLUT.put("HHOOK", "int");
		TypeLUT.put("HICON", "int");
		TypeLUT.put("HINSTANCE", "int");
		TypeLUT.put("HKEY", "int");
		TypeLUT.put("HKL", "int");
		TypeLUT.put("HLOCAL", "int");
		TypeLUT.put("HMENU", "int");
		TypeLUT.put("HMETAFILE", "int");
		TypeLUT.put("HMIDIIN", "int");
		TypeLUT.put("HMIDIOUT", "int");
		TypeLUT.put("HMMIO", "int");
		TypeLUT.put("HMODULE", "int");
		TypeLUT.put("HOOKPROC", "int");
		TypeLUT.put("HPALETTE", "int");
		TypeLUT.put("HPEN", "int");
		TypeLUT.put("HPSTR", "StringBuffer");
		TypeLUT.put("HRESULT", "int");          // an errorcode defined as a C long.
		TypeLUT.put("HRGN", "int");
		TypeLUT.put("HRSRC", "int");
		TypeLUT.put("HSZ", "int");
		TypeLUT.put("HTASK", "int");
		TypeLUT.put("HWAVEIN", "int");
		TypeLUT.put("HWAVEOUT", "int");
		TypeLUT.put("HWINSTA", "int");
		TypeLUT.put("HWND", "int");
		TypeLUT.put("INT", "int");
		TypeLUT.put("LANGID", "short");
		TypeLUT.put("LARGE_INTEGER", "long");
		TypeLUT.put("LCID", "int");
		TypeLUT.put("LCTYPE", "int");
		TypeLUT.put("LINEDDAPROC", "LINEDDAPROC");
		TypeLUT.put("LONG", "int");
		TypeLUT.put("LONGLONG", "long");
		TypeLUT.put("LP", "StringBuffer");
		TypeLUT.put("LPARAM", "int");
		TypeLUT.put("LPBOOL", "boolean[]");
		TypeLUT.put("LPBOOLEAN", "int[]");
		TypeLUT.put("LPBYTE", "byte[] /* BUGBUG: LPBYTE */");
		TypeLUT.put("LPCBOOL", "boolean[]");
		TypeLUT.put("LPCBOOLEAN", "byte[]");
		TypeLUT.put("LPCCH", "String");
//		TypeLUT.put("LPCCHOOKPROC", CallbackString);
//		TypeLUT.put("LPCFHOOKPROC", CallbackString);
		TypeLUT.put("LPCH", "StringBuffer");
		TypeLUT.put("LPCOLESTR", "String");
		TypeLUT.put("LPCOLORREF", "int[]");
		TypeLUT.put("LPCSTR", "String");
		TypeLUT.put("LPCTSTR", "String");
		TypeLUT.put("LPCVOID", "int");
		TypeLUT.put("LPCWCH", "String");
		TypeLUT.put("LPCWSTR", "String");
		TypeLUT.put("LPDWORD", "int[]");
		TypeLUT.put("LPHANDLE", "int[]");
		TypeLUT.put("LPHWAVEIN", "int[]");
		TypeLUT.put("LPHWAVEOUT", "int[]");
		TypeLUT.put("LPINT", "int[]");
		TypeLUT.put("LPLONG", "int[]");
		TypeLUT.put("LPOLESTR", "StringBuffer");
		TypeLUT.put("LPSTR", "StringBuffer");
		TypeLUT.put("LPTCH", "StringBuffer");
		TypeLUT.put("LPTSTR", "StringBuffer");
		TypeLUT.put("LPUINT", "int[]");
		TypeLUT.put("LPVOID", "int");
		TypeLUT.put("LPWCH", "StringBuffer");
		TypeLUT.put("LPWORD", "short[]");
		TypeLUT.put("LPWSTR", "StringBuffer");
		TypeLUT.put("LRESULT", "int");
		TypeLUT.put("LUID", "long");
		TypeLUT.put("MCIDEVICEID", "int");
		TypeLUT.put("MCIERROR", "int");
		TypeLUT.put("MMRESULT", "int");
		TypeLUT.put("NPSTR", "StringBuffer");
		TypeLUT.put("NWPSTR", "StringBuffer");
		TypeLUT.put("OLECHAR", "char");
		TypeLUT.put("PBOOL", "boolean[]");
		TypeLUT.put("PBOOLEAN", "byte[]");
		TypeLUT.put("PBYTE", "byte[] /* BUGBUG: PBYTE */");
		TypeLUT.put("PCCH", "String");
		TypeLUT.put("PCH", "StringBuffer");
		TypeLUT.put("PCHAR", "StringBuffer");
		TypeLUT.put("PCSTR", "String");
		TypeLUT.put("PCWCH", "String");
		TypeLUT.put("PCWSTR", "String");
		TypeLUT.put("PDWORD", "int[]");
		TypeLUT.put("PFLOAT", "float[]");
		TypeLUT.put("PHANDLE", "int[]");
		TypeLUT.put("PHKEY", "int[]");
		TypeLUT.put("PINT", "int[]");
		TypeLUT.put("PLARGE_INTEGER", "long[]");
		TypeLUT.put("PLONG", "int[]");
		TypeLUT.put("PLUID", "long[]");
		TypeLUT.put("PSECURITY_DESCRIPTOR_CONTROL", "short[]");
		TypeLUT.put("PSECURITY_INFORMATION", "int[]");
		TypeLUT.put("PSHORT", "short[]");
//		TypeLUT.put("PSID", "int");
		TypeLUT.put("PSID_NAME_USE", "int[]");
		TypeLUT.put("PSTR", "StringBuffer");
		TypeLUT.put("PSZ", "StringBuffer");
		TypeLUT.put("PTCH", "StringBuffer");
		TypeLUT.put("PTCHAR", "StringBuffer");
		TypeLUT.put("PTSTR", "StringBuffer");
		TypeLUT.put("PUCHAR", "StringBuffer");
		TypeLUT.put("PUINT", "int[]");
		TypeLUT.put("PULARGE_INTEGER", "long[]");
		TypeLUT.put("PULONG", "int[]");
		TypeLUT.put("PUSHORT", "short[]");
		TypeLUT.put("PVOID", "int");
		TypeLUT.put("PWCH", "StringBuffer");
		TypeLUT.put("PWCHAR", "StringBuffer");
		TypeLUT.put("PWORD", "short[]");
		TypeLUT.put("PWSTR", "StringBuffer");
		TypeLUT.put("REGSAM", "int");
		TypeLUT.put("SC_HANDLE", "int");
		TypeLUT.put("SECURITY_DESCRIPTOR_CONTROL", "short");
		TypeLUT.put("SERVICE_STATUS_HANDLE", "int");
		TypeLUT.put("SHORT", "short");
		TypeLUT.put("SPHANDLE", "int");
		TypeLUT.put("TCHAR", "char");
		TypeLUT.put("UCHAR", "char");
		TypeLUT.put("UINT", "int");
		TypeLUT.put("ULARGE_INTEGER", "long");
		TypeLUT.put("ULONG", "int");
		TypeLUT.put("USHORT", "short");
		TypeLUT.put("VOID", "void");
		TypeLUT.put("WCHAR", "char");
		TypeLUT.put("WORD", "short");
		TypeLUT.put("WPARAM", "int");
		// Real primitives
		TypeLUT.put("int", "int");
		TypeLUT.put("short", "short");
		TypeLUT.put("long", "int");
		TypeLUT.put("bool *", "boolean[]");
		TypeLUT.put("boolean *", "byte[]");
		TypeLUT.put("char", "char");
		TypeLUT.put("char *", "StringBuffer");
		TypeLUT.put("char * ", "StringBuffer");
		TypeLUT.put("size_t", "int");
		TypeLUT.put("void", "void");
		TypeLUT.put("void *", "int");
		TypeLUT.put("wchar_t", "char");
		TypeLUT.put("wctype_t", "char");
		TypeLUT.put("wint_t", "char");  // defined as wchar_t
		TypeLUT.put("float", "float");
		TypeLUT.put("double", "double");
		TypeLUT.put("__int8", "byte");  // VC++ supports these.
		TypeLUT.put("__int16", "short");
		TypeLUT.put("__int32", "int");
		TypeLUT.put("__int64", "long");

		// Nasty hacks for opaque structs
		TypeLUT.put("_PSP", "int");
		TypeLUT.put("HPROPSHEETPAGE", "int");
		TypeLUT.put("_PROPSHEETPAGEA", "int");
		TypeLUT.put("_PROPSHEETPAGEW", "int");
		TypeLUT.put("_IMAGELIST", "int");
		TypeLUT.put("HIMAGELIST", "int");
		TypeLUT.put("HTREEITEM", "int");

		if(DEBUG>4)
			System.out.println("After filling, Type lookup table size = " + TypeLUT.size());
	}

	/**
	 * Fills the StringTypes Hashtable with all String types and how to convert them from
	 * Unicode to whatever format is needed.  Punts on TCHAR and derivatives, setting 
	 * them to auto.
	 * @return No return value.
	 */
	protected void SetStringTypes()
	{
		StringTypes = new Hashtable();

		Array.setStringTable(StringTypes);

		StringTypes.put("char", "ansi");
		StringTypes.put("char *", "ansi");
		StringTypes.put("char * ", "ansi");
		StringTypes.put("CCHAR", "ansi");
		StringTypes.put("CHAR", "ansi");
		StringTypes.put("LP", "unicode");
		StringTypes.put("LPCCH", "ansi");
		StringTypes.put("LPCH", "ansi");
		StringTypes.put("LPCSTR", "ansi");
		StringTypes.put("LPCWCH", "unicode");
		StringTypes.put("LPCWSTR", "unicode");
		StringTypes.put("LPTSTR", "auto");  // may not need to be converted...
		StringTypes.put("LPSTR", "ansi");
		StringTypes.put("LPTCH", "auto");   // may not need to be converted.
		StringTypes.put("LPTSTR", "auto");  // may not need to be converted.
		StringTypes.put("LPWCH", "unicode");
		StringTypes.put("LPWSTR", "unicode");
		StringTypes.put("NPSTR", "ansi");
		StringTypes.put("NWPSTR", "unicode");
		StringTypes.put("PCCH", "ansi");
		StringTypes.put("PCH", "ansi");
		StringTypes.put("PCHAR", "ansi");
		StringTypes.put("PCSTR", "ansi");
		StringTypes.put("PCWCH", "unicode");
		StringTypes.put("PCWSTR", "unicode");
		StringTypes.put("PSTR", "ansi");
		StringTypes.put("PSZ", "ansi");
		StringTypes.put("PTCH", "auto");    // may not need to be converted.
		StringTypes.put("PTCHAR", "auto");  // may not need to be converted.
		StringTypes.put("PTSTR", "auto");   // may not need to be converted.
		StringTypes.put("PWCH", "unicode");
		StringTypes.put("PWCHAR", "unicode");
		StringTypes.put("PWSTR", "unicode");
		StringTypes.put("TCHAR", "auto");   // may not need to be converted.
		StringTypes.put("UCHAR", "ansi");
		StringTypes.put("WCHAR", "unicode");
		StringTypes.put("wchar_t", "unicode");
		StringTypes.put("wctype_t", "unicode");
		StringTypes.put("wint_t", "unicode");
	}


	/**
	 * Converts all functions and structures from C to Java.
	 * @return No return value.
	 */
	public void Convert() throws InvalidParameterException
	{
		try {
			for(int i=0; i<Functions.size(); i++) {
				Function func = (Function) Functions.elementAt(i);
				OutputToClassFile(func);
			}

			Enumeration e = StructureLUT.elements();
			Vector Structures = new Vector();
			while(e.hasMoreElements()) {
				multiFieldDataStructure data = (multiFieldDataStructure) e.nextElement();
				if(!Structures.contains(data))
					Structures.addElement(data);
			}
			System.out.print("Sorting data structures... ");
			com.ms.util.VectorSort.sort(Structures, new multiFieldDataStructureCompare());
			System.out.print("outputting... ");
			for(int i=0; i<Structures.size(); i++) {
				//String javaclass = ConvertStruct((Struct)Structures.elementAt(i));
				multiFieldDataStructure data = (multiFieldDataStructure) Structures.elementAt(i);
				if(data.isUnion()) { // Punting on all unions.
					PuntOutput.println("Punting on union: "+data.getName());
					continue;
				}
				if(data.containsUnion()) { // Punt on structures containing unions.
					PuntOutput.println("Punting on structure containing a union: "+data.getName());
					continue;
				}

				PrintWriter out;
				if(Suppress_Unused_Structures && !data.isUsed())
					out = new PrintWriter(new FileOutputStream("com\\ms\\win32\\dead\\"+data.getName()+".java"));
				else
					out = new PrintWriter(new FileOutputStream("com\\ms\\win32\\"+data.getName()+".java"));
				out.print(CopyrightNotice+"\r\n\r\npackage "+PackageName+";\r\n\r\n");
				String javaclass = data.toJavaString(false);
				out.print(javaclass + "\r\n");
				out.close();
			}
			System.out.println("Done.");
		}
		catch (IOException e) {
			System.out.println("Convert hit a snag: " + e);
		}
	}
	

	/**
	 * Writes out a Function to the correct class file for that function.
	 * @param func Function to write to a class.
	 * @return No return value.
	 * @exception InvalidParameterException if func is null.
	 */
	protected void OutputToClassFile(Function func) throws InvalidParameterException
	{
		if(func==null)
			throw new InvalidParameterException("OutputToClassFile won't take a null function!");
		String lib = func.getLibrary();
		PrintWriter file = (PrintWriter) OutputClasses.get(lib);
		if(file == null) {
			System.out.println("Ack!  No file for functions in DLL " + lib);
			return;
		}

		String javaFunc = ConvertFunction(func);
		if(javaFunc != null)
			file.print(javaFunc + "\r\n\r\n");
	}


	/**
	 * Converts a C function prototype to a Java wrapper.
	 * @param func A Function object to convert.
	 * @return String of converted Java wrapper or "" if conversion failed.
	 * @exception InvalidParameterException if func is null or messed up.
	 */
	public String ConvertFunction(Function func) throws InvalidParameterException
	{
		if(func==null)
			throw new InvalidParameterException("ConvertFunction refuses to take a null parameter!");
		String javaFunc = "public native static ";
		if(func.isAbstract())
			javaFunc = "public abstract static ";
		String trailer = "";
		if(func.getReturnType() == null) {
			System.out.println("Ack! Return type was null!");
			System.out.println("Function was "+func.getName());
		}
		String javaReturn = (String) TypeLUT.get(func.getReturnType());
		if(javaReturn == null) {
			multiFieldDataStructure data = (multiFieldDataStructure) StructureLUT.get(func.getReturnType());
			if(data != null)
				javaReturn = data.getName();
			if(javaReturn == null) {
				javaReturn = "int /* BUGBUG: unknown type: " + func.getReturnType()+" */";
				System.out.println("Unknown return type: "+func.getReturnType());
			}
		}
//System.out.print("ConvertFunction: "+func.getName()+"  ");

		// Can't return a StringBuffer
		if(javaReturn.equals("StringBuffer"))
			javaReturn = "String";
		// Now it looks like returning Strings isn't supported.  Convert to int.
		if(javaReturn.equals("String"))
			javaReturn = "int";
		// Never return a callback object, but a pointer to one as an int.
		if(javaReturn.equals(CallbackString))
			javaReturn = "int";

		javaFunc = javaFunc + javaReturn + " " + func.getName() + " (";

		// Check to see if this function should be excluded.
		if(ExcludeFunctions.contains(func.getName())) {
			System.out.println("Excluding function "+func.getName());
			javaFunc = "/* BUGBUG - explicitly excluded */ /* "+ javaFunc;
			trailer = " */";
		}

		// We considered outputting JavaDoc comments for every function, but there were a few
		// problems with the idea.  Any anonymous parameters would still need to be edited,
		// text descriptions should be added to all variables, and they double the size of our
		// code for no particularly good reason (they're kinda useless right now).  But
		// if you want to add a standard version of a JavaDoc comment, uncomment some of the
		// lines below here.
		String header = "";//"\t/** Calls the Win32 function "+func.getName() +"\r\n";

		try {
			for(int i=0; i<func.getNumArgs(); i++) {
				Variable var = func.getArgument(i);
				if(var==null)
					throw new InvalidParameterException("Function "+func.getName()+"'s argument "+i+" was null!");
				if(var.Type==null)
					throw new InvalidParameterException("Function "+func.getName()+"'s argument "+i+"'s Type was null!");

				if(var.isVarArg())  // comment out vararg functions.
					javaFunc = "// BUGBUG: Variable Arguments "+javaFunc;

				// All of the next lines dealing with data are for 2 purposes.
				// They skip functions that have Union parameters or structs containing unions
				// and they mark structures as "in use".  If a structure isn't used by
				// a function I'm processing, let's skip it.
				multiFieldDataStructure data = null;
				if(var.ismultiFieldDataStructure())
					data = (multiFieldDataStructure) var.getmultiFieldDataStructure();
				else
					data = (multiFieldDataStructure) StructureLUT.get(var.Type);
				if(data==null) {
					StringTokenizer st = new StringTokenizer(var.Type);
					do {
						String token = st.nextToken();
						if(token.equals("const"))
							continue;
						data = (multiFieldDataStructure) StructureLUT.get(token);
					} while (data==null && st.hasMoreTokens());
				}

				if(data != null) {
					if(data.isUnion() || data.containsUnion()) {
						PuntOutput.println("Punting on a function that takes a union or a struct containing a union: "+func.getName());
						return "// "+func.getName()+" took a parameter that either was or contained a union.";
					}
					if(Suppress_Unused_Structures)
						data.Use();  // Mark that a function uses this data structure.
				}

				String jArg = ConvertArgumentType(var, func);
				// For now, assume if we can't convert the type, the function is unusable.
				if(jArg == null)
					return "";

				String ParamName = (AnonymousString.equals(var.Name) ? "anon"+i : var.Name);
				if(ParamName.equals(multiFieldDataStructure.anonymous)) {
					ParamName = "anonymous_struct"+i;
				}
				// Add a line into the comments describing the parameter.
				//header = header + "\t * @param "+ParamName+" Empty\r\n";
				javaFunc = javaFunc + jArg + " " + ParamName;
				if(i+1<func.getNumArgs())
					javaFunc = javaFunc + ", ";		
			}
		}
		catch (UnrecognizedCodeException e) {
			System.out.println("Caught Unrecognized Code: " +e+"\r\n"+ e.BadFragment);
			System.out.println("Function was " + func.toString());
			return "";
		}
		javaFunc = javaFunc + ");";

		// Add return type to comments...
		/*
		header = header + "\t * @return ";
		if(javaReturn.equals("void"))
			header = header + "No return value.\r\n";
		else
			header = header + javaReturn +"\r\n";
		*/

		// Tack in @dll.import line...
		String libname = func.getLibrary();
		if(Suppress_UnknownLib_Functions && libname.equals(UnknownLibraryString)) {
			PuntOutput.println("Punting on "+func.getName()+" because we can't find out what DLL it was in!");
			return null;
		}

		//header = header +"\t * @dll.import(\"" + libname + "\"";
		header = "\t/** @dll.import(\"" + libname + "\"";
		switch(func.getStringFormat()) {
		case Function.StrFmt_Unknown: break;
		case Function.StrFmt_ANSI: header = header + ", ansi"; break;
		case Function.StrFmt_Unicode: header = header + ", unicode"; break;
		case Function.StrFmt_Auto: header = header + ", auto"; break;
		default: 
			System.out.println("Ack!  Fell through switch statement in ConvertFunction!");
		}
		//header = header + ")\r\n\t */\r\n\t";
		header = header + ") */\r\n\t";
		javaFunc = header + javaFunc + trailer;
//System.out.println("Done w/ "+func.getName());
		return javaFunc;
	}

	
	/**
	 * Converts a C function argument's type into the equivalent Java type.  Also 
	 * determines how to do any string conversion (Ansi vs. Unicode) by setting
	 * function's stringformat.
	 * @param var Variable object to convert
	 * @param func Function containing this Variable
	 * @return String holding Java type name.
	 * @exception UnrecognizedCodeException if cannot convert argument's C type to Java.
	 */
	public String ConvertArgumentType(Variable var, Function func) throws UnrecognizedCodeException, InvalidParameterException
	{
		if(var == null)
			throw new InvalidParameterException("Got passed NULL Variable!");
		if(func == null)
			throw new InvalidParameterException("Got passed NULL Function!");

		String CType = var.Type;
		String JType = "";
		JType = (String) TypeLUT.get(CType);

		String format = (String) StringTypes.get(CType);
		if(format != null) {
			//System.out.println("Found a " + format + " parameter in " + func.getName());
			if(format.equals("ansi"))
				func.setStringFormat(Function.StrFmt_ANSI);
			else if(format.equals("unicode"))  // Unicode functions aren't implemented in Win95.
				func.setStringFormat(Function.StrFmt_Auto);
			else if(format.equals("auto"))
				func.setStringFormat(Function.StrFmt_Auto);
			else
				System.out.println("Ack!  What kind of String format is this???  " + format);
		}

		// When converting some of the types with more exotic uses, such as LPBYTE, print
		// out a message.  Or at least make this message disable-able.
		if(Comment_Variant_Types) {
			if("LPBYTE".equals(CType) || "PBYTE".equals(CType) || CType.startsWith("BYTE *")) {
				JType = "byte[] /* BUGBUG: "+CType+" */";
			}
		}


		if(JType != null)
			return JType;

		// Handle case of pointers to functions here.
		if(var.isFunction()) {
			return CallbackString;
		}

		// Handle trickier cases, parsing * and modifiers like const.
		StringTokenizer st = new StringTokenizer(CType);
		/* Rules:
		 * If it's a char *, convert to StringBuffer, unless const is in effect.
		 * 
		 * If it's a pointer, convert it to an integer.
		 * Otherwise, write out the type as-is and print a warning.
		 */
		JType = null;
		boolean isConst = false;
		boolean isChar = false;   // strictly if this is a character type.
		boolean isString = false; // if this is a pointer to a character or char[].
		boolean isPtr = false;    // if this a pointer?
		boolean isReference = false;
		boolean isStruct = false;
		while(st.hasMoreTokens()) {
			String token = st.nextToken();
			//System.out.print("token \""+token+"\"");
			if(token.equals("const")) {
				isConst = true;
				continue;
			}
			if(token.equals("&")) {
				isReference = true;
			}
			// If its a pointer...
			if(token.equals("*")) {
				isPtr = true;
				//System.out.print(" Found pointer. JType=\""+JType+"\" ");
				if(isChar) {
					JType = (isConst ? "String" : "StringBuffer");
					isString = true;
					isChar = false;
					isPtr = false;
					continue;
				}
				if(isString) {
					//System.out.println("Fixup: Found a pointer to a "+JType+"! Changing to int. CType was: "+CType);
					JType = "int /* BUGBUG: "+CType+" */";
					continue;
				}
				//System.out.println("Before *, JType was " + JType);
				if(JType != null && !isStruct)
					JType = JType + "[]";
				/*
				else
					throw new UnrecognizedCodeException("Ack! Null JType or * in wrong place!");
				*/
				continue;
			}
			if(token.equals("char")) {
				isChar = true;
				continue;
			}
			// if its a struct keyword, look up structure.
			if(token.equals("struct")) {
				//System.out.println("Found struct keyword in type...");
				token = st.nextToken();
				isStruct = true;
			}
			// Special case: GUID
			if(token.equals("GUID")) {
				JType = (String) TypeLUT.get("GUID");
				break;
			}
			// New normal Primitive lookup.
			if(JType == null) {
				JType = (String) TypeLUT.get(token);
				//System.out.println("primitive lookup on "+token+" returned "+JType);
				if(JType != null) {
					isChar = isChar || JType.equals("char");
					isString = isString || JType.startsWith("String");
					continue;
				}
			}
			// Look up in StructureLUT.
			if(true) {
				String name = token;
				multiFieldDataStructure data = (multiFieldDataStructure) StructureLUT.get(name);
				if(data!=null) {
					//System.out.print("Found a structure in StructureLUT named "+data.getName());
					JType = data.getName();
					isStruct = true;
				}
				else
					if(isStruct)
						JType = "structure_" + name;
				continue;
			}
			// Try to save something.  Fortunately this never gets used, as far as I can tell.
			if(JType == null) {
				JType = (String) TypeLUT.get(token);
				//System.out.println("special late Type lookup on \""+token+"\" returned \""+JType+"\"");
				if(JType == null) { // special lookup rules
					if(token.startsWith("H"))  // Handle
						JType = "int /* BUGBUG: guessing for "+token+" */";
					else if(token.startsWith("LPC")) { // constant pointer
						isConst = true;
						JType = "int /* BUGBUG: guessing for "+token+" */";
					}
					else if(token.startsWith("LP"))  // pointer
						JType = "int /* BUGBUG: guessing for "+token+" */";
				} // end special lookup rules
				if(JType == null)  // Just can't deal with it.
					throw new UnrecognizedCodeException("Can't handle type " + CType);
			}
			else
				System.out.println("Hit bottom of convertargumenttype's while loop. JType="+JType);
		}  // end while

		if(CType.equals("")) {
			System.out.println("Ack!  CType was \"\"!!!!");
			throw new UnrecognizedCodeException("function argument of unknowable type");
		}

		// last-minute fix-up for strings and void[]'s.
		if(JType != null) {
			if(JType.equals("char[]"))
				JType = "StringBuffer";
			
			if(JType.equals("void[][]"))
				JType = "int /* BUGBUG: "+CType+" */";

			if(JType.equals("void[]"))
				JType = "int[] /* BUGBUG: "+CType+" */";

			// Shouldn't happen often, but we'll leave this in here...
			if(JType.equals("null[]") || JType.equals("null[][]"))
				throw new UnrecognizedCodeException("null array! CType was \""+CType+"\"  JType was " + JType);
		}
		else {
			System.out.println("Unrecognized C type \""+CType+"\".  Giving up.");
			//JType = "<"+CType+">";
			return null;
		}
		//System.out.println("Returning java type " + JType);
		return JType;
	} // end ConvertArgumentType(String)


	/** 
	 * Parsefile(String) reads in the filename you pass it, stores the functions and
	 * structures from that file in a vector of functions or a hash table of structures.  
	 * This is the main input processing function.
	 * @param FileIn Filename to parse.
	 * @return No return value.
	 * @exception UnrecognizedCodeException if there was a parsing problem.
	 * @exception InvalidParameterException if there's a problem with a function called by this one.
	 */
	public void ParseFile(String FileIn) throws UnrecognizedCodeException, InvalidParameterException
	{
		// CurrentFile is the file within FileIn we're reading through.  Here we assume
		// FileIn is the output of the C preprocessor.  We'll ignore some files and examine
		// others.
		String CurrentFile = UnknownFileString;
		Stack packsize = new Stack();
		packsize.push(new PackContainer(8, "VC++ Default Pack size"));  // VC defaults to 8-byte alignment
		InputStreamReader isr = null;
		try {
			Functions = new Vector();
			isr = new InputStreamReader((InputStream) new FileInputStream(FileIn));

			StreamTokenizer st = new StreamTokenizer(isr);
			st.eolIsSignificant(false);
			st.ordinaryChar('/');
			st.slashStarComments(true);
			st.slashSlashComments(true);
			// Add all the modifying characters such as *
			st.ordinaryChar('*');
			st.ordinaryChar('(');
			st.ordinaryChar(')');
			st.ordinaryChar('#');
			st.wordChars('_', '_');
			st.ordinaryChar('.');

			String lastString = "<unknown last string>";

			while (st.nextToken() != StreamTokenizer.TT_EOF) {
				if(st.ttype == StreamTokenizer.TT_WORD) {
//					if(st.sval.equals("WINAPI") || st.sval.equals("APIENTRY")
//						|| st.sval.equals("WINAPIV")) {
					if(st.sval.equals("__stdcall") || st.sval.equals("__cdecl")) {
						// Found a function
						String keyword = st.sval;
						st.nextToken();
						if(st.ttype == StreamTokenizer.TT_WORD) {
							Function func = new Function(st.sval);
							func.setReturnType(lastString);

							// Now read in parenthesis and function parameters
							st.nextToken();
							if(st.ttype != '(') {
								if(st.ttype == StreamTokenizer.TT_WORD)
									throw new UnrecognizedCodeException(func.getName() + ": " + st.sval);
								else
									throw new UnrecognizedCodeException(func.getName() + " had a problem.");
							}

							MungeVariables(func, st);

							if(ReadSymbols)
								FindLibrary(func);

							// If it's already in the Functions list, don't add a second copy.
							if(findFunction(func.getName()) != null || ExcludeFunctions.contains(func.getName()))
								continue;
							Functions.addElement(func);
							//System.out.println("Added " + func.getName());

						} else {
							// Handle WINAPI in weird places, such as a typedef?
							// These are bad states, or at least ones I didn't write code to handle.
							if(st.ttype == ')') {
								throw new UnrecognizedCodeException(keyword + " trailed by ')'");
							}
							if(st.ttype == '*') {
								// Whenever we see a COM library, they invariably have a Vtbl struct
								// that contains pointers to functions.  I don't parse them in this format.
								// I see this in mapidefs.h, around IMAPIAdviseSinkVtbl
								throw new UnrecognizedCodeException(keyword + " trailed by '*' - maybe a COM library? (Can't parse COM)");
							}
							if(st.ttype == StreamTokenizer.TT_EOL) {
								throw new UnrecognizedCodeException(keyword + " trailed by number, num = " + st.nval);
							}
							throw new UnrecognizedCodeException("Unknown token following " + keyword + "\r\nType: " + ((char)st.ttype));
						}
					} // end WINAPI

					else if(st.sval.equals("typedef")) {
						// Note that sometimes WINAPI occurs in pointer to function typedefs.
						st.nextToken();
						if(st.ttype == st.TT_WORD) {
							// Check for defining a primitive as another type name.
							// Two possibilities - could be a pointer to a function or something
							// like typedef int DWORD;
							if(st.sval.equals("const") || st.sval.equals("unsigned"))
								st.nextToken();
							if(TypeLUT.contains(st.sval) || TypeLUT.containsKey(st.sval)) {
								String old_name = st.sval;
								String primitive = (String) TypeLUT.get(old_name);
								st.nextToken();
								if(st.ttype == st.TT_WORD && st.sval.equals("const"))
									st.nextToken();
								if(st.ttype == '*')
									while(st.nextToken() == '*');
								if(st.ttype == '(') {// this is a pointer to a function
									while(st.nextToken() != '*');
									st.nextToken();
									if(st.ttype == st.TT_WORD && !TypeLUT.contains(st.sval)) {
										System.out.println("Adding pointer to function "+st.sval);
										TypeLUT.put(st.sval, CallbackString);
									}
									while(st.nextToken()!=';');
									continue;
								}
								if(st.ttype != st.TT_WORD)
									throw new UnrecognizedCodeException("typedef primitive new_primitive_name encountered something that wasn't a string! original word: "+old_name);
								String new_primitive = st.sval;
								if(!TypeLUT.containsKey(new_primitive)) {
									System.out.println("Adding new primitive "+new_primitive+" as "+primitive);
									TypeLUT.put(new_primitive, primitive);
								}
								st.nextToken();
							}
							// Check for being a struct or a union
							else if(st.sval.equals("struct") || st.sval.equals("union")) {
								multiFieldDataStructure s = ReadStructure(st, false);
								if(s == null)  // a few special cases like GUID.
									continue;
								if(!packsize.isEmpty()) {  //foobie
									int ps = ((PackContainer) packsize.peek()).getPackSize();
									s.setPackSize(ps);
								}

								// Throw all typedef'ed names in there too!!!
								StructureLUT.put(s.getName(), s);
								for(int i=0; i<s.numAltNames(); i++)
									StructureLUT.put(s.getAltName(i), s);

								System.out.println("Added "+ (s.isStruct() ? "struct " : "union ") +s.getName()+"\r\n");
							}  // end typedef struct
							else if(StructureLUT.containsKey(st.sval)) {
								// This is the typedef struct_name [*] alt_name; code.
								multiFieldDataStructure s = (multiFieldDataStructure) StructureLUT.get(st.sval);
								String name = null;
								st.nextToken();
								do {
									if(st.ttype == '*')
										st.nextToken();
									String append = st.sval;
									if(st.ttype==st.TT_WORD && st.sval.equals("const"))
										continue;
									if(name==null)
										name = append;
									else
										name = name + append;
									// may not be correct - especially in the case where there are multiple typedef'ed names.
								} while(st.nextToken() != ';');
								s.addAltName(name);
								StructureLUT.put(name, s);
								System.out.println("Added alias " + name + " for " + s.getName());
							} // typedef <struct_name> alias;
							else if(TypeLUT.containsKey(st.sval)) {
								//System.out.print("Ptr to function detected, maybe.  typedef " + st.sval);
								st.nextToken();
								//System.out.println((char)st.ttype);
								if(st.ttype == '*')  // could return, say, void*
									st.nextToken();
								if(st.ttype == '(') {
									System.out.println("Found pointer to function!");
									while(st.nextToken() != ';');
								}
							} // end typedef <type> ( <ptr-to-Function> ) ( [args] );
							// Handle enumerated types...  This section is weak.
							else if(st.sval.equals("enum")) {
								st.nextToken();
								if(st.ttype == st.TT_WORD) {
									System.out.println("Throwing in enumerated type " + st.sval);
									TypeLUT.put(st.sval, "int");
									st.nextToken();
								}
								if(st.ttype == '{') {
									while(st.nextToken() != '}');
									st.nextToken();
								}
								while(st.ttype != ';') {
									String alias = null;
									while(st.ttype != ',' && st.ttype != ';') {
										if(st.ttype=='*')
											st.nextToken();
										if(alias==null)
											alias=st.sval;
										else
											alias = alias+" "+st.sval;
										st.nextToken();
									}
									if(st.ttype==',')
										st.nextToken();
									System.out.println("Adding alias for enumerated type "+alias);
									TypeLUT.put(alias, "int");
								}
							}
							//else
							//	System.out.println("Didn't recognize token sequence typedef "+st.sval);
						} // end typedef <word>
						else
							throw new UnrecognizedCodeException("typedef what?  token was " + (char)st.ttype);
					} // end typedef
					else if(st.sval.equals("struct")) {
						// Handle forward definitions of structures as ints.
						// For cases like:  struct blah;  typedef struct blah * blahptr;
						// And then they never define blah.  However, if a function returns a struct,
						// it could go through this code path.  Same if they define then don't
						// immediately typedef the struct...
						st.nextToken();
						if(st.ttype != st.TT_WORD)
							throw new UnrecognizedCodeException("Thought I would read an opaque structure, but didn't!  Found non-word!");
						String structname = st.sval;
						st.nextToken();
						if(st.ttype != ';') {
							st.pushBack();
							continue;
							//throw new UnrecognizedCodeException("Thought I was reading an opaque struct, "+structname+", but didn't find ';' after it!");
						}
						//TypeLUT.put(structname, "int");
						if(!TypeLUT.containsKey(structname)) {
							StructureLUT.put(structname, new OpaqueStruct(structname));
							System.out.println("Added opaque struct "+structname);
						}
					}
					else if(st.sval.equals("class")) {
						// What about forward definitions of classes????
						multiFieldDataStructure data = ReadStructure(st, false);
						if(data!=null) {
							System.out.println("Adding class "+data.getName());
							StructureLUT.put(data.getName(), data);
						}
					}
					else 
						lastString = st.sval;  // Track lastString so we know return type.

				} // end is word

				else if(st.ttype == '#') {
					//System.out.println("Found a #.");
					// Look for #line x "Current File Name"
					// Look for #if(WINVER >= 0x0400) .. [#else ..] #endif
					// Look for #pragma pack([push,x | pop])
					st.nextToken();
					if(st.ttype == StreamTokenizer.TT_WORD) {
						if(st.sval.equals("line")) {
							st.nextToken();
							st.nextToken();
							String NextFile;
							if(st.sval.startsWith(".\\"))
								NextFile = st.sval.substring(2);
							else
								NextFile = st.sval;
							if(CurrentFile.equals(NextFile))
								continue;
							CurrentFile = NextFile;
							//System.out.println("Hit file marker... In " + CurrentFile);

							// Aggressively skip to the next file we can parse.
							while (!CheckFile(CurrentFile)) {
								//System.out.println("#line handler skipping to next file...");
								boolean changedFile = false;
								do {
									int ntoken;
									do {
										ntoken = st.nextToken();
									} while(ntoken != '#' && ntoken != StreamTokenizer.TT_EOF);
									if(ntoken == StreamTokenizer.TT_EOF)
										throw new DoneException();
									st.nextToken();
									if(st.sval != null && st.sval.equals("line")) {
										st.nextToken();
										st.nextToken();
										if(st.sval.startsWith(".\\"))
											NextFile = st.sval.substring(2);
										else
											NextFile = st.sval;
										if(!NextFile.equals(CurrentFile)) {
											CurrentFile = NextFile;
											//System.out.println("Changed file to " + CurrentFile);
											changedFile = true;
										}
									}
									else if(st.sval.equals("pragma")) {
										// Must handle pack size changes even in these files.
										st.nextToken();
										if(st.ttype == st.TT_WORD && st.sval.equals("pack"))
											PackHandler(st, packsize);
									}
								} while (!changedFile);
							} // end while(!CheckFile(CurrentFile))
						}  // end #line
						if(st.sval.equals("pragma")) 
						{
							st.nextToken();
							if(st.sval.equals("pack")) {
								PackHandler(st, packsize);
							} // end #pragma pack
							//else
							//	System.out.println("Unrecognized pragma \"" + st.sval + "\"");
						} // end #pragma handlers.
					} // end # <word>
				} // end #

			}  // end while
		}
		catch(DoneException e) {}
		catch(InvalidParameterException e) {
			System.out.println("Ack!  Invalid parameter exception caught in ParseFile!");
			System.out.println(e.Description);
			e.printStackTrace();
		}
		catch(IOException e) {
			System.out.println("IO Error!  CurrentFile: "+CurrentFile);
			System.out.println(e);
		}
		catch(UnrecognizedCodeException e) {
			System.out.println("Didn't recognize a code fragment in "+CurrentFile+".  Stopping parsing.");
			//System.out.println(e);
			//System.out.println(e.Description + "  " + e.BadFragment);
			//e.printStackTrace();
			throw e;
		}
		catch(NullPointerException npe) {
			System.out.println("Ack!  Caught "+npe+"!  CurrentFile: "+CurrentFile);
			npe.printStackTrace();
			throw npe;
		}
		catch(Exception e) {
			System.out.println("Uncaught exception at bottom of ParseFile(String)  CurrentFile: "+CurrentFile);
			e.printStackTrace();
			//throw e;
		}
		catch(Throwable t) {
			System.out.println("Uncaught throwable object at bottom of Parsefile!  CurrentFile: "+CurrentFile);
			System.out.println(t);
			t.printStackTrace();
		}
		finally {
			try { isr.close(); }
			catch (IOException ioe) {}
			isr = null;
			packsize = null;
			CurrentFile = null;
		}
	} // end ParseFile(String in);

	  
	/** 
	 * MungeVariables takes the current function name and a
	 * StreamTokenizer positioned right after the first parenthesis.
	 * It prints the function name, a tab, the type of a parameter, then
	 * the parameter name on a line for every parameter.
	 * <p>Example:  void WINAPI foo(int, char ch);
	 * <p>Translates into:
	 * <br>foo\t void
	 * <br>foo\t int\t &lt;anonymous&gt;
	 * <br>foo\t char\t ch
	 * @param func Function object whose arguments are being munged.
	 * @param st StreamTokenizer positioned right after beginning '(' of function arguments.
	 * @return No return value.
	 * @exception IOException if StreamTokenizer has a problem
	 * @exception UnrecognizedCodeException if it can't parse a variable (unlikely, but possible)
	 */
	protected void MungeVariables(Function func, StreamTokenizer st) throws IOException, UnrecognizedCodeException
	{
		int ntoken = st.nextToken();
		do {
			boolean addTypeandParam = true;
			String Type = new String("");
			String Name = AnonymousString;
			boolean firsttime = true;  // Used to check for anonymous args where the type has only one token.
			while(ntoken != ',' && ntoken != ')') {
				// Invariant: Either addTypeandParam is false (pointer to function case) OR
				//            (Type hold what we've parsed of the type so far and
				//             Name holds data that may or may not be part of the type).
				if(st.ttype == StreamTokenizer.TT_WORD) {
					if(firsttime) {
						firsttime = false;
						Type = st.sval;
					}
					else {
						if(!Name.equals(AnonymousString))
							Type = Type+' '+Name;
						Name = st.sval;
					}
				}
				// Handle one of two variable argument syntaxes
				if(st.ttype == '.') {
					// Leave it in this order - remember && is short-circuited.
					if(st.nextToken() == '.' && st.nextToken() == '.') {
						Type = "Old-style vararg list";
						Name = "...";
						System.out.println("Note: Function " + func.getName() + " has a '...' argument.");
					}
					else {
						System.out.println("Vararg ... test failed.  st.sval: " + st.sval + "  st.nval = " + ((char) st.nval) + "  st.ttype = " + ((char) st.ttype));
						throw new UnrecognizedCodeException("While processing function " + func.getName() + ", found period in\r\nargument name or type and it wasn't part of a '...'");
					}
				}  // End var arg section.
				if(st.ttype == '*' || st.ttype == '&') {
					//if(st.ttype == '&')
					//	System.out.println("Found a & in the type of one of function " + func.getName() + "'s arguments.");
					if(!Name.equals(AnonymousString))
						Type = Type+" "+Name;
					// This expression was just sitting here without the assignment, which is all wrong.
					// I think this is correct, Type=... And this probably was a major 
					// source of bugs in my code.
					Type = Type+' '+(char)st.ttype;
					Name = "";
				}
				if(st.ttype == '(')  {  // Got a pointer to a function argument
					Function pfunc = new Function();
					addTypeandParam = false;
					pfunc.setReturnType(Type);
					pfunc.setName("Pointer-to-function-type");
					ntoken = st.nextToken();
					System.out.println("Found pointer to function in function " + func.getName());
					while(st.nextToken() != ')') {
						// throw away for now...  Lazy.
						
					}
					while(st.nextToken() != '(');
					MungeVariables(pfunc, st);
					System.out.println("Got arguments to pointer to function...");
					func.addArgument(pfunc);
				}
				ntoken = st.nextToken();
			}
			
			// If this isn't a pointer to a function...
			if(addTypeandParam && !Type.equals("")) {
				if(Name.equals("")) {
					//System.out.println("In function " + func.getName() + ", Name was \"\" at the end.");
					Name = AnonymousString;
				}

				func.addArgument(Type, Name);
			}
			
			if(ntoken != ')')
				ntoken = st.nextToken();
		} while(ntoken != ')');

	} // end MungeVariables


	/**
	 * Parses a multiFieldDataStructure, reading in its fields, etc.  Returns the Struct
	 * or Union object.
	 * @param st StreamTokenizer positioned at the struct or union keyword.
	 * @param insideStructure true if ReadStructure is nested in a struct or union.
	 * @return a new multiFieldDataStructure object.
	 * @exception UnrecognizedCodeException if struct was unparsible.
	 * @exception InvalidParameterException if StreamTokenizer wasn't positioned on struct.
	 * @exception IOException if StreamTokenizer can't read stream.
	 */
	protected multiFieldDataStructure ReadStructure(StreamTokenizer st, boolean insideStructure) throws UnrecognizedCodeException, InvalidParameterException, IOException
	{
		if(st.sval == null || !(st.sval.equals("struct") || st.sval.equals("union") || st.sval.equals("class")))
			throw new InvalidParameterException("stream tokenizer not positioned exactly on struct!");
		String objType = st.sval;  // For debugging purposes, either class, struct, or union
		boolean use_struct = st.sval.equals("struct") || st.sval.equals("class");
		// Set default protection for fields of this structure, if applicable.
		int prot = (st.sval.equals("class") ? Field.PRIVATE : Field.PUBLIC);
		st.nextToken();
		multiFieldDataStructure str = null;
		String structure_name = null;
		boolean putInStructureLUT = false;   // Sometimes we put a half-built structure
		// in StructureLUT so that readField can deal with recursive struct definitions.
		// We also need to take it out afterwards...

		// Read in the name of the struct.  Change this to be an alternate name later, if
		// one is present (assuming typedef struct ...  alt_struct_name;).  Use
		// the first typedef'ed name as the real name of the struct.  Move to '{'.
		if(st.ttype != '{') {
			structure_name = st.sval;
			st.nextToken();
		}
		if(st.ttype == ':') {
			// Inheritance
			System.out.println("Ignoring inheritance list"+(structure_name!=null ? " for "+structure_name : "."));
			while(st.nextToken() != '{' && st.ttype != ';' && st.ttype != st.TT_EOF);
		}
		if(use_struct)
			str = new Struct(structure_name);
		else
			str = new Union(structure_name);

//		System.out.print("\r\nProcessing "+(structure_name!=null ? structure_name : "an anonymous "+
//			(str.isStruct() ? "struct" : "union"))+"... ");

		// Special case: skip GUID.  We have our own version.
		if(structure_name!=null && "_GUID".equals(structure_name)) {
			System.out.println("Skipping GUID - we treat it as a special primitive.");
			while(st.nextToken() != '}');
			return null;
		}

		// _RTL_CRITICAL_SECTION and _RTL_CRITICAL_SECTION_DEBUG each have a pointer to the other.
		// Consequently I can't deal with those structs normally.
		/*
		if(structure_name != null && structure_name.startsWith("_RTL_CRITICAL_SECTION")) {
			System.out.println("Skipping "+structure_name+" because of circular dependancies...");
			while(st.nextToken() != '}');
			while(st.nextToken() != ';');
			return null;
		}
*/
		// Now we've seen struct|union [structure_name]
		try {
			// typedef struct_name [*] pfoo is handled in ParseFile's typedef section.
			// Deal with something like  struct foobie * pfoobie_field; 
			// Could be either a typedef struct blah alt_blah or field name in embedded struct
			if(st.ttype == '*')
				st.nextToken();
			if(st.ttype == st.TT_WORD) {
				// We've seen struct|union [structure_name] [*] <word>
				// Could be an alias, like typedef struct foo * fooptr;
				// Or most probably we're inside a structure or union and hit an embedded one.
				// And that word there is the field name, or possibly a C modifier like volatile.
				// Use insideStructure to decide which is which.

				// check for any C modifiers that might be in effect...   const, volatile
				// Don't know what to do with them now though.  They're a field-based thing,
				// usually not for an entire structure.  So... ignore for now?
				if(st.sval.equals("volatile") || st.sval.equals("const") ||
					st.sval.equals("FAR") || st.sval.equals("NEAR")) {
					//System.out.println("Adding modifier " + st.sval);
					//str.addModifier(st.sval);  // this line is quite likely wrong.
					st.nextToken();
					// Do another pointer check now.
					if(st.ttype == '*')
						st.nextToken();
					if(st.ttype != st.TT_WORD)
						throw new UnrecognizedCodeException("ReadStructure messed up the stream while trying to handle a const or volatile structure modifier.");
				}

//				System.out.println("In "+objType+" name [*] fieldname now...\r\nstruct "+structure_name+" [*] "+st.sval);
				multiFieldDataStructure data = (multiFieldDataStructure) StructureLUT.get(structure_name);
				if(data != null) {
					System.out.println("Found "+objType+" " + data.getName()+" in StructureLUT");
					if(insideStructure) {
						// Now st is at the field name, with up to one modifier stripped out.
						// must quit now and let readfield deal with the rest.
						return data;
					}
					else {
						// Adding aliased name for this structure.
						if(st.ttype != st.TT_WORD)
							throw new UnrecognizedCodeException("Readstructure was going to add alias to a structure, but no name was found! "+structure_name);
						if(!st.sval.equals(structure_name)) {  // If its the same, redefine the structure.
							data.addAltName(st.sval);
							return data;
						}
					}
				}
				else {
					// This could have been an opaque struct, where we have a forward definition
					// then a typedef of a pointer to that struct.  Allow those, as ints.
					// maybe.
					System.out.println("Couldn't find struct or union named "+structure_name+" in StructureLUT.");
					st.nextToken();
					throw new PuntException("Found struct <undefined struct> somewhere... Maybe you punted on: ", structure_name);
				}
			}
			else if(st.ttype == '{') {
				st.nextToken();

				// Add half-built struct into hashtable so we can use it for recursive structs.
				boolean wasPresent = StructureLUT.containsKey(str.getName());
				if(!wasPresent) {
					//System.out.println("Adding half-built structure named " + str.getName()+" to StructureLUT.");
					StructureLUT.put(str.getName(), str);
					str.setComplete(false);
					putInStructureLUT = true;
				}

				while(st.ttype != '}') {
					// Check for #line's in the middle of the structure...
					if(st.ttype == '#') {
						st.nextToken(); // line
						st.nextToken(); // x
						st.nextToken(); // "word"?????
						st.nextToken();
						//System.out.println("Read my #line..  Token should be LONGLONG.  "+st.sval);
						continue;
					}

					// Protection check - change protection, read to end of line, then continue.
					if(st.ttype==st.TT_WORD) {
						boolean change = false;
						if(st.sval.equals("public")) {
							prot = Field.PUBLIC;
							change = true;
						}
						else if(st.sval.equals("protected")) {
							prot = Field.PROTECTED;
							change = true;
						}
						else if(st.sval.equals("private")) {
							prot = Field.PRIVATE;
							change = true;
						}
						if(change) {
							st.nextToken();
							st.nextToken();
							continue;
						}
					}

					Field var=null;
					try {
						var = (Field) readField(st, ';', '}', true, true);
						var.setProtection(prot);
					}
					catch (UnrecognizedCodeException e) {
						System.out.print("\r\nUnrecognizedCodeException filtered through ReadStructure while reading ");
						System.out.println((str.isStruct() ? "struct" : "union") + " named " + structure_name);
						throw e;
					}
					
					if(var == null)
						System.out.println("Ack! var == null");
					str.addField(var);
					st.nextToken();
				} // parsing struct fields.
				// Now pull out str, since we only added it to handle embedded structures.
				// suspicious.
				if(!wasPresent) {
					StructureLUT.remove(str.getName());
					str.setComplete(true);
					putInStructureLUT = false;
				}
			} // end typedef struct [name] {  ( [fields] }

			// Status check for debugging.
			if(st.ttype != '}')
				throw new UnrecognizedCodeException("ReadStructure got lost after reading a structure and before reading its alias list/fieldname.");

			// Now we hit the list of aliases for this struct or union, assuming there was a typedef.
			// However, for embedded structs, these might really be fieldnames!!!!
			// We've seen struct|union [structure_name] [*] [{ [fields] }] 
			// Now we expect to see either a semicolon or a list of words and *'s, followed by a ';'
			if(!insideStructure) {
				st.nextToken();
				boolean firsttime = true;
				while(st.ttype != ';') {
					if(st.ttype != st.TT_WORD && st.ttype != '*')
						throw new UnrecognizedCodeException("Ack!  Freaking out in a typedef alias list!  token="+(char)st.ttype);
					
					// Parse the type once again, looking for pointers, etc.
					String type = null;
					do {
						String append = null;
						if(st.ttype == '*')
							append = null;  // could use "*" here...
						else if(st.ttype == st.TT_WORD) {
							if(!st.sval.toUpperCase().equals("FAR") && !st.sval.toUpperCase().equals("NEAR"))
								append = st.sval;
						}
						else
							throw new UnrecognizedCodeException("Ack!  Bailing while parsing alias list for " +
							(str.isStruct() ? "struct " : "union ") + str.getName() +"! (unexpected token \""+(char)st.ttype+"\" sval: "+st.sval);
						if(type == null)
							type = append;
						else
							type = type + " " + append;
						st.nextToken();
					} while(st.ttype != ',' && st.ttype != ';');
					if(firsttime) {
						str.addAltName(str.getName());
						str.setName(type);
						firsttime = false;
					}
					else
						str.addAltName(type);
					if(DEBUG>5)
						System.out.println("Adding alt name " + type);
					
					if(st.ttype == ',')
						st.nextToken();
				} // end while to read alias names,
			} // end if !insideStructure

		} // end try
		catch(PuntException p) {
			System.out.println("Punted in " + p.Name +" because " + p.Reason);
			PuntOutput.println(p.Reason + "  Punted in: " + p.Name+"  ReadStructure in: "+structure_name);
			//	(str!=null ? "  ReadStructure in: "+str.getName() : ""));
			if(putInStructureLUT)
				StructureLUT.remove(str.getName());
			str = null;
		}
		return str;
	}

	/**
	 * Given a StreamTokenizer, it will read a variable type and name, including the
	 * more complex user-defined data types like unions and structs.  Assumes it is being
	 * called on text within a structure or a union, although it should work with functions
	 * too.  Recursively calls ReadStructure if it hits an embedded structure.
	 * Reads a field until the ending separator or terminator, leaving st there.
	 * within this one.  Also tries to handle some slightly different conversion rules
	 * while reading fields from structures.
	 * @param st StreamTokenizer positioned at beginning of a field.
	 * @param separator character used to separate multiple fields
	 * @param terminator character used to end a list of fields
	 * @param isInsideStruct whether we're reading a data structure
	 * @param allowAnonymous whether we can have anonymous data types declared in place.
	 * @return a Variable object (or if isInsideStruct is true, a Field) representing 
	 *         the field read in.
	 * @exception UnrecognizedCodeException if the function gets lost.
	 * @exception InvalidParameterException if separator or terminator equal StreamTokenizer.TT_WORD, or if st is null.
	 * @exception IOException if StreamTokenizer has an IO problem.
	 * @exception PuntException if the parser doesn't understand this field or is told to ignore it, based on name and/or type.
	 */
	protected Variable readField(StreamTokenizer st, char separator, char terminator, boolean isInsideStruct, boolean allowAnonymous) 
		throws UnrecognizedCodeException, InvalidParameterException, IOException, PuntException
	{
		/* New assumptions:
		 * 1) All fields have a type and/or a field name.  At least one is present.
		 * 2) All fields start with a one-word type (modulo *), which is either a primitive,
		 *    a user-defined data type, or the name of the current user-defined data type.
		 * 3) All user-defined data types will be in the StructureLUT, even in the recursive
		 *    struct field case.
		 * 4) user-defined data types don't have to have a type name associated with them.
		 * 5) Fields can be bitfields.  Punt on those.
		 * Sometimes embedded structs can be declared anonymously in place:  
		 * union example { struct { int a, int b }; };  Example is the pathological LARGE_INTEGER.
		 */
		if(st==null)
			throw new InvalidParameterException("readField won't accept a null StreamTokenizer parameter!");
		String Type = null;
		String Name = null;
		Variable var = null;
		boolean isConst = false;
		boolean isStatic = false;
		boolean isVolatile = false;
		boolean isVirtual = false;
		boolean isMutable = false;
		if(separator == st.TT_WORD || terminator == st.TT_WORD)
			throw new InvalidParameterException("separator and terminator can't be \""
				   +st.TT_WORD+"\" or readField will fail.  Design flaw.  That's the cost of using the StreamTokenizer.");

		if(st.ttype == separator || st.ttype == terminator)
			return null;
		//System.out.print("Reading field... ");

		if(st.ttype != st.TT_WORD)
			throw new UnrecognizedCodeException("Unknown type part of a field! Token: "+st.ttype);

		if(st.sval.equals("unsigned") || st.sval.equals("signed")) {
			if(DEBUG > 2)
				System.out.println("Readfield moving past "+st.sval+"... ");
			st.nextToken();
		}

		// Check for modifiers
		if(st.sval.equals("virtual")) {
			isVirtual = true;
			st.nextToken();
		}
		if(st.sval.equals("const")) {
			isConst = true;
			st.nextToken();
		} else if(st.sval.equals("volatile")) {
			isVolatile = true;
			st.nextToken();
		}
		if(st.sval.equals("static")) {
			isStatic = true;
			st.nextToken();
		}
		if(st.sval.equals("mutable")) {
			isMutable = true;
			st.nextToken();
		}
		// Check again for const-ness, in case of "static const" or something.
		if(st.sval.equals("const")) {
			isConst = true;
			st.nextToken();
		} else if(st.sval.equals("volatile")) {
			isVolatile = true;
			st.nextToken();
		}

		// If primitive...
		if(TypeLUT.containsKey(st.sval)) {
//			System.out.println("Found a primitive field.");
			Type = st.sval;
			IntExpression assign_expr = null;
			st.nextToken();
			if(st.ttype == '(') {  // pointer to function inside structure
				st.nextToken();
				if(st.sval.equals("__stdcall")) {
					st.nextToken();
					Name = st.sval;
					Type = "int /* BUGBUG: pointer to function */";
					while(st.nextToken() != separator && st.ttype != terminator);
					if(isInsideStruct)
						var = new Field(Type, Name);
					else
						var = new Variable(Type, Name);
					return var;
				}
			}
			if(st.ttype == '*') {
				Type = Type + " *";
				// Ignore all pointers to things inside structures, except of course embedded char arrays.
				//throw new PuntException("Not going to deal with pointers inside data structures.", Type);
				// Unfortunately, this is NOT done very well at all.
				Type = "int";
				do {
					if(st.ttype == st.TT_WORD)
						Name = st.sval;
				} while(st.nextToken() != separator && st.ttype != terminator);
				if(isInsideStruct) {
					var = new Field(Type, Name);
					((Field)var).setStatic(isStatic);
					((Field)var).setMutable(isMutable);
				}
				else
					var = new Variable(Type, Name);
				var.setConst(isConst);
				var.setVolatile(isVolatile);
				var.setPointer(true);
				return var;
			}
			else if(st.ttype != st.TT_WORD)
				throw new UnrecognizedCodeException("While handling primitive type, found hideous symbol (or anonymous field). token="+(char)st.ttype);
			do {
				if(st.ttype == '[') {  // if we have an array...
					Array a;
					boolean isString = false;
					st.nextToken();
					// Some embedded arrays are of variable length.  If their size is 1, then
					// somehow they can change size, or at least be declared to have some odd
					// size at runtime.  And the size of the struct they are in varies too.
					// Consequently, punt on any arrays of size 1.  (detected a few lines down)
					// There's a string like [ANYSIZE ARRAY] that the preprocessor changes to 1
					if(StringTypes.containsKey(Type)) {
						//System.out.println("Found a String or StringBuffer type.");
						isString = true;
					}
					int length = -1;

					//if(st.ttype==st.TT_NUMBER || st.ttype=='(' || st.ttype=='-') {
						//symbol sym = parseNumExp(st, ']');
						//length = sym.value;
						IntExpression len_expr = (IntExpression) parseNumExp(st, ']');
						if(len_expr == null) {
							System.out.println("Ack!  For array "+Name+", length parsing returned NULL!");
							System.exit(1);
						}
						if(DEBUG >= 2)
							System.out.println("For array "+Name+", length was: "+len_expr.toString()+"  evals to: "+len_expr.eval());
						length = (int) len_expr.eval();
					//}

					if(length != -1) {
						if(isString)
							a = new CharArray(Name, length);
						else
							a = new Array(Name, length);
					}
					else {
						if(isString)
							a = new CharArray(Name);
						else
							a = new Array(Name);
					}
					if(a.getLength() == 1)
						throw new PuntException("Found an array of size one in a struct: ", a.getName());
					a.setType(Type);
					if(isInsideStruct)
						var = new Field(a);
					else
						var = new Variable(a);
					//st.nextToken();
					if(st.ttype != ']')
						throw new UnrecognizedCodeException("While processing a primitive array named " 
						   +Name+", got lost while looking for ']'! token="+(char)st.ttype);
					//System.out.print("Made array. ");
				}
				else if(st.ttype == ':') {
					// We have a bitfield.
					if(DEBUG>0)
						System.out.println("Found a bitfield... ");
					//while(st.nextToken() != '}');
					//while(st.nextToken() != ';');
					//throw new PuntException("Not going to deal with bitfields", "<>");
//					while(st.nextToken() != ';');
//					return null;
				}
				else if(st.ttype == '=') {  // Assignment
					System.out.println("Found an initializer for variable "+Name);
					st.nextToken();
					if(st.ttype==st.TT_NUMBER || st.ttype=='(') {
						assign_expr = (IntExpression) parseNumExp(st, ';');
						st.pushBack();
					}
				}
				else {
					if(Name!=null)
						Type = Type + " " + Name;
					Name = st.sval;
				}
				st.nextToken();
			} while (st.ttype != separator && st.ttype != terminator);
			if(var == null) {
				if(isInsideStruct) {
					var = new Field(Type, Name);
					((Field)var).setStatic(isStatic);
					((Field)var).setMutable(isMutable);
				}
				else
					var = new Variable(Type, Name);
			}
			var.setConst(isConst);
			var.setVolatile(isVolatile);
			if(assign_expr != null) {
				var.setInitialValue(assign_expr);
				System.out.println("Adding initializer to "+var.Name+" that evals to "+assign_expr.eval());
			}
			return var;
		}  // end Primitive

		// if user-defined data structure in StructureLUT...
		multiFieldDataStructure data = (multiFieldDataStructure) StructureLUT.get(st.sval);
		if(data != null) {
//			System.out.println("Found a data structure we've seen before.");
			boolean ptrToStruct = false;
			st.nextToken();
			if(st.ttype==st.TT_WORD && (st.sval.equals("FAR") || st.sval.equals("NEAR")))
				st.nextToken();
			if(st.ttype == '*') { // change pointers to structs to ints.
				st.nextToken();
				ptrToStruct = true;
			}
			String fieldname = st.sval;
			st.nextToken();
			if(st.ttype == '[') { // Ignoring arrays of structures for now.
				System.out.println("Ignoring an array of structures, "+data.getName()+"[]");
				while(st.nextToken() != separator && st.ttype != terminator);
				throw new PuntException("ignoring an array of "+(data.isStruct() ? "structs " : "unions ")+data.getName(), fieldname);
			}
			if(st.ttype != separator && st.ttype != terminator)
				throw new UnrecognizedCodeException("Found an odd mark after a structure! token="+(char)st.ttype);
//			System.out.println("read in Data structure of type "+data.getName()+", named "+fieldname+" here.");
			if(isInsideStruct)
				var = new Field(data, fieldname);
			else
				var = new Variable(data, fieldname);
			var.setPointer(ptrToStruct);
			return var;
		}  // end in StructureLUT

		// if "struct" or "union" or "class"...
		if(st.sval.equals("struct") || st.sval.equals("union") || st.sval.equals("class")) {
			multiFieldDataStructure newData = (multiFieldDataStructure) ReadStructure(st, true);
			if(newData == null)
				throw new PuntException("Punting because we got a null structure while reading one in.", "");
			// st could be at one of two places:  on the terminating } in the structure if 
			// this was an embedded structure, or on the fieldname if this was something like:
			// struct struct_name * fieldname;   <--- used in linked list-like structures.
			// Read in the field name, the only string following this.  may not exist though.
			// However, we should deal with words like volatile in here.
			if(st.ttype == '}')
				st.nextToken();
			if(st.ttype == ';') {
				if(isInsideStruct)
					var = new Field(newData, "anonymous_field");
				else
					var = new Variable(newData, "anonymous_field");
			}
			else {
				if(st.ttype != st.TT_WORD)
					throw new UnrecognizedCodeException("maybe there was a pointer in a structure's field name?");
				String fieldname = st.sval;
				if(newData.isComplete()) {
					if(isInsideStruct)
						var = new Field(newData, fieldname);
					else
						var = new Variable(newData, fieldname);
				}
				else {
					if(isInsideStruct)
						var = new Field("int", fieldname);
					else
						var = new Variable("int", fieldname);
				}
				st.nextToken();
				if(st.ttype != ';')
					throw new UnrecognizedCodeException("Ack!  readField expected a ';' but found a "+
					    (char)st.ttype+(st.ttype==st.TT_WORD ? " sval="+st.sval : ""));
			}
			return var;
		}  // end struct or union.

		// Handle callback functions with a good guess...
		if(st.sval.toLowerCase().endsWith("callback") || st.sval.toLowerCase().endsWith("proc")
			|| st.sval.toLowerCase().endsWith("routine")) {
			String ptrFuncType = st.sval;
			if(!TypeLUT.containsKey(ptrFuncType))
				TypeLUT.put(ptrFuncType, CallbackString);
			while(st.nextToken()=='*');
//			System.out.println("Adding pointer to function field "+st.sval);
			if(isInsideStruct) {
				var = new Field(CallbackString, st.sval);
				((Field)var).setStatic(isStatic);
				((Field)var).setMutable(isMutable);
				((Field)var).setVirtual(isVirtual);
			}
			else
				var = new Variable(CallbackString, st.sval);
			var.setConst(isConst);
			var.setVolatile(isVolatile);

			st.nextToken(); // read the ';'
			return var;
		}

		// For now, if we hit here, deal with it as a type we punted on.  So punt on this
		// type too.  If we take this line out, make sure to uncomment the lost exception below.
		throw new PuntException("type not recognized in readField.  You probably punted on: ", st.sval);

		// if we reach here, we're lost.  (You should have called return by now)
		//throw new UnrecognizedCodeException("Lost in readField! word is "+st.sval);

		//System.out.println("Done w/ readField.");
		//return var;
	}

	/**
	 * Starting to build a real Expression parser now, finally.
	 * Returns a numerical expression parsed from st.
	 * If we hit a '(' or a series of operations, then cascade
	 * forward and recurse, building a tree of NumExpressions.<p><pre>
	 * Grammar: UnaryOperator NumExpression
	 *				NumExpression UnaryOperator
	 *				NumExpression BinaryOperator NumExpression
	 *				NumExpression BinaryOperator NumExpression BinaryOperator NumExpression
	 * </pre>
	 * @return NumExpression of parsed number, or null if none exist.
	 * @exception NumExprSyntaxError if syntax was messed up.
	 * @exception IOException if StreamTokenizer doesn't work.
	 * @exception InvalidParameterException if parseCNum is passed invalid data.
	 */
	NumExpression parseNumExp(StreamTokenizer st, char terminator) throws NumExprSyntaxError, IOException, BadOperationException, InvalidParameterException
	{
		if(st.ttype == terminator)
			return null;
		st.ordinaryChar('-');
//		st.ordinaryChar('/');
		NumExpression first = null;
		Operator preOperator = null;
		Operator operator = null;
		boolean paren = false;  // use for order of operations fixup.
		boolean unary = false;

		// check for unary prefix operators
		if(isCOperator((char)st.ttype))
			preOperator = readOperator(st, true);
		if(preOperator != null)
			unary = preOperator.isUnaryOperator();

		// Read first token.
		if(st.ttype == st.TT_NUMBER) {
			first = parseCNum(st);
			st.nextToken();
		}
		else if(st.ttype == '(') {
			st.nextToken();
			paren = true;
			first = parseNumExp(st, ')');
			if(first==null)
				throw new NumExprSyntaxError("Empty parenthesized expression!", "()");
//			System.out.println("Paren eval - First was: "+first+"  evals to: "+first.eval());
			st.nextToken();
		}
		else if(st.ttype==st.TT_WORD) {
			// Try looking up in known constants tables.
			throw new NumExprSyntaxError("Found word in numerical expression!", st.sval);
		}

		// Read in one symbol  Check for terminator.  Happens commonly, like in ++x;
		// or in (-1);  Most common case though:  1;
		if(st.ttype == terminator) {
			if(preOperator != null && unary)
				return new IntExpression(preOperator.getOp(), first);
			else
				return first;
		}

		// What about x-++y+1;  Correct parsing: [(x) - (++y)] + (1)
		// I think the ++y would have been handled already.
		// How do I parse operand Operator Operator operand, like x-++y;?
		if(isCOperator((char)st.ttype))
			operator = readOperator(st, false);
			
		//st.nextToken();
		if(unary) {
			if(st.ttype != terminator)
				throw new NumExprSyntaxError("Read in unary operator \""+operator+"\" but didn't find terminator!", "token: "+(char)st.ttype+" sval: "+st.sval);
			return new IntExpression(first, operator.getOp());
		}

		// Have read in one symbol plus operator.
		if(st.ttype == terminator)
			throw new NumExprSyntaxError("Read in binary operator \""+operator+"\" but didn't find another operand!", "token: "+(char)st.ttype+" sval: "+st.sval);


		// Read second token.
		NumExpression second = null;
		if(st.ttype == st.TT_NUMBER) {
			second = parseCNum(st);
			st.nextToken();
		}
		else if(st.ttype == '(') {
			st.nextToken();
			paren = true;
			second = parseNumExp(st, ')');
			if(first==null)
				throw new NumExprSyntaxError("Empty parenthesized expression!", "()");
			st.nextToken();
		}
		else if(st.ttype==st.TT_WORD) {
			// Try looking up in known constants tables.
			throw new NumExprSyntaxError("Found word in numerical expression!", st.sval);
		}
		else if(isCOperator((char)st.ttype)) {
			return new IntExpression(first, operator.getOp());
		}

		if(st.ttype == terminator)
			return new IntExpression(first, operator.getOp(), second);
//		else
//			System.out.println("Need to deal with compound expressions and add recursion.");

		Operator secondOp = readOperator(st, false);

		if(secondOp==null)
			throw new NumExprSyntaxError("Read in "+first+" "+operator+" "+second+" then expected an operand.", ""+(char)st.ttype);

		// Deal with long strings of operations, like (5 + 6 * 10) and make sure order of
		// operations is done correctly, if neither of the operands is parenthesized (!paren)
		// What about this: (1+2*3) * (1*2+3) + 1*5 -1
//		if(!paren) {
			//System.out.println("Checking order of operations for "+operator+" and "+secondOp);
			// Worry about precedent.
			if(operator.getPrecedent() >= secondOp.getPrecedent()) {
				IntExpression left = new IntExpression(first, operator.getOp(), second);
				NumExpression right = parseNumExp(st, terminator);
				return new IntExpression(left, secondOp.getOp(), right);
			} 
			else {
				NumExpression left = first;
				NumExpression tail = parseNumExp(st, terminator);
				NumExpression right = new IntExpression(second, secondOp.getOp(), tail);
				return new IntExpression(left, operator.getOp(), right);
			}
//		}
/*
		System.out.println("Default return case, unparenthesized dual expressions.  Didn't check precedence.");
		NumExpression tail = parseNumExp(st, terminator);
		return new IntExpression(first, operator.getOp(), new IntExpression(second, secondOp.getOp(), tail));
*/
	}


	/**
	 * Is this character an operator or a valid first token in an operator in C?
	 * @param c char to test
	 * @return true if c is a C operator or the first character in a C operator, else false
	 */
	public boolean isCOperator(char c)
	{
		if(c == '&' || c == '|' || c == '+' || c == '-' || c == '*' || c == '/' ||
			c == '%' || c == '~' || c == '<' || c == '>' || c == '|' || c == '=' || 
			c == '^')
			return true;
		return false;
	}

	/**
	 * Reads in a C++ operator, given a set of constraints on what this operator could be.
	 * @param st StreamTokenizer positioned at start of operator.
	 * @return Operator instance of token we just read.
	 * @exception IOException if StreamTokenizer has problems.
	 */
	public Operator readOperator(StreamTokenizer st, boolean couldBePrefix) throws IOException
	{
		Operator op = null;
		String opname = null;
		boolean unary = false;
		char firstchar;

		if(isCOperator((char)st.ttype)) {
			opname = ""+(char)st.ttype;
			firstchar = (char)st.ttype;
		}
		else {
			st.pushBack();
			return null;
		}
		st.nextToken();

		// Unary two-token operators
		if(firstchar==st.ttype && (st.ttype=='+' || st.ttype == '-')) {
			unary = true;
			opname = opname+(char)st.ttype;
			st.nextToken();
		}
		// binary two-token operators
		else if(st.ttype == '=' || st.ttype == '&' ||
			st.ttype == '|' || st.ttype == '<' || st.ttype == '>') {
			opname = opname+(char)st.ttype;
			couldBePrefix = false;
			st.nextToken();
		}

		try {
			op = getOperator(opname, unary, couldBePrefix);
		}
		catch (BadOperationException e) {
			System.out.println("Ack! readOperator caught "+e+" from getOperator!");
			System.out.println(e.Description);
			System.exit(1);
		}

		return op;
	}


	/**
	 * Parse a C integer or a float, in decimal or hex, into an appropriate NumExpression
	 * and return it.
	 * @param st StreamTokenizer positioned where we should start reading a number.
	 * @return NumExpression containing the parsed number.
	 * @exception IOException if StreamTokenizer doesn't work.
	 * @exception InvalidParameterException if st isn't positioned at a number or a '-'.
	 */
	NumExpression parseCNum(StreamTokenizer st) throws IOException, InvalidParameterException
	{
		if(st.ttype != st.TT_NUMBER && st.ttype != '-') {
			System.out.println("Invalid StreamTokenizer in parseNum!");
			throw new InvalidParameterException("StreamTokenizer mispositioned in parseCNum!");
		}
		NumExpression num = null;
		String text = "";
		boolean negative = false;
		boolean doULcheck = true;
		boolean isLong = false;
		boolean isDouble = false;
		if(st.ttype=='-') {
			st.nextToken();
			negative = true;
		}

		Double d = new Double(st.nval);
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
					isLong = true;
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
					isDouble = true;
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
		if(isDouble)
			System.out.println("Ack! Can't parse doubles yet!");  // more to the point, can't return doubles yet.
		else if(isLong)
			num = new IntExpression((new Long(text)).longValue());
		else  // isInt
			num = new IntExpression((new Integer(text)).intValue());

		return num;
	}  // end parseCNum


	/**
	 * Handles #pragma pack lines.  Adjusts packsize stack as needed.
	 * @param st StreamTokenizer positioned on a #pragma pack (specifically on "pack").
	 * @param packsize Stack of PackContainer's representing current alignment.
	 * @return No return value.
	 * @exception InvalidParameterException if st isn't positioned on the word "pack"
	 * @exception IOException if st encounters an I/O error.
	 * @exception UnrecognizedCodeException if PackHandler encounters some strange syntax.
	 * @see PackContainer.html
	 */
	protected void PackHandler(StreamTokenizer st, Stack packsize) throws InvalidParameterException, IOException, UnrecognizedCodeException
	{
		if(st.ttype != st.TT_WORD || !st.sval.equals("pack"))
			throw new InvalidParameterException("PackHandler passed stream tokenizer that wasn't on \"pack\" keyword.");

		if(DEBUG>3)
			System.out.println("Found a pack command... ");
		st.nextToken();
		st.nextToken();
		if(st.ttype == ')') {   // #pragma pack()  As far as I can tell, this is a pop.
			packsize.pop();
		}
		else if(st.ttype == st.TT_NUMBER) {
			int n = (new Double(st.nval)).intValue();
			// Add this to the stack, don't destroy what's there.
			packsize.push(new PackContainer(n));
			//System.out.println("Changed pack size to " + (int)st.nval);
		} 
		else if(st.ttype==st.TT_WORD && st.sval.equals("push")) {
			st.nextToken();
			if(st.ttype == ')')
				return;
			st.nextToken();
			String label = null;
			if(st.ttype==st.TT_WORD) {  // in wininet.h:  #pragma pack(push, wininet, 4)
				label = st.sval;
				st.nextToken();
				st.nextToken();
			}
			int n = 0;  // Default invalid number, to find bugs.
			if(st.ttype == st.TT_NUMBER)
				n = (new Double(st.nval)).intValue();
			if(label == null)
				packsize.push(new PackContainer(n));
			else
				packsize.push(new PackContainer(n, label));
			st.nextToken();
			//System.out.println("Pushed pack size of "+(int)st.nval+(label==null?"":", label was "+label));
		} // end #pragma pack(push, n)
		else if(st.ttype==st.TT_WORD && st.sval.equals("pop")) {
			String label = null;
			st.nextToken();
			if(st.ttype==',') { // Found a label to search for.
				// BUGBUG: doesn't support #pragma pack(pop, n);  n = [1, 2, 4, 8]
				PackContainer p;
				st.nextToken();
				if(st.ttype != st.TT_WORD)
					throw new UnrecognizedCodeException("Ack!  PackHandler on \"pack(pop, \" looking for a string and found "+(char)st.ttype+" instead.");
				label = st.sval;
				do {
					p = (PackContainer) packsize.pop();
				} while (p!=null && !p.hasLabel() && !p.getLabel().equals(label));
				if(p==null)
					throw new UnrecognizedCodeException("Ack!  PackHandler was searching for label "+label+" during a pop, but the stack is empty!!!");
			}
			else
				packsize.pop();
			st.nextToken();
			//System.out.println("pack size pop"+(label==null?"":", label was "+label));
		} // end #pragma pack(pop)
		else
			System.out.println("Ack!  unknown pack syntax \"" + st.sval+"\"");
		st.nextToken();
		//System.out.println("Done w/ pack.");
	} // end PackHandler (#pragma pack)
	

	/**
	 * Reads in a symbol file, adding all symbols to the Symbol table, noting which file
	 * each symbol came from for use later when putting functions in files.<p>
	 * 
	 * Symbol files can be generated by calling dumpbin on a library, like this:<p>
	 * <pre>dumpbin /exports c:\windows\system\kernel32.dll > kernel32.sym</pre><p>
	 *
	 * Do not edit symbol files, except to get rid of function names with question marks
	 * or other really odd names in them.  You can leave the Microsoft dumpbin
	 * header + trailer info, or you can remove them if you need to.  (Its not used by 
	 * this program, but there is a keyword used to stop skipping over the header).
	 * Symbol files should contain info like this:<p>
	 * <pre>
	 *                   1    0   AddAtomA  (000079FE)
	 *                   2    1   AddAtomW  (00004478)
	 * </pre>
	 * @param File Symbol file name.
	 * @return No return value.
	 * @exception BadInputFileException if file is not strictly the output of dumpbin /exports
	 * @exception InvalidParameterException if one of the functions called here failed.
	 */
	protected void ParseSymbolFile(String File) throws BadInputFileException, InvalidParameterException
	{
		if(File==null || File.equals(""))
			throw new BadInputFileException("ParseSymbolFile won't accept a null or blank file name!");

		if(Symbols == null)
			Symbols = new Vector();

		// Extract library name to store in function.
		String libname = null;
		StringTokenizer parse = new StringTokenizer(File, "\\");
		while(parse.hasMoreTokens()) {
			libname = parse.nextToken();
		}
		if(libname == null)
			throw new BadInputFileException("I couldn't parse the name of the file!");
		if(libname.endsWith(".sym")) {
			libname = libname.toUpperCase().substring(0, libname.length()-4);
//			System.out.println("Mangled lib name: "+libname);
		}

		try {
			InputStreamReader isr = new InputStreamReader((InputStream) (new FileInputStream(File)));
			StreamTokenizer st = new StreamTokenizer(isr);
			st.eolIsSignificant(true);
			st.wordChars('_', '_');
			//st.wordChars('0', '9');  // to handle hex numbers in file

			st.nextToken();  // Do this to read in MS dumpbin output without needing to edit files.
			if(st.ttype==st.TT_WORD && st.sval.equals("Microsoft")) {
				// Read through to beginning of symbols in symbol file.
				while(st.nextToken() != st.TT_EOF) {
					if(st.ttype==st.TT_WORD && st.sval.equals("name")) {
						st.nextToken();
						st.nextToken();
						break;
					}
				}
			}
			else
				st.pushBack();

			while(st.nextToken() != StreamTokenizer.TT_EOF) {
				if(st.ttype == st.TT_EOL)
					continue;
				else if(st.ttype == st.TT_WORD && st.sval.equals("Summary"))
					break;
				st.nextToken();
				st.nextToken();
				if(st.ttype == StreamTokenizer.TT_NUMBER) {
					System.out.println("Ack!  st.ttype was a number!  " + st.nval);
				}
				if(st.ttype != StreamTokenizer.TT_WORD) {
					throw new BadInputFileException("Expected a string, found junk in file " + File + "\r\nst.ttype was "+((char)st.ttype) + "\tst.nval was " + st.nval);
				}

				if(st.sval.length() <= 2)  // hex digit
					st.nextToken();

				Function func = new Function(st.sval);
				func.setLibrary(libname);
				//System.out.println("Adding Symbol " + func.getName());
				Symbols.addElement(func);

				st.nextToken();
				// Read until end of line.
				while(st.nextToken() != StreamTokenizer.TT_EOL && st.ttype != StreamTokenizer.TT_EOF);
			}

			isr.close();
			isr = null;
		}
		catch (IOException e) 
		{
			System.out.println("\r\nIO Exception caught while trying to parse symbol file "+ File+": "+ e);
			e.printStackTrace();
		}
	}


	/** 
	 * Compares parsed functions with symbols from a DLL.  Assumes a file has been 
	 * parsed and a symbols file has been read in.
	 * @return No return value.
	 */
	protected void CompareFunctionWithSymbols()
	{
		Function f;
		Function s;
		int i=0;
		int j=0;
		try {
			PrintWriter notdll = new PrintWriter(new FileOutputStream("notindll.txt"));
			PrintWriter indll = new PrintWriter(new FileOutputStream("indll.txt"));
			
			while(i<Functions.size() && j<Symbols.size())
			{
				f = (Function) Functions.elementAt(i);
				s = (Function) Symbols.elementAt(j);
				if(f.getName().equals(s.getName())) {
					i++;
					j++;
				} 
				else if(f.getName().compareTo(s.getName()) < 0)  {
					i++;
					// output f - it wasn't in the DLL symbols.
					notdll.println(f.getName());
					System.out.println("Not in DLL: " + f.toString());
				}
				else {
					j++;
					// output s - it wasn't in my parsed function.
					indll.println(s.getName());
					System.out.println("MISSED THIS FUNCTION: " + s.toString());
				}
			}

			notdll.close();
			indll.close();
		}
		catch (IOException e)
		{
			System.out.println("IOException in CompareFunctionWithSymbols.\r\n" + e);
		}
	}


	/**
	 * Scans through read in functions, looking for the ASCII and Unicode versions of
	 * any such functions.  If it finds them both, it will strip off the last 
	 * character, merging them into one function call.  Deals with the 4 special
	 * cases I found in the Win32 API.
	 * @return No return value.
	 */
	public void UnifyFunctions()
	{
		Function f;
		String search;
		//System.out.print("Unifying ASCII and Unicode versions of functions... ");
		for(int i=0; i<Functions.size(); i++) {
			search = null;
			Function Unicode_f = null;  // Remember which was the unicode version.
			String rootname = null;
			f = (Function) Functions.elementAt(i);
			// Check whether last character is an 'A' or a 'W'
			// Special cases:            Other version:          Expose as:
			// CommandLineToArgvW    --> X                       CommandLineToArgvW
			// GetEnviromentStringsW --> GetEnvironmentStrings   GetEnvironmentStrings
			// LHashValOfNameSysA    --> LHashValOfNameSys       LHashValOfNameSys
			// ReadDirectoryChangesW --> X                       ReadDirectoryChangesW
			// wglGetProcAddress     --> X (only ASCII version)  wglGetProcAddress
			// CharPrevExA           --> X                       CharPrevExA
			// CharNextExA           --> X                       CharNextExA
			// RegisterMediaTypesW   --> RegisterMediaTypes      RegisterMediaTypes
			// LineDDA is NOT a string function.  It just ends with a 'A'.
			if(f.getName().endsWith("A") && !f.getName().equals("LineDDA")) {
				rootname = f.getName().substring(0, f.getName().length()-1);
//				System.out.println("Searching for function root " + rootname);
				// Handle special cases.  Append 'W' in normal case.
				if(!rootname.equals("LHashValOfNameSys"))
					search = rootname + "W";
			}
			else if(f.getName().endsWith("W")) {
				rootname = f.getName().substring(0, f.getName().length()-1);
//				System.out.println("Searching for function root " + rootname);
				// Handle special cases.  Append 'A' in normal case.
				if(!rootname.equals("CommandLineToArgv") && !rootname.equals("ReadDirectoryChanges")) {
					if(rootname.equals("GetEnvironmentStrings") || rootname.equals("RegisterMediaTypes"))
						search = rootname;
					else
						search = rootname + "A";  // Normal case.
				}
				Unicode_f = f;
			}
			// look up search in Functions list. If found, remove one and rename Unicode one.
			if(search!=null) {
				Function search_func = findFunction(search);
				if(search_func != null) {
//					System.out.println("Removing " + f.getName() + " and " + search + ", replacing with " + rootname);
//					System.out.print(".");
					// Leave the Unicode one in our Function array - types are closer to Java.
					if(Unicode_f == null) {
						Functions.removeElement(f);
						Unicode_f = search_func;
					} else
						Functions.removeElement(search_func);
					Unicode_f.setName(rootname);
				}
				else
					System.out.println("\r\nFound one version of a function ("+f.getName()+"), but not the other!");
			}
		}
		//System.out.println("Done.");
	}

	/**
	 * Scans through read in functions, looking for the ASCII and Unicode versions of
	 * any such functions.  If it finds them both, it will strip off the last 
	 * character, merging them into one function call.  Deals with the 4 special
	 * cases I found in the Win32 API.
	 * @return No return value.
	 */
	public void UnifyStructures()
	{
		multiFieldDataStructure data;
		multiFieldDataStructure ASCIIdata;
		multiFieldDataStructure Unicodedata;
		String rootname = null;
		System.out.print("Unifying ASCII and Unicode versions of data structures... ");
		// Must use enumeration interface
		Enumeration e = StructureLUT.elements();
		while(e.hasMoreElements()) {
			ASCIIdata = null;
			Unicodedata = null;
			data = (multiFieldDataStructure) e.nextElement();

		  if(data.getName().endsWith("A")) {
				ASCIIdata = data;
				rootname = data.getName().substring(0, data.getName().length()-1);
				Unicodedata = (multiFieldDataStructure) StructureLUT.get(rootname+"W");
			}
			else if(data.getName().endsWith("W")) {
				Unicodedata = data;
				rootname = data.getName().substring(0, data.getName().length()-1);
				ASCIIdata = (multiFieldDataStructure) StructureLUT.get(rootname+"A");
			}
			if(Unicodedata != null && ASCIIdata != null) {
				if(Unicodedata == ASCIIdata) {
					System.out.println("For "+data.getName()+", two structures were equal!");
					continue;
				}
//				System.out.print("Unifying structs to "+rootname+"... ");
				Unicodedata.setMerged(true);
				Unicodedata.addAltName(Unicodedata.getName());
				Unicodedata.setName(rootname);
				Unicodedata.addAltName(rootname+"A");
				// Get all of ascii version's alias names and put them into unicode's aliases?
				//ASCIIdata.setName(rootname);
				StructureLUT.remove(ASCIIdata.getName());
				//System.out.print("removing "+ASCIIdata.numAltNames()+" altnames... ");
				for(int i=0; i<ASCIIdata.numAltNames(); i++) {
					String altname = ASCIIdata.getAltName(i);
					Unicodedata.addAltName(altname);
					StructureLUT.remove(altname);  // give it key to remove...
					StructureLUT.put(altname, Unicodedata);
				}
				//System.out.print("copied names... ");
				e = StructureLUT.elements();
//				System.out.println("Done.");
				continue;
			}
		}
		System.out.println("Done with data structure unification.");
	}  // end UnifyStructures

	/**
	 * Builds file Include and Exclude lists.  Here is where we set IncludeHeaders
	 * and ExcludeHeaders to their original values.  This should be edited when you add
	 * a new set of libraries, although the default rules should let your own header files
	 * be parsed with a warning.  Remember, this program can't parse COM.
	 * @return No return value.
	 */
	protected void SetupFileFilters()
	{
		ExcludeHeaders = new Vector();
		IncludeHeaders = new Vector();

		// Standard headers
		ExcludeHeaders.addElement("stdlib.h");
		ExcludeHeaders.addElement("stdarg.h");
		ExcludeHeaders.addElement("stdio.h");
		ExcludeHeaders.addElement("string.h");
		ExcludeHeaders.addElement("strings.h");
		ExcludeHeaders.addElement("varargs.h");
		ExcludeHeaders.addElement("math.h");
		// Can't process any COM libraries.
		ExcludeHeaders.addElement("ole.h");
		ExcludeHeaders.addElement("ole2.h");
		ExcludeHeaders.addElement("ole2ver.h");
		ExcludeHeaders.addElement("oleauto.h");
		ExcludeHeaders.addElement("olectl.h");
		ExcludeHeaders.addElement("olectlid.h");
		ExcludeHeaders.addElement("oledlg.h");
		ExcludeHeaders.addElement("oleidl.h");
		ExcludeHeaders.addElement("olenls.h");

		ExcludeHeaders.addElement("imm.h");
		ExcludeHeaders.addElement("excpt.h");
		ExcludeHeaders.addElement("winsvc.h");
		ExcludeHeaders.addElement("mcx.h");     // modem control
//		ExcludeHeaders.addElement("winnls.h");  // natural language services
		ExcludeHeaders.addElement("winnetwk.h");
		ExcludeHeaders.addElement("winsock.h");
		ExcludeHeaders.addElement("winsock2.h");
		ExcludeHeaders.addElement("dde.h");     // dynamic data exchange
		ExcludeHeaders.addElement("ddeml.h");   // Sobesky says DDE is implemented badly with many 95/NT differences
		ExcludeHeaders.addElement("winreg.h");  // registry
		ExcludeHeaders.addElement("nb30.h");    // netbios
		ExcludeHeaders.addElement("winperf.h"); // performance monitor
		ExcludeHeaders.addElement("unknwn.h");  // RPC stubs
		ExcludeHeaders.addElement("wtypes.h");  // more RPC types?  Really gross file.
		ExcludeHeaders.addElement("cguid.h");   // odd constants?
		ExcludeHeaders.addElement("mswsock.h"); // MS socket Extensions, NT only????
		ExcludeHeaders.addElement("objbase.h"); // COM/OLE stuff
		ExcludeHeaders.addElement("aclapi.h");  // some ACL stuff (rest is in winbase.h)
		ExcludeHeaders.addElement("wintrust.h");
		ExcludeHeaders.addElement("ctype.h");   // ischar() type macros.
		ExcludeHeaders.addElement("urlmon.h");  // URL accessing functions (Uses COM)
		ExcludeHeaders.addElement("vfw.h");     // Video for Windows (Uses COM)

		// At this point, concentrate on these:
		// Kernel, User, GDI, Shell, commctrl, commdlg
		IncludeHeaders.addElement("gen.h");     // My wrapper for generating mega.prep.
		IncludeHeaders.addElement("windows.h"); // Doesn't declare any functions
		IncludeHeaders.addElement("winuser.h");
		IncludeHeaders.addElement("wingdi.h");
		IncludeHeaders.addElement("winbase.h");
		IncludeHeaders.addElement("winnt.h");
		IncludeHeaders.addElement("windef.h");
		IncludeHeaders.addElement("shellapi.h");
		IncludeHeaders.addElement("winerror.h");// no functions, but probably worth including.
		IncludeHeaders.addElement("winver.h");  // version of windows files
		IncludeHeaders.addElement("cderr.h");   // No functions here, but we need it.
		IncludeHeaders.addElement("commdlg.h");
		IncludeHeaders.addElement("dlgs.h");    // no functions, but...
		IncludeHeaders.addElement("prsht.h");   // CommCtrl.h & windows.h include this

		// Not included by windows.h, but important.
		IncludeHeaders.addElement("commctrl.h");// CommCtrl

		// OpenGL
		IncludeHeaders.addElement("gl.h");
		IncludeHeaders.addElement("glu.h");
		IncludeHeaders.addElement("glaux.h");
		IncludeHeaders.addElement("GL/gl.h");
		IncludeHeaders.addElement("GL/glu.h");
		IncludeHeaders.addElement("GL/glaux.h");

		// Added for the Java Office group (they call these functions)
		IncludeHeaders.addElement("winnls.h");  // language services?
		IncludeHeaders.addElement("winspool.h");// printer

		// Added because people thought it was cool
		IncludeHeaders.addElement("mmsystem.h");// MCI (multimedia control interface)
		IncludeHeaders.addElement("mciavi.h");  // Movie player

		// Added for no good reason
		IncludeHeaders.addElement("wincon.h");  // NT Console
		IncludeHeaders.addElement("wincrypt.h");
		IncludeHeaders.addElement("lzexpand.h");// LZ
		IncludeHeaders.addElement("wininet.h"); // Windows internet wrappers (FTP, etc)

		// Need to process these to get the alignment of the C structures.
		IncludeHeaders.addElement("pshpack1.h");
		IncludeHeaders.addElement("pshpack2.h");
		IncludeHeaders.addElement("pshpack4.h");
		IncludeHeaders.addElement("pshpack8.h");
		IncludeHeaders.addElement("poppack.h");
	}


	/**
	 * Initializes hash table containing package files for each of the DLL's.  To add
	 * a new output class, create a PrintWriter for it, output the header info and class
	 * name to it, and add it to the hash table, using the symbol file name as the key.
	 * This function totally controls how various functions are routed into their own
	 * Java classes.
	 * @return No return value.
	 */
	protected void SetupOutputClasses()
	{
		OutputClasses = new Hashtable();
		String path = "com\\ms\\win32\\";
		
		try {
			// Create a PrintWriter associated with the output file.
			PrintWriter kernel = new PrintWriter(new FileOutputStream(path+"Kernel32.java"));
			PrintWriter user = new PrintWriter(new FileOutputStream(path+"User32.java"));
			PrintWriter shell = new PrintWriter(new FileOutputStream(path+"Shell32.java"));
			PrintWriter gdi = new PrintWriter(new FileOutputStream(path+"Gdi32.java"));
			PrintWriter spool = new PrintWriter(new FileOutputStream(path+"Spoolss.java"));
			PrintWriter advapi = new PrintWriter(new FileOutputStream(path+"Advapi32.java"));
			PrintWriter comdlg = new PrintWriter(new FileOutputStream(path+"Comdlg32.java"));
			PrintWriter commctrl = new PrintWriter(new FileOutputStream(path+"Comctl32.java"));
			PrintWriter winmm = new PrintWriter(new FileOutputStream(path+"Winmm.java"));
			PrintWriter misc = new PrintWriter(new FileOutputStream(path+"Misc.java"));
			PrintWriter opengl = new PrintWriter(new FileOutputStream(path+"OpenGL.java"));
			PrintWriter lz = new PrintWriter(new FileOutputStream(path+"Lz32.java"));
			PrintWriter mapi = new PrintWriter(new FileOutputStream(path+"Mapi32.java"));
			PrintWriter wininet = new PrintWriter(new FileOutputStream(path+"Wininet.java"));

			String Header = CopyrightNotice 
				+"\r\n\r\npackage "+PackageName+";\r\n\r\npublic class ";
			// Output the package name and other necessary tokens
			kernel.println(Header+"Kernel32 {");
			user.println(Header+"User32 {");
			shell.println(Header+"Shell32 {");
			gdi.println(Header+"Gdi32 {");
			spool.println(Header+"Spoolss {");
			advapi.println(Header+"Advapi32 {");
			comdlg.println(Header+"Comdlg32 {");
			commctrl.println(Header+"Comctl32 {");
			winmm.println(Header+"Winmm {");
			misc.println(Header+"Misc {");
			opengl.println(Header+"OpenGL {");
			lz.println(Header+"Lz32 {");
			mapi.println(Header+"Mapi32 {");
			wininet.println(Header+"Wininet {");

			// Here you set up the mapping between the DLL the function occurs in and 
			// the output class.  Use all upper case and this must match the name of the
			// symbol file (without the .sym) generated by dumpbin.
			OutputClasses.put("KERNEL32", kernel);
			OutputClasses.put("USER32", user);
			OutputClasses.put("SHELL32", shell);
			OutputClasses.put("GDI32", gdi);
			OutputClasses.put("SPOOLSS", spool);
			OutputClasses.put("ADVAPI32", advapi);
			OutputClasses.put("COMDLG32", comdlg);
			OutputClasses.put("COMCTL32", commctrl);
			OutputClasses.put("WINMM", winmm);
			OutputClasses.put("GLU32", opengl);
			OutputClasses.put("OPENGL32", opengl);
			OutputClasses.put("LZ32", lz);
			OutputClasses.put("MAPI32", mapi);
			OutputClasses.put("WININET", wininet);
			OutputClasses.put("WINTRUST", misc);
			OutputClasses.put("VERSION", misc);
			// Default case - if a function isn't listed in any symbol file.
			OutputClasses.put(UnknownLibraryString, misc);
		}
		catch (IOException e) {
			System.out.println("problem in SetupOutputClasses(): "+e);
			System.exit(2);
		}	
	}

	/**
	 * Set up a table of C operator precedence.  Taken from the VC++ 5 online help.
	 * Keys are String's containing operator and values are ints describing precedence,
	 * with 0 being the lowest.  Duplicate entries are handled by appending odd 
	 * characters that convey some sense of the meaning with them.  I spaced out the
	 * precedence numbers to add new operators, in case the table was incomplete or if
	 * the ISO committee goes change-happy.
	 * @return No return value.
	 */
	protected void SetupPrecedenceTable()
	{
		Precedence = new Hashtable();
		// Anyone remember line numbers in BASIC?
		Precedence.put(",", new Operator(",", false, false, 10));
		Precedence.put("*=", new Operator("*=", false, false, 20));
		Precedence.put("/=", new Operator("/=", false, false, 20));
		Precedence.put("%=", new Operator("%=", false, false, 20));
		Precedence.put("+=", new Operator("+=", false, false, 20));
		Precedence.put("-=", new Operator("-=", false, false, 20));
		Precedence.put("<<=", new Operator("<<=", false, false, 20));
		Precedence.put(">>=", new Operator(">>=", false, false, 20));
		Precedence.put("&=", new Operator("&=", false, false, 20));
		Precedence.put("^=", new Operator("^=", false, false, 20));
		Precedence.put("|=", new Operator("|=", false, false, 20));
		Precedence.put("=", new Operator("=", false, false, 30));
		Precedence.put("?:", new Operator("?:", false, false, 40));
		Precedence.put("||", new Operator("||", false, false, 50));
		Precedence.put("&&", new Operator("&&", false, false, 60));
		Precedence.put("|", new Operator("|", false, false, 70));
		Precedence.put("^", new Operator("^", false, false, 80));
		Precedence.put("&", new Operator("&", false, false, 90));  // bitwise and, not address
		Precedence.put("!=", new Operator("!=", false, false, 100));
		Precedence.put("==", new Operator("==", false, false, 110));
		Precedence.put(">=", new Operator(">=", false, false, 120));
		Precedence.put(">", new Operator(">", false, false, 130));
		Precedence.put("<=", new Operator("<=", false, false, 140));
		Precedence.put("<", new Operator("<", false, false, 150));
		Precedence.put(">>", new Operator(">>", false, false, 160));
		Precedence.put("<<", new Operator("<<", false, false, 170));
		Precedence.put("-", new Operator("-", false, false, 180));  // subtraction
		Precedence.put("+", new Operator("+", false, false, 190));
		Precedence.put("%", new Operator("%", false, false, 200));
		Precedence.put("/", new Operator("/", false, false, 210));
		Precedence.put("*", new Operator("*", false, false, 220));  // multiplication, not dereference
		// Here the help gets a little weird.  I'm not sure how to interpret
		// ->*  and .*_  They're described as pointers to members, for pointers vs. objects
		Precedence.put("->*", new Operator("->*", false, false, 230));
		Precedence.put(".*_", new Operator(".*_", false, false, 240));
		Precedence.put("(cast)", new Operator("(cast)", true, true, 250));
		Precedence.put("delete", new Operator("delete", true, true, 260));
		Precedence.put("new", new Operator("new", true, true, 270));
		Precedence.put("sizeof", new Operator("sizeof", true, true, 280));
		Precedence.put("*u", new Operator("*", true, true, 290));    // dereference, not multiplication
		Precedence.put("&u", new Operator("&", true, true, 300));    // address, not bitwise and
		Precedence.put("+u", new Operator("+", true, true, 310));    // unary plus
		Precedence.put("-u", new Operator("-", true, true, 320));    // unary minus
		Precedence.put("~", new Operator("~", true, true, 330));
		Precedence.put("!", new Operator("/", true, true, 340));
		Precedence.put("--p", new Operator("--", true, true, 350));   // pre-decrement
		Precedence.put("++p", new Operator("++", true, true, 360));   // pre-increment
		Precedence.put(".", new Operator("%", false, false, 370));   // struct or union member
		Precedence.put("->", new Operator("->", false, false, 380));
		Precedence.put("[]", new Operator("[]", true, false, 390));
		Precedence.put("()", new Operator("()", false, false, 400)); // function call
		Precedence.put("--", new Operator("--", true, false, 410)); // post-decrement
		Precedence.put("++", new Operator("++", true, false, 420)); // post-increment
	}

	/**
	 * Returns the Operator corresponding to the operator string.  Contains precedent
	 * information, etc.
	 * @param operator String with the name of the operator
	 * @param unary is this a unary operator vs. binary
	 * @param prefix is this a prefix operator vs. postfix or infix
	 * @return Operator with same name as operator in appropriate contexts.
	 * @exception BadOperationException if operator isn't found
	 */
	Operator getOperator(String operator, boolean unary, boolean prefix) throws BadOperationException
	{
		Operator op = (Operator) Precedence.get(operator);
		if(op == null)
			throw new BadOperationException("getPrecedence called with illegal operator \""+operator+"\"");

		// Check op to make sure it's the correct operator.
		if(unary ^ op.isUnaryOperator() || prefix ^ op.isPrefixOperator()) {
			// Got wrong operator.
			if(unary)
				op = (Operator) Precedence.get(operator+"u");
			if(op==null)
				op = (Operator) Precedence.get(operator+"p");
		}

		if(op!=null && unary == op.isUnaryOperator() && prefix == op.isPrefixOperator())
			return op;
		else {
			if(op==null)
				throw new BadOperationException("getPrecedence called with unknown operator \""+operator+"\", with constraints unary: "+unary+"  prefix: "+prefix);
			else
				throw new BadOperationException("getPrecedence called with unknown operator \""+operator+"\", with constraints unary: "+unary+"  prefix: "+prefix+"\r\nOperator - isUnary: "+op.isUnaryOperator()+"  isPrefix: "+op.isPrefixOperator());
		}
	}

	
	/**
	 * Decides if we should examine the current file or not.  Checks IncludeHeaders, 
	 * ExcludeHeaders, whether its an IDL file, and whether it starts with "mm".
	 * @param File Header file we may want to parse.
	 * @return true if we should parse it, else false.
	 */
	protected boolean CheckFile(String File)
	{
		String header;
		if(File.equals(UnknownFileString))
			return true;
		for(int i=0; i<IncludeHeaders.size(); i++)
			if(File.equals((String) IncludeHeaders.elementAt(i)))
				return true;
		for(int i=0; i<ExcludeHeaders.size(); i++)
			if(File.equals((String) ExcludeHeaders.elementAt(i)))
				return false;

		// Ignore IDL files.
		if(File.endsWith("idl.h"))
			return false;
		// Ignore RPC files
		if(File.startsWith("rpc"))
			return false;

		System.out.println("Don't know about parsing " + File + "...  Will parse anyway.");
		return true;
	}  // end CheckFile(String)


	/**
	 * Finds a Function with the given name in the Functions vector, returning the 
	 * Function object.
	 * @param Name Name of the Function to look for.
	 * @return reference to the Function or null if a function with that name didn't exist.
	 */
	protected Function findFunction(String Name)
	{
		for(int i=0; i<Functions.size(); i++) {
			Function f = (Function) Functions.elementAt(i);
			if(Name.equals(f.getName()))
				return f;
		}
		return null;
	}

	/**
	 * Finds which library function occurs in based on loaded symbol files.  Assumes the
	 * symbol tables have been set up to be effective.  Changes Function's library field.
	 * @param func Function to search for in symbol tables.
	 * @return No return value.
	 */
	protected void FindLibrary(Function func) throws InvalidParameterException
	{
		if(func == null || func.getName() == null)
			throw new InvalidParameterException("FindLibrary passed an invalid Function object.");
		if(Symbols == null)
			return;
		Function sym = null;
		for(int i=0; i<Symbols.size(); i++) {
			Function f = (Function) Symbols.elementAt(i);
			if(func.getName().equals(f.getName())) {
				sym = f;
				break;
			}
		}
		if(sym == null)
			func.setLibrary(UnknownLibraryString);
		else
			func.setLibrary(sym.getLibrary());
	}


	/**
	 * Given a file name for a list of function names, it will print out the
	 * ones not in the parser's internal storage.  Writes out the missing
	 * function names to the screen and to a file.
	 * @param OfficeFileName File containing a list of function names, separated by whitespace
	 * @param MissingFileName File to output all missing function names to
	 * @return No return value.
	 */
	public void OfficeFunctions(String OfficeFileName, String MissingFileName)
	{
		try {
			System.out.println("Looking for missing functions... ");
			FileInputStream off = new FileInputStream(OfficeFileName);
			StreamTokenizer st = new StreamTokenizer(new InputStreamReader(off));
			PrintWriter missing = new PrintWriter(new FileOutputStream(MissingFileName));
			int numMissing = 0;
			st.eolIsSignificant(false);

			while(st.nextToken() != StreamTokenizer.TT_EOF) {
				if(st.ttype == StreamTokenizer.TT_WORD) {
					Function f = findFunction(st.sval);
					if(f == null) {
						System.out.println("Missing: " + st.sval);
						missing.println(st.sval);
						numMissing++;
					}
				} // end word
			}  // end while

			System.out.println("Missing " + numMissing + " Office functions.");
			missing.close();
			missing = null;
		}
		catch (IOException e) {
			System.out.println("IOException in OfficeFunctions: " + e);
			e.printStackTrace();
		}
	}

	/**
	 * Prints the functions out to the PrintWriter.  Uses the format specified in
	 * Function::toString().
	 * @param pw PrintWriter to send output to.
	 * @return No return value.
	 */
	public void WriteOutFunctions(PrintWriter pw)
	{
		System.out.print("Writing out to file... ");
		for(int i=0; i<Functions.size(); i++)
			pw.print(((Function)Functions.elementAt(i)).toString());
		System.out.println("Done.");
	} // end WriteOutFunctions(PrintWriter p)

	/**
	 * Reads in a file containing filenames of symbol files, then subsequently parses each 
	 * symbol file.  Filenames should be separated by newlines.  Comment char is '#'.
	 * @param list name of file containing paths to symbol files.
	 * @return No return value.
	 * @exception InvalidParameterException if list file isn't in the correct format.
	 */
	public void ReadListofSymbolFiles(String list) throws InvalidParameterException
	{
		boolean have_symbols = false;
		try {
			InputStreamReader isr = new InputStreamReader((InputStream) new FileInputStream(list));
			StreamTokenizer st = new StreamTokenizer(isr);
			st.eolIsSignificant(false);
			st.slashSlashComments(true);
			st.slashStarComments(true);
			st.commentChar('#');
			st.wordChars('\\', '\\');
			st.wordChars('.', '.');
			st.wordChars(':', ':');
			System.out.println("Reading DLL symbol files... ");
			while(st.nextToken() != st.TT_EOF) {
				if(st.ttype != st.TT_WORD) {
					System.out.println("Ack!  list of symbol files \""+list+"\" contained a non-word character!");
					System.out.println("Expected list of symbol files, like:\r\nc:\\symbols\\r\nt\\shell32.sym\r\nc:\\symbols\\r\nt\\kernel32.sym\r\n");
					throw new InvalidParameterException("list of symbol files \""+list+"\" was bad!");
				}
				try {
					ParseSymbolFile(st.sval);
					have_symbols = true;
				}
				catch(BadInputFileException e) {
					System.out.println("Skipping a bad symbol file! "+st.sval+"\r\n"+e.BadFile);
				}
			}
			st = null;
			isr.close();
			isr = null;

			com.ms.util.VectorSort.sort(Symbols, new FunctionCompare());
			System.out.println("Done reading symbols.");
		}
		catch(FileNotFoundException fnfe) {
			System.out.println("Couldn't find file \""+list+"\"");
		}
		catch(IOException e) {
			System.out.println("Error while reading file \""+list+"\"");
			System.out.println(e);
		}
		finally {
			if(!have_symbols) {
				System.out.print("No symbols were read in.  ");
				if(Suppress_UnknownLib_Functions)
					System.out.println("All functions will be suppressed.");
				else
					System.out.println("Functions will be output to Misc.java.");
			}
		}
	}

	/**
	 * Main.  Runs the application.
	 * @param args[] Array of Strings containing command line parameters.
	 * @return No return value.
	 */
	public static final void main(String args[])
	{
		System.out.println("Win32 API header file parser, v"+version);
		if(args.length == 0) {
			usage();
			System.exit(1);
		}

		Parser parse = new Parser();

		try {
			if(ReadSymbols) {
				parse.ReadListofSymbolFiles("symbolfiles.txt");
			}

			for(int i=0; i<args.length; i++) {
				System.out.println("Processing \"" + args[i] + "\"...");
				parse.ParseFile(args[i]);

				System.gc();  // ParseFile generates a hideous amount of garbage.

				//if(i+1 < args.length)
				//	parse.ParseSymbolFile(args[i+1]);

				// Sort Vector of Functions.
				System.out.print("Sorting... ");
				com.ms.util.VectorSort.sort(parse.Functions, new FunctionCompare());
				//com.ms.util.VectorSort.sort(parse.Symbols, new FunctionCompare());
				System.out.println("Done.");

				// Do something interesting
				//if(ReadSymbols)
				//	parse.CompareFunctionWithSymbols();

//				parse.OfficeFunctions("office.txt", "missing.txt");

				parse.UnifyFunctions();
				parse.UnifyStructures();

				// Converts C prototypes to Java
				parse.Convert();

				PrintWriter out = new PrintWriter(new FileOutputStream(args[i] + ".parse"));
				parse.WriteOutFunctions(out);
				out.close();
			}
			System.out.println("Parsing and translation complete.");
		}
		catch (IOException e)
		{
			System.out.println("Ack!  IO Exception during output!");
			System.out.println(e);
			e.printStackTrace();
		}
		catch(UnrecognizedCodeException e) {
			System.out.println(e);
			System.out.println(e.BadFragment);
			e.printStackTrace();
		}
		catch(InvalidParameterException e) {
			System.out.println(e);
			System.out.println(e.Description);
			e.printStackTrace();
		}
		catch (Exception e)
		{
			System.out.println("Uncaught exception in main.  " + e);
			e.printStackTrace();
		}
		finally {
			// Force finalizer to run and close files.
			parse.finalizer();
			parse = null;
			//System.runFinalization();
			System.gc();
		}
	} // end main
}
