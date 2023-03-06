import java.io.*;
import java.awt.*;
import java.util.*;        // StringTokenizer
import java.awt.event.*;

class FileSearch extends Frame 
    implements ActionListener, WindowListener {

    private BufferedReader inFile;
    private Button searchButton;
    private TextField result1Field;
    private TextField result2Field;
    private TextField personField;
    private TextField fileNameField;
    private TextField errorField;
    private String fileName;

    public static void main (String [ ]  args) {
        FileSearch  search = new FileSearch();
        search.setSize(400,400);
        search.makeGui();
        search.setVisible(true);
    }


    public void makeGui() {
        setLayout(new FlowLayout() );
        errorField= new TextField("Type the File name:");
        errorField.setEditable(false);
        add(errorField);
        fileNameField = new TextField(20);
        fileNameField.setText("");
        add(fileNameField);
        searchButton = new Button("Search");
        add(searchButton);
        searchButton.addActionListener(this);
        add(new Label("Type Name:"));
        personField = new TextField(20);
        personField.setText("");
        add(personField);
        add( new Label("Result1:"));
        result1Field = new TextField(5);
        result1Field.setEditable(false);
        add(result1Field);
        add (new Label("Result2:"));
        result2Field= new TextField(5);
        result2Field.setEditable(false);
        add(result2Field);
        this.addWindowListener(this);
    }


    public void actionPerformed(ActionEvent evt) {
        if (evt.getSource() == searchButton) {
            fileName = fileNameField.getText();
            try {
                inFile = new BufferedReader(
                             new FileReader(fileName));
            }

            catch (IOException e) {
                errorField.setText("Can't find file ");
                return;     /////////////////////note?????????????????????
               }
             errorField.setText("Type the file name:");
            // now read the file
            try {
                String line;
                boolean found = false;
                while (( ( line = inFile.readLine() ) != null)
                      && (! found)) {
                    // tokens split on commas, spaces
                    StringTokenizer tokens = new
                                    StringTokenizer( line, " ,");
                    String nameInFile = tokens.nextToken();
                    if (personField.getText().equals(nameInFile)) {
                        found = true;
                        result1Field.setText(tokens.nextToken() );
                        result2Field.setText(tokens.nextToken() );
                    }
                }
               inFile.close();
            }
            catch (IOException e) {
                System.err.println("Error reading file "+
                                   fileName+": "+e.toString() );
                System.exit(1);
            }
        }
    }

    // WindowListener methods - all needed!
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

