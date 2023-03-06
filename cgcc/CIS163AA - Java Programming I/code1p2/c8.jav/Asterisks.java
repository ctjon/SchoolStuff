import java.awt.*;
import java.applet.Applet;
import java.awt.event.*;
public class Asterisks extends Applet
    implements AdjustmentListener {
    private Scrollbar bar;
    private int count, numberRequired = 8;

    public void init() {
        bar = new Scrollbar(Scrollbar.HORIZONTAL, 0, 1, 0, 100);
        add(bar);
        bar.addAdjustmentListener(this);
    }

    public void paint(Graphics g) {
        int count;
        int x = 10;
        for (count = 0; count < numberRequired; count++) {
            g.drawString ("*", x, 30);
            x = x + 10;
        }
    }

    public void adjustmentValueChanged(AdjustmentEvent e) { 
        numberRequired = bar.getValue();
        repaint();
    }
}

