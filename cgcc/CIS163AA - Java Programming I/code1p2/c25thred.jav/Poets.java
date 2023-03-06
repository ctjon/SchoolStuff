import java.awt.*;
import java.beans.*;
import java.lang.*;
import java.awt.event.*;
import java.applet.*;

public class Poets extends Applet implements Runnable
   {

   public void init() 
      {
      setBackground (new java.awt.Color(0,255,0));
      setSize (450,300);
      enableEvents (AWTEvent.COMPONENT_EVENT_MASK+AWTEvent.FOCUS_EVENT_MASK+AWTEvent.KEY_EVENT_MASK+AWTEvent.MOUSE_EVENT_MASK+AWTEvent.MOUSE_MOTION_EVENT_MASK);
      initListeners();
      //Add your code here
      }

   private void initListeners()
      {
      }

   public void start() 
      {
      //Add your code here
      }

   public void stop() 
      {
      //Add your code here
      }

   public void destroy() 
      {
      //Add your code here
      }

   public void run() 
      {
      //Add your code here
      }

   public void paint(Graphics g) 
      {
      //Add your code here
      super.paint (g);
      }

   public void processEvent (AWTEvent e)
      {
      //Add your code here
      super.processEvent (e);
      }

   public void processComponentEvent (ComponentEvent e)
      {
      //Add your code here
      super.processComponentEvent (e);
      }

   public void processFocusEvent (FocusEvent e)
      {
      //Add your code here
      super.processFocusEvent (e);
      }

   public void processKeyEvent (KeyEvent e)
      {
      //Add your code here
      super.processKeyEvent (e);
      }

   public void processMouseEvent (MouseEvent e)
      {
      //Add your code here
      super.processMouseEvent (e);
      }

   public void processMouseMotionEvent (MouseEvent e)
      {
      //Add your code here
      super.processMouseMotionEvent (e);
      }

   }
//JAVADRAW! type definition section
//Please do not alter this remark! [JDV5.0tds]
