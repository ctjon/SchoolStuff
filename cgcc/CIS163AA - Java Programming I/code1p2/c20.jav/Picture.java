import java.awt.*;
import java.applet.Applet;
 
public class Picture extends Applet {
    Image image;

    public void init() {
        image=getImage(getDocumentBase(), "picture.gif");
    }

    public void paint (Graphics g) {
        boolean b = g.drawImage(image, 20, 20, 200, 200, this);
    }
}

