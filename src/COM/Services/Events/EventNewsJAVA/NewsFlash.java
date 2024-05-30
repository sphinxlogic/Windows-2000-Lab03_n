import com.ms.wfc.app.*;
import com.ms.wfc.core.*;
import com.ms.wfc.ui.*;
import com.ms.wfc.html.*;

/**
 * This class can take a variable number of parameters on the command
 * line. Program execution begins with the main() method. The class
 * constructor is not invoked unless an object of type 'Form1' is
 * created in the main() method.
 */
public class Form1 extends Form
{
	public Form1()
	{
		// Required for Visual J++ Form Designer support
		initForm();		

		// TODO: Add any constructor code after initForm call
	}

	/**
	 * Form1 overrides dispose so it can clean up the
	 * component list.
	 */
	public void dispose()
	{
		super.dispose();
		components.dispose();
	}

	private void publishButton_click(Object source, Event e)
	{
		
	}

	private void installEventButton_click(Object source, Event e)
	{
		
	}

	

	/**
	 * NOTE: The following code is required by the Visual J++ form
	 * designer.  It can be modified using the form editor.  Do not
	 * modify it using the code editor.
	 */
	Container components = new Container();
	GroupBox PublishEventBorder = new GroupBox();
	GroupBox InstallEventBorder = new GroupBox();
	Button publishButton = new Button();
	Button installEventButton = new Button();
	Label symbolLabel = new Label();
	Label urlLabel = new Label();
	Label headlineLabel = new Label();
	Edit symbolTF = new Edit();
	Edit headlineTF = new Edit();
	CheckBox queuedCB = new CheckBox();
	Edit urlTF = new Edit();
	CheckBox parallelCB = new CheckBox();
	Label ecDllNameLabel = new Label();
	Edit ecDllNameFT = new Edit();

	private void initForm()
	{
		this.setText("Form1");
		this.setAutoScaleBaseSize(new Point(5, 13));
		this.setClientSize(new Point(555, 430));

		PublishEventBorder.setLocation(new Point(24, 24));
		PublishEventBorder.setSize(new Point(408, 184));
		PublishEventBorder.setTabIndex(0);
		PublishEventBorder.setTabStop(false);
		PublishEventBorder.setText("Publish News Event");

		InstallEventBorder.setLocation(new Point(24, 224));
		InstallEventBorder.setSize(new Point(408, 176));
		InstallEventBorder.setTabIndex(1);
		InstallEventBorder.setTabStop(false);
		InstallEventBorder.setText("Instal Event");

		publishButton.setLocation(new Point(24, 32));
		publishButton.setSize(new Point(112, 32));
		publishButton.setTabIndex(0);
		publishButton.setText("Publish");
		publishButton.addOnClick(new EventHandler(this.publishButton_click));

		installEventButton.setLocation(new Point(24, 32));
		installEventButton.setSize(new Point(112, 32));
		installEventButton.setTabIndex(0);
		installEventButton.setText("Install");
		installEventButton.addOnClick(new EventHandler(this.installEventButton_click));

		symbolLabel.setLocation(new Point(152, 32));
		symbolLabel.setSize(new Point(80, 20));
		symbolLabel.setTabIndex(1);
		symbolLabel.setTabStop(false);
		symbolLabel.setText("Symbol");

		urlLabel.setLocation(new Point(152, 136));
		urlLabel.setSize(new Point(80, 20));
		urlLabel.setTabIndex(3);
		urlLabel.setTabStop(false);
		urlLabel.setText("URL");

		headlineLabel.setLocation(new Point(152, 88));
		headlineLabel.setSize(new Point(80, 20));
		headlineLabel.setTabIndex(2);
		headlineLabel.setTabStop(false);
		headlineLabel.setText("Headline");

		symbolTF.setLocation(new Point(256, 32));
		symbolTF.setSize(new Point(144, 20));
		symbolTF.setTabIndex(4);
		symbolTF.setText("");

		headlineTF.setLocation(new Point(256, 88));
		headlineTF.setSize(new Point(144, 20));
		headlineTF.setTabIndex(5);
		headlineTF.setText("");

		queuedCB.setLocation(new Point(24, 136));
		queuedCB.setSize(new Point(104, 16));
		queuedCB.setTabIndex(6);
		queuedCB.setText("Queued");

		urlTF.setLocation(new Point(256, 136));
		urlTF.setSize(new Point(144, 20));
		urlTF.setTabIndex(7);
		urlTF.setText("");

		parallelCB.setLocation(new Point(24, 120));
		parallelCB.setSize(new Point(120, 24));
		parallelCB.setTabIndex(1);
		parallelCB.setText("Parallel");

		ecDllNameLabel.setLocation(new Point(152, 40));
		ecDllNameLabel.setSize(new Point(96, 24));
		ecDllNameLabel.setTabIndex(2);
		ecDllNameLabel.setTabStop(false);
		ecDllNameLabel.setText("EC DLL Path");

		ecDllNameFT.setLocation(new Point(256, 40));
		ecDllNameFT.setSize(new Point(144, 20));
		ecDllNameFT.setTabIndex(3);
		ecDllNameFT.setText("");

		this.setNewControls(new Control[] {
							InstallEventBorder, 
							PublishEventBorder});
		PublishEventBorder.setNewControls(new Control[] {
										  urlTF, 
										  queuedCB, 
										  headlineTF, 
										  symbolTF, 
										  urlLabel, 
										  headlineLabel, 
										  symbolLabel, 
										  publishButton});
		InstallEventBorder.setNewControls(new Control[] {
										  ecDllNameFT, 
										  ecDllNameLabel, 
										  parallelCB, 
										  installEventButton});
	}

	/**
	 * The main entry point for the application. 
	 *
	 * @param args Array of parameters passed to the application
	 * via the command line.
	 */
	public static void main(String args[])
	{
		Application.run(new Form1());
	}
}
