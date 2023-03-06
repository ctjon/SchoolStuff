import java.awt.*;
import java.applet.Applet;
import java.awt.event.*;
public class Sales extends Applet 
    implements ActionListener, MouseListener {

   private Table sales;
   private TextField value;

   public void init() {
       sales = new Table(3, 7);
       Label l = new Label("Enter number and click component");
       add(l);
       value = new TextField(8);
       add(value);
       value.addActionListener(this);
       this.addMouseListener(this);
   }

   public void paint(Graphics g) {
       sales.display(g);
   }
   
    public void actionPerformed(ActionEvent event) {
        if (event.getSource() == value) {
            int newValue=Integer.parseInt(value.getText());
            sales.setValue(newValue);
            repaint();
        }
    }
      
    //MouseListener implementation - all 5 methods needed
    public void mouseClicked (MouseEvent event){
        int x = event.getX();
        int y=event.getY();
        sales.selectComponent(x, y);
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

class Table {   //  ============ not like book


    private int[][] data;
    private int rowSubscript;
    private int colSubscript;
    private int newValue;

    private int sum;

    private final int xStart = 20;
    private final int yStart = 60;
    private final int boxHeight = 20;
    private final int boxWidth = 40;

    Table(int rows, int columns) {
        data = new int[rows][columns];

        for(int row = 0; row < rows; row++)
            for(int col = 0; col < columns; col++)
    data[row][col] = 0;
    }

    public void display(Graphics g) {

        for(int row = 0; row < data.length; row++) {
      for(int col = 0; col < data[0].length; col++) {
                int x = xStart + col * boxWidth;
                int y = yStart + row * boxHeight;
                g.drawRect(x, y, boxWidth, boxHeight );
                g.drawString(Integer.toString(data[row][col]),
                             x, y + boxHeight*3/4);
            }
        }
        calculateSum();
        g.drawString("Total is " + sum, 100, 150);
    }

    public void selectComponent( int x, int y) {
        rowSubscript = (y - yStart)/boxHeight;
        colSubscript = (x - xStart)/boxWidth;
        data[rowSubscript][colSubscript] = newValue;
    }

    public void setValue(int value) {
        newValue = value;
    }

     private void calculateSum() {
        sum = 0;
        for (int row=0; row < data.length; row++)
            for (int col = 0; col < data[0].length; col++)
                sum =sum + data[row][col];
    }
}

