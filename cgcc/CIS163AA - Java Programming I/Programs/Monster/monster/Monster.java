/*
 * Chris Tjon, Monster Class, Wed 4pm
 */
package monster;

import java.awt.*;

public class Monster {

	private int x;
	private int y;
	private int size; //in pixels
	private Color eyeColor;  //data type of color variable is the Color class.
	private Color bodyColor;
	
	public Monster(int desiredXCoord, int desiredYCoord, int desiredSize) 
	{
	    x = desiredXCoord; 
	    y = desiredYCoord;
	    size = desiredSize;
	    eyeColor = Color.red;  //I decided not to allow the user to set the colors
	    bodyColor = Color.black;
	}
	
	public void run(int howFar) 
	{
		x += howFar;
	}
	
	public void reset(Graphics g, int desiredXCoord, int desiredYCoord, int desiredSize) 
	{
		x = desiredXCoord; 
	    y = desiredYCoord;
	    size = desiredSize;
	    eyeColor = Color.red;
	    bodyColor = Color.black;
	}
	
	public void puffUp(Graphics g) 
	{
		size = size * 2;
		display(g);
		for (int i = 0; i < 999999999; i++);
		eyeColor = Color.white;
	    bodyColor = Color.white;
	    display(g);
	    eyeColor = Color.red;
	    bodyColor = Color.black;
		size = size / 2;
	}
	
	public void jump(Graphics g) 
	{
		x += 25;
		y += 150;
	}
	
	public void growl(Graphics g) 
	{
		g.setColor(Color.blue);
		g.drawString("Growl", x, y);
	}
	
	public void becomeAngry(Graphics g) 
	{
		eyeColor = Color.black;
	    bodyColor = Color.red;
	    display(g);
	    for (int i = 0; i < 999999999; i++);
	    eyeColor = Color.red; 
	    bodyColor = Color.black;
	    display(g);
	}
	
	
	public void display(Graphics g) 
	{
	    // BODY
	    g.setColor(bodyColor);
	    int monsterWidth = size;
	    int monsterHeight = size * 2 / 3;
	    g.fillOval(x, y, monsterWidth, monsterHeight);
	    // EYES
	    
	    g.setColor(eyeColor);
	    int eyeWidth = monsterWidth / 10;
	    int eyeHeight = eyeWidth * 2 / 3;
	    int eye1X = x + monsterWidth / 6;
	    int eye1Y = y + monsterHeight / 3;
	    g.fillOval( eye1X, eye1Y, eyeWidth, eyeHeight );
	    int eye2X = eye1X + monsterWidth / 2;
	    int eye2Y = eye1Y;
	    g.fillOval( eye2X, eye2Y, eyeWidth, eyeHeight );
	}
}
