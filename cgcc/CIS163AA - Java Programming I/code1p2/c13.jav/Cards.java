import java.applet.Applet;
import java.awt.*;
import java.awt.event.*;
public class Cards extends Applet
    implements ActionListener {

    boolean showIt = false;
    private Button show;
    private Deck hand = new Deck();

    public void init() {
        show = new Button("Show");
        add(show);
        show.addActionListener(this);
}

    public void actionPerformed(ActionEvent event) {
        if (event.getSource() == show)
            showIt = true;

        repaint();
    }

    public void paint(Graphics g) {
        if (showIt) hand.display(g);
    }
}




 class Deck {

    private Card[] deck = new Card[52];
    final String[] suit = {"hearts", "diamonds", "spades", "clubs"};

    public Deck() {
        int cardNumber = 0;
        for (int suitNo = 0; suitNo < 4; suitNo++)
            for (int rank = 1; rank < 14; rank++) {
                deck[cardNumber] = new Card();
                deck[cardNumber].suit = suit[suitNo];
                deck[cardNumber].rank = rank;
                cardNumber++;
            }
    }

    public void display(Graphics g) {
        int x = 15, y = 15;
        for(int card = 0; card < 52; card++) {
            deck[card].display(g, x, y);
            y = y + 15;
        }
    }
}

class Card {
    public int rank;
    public String suit;

    public void display(Graphics g, int x, int y) {
        g.drawString("rank is " + rank, x, y);
        g.drawString("suit is " + suit, x + 60, y);
    }

}

