//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//

public interface SDKCallbacks
{
	public void displayTestBtn(int btn);

	public void setStatusPush();

	public void setStatusCheck();
	public boolean isCustomCheck();
	public void repaintCheck();

	public void setStatusRadio();
	public void setEnabledRadio();
	public boolean isCustomRadio();
	public void repaintRadio();

	public void setStatusRepeat();
	public void setEnabledRepeat();
}
