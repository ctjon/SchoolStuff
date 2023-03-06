import java.awt.*;
import java.applet.*;
import java.util.*;
import java.awt.event.*;

public class StringDemo extends Applet 
    implements ActionListener {
    private TextField string1Field, string2Field;
    private TextField resultField;
    Label string1Label, string2Label, resultLabel;
    Button goButton;

 public void init()  {
    string1Label = new Label("Type string1: ");
    string2Label = new Label("Type string2: ");
    resultLabel = new Label("result is: ");

    goButton = new Button("do it");

    string1Field = new TextField(20);
    string2Field = new TextField(20);
    resultField = new TextField(40);
    resultField.setEditable(false);

    add(string1Label);
    add(string1Field);
    add(string2Label);
    add(string2Field);
    add(goButton);  
    goButton.addActionListener(this);
    add(resultLabel);
    add(resultField);
}

    public void actionPerformed(ActionEvent event) {
        String result ="";
        if (event.getSource() == goButton) {
            String string1 = string1Field.getText();
            String string2 = string2Field.getText();
            // string example - enter string1 and string2
            //.... insert your code here

            if(string1.equals(string2))
                result="They are equal.";
            else
                result="They are not equal.";

            // end of example
            resultField.setText(result);
        }
   }
}

