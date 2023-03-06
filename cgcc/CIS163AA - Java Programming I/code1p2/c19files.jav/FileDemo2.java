import java.io.*;
import java.awt.*;
import java.awt.event.*;

class FileDemo2 extends Frame
    implements WindowListener, ActionListener {

    private TextArea inputTextArea;
    private Button loadButton;
    private BufferedReader inFile;
    private TextField nameField;

    public static void main (String [] args) {
        FileDemo2 demo = new FileDemo2();
        demo.setSize(300,400);
        demo. makeGui();
        demo.setVisible(true);
    }

    public void makeGui() {
        Panel top = new Panel();
        loadButton = new Button("load");
        top.add(loadButton);
        loadButton.addActionListener(this);
        nameField = new TextField(20);
        top.add(nameField);
        nameField.addActionListener(this);
        add ("North", top);
        inputTextArea = new TextArea("",10,50);
        add ("Center", inputTextArea);
        addWindowListener(this);
    }



    public void actionPerformed(ActionEvent evt) {
        if (evt.getSource()==loadButton) {
            String fileName;
            fileName = nameField.getText();
            try {
                inFile = new BufferedReader(
                             new FileReader(fileName));
                inputTextArea.setText( "");       // clear the input area
                String line;

                while( ( line = inFile.readLine() ) != null) {
                    inputTextArea.append(line+"\n");
                }
               inFile.close();
            }

            catch (IOException e) {
                System.err.println("Error in file "+fileName+": "+e.toString() );
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



