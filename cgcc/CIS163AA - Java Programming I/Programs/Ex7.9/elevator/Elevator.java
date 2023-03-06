/*
 * Chris Tjon - Wed 4pm - Ex 7.9 - Elevator Program
 */
package elevator;

import java.awt.*;
import java.applet.Applet;
import java.awt.event.*; 

public class Elevator extends Applet implements ActionListener
{
    private Button upButton;
    private Button downButton;
    private boolean up;
    private boolean down;
    
    public void init ()
    {
        upButton = new Button("Up");
        add(upButton);
        upButton.addActionListener(this);
        downButton = new Button("Down");
        add(downButton);
        downButton.addActionListener(this);
        
    }

    public void paint (Graphics g)
    {
    	if (up) // Up Button Pressed
    	{
    		showStatus("Going Up!");
            g.drawRect(40, 80, 60, 100);
        }
    	else if (down) // Down Button Pressed
    	{
    		showStatus("Going Down!");
            g.drawRect(40, 180, 60, 100);
    	}
    	else  // Initial Starting Position - Down
    		g.drawRect(40, 180, 60, 100);  
        
    }

    public void actionPerformed(ActionEvent event)
    {
    	// Determine which button was pressed & repaint
        if (event.getSource() == upButton)
        {
        	up = true;
        	down = false;
        }
        if (event.getSource() == downButton)
        {
        	up = false;
        	down = true;
        }
        repaint();
    }
}