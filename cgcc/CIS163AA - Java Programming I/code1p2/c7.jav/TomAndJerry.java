// 1.1 basic version, no buttons
import java.awt.*;
import java.applet.Applet;
import java.awt.event.*;     //mp

public class TomAndJerry extends Applet 
               implements AdjustmentListener {   //mp

    private Scrollbar tom, jerry;
    private int tomValue = 0, jerryValue = 0;

    public void init() {
        Label toms = new Label ("Tom:");
        add(toms);
        tom = new Scrollbar(Scrollbar.HORIZONTAL, 0, 1, 0, 100);
        add(tom);
        tom.addAdjustmentListener( this);


        Label jerrys = new Label ("Jerry:");
        add(jerrys);
        jerry = new Scrollbar(Scrollbar.HORIZONTAL, 0, 1, 0, 100);
        add(jerry);
        jerry.addAdjustmentListener( this);    //mp


    }

    public void paint(Graphics g) {
        g.drawString("Tom", 5, 70);
        g.fillRect(40, 60, tomValue, 10);
        g.drawString("Jerry", 5, 85);
        g.fillRect(40, 75, jerryValue, 10);

        if (tomValue > jerryValue) 
            g.drawString ("Tom is bigger  ", 50, 50);
        else
            g.drawString ("Jerry is bigger", 50, 50);
    }

 /***   public boolean handleEvent(Event e) {
        tomValue = tom.getValue();
        jerryValue = jerry.getValue();
        repaint();
        return true;
    }    *** handleevent deleted   mp   **/

/*** new event code   *****/
// Hmmmm..  how do I know which scrollbar was used?
//   I dont need to know for THISD prgram, but I do in general...

//  do I use getSource?  within each type of event?

}

