// Evan Conley & Yiwei Zheng//
package game;


import java.awt.*;
import java.awt.geom.Ellipse2D;

public class Mine extends Sprite
{
	Ellipse2D Round;
	Ellipse2D middle;
	Rectangle Top;
	
	public Mine()
	{
		Rectangle fuse = new Rectangle(110, 85, 10, 35);
		add(fuse, Color.WHITE);
		
		Ellipse2D.Float round = new Ellipse2D.Float(100, 100, 50, 50);
		add(round,Color.BLACK);
	}
	public Mine(int x, int y)
	{
		this();
		setPosition(new Point(x,y));
	}
	public double getMinScaleFactor()
	{
		return 0.3;
	}
	public double getMaxScaleFactor()
	{
		return 0.4;
	}


}
