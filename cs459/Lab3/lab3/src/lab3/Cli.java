package lab3;

import java.io.IOException;

import console.*;

/** Class to test the OS Console class */
public class Cli implements CommandListener
{
	public OSConsole console;
	public Thread kernelT;
	public Kernel kernelO;
	public SystemCall call;
	
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
		kernelT.start();
		try {
			call = new SystemCall(SystemCall.PORT,100);
			call.start();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
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
