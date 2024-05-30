//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//

public interface SDKCallbacks
{
	public void setDisplay(boolean multi);
	public void setDisplay(int state, boolean redraw);
	public int getListSelState();
	public int getTreeSelState();
	public void setSelStateAndMode(int control, int state);
}
