import java.awt.*;
import java.applet.Applet;

public class JavaStyle extends Applet
{

	public void paint(Graphics gosh)
	{

		setBackground(Color.black);
		gosh.setColor(Color.white);
		gosh.drawString("Frosty the Snowman was a jolly happy soul "
						+ "with a corn cob pipe and a button nose and "
						+ "two eyes made out of coal.", 50, 50);

		// Draw Snowman
		gosh.fillOval(150, 100, 100, 100);
		gosh.fillOval(175, 50, 50, 50);

	}

}