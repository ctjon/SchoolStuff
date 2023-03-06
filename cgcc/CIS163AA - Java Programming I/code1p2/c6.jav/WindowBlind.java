// Scrollbar example - window blind simulator
import java.awt.*;
import java.applet.Applet;
import java.awt.event.*; 
public class WindowBlind extends Applet
    implements AdjustmentListener {
    private Scrollbar slider;
    private int sliderValue;

    public void init () {
        slider = new Scrollbar(Scrollbar.VERTICAL,0,1,0,100);
        add(slider);
        slider.addAdjustmentListener(this);
    }

    public void paint (Graphics g) {
        showStatus("Scrollbar value is " + sliderValue);
        g.drawRect(40, 80, 60, 100);
        g.fillRect(40, 80, 60, sliderValue);
    }

    public void adjustmentValueChanged(AdjustmentEvent e) {
        sliderValue = slider.getValue();
        repaint();
    }
}

