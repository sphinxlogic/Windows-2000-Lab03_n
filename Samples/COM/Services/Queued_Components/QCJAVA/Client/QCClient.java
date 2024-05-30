import com.ms.wfc.app.*;
import com.ms.wfc.core.*;
import com.ms.wfc.ui.*;
import com.ms.wfc.html.*;
import com.ms.wfc.data.*;

/**
 * This class can take a variable number of parameters on the command
 * line. Program execution begins with the main() method. The class
 * constructor is not invoked unless an object of type 'QCClient' is
 * created in the main() method.
 */
public class QCClient extends Form
{
	private qcorder.IOrder order_obj = null;
	
	public QCClient()
	{
		// Required for Visual J++ Form Designer support
		initForm();		
		createOrderObject();
		// TODO: Add any constructor code after initForm call
	}
	
	/**
     * Create the instance of order com object.
     *
     * @param       ---
     * @return      ---
     * @see			com.ms.win32.ole32.CoGetObject
     **/
	private void createOrderObject()
	{
		try
		{
			order_obj = (qcorder.IOrder)com.ms.win32.Ole32.CoGetObject("new:QCOrderLib.Order",null,qcorder.IOrder.iid);
		}
		catch(com.ms.com.ComFailException exp)
		{
			System.out.println("Order Object Creation: Exception " + exp);
		}
	}
	
	/**
     * Retreive the Shipment Status from the database
     *
     * @param       ---
     * @return      ---
     * @see			com.ms.wfc.Data.Connection
     **/
	
	private void checkStatusFromDB()
	{
		int			result		=	0;
		Connection	con			=	null;
		Recordset	rs			=	null;
		String		conDetail	=	null;
		boolean		returnValue	=	false;
		conDetail	=	"Data Source=" + helper.DatabaseSettings.DSN + ";" + "User Id=" + helper.DatabaseSettings.User + ";" + "Password=" + helper.DatabaseSettings.Pass + ";";
		con			=	new Connection();
		rs			=	new Recordset();
		con.open(conDetail);
		StringBuffer sqlQuery	=	new StringBuffer("");
		sqlQuery.append("Select * from QCSampleOrder where order_id = ");
		sqlQuery.append(orderTF.getText());
		sqlQuery.append(" and cust_id =  ");
		sqlQuery.append(customerTF.getText());
		rs = con.execute(sqlQuery.toString());
		while(!rs.getEOF())
		{
			int index = 0;
			index = getItemIndex(rs.getField("item_id").getString());
			setShipingStatus(index,(rs.getField("ship_status").getString()) );
			rs.moveNext();
		}
		rs.release();
		con.close();
		
		
	}
	
	/**
     * Set the shipment status for the order line.
     *
     * @param       ---
     * @return      ---
     **/
	private void setShipingStatus(int index , String status)
	{
		if(index != 0)
		{
			switch(index)
			{
				case 1:
					{
						shipingStatus_1.setText(status);
						break;
					}
				case 2:
					{
						shipingStatus_2.setText(status);
						break;
					}
				case 3:
					{
						shipingStatus_3.setText(status);
						break;
					}
				case 4:
					{
						shipingStatus_4.setText(status);
						break;
					}
				case 5:
					{
						shipingStatus_5.setText(status);
						break;
					}
				case 6:
					{
						shipingStatus_6.setText(status);
						break;
					}
			}
		}
	}
	
	/**
     * Return the item line number
     *
     * @param       ---
     * @return      ---
     **/
	private int getItemIndex(String itemNumber)
	{
		int resultingIndex = 0;
		if((itemNo_1.getText()).equals(itemNumber))
		{
			resultingIndex = 1;
		}
		else if((itemNo_2.getText()).equals(itemNumber))
		{
			resultingIndex = 2;
		}
		else if((itemNo_3.getText()).equals(itemNumber))
		{
			resultingIndex = 3;
		}
		else if((itemNo_4.getText()).equals(itemNumber))
		{
			resultingIndex = 4;
		}
		else if((itemNo_5.getText()).equals(itemNumber))
		{
			resultingIndex = 5;
		}
		else if((itemNo_6.getText()).equals(itemNumber))
		{
			resultingIndex = 6;
		}
		return resultingIndex;
	}
	/**
	 * QCClient overrides dispose so it can clean up the
	 * component list.
	 */
	public void dispose()
	{
		super.dispose();
		components.dispose();
	}
	
	/**
     * Shipment Status Button processing
     *
     * @param       ---
     * @return      ---
     **/
	private void statusButton_click(Object source, Event e)
	{
		checkStatusFromDB();
		statusBorder.setVisible(true);
		statusButton.setText("Update Shipment Status");
	}

	/**
     * Process Order button processing.
     *
     * @param       ---
     * @return      ---
     **/
	private void processButton_click(Object source, Event e)
	{
		processOrder();
		statusButton.setEnabled(true);
		processButton.setEnabled(false);
		setOrderDetailEnabled(false);
		
	}
	/**
     * Process order.It calls message on the order_obj which in turn calls Queued shipment component.
     *
     * @param       ---
     * @return      ---
     **/
	private void processOrder()
	{
		if(order_obj != null)
		{
			try
			{
				String str = customerTF.getText();
				order_obj.setCustomerId(Integer.parseInt(customerTF.getText()));
				order_obj.setOrderId(Integer.parseInt(orderTF.getText()));
				handleOrderLine();
				order_obj.Process(0);
			}
			catch(com.ms.com.ComFailException exp)
			{
				System.out.println("Order Processing: Exception " + exp);
			}
			catch(NumberFormatException exp)
			{
				com.ms.win32.User32.MessageBox(0,"Error","Please Enter only numbers",0);		
			}
		}
	}
	
	/**
     * Check if user has specifed a item for the order line.
     *
     * @param       ---
     * @return      ---
     **/
	private void handleOrderLine()
	{
		if(!(itemNo_1.getText().equals("")) && !(quantity_1.getText().equals(""))) 
		{
			order_obj.LineItem(Integer.parseInt(itemNo_1.getText()) , Integer.parseInt(quantity_1.getText()));
		}
		if(!(itemNo_2.getText().equals("")) && !(quantity_2.getText().equals(""))) 
		{
			order_obj.LineItem(Integer.parseInt(itemNo_2.getText()) , Integer.parseInt(quantity_2.getText()));
		}
		if(!(itemNo_3.getText().equals("")) && !(quantity_3.getText().equals(""))) 
		{
			order_obj.LineItem(Integer.parseInt(itemNo_3.getText()) , Integer.parseInt(quantity_3.getText()));
		}
		if(!(itemNo_4.getText().equals("")) && !(quantity_4.getText().equals(""))) 
		{
			order_obj.LineItem(Integer.parseInt(itemNo_4.getText()) , Integer.parseInt(quantity_4.getText()));
		}
		if(!(itemNo_5.getText().equals("")) && !(quantity_5.getText().equals(""))) 
		{
			order_obj.LineItem(Integer.parseInt(itemNo_5.getText()) , Integer.parseInt(quantity_5.getText()));
		}
		if(!(itemNo_6.getText().equals("")) && !(quantity_6.getText().equals(""))) 
		{
			order_obj.LineItem(Integer.parseInt(itemNo_6.getText()) , Integer.parseInt(quantity_6.getText()));
		}
		
	}
	/**
     * Enable or disable all the components based on the flag.
     *
     * @param       ---
     * @return      ---
     **/
	
	private void setOrderDetailEnabled(boolean flag)
	{
		itemNo_1.setEnabled(flag);
		quantity_1.setEnabled(flag);
		shipingStatus_1.setEnabled(flag);
		
		itemNo_2.setEnabled(flag);
		quantity_2.setEnabled(flag);
		shipingStatus_2.setEnabled(flag);
		
		itemNo_3.setEnabled(flag);
		quantity_3.setEnabled(flag);
		shipingStatus_3.setEnabled(flag);
		
		itemNo_4.setEnabled(flag);
		quantity_4.setEnabled(flag);
		shipingStatus_4.setEnabled(flag);
		
		itemNo_5.setEnabled(flag);
		quantity_5.setEnabled(flag);
		shipingStatus_5.setEnabled(flag);
		
		itemNo_6.setEnabled(flag);
		quantity_6.setEnabled(flag);
		shipingStatus_6.setEnabled(flag);
		
		customerTF.setEnabled(flag);
		orderTF.setEnabled(flag);
	}
	/**
     * Handle reset button.
     *
     * @param       ---
     * @return      ---
     **/
	
	private void resetButton_click(Object source, Event e)
	{
		itemNo_1.setText("");
		quantity_1.setText("");
		shipingStatus_1.setText("");
		
		itemNo_2.setText("");
		quantity_2.setText("");
		shipingStatus_2.setText("");
		
		itemNo_3.setText("");
		quantity_3.setText("");
		shipingStatus_3.setText("");
		
		itemNo_4.setText("");
		quantity_4.setText("");
		shipingStatus_4.setText("");
		
		itemNo_5.setText("");
		quantity_5.setText("");
		shipingStatus_5.setText("");
		
		itemNo_6.setText("");
		quantity_6.setText("");
		shipingStatus_6.setText("");
		
		customerTF.setText("");
		orderTF.setText("");
		
		processButton.setEnabled(true);
		setOrderDetailEnabled(true);
		statusButton.setText("Check Shipment Status");
		statusButton.setEnabled(false);
		statusBorder.setVisible(false);
	}

	/**
	 * NOTE: The following code is required by the Visual J++ form
	 * designer.  It can be modified using the form editor.  Do not
	 * modify it using the code editor.
	 */
	Container components = new Container();
	Edit customerTF = new Edit();
	Label label1 = new Label();
	Label label2 = new Label();
	Edit orderTF = new Edit();
	GroupBox orderDetailBorder = new GroupBox();
	Edit quantity_5 = new Edit();
	Edit itemNo_5 = new Edit();
	Button statusButton = new Button();
	Edit shipingStatus_4 = new Edit();
	Edit quantity_4 = new Edit();
	Edit itemNo_4 = new Edit();
	Edit shipingStatus_3 = new Edit();
	Edit quantity_3 = new Edit();
	Edit itemNo_3 = new Edit();
	Edit shipingStatus_2 = new Edit();
	Edit quantity_2 = new Edit();
	Edit itemNo_2 = new Edit();
	Button processButton = new Button();
	Edit shipingStatus_1 = new Edit();
	Edit quantity_1 = new Edit();
	Edit itemNo_1 = new Edit();
	Label label5 = new Label();
	Label label4 = new Label();
	Label label3 = new Label();
	GroupBox statusBorder = new GroupBox();
	Edit shipingStatus_5 = new Edit();
	Edit itemNo_6 = new Edit();
	Edit quantity_6 = new Edit();
	Edit shipingStatus_6 = new Edit();
	Button resetButton = new Button();

	private void initForm()
	{
		this.setText("QCClient");
		this.setAutoScaleBaseSize(new Point(5, 13));
		this.setClientSize(new Point(590, 411));

		customerTF.setLocation(new Point(120, 32));
		customerTF.setSize(new Point(144, 20));
		customerTF.setTabIndex(0);
		customerTF.setText("");

		label1.setLocation(new Point(8, 32));
		label1.setSize(new Point(96, 16));
		label1.setTabIndex(1);
		label1.setTabStop(false);
		label1.setText("Customer Number");

		label2.setLocation(new Point(328, 32));
		label2.setSize(new Point(88, 16));
		label2.setTabIndex(3);
		label2.setTabStop(false);
		label2.setText("Order Number");

		orderTF.setLocation(new Point(440, 32));
		orderTF.setSize(new Point(144, 20));
		orderTF.setTabIndex(2);
		orderTF.setText("");

		orderDetailBorder.setLocation(new Point(8, 72));
		orderDetailBorder.setSize(new Point(576, 264));
		orderDetailBorder.setTabIndex(4);
		orderDetailBorder.setTabStop(false);
		orderDetailBorder.setText("");

		quantity_5.setLocation(new Point(168, 184));
		quantity_5.setSize(new Point(96, 20));
		quantity_5.setTabIndex(12);
		quantity_5.setText("");

		itemNo_5.setLocation(new Point(24, 184));
		itemNo_5.setSize(new Point(112, 20));
		itemNo_5.setTabIndex(11);
		itemNo_5.setText("");

		statusButton.setEnabled(false);
		statusButton.setLocation(new Point(220, 368));
		statusButton.setSize(new Point(136, 24));
		statusButton.setTabIndex(6);
		statusButton.setText("Check Shipment Status");
		statusButton.addOnClick(new EventHandler(this.statusButton_click));

		shipingStatus_4.setLocation(new Point(24, 144));
		shipingStatus_4.setSize(new Point(176, 20));
		shipingStatus_4.setTabIndex(4);
		shipingStatus_4.setText("");

		quantity_4.setLocation(new Point(168, 152));
		quantity_4.setSize(new Point(96, 20));
		quantity_4.setTabIndex(10);
		quantity_4.setText("");

		itemNo_4.setLocation(new Point(24, 152));
		itemNo_4.setSize(new Point(112, 20));
		itemNo_4.setTabIndex(9);
		itemNo_4.setText("");

		shipingStatus_3.setLocation(new Point(24, 112));
		shipingStatus_3.setSize(new Point(176, 20));
		shipingStatus_3.setTabIndex(3);
		shipingStatus_3.setText("");

		quantity_3.setLocation(new Point(168, 120));
		quantity_3.setSize(new Point(96, 20));
		quantity_3.setTabIndex(8);
		quantity_3.setText("");

		itemNo_3.setLocation(new Point(24, 120));
		itemNo_3.setSize(new Point(112, 20));
		itemNo_3.setTabIndex(7);
		itemNo_3.setText("");

		shipingStatus_2.setLocation(new Point(24, 80));
		shipingStatus_2.setSize(new Point(176, 20));
		shipingStatus_2.setTabIndex(2);
		shipingStatus_2.setText("");

		quantity_2.setLocation(new Point(168, 88));
		quantity_2.setSize(new Point(96, 20));
		quantity_2.setTabIndex(6);
		quantity_2.setText("");

		itemNo_2.setLocation(new Point(24, 88));
		itemNo_2.setSize(new Point(112, 20));
		itemNo_2.setTabIndex(5);
		itemNo_2.setText("");

		processButton.setLocation(new Point(40, 368));
		processButton.setSize(new Point(112, 24));
		processButton.setTabIndex(5);
		processButton.setText("Process Order");
		processButton.addOnClick(new EventHandler(this.processButton_click));

		shipingStatus_1.setLocation(new Point(24, 48));
		shipingStatus_1.setSize(new Point(176, 20));
		shipingStatus_1.setTabIndex(1);
		shipingStatus_1.setText("");

		quantity_1.setLocation(new Point(168, 56));
		quantity_1.setSize(new Point(96, 20));
		quantity_1.setTabIndex(4);
		quantity_1.setText("");

		itemNo_1.setLocation(new Point(24, 56));
		itemNo_1.setSize(new Point(112, 20));
		itemNo_1.setTabIndex(3);
		itemNo_1.setText("");

		label5.setLocation(new Point(80, 16));
		label5.setSize(new Point(96, 16));
		label5.setTabIndex(0);
		label5.setTabStop(false);
		label5.setText("Shipment Status");

		label4.setLocation(new Point(168, 24));
		label4.setSize(new Point(96, 24));
		label4.setTabIndex(2);
		label4.setTabStop(false);
		label4.setText("Quantity");

		label3.setLocation(new Point(32, 24));
		label3.setSize(new Point(80, 16));
		label3.setTabIndex(1);
		label3.setTabStop(false);
		label3.setText("Item Number");

		statusBorder.setLocation(new Point(320, 8));
		statusBorder.setSize(new Point(248, 248));
		statusBorder.setTabIndex(0);
		statusBorder.setTabStop(false);
		statusBorder.setText("");
		statusBorder.setVisible(false);

		shipingStatus_5.setLocation(new Point(24, 176));
		shipingStatus_5.setSize(new Point(176, 20));
		shipingStatus_5.setTabIndex(5);
		shipingStatus_5.setText("");

		itemNo_6.setLocation(new Point(24, 216));
		itemNo_6.setSize(new Point(112, 20));
		itemNo_6.setTabIndex(13);
		itemNo_6.setText("");

		quantity_6.setLocation(new Point(168, 216));
		quantity_6.setSize(new Point(96, 20));
		quantity_6.setTabIndex(14);
		quantity_6.setText("");

		shipingStatus_6.setLocation(new Point(24, 208));
		shipingStatus_6.setSize(new Point(176, 20));
		shipingStatus_6.setTabIndex(6);
		shipingStatus_6.setText("");

		resetButton.setLocation(new Point(424, 368));
		resetButton.setSize(new Point(128, 24));
		resetButton.setTabIndex(7);
		resetButton.setText("Reset");
		resetButton.addOnClick(new EventHandler(this.resetButton_click));

		this.setNewControls(new Control[] {
							resetButton, 
							statusButton, 
							orderDetailBorder, 
							processButton, 
							orderTF, 
							label2, 
							label1, 
							customerTF});
		orderDetailBorder.setNewControls(new Control[] {
										 quantity_6, 
										 itemNo_6, 
										 quantity_5, 
										 itemNo_5, 
										 quantity_4, 
										 itemNo_4, 
										 quantity_3, 
										 itemNo_3, 
										 quantity_2, 
										 itemNo_2, 
										 quantity_1, 
										 itemNo_1, 
										 label4, 
										 label3, 
										 statusBorder});
		statusBorder.setNewControls(new Control[] {
									shipingStatus_6, 
									shipingStatus_5, 
									shipingStatus_4, 
									shipingStatus_3, 
									shipingStatus_2, 
									shipingStatus_1, 
									label5});
	}

	/**
	 * The main entry point for the application. 
	 *
	 * @param args Array of parameters passed to the application
	 * via the command line.
	 */
	public static void main(String args[])
	{
		Application.run(new QCClient());
	}
}
