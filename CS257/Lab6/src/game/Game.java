/*
 * Evan Conley & Yiwei Zheng
 * Professor Harvey
 * CS 257
 * Game.java
 * This program just creates a window
 * from which the world and avatar 
 * are drawn.
 * */

package game;

import java.awt.Component;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.Frame;
import java.awt.image.BufferedImage;
import java.net.URL;

import javax.imageio.ImageIO;
import javax.swing.JApplet;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;


public class Game extends JApplet
{
   
	private static final long serialVersionUID = 1L;
	public static final Dimension APP_SIZE = new Dimension(800, 600);
    private BufferedImage image;
    
    public static void main(String[] args)
    {
    JFrame frame = new JFrame ();
    Game applet = new Game();
    frame.setTitle("Astronaut vs. Aliens");
    applet.init();
    frame.getContentPane().add(applet);
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    frame.setVisible(true);
    frame.setSize(APP_SIZE);
    }
    /** Initialize the JApplet */
    public @Override void init()
    { 
    	getIcon("sprite.gif");
    	setIcon();

    	JPanel panel = new MainPanel();
    	Container container = getContentPane();
    	container.add(panel);
    	setSize(APP_SIZE);
    }


  /** Method to load the Buffered image for the icon */
    private void getIcon(String picture)
    {  
    	try
     {
         URL file = this.getClass().getResource("/data/" + picture);
         image = ImageIO.read(file);
     }
     catch (Exception e) {  JOptionPane.showMessageDialog(this, e);  }
    }
 
  // Load the icon and set it into the current frame's title bar
    private void setIcon()
    {  Component root = SwingUtilities.getRoot(this);
    	if (root instanceof JFrame || root instanceof Frame)
    	{   Frame frame = (Frame)root;
         frame.setIconImage(image);
    	}
    }
}    // End of Game class

