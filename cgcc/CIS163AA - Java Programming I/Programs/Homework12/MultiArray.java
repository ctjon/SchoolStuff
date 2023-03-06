/*
 * CSC110AA/CIS163AA
 * Beginning from what you learned about arrays in
 * the previous lesson, convert StatsArray class into MultiArray
 * to house a 2 dimensional array.
 *
 * Convert the methods appropriately and add a method to
 * display the 2nd column and another method that finds the sum
 * of the 2nd column.
 *
 * I have given you the code for some of the methods.
 *
 * Please add code for the remaining methods.
 * I have put "return 0;" in the incomplete methods so that the code will
 * compile while you are completing each one
 */

import java.awt.*;



public class MultiArray {

	private int x;  //x, y coordinates for displayings array
	private int y;
	private int rowSize;  //number of rows
	private int columnSize; //number of columns
	private int[][]stats; // an array of integers

	//constructor method
	MultiArray(int desiredRowSize,int desiredColumnSize,
				int desiredXCoord,int desiredYCoord) {

		 rowSize = desiredRowSize;
		 columnSize = desiredColumnSize;
		 x = desiredXCoord;
		 y = desiredYCoord;

		//instantiate the 2 dimensional array stats
		 stats = new int[rowSize][columnSize];
	 }

	//default constructor -overloaded method
	//by default the array has 10 rows and 4 columns
	MultiArray() {
		rowSize = 10;
		columnSize = 4;
		x = 75;
		y = 75;
		stats = new int[rowSize][columnSize];
	}


	public void display(Graphics g) {

		//displaying the array
		for(int i = 0; i < stats.length; i++) { //rows
			for (int j = 0; j < stats[0].length; j++) { //columns
				g.drawString("" + stats[i][j], x + j * 25,
									(y + 15 * i)); //quessed on spacing!
			}
		}
	}

	public void fillArray() {
	//produces numbers from 1 to 100
		for(int i = 0; i < stats.length; i++) { //rows
			for (int j = 0; j < stats[0].length; j++) { //columns
			 	stats[i][j] = (int) (Math.random() * 100) + 1;
			}
		}
	}

	public int getSum() {
		//add code to add up the entire array.
		return 0;
	}


	public int getMax() {
			int maxValue = stats[0][0];
			for (int i = 0; i < stats.length; i++){ //rows
				for (int j = 0; j < stats[0].length; j++) { //columns
					if (stats[i][j] > maxValue)
						maxValue = stats[i][j];
				}
			}
			return maxValue;
	}

	public int getMin() {
			//add code to find the minimum value of the array
			return 0;
	}

	public float getAverage() {
			//add code to find the average
			return 0;

	}

	public int count90s() {
		//add code to count how many numbers are >= 90 which is an A

		return 0;
	}


	public char getLucky7() {
		//check to see if a 7 is in the array
		char luckyStatus = 'N';

		for(int i = 0; i < stats.length; i++) { //rows
			for (int j = 0; j < stats[0].length; j++) { //columns
				if (stats[i][j] == 7)
					luckyStatus = 'Y';
			}
		}
		return luckyStatus;
	}

	public void displayColumn(int desiredColumn, Graphics g) {
		//add code display a given column in blue

	}

	public int sumColumn(int desiredColumn, Graphics g) {
			//add code to compute the sum or total of a given column

			return 0;
	}
}