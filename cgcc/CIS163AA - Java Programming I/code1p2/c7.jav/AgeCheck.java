import java.applet.*;
import java.awt.*;
import java.awt.event.*;
public class AgeCheck extends Applet
    implements ActionListener {

    private TextField ageField;
    private int age;

    public void init() {
        ageField=new TextField(10);
        add(ageField);
        ageField.addActionListener(this);
    }

    public void actionPerformed(ActionEvent event) {
        if (event.getSource()==ageField)
            age=Integer.parseInt(ageField.getText());
        repaint();
    }

    public void paint (Graphics g) {
        g.drawString("Age is " + age, 50, 50);
        if (age >= 18)
            g.drawString("You can vote", 50, 100);
        else
            g.drawString("You cannot vote", 50,100);
    }

}
