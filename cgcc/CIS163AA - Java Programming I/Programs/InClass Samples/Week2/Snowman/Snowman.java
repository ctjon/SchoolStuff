// Chris Tjon snowman W 4:00
import java.awt.*;
import java.applet.Applet;

public class Snowman extends Applet
{
	public void paint(Graphics g)
	{
		setBackground(Color.blue);
		g.setColor(Color.white);
		g.fillOval(160, 90, 30, 30);  // Top
		g.fillOval(155, 115, 40, 40); // Middle
		g.fillOval(150, 150, 50, 50); // Bottom
		g.setColor(Color.black);
		g.drawLine(150, 95, 200, 95);  // Brim of Hat
		g.fillRect(160, 75, 30, 20);  // Top Hat
	}
}