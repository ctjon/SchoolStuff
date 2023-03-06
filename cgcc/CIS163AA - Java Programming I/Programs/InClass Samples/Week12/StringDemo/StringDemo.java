/*   Use with Chapter 15:  String Manipulation

   This program illustrates how to use text fields as
   well as String concepts.

   Note: with text fields you implement ActionListener
         and implement the method ActionPerformed

 */
import java.awt.*;
import java.applet.*;
import java.util.*;
import java.awt.event.*;


public class StringDemo extends Applet
	implements ActionListener {

		//declare the 3 text fields
		private TextField string1Field;
		private TextField string2Field;
		private TextField resultField;

		Label string1Label;
		Label string2Label;
		Label resultLabel;
		Button goButton;


	public void init() {
		string1Label = new Label("Type string1: ");
		string2Label = new Label("Type string2: ");
		resultLabel = new Label("Result is: ");

		goButton = new Button ("do it");

		string1Field = new TextField(20);
		string2Field = new TextField(20);
		resultField = new TextField(40);

		resultField.setEditable(false); // cannot be changed

		add(string1Label);
		add(string1Field);

		add(string2Label);
		add(string2Field);

		add(goButton);
		goButton.addActionListener(this);

		add(resultLabel);
		add(resultField);

	}


	public void actionPerformed(ActionEvent event) {
		String result = "";

		if(event.getSource() == goButton) {
			String string1 = string1Field.getText();
			String string2 = string2Field.getText();
			//string example - enter string1 and string 2
			// ..insert your testing code here




			if (string1.equals(string2))
				result = "They are equal.";
			else
				result = "They are not equal.";




			// end of example

			resultField.setText(result);  //put the result in the text field
		}
	}

}
