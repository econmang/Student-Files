package fractals;

//Program to create a recursive tree.
//This is the base program to be used to start the cs258 project on recursion.

import java.applet.Applet;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Point;

public class NewTree extends Applet
{  
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private final int    APPLET_WIDTH  = 320;
	private final int    APPLET_HEIGHT = 320;
	private final double STARTSIZE     = 110.0;
	private final double STARTANGLE    = 180.0;
	private final double CHANGEANGLE   =  30.0;
	private final double FACTOR        =   2.0;
	private final double MINSIZE       =  10.0;

	//Initialize the applet.

	public void init()
	{  
		setSize(APPLET_WIDTH, APPLET_HEIGHT);
		setBackground(new Color(102, 153, 255));
	}

	//Create the drawing that displays on the applet.

	public void paint(Graphics page)  
	{
		page.setColor(new Color(51, 102, 0));
		page.fillRect(0,(APPLET_HEIGHT-(APPLET_HEIGHT/4)),APPLET_WIDTH,APPLET_HEIGHT);
		for (int i = 1; i <= pickRandom(3,6);i++)
		{
			int x = (pickRandom(2,4)*i) * pickRandom(12,14);
			int y = (int)(i/i-(i/pickRandom(2,4))) * 120;
			drawCloud(page,x,y,32,32,6);
			drawCloud(page,x-2,y+12,32,32,4);
		}
		for(int i = 1; i <= pickRandom(3,5);i++)
		{
			int x = pickRandom(20,30) * i;
			int y = pickRandom(4,8) * i;
			int startSizeChange = pickRandom(15,40);
			drawTree(page, APPLET_WIDTH/2 - x, APPLET_HEIGHT-5 - y, STARTSIZE - startSizeChange, STARTANGLE);
			drawTree(page, APPLET_WIDTH/2 - x, APPLET_HEIGHT-5 - y, STARTSIZE - startSizeChange, STARTANGLE);
			
			drawTree(page, APPLET_WIDTH/2 + x, APPLET_HEIGHT - y, STARTSIZE + startSizeChange, STARTANGLE);
			drawTree(page, APPLET_WIDTH/2 + x, APPLET_HEIGHT - y, STARTSIZE + startSizeChange, STARTANGLE);
			
			drawTree(page, APPLET_WIDTH/2 + 2*x, APPLET_HEIGHT - 2*y, STARTSIZE - 2*startSizeChange, STARTANGLE);
			drawTree(page, APPLET_WIDTH/2 + 2*x, APPLET_HEIGHT - 2*y, STARTSIZE - 2*startSizeChange, STARTANGLE);
		}
	}
	public void drawTree( Graphics page, int x, int y, double size, double angle )
	{
		Point endPoint = calculatePoint(x, y, size, angle );
		page.setColor(new Color(124, 83, 0));
		page.drawLine(x, y, endPoint.x, endPoint.y);
		int width = (int) ((Math.sqrt(Math.pow((endPoint.y - y), 2))/8)/5) + 1;
		int[] xPoints = {x, endPoint.x, endPoint.x + width, x + width};
		int[] yPoints = {y, endPoint.y, endPoint.y, y};
		page.fillPolygon(xPoints, yPoints, 4);
		drawLeaf(page, endPoint.x, endPoint.y,5,4,5,6);
		if (size > MINSIZE)
		{
			int numBranches = pickRandom(1,3);
			for(int i = 0; i < numBranches; i++)
			{
				drawTree(page, endPoint.x, endPoint.y, size/(pickRandom(2,5)), angle + pickRandom(-40,40));
				drawTree(page, endPoint.x, endPoint.y, size/(pickRandom(2,5)), angle - pickRandom(-40,40));	
			}
		}  
	}   
	public void drawLeaf(Graphics g,int x,int y,int w,int h,int angle,int order)
	{
		g.setColor(new Color(pickRandom(45,145), pickRandom(115,125), pickRandom(35,75)));
		Point endPoint = calculatePoint(x,y,12,angle);
		int[] xVal = {x, endPoint.x, x + w};
		int[] yVal = {y, endPoint.y, y + h};
		g.fillPolygon(xVal, yVal, 3);
		if (order > 1)
		{
			order--;
			drawLeaf(g, x, y, h + pickRandom(-2,2), w + pickRandom(-2,2), angle + pickRandom(-30,30),order);
			drawLeaf(g, x, y, h + pickRandom(-2,2), w + pickRandom(-2,2), angle - pickRandom(-30,30),order);
		}
	}
	public Point calculatePoint( int x, int y, double size, double degree )
	{
		Point point = new Point(x, y);
		double radians = Math.PI/180. * degree;

		point.x += (int)(size * Math.sin(radians));
		point.y += (int)(size * Math.cos(radians));  
		return point;
	}
	int pickRandom(int min, int max)
	{
		double randDoub = Math.random()*((max+1) - min) + min;
		int randInt = (int) randDoub;
		return randInt;
	}
	void drawCloud(Graphics page, int x, int y, int w, int h, int order)
	{
		page.setColor(new Color(pickRandom(140,155), pickRandom(160,195), pickRandom(200,255)));
		page.fillOval(x, y, w, h);
		if (order > 1)
		{
			order--;
			drawCloud(page, x + pickRandom(-8, 8), y + pickRandom(-8, 8), h + pickRandom(-2,2), w + pickRandom(-2,2),order);
			drawCloud(page, x + pickRandom(-8, 8), y + pickRandom(-8, 8), h + pickRandom(-2,2), w + pickRandom(-2,2),order);
		}
	}

}