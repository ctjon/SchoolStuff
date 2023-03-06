import java.applet.*;
import java.awt.*;
import java.awt.event.*;
public class Safe extends Applet 
    implements ActionListener {

    private int guess = 0;
    private int combination = 321;
    private Button one, two, three, again;

    public void init() {
        one = new Button("1");
        add (one);
        one.addActionListener(this);
        two = new Button("2");
        add (two);
        two.addActionListener(this);
        three = new Button ("3");
        add (three);
        three.addActionListener(this);
        again = new Button("Try Again");
        add(again);
        again.addActionListener(this);
    }

    public void paint(Graphics g) {
        if (guess==combination)
            g.drawString ("Unlocked", 50,50);
        else
            g.drawString ("Locked", 50,50);
    }

    public void actionPerformed(ActionEvent event) {
        if (event.getSource() == one)
            guess = guess*10 + 1;
        if (event.getSource() == two)
            guess = guess*10 + 2;
        if (event.getSource() == three)
            guess = guess*10 + 3;
        if (event.getSource() == again)
            guess=0;

        repaint();
    }
}

