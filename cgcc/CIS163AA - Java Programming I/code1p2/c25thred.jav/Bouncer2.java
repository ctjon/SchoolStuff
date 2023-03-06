import java.awt.*;
import java.applet.Applet;
import java.awt.event.*;
public class Bouncer2 extends Applet
    implements ActionListener {

    private Button start;

    public void init() {
        start = new Button("Start");
        add(start);
        start.addActionListener(this);
    }

    public void actionPerformed(ActionEvent event) { 
        if (event.getSource() == start) {
            Graphics g = getGraphics();
            Ball ball = new Ball(g);
            ball.start();
        }
    }
}

class Ball extends Thread {
    private Graphics g;
    private int x = 7, xChange = 7;
    private int y = 0, yChange = 2;
    private int diameter = 10;
    private int rectLeftX = 0, rectRightX = 100;
    private int rectTopY = 0, rectBottomY = 100;

    public Ball(Graphics graphics) {
        g = graphics;
    }

    public void run() {
        g.drawRect(rectLeftX, rectTopY,
                   rectRightX - rectLeftX, rectBottomY - rectTopY);

        for (int n = 1; n < 1000; n++) {
            g.setColor(Color.white);
            g.fillOval (x, y, diameter, diameter);
            if (x + xChange <= rectLeftX) 
                xChange = -xChange;
            if (x + xChange >= rectRightX)
                xChange = -xChange;

            if (y + yChange <= rectTopY)
                yChange = -yChange;
            if (y + yChange >= rectBottomY)
                yChange = -yChange;

            x = x + xChange;
            y = y + yChange;

            g.setColor(Color.red);  
            g.fillOval (x, y, diameter, diameter);

            try {
                Thread.sleep(50);
            }
            catch (InterruptedException e) {
                System.err.println("sleep exception");
            }
        }
    }
}
