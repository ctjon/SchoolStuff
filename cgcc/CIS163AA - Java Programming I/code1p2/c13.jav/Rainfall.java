import java.awt.*;
import java.applet.*;
import java.awt.event.*;
public class Rainfall extends Applet
    implements ActionListener, MouseListener {

    private Table rainData;              
    private TextField value;

    public void init() {
        rainData = new Table();

        Label l = new Label("Enter number and click component");
        add(l);
        value = new TextField(10);
        add(value);
        value.addActionListener(this);
        this.addMouseListener(this);
    }

    public void paint(Graphics g) {
        rainData.display(g);
    }

    public void actionPerformed(ActionEvent event) {
        if (event.getSource() == value) {
            int newValue=Integer.parseInt(value.getText());
            rainData.setValue(newValue);
            repaint();
        }
    }

    //MouseListener implementation - all 5 methods needed
    public void mouseClicked (MouseEvent event){
        int y=event.getY();
        rainData.selectComponent(y);
        repaint();
    }    
      
      
    public void mouseReleased (MouseEvent e){
    }
    
    public void mousePressed (MouseEvent e){ 
    }
      
    public void mouseEntered (MouseEvent e){
    }
        
    public void mouseExited (MouseEvent e){
    }
   
}


class Table {      // code  is not like book!!  *******************

private int[] rain = new int[7];
private int subscript;
private int newValue;
private int sum = 0;

private final int startX = 20;
private final int startY = 60;
private final int boxHeight = 20;
private final int boxWidth = 60;

    public void display(Graphics g) {
    int y = startY;
    for(int s = 0; s < rain.length; s++) {
        g.drawRect(startX, y, boxWidth, boxHeight);
        g.drawString(Integer.toString(rain[s]),
                     startX, y + boxHeight*3/4);
        y=y+boxHeight;
    }
    add();
    g.drawString("Total rainfall is " + sum, 100, 100);
    }

    public void selectComponent(int y) {
    subscript = (y - startY)/boxHeight;
    rain[subscript] = newValue;
    }

    public void setValue(int value) {
    newValue = value;
    }

    private void add() {
    sum = 0;
    for (int s=0; s < rain.length; s++)
        sum = sum + rain[s];
    }
}

