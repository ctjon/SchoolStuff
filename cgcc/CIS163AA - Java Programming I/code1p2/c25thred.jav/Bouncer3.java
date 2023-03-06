import java.awt.*;
import java.applet.Applet;
import java.awt.event.*;
public class Bouncer3 extends Applet 
    implements ActionListener {

    private Button start, stop;
    private Ball ball;

    public void init() {
        start = new Button("Start");
        add(start);
        start.addActionListener(this);
        stop = new Button("Stop");
        add(stop);
        stop.addActionListener(this);
    }

    public void actionPerformed(ActionEvent event) {
        if (event.getSource() == start) {
            Graphics g = getGraphics();
            ball = new Ball(g);
            ball.start();
        }
        if (event.getSource() == stop)
            ball.pleaseStop();
    }
}

class Ball extends Thread {
    private boolean keepGoing;
    private Graphics g;
    private int x = 7, xChange = 7;
    private int y = 0, yChange = 2;
    private int diameter = 10;
    private int rectLeftX = 0, rectRightX = 100;
    private int rectTopY = 0, rectBottomY = 100;

    public Ball(Graphics graphics) {
        g = graphics;
        keepGoing = true;
    }

    public void pleaseStop() {
        keepGoing = false;
    }

    public void run() {
        g.drawRect(rectLeftX, rectTopY,
                   rectRightX - rectLeftX, rectBottomY - rectTopY);

        while (keepGoing) {
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


