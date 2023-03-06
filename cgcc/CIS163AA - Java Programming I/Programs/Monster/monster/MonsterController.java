/*
 * Chris Tjon, Monster Controller, Wed 4pm
 */
package monster;

import java.awt.*;
import java.applet.Applet;
import java.awt.event.*;

public class MonsterController extends Applet implements ActionListener
{
   
   Monster fred; //declare an identifier to hold the object you will instantiate
   
   Button runButton;
   Button angryButton;
   Button growlButton;
   Button resetButton;
   Button jumpButton;
   Button puffUpButton;
   boolean runPressed = false;
   boolean angryPressed = false;
   boolean growlPressed = false;
   boolean jumpPressed = false;
   boolean puffUpPressed = false;
   boolean resetPressed = false;
   
   public void init() {
        /*  new instantiates (creates) the object from your class pattern.
            At the time your object is instantiated, java runs it's 
            constructor
            method, passing it the parameters in parentheses. */
   		runButton = new Button("Run");
   		add(runButton);
   		runButton.addActionListener(this);

   		angryButton = new Button("Angry");
   		add(angryButton);
   		angryButton.addActionListener(this);
   		
   		growlButton = new Button("Growl");
   		add(growlButton);
   		growlButton.addActionListener(this);
   		
   		jumpButton = new Button("Jump");
   		add(jumpButton);
   		jumpButton.addActionListener(this);
   		
   		puffUpButton = new Button("Puff Up");
   		add(puffUpButton);
   		puffUpButton.addActionListener(this);
   		
   		resetButton = new Button("Reset");
   		add(resetButton);
   		resetButton.addActionListener(this);
   		
        fred = new Monster(50, 50, 75);
        /*fred now exists and you can execute his methods, 
               *making him do tricks - such as displaying and growling 
        */
    }
   
   	public void actionPerformed(ActionEvent event) 
   	{
   		if (event.getSource() == runButton)
   			runPressed = true;
   		if (event.getSource() == angryButton)
   			angryPressed = true;
   		if (event.getSource() == growlButton)
   			growlPressed = true;
   		if (event.getSource() == jumpButton)
   			jumpPressed = true;
   		if (event.getSource() == puffUpButton)
   			puffUpPressed = true;
   		if (event.getSource() == resetButton)
   			resetPressed = true;
   		repaint();
   	}
   	
    public void paint(Graphics g) {
        
        if (runPressed)
        {
        	fred.run(20);
        	runPressed = false;
        }
        
        if (angryPressed)
        {        	
        	fred.becomeAngry(g);
        	angryPressed = false;
        }
        
        if (growlPressed)
        {
        	fred.growl(g);
        	growlPressed = false;
        } 
        
        if (jumpPressed)
        {
        	fred.jump(g);
        	jumpPressed = false;
        } 
        
        if (puffUpPressed)
        {
        	fred.puffUp(g);
        	puffUpPressed = false;
        }  
        
        if (resetPressed)
        {
        	fred.reset(g, 50, 50, 75);
        	resetPressed = false;
        } 
        fred.display(g); // displays fred
    }
}
