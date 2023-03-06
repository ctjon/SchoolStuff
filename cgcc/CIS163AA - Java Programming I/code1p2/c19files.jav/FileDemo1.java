import java.io.*;
import java.awt.*;
import java.awt.event.*;
class FileDemo1 extends Frame 
    implements WindowListener, ActionListener {

    private TextArea inputTextArea; 
    private Button saveButton;
    private PrintWriter outFile;


    public static void main (String []  args) {
        FileDemo1 demo = new FileDemo1();
        demo.setSize(300,400);
        demo. makeGui();
        demo.setVisible(true);
    }


    public void makeGui() {
        saveButton = new Button("save");
        add ("North", saveButton);
        saveButton.addActionListener(this);
        inputTextArea = new TextArea(10,50);
        add ("Center", inputTextArea);
        addWindowListener(this);   //for windowClosing
    }

    public void actionPerformed(ActionEvent evt) { 
        if (evt.getSource()==saveButton )  {
            try{
                outFile = new PrintWriter(
                                  new FileWriter("testout.txt"), true);              
                outFile.print( inputTextArea.getText() );
                outFile.close();
            }
            catch (IOException e)  {
                System.err.println("File Error: " + e.toString() );
                System.exit(1);
            }
        }
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
}

