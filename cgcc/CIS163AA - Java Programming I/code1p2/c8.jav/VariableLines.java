import java.awt.*;
import java.applet.Applet;
import java.awt.event.*;

public class VariableLines extends Applet
    implements AdjustmentListener {

    private Scrollbar lines;
    private int numberOfLines;

    public void init() {
        lines = new Scrollbar(Scrollbar.HORIZONTAL, 0, 1, 0, 100);
        add(lines);
        lines.addAdjustmentListener(this);
    } 


    public void paint (Graphics g) {
        int count = 1;
        int x = 20;
        int y = 20;
        while (count < numberOfLines) {
            g.drawLine (x, y, x + 100, y);
            y = y + 10;
            count++;
        }
    }

    public void adjustmentValueChanged(AdjustmentEvent e) {
        numberOfLines = lines.getValue();
        repaint();
    }
}

