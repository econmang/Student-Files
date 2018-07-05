package lab2;

import console.*;

/** Class to test the OS Console class */
public class Cli implements CommandListener
{
	public OSConsole console;
	// kernel must be a singleton instance object rather than a class object, 
	// because can't seem to ask a class object to start()
	public Thread kernelT;
	// shared data with the kernel thread
	
	private String cmd;

	public String gCmd() {
		return cmd;
	}
	public  void sCmd(String s) {
		cmd = s;
	}
	//reads current, sets new value, returns value read
	// single reads or writes to 4 byte quantities are atomic
	// but a read + a write (2 operations) need to be sync'ed
	public synchronized String atomicRWCmd(String s) {
		String retVal = cmd;
		cmd = s;
		return retVal;
	}
	
	public static void main(String[] args)
	{
		new Cli();
	}
	
	public Cli()
	{
		console = new OSConsole("Batch Sequencer");
		console.setCommandListener(this);
		kernelT = new Thread (new Kernel(this, this.console));
		// start the kernel thread
		kernelT.start();
	}

	@Override
	public void commandReceived(String command)
	{
		// empty command
		if (command.trim().length()<1)
			return;
		// write it where the kernel can read it
		Kernel.cPrintln(System.err, command);
		cmd = command;
		// let the kernel know 
		kernelT.interrupt();
	}	
}
