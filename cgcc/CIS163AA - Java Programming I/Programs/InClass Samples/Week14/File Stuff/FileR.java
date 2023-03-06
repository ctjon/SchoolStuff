/*Example of Reading from a file*/

import java.io.*; //needed for BufferedReader
import java.util.*; //needed for StringTokenizer

public class FileR
{
	public static void main(String[] s)
	{

		BufferedReader inFile;          //declare the input File
		PrintWriter outFile;

		try
		{  //must check for exception

			//instantiate BufferedReader object inFile and open the file
			inFile = new BufferedReader(new FileReader("FileReader.txt"));
			outFile = new PrintWriter(new FileWriter("FileWriter.txt"));

			String line; //variable to put each line as read

			//use while because don't know how many lines in the file
			//readLine will return null when it can't find anymore data
			while ( (line = inFile.readLine()) != null)
			{

				StringTokenizer tokens = new StringTokenizer(line, ",");
				String name;
				int exam1;
				int exam2;
				int exam3;
				float average;

				name = tokens.nextToken();
				exam1 = Integer.parseInt(tokens.nextToken());
				exam2 = Integer.parseInt(tokens.nextToken());
				exam3 = Integer.parseInt(tokens.nextToken());
				average = (exam1 + exam2 + exam3)/3;

				System.out.println(name + "'s average is " + average);
				outFile.println(name + "'s average is " + average);
			}
			inFile.close();		//close the file
			outFile.close();
		}
		catch(IOException e)
		{
			System.err.println("Error in FileReader.txt " + e.toString() );
			//inFile.close();		//close the file
			//outFile.close();
			System.exit(1); //exits the program
		}
	}

}