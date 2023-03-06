//simple applet
import java.awt.*;
import java.applet.Applet;
import java.awt.event.*;

public class AnySmallApplet extends Applet
    implements ActionListener {
    // instance variables etc
    private Button aButton;

    public void init() {
        aButton = new Button("press me");
        add(aButton);
        aButton.addActionListener(this);
    }
    
    public void paint(Graphics g) {
        //code
    }

    public void actionPerformed(ActionEvent event) {
        if(event.getSource() == aButton)
            // respond to button
        repaint();  // if needed
    }
}
