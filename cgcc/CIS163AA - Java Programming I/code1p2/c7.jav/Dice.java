import java.awt.*;
import java.applet.Applet;
import java.awt.event.*;
public class Dice extends Applet
    implements ActionListener {

    private Button throwDice;
    private boolean thrown = false;

    public void init() {
        throwDice = new Button("Throw");
        add (throwDice);
        throwDice.addActionListener(this);
    }

        public void actionPerformed(ActionEvent event) {
        if (event.getSource() == throwDice) {
            thrown = true;
            repaint();
        }
}

    public void paint(Graphics g) {
        int die1, die2;
        if(thrown) {
            die1 = (int)(Math.random() * 6)+1;
            die2 = (int)(Math.random() * 6)+1;
            g.drawString("The dice are " + die1 + " and " + die2, 20, 40);
            if (die1 == die2)
                g.drawString ("a win", 20, 60);
            else
                g.drawString ("sorry" , 20, 60);
        }
    }
}
