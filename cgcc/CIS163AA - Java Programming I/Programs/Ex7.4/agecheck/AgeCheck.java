/*
 * Chris Tjon, Ex 7.4 Wed 4pm
 */
package agecheck;

import java.applet.*;
import java.awt.*;
import java.awt.event.*;

public class AgeCheck extends Applet implements AdjustmentListener {

    private Scrollbar ageBar;
    private int age;

    public void init() {
        Label ageLabel = new Label ("Age:");
        add(ageLabel);
        ageBar = new Scrollbar(Scrollbar.HORIZONTAL, 0, 1, 0, 100);
        add(ageBar);
        ageBar.addAdjustmentListener(this);
    }

    public void adjustmentValueChanged(AdjustmentEvent e)
    {
    	age = ageBar.getValue();
    	repaint();
    }

    public void paint (Graphics g)
    {
        g.drawString("Age is " + age, 50, 50);
        if (age < 5)
            g.drawString("Free", 50, 100);
        else if (age < 13)
            g.drawString("Half Price", 50,100);
        else if (age < 55)
            g.drawString("Full Price", 50,100);
        else if (age > 54)
            g.drawString("Free", 50,100);
    }

}
