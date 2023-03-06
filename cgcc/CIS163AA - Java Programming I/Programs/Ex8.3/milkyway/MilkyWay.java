/*
 * Chris Tjon - Wed 4pm - Ex 8.3 - Milky Way Program
 */
package milkyway;

import java.awt.*;
import java.applet.Applet;

public class MilkyWay extends Applet
{ 
    private Scrollbar lengthBar, heightBar;
    private int height = 100, length = 100;
   
    public void paint(Graphics g)
    {
    	int xpos;
    	int ypos;
    	int diameter;
    	
        for (int i = 0; i < 100; i++)
        {
        	xpos = (int)((Math.random() * 200) + 1);
        	ypos = (int)((Math.random() * 200) + 1);
        	diameter = (int)((Math.random() * 100) + 1);
        	g.drawOval(xpos, ypos, diameter, diameter);
        }
    }
}