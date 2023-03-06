import java.awt.*;
import java.applet.*;

public class Bars extends Applet {

    int[] data = {12, 30, 45, 5, 60, 20, 10};

    public void paint(Graphics g)
    {
        displayBars(data, g);
    }

public void displayBars( int[] data, Graphics g) {
int largest;
int[] scaledData = new int[data.length];

int yHeight = 200;
int yStart = 20;
int width = 30;
int gap = 10;
int xStart = 20;

largest = findLargest(data);
scaledData = scaleValues(data, largest, yHeight);

int x = xStart;
for (int count = 0; count < scaledData.length; count++) {
    g.fillRect(x, yStart + yHeight - scaledData[count],
               width, scaledData[count]);
    x = x + width + gap;
}
}

private int findLargest( int[] data) {
    int largest = data[0];
    for (int count = 0; count < data.length; count++)
    {
        if (data[count] > largest)
            largest = data[count];
    }
return largest;
}

private int[] scaleValues(int[] data, int largest, int yHeight)
{
    int[] newArray = new int[data.length];
    for (int count = 0; count < data.length; count++) {
        newArray[count] = data[count]*yHeight/largest;
    }
return newArray;
}


}
