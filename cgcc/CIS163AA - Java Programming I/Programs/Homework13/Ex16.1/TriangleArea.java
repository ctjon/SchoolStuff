/*
 * CSC110AA/CIS163AA
 *
 * EX 16.3 - Catching Exceptions
 *
 * This code attempts to calculate the area of a triangle
 * given the length of 3 sides.  Students are to add code
 * to catch and try exceptions.
 *
 *
 *
 */
import java.awt.*;
import java.applet.Applet;
import java.util.*;
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



	public void actionPerformed(ActionEvent event) {
		if(event.getSource() == goButton) {

				float number1 =
					Float.parseFloat(stringField1.getText());
				float number2 =
					Float.parseFloat(stringField2.getText());
				float number3 =
					Float.parseFloat(stringField3.getText());


				float s = (number1 + number2 + number3 / 2.0f);


				double area =
					Math.sqrt(s * (s - number1) * (s - number2)
						* (s - number3));

				resultField.setText("The area is " +
					(area));



		}

		repaint();
	}
}


