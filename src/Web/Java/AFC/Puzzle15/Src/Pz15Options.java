//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.Insets;
import com.ms.ui.*;
import com.ms.fx.*;

public class Pz15Options extends UIPropertyDialog implements Pz15Consts
{
	Insets m_Insets;
	public boolean cpuactive;
	public int navmode;
	public int numscramble;

	public Pz15Options(UIFrame frame, String title, boolean modal, int pagesize)
	{
		super(frame, title, modal, pagesize);
		cpuactive = true;
		navmode = M_BUTTON;
		numscramble = 60;
	}
}