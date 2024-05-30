//////////////////////////////////////////////////////////////////////////
// JBrowserOpen.java
// This is a dialog box which asks the user to enter a URL to open
//
// (C) Copyright 1997 by Microsoft Corporation. All rights reserved
//////////////////////////////////////////////////////////////////////////


// standard java
import java.awt.*;
import java.awt.event.*;

//
//
// JBrowserOpen
//
//
public class JBrowserOpen extends Dialog implements ActionListener
{
	JBrowser parent;																	// the browser who called this dialog
	TextField urlEdit = new TextField("                                  ");			// the url to go to.
	Button openButton = new Button(" open ");			// open button
	Button cancelButton = new Button(" cancel ");		// cancel button

	public JBrowserOpen(JBrowser parent)
	{
		// call the Dialog constructor to create a modal dialog box
		super(parent, "Open URL", true);

		this.parent = parent;

		// setup the dialog box
		setBackground(Color.lightGray );
		setBounds(200,200,400,400);
		setLayout( new FlowLayout() );

		// add a text message
		add( new Label("The URL to open"));

		// add a text field
		add( urlEdit);

		// add a panel with two buttons
		Panel p2 = new Panel();
		p2.setLayout( new FlowLayout(2) );
		p2.add(openButton);
		p2.add(cancelButton);
		add(p2);

		// add event hooks
		urlEdit.addActionListener(this);
		openButton.addActionListener(this);
		cancelButton.addActionListener(this);
		addWindowListener( new JBrowserOpenWindowListener() );
		pack();
		urlEdit.setText("");
		setVisible(true);
	}

	/**
	 * This method is invoked when an AWT event occurs (i.e. an AWT component
	 * fires an action event).
	 *
	 * @param	ActionEvent		The action event which occurred
	 */
	public void actionPerformed(ActionEvent evt)
	{
		Object source = evt.getSource();

		if(source == urlEdit)
		{
			dispose();
			parent.navigate(urlEdit.getText() );
		}
		else if(source == cancelButton)
		{
			dispose();
		}

		else if (source == openButton)
		{
			dispose();
			parent.navigate(urlEdit.getText() );
		}

	}

	/**
	 * This inner class is to listen to window events
	 */
	public class JBrowserOpenWindowListener extends WindowAdapter
	{
		/**
		 * This method is invoked when the user clicks on the close window button
		 * in the dialog box's window
		 *
		 * @param	WindowEvent	The event which occurred
		 */
		public void windowClosing(WindowEvent evt)
		{
			dispose();
		}
	}

}
