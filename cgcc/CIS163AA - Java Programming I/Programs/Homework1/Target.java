/*
 * Chris Tjon Wed 4pm  Ex. 3.5 - Target
 *
 * Draw a target and place inside a rectangle.  Additionally,
 * present values for each ring on the target.
 */
import java.awt.*;
import java.applet.Applet;

public class Target extends Applet
{
	public void paint(Graphics g)
	{
		g.setColor(Color.black);
		g.fillRect(0, 0, 320, 320);
		g.setColor(Color.blue);
		g.fillOval(0, 0, 320, 320);   // Outer Ring
		g.setColor(Color.orange);
		g.fillOval(40, 40, 240, 240); // Second Ring
		g.setColor(Color.cyan);
		g.fillOval(80, 80, 160, 160); // Third Ring
		g.setColor(Color.red);
		g.fillOval(120, 120, 80, 80); // Inner Ring
		g.setColor(Color.white);

		g.drawString("10", 155, 30);  // Label for "10"
		g.drawString("20", 155, 70);  // Label for "20"
		g.drawString("30", 155, 110); // Label for "30"
		g.drawString("50", 155, 165); // Label for "50"

	}
}