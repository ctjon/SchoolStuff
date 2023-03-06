import java.awt.*;
import java.applet.Applet;
import java.awt.event.*;

public class GraphDraw extends Applet
    implements AdjustmentListener {

    private Graph myGraph;
    private Scrollbar aScrollbar, bScrollbar, cScrollbar, dScrollbar;

    public void init() {
        myGraph = new Graph();

        Label aLabel = new Label("a:");
        add(aLabel);
        aScrollbar = new Scrollbar(Scrollbar.HORIZONTAL,
            50, 10, 0, 100);
        add(aScrollbar);
        aScrollbar.addAdjustmentListener( this); 
        Label bLabel = new Label("b:");
        add(bLabel);
        bScrollbar = new Scrollbar(Scrollbar.HORIZONTAL,
            50, 10, 0, 100);
        add(bScrollbar);
        bScrollbar.addAdjustmentListener( this);
        Label cLabel = new Label("c:");
        add(cLabel);
        cScrollbar = new Scrollbar(Scrollbar.HORIZONTAL,
            50, 10, 0, 100);
        add(cScrollbar);
        cScrollbar.addAdjustmentListener( this); 
        Label dLabel = new Label("d:");
        add(dLabel);
        dScrollbar = new Scrollbar(Scrollbar.HORIZONTAL,
            50, 10, 0, 100);
        add(dScrollbar);
        dScrollbar.addAdjustmentListener( this);
    }
    public void adjustmentValueChanged(AdjustmentEvent e) {
        int aValue = aScrollbar.getValue();
        int bValue = bScrollbar.getValue();
        int cValue = cScrollbar.getValue();
        int dValue = dScrollbar.getValue();
        myGraph.setParameters(aValue, bValue, cValue, dValue);
        repaint();
    }

    public void paint(Graphics g) {
        myGraph.draw(g);
    }
}

class Graph {

    private final int xPixelStart = 10, xPixelEnd = 410, xOrigin = 215;
    private final int yPixelStart = 10, yPixelEnd = 410, yOrigin = 215;
    private final float xStart = -5.0f, xEnd = 5.0f;
    private final float yStart = -5.0f, yEnd = 5.0f;
        private final float scale = (xPixelEnd - xPixelStart) / (xEnd - xStart);

        private float a, b, c, d;

        private float theFunction(float x, float a,
                float b, float c, float d) {
            return a*x*x*x + b*x*x + c*x+d;
        }

        private float scaleX(int xPixel) {
            float value = (xPixel - xOrigin) / scale;
            return value;
        }

        private int scaleY(float y) {
            int pixelCoord;
            pixelCoord = Math.round(-y * scale) + yOrigin;
            return pixelCoord;
        }

        public void setParameters(
            int aValue, int bValue, int cValue, int dValue) {
            a = scale(aValue);
            b = scale(bValue);
            c = scale(cValue);
            d = scale(dValue);
        }

        private float scale(int coefficient) {
            return ((coefficient - 50) / 10.0f);
        }

        public void draw(Graphics g) {
            float x, y, nextX, nextY;
            int xPixel, yPixel, nextXPixel, nextYPixel;

            g.drawString("a= "+a+" b= "+b+" c= "+c+" d= "+d, 30, 60);

            for(xPixel = xPixelStart; xPixel < xPixelEnd; xPixel++) {
                x = scaleX(xPixel);
                y = theFunction(x, a, b, c, d);
                yPixel = scaleY(y);
            nextXPixel = xPixel + 1;

            nextX = scaleX(nextXPixel);
            nextY = theFunction(nextX, a, b, c, d);
            nextYPixel = scaleY(nextY);

            g.drawLine(xPixel, yPixel, nextXPixel, nextYPixel);
        }
    }
}

