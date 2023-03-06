/*
 * Chris Tjon - Ex5.9 Wed 4pm 
 *
 */
package doubled;

import java.applet.Applet;
import java.awt.Graphics;
import java.awt.*;
import java.awt.event.*;

public class Doubled extends Applet implements ActionListener 
{
	private TextField inputField;
	private int input;
	
	int doubled(int operand)
	{
		return(operand * 2); // double the parameter and return it
	}
	
	public void init()
	{
		Label fieldName = new Label("Input:");
		add(fieldName);
		inputField = new TextField(5);
		add(inputField);
		inputField.addActionListener(this);
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
}