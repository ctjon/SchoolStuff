import java.awt.*;
import java.applet.Applet;
public class FirstShapes extends Applet {
    public void paint(Graphics g) {
        g.drawRect(30,30,80,40);
        g.drawOval(120,30,50,50);
        g.setColor(Color.black);
        g.fillRect(30,100,80,40);
        g.fillOval(120,100,50,50);
        g.drawLine(30,160,130,170);
        g.drawArc(30,180,50,50,60,40);
        g.fillArc(120,180,50,50,60,40);
    }
}
