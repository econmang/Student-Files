/*
 * Evan Conley & Yiwei Zheng
 * Professor Harvey
 * CS 257
 * Avatar.java
 * This was written to create the avatar class for
 * game creation. It houses information about pieces of the
 * graphics for the avatar as well as an draw function for this
 * class.
 * */

package game;

import java.awt.Color;
import java.awt.Point;
import java.awt.Rectangle;
import java.awt.geom.Ellipse2D;
import java.awt.geom.Line2D;
import java.awt.geom.RoundRectangle2D;

public class Avatar extends Sprite implements Move, Cloneable
{
	public Avatar()
	{
		super ();
		
		Rectangle backPack = new Rectangle(328, 200,124,115);
		add(backPack,Color.LIGHT_GRAY);		
		
		Rectangle leftLeg = new Rectangle(343, 350,45,80);
		add(leftLeg,Color.LIGHT_GRAY);
		
		Rectangle rightLeg = new Rectangle(395, 350,45,80);
		add(rightLeg,Color.LIGHT_GRAY);
			
		Ellipse2D.Float torsoFill = new Ellipse2D.Float(320,225,140,150);
		add(torsoFill,Color.WHITE);
		
		Ellipse2D.Float helmet = new Ellipse2D.Float(335,145,100,100);
		add(helmet,Color.WHITE);
		
		Rectangle rect = new Rectangle(345,170,80,10);
		add(rect,Color.CYAN);
		
		Rectangle leftFoot = new Rectangle(323, 405,65,30);
		add(leftFoot,Color.WHITE);
		
		Rectangle rightFoot = new Rectangle(395, 405,65,30);
		add(rightFoot,Color.WHITE);	
		
		Rectangle chestPieceLarge = new Rectangle(365, 258,45,30);
		add(chestPieceLarge,Color.CYAN);
		
		Rectangle chestPieceSmall = new Rectangle(368, 260,41,24);
		add(chestPieceSmall,Color.GREEN);

		Line2D.Float line = new Line2D.Float(320, 305, 460, 305);
		add(line,Color.BLACK);
		
		RoundRectangle2D.Float rrect = new RoundRectangle2D.Float(345, 170, 80, 55, 10, 10);
		add(rrect,Color.CYAN);
	}

	public Avatar(int x, int y)
	{
		this();
		setPosition(new Point(x,y));
	}
	
	@Override
	public Point nextposition(Rectangle bounds) 
	{
		Point position = getPosition();
		position.x += 30;
		position.y += 15;
		setPosition(position);
		return position;
	}
	
	@Override
	public Avatar clone()
	{
				Avatar av = new Avatar();
				av.setPosition(getPosition());
				av.setScale(getScale());
				av.setAngle(getAngle());
				return av;				
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