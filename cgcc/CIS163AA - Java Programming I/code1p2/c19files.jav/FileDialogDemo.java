import java.io.*;
import java.awt.*;
import java.awt.event.*;

class FileDialogDemo extends Frame 
    implements ActionListener, WindowListener {

    private Button loadButton;
    private FileDialog getNameBox;
    private TextField nameField;

    public static void main (String []  args) {
        FileDialogDemo demo = new FileDialogDemo();
        demo.setSize(500,400);
        demo. makeGui();
        demo.setVisible(true);
    }


    public void makeGui() {
        setLayout( new FlowLayout() );
        loadButton = new Button("load");
        add(loadButton);
        loadButton.addActionListener(this);
        nameField = new TextField(30);
        add(nameField);
        addWindowListener(this);    // for windowClosing
    }
      
    public void actionPerformed(ActionEvent evt) { 
        String fileName;
        if (evt.getSource() == loadButton) {
            getNameBox = new FileDialog(this, "get Name", FileDialog.LOAD);
            getNameBox.show();

            // display the name
            fileName = getNameBox.getFile();
            nameField.setText(fileName);
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

