/*
 * Chris Tjon
 * CIS163AA Homework Week 9 - Monster 2 Inheritance Problem - Wed 4pm
 * 
 */

import java.awt.*;
import java.applet.Applet;
import java.awt.event.*;

//import monster.Monster;

public class MonsterController extends Applet implements ActionListener{

   	Monster oscar; //declare variable to hold the object you will instantiate
   	Monster elmo;
   	Monster2 fred;
	Button runRightButton;
	Button runLeftButton;
	Button changeEyeColorButton;
	Button angryButton;
	Button resetButton;
	Button puffUpButton;
	boolean angryPressed = false;
	boolean puffUpPressed = false;
	boolean resetPressed = false;
	boolean runRightPressed = false;
	boolean runLeftPressed = false;
	boolean changeEyeColorPressed = false;

   public void init() {
        runRightButton = new Button("Run right");
        add(runRightButton);
        runRightButton.addActionListener(this);

		runLeftButton = new Button("Run left");
		add(runLeftButton);
        runLeftButton.addActionListener(this);

		changeEyeColorButton = new Button("Change Eye Color");
		add(changeEyeColorButton);
        changeEyeColorButton.addActionListener(this);

   		angryButton = new Button("Angry");
   		add(angryButton);
   		angryButton.addActionListener(this);
   		
   		puffUpButton = new Button("Puff Up");
   		add(puffUpButton);
   		puffUpButton.addActionListener(this);
   		
   		resetButton = new Button("Reset");
   		add(resetButton);
   		resetButton.addActionListener(this);
   		
        fred = new Monster2(50, 50, 75);

        /*  new instantiates (creates) the object from your class pattern.
            At the time your object is instantiated, java runs it's
            constructor
            method, passing it the parameters in parentheses. */

        oscar = new Monster(50, 50, 125);
        /*oscar now exists and you can execute his methods,
                   *making him do tricks - such as displaying and growling
                  */
       elmo = new Monster(); //Instantiate another monster using default

    }
    public void paint(Graphics g) {


        elmo.display(g);
		if (runRightPressed)
		{
			oscar.runRight(g);
			runRightPressed = false;
		} 
		else if (runLeftPressed)
		{
			oscar.runLeft(g);
			runLeftPressed = false;
		} 
		else if (changeEyeColorPressed)
		{
			oscar.changeEyeColor(g);
			changeEyeColorPressed = false;
		} 
		else if (angryPressed)
        {        	
        	fred.becomeAngry(g);
        	angryPressed = false;
        	fred.display(g); // displays fred
        }
        else if (puffUpPressed)
        {
        	fred.puffUp(g);
        	puffUpPressed = false;
        	fred.display(g); // displays fred
        }  
        else if (resetPressed)
        {
        	fred.reset(g, 50, 50, 75);
        	resetPressed = false;
        	fred.display(g); // displays fred
        } 
        else 
		{
			oscar.display(g); // displays oscar
			oscar.growl(g); // makes oscar growl
		}
		repaint();
    }

    public void actionPerformed(ActionEvent e) {
		if (e.getSource() == runRightButton)
		{
			runRightPressed = true;
		}
		else if (e.getSource() == runLeftButton)
		{
			runLeftPressed = true;
		}
		else if (e.getSource() == changeEyeColorButton)
		{
			changeEyeColorPressed = true;
		}
		else if (e.getSource() == angryButton)
		{
   			angryPressed = true;
    	}
		else if (e.getSource() == puffUpButton)
		{
   			puffUpPressed = true;
    	}
		else if (e.getSource() == resetButton)
		{
   			resetPressed = true;
		}
		
	}

}

