/*
 * Ex 4.3, Chris Tjon, Wed 4pm 
 * 
 * Calculate the average of two values to 1 decimal place
 */
package average;

import java.applet.Applet;
import java.awt.Graphics;

public class Average extends Applet 
{
    public void paint(Graphics g) 
    {
    	int mark1 = 44;
    	int mark2 = 51;
    	float average;
	
    	average = (float)(mark1 + mark2) / 2;  // cast the addition to get float result
	   	g.drawString("Average = " + average, 50, 50);
    }
}
