/*
 * Chris Tjon - Wed 4pm
 * CSC110AA/CIS163AA
 * An Integer Array
 *
 */

import java.awt.*;



public class StatsArray {

    //instance variables
	private int x;  //x, y coordinates for displaying array
	private int y;
	private int size;  //how big is the array
	private int[] stats; // declare array of integers called stats


	//constructor method
	public StatsArray(int desiredSize, int desiredXCoord, int desiredYCoord)
	{
		size = desiredSize;
		x = desiredXCoord;
		y = desiredYCoord;
		stats = new int[size];
	}


	public StatsArray()
	{
		//default constructor -overloaded method
		size = 10;
		x = 75;
		y = 75;
		stats = new int[size];
	}


	public void display(Graphics g)
	{
		//display the array with position number
		for (int i = 0; i < stats.length; i++)
		{
			g.drawString("stats[" + i + "] = " + stats[i], x, (y + (15 * i)));
		}
	}


	public void fillArray()
	{
		//fill the array with random numbers (int) in the range 0 - 100
		for (int i = 0; i < stats.length; i++)
		{
			stats[i]= (int)(Math.random() * 101);
		}
	}


	public int getSum()
	{
		//add up all the values in the array
		int sum = 0;

		for (int i = 0; i < stats.length; i++)
		{
			sum += stats[i];
		}
		return(sum);
	}


	public int getMax()
	{
		//return the maximum value in the array
		int max = stats[0];

		for (int i = 1; i < stats.length; i++)
		{
			if (stats[i] > max)
				max = stats[i];
		}
		return(max);
	}


	public int getMin()
	{
		//return the minimum value in the array
		int min = stats[0];

		for (int i = 1; i < stats.length; i++)
		{
			if (stats[i] < min)
				min = stats[i];
		}
		return(min);
	}


	public float getAverage()
	{
		//return the average
		int sum = 0, count = 0;
		float avg;

		for (int i = 0; i < stats.length; i++)
		{
			sum += stats[i];
			count++;
		}
		avg = (float)sum/(float)count;
		return(avg);
	}


	public int count90s()
	{
		//count how many numbers are >= 90 which is an A
		int count = 0;

		for (int i = 1; i < stats.length; i++)
		{
			if (stats[i] < 100 && stats[i] >= 90)
				count++;
		}
		return(count);
	}


	public char getLucky7()
	{
		//check to see if a 7 is in the array

		for (int i = 1; i < stats.length; i++)
		{
			if (stats[i] == 7)
				return('y');
		}
		return('n');
	}


	public void sortArray() {
		/*sort the array in ascending order*/

		int tempValue;

		for (int i = 0; i < (stats.length - 1); i++)
		{
			for (int j = (i + 1); j < (stats.length); j++)
			{
				if (stats[j] < stats[i])
				{
					tempValue = stats[i];
					stats[i] = stats[j];
					stats[j] = tempValue;
				}
			}
		}
	}





}