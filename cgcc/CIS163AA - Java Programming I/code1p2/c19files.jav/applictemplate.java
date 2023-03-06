import java.io.*;
import java.awt.*;
import java.awt.event.*;
class CLASS extends Frame 
    implements WindowListener {

    private DebugWin dw = new DebugWin();  // for tracing

    public static void main (String []  args) {
        CLASS demo = 
                     new CLASS();
        demo.setSize(300,400);
        demo. makeGui();
        demo.setVisible(true);
    }


    public void makeGui() {
       // GUI creation, etc....
       //    goes here

        addWindowListener(this);   //for windowClosing
    }

   

 // standard code for window closing, etc
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
}

