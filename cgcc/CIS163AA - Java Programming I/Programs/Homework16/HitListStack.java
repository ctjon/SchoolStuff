/*
 * Chris Tjon - HitListStack, wed 4pm
 */

import java.applet.Applet;
import java.awt.*;
import java.awt.event.*;
import java.util.*;

//This is the controller for an ArrayList of Artist objects

public class HitListStack extends Applet implements ActionListener, MouseListener
{

    private ArrayList artists = new ArrayList(); //create
    private String text;
    private boolean itemSelected = false;
    private int indexSelected = -1;
    private Button push, pop, test;
    private TextField textField;
    private Artist artist;  //object artist is type class Artist
    private int stepSize = 40;
    private int startY = 60;

    public void init()
    {
        push = new Button("Push");
        add(push);
        push.addActionListener(this);
        pop = new Button("Pop");
        add(pop);
        pop.addActionListener(this);
    	test = new Button("Test");
		add(test);
		test.addActionListener(this);
        textField = new TextField("", 10);
        add(textField);
        addMouseListener(this);

        artist = new Artist("Elvis"); //instantiate artist
        boolean result =artists.add(artist); //adds the first item in the list
    }

    public void actionPerformed(ActionEvent event)
    {
        text = textField.getText();
        if (event.getSource() == push)
            push();
        if (event.getSource() == pop)
            pop();
        if (event.getSource() == test)
        	test();
        itemSelected = false;
        repaint();
    }

    public void mouseClicked(MouseEvent event)
    {
        int yCoord = event.getY();
        indexSelected = (yCoord - startY) / stepSize;
        itemSelected = true;
        repaint();
    }

    public void mouseReleased(MouseEvent mouse)
    {
    }

    public void mousePressed(MouseEvent mouse)
    {
    }

    public void mouseEntered(MouseEvent mouse)
    {
    }

    public void mouseExited(MouseEvent mouse)
    {
    }

    private void push()
    {
        artist = new Artist(text);
        artists.add(0,artist); //pushes an item on the top of the stack
    }

    private void pop()
    {
        artists.remove(0); //pops the item on the top of the stack
    }

    private void test()
    {
			if (artists.isEmpty())
				textField.setText("empty");
			else
				textField.setText(""+artists.size());
    }

    public void paint(Graphics g) //displays the stack
    {
        for (int i = 0; i < artists.size(); i++)
        {
        	/* extracts an element.  In ArrayLists info is held as
        	 * instances of the superclass Object.  So to convert back
        	 * to an Artist object by casting with (Artist)
        	 */

        	artist = (Artist) artists.get(i);
            int x = 20;
            int y = stepSize * i + startY;
            if (i == indexSelected && itemSelected)
                artist.display(g, x, y, true);
            else
                artist.display(g, x, y, false);
        }
    }
}