// MVC Applet
import java.awt.*;
import java.applet.Applet;
import java.awt.event.*;

public class AnyMVCApplet extends Applet
    implements ActionListener {
    // instance variables etc
    private Button aButton;
    private Model aModelInstance;
    
    public void init() {
        aButton = new Button("press me");
        add(aButton);
        aButton.addActionListener(this);
        
        aModelInstance = new Model();
    }
    public void paint(Graphics g) {
        aModelInstance.display(g);
    }
    
    public void actionPerformed(ActionEvent event) {
        if(event.getSource() == aButton)
            // respond to button, e.g:
            aModelInstance.getSomething();
        repaint();  //if needed
    }
}

class Model {   // start of model class
    // private instance items
    public void setSomething() {
    // code
    }
    public void getSomething() {
        // code
    }
    public void display(Graphics g) {
        // code to display current state
    }
}   // end of model class
