/*
 * Created on Feb 7, 2005
 *
 * TODO To change the template for this generated file go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
package Average;

import java.applet.Applet;
import java.awt.Graphics;

/**
 * @author chris
 *
 * TODO To change the template for this generated type comment go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
public class Average extends Applet 
{
    public void paint(Graphics g) 
    {
    	int mark1 = 44;
    	int mark2 = 51;
    	float average;
	
    	average = mark1/mark2;
	   	g.drawString("Average = " + average, 50, 50);
    }
}
