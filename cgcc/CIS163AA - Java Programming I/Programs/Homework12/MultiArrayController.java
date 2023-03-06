/*This controller displays the 2 dimensional array and all buttons to
  manipulate the array.*/


import java.awt.*;
import java.applet.Applet;
import java.awt.event.*;

public class MultiArrayController extends Applet
		implements ActionListener {

	//set up buttons to control the MultiArray
	private Button maxButton;
	private Button minButton;
	private Button sumButton;
	private Button avgButton;
	private Button aButton;
	private Button luckyButton;

	private Button specificColButton;

	// variables for communicating with paint()
	private boolean maxPressed;
	private boolean minPressed;
	private boolean sumPressed;
	private boolean avgPressed;
	private boolean aPressed;
	private boolean luckyPressed;

	private boolean specificColPressed;

	/*instantiate your MultiArray object called grades
	  creates array of size 10 rows and 5 columns
	  located at x = 50, y = 70 when displayed */
	private MultiArray grades = new MultiArray(10, 5, 50, 70);

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

		aButton = new Button("Number of A's");
		add(aButton);
		aButton.addActionListener(this);


		luckyButton = new Button("Lucky 7");
		add(luckyButton);
		luckyButton.addActionListener(this);

		specificColButton = new Button("2nd column");
		add(specificColButton);
		specificColButton.addActionListener(this);

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

		else if (avgPressed) {
			g.drawString("Average is: " + grades.getAverage(), 50, 50);
			avgPressed = !avgPressed;
		}
		else if (aPressed) {
					g.drawString("Number of A's: " + grades.count90s(), 50, 50);
					aPressed = !aPressed;
		}
		else if (luckyPressed) {
			g.drawString("Lucky 7  Y or N: " + grades.getLucky7(),
						  50, 50);
			luckyPressed = !luckyPressed;
		}
		else if (specificColPressed) {  //displays and totals the 2nd col
			int col = 1;  //the index for 2nd column

			grades.displayColumn(col, g);
			g.drawString("The total of the 2nd column is: " +
				grades.sumColumn(col, g), 50, 50);
			specificColPressed = !specificColPressed;
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
		else if (event.getSource() == avgButton)
			avgPressed = true;
		else if (event.getSource() == aButton)
			aPressed = true;
		else if (event.getSource() == luckyButton)
			luckyPressed = true;
		else if (event.getSource() == specificColButton)
			specificColPressed = true;

		repaint();
	}

}

