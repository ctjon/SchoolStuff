import java.awt.Color;
import java.awt.Graphics;

/*
 * Created on Mar 29, 2005
 *
 * TODO To change the template for this generated file go to
 * Window - Preferences - Java - Code Style - Code Templates
 */

/**
 * @author chris
 *
 * TODO To change the template for this generated type comment go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
public class Monster2 extends Monster
{
	public Monster2()
	{
		super();
	}
	
	public Monster2(int desiredXCoord, int desiredYCoord, int desiredSize)
	{
		super(desiredXCoord, desiredYCoord, desiredSize);
	}
	
	public void reset(Graphics g, int desiredXCoord, int desiredYCoord, int desiredSize) 
	{
		x = desiredXCoord; 
	    y = desiredYCoord;
	    size = desiredSize;
	    eyeColor = Color.red;
	    bodyColor = Color.black;
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
}
