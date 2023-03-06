//use an example with Black and White box testing - CH 23
import java.awt.*;
import java.applet.Applet;
import java.awt.event.*;

public class BiggestController extends Applet
		implements ActionListener {

	private Button myButton;
	private Button enter;
	private TextField myTextField;
	private Biggest bigObj;
	public void init() {

		bigObj = new Biggest();

		//label
		Label myLabel = new Label("Enter a number");
		add(myLabel);

		//button
		myButton = new Button("Start Again");
		add(myButton);
		myButton.addActionListener(this);

		//button
		enter = new Button("Enter number");
		add(enter);
		enter.addActionListener(this);

		//textfield
		myTextField = new TextField(10);
		add(myTextField);
		myTextField.addActionListener(this);

	}

	public void paint (Graphics g) {

		bigObj.display(g);

	}

	//Button and TextField event handler
	public void actionPerformed(ActionEvent event) {

		if (event.getSource() == myButton) {
			bigObj.startAgain();
		}
		else if (event.getSource() == enter) {
			int newNum;
			newNum = Integer.parseInt(myTextField.getText());
			bigObj.nextNumber(newNum);
		}

		repaint();
	}

}

class Biggest {

	private int largest;
	private boolean entered;

	public Biggest() {
		startAgain();
	}

	public void nextNumber(int n) {

		if (n > largest)
				largest = n;
		}

	public void display(Graphics g) {
			g.drawString(" largest so far is " + largest, 50, 50);
	}

	public void startAgain() {
		largest = 0;
	}
}


