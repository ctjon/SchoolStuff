import java.awt.*;
import java.applet.Applet;
import java.awt.event.*;

public class Accumulate extends Applet
    implements ActionListener {

    private Button year;
    private TextField interestField, amountField;
    private Invest myMoney;

    public void init() {
        Label amountLabel = new Label("Enter amount:");
        add(amountLabel);

        amountField = new TextField(8);
        add(amountField);
        amountField.addActionListener(this);

        Label ratelabel = new Label("Enter interest rate");
        add(ratelabel);
        
        interestField = new TextField(4);
        add(interestField);
       interestField.addActionListener(this);

        year = new Button ("Another Year");
        add (year);
        year.addActionListener(this);

        myMoney = new Invest();
    }

    public void actionPerformed(ActionEvent event) {
        if (event.getSource() == amountField) {
            float amount = Integer.parseInt(amountField.getText());
            myMoney.setAmount(amount);
        }
        if (event.getSource() == interestField) {
            Float temp = Float.valueOf(interestField.getText());
        float rate = temp.floatValue();
        myMoney.setRate(rate);
    }
    if (event.getSource() == year)
            myMoney.anotherYear();

        repaint();
    }

    public void paint (Graphics g) {
        myMoney.displayInterest(g);
    }
}


class Invest {

    private float interestRate;
    private float oldAmount, newAmount;
    private int dollars, cents;

    public void setAmount(float amount) {
        oldAmount = amount;
    }

    public void setRate(float rate) {
        interestRate = rate;
    }

    public void anotherYear() {
        newAmount = oldAmount + (oldAmount * interestRate / 100.0f);

        dollars = (int)newAmount;
        cents = Math.round(100.0f * (newAmount - dollars));

        oldAmount = newAmount;
    }

    public void displayInterest(Graphics g) {
        g.drawString("Your money at the end of the year is",
            10, 100);
        g.drawString(dollars + " dollars" + cents + " cents",
            10, 120);
    }
}
