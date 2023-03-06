

//--------------------------------------------------------------------------
import java.io.*;
import java.awt.*;

class FileDialogDemo extends Frame {

    private Button loadButton;
    private FileDialog getNameBox;
    private TextField nameField;

    public static void main (String []  args) {
        FileDialogDemo demo = new FileDialogDemo();
        demo.resize(500,400);
        demo. makeGui();
        demo.show();
    }


    public void makeGui() {
        setLayout( new FlowLayout() );
        loadButton = new Button("load");
        add(loadButton);
        nameField = new TextField(30);
        add(nameField);
    }

    public boolean action(Event evt, Object obj)  {
        String fileName;
        if (evt.target==loadButton) {
            getNameBox = new FileDialog(this, "get Name", FileDialog.LOAD);
            getNameBox.show();

            // display the name
            fileName = getNameBox.getFile();
            nameField.setText(fileName);
       }
       return true;
    }

    public boolean handleEvent(Event event) {
        if (event.id == Event.WINDOW_DESTROY)
            System.exit(0);
        return super.handleEvent(event);
    }

}

