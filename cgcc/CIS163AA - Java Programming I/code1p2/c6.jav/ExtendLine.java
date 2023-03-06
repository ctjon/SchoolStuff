import java.awt.*;
import java.applet.Applet;
import java.awt.event.*;
public class ExtendLine extends Applet
    implements AdjustmentListener {
    private Scrollbar slider;
    private int currentX = 1;
    private int newX;
    
    public void init() {
        slider = new Scrollbar(Scrollbar.HORIZONTAL ,0, 1, 0, 100);   
        add(slider);
        slider.addAdjustmentListener(this);
    }   

    public void adjustmentValueChanged(AdjustmentEvent e) {
        Graphics g = getGraphics();
        newX = currentX+slider.getValue();
        g.drawLine(currentX, 50, newX, 50);
        currentX = newX;  
    }
}
