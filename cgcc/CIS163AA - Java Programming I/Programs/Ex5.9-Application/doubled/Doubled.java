/*
 * Chris Tjon - Ex5.9 Wed 4pm
 *
 */
package doubled;


import java.awt.Graphics;
import java.awt.*;
import java.awt.event.*;

public class Doubled extends Frame implements ActionListener, WindowListener
{
	private TextField inputField;
	private int input;

	int doubled(int operand)
	{
		return(operand * 2); // double the parameter and return it
	}

	public static void main(String[] args)
	{
		Doubled f = new Doubled();
		f.setSize(500,500);
		f.setVisible(true);
	}


	public Doubled()
	{
		Label fieldName = new Label("Input:");
		add(fieldName);
		inputField = new TextField(5);
		add(inputField);
		inputField.addActionListener(this);
		this.addWindowListener(this);
		setLayout(new FlowLayout());

	}

	public void actionPerformed(ActionEvent event)
	{
		input = Integer.parseInt(inputField.getText());
		repaint();
	}

	public void paint(Graphics g)
    {
    	g.drawString("doubled(" + input + ") = " + doubled(input), 50, 50);
    }


//Window Listener Methods
	public void windowClosing(WindowEvent event)
	{
		System.exit(0);
	}

	public void windowIconified(WindowEvent event)
	{

	}

	public void windowOpened(WindowEvent event)
	{

	}

	public void windowClosed(WindowEvent event)
	{

	}

	public void windowDeiconified(WindowEvent event)
	{

	}

	public void windowActivated(WindowEvent event)
	{

	}

	public void windowDeactivated(WindowEvent event)
	{

	}
}