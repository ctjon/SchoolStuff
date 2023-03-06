import java.awt.*;
import java.applet.Applet;
public class HouseDemo extends Applet
{
    public void paint(Graphics g) {
        drawHouse(g,50,50, 70,30);
        drawHouse(g,100,50,60,20);
    }

    private void drawTriangle(Graphics g,int bottomX, int bottomY,
                            int base,int height) {
        g.drawLine(bottomX,bottomY, bottomX+base,bottomY);
        g.drawLine(bottomX+base,bottomY,bottomX+base/2,bottomY-height);
        g.drawLine(bottomX+base/2,bottomY-height, bottomX,bottomY);
    }

    private void drawHouse(Graphics g,int bottomX,int bottomY,
                            int width,int height) {
        g.drawRect(bottomX, bottomY-height, width,height);
        drawTriangle(g,bottomX, bottomY-height,width, height/2);
    }
}
