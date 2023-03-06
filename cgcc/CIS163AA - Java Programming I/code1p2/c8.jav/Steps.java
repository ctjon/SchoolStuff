import java.awt.*;
import java.applet.Applet;
import java.awt.event.*;
public class Steps extends Applet
    implements AdjustmentListener {

    private Scrollbar steps;
    private int count, numberOfSteps;

    public void init() {
        steps = new Scrollbar(Scrollbar.HORIZONTAL, 0, 1, 0, 100);
        add(steps);
        steps.addAdjustmentListener( this);
    }

    public void paint(Graphics g) {
        int count=0;
        int x = 20;
        int y = 20;
        while (count<numberOfSteps) {
            g.drawLine (x, y, x+20, y);
            g.drawLine (x+20, y, x+20, y+20);

            x = x+20;
            y = y+20;
            count++;
        }
    }

    public void adjustmentValueChanged(AdjustmentEvent e) {
        numberOfSteps = steps.getValue();
        repaint();
    }
}

