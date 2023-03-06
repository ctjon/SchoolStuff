import java.awt.*;
import java.applet.Applet;
public class TriangleMethodDemo extends Applet {
    public void paint(Graphics g) {
        drawTriangle(g,80,200,100,110);
        drawTriangle(g,125,220,60,70);
    }
    private void drawTriangle‹(Graphics g,int bottomX, int bottomY,
                            int base,int height) {
            int rightX = bottomX+base;
            int topX = bottomX+base/2;
            int topY = bottomY-height;

            g.drawLine‹(bottomX,bottomY, rightX,bottomY);
            g.drawLine‹(rightX,bottomY,topX,topY);
            g.drawLine‹(topX,topY, bottomX,bottomY);
        }
    }
