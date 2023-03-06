import java.applet.Applet;
import java.awt.*;
import java.awt.event.*;
public class Voting extends Applet
    implements AdjustmentListener {

    private Scrollbar bar;
    private int age = 0;

    public void init() {
        bar = new Scrollbar(Scrollbar.HORIZONTAL ,0,1,0,100);
        add(bar);
        bar.addAdjustmentListener( this);
    }


    public void paint(Graphics g) {
        if (age >17)
            g.drawString ("You may vote", 50, 50);
        g.drawString("Age is " + age, 50, 70);
    }

    public void adjustmentValueChanged(AdjustmentEvent event) {
        age = bar.getValue();
        repaint();
    }
}
