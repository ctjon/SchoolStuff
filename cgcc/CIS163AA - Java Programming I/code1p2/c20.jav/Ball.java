import java.awt.*;
import java.applet.Applet;

public class Ball extends Applet {

    private int x = 7, xChange = 7;
    private int y = 2, yChange = 2;
    private int diameter=10;

    private int rectLeftX = 0, rectRightX = 100;
    private int rectTopY = 0, rectBottomY = 100;

    public void paint (Graphics g) {
        g.drawRect(rectLeftX, rectTopY,
                   rectRightX-rectLeftX, rectBottomY-rectTopY);

        for (int n = 1; n< 100; n++) {
            Color backgroundColour = getBackground();
            g.setColor(backgroundColour);
            g.fillOval (x, y, diameter, diameter);

            if (x + xChange <= rectLeftX)
                xChange = -xChange;
            if(x+xChange+diameter >= rectRightX)
                xChange = -xChange;

            if (y+yChange <= rectTopY)
                yChange = -yChange;
            if(y+yChange+diameter >= rectBottomY)
                yChange = -yChange;

            x = x + xChange;
            y = y + yChange;

            g.setColor(Color.red);
            g.fillOval (x, y, diameter, diameter);
            try {
                Thread.sleep(50);
            } catch (InterruptedException e) {
                g.drawString("sleep exception", 20, 20);
            }
        }
    }
}

