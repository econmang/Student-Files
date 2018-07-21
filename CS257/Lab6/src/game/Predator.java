// Evan Conley & Yiwei Zheng//
package game;

import java.awt.Color;
import java.awt.Point;
import java.awt.Polygon;
import java.awt.Rectangle;
import java.awt.geom.Ellipse2D;

public class Predator extends Sprite implements Move, Cloneable
{
	private static final int MAX_TRIES = 2;
	private int direction;
	Polygon top, left, right;
	Rectangle middle;
	Ellipse2D.Float bottom1;
	
	public Predator()
	{
		Ellipse2D.Float glassCase = new Ellipse2D.Float(325,250,110,115);
		add(glassCase, new Color(173,215,255));
		
		Ellipse2D.Float alienHead = new Ellipse2D.Float(340,253,60,60);
		add(alienHead, new Color(54,221,35));
		
		Ellipse2D.Float eye1 = new Ellipse2D.Float(360,260,10,15);
		add(eye1, Color.BLACK);
		
		Ellipse2D.Float eye2 = new Ellipse2D.Float(375,260,10,15);
		add(eye2, Color.BLACK);
	
		Ellipse2D.Float ufo = new Ellipse2D.Float(280,295,190,80);
		add(ufo,new Color(188,187,186));
		
		Ellipse2D.Float mouth = new Ellipse2D.Float(360,280,35,5);
		add(mouth,Color.BLACK);
	}
		
	
	public Predator(int x, int y)
	{
		this();
		setPosition(new Point(x,y));
	}
	
	@Override
	public Point nextposition(Rectangle bounds) 
	{
		setParameters();
		
		Point position = getPosition();
		int i = 0;
		while(i<MAX_TRIES)
		{
		position.x += DELTA_XY[direction][0];
		position.y += DELTA_XY[direction][1];
		setPosition(position);
		setAngle(ANGLES[direction]);
		
	    if(!bounds.contains(getBounds()))
		{
			restore();
			 direction = (int)(Math.random()*DELTA_XY.length);
			
		}
	     i++;
		}
		return position;
	}
	
	@Override
	public Predator clone()
	{
		Predator pre = new Predator();
		pre.setPosition(getPosition());
		pre.setScale(getScale());
		pre.setAngle(getAngle());
		return pre;				
	}
	
	public double getMinScaleFactor()
	{
		return 0.3;
	}
	public double getMaxScaleFactor()
	{
		return 0.3;
	}

}