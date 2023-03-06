import java.awt.*;
import java.applet.Applet;
public class TriangleTry extends Applet {
    public void paint(Graphics g) {
        int bottomX=80;
        int bottomY=200;
        int base=100;
        int height=110;

        g.drawLine(bottomX,bottomY, bottomX+base,bottomY);
        g.drawLine(bottomX+base,bottomY,bottomX+base/2,bottomY-height);
        g.drawLine(bottomX+base/2,bottomY-height, bottomX,bottomY);

    }
}
