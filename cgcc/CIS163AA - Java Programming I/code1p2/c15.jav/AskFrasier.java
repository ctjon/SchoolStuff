import java.awt.*;
import java.applet.*;
import java.util.*;
import java.awt.event.*;

public class AskFrasier extends Applet 
    implements ActionListener {

    private TextField questionField;
    private TextField replyField;
    Label questionLabel, psychiatristLabel;
    private Psychiatrist frasier;

    public void init()  {
    questionLabel =  new Label("Type here.... ");
    psychiatristLabel = new Label("Frasier says: ");
    add(questionLabel);

    questionField = new TextField(40);
    add(questionField);
    questionField.addActionListener(this);
    add(psychiatristLabel);
    replyField = new TextField(40);
    replyField.setEditable(false);
    add(replyField);
    replyField.setText("Go  ahead please....");
    frasier = new Psychiatrist();
}

    public void actionPerformed(ActionEvent event) {
        if (event.getSource() == questionField) {
            String itsValue=questionField.getText();
            frasier.putQuestion(itsValue);
            replyField.setText(frasier.getReply() );
        }
   }
}

     class Psychiatrist {
         private String question;
         private String reply;
         Random randomValue = new Random();

         public void putQuestion(String q) {
             question = " "+q+" ";
        }

         public String getReply() {
             int variation =randomValue.nextInt()%3;
             switch (variation) {
                 case 0: reply=transformQuestion(); break;
                 case 1: reply = "Why do you feel that?"; break;
                 case 2: reply = "please be frank!"; break;
             }
           return reply;

        }

        private String transformQuestion() {
            if(question.indexOf(" I ")>=0) {
                String tempReply = replace (question," I ", " you ");
                tempReply = replace(tempReply, " am ", " are ");
                return replace(tempReply, " my "," your ")+"-why?";
            }

            else if(question.indexOf(" no ")>=0)
                return "no? that is  negative!  Please explain....";

            else return "\""+question+"\"-Please re-phrase..";
        }

        private String replace(String original, String from, String to) {

            String leftBit, rightBit;
            int startSearch = 0;
            int place = original.indexOf(from);
            if(from.length()!=0) {

                while (place>=startSearch) {
                    leftBit = original.substring(0, place);
                    rightBit=original.substring(place+from.length(),
                                        original.length());

                    original = leftBit+to+rightBit;
                    startSearch = leftBit.length()+to.length();
                    place = original.indexOf(from);
               }
            }
       return original;
    }
}
   
