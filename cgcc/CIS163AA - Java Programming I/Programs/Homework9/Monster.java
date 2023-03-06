/*use this Base Monster Class in your inheritance assignment*/

import java.awt.* ;// awt needed because monster must display self

public class Monster {  //Monster is the Class name, taken from

		protected int x;
		protected int y;
		protected int size; //in pixels
		protected Color eyeColor;  //data type of color variable is the Color class.
		protected Color bodyColor;

		//Constructor Methods

		Monster(int desiredXCoord, int desiredYCoord, int desiredSize) {
		    x = desiredXCoord;
		    y = desiredYCoord;
		    size = desiredSize;
		    eyeColor = Color.red;  //I decided not to allow the user to set the colors
		    bodyColor = Color.black;
		}

		//Overloaded constructor, default constructor
		Monster() {
			x = 30;
			y = 200;
			size = 50;
			eyeColor = Color.red;
			bodyColor = Color.black;
		}

		public void display(Graphics g) {
		    // BODY
		    g.setColor(bodyColor);
		    int monsterWidth = size;
		    int monsterHeight = size * 2 / 3;
		    g.fillOval(x, y, monsterWidth, monsterHeight);

		    // EYES
		    g.setColor(eyeColor);
		    int eyeWidth = monsterWidth / 10;
		    int eyeHeight = eyeWidth * 2 / 3;
		    int eye1X = x + monsterWidth / 6;
		    int eye1Y = y + monsterHeight / 3;
		    g.fillOval( eye1X, eye1Y, eyeWidth, eyeHeight );
		    int eye2X = eye1X + monsterWidth / 2;
		    int eye2Y = eye1Y;
		    g.fillOval( eye2X, eye2Y, eyeWidth, eyeHeight );
		}


		public void runRight(Graphics g) {
			x += 20;
			display(g);
		}

		public void runLeft(Graphics g) {
			x -= 20;
			display(g);
		}

		public void growl(Graphics g) {
			g.setColor(Color.blue);
			g.drawString("Grrrrrr", x, y - 15);
		}

		public void changeEyeColor(Graphics g) {
			//colors are a combination of red, green, and blue
			int iRed = (int)(Math.random() * 200);
			int iGreen = (int)(Math.random() * 200);
			int iBlue = (int)(Math.random() * 200);

			//instantiate the object newEyeColor
			Color newEyeColor = new Color(iRed, iGreen, iBlue);

			eyeColor = newEyeColor;

			display(g);

		}



}