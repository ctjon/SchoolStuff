/*
 * Created on Feb 9, 2005
 *
 * TODO To change the template for this generated file go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
package firstevent;

import java.awt.*;
import java.applet.Applet;
import java.awt.event.*;  //new library needed for events

public class FirstEvent extends Applet
	implements AdjustmentListener {

	//instance variables
	private Scrollbar mySlider;  //object of type Scrollbar
	private int mySliderValue;



	/*will be automatically invoked when applet is run and
	  creates an initial screen with a scrollbar widget
	 */
	public void init() {
		Label mySliderTitle;
		mySliderTitle = new Label("Move Blind");
		add(mySliderTitle);
		
		mySlider = new Scrollbar(Scrollbar.HORIZONTAL,
					0, 1, 0, 101);

		add(mySlider);

		//register our program as a scrollbar listener
		mySlider.addAdjustmentListener(this);
	}



	public void paint(Graphics g) {
		g.drawString("Current value is " + mySliderValue, 100, 100);
		g.drawRect(40,80,60,100);
		if (mySliderValue > 50)
			g.setColor(Color.green);
		if (mySliderValue < 25)
			g.setColor(Color.red);
		g.fillRect(40,180 - mySliderValue,60,mySliderValue);
 	}



	/* Because our program is registered as a listener
	   whenever the scrollbar is used this method is executed
	   automatically
	 */
	public void adjustmentValueChanged(AdjustmentEvent e) {

		/*put whatever code is needed to be executed when an
		 event occurs */

		mySliderValue = mySlider.getValue();
		repaint();  //invokes the paint method
	}

}


/* NOTES

 SCOPE OF A VARIABLE = area of the program where the variable can be used

 WHAT IS THE SCOPE OF mySlider AND mySliderValue?
 	Can be used by any method in the FirstEvent class.
 	Also called INSTANCE variables

 */