import java.awt.*;

public class PlayBalloon extends Frame {

    private Button grow, shrink;
    private Balloon myBalloon;

    public static void main(String[] args) {
        PlayBalloon f = new PlayBalloon();
        f.resize(300, 200);
        f.show();
    }

    public  PlayBalloon() {

        setTitle("Balloon");

        setLayout(new FlowLayout());

        grow = new Button("Grow");
        add(grow);

        shrink = new Button("Shrink");
        add(shrink);

        myBalloon = new Balloon(20, 50, 50);
    }

    public boolean action (Event event, Object arg) {
        if (event.target == grow)
            myBalloon.changeSize(10);
        if (event.target == shrink)
            myBalloon.changeSize(-10);
        repaint();
        return true;
    }

    public boolean handleEvent(Event e) {
        if (e.id == Event.WINDOW_DESTROY)
            System.exit(0);
        return super.handleEvent(e);
    }

    public void paint (Graphics g) {
        myBalloon.display(g);
    }
}

class Balloon {

    private int diameter;
    private int xCoord, yCoord;

    Balloon (int initialDiameter, int initialX, int initialY) {
        diameter = initialDiameter;
        xCoord = initialX;
        yCoord = initialY;
    }

    public void changeSize (int change) {
        diameter = diameter+change;
    }

    public void display (Graphics g) {
        g.drawOval (xCoord, yCoord, diameter, diameter);
    }
}

