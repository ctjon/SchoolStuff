import java.awt.*;
import java.applet.Applet;
import java.awt.event.*;
public class ScrollbarValues extends Applet
    implements AdjustmentListener {
    private Scrollbar slider;
    private int currentX = 1;
    private int currentY = 5;
        
    public void init() {
        slider = new Scrollbar(Scrollbar.HORIZONTAL ,0, 1, 0, 100);   
        add(slider);
        slider.addAdjustmentListener(this);
    }   

    public void adjustmentValueChanged(AdjustmentEvent e) {
        Graphics g = getGraphics();
        currentX = slider.getValue();
        g.drawLine(0, currentY, currentX, currentY);
        currentY = currentY+5;  
    }
}
