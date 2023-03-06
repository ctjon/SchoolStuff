import java.applet.Applet;
import java.awt.*;
import java.awt.event.*;
public class LittleAndLarge extends Applet
    implements ActionListener {

    private int diameter=20;
    private Button little, large;

    public void init() {
        little = new Button("Little");
        add (little);
        little.addActionListener(this);
        large = new Button("Large");
        add (large);
        large.addActionListener(this);
    }

    public void paint(Graphics g) {
        g.drawOval (25,25, diameter, diameter);
    }

    public void actionPerformed(ActionEvent event) {
        if (event.getSource() == little)
            diameter = diameter - 10;
        if (event.getSource() == large)
            diameter = diameter + 10;
        repaint();
    }
}

