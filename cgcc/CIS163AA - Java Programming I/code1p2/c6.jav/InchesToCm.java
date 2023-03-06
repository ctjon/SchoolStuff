import java.awt.*;
import java.applet.Applet;
import java.awt.event.*;
public class InchesToCm extends Applet
    implements AdjustmentListener {
    private Scrollbar slider;
    private float sliderValue;
    public void init() {
        slider = new Scrollbar(Scrollbar.HORIZONTAL ,0, 1, 0, 100);   
        add(slider);
        slider.addAdjustmentListener(this);
    }   

    public void paint(Graphics g) {   
        float cmEquivalent;
        cmEquivalent = sliderValue*2.54f; 
        g.drawString("Inches="+sliderValue+    
                   " Cm="+cmEquivalent,100,100);
    }

    public void adjustmentValueChanged(AdjustmentEvent e) {
        sliderValue = (float) slider.getValue()/10;
        repaint();
    }
}
