/*
 * Created on Feb 9, 2005
 *
 * TODO To change the template for this generated file go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
package shapes;

/**
 * @author chris
 *
 * TODO To change the template for this generated type comment go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
/*	Your Name Here:
Please add the appropriate code to this small
applet as indicated.  When your code is running
then print out and answer the questions at the bottom.
*/
import java.awt.*;
import java.applet.Applet;

public class Shapes extends Applet 
{
	public void paint (Graphics g) 
	{



		/*  Add two lines of code that declare two int
        variables called volumeCube and volumeRectangle
    AND
  	Assign volumeCube the value returned when the
    calcCubeVolume method is invoked for a cube with
    a side = 5.
    AND
    Assign volumeRectangle to the value returned when
    method calcRectVolume is invoked for a rectangle with
    the length = 10, width = 5, and the height = 2.
*/
		int volumeCube;
		int volumeRectangle;

		volumeCube = calcCubeVolume(5);
		volumeRectangle = calcRectVolume(10, 5, 2);

		setBackground(Color.lightGray);
		g.setColor(Color.blue);
		g.drawString("The Volume of the cube is: "
			+ volumeCube, 100, 100);
		g.drawString("The Volume of the rectangle is: "
			+ volumeRectangle, 100, 150);
	}

	private int calcCubeVolume(int side)
	{
		int volume = side * side * side;
		return volume;
	}

	private int calcRectVolume(int length, int width,int height)
	{
		return	(length * width * height);
	}
}



/*QUESTIONS TO ANSWER:

FOR THE calcCubeVolume METHOD:

	Identify the  local variables

	Identify the formal arguments

	Datatype of returned value

	What value is returned

	What is the scope/lifetime of variable volume

	Where is this method invoked?


General Questions:

	How does the return statement work in the calcRectVolume method?


	What are the actual parameters in your calcRectVolume call?


	What are the formal parameters in the calcRectVolume method?


	What rules must be followed between actual and formal parameters?

*/