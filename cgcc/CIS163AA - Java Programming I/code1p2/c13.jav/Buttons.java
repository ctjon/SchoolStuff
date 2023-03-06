import java.awt.*;
import java.applet.*;
import java.awt.event.*;
public class Buttons extends Applet
    implements ActionListener {

    private int number;

    public void init() { 
        Button[] digit = new Button[10];
        for (int b=0; b <10; b++) {
            digit[b] = new Button(Integer.toString(b));
            add(digit[b]);
            digit[b].addActionListener(this);
        }
    }

    public void actionPerformed(ActionEvent event) {
        String buttonCaption = event.getActionCommand();
        number = Integer.parseInt(buttonCaption);
        repaint();
    }

    public void paint(Graphics g) {
        g.drawString("Button number is "+ number, 50,100);
    }
}

