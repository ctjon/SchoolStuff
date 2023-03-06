import java.awt.*;
import java.applet.Applet;
import java.awt.event.*;
public class LabelDemo extends Applet 
    implements AdjustmentListener {
    private Scrollbar bar1, bar2;
    private int bar1Value = 0;
    private int bar2Value = 0;

    public void init() {
        Label title1, title2;      // local scope is sufficient
        title1 = new Label("up:");
        add(title1);
        bar1 = new Scrollbar(Scrollbar.HORIZONTAL, 0,1,0,100);
        add(bar1);
        bar1.addAdjustmentListener(this);
        title2 = new Label("    down:");
        add(title2);
        bar2 = new Scrollbar(Scrollbar.HORIZONTAL, 0,1,0,100);
        add(bar2);
        bar2.addAdjustmentListener(this);
    }

    public void paint(Graphics g) {   
        g.drawString("UP value is " + bar1Value, 100,100);
        g.drawString("DOWN value is " + bar2Value, 100, 150);
    }

    public void adjustmentValueChanged(AdjustmentEvent e) {
        bar1Value = bar1.getValue();  
        bar2Value = bar2.getValue();
        repaint();
    }
}

