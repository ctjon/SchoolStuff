import java.applet.*;
import java.awt.*;
import java.awt.event.*;
public class ButtonCount extends Applet
    implements ActionListener {

    private Button tester;
    private int count = 0;

    public void init(){
        tester = new Button("Press here");
        add (tester);
        tester.addActionListener(this);
    }


    public void paint(Graphics g) {
        g.drawString ("Number of button presses is " + count, 10,50);
    }


    public void actionPerformed(ActionEvent event) {
        if (event.getSource()==tester) {
            count++;
            repaint();
        }
    }
}

