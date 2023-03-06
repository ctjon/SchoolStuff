/*
 * Chris Tjon, Ex 6.4 Wed 4pm
 */
package filledOval;

import java.awt.*;
import java.applet.Applet;
import java.awt.event.*;     //mp

public class FilledOval extends Applet implements AdjustmentListener
{ 
    private Scrollbar lengthBar, heightBar;
    private int height = 100, length = 100;
   
    public void init() {
        Label lengthLabel = new Label ("Length");
        add(lengthLabel);
        lengthBar = new Scrollbar(Scrollbar.HORIZONTAL, 0, 10, 100, 1000);
        add(lengthBar);
        lengthBar.addAdjustmentListener(this);

        Label heightLabel = new Label ("Height");
        add(heightLabel);
        heightBar = new Scrollbar(Scrollbar.VERTICAL, 0, 10, 100, 1000);
        add(heightBar);
        heightBar.addAdjustmentListener(this);
    }
    
    public void adjustmentValueChanged(AdjustmentEvent e)
    {
    	length = lengthBar.getValue();
    	height = heightBar.getValue();
    	repaint();
    }

    public void paint(Graphics g)
    {
        g.fillOval(40, 60, length, height);
    }
}