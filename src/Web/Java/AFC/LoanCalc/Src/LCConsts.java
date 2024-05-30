//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
public interface LCConsts
{
	public static final String IMG_NAMES[] = { 
		"intro.gif",	"pvalue.gif",	"interest.gif",
		"numper.gif",	"payment.gif",
		"s_pvalue.gif",	"s_interest.gif",
		"s_numper.gif",	"s_payment.gif"
	};

	public static final int INTRO = 0;
	public static final int PVALUE = 1;
	public static final int INTEREST = 2;
	public static final int NUMPERIODS = 3;
	public static final int PAYMENT = 4;
	public static final int S_PVALUE = 5;
	public static final int S_INTEREST = 6;
	public static final int S_NUMPERIODS = 7;
	public static final int S_PAYMENT = 8;

	public static final int NUM_IMAGES = 9;

	public static final int IDX_IMG[] = { S_PVALUE, 
										  S_INTEREST,
										  S_NUMPERIODS,
										  S_NUMPERIODS,
										  S_PAYMENT };

	public static final String IDX_STR[] = {
		"Loan Amount:",			"Interest Rate:",	"Length of Loan:", 
		"Pmnt Frequency:",		"Payment Amount:" };

	public static final int IDX_PV = 0;
	public static final int IDX_INT = 1;
	public static final int IDX_LEN = 2;
	public static final int IDX_FREQ = 3;
	public static final int IDX_PMNT = 4;

	public static final int BL_NONE = 0;
	public static final int BL_PV = 1;
	public static final int BL_LEN = 2;
	public static final int BL_PMNT = 3;

	public static final int INIT_PV = 10000;
	public static final int INIT_RATE = 80;
	public static final int INIT_LEN = 6;
	public static final int INIT_FREQ = 0;

	public static final String INTRO_TXT = 
		"Welcome to LoanCalc!\n\n    LoanCalc will calculate and display "+
		"loan information given the loan parameters that you will enter. "+
		"LoanCalc will calculate either your loan payment, the number "+
		"of periods in your loan, or the amount of the loan. One of these "+
		"three parameters must be left blank.";

	public static final String VALUE_TXT = 
		"How much money are you borrowing?";
	public static final int MAX_PV = 9999999;

	public static final String INTEREST_TXT = 
		"At what interest rate (per annum)?";

	public static final int MIN_RATE = 24;

	public static final String PERIOD_TXT = 
		"How much time do you want to take to pay off this loan?";
	public static final String FREQ_TXT = "How often do you wish to make payments?";
	public static final String FREQ_STR[] = {
		"Monthly", "Every other month", "Every three months",
		"Every four months", "Twice per year", "Yearly"
	};
	public static final int MAX_MONTHS = 35*12; // 35 years is maximum loan length
	public static final int FREQ_FACTOR[] = { 12, 6, 4, 3, 2, 1 };
	public static final int ID_MONTHS = 551;
	public static final int ID_YEARS = 552;

	public static final String PMNT_TXT = "What size payment would you like to make?";

	public static final String FINAL_TXT = 
		"All loan parameters have been entered.\n\n    LoanCalc will now calculate "+
		"your payment schedule given the values that you have entered. "+
		"If you would like to change any of the values press the 'Back' "+
		"button, otherwise press the 'Finish' button to continue.\n\n"+
		"    The calculation may take a few seconds.";

	public static final String LEN_CALC_PV =
		"The loan amount has been left blank or set to zero.\n\n" +
		"Either enter a value for the loan length, or press\n" +
		"the 'Back' button twice and enter a value for the\n" +
		"loan amount.";

	public static final String NUMPER_TOO_LARGE =
		"Do you really think we will trust you with our\n" +
		"money for that long?\n\n" +
		"Please enter a smaller loan length. The duration\n" +
		"of the loan must not exceed 35 years.\n";

	public static final String PMNT_CALC_PV =
		"The loan amount has been left blank or set to zero.\n\n" +
		"Either enter a value for the payment amount, or press\n" +
		"the 'Back' button three times and enter a value for\n" +
		"the loan amount.";

	public static final String PMNT_CALC_LEN =
		"The length of the loan has been left blank or set to\n" +
		"zero.\n\n" +
		"Either enter a value for the payment amount, or press\n" +
		"the 'Back' button and enter a value for the length of\n" +
		"the loan.";

	public static final String PMNT_TOO_SMALL_INT =
		"The payment you have entered is too small. You could\n" +
		"not even pay the accrued interest with that payment.\n\n"+
		"Either go to another bank, press the 'Back' button\n" +
		"and change the other loan parameters, or enter a\n" +
		"payment of at least ";

	public static final String PMNT_TOO_SMALL_LEN =
		"The payment you have entered is too small. Do you want\n" +
		"your grandchildren to be paying off this loan?\n\n" +
		"Press the 'Back' button and change the other loan\n" +
		"parameters, or enter a payment of at least ";

	public static final String PMNT_TOO_LARGE_PV =
		"The payment you have entered would pay back a loan that\n" +
		"far exceeds your financial means.\n\n" +
		"Please enter a smaller payment or press the 'Back'\n" +
		"button and change the other loan parameters.";
}

class DNC
{
	private long i;

	public DNC(long j) { i = j; }

	public String toString()
	{
		String str;

		if ( i < 0 ) {
			str = "-$";
			i = -i;
		}
		else
			str = "$";

		return str + DLRS.mkString(i/100) + "." + DLRS.mk2Digits(i % 100);
	}
}

class DLRS
{
	private long i;

	public DLRS(long j) { i = j; }

	public String toString() { return "$" + mkString(i); }

	public static String mkString(long i)
	{
		if ( i < 1000 )
			return "" + i;
		else
			return mkString(i/1000) + "," + mk3Digits(i%1000);
	}

	private static String mk3Digits(long i)
	{
		if ( i < 100 )
			return "0" + mk2Digits(i);
		else
			return "" + i;
	}

	public static String mk2Digits(long i)
	{
		if ( i < 10 )
			return "0" + i;
		else
			return "" + i;
	}
}

class PRCNT
{
	private int i;

	public PRCNT(int j) { i = j; }

	public String toString()
	{
		String str = "" + i/8 + " ";
		int j = i%8;
		switch ( j ) {
		case 0: return str + "%";
		case 4: return str + "1/2 %";
		case 1: case 3: case 5:	case 7: return str + j + "/8 %";
		case 2:	case 6: return str + (j/2) + "/4 %";
		}
		// We will never get to here
		return "";
	}
}
