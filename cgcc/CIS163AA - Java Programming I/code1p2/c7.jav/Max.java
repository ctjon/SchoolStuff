import java.awt.*;
import java.applet.Applet;
import java.awt.event.*;
public class Max extends Applet 
    implements AdjustmentListener {

    private Scrollbar volumeControl;
    private int max = 0;
    private int volume = 0;

    public void init() {
        volumeControl = new Scrollbar(Scrollbar.HORIZONTAL, 0, 1, 0, 100);
        add(volumeControl);
        volumeControl.addAdjustmentListener( this);
    }


    public void paint(Graphics g) {
        if (volume > max)
            max = volume;
        g.drawString("Maximum value is " + max, 50, 50);
    }

    public void adjustmentValueChanged(AdjustmentEvent event) {
        volume = volumeControl.getValue();
        repaint();
    }
}
