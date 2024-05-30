//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//

public class LCParams implements LCConsts
{
	public long pv;
	public int i, len, hz_idx, n, pmnt;
	public boolean years;
	public double ip;

	public LCParams(LCParams lp)
	{
		this(lp.pv, lp.i, lp.len, lp.years, lp.hz_idx, lp.pmnt);
	}

	public LCParams(long pv, int i, int len, boolean years, int hz_idx, int pmnt)
	{
		this.pv = pv; this.i = i; this.len = len; 
		this.years = years; this.hz_idx = hz_idx; this.pmnt = pmnt;

		n = len*FREQ_FACTOR[hz_idx];
		if ( !years )
			n /= 12;

		ip = i/(FREQ_FACTOR[hz_idx]*800.0);
	}

	// Calculate parameter that was = 0
	public boolean calc(int what)
	{
		boolean setwiz = false;

		switch ( what ) {
		case BL_PV:	pv = calcPV(); break;
		// need to recalculate pmnt after calculating number of periods since n
		//  will be rounded down to the nearest int. May also need to reset text in Wizard
		case BL_LEN: n = calcN(); setwiz = true; // Fall through
		case BL_PMNT: pmnt = calcPmnt(); break;
		}
		return setwiz;
	}

	public int calcPmnt()
	{
		if ( n == 0 ) n = 1;
		double factor = Math.pow(1.0 + ip, n);
		return (int)(((factor*ip*pv)/(factor - 1.0))*100.0);
	}

	public long calcPV()
	{
		if ( n == 0 ) n = 1;
		double factor = Math.pow(1.0 + ip, n);
		return (long)(((factor - 1.0)*(pmnt/100.0))/(factor*ip));
	}

	public int calcN()
	{
		double a = pmnt/100.0;
		int n = (int)(Math.log(a/(a-(pv*ip)))/Math.log(1.0+ip)); 
		if ( n == 0 )
			n = 1;
		len = n*(12/FREQ_FACTOR[hz_idx]);
		if ( (len % 12) == 0 ) {
			len /= 12;
			years = true;
		}
		else
			years = false;

		return n;
	}
}
