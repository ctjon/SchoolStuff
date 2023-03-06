/*
 * CSC110AA/CIS163AA
 *
 * EX 16.3 - Catching Exceptions
 *
 * This code attempts to calculate the area of a triangle
 * given the length of 3 sides.  Students are to add code
 * to catch and try exceptions.
 *
 * NumberFormatException (ie. a nonnumeric character was entered)
 * 
 * IllegalArgumentException (thrown by checkforBadNumber - see below)
 * 
 * Exception, the superClass. (for some unexpected Exception)
 * 
 * Please include a method called checkForBadNumber that throws an 
 *   IllegalArgumentException if any input numbers are zero or negative.
 * 
 * Please include finally statement with a statement of your choice.
 *
 */

package triangle_area;

import java.awt.*;
import java.applet.Applet;
//import java.util.*;
import java.awt.event.*;

public class TriangleArea extends Applet
	implements ActionListener {

	private TextField stringField1;
	private TextField stringField2;
	private TextField stringField3;
	private TextField resultField;
	private Label resultLabel;
	private Label stringLabel;
	
	private Button goButton;

	public void init() {
		stringLabel = new Label("Type 3 integers: ");
		resultLabel = new Label ("Answer");
		stringField1 = new TextField(10);
		stringField2 = new TextField(10);
		stringField3 = new TextField(10);

		goButton = new Button ("Calculate Area");

		resultField = new TextField(30);
		resultField.setEditable(false);

		add(stringLabel);
		add(stringField1);
		add(stringField2);
		add(stringField3);
		add(goButton);

		goButton.addActionListener(this);

		add(resultLabel);
		add(resultField);
	}

	private void checkForBadNumber(float number)throws IllegalArgumentException
	{
		if (number <= 0.0)
			throw new IllegalArgumentException();
	}

	public void actionPerformed(ActionEvent event) {
		if(event.getSource() == goButton)
		{
			try
			{
				float number1 =
					Float.parseFloat(stringField1.getText());
				checkForBadNumber(number1);
				float number2 =
					Float.parseFloat(stringField2.getText());
				checkForBadNumber(number2);
				float number3 =
					Float.parseFloat(stringField3.getText());
				checkForBadNumber(number3);

				float s = (number1 + number2 + number3 / 2.0f);


				double area =
					Math.sqrt(s * (s - number1) * (s - number2)
						* (s - number3));

				resultField.setText("The area is " +
					(area));
			}
			
			catch(NumberFormatException e)
			{
				resultLabel.setText("Must enter a number!");
				System.out.println(e.toString());
			}
			
			catch(Exception e)
			{
				resultLabel.setText("Unexpected Exception");
				System.out.println(e.toString());
			}
			
			finally
			{
				System.out.println("Please call tech support");
			}
		}

		repaint();
	}
}