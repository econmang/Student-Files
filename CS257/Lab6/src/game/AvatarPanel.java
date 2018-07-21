/*
 * Evan Conley & Yiwei Zheng
 * Professor Harvey
 * CS 257
 * */

package game;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Point;
import java.awt.Rectangle;

import javax.swing.BorderFactory;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

public class AvatarPanel extends JPanel implements Constants
{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private final static int HEIGHT = 30;
	private Avatar avatar;
	private int numAvatars;
	private Rectangle bounds;
	private static Color[] colors = {Color.GREEN, new Color(25,255,0), new Color(75,175,0),Color.RED};
    private static int color=0;
public AvatarPanel()
{
	numAvatars = 0;
	avatar = new Avatar(0,0);
	
	bounds = avatar.getBounds();  // Store the new Avatar bounds after scaling
    double scale = (double)HEIGHT / bounds.height;
    avatar.setScale(scale);
    bounds = avatar.getBounds();  // Store the new Avatar bounds after scaling
    
    Dimension size = new Dimension(bounds.width * MAX_AVATARS, HEIGHT);
    setSize(size);
    setPreferredSize(size);
    setMinimumSize(size);
    setMaximumSize(size);
    
    setBorder(BorderFactory.createEtchedBorder());
    setBackground(Color.WHITE);
    
}
public void reset()
{
	numAvatars = 3;
	repaint();
}

public boolean killAvatar()
{
	 if(numAvatars>0)
		 {
		 numAvatars--;
		 repaint();
		 }
	 else if (numAvatars == 0)
		{
			JOptionPane.showMessageDialog(this,"Better luck next time!");
			System.exit(0);
		}
	 else
			reset();
			color = 0;
		 return numAvatars==0;
}

public void makeAvatar()
{
	 if (numAvatars < MAX_AVATARS)
		 numAvatars++;
	    repaint();
}

public boolean setColor(boolean bad) 
{
	if(bad)
	{
		if(color<colors.length -1) color++;
		else
			{
				repaint();
				return killAvatar();
			}	
	}
	else
	{
		if (color>0) color--;
		if (color==0) 
			{
				makeAvatar();
				repaint();
				return false;
			}
	}
	repaint();
	return false;
}

public @Override void paintComponent(Graphics g)
{
	super.paintComponent(g);
	int x, y;
	for(int num=0; num<numAvatars; num++)
	{
		if (num ==0) avatar.setBackground(colors[color]);
		else avatar.setBackground(null);
		
		x = -bounds.x + num*bounds.width;
		y = -bounds.y;
		avatar.setPosition(new Point(x,y));
		avatar.draw(g);
		
	}
}

    
}
