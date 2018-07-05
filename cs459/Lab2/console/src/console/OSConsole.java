package console;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;
import javax.imageio.*;
import java.net.*;
import java.util.*;


/** OS command line console to be used with the batch sequencer simulated OS */
public class OSConsole extends JFrame
{
	private static final long serialVersionUID = 1L;
	private static final int MAX_HISTORY = 100;
	
	private static OSConsole console = null;
	
	private JTextArea textArea;
	private Vector<String> history;
	private int historyIndex;
	private boolean passwordMode;
	private String passwordData;
	private int lastCommandOffset;
	
	private static CommandListener listener;
	
	int typeCount = 0, pressCount = 0;		
	
	public static OSConsole getConsoleInstance(String title)
	{
		if (console == null)
			console = new OSConsole(title);
		
		return console;
	}
	// Constructor to initialize the console
	public OSConsole(String title)
	{
		history = new Vector<String>();
		historyIndex = 0;
		passwordMode = false;
		passwordData = "";
		
		setIcon( getIcon("console.gif") );
		
		setTitle(title);
		setSize(new Dimension(1000, 600));
		
		Container container = getContentPane();
		container.setLayout(new BorderLayout());
		
		textArea = new JTextArea(80, 20);
		textArea.setCaretColor(Color.white);
	    textArea.getCaret().setVisible(true);
		textArea.setFont(new Font("Courier", Font.PLAIN, 20));
		textArea.setBackground(Color.BLACK);
		textArea.setForeground(Color.WHITE);

	    JScrollPane scrollPane = new JScrollPane(textArea);
		container.add(scrollPane, BorderLayout.CENTER);
		
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setVisible(true);
		
		// The following statement adds an anonymous key listener
		textArea.addKeyListener(new KeyListener()
		{
	          public void keyTyped(KeyEvent event)
	          {
				  String text = textArea.getText();
				  int position = textArea.getCaretPosition();
				  historyIndex = history.size();
		  
				  if (text.length()>0 && position < text.substring(0, text.length()-1).lastIndexOf('\n'))
				  {
					  textArea.setCaretPosition(text.length());
				  }
				  
	        	  char c = event.getKeyChar();
	              if (c == '\n')
	              {
					  String command = getCommand();
					  processCommand(command);
					  return;
	              }
	              else if (passwordMode)
	              {
                      if (event.getKeyChar()==KeyEvent.VK_BACK_SPACE) 
                      {
                    	  int len = passwordData.length();
                    	  if (len>0)
                    		  passwordData = passwordData.substring(0, len-1);
                    	  return;
                      }
                      
	            	  passwordData += c;
	            	  event.setKeyChar('*');
	            	  event.setKeyCode(KeyEvent.VK_ASTERISK);
	              }
	          }
				  
			  public void keyPressed(KeyEvent event) 
			  {
				  String command = "";
				  String text = textArea.getText();
				  
				  if (event.getKeyCode()==KeyEvent.VK_BACK_SPACE)
				  {
            		  int length = textArea.getText().length();
            		  if  (lastCommandOffset>=length)
            		  {
    					  event.consume();
            		  }
					  return;
				  }

				  if (passwordMode) return;
				  
				  if (event.getKeyChar()=='\n') 
				  {
					  if (text.endsWith("\n"))
					  {
						  text = text.substring(0, text.length()-1);
						  textArea.setText(text);
					  }
					  return;
				  }
			
				  if (event.getKeyCode() == KeyEvent.VK_UP)
				  {
 					  if (historyIndex == history.size())
					  {
						  if (text.endsWith("\n") || text.length()==0)
						  {
							  if (!text.endsWith(" \n")) textArea.append(" \n");
							  textArea.setCaretPosition(textArea.getText().length());
						  }
					  }
					  if (historyIndex>0)
					  {
						  historyIndex--;
					  }
					  command = getCommand();
					  displayCommand(command );
				  }
			    
				  if (event.getKeyCode() == KeyEvent.VK_DOWN)
				  {
					  if (historyIndex<history.size())
					  {
						  historyIndex++;
						  command = getCommand();
						  displayCommand(command);
					  }
					  else textArea.setCaretPosition(textArea.getText().length());
				  }
			  }
		  
			  public void keyReleased(KeyEvent event) {}
        });
	
	}	// End of constructor
	
	/** Set the callback listener for processing command line when new lines are detected
	 * 
	 * @param listener callback listener object
	 */
	public void setCommandListener(CommandListener listener)
	{
		OSConsole.listener = listener;
	}
	
	/** Get the current command listener object */
	public CommandListener getCommandListener()
	{
		return  listener;
	}
	
	/** Display output to the console
	 * 
	 * @param text The output to display
	 */
	public synchronized void write(final String text)
	{
		EventQueue.invokeLater(new Runnable() 
		{
            @Override
            public void run() 
            {
        		textArea.append(text);
        		
        		int length = textArea.getText().length();
        	    textArea.setCaretPosition(length);
        	    lastCommandOffset = length;
            }
		});
	}
	
	/** Display output to the console and end with a new line character
	 * 
	 * @param text The output to display
	 */
	public void writeLine(String text)
	{
		write(text + "\n");
	}
	
	/** Display the command retrieved from the history list
	 * 
	 * @param command Command to display in the textArea
	 */
	private void displayCommand(String command)
	{
		String data = textArea.getText();
				
		while (data.endsWith("\n")) 
			data = data.substring(0, data.length()-1);
		int lastIndex = lastCommandOffset = data.lastIndexOf("\n");
		lastCommandOffset++;
		data = data.substring(0,lastIndex+1) + command;
		textArea.setText(data);
	    textArea.append("\n");
	    textArea.setCaretPosition(textArea.getDocument().getLength());
	}
	
	/** Get command line to be processed */
	private String getCommand()
	{
		String command = "";
	  	if (historyIndex>=0 && historyIndex < history.size())
	  	{
	  		command = history.get(historyIndex);
	  		return command;
	  	}

	  	// Get last command from the text area
		command = textArea.getText();
		
		int length = command.length();
		if (length< lastCommandOffset)
		{
			command = "";
		}
		else
		{
			command = command.substring(lastCommandOffset);
		}
		
		lastCommandOffset = length;
		command.trim();
	  	return command;
	}
	
	/** Process a command line */
	private void processCommand(String command)
	{
		if (listener!=null)
		{
			command = command.trim();
			if (command.length()>0) history.add(command);
	  		if (history.size()>MAX_HISTORY) history.remove(0);
	  		
	  		historyIndex = history.size();
	  		listener.commandReceived(command);
	  		
	  		lastCommandOffset = textArea.getText().length();
		}
	}
	
	/** Method to load the Buffered image for the icon */
  	private BufferedImage getIcon(String picture)
  	{  
  		try
   		{
  			URL file = this.getClass().getResource("/data/" + picture);
  			return ImageIO.read(file);
     	}
     	catch (Exception e) 
		{  
			JOptionPane.showMessageDialog(this, e);  
		}
		return null;
  	}
 
  	/** Load the icon and set it into the current frame's title bar
  	 * 
  	 * @param image The buffered image to use
  	 */
  	private void setIcon(BufferedImage image)
  	{  
  		Component root = SwingUtilities.getRoot(this);
    	if (root instanceof JFrame || root instanceof Frame)
    	{   
    		Frame frame = (Frame)root;
     	    frame.setIconImage(image);
     	}
  	}
}    // End of OSConsole class

