/*
 * Chris Tjon - Wed 4pm - Ex 8.8 - Multiplication Table
 */
//package multiplication;

import java.awt.*;
import java.applet.*;

public class TimesTable extends Applet
{
	private int size = 12;

	public void paint (Graphics g)
    {
    	for (int i = 1; i <= size; i++)
    	{
    		for (int j = 1; j <= size; j++)
    		{
    			g.drawString("" + (i * j), i * 25, j * 25);
    		}
    	}
    }
}

