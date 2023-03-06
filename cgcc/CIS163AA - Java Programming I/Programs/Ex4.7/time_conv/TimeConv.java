/*
 * Chris Tjon, Ex 4.7 Wed 4pm
 * 
 * Program to translate 2549 seconds into hours, minutes, and seconds
 */
package time_conv;

import java.applet.Applet;
import java.awt.Graphics;

public class TimeConv extends Applet 
{
    public void paint(Graphics g) 
    {
    	int totalSeconds = 3671;
    	int hours;
    	int minutes;
    	int seconds;
    	int remainder;
	
    	hours = totalSeconds / 3600;		//3600 seconds/hr
    	remainder = totalSeconds % 3600;    //how many seconds left for min:sec
    	minutes = remainder / 60;			//60 seconds/min
    	seconds = remainder % 60;           //remainder is :sec
    	
    	//Do the output    	
		g.drawString("Hours = " + hours, 50, 50);
    	g.drawString("Minutes = " + minutes, 50, 70);
    	g.drawString("Seconds = " + seconds, 50, 90);
    }
}