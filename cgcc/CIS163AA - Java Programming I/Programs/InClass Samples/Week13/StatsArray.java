/*
 * CSC110AA
 *
 * Don't need the other import statements or the extends Applet
 * Those statements are in the Controller
 */
import java.awt.*;




public class StatsArray {

	private int x;  //x, y coordinates for displayings array
	private int y;
	private int size;  //how big is the array
	private int[] stats; // an array of integers

	//constructor method
	StatsArray(int desiredSize, int desiredXCoord,
				int desiredYCoord) {

		 size = desiredSize;
		 x = desiredXCoord;
		 y = desiredYCoord;

		 stats = new int[size]; //instantiate the array stats
	 }

	//default constructor -overloaded method
	StatsArray() {
		size = 10;
		x = 75;
		y = 75;
		stats = new int[size];
	}


	public void display(Graphics g) {

		//displaying the array
		for(int i = 0; i < stats.length; i++) {
			g.drawString("Stats [" + i + "] = "+ stats[i], x,
				(y + 15 * i));
		}
	}

	public void fillArray() {

		for(int i = 0; i < stats.length; i++) {
			stats[i] = (int) (Math.random() * 100) + 1;
		}
	}

	public int getSum() {
		int total = 0;
		for (int s = 0; s < stats.length; s++)
			total = total + stats[s];
		return total;
	}


	public int getMax() {
			int maxValue = stats[0];
			for (int s = 0; s < stats.length; s++){
				if (stats[s] > maxValue)
					maxValue = stats[s];
			}
			return maxValue;
	}

	public int getMin() {
			int minValue = stats[0];
			for (int s = 0; s < stats.length; s++){
				if (stats[s] < minValue)
					minValue = stats[s];
			}
			return minValue;
	}

	public float getMean() {
			int total = 0;
			float average = 0f;
			for (int s = 0; s < stats.length; s++)
				total = total + stats[s];
			average = (float) (total) / stats.length;
			return average;
	}

	public char getLucky7() {
		//check to see if a 7 is in the array
		char luckyStatus = 'N';

		for(int i = 0; i < stats.length; i++) {
			if (stats[i] == 7) {
				luckyStatus = 'Y';
			}
		}
		return luckyStatus;
	}


}