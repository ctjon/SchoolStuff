import java.awt.*;
import java.applet.Applet;
import java.util.*;
import java.awt.event.*;

public class ExceptionDemo1 extends Applet
    implements ActionListener {
    private TextField stringField;
    private TextField resultField;
    private Label resultLabel, stringLabel;
    public void init()  {
        stringLabel = new Label("Type an integer: ");
        resultLabel = new Label("Answer: ");
        stringField = new TextField(20);
        resultField = new TextField(20);
        resultField.setEditable(false);

        add(stringLabel);
        add(stringField);
        stringField.addActionListener(this);
        add(resultLabel);
        add(resultField);
    }

        public void actionPerformed(ActionEvent event) {
        if (event.getSource() == stringField) {
            try{
                int number = Integer.parseInt(stringField.getText());
                resultField.setText("Doubled value is "+(2*number));
            }
            catch (NumberFormatException e) {
                resultField.setText("Error in number: retype ");
            }
        }
   }
}

