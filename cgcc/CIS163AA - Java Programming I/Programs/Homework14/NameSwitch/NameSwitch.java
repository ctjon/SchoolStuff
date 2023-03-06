/*
 * NameSwitch.java (Parts 1 & 2)
 * Chris Tjon, Wed 4pm
 *
 */

import java.io.*;
import java.util.*;

public class NameSwitch
{
	public static void main(String[] s)
	{

		BufferedReader inFile;
		PrintWriter outFile;

		try
		{
			inFile = new BufferedReader(new FileReader("names.txt"));
			outFile = new PrintWriter(new FileWriter("names-output.txt"));

			String line;

			while ( (line = inFile.readLine()) != null)
			{

				StringTokenizer tokens = new StringTokenizer(line, ",");
				String firstName;
				String lastName;

				firstName = tokens.nextToken();
				lastName = tokens.nextToken();

				System.out.println(lastName + ", " + firstName);
				outFile.println(lastName + ", " + firstName);
			}
			inFile.close();
			outFile.close();
		}

		catch(IOException e)
		{
			System.err.println("Error in input file " + e.toString() );
			System.exit(1);
		}
	}

}