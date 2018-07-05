package console;

/** Thread to get input from  the  text area object. It starts a new thread which waits
 * 		for the user to enter a new line. When it does is saves the result for retrieval.
 * 
 *  Note: A new thread is spawned for each input. A thread factory would be more efficient,
 *  but for this application, this approach will suffice.
 */
public class ConsoleReader extends Thread implements CommandListener
{
	private String[] result;
	
	public ConsoleReader(OSConsole console, String[] result)
	{
		CommandListener oldListener = console.getCommandListener();
		console.setCommandListener(this);
		
		this.result = result;
		result[0] = null;
		
		start();
		
		try
		{
			join();
		}
		catch (InterruptedException e) {}
		
		console.setCommandListener(oldListener);
	}
	
	public void run()
	{
		while (true)
		{
			try
			{
				Thread.sleep(10000);
			}
			catch (InterruptedException e) {  return; }
		}
		
	}

	@Override
	public void commandReceived(String data)
	{
		if (data.length()>0)  result[0] = data;
		this.interrupt();
	}
	
}