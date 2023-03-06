import java.awt.*;
import java.awt.event.*;

public class MenuBalloon extends Frame 
    implements WindowListener, ActionListener {

    private Balloon myBalloon;
    private MenuItem growItem, shrinkItem;
    private MenuItem leftItem, rightItem;

    public static void main(String[] args) {
        Frame f = new MenuBalloon();
        f.setSize(200, 200);
        f.setVisible(true);
    }

    public MenuBalloon() {
        setTitle("Balloon");
        setLayout(new FlowLayout());

        MenuBar menuBar = new MenuBar();

        Menu sizeMenu = new Menu("Size");

        growItem = new MenuItem("Grow");
        sizeMenu.add(growItem);
        growItem.addActionListener(this);

        shrinkItem = new MenuItem("Shrink");
        sizeMenu.add(shrinkItem);
        shrinkItem.addActionListener(this);

        menuBar.add(sizeMenu);
        Menu moveMenu = new Menu("Move");

        leftItem = new MenuItem("Left");
        moveMenu.add(leftItem);
        leftItem.addActionListener(this);

        moveMenu.addSeparator();

        rightItem = new MenuItem("Right");
        moveMenu.add(rightItem);
        rightItem.addActionListener(this);

        menuBar.add(moveMenu);
        setMenuBar(menuBar);
        addWindowListener(this);

        myBalloon = new Balloon(20, 50, 50);
    }

    public void actionPerformed(ActionEvent event)  {
        if (event.getSource() == growItem)
            myBalloon.changeSize(10);
        if (event.getSource() == shrinkItem)
            myBalloon.changeSize(-10);
 //     if(event.getSource() == leftItem)
 //         myBalloon.moveLeft();
 //     if(event.getSource() == rightItem)
 //         myBalloon.moveRight();
         repaint();
    }

   

    public void paint (Graphics g) {
        myBalloon.display(g);
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


class Balloon {

    private int diameter;
    private int xCoord, yCoord;

    Balloon (int initialDiameter, int initialX, int initialY) {
        diameter = initialDiameter;
        xCoord = initialX;
        yCoord = initialY;
    }

    public void changeSize (int change) {
        diameter = diameter+change;
    }

    public void display (Graphics g) {
        g.drawOval (xCoord, yCoord, diameter, diameter);
    }
}


