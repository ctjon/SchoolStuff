import java.applet.*;
import java.awt.*;
import java.awt.event.*;
public class ButtonOuch extends Applet
    implements ActionListener {

    private Button tester;
    private boolean clickedYet = false;

    public void init() {
        tester = new Button("Press here");
        add (tester);
        tester.addActionListener(this);
    }


    public void paint(Graphics g) {
        if(clickedYet)
            g.drawString ("OUCH", 100,50);
    }


    public void actionPerformed(ActionEvent event) {
        if (event.getSource() == tester) {
            clickedYet = true;
            repaint();
        }
    }
}
