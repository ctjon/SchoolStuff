/*This is the class definition for Artist
* Use with ArrayList lecture
*
* Controller is called HitList.java
* HitList creates an ArrayList of Artist objects
*/

import java.awt.*;

class Artist {

    private int height = 25, width = 75;
    private String name;

    public Artist(String name) {
        this.name = name;
    }

    public void display(Graphics g, int x, int y, boolean selected) {
        if (selected) {
            g.setColor(Color.lightGray);
            g.fillRect(x, y, width, height);
            g.setColor(Color.black);
        }
        else
            g.drawRect(x, y, width, height);
        g.drawString(name, x + 5, y + 20);
    }
}