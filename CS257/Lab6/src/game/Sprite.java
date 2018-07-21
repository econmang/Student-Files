/* Evan Conley & Yiwei Zheng */

package game;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Point;
import java.awt.Rectangle;
import java.awt.Shape;
import java.awt.geom.AffineTransform;
import java.awt.geom.Area;
import java.util.ArrayList;

//Appropriate package and import statements

public abstract class Sprite extends Area 
{
	private int x, y;  // horizontal & vertical position of a sprite
	private double angle, scale; // rotation angle and scale factor
	private ArrayList<Area> areas; // List of sprite pieces
	private ArrayList<Color> colors; // List of colors for each piece
	private Color background;
	private int oldX,oldY;
	private double oldAngle,oldScale;
	
	public Sprite()
	{
   // Constructors initialize objects by setting values into each instance variable
   // Set the initial scale factor to 1.0, and other variables to zero
         // Instantiate the ArrayLists (e.g. new ArrayList<Area>();)
		angle = oldAngle = x = y = oldX = oldY = 0;
		scale = oldScale = 1;
		areas = new ArrayList<Area>();
		colors = new ArrayList<Color>();
		background = null;
	
		
		
	}
	public void setParameters()
	{
		oldX = x;
		oldY = y;
		oldAngle = angle;
		oldScale = scale;
	}
	public void restore()
	{
		AffineTransform tx = getTransform(oldX, oldY, oldAngle, oldScale);
		transform(tx);

	}
	public void setBackground(Color background)
	{
		this.background = background;
	}
	public void setAngle(double angle)
	{
		AffineTransform tx = getTransform(x, y, angle, scale);
		transform(tx);
	}
	
	public double getAngle() 
	{  // Return the current angle   
		return angle;
	}
	public void setScale(double scale)
	{
		AffineTransform tx = getTransform(x,y,angle,scale);
		transform(tx);
	// The getTransform method provided for you below returns an AffineTransform object
   // The transform method uses the AffineTransform to position, rotate, and sacle
   // Add the identical two statements as those provided in the setAngle method.
	}
	public double getScale()
	{  // return the current scale factor
		return scale;
	}
	public void setPosition(Point p)
	{
		AffineTransform tx = getTransform(p.x,p.y,angle,scale);
		transform(tx);
   // Repeat the getTransform and transform calls as done in setAngle and setScale
   // Don't use x and y as arguments, but extract x and y from the Point parameter, p
	}
	public Point getPosition()
	{
		return new Point(x,y);// Return the current x, y position by instantiating a Point object
	}
	public void add(Shape shape, Color color)
	{
		Area a = new Area(shape);
		super.add(a);
		areas.add(a);
		colors.add(color);
	// Instantiate an Area object with the shape that is passed
   // Call the add method in the parent class
   // Append the Color and Area object to the Sprite class array lists
	}

/** Create an AffineTransform object (Review the week 2 slides) 
 *   to enable the object to be moved, rotated, and scaled
 *   @param x The desired horizontal position 
 *   @param y The desired vertical position
 *   @param angle The desired rotation angle in degrees
 *   @param scale The desired scale factor (1.0 is full size)
 *   @return The AffineTransform object to move, rotate, and scale
 */
	private AffineTransform getTransform
                    (int x, int y, double angle, double scale)
	{
      AffineTransform transform = new AffineTransform();
      transform.translate(x, y);
          
      if ( (angle>90 && angle<270) )   
      { transform.scale(1,-1);  }

      double deltaA = angle - this.angle;
      transform.rotate(deltaA * Math.PI/180.);
          
      if (this.angle>90 && this.angle<270)    
      { transform.scale(1,-1);  }
          
      double deltaScale = scale / this.scale;
      transform.scale(deltaScale, deltaScale);
          
      Rectangle rect = getBounds();
      int centerX = rect.x + rect.width/2;
      int centerY = rect.y + rect.height/2;
      transform.translate(-centerX, -centerY);
          
      this.x = x;
      this.y = y;
      this.angle = angle;
      this.scale = scale;

      return transform;
	}

	public void draw(Graphics g)
	{
   // Cast the Graphics object and store in a Graphics2D local variable
		Graphics2D g2d = (Graphics2D)g;
		if(background !=null)
		{
			g2d.setColor(background);
			Rectangle rect = getBounds();
			g2d.fill(rect);
			
		}
		for (int a=0; a<areas.size(); a++)
		{
			g.setColor(colors.get(a));
			g2d.fill(areas.get(a));
		}
   // For each element in the ArrayList object of Area objects, 
   //    set the color using setColor and call the graphics2D fill method
	}
	public @Override void transform(AffineTransform tx)
	{
   // Call the parent class version of transform using the super reserved word 
		super.transform(tx);
   // Call transform for each element in the ArrayList of Area objects
		
		for (Area area: areas)
		{
			area.transform(tx);
		}
		
	}
	public abstract double getMinScaleFactor();
	public abstract double getMaxScaleFactor();

}


