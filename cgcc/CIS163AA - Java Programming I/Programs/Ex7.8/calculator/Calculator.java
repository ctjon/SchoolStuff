/*
 * Chris Tjon - Wed 4pm - Ex 7.8 - Calculator Program
 */

package calculator;

import java.applet.*;
import java.awt.*;
import java.awt.event.*;

public class Calculator extends Applet implements ActionListener
{
    private Button one, two, three, four, five, six, seven,
					eight, nine, zero, plus, minus, equals, clear;
    private int input;
    private int total;

    public void init() 
    {
        one = new Button("1");
        add (one);
        one.addActionListener(this);
        
        two = new Button("2");
        add (two);
        two.addActionListener(this);
        
        three = new Button ("3");
        add (three);
        three.addActionListener(this);
        
        four = new Button ("4");
        add (four);
        four.addActionListener(this);
        
        five = new Button ("5");
        add (five);
        five.addActionListener(this);
        
        six = new Button ("6");
        add (six);
        six.addActionListener(this);
        
        seven = new Button ("7");
        add (seven);
        seven.addActionListener(this);
        
        eight = new Button ("8");
        add (eight);
        eight.addActionListener(this);
        
        nine = new Button ("9");
        add (nine);
        nine.addActionListener(this);
        
        zero = new Button ("0");
        add (zero);
        zero.addActionListener(this);
        
        plus = new Button ("+");
        add (plus);
        plus.addActionListener(this);
        
        minus = new Button ("-");
        add (minus);
        minus.addActionListener(this);
        
        equals = new Button ("=");
        add (equals);
        equals.addActionListener(this);
        
        clear = new Button ("Clear");
        add (clear);
        clear.addActionListener(this);
    }

    public void paint(Graphics g) 
    {
            g.drawString ("Input = " + input, 50,130);
            g.drawString ("Total = " + total, 50,150);
    }

    public void actionPerformed(ActionEvent event) {
        if (event.getSource() == one)
            input = (input * 10) + 1;
        
        if (event.getSource() == two)
            input = (input * 10) + 2;
        
        if (event.getSource() == three)
            input = (input * 10) + 3;
        
        if (event.getSource() == four)
            input = (input * 10) + 4;
        
        if (event.getSource() == five)
            input = (input * 10) + 5;
        
        if (event.getSource() == six)
            input = (input * 10) + 6;
        
        if (event.getSource() == seven)
            input = (input * 10) + 7;
        
        if (event.getSource() == eight)
            input = (input * 10) + 8;
        
        if (event.getSource() == nine)
            input = (input * 10) + 9;
        
        if (event.getSource() == zero)
            input = (input * 10) + 0;
        
        if (event.getSource() == plus)
        {
        	total += input;
        	input = 0;
        }
        
        if (event.getSource() == minus)
        {
        	total -= input;
        	input = 0;
        }
        
        if (event.getSource() == equals)
        	input = total;
        
        if (event.getSource() == clear)
        {
            input = 0;
            total = 0;
        }
        
        repaint();
    }
}

