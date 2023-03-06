iimport java.awt.*;

public class WordProcessor extends Frame {


    public static void main(String[] args) {
        Frame f = new WordProcessor();
        f.resize(200, 200);
        f.show();
    }

    public WordProcessor() {

        setTitle("Word Processor");

        setLayout(new FlowLayout());

        MenuBar menuBar = new MenuBar();

        Menu fileMenu = new Menu("File");
        fileMenu.add(new MenuItem("New"));
        fileMenu.add(new MenuItem("Open"));
        fileMenu.add(new MenuItem("Delete"));
        menuBar.add(fileMenu);

        Menu editMenu = new Menu("Edit");
        editMenu.add(new MenuItem("Undo"));
        editMenu.add(new MenuItem("Redo"));
        editMenu.addSeparator();
        editMenu.add(new MenuItem("Cut"));
        editMenu.add(new MenuItem("Copy"));
        editMenu.add(new MenuItem("Paste"));
        menuBar.add(editMenu);

        setMenuBar(menuBar);

    }



    public boolean handleEvent(Event event) {
        if (event.id == Event.WINDOW_DESTROY)
            System.exit(0);
        return super.handleEvent(event);
    }

    public void paint (Graphics g) {
    }
}


