/*
 * Chris Tjon - Wed 4pm - Ex 7.2 - Card Dealer
 */
package dealer;

import java.awt.*;
import java.applet.Applet;
import java.awt.event.*; 

public class Dealer extends Applet implements ActionListener
{
    private Button dealButton;
    private String card;
    private String suit; // Spades, Diamonds, Hearts, Clubs
    private String value; // A,2,3,4,5,6,7,8,9,10,J,Q,K
   
    public void init ()
    {
        dealButton = new Button("Deal");
        add(dealButton);
        dealButton.addActionListener(this);     
    }

    public void paint (Graphics g)
    {
    	if ((value != null) && (suit != null))
    		showStatus("Your Card is " + value + " of " + suit);
    }

    public void actionPerformed(ActionEvent event)
    {
    	int suitNum = (int)((Math.random() * 4) + 1);
    	int valueNum = (int)((Math.random() * 13) + 1);
        
    	switch (suitNum)
		{
    		case 1: suit = "Hearts"; break;
    		case 2: suit = "Diamonds"; break;
    		case 3: suit = "Spades"; break;
    		case 4: suit = "Clubs"; break;
    	}
    	
    	switch (valueNum)
		{
    		case 1: value = "Ace"; break;
    		case 2: value = "2"; break;
    		case 3: value = "3"; break;
    		case 4: value = "4"; break;
    		case 5: value = "5"; break;
    		case 6: value = "6"; break;
    		case 7: value = "7"; break;
    		case 8: value = "8"; break;
    		case 9: value = "9"; break;
    		case 10: value = "10"; break;
    		case 11: value = "Jack"; break;
    		case 12: value = "Queen"; break;
    		case 13: value = "King"; break;
    	}
        repaint();
    }
}