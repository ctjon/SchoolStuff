// AWT-based application
import java.awt.*;
import java.awt.event.*;

public class AWTApplication extends Frame 
    implements ActionListener, WindowListener {
    // instance variables etc
    private Button aButton;
    private Scrollbar aScrollbar;
    private Model aModelInstance;

    public static void main(String [] args) {
        AWTApplication anInstance = new AWTApplication();
        anInstance.setSize(300,200);
        anInstance.setVisible(true);
    }
    
    public AWTApplication() {      // constructor
        aButton = new Button("press me");
        add(aButton);
        aButton.addActionListener(this);
        aModelInstance = new Model();
        this.addWindowListener(this);     //for windowClosing
    }
    
    public void paint(Graphics g) { 
        aModelInstance.display(g);
    }

    public void actionPerformed(ActionEvent event) { 
        if(event.getSource() == aButton)
            //  respond to button, e.g:
            aModelInstance.getSomething();
    }
    

    public void windowClosing(WindowEvent e) {
        System.exit(0);
    }
    //empty WindowListener Methods
    public void windowIconified(WindowEvent e) {
    }
    public void windowOpened(WindowEvent e) {
    }
    public void windowClosed(WindowEvent e) {
    }
    public void windowDeiconified(WindowEvent e) {
    }
    public void windowActivated(WindowEvent e) {
    }
    public void windowDeactivated(WindowEvent e) {
    }

    // the Model class is identical to the applet
    // example, and is in its own file.
}
