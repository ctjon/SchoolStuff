import java.awt.*;
import java.applet.Applet;
import java.awt.event.*;

public class StatsArrayController extends Applet
		implements ActionListener {

	//set up buttons to control the StatsArray
	private Button maxButton;
	private Button minButton;
	private Button sumButton;
	private Button meanButton;
	private Button luckyButton;


	// variables for communicating with paint()
	private boolean maxPressed;
	private boolean minPressed;
	private boolean sumPressed;
	private boolean meanPressed;
	private boolean luckyPressed;

	//instantiate your StatsArray object called grades
	//creates array of size 10 located at x = 50, y = 70 when displayed
	private StatsArray grades = new StatsArray(10, 50, 70);

	public void init() {

		//buttons
		maxButton = new Button("Maximum");
		add(maxButton);
		maxButton.addActionListener(this);

		minButton = new Button("Minimum");
		add(minButton);
		minButton.addActionListener(this);

		sumButton = new Button("Sum");
		add(sumButton);
		sumButton.addActionListener(this);

		meanButton = new Button("Mean");
		add(meanButton);
		meanButton.addActionListener(this);

		luckyButton = new Button("Lucky 7");
		add(luckyButton);
		luckyButton.addActionListener(this);

		/* invokes method to fill array with random numbers
		   between 1 and 100 */
		grades.fillArray();

	}

	public void paint (Graphics g) {

		grades.display(g);  //lets see the array or random numbers!

		if (maxPressed) {
			g.drawString("Maximum is: " + grades.getMax(), 50, 50);
			maxPressed = !maxPressed;
		}

		else if (minPressed) {
			g.drawString("Minimum is: " + grades.getMin(), 50, 50);
			minPressed = !minPressed;
		}

		else if (sumPressed) {
			g.drawString("Sum is: " + grades.getSum(), 50, 50);
			sumPressed = !sumPressed;
		}

		else if (meanPressed) {
			g.drawString("Mean is: " + grades.getMean(), 50, 50);
			meanPressed = !meanPressed;
		}
		else if (luckyPressed) {
			g.drawString("Lucky 7  Y or N: " + grades.getLucky7(),
						  50, 50);
			luckyPressed = !luckyPressed;
		}


	}

	//Button and TextField event handler
	public void actionPerformed(ActionEvent event) {
		if (event.getSource() == minButton)
			minPressed = true;
		else if (event.getSource() == maxButton)
			maxPressed = true;
		else if (event.getSource() == sumButton)
			sumPressed = true;
		else if (event.getSource() == meanButton)
			meanPressed = true;
		else if (event.getSource() == luckyButton)
			luckyPressed = true;
		repaint();
	}

}

