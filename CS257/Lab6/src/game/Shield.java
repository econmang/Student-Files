// Evan Conley & Yiwei Zheng//
package game;

import java.awt.*;

public class Shield extends Sprite 
{
	Polygon S;
	public Shield()
	{
		int[] xPoints = new int[]{50, 50, 70, 90, 90, 70};
		int[] yPoints = new int[]{50, 100, 120, 100, 50, 70};
		
		S = new Polygon(xPoints, yPoints, xPoints.length);
		add(S,Color.YELLOW);
		
	}
	
	

	public Shield(int x, int y)
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

