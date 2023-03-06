/*
 * Chris Tjon - Wed 4pm
 * 
 * This is the controller for the StatsArray class.
 * The StatsArray is used to hold 10 grades   
 */

import java.awt.*;
import java.applet.Applet;
import java.awt.event.*;

public class StatsArrayController extends Applet
		implements ActionListener {

	//set up buttons to control the StatsArray
	private Button maxButton;
	private Button minButton;
	private Button sumButton;
	private Button avgButton;
	private Button aButton;
	private Button luckyButton;
	private Button sortButton;
	private Button resetButton;


	// variables for communicating with paint()
	private boolean maxPressed;
	private boolean minPressed;
	private boolean sumPressed;
	private boolean avgPressed;
	private boolean aPressed;
	private boolean luckyPressed;
	private boolean sortPressed;
	private boolean resetPressed;

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

		avgButton = new Button("Average");
		add(avgButton);
		avgButton.addActionListener(this);

		aButton = new Button("Number of A's ");
		add(aButton);
		aButton.addActionListener(this);


		luckyButton = new Button("Lucky 7");
		add(luckyButton);
		luckyButton.addActionListener(this);

		sortButton = new Button("Sort");
		add(sortButton);
		sortButton.addActionListener(this);

		resetButton = new Button("Reset");
		add(resetButton);
		resetButton.addActionListener(this);

		/* invokes method to fill array with random numbers
		   between 1 and 100 */
		grades.fillArray();

	}

	public void paint (Graphics g) {


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

		else if (avgPressed) {
			g.drawString("Average is: " + grades.getAverage(), 50, 50);
			avgPressed = !avgPressed;
		}
		else if (aPressed) {
			g.drawString("Number of A's = " + grades.count90s(), 50, 50);
			aPressed = !aPressed;
		}
		else if (luckyPressed) {
			g.drawString("Lucky 7  Y or N: " + grades.getLucky7(),
						  50, 50);
			luckyPressed = !luckyPressed;
		}
		else if (sortPressed) {
			g.drawString("Sorted!" , 50, 50);
			sortPressed = !sortPressed;
		}
		else if (resetPressed) {
					g.drawString("Reset!" , 50, 50);
					grades.fillArray();
					resetPressed = !resetPressed;
		}
		grades.display(g);  //lets see the array of random numbers!


	}

	//Button and TextField event handler
	public void actionPerformed(ActionEvent event) {
		if (event.getSource() == minButton)
			minPressed = true;
		else if (event.getSource() == maxButton)
			maxPressed = true;
		else if (event.getSource() == resetButton)
			resetPressed = true;
		else if (event.getSource() == sumButton)
			sumPressed = true;
		else if (event.getSource() == avgButton)
			avgPressed = true;
		else if (event.getSource() == aButton)
			aPressed = true;
		else if (event.getSource() == luckyButton)
			luckyPressed = true;
		else if (event.getSource() == sortButton){
			sortPressed = true;
			grades.sortArray();
		}

		repaint();
	}

}

