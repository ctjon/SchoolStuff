import java.applet.Applet;
import java.awt.*;
import java.awt.event.*;
public class Balloons extends Applet
    implements ActionListener {

    private Button twice, shrink, down, random;

    private Balloon[] party = new Balloon[10];


    public void init() {
        twice = new Button("double");
        add(twice);
        twice.addActionListener(this);
        shrink = new Button("Shrink");
        add(shrink);
        shrink.addActionListener(this);
        down = new Button("down");
        add(down);
        down.addActionListener(this);
        random = new Button("random");
        add(random);
        random.addActionListener(this);

        for (int b = 0; b < 10; b++)
            party[b] = new Balloon();

    }
    public void actionPerformed(ActionEvent event) {
        if (event.getSource() == twice)
            for (int b = 0; b < 10; b++)
                party[b].changeSize(2.0f);

        if (event.getSource() == shrink)
           for (int b = 0; b < 10; b++)
               party[b].changeSize(b/10.0f);

        if (event.getSource() == down)
            for (int b = 0; b < 10; b++)
                party[b].changeY(10);

        if (event.getSource() == random) {
            for (int b = 0; b < 10; b++) {
                int x = (int)(Math.random() * 100);
                int y = (int)(Math.random() * 100);
                int radius = (int)(Math.random() * 50);
                party[b] = new Balloon(x, y, radius);
            }
        }

        repaint();
    }

    public void paint(Graphics g) {
       for (int b = 0; b < 10; b++)
          party[b].display(g);

    }
}

class Balloon {

    private int x; // x pixel co-ordinate of centre
    private int y; // y pixel co-ordinate of centre
    private int radius;

    public Balloon () {
        x = 50;
        y = 50;
        radius = 20;
    }

    public Balloon(int x, int y, int radius) {
        this.x = x;
        this.y = y;
        this.radius = radius;
    }


    public void display(Graphics g) {
        g.drawOval(x-radius, y-radius, radius*2, radius*2);
    }

    public void changeSize(float factor) {
        radius = (int) (radius * factor);
    }

    public void changeY(int y) {
        this.y = this.y + y;
    }

}
