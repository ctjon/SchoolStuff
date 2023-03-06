/*
 * Created on Feb 16, 2005
 *
 * TODO To change the template for this generated file go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
package buttoncount;

/**
 * @author chris
 *
 * TODO To change the template for this generated type comment go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
/*This programs tallies whether a user likes cars
 * or trucks based on votes (button clicks).  It cleverly
 * prints an appropriate message.
 */

import java.awt.*;
import java.applet.*;
import java.awt.event.*;

public class ButtonCount extends Applet
	implements ActionListener {

	private Button truckButton;
	private Button carButton;
	private Button funnyButton;

	private int truckCount = 0;
	private int  carCount = 0;

	private boolean funny = false;



	public void init() {
		carButton = new Button("Press here for cars");
		add(carButton);
		carButton.addActionListener(this);

		truckButton = new Button("Press here for trucks");
		add(truckButton);
		truckButton.addActionListener(this);

		funnyButton = new Button("Press here for funny message");
		add(funnyButton);
		funnyButton.addActionListener(this);
	}

	public void paint(Graphics g) {
		g.drawString("Number of cars is " + carCount, 10, 120);
		g.drawString("Number of trucks is " + truckCount, 10, 135);

		g.setColor(Color.blue);
		if (carCount > truckCount) {
			g.drawString("I like cars better", 10, 150);
		} else if (carCount < truckCount) {
			g.drawString("I like trucks better", 10, 150);
		} else {
			g.drawString("We have a tie", 10, 150);
		}

		if (funny) {
			g.setColor(Color.green);
			g.drawString("Who cares!", 10, 170);
			funny = !funny;
		}

	}


	public void actionPerformed(ActionEvent event) {
		if (event.getSource() == truckButton)
			truckCount++;
		if (event.getSource () == carButton)
			carCount++;


		if (event.getSource() == funnyButton)
			funny = true;


		repaint();
	}
}