/*
 * Created on Feb 16, 2005
 *
 * TODO To change the template for this generated file go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
package carfun;

//USING BUTTONS
import java.awt.*;
import java.applet.*;
import java.awt.event.*;

public class CarFun extends Applet
	implements ActionListener {

	private Button carButton;
	private int carCount = 0;


	public void init() {
		carButton = new Button("Press here for cars");
		add(carButton);
		carButton.addActionListener(this);
	}

	public void paint(Graphics g) {

		/* Put if..else statements here that print out the
		 * words "One" when carCount is 1, and "Two" when
		 * carCount is 2, etc. through 4.  If carCount is some
		 * other number then print out the words "What??"
		 */
		/*
		if (carCount == 1)
			g.drawString("One", 50, 50);
		else if (carCount == 2)
			g.drawString("Two", 50, 50);
		else if (carCount == 3)
			g.drawString("Three", 50, 50);
		else if (carCount == 4)
			g.drawString("Four", 50, 50);
		else
			g.drawString("Huh?", 50, 50);

	*/
		switch(carCount)
		{
			case 1: g.drawString("One", 50, 50); break;
			case 2: g.drawString("Two", 50, 50); break;
			case 3: g.drawString("Three", 50, 50); break;
			case 4: g.drawString("Four", 50, 50); break;
			default: g.drawString("Huh?", 50, 50);
		}
	}
	public void actionPerformed(ActionEvent event)
	{
		carCount = (int)(Math.random() * 7) + 1;
		repaint();
	}
}