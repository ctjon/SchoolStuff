import java.io.*;
import java.net.*;

class TinyBrowser  { 

    private BufferedReader inStream, keyboard;

    public static void main (String []  args) {
        TinyBrowser aBrowser = new TinyBrowser();     
        aBrowser.fetch();
    }

    private void fetch() {
        String urlString = "";
        String line;
        keyboard = new BufferedReader(new InputStreamReader(System.in),1);
        try {
            urlString = prompt
               ("Type a URL address (e.g http://java.sun.com/) :");

            // create a link to  a URL
            URL urlAddress = new URL(urlString);
            URLConnection link = urlAddress.openConnection();
             
            inStream = new BufferedReader(new
                         InputStreamReader(link.getInputStream()));

            while ((line = inStream.readLine()) != null) {
                System.out.print(line);  
            }

        }
        catch (MalformedURLException e) {
            System.err.println(urlString + e.toString());
            System.exit(2);
        }

        catch (IOException e) {
            System.err.println("Error in accessing URL: "+
                                e.toString());
            System.exit(1);
        }
     
    } 

    private String prompt(String message) {
        String reply = "";
        try {
            System.out.print(message);
            System.out.flush();
            reply = keyboard.readLine();
        }
        catch (IOException e) {
            System.out.println("Keyboard input "+ e.toString() );
            System.exit(2);
        }
        return reply;
    }

}

