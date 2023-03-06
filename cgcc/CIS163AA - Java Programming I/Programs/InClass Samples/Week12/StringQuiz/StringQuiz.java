/*
 * Created on Apr 13, 2005
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

import java.awt.*;
import java.applet.Applet;


public class StringQuiz extends Applet
{

	public void paint(Graphics g)
	{
		String myStringA = "StringA";
		String myStringB = "StringA";
		String myQuoteString = "Quote = \"";
		int result;
		char charResult;
		
		g.drawString(24 + 10 + " is a great number", 50, 50);
		g.drawString("This is a great number " + 24 + 10, 50, 65);
		
		if (myStringA == myStringB)
			g.drawString(myStringA + " ==  " + myStringB, 50, 80);
		else
			g.drawString(myStringA + " != " + myStringB, 50, 80);
		
		if (myStringA.equals(myStringB))
			g.drawString(myStringA + " ==  " + myStringB, 50, 95);
		else
			g.drawString(myStringA + " != " + myStringB, 50, 95);
		
		g.drawString("Top\nBottom", 50, 110);
		
		g.drawString("QuoteString = [" + myQuoteString + "]", 50, 125);
		
		result = "a".compareTo("z");
		g.drawString("\"a\".compareTo(\"z\") == " + result, 50, 140);
		
		result = "a".compareTo("Z");
		g.drawString("\"a\".compareTo(\"Z\") == " + result, 50, 155);
		
		charResult = myStringB.charAt(1);
		g.drawString("charResult = " + charResult, 50, 170);
		
		myStringB.charAt(1) = 'p';
		g.drawString("charResult = " + charResult, 50, 185);
	}
}
