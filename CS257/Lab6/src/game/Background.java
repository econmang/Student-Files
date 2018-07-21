/*
 * Evan Conley & Yiwei Zheng
 * Professor Harvey
 * CS 257
 * */

package game;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.KeyEventDispatcher;
import java.awt.KeyboardFocusManager;
import java.awt.Point;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.util.ArrayList;

import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.Timer;

public class Background extends JPanel implements Constants, ActionListener
{
	private static final long serialVersionUID = 1L;
	private static final Color BACK_COLOR = new Color(66,133,150);
	private ArrayList<Sprite> sprites;
	private static final int BORDER = 85;
	private static int numShields = 0;
	private  Avatar avatar;
	
	public Background()
	{
		setBackground(BACK_COLOR);
		// Instantiate the array list of Sprites
		sprites= new ArrayList<Sprite>();
		reset(0);
		avatarPanel.reset();
		
		KeyboardFocusManager manager = KeyboardFocusManager.getCurrentKeyboardFocusManager();
		// The following statement adds the key dispatcher along with an anonymous listener
		manager.addKeyEventDispatcher(new KeyEventDispatcher()
		{
			public boolean dispatchKeyEvent(KeyEvent event)
		    	{
					Point position = avatar.getPosition();
					double angle =0;
		            // Get the avatar object
		            // Get the avatar current position
		        	switch (event.getKeyCode())
		            {
		                     case KeyEvent.VK_DOWN: 
		                           position.y += 5;
		                           angle = 2;
		                           break;
		                           
		                       case KeyEvent.VK_UP:
		                           position.y -= 5;
		                           angle = 182;
		                           break;
		                          
		                       case KeyEvent.VK_LEFT:
		                           position.x -= 5;
		                           angle = 180;
		                           break;
		                       case KeyEvent.VK_RIGHT:
		                    	   position.x += 5;
		                    	   angle = 0;
		                    	   break;
		            }
		            avatar.setParameters();
		            avatar.setAngle(angle);
		        	avatar.setPosition(position);
		        	
		        	
		                   if (!getBounds().contains(avatar.getBounds()))
		                   {   
		                	   avatar.restore();
		                	   Toolkit.getDefaultToolkit().beep();
		                       return true;
		                   }
		                   else
		                   {
		                	   repaint();
		                   }
		                   // Repaint the background
		                  return true;
		              }
		           });
					Timer timer=new Timer(33,this);
					timer.start(); 
		
		
	}
	public void reset(int level)
	{
		sprites.clear();
		int[] figures = FIGURES[level];  // Four predators and one avatar
		Sprite sprite = null;
		int x, y;
		for (int type=0; type<figures.length; type++)
       		{ 
					for (int figure=0; figure<figures[type]; figure++)
				{
	               // Set x and y with random values within bounds of the Game width and height
					x = (int)(Math.random()*(Game.APP_SIZE.width - 2*BORDER) + BORDER);
					y = (int)(Math.random()*(Game.APP_SIZE.height - 2* BORDER) + BORDER);
	    	
					switch (type)
					{
					case 0:
						sprite = new Predator(x,y);
						break;
					case 1:
						sprite = new Mine(x,y);
						break;
					case 2:
						sprite = new Shield(x,y);
						break;
					case 3:
						sprite = avatar = new Avatar(50,50);
						break;
	    		   }
	    		   
			        // call the Sprite object setScale() method with a random size (1.0 is its original size)
			    	double min = sprite.getMinScaleFactor();
			    	double max = sprite.getMaxScaleFactor();
			    	sprite.setScale(Math.random()*(max-min) + min);
			       // call the Sprite object setAngle() method with a random angle
			    		sprite.setAngle(Math.random()*360);
			       	// Hint: use Math.random() for choosing random angles and sizes.
			              // add the Sprite object to the array list
			    	sprites.add(sprite);
				}
       		}
		repaint();
	}
    /** Draw the background on the panel
     *
     * @param g Graphic object with draw and color methods
     */
	
	    
    public @Override void paintComponent(Graphics g)
    {
       super.paintComponent(g);
       for (Sprite sprite: sprites)
       {
    	   sprite.draw(g);
    	   
       }
       
    }
    public void actionPerformed(ActionEvent event)
    {
    	Sprite sprite;
    	Move move;
    	for (int i = 0; i<sprites.size(); i++)
    	{
    		sprite = sprites.get(i);
    		if (sprite instanceof Move)
    		{
    			move = (Move)sprite;
    			move.nextposition(getBounds());
    		}
    		else
    		{
    			break;
    		}
    	    action();
    	    win();
    		repaint();
    	}
    
    }
    
    public void win()
    {
    	if(numShields== SHIELDS_WIN)
    			{
    				JOptionPane.showMessageDialog(this,"Congrats, you did it!");
    				System.exit(0);
    			}
    }
    
    public void action()
    {
    Sprite sprite;
    for (int i=0; i<sprites.size(); i++)
    {
         
         sprite = sprites.get(i);
         if (avatar==sprite) continue;
         
         if (avatar.getBounds().intersects(sprite.getBounds()))
        {
        	 if (sprite instanceof Predator)
		    	{
		    		avatarPanel.killAvatar();
		    		southPanel.adjustPoints(-100);
		    		avatarPanel.setColor(true);
		    		avatar.setPosition(new Point(50,50));
		    	}
		    	repaint();
		    	
		    	if (sprite instanceof Mine)
		    	{
		    		avatarPanel.killAvatar();
		    		southPanel.adjustPoints(-100);
		    		avatarPanel.setColor(true);
		    		avatar.setPosition(new Point(50,50));
		    		sprites.remove(sprite);
		    	}
		    	
		    	if (sprite instanceof Shield)
		    	{
		    		avatarPanel.setColor(false);
					southPanel.adjustPoints(100);
					numShields++;
		    		sprites.remove(sprite);	
		    	}// Logic goes here depending on the rules of your game	    	
        }
    }

    }
   
}