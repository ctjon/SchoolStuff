/* Converting an Applet into an Application
 *
 * Applets need to be invoked from a web page or applet viewer
 *
 * Applications are completely independent programs.
 *
 * Don't make any changes to the StatsArray class
 *
 * Alter the StatsArrayController to work in a window on the screen
 * called a frame.
 *
 * There are 6 Steps to convert from Applet to Application
 */


import java.awt.*;
//import java.applet.Applet;  STEP #4 Delete - redundant
import java.awt.event.*;

/*STEP #2 change extends Applet to extends Frame
  STEP #5 add implements WindowListener  */
public class StatsArrayControllerApp extends Frame
		implements ActionListener , WindowListener{

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

	/*STEP #1: change the init method to the name of the class.
	Delete the word void.  This becomes the contructor method */
	public StatsArrayControllerApp() {

		/*Step #5  Register the window event handler */
		this.addWindowListener(this);

		/*Step #6 set the layout of the widgets -override the
		  default "border" layout */
		setLayout(new FlowLayout());

		/*Fun addition- put a title in the blue title bar*/
		setTitle("My StatsArray Controller Application");

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

	/*STEP #3:  Create the method main.  This creates the Frame object
	  as an instance of the class */

	 public static void main(String[] args) {
	  	StatsArrayControllerApp f = new StatsArrayControllerApp();
	  	f.setSize(500, 500);  //sets the size of the window
	  	f.setVisible(true);   //make the window visible
	  	}

	public void paint (Graphics g) {

		grades.display(g);  //lets see the array or random numbers!

		if (maxPressed) {
			g.drawString("Maximum is: " + grades.getMax(), 150, 150);
			maxPressed = !maxPressed;
		}

		else if (minPressed) {
			g.drawString("Minimum is: " + grades.getMin(), 150, 150);
			minPressed = !minPressed;
		}

		else if (sumPressed) {
			g.drawString("Sum is: " + grades.getSum(), 150, 150);
			sumPressed = !sumPressed;
		}

		else if (meanPressed) {
			g.drawString("Mean is: " + grades.getMean(), 150, 150);
			meanPressed = !meanPressed;
		}
		else if (luckyPressed) {
			g.drawString("Lucky 7  Y or N: " + grades.getLucky7(),
						  150, 150);
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

	/*STEP #5 Add ALL of the WindowListener required methods.
   		The windowClosing method to handle the event when a user
   		clicks on the "close window button".  Also must add implements
   		WindowListener to the header and this.addWindowListener(this)
   		to register the event handler */


		public void windowClosing(WindowEvent event) {
			System.exit(0);  //closes window and app cleanly
		}

		public void windowIconified(WindowEvent event) {
		}

		public void windowOpened(WindowEvent event) {
		}

		public void windowClosed(WindowEvent event) {
		}

		public void windowDeiconified(WindowEvent event) {
		}

		public void windowActivated(WindowEvent event) {
		}

		public void windowDeactivated(WindowEvent event) {
		}

}

