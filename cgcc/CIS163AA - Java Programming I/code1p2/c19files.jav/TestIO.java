/*** lots of probs in convering this - need to ensure I have
removed alll my debug code (eg."done")  in final version.
  also, my environ didnt allow commandline args to JAVA
  If I didnt print done, the output dint always flush
  Without the buffer size, an err shoed up when typing e,g 11 h's
     .. hitting enter did not force the read - I needed to type in lots
     more chars or lines.  Then, eventually, the first line was read.
     '
  
  */
import java.io.*;
class TestIO  { 

    private String line1, line2, line3;     
    private DataInputStream inStream;
    private BufferedReader keyboard;

    public static void main (String []  args) {
        TestIO aFind = new TestIO();     
        aFind.doSearch("");           //"")(args[0]);
    }

    private void doSearch(String fileName) {
        keyboard = new BufferedReader(new InputStreamReader(System.in), 1);
        String  wanted = prompt("Type string to find:");
      
    }  
        private String prompt(String message) {
        String reply = "";
         try {
            System.out.print(message);
            System.out.flush();
            reply = keyboard.readLine();
            System.out.print(reply);
        }
        catch (IOException e) {
            System.out.println("Keyboard input "+ e.toString() );
 //           System.exit(2);
        }
        return reply;
    }

}


