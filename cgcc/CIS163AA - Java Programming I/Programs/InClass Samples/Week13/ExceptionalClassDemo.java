/*Start with this code to show exceptions

 */
import java.awt.*;
import java.applet.Applet;
import java.awt.event.*;

public class ExceptionalClassDemo extends Applet
		implements ActionListener {

	private Button myButton;
	private TextField myTextField;
	private TextField myTextField2;
	private Label myLabel;

	public void init() {

		//label to write answer
	    myLabel = new Label("Divide                                                                                                       ");
		add(myLabel);

		//button
		myButton = new Button("Calculate");
		add(myButton);
		myButton.addActionListener(this);
		//textfields
		myTextField = new TextField(10);
		add(myTextField);
		myTextField.addActionListener(this);

		myTextField2 = new TextField(10);
		add(myTextField2);
		myTextField2.addActionListener(this);

	}

	public void paint (Graphics g) {

	}

	private void checkForTwo(int someNumber) throws IllegalArgumentException
	{
		if (someNumber == 2)
		throw new IllegalArgumentException();
	}

	//Button and TextField event handler
	public void actionPerformed(ActionEvent event)
	{

		try
		{
			int num1 = Integer.parseInt(myTextField.getText());
			int num2 = Integer.parseInt(myTextField2.getText());
			checkForTwo(num1);
			checkForTwo(num2);
			myLabel.setText(""+ num1 / num2);
		}

		catch(NumberFormatException e)
		{
			myLabel.setText("Must enter an integer!");
			System.out.println(e.toString());
		}

		catch(ArithmeticException e)
		{
					myLabel.setText("Invalid Arithmetic Error");
					System.out.println(e.toString());
		}

		catch(IllegalArgumentException e)
		{
					myLabel.setText("2 is a bad number");
					System.out.println(e.toString());
		}

		catch(Exception e)
		{
			myLabel.setText("Unexpected Exception");
			System.out.println(e.toString());
		}

		finally
		{
			System.out.println("Please call tech support");
		}

		repaint();
	}

}

