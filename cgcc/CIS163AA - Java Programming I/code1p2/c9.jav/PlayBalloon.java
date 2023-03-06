import java.applet.Applet;
import java.awt.*;
import java.awt.event.*;
public class PlayBalloon extends Applet 
    implements ActionListener {
    private Button grow, shrink;
    private Balloon myBalloon;

    public void init() {
        grow = new Button ("Grow");
        add (grow);
        grow.addActionListener(this);
    
        shrink = new Button ("Shrink");
        add (shrink);
        shrink.addActionListener(this);
    
        myBalloon = new Balloon (20, 50, 50);
    }

    public void actionPerformed(ActionEvent event) {
        if (event.getSource() == grow)
            myBalloon.changeSize(10);
        if (event.getSource() == shrink)
            myBalloon.changeSize(-10);
        repaint();
    }

    public void paint (Graphics g) {
        myBalloon.display(g);
    }
}

class Balloon{
    private int diameter;
    private int xCoord, yCoord;

    public Balloon (int initialDiameter, int initialX, int initialY) {
        diameter = initialDiameter;
        xCoord = initialX;
        yCoord = initialY;
    }

    public void changeSize (int change) {
        diameter = diameter + change;
    }

    public void display (Graphics g) {
        g.drawOval (xCoord, yCoord, diameter, diameter);
    }
}

