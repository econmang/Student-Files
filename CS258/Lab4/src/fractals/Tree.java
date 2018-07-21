package fractals;
// Program to create a recursive tree.
// This is the base program to be used to start the cs258 project on recursion.

import java.applet.Applet;
import java.awt.*;

public class Tree extends Applet
{  private final int    APPLET_WIDTH  = 320;
   private final int    APPLET_HEIGHT = 320;
   private final double STARTSIZE     = 110.0;
   private final double STARTANGLE    = 180.0;
   private final double CHANGEANGLE   =  30.0;
   private final double FACTOR        =   2.0;
   private final double MINSIZE       =  10.0;

// Initialize the applet.

   public void init()  {  setSize(APPLET_WIDTH, APPLET_HEIGHT);  }

// Create the drawing that displays on the applet.

   public void paint(Graphics page)  
   { drawTree(page, APPLET_WIDTH/2, APPLET_HEIGHT, STARTSIZE, STARTANGLE);
   }
   public void drawTree( Graphics page, int x, int y, double size, double angle )
   {  Point endPoint = calculatePoint(x, y, size, angle );
      page.drawLine(x, y, endPoint.x, endPoint.y);
      if (size > MINSIZE)
      {  drawTree(page, endPoint.x, endPoint.y
                                  , size/FACTOR, angle+CHANGEANGLE);
         drawTree(page, endPoint.x, endPoint.y
                                  , size/FACTOR, angle-CHANGEANGLE);
   }  }   
   public Point calculatePoint( int x, int y, double size, double degree )
   {  Point point = new Point(x, y);
      double radians = Math.PI/180. * degree;

      point.x += (int)(size * Math.sin(radians));
      point.y += (int)(size * Math.cos(radians));  
      return point;
   }
}