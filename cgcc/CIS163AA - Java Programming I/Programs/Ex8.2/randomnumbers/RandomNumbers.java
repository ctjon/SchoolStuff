/*
 * Chris Tjon - Wed 4pm - Ex 8.2 - Random Numbers in While Loop
 */
package randomnumbers;

import java.awt.*;
import java.applet.*;

public class RandomNumbers extends Applet
{

    public void paint (Graphics g)
    {
    	int numCount = 0;
    	double randomNum;
    	
    	while (numCount < 10)
    	{
    		randomNum = Math.random();
    		g.drawString("Random Number " 
    				+ (numCount + 1)
					+ " is " 
					+ randomNum, 
					50, (50 + (numCount * 20)));
    		numCount++;
    	}        
    }
}
