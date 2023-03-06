import java.applet.Applet;
import java.awt.*;
import java.awt.event.*;

public class PlayBalloon extends Applet implements ActionListener {

    private Button grow, shrink, left, right;
    private Balloon myBalloon;

    public void init() {
        grow = new Button("Grow");
        add(grow);
        grow.addActionListener(this);

        shrink = new Button("Shrink");
        add(shrink); 
        shrink.addActionListener(this);      

        left = new Button("Left");
        add(left);
        left.addActionListener(this);

        right = new Button("Right");
        add(right);
        right.addActionListener(this);

        myBalloon = new Balloon();
    }

    public void actionPerformed(ActionEvent event) {
        if (event.getSource() == grow)
            myBalloon.grow();
        if (event.getSource() == shrink)
            myBalloon.shrink();
        if (event.getSource() == left)
            myBalloon.left();
        if (event.getSource() == right)
            myBalloon.right();
        repaint();
    }

    public void paint (Graphics g) {
        myBalloon.display(g);
    }
}


class Balloon {

    private int diameter = 10;
    private int xCoord = 20, yCoord = 50;

    public void display(Graphics g) {
        g.drawOval(xCoord, yCoord, diameter, diameter);
    }

    public void left() {
        xCoord = xCoord - 10;
    }

    public void right() {
        xCoord = xCoord + 10;
    }

    public void grow() {
        diameter = diameter+5;
    }

    public void shrink() {
        diameter = diameter-5;
    }
}
