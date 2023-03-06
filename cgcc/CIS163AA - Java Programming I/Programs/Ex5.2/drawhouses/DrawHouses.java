/*
 * Chris Tjon, Ex 5.2, Wed 4pm
 * 
 * Draw a street of 4 houses 10 pixels apart
 */
package drawhouses;

import java.awt.*;
import java.applet.Applet;

public class DrawHouses extends Applet
{
	public void paint(Graphics g)
	{
		drawStreet(g, 30, 50, 50);
	}	
	
	private void drawStreet(Graphics g, int wallHeight, int bottomX, int bottomY)
	{
		int i;
		int gap = 10;
		int width = wallHeight;
		int numHouses = 4;
			
		for (i = 0; i < numHouses; i++)
		{
			drawHouse(g, (bottomX + (width * i) + (gap * i)), bottomY, width, wallHeight);
		}
	}
	
	
	private void drawTriangle(Graphics g, int bottomX, int bottomY, int base, int height)
	{
		g.drawLine(bottomX, bottomY, bottomX + base, bottomY);
		g.drawLine(bottomX + base, bottomY, bottomX+base/2, bottomY - height);
		g.drawLine(bottomX+base/2, bottomY - height, bottomX, bottomY);
	}
	
	private void drawHouse(Graphics g, int bottomX, int bottomY, int width, int height)
	{
		g.drawRect(bottomX, bottomY-height, width, height);
		drawTriangle(g, bottomX, bottomY-height, width, height/2);
	}
}
