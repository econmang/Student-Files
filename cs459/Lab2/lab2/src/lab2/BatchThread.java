package lab2;
import java.io.*;
public class BatchThread extends Thread
{  
   private Cli cli;
   private String      fileName;   // The file where to direct output.
   private long        limit;      // Time limit.
   private ProcessList runList;    // The processes queued to the batch.
   public Process proc;
   	// the process list also contains the name of the batch.

   // Constructor 
   public BatchThread(
		   Cli cli,
		   String fileName, 
		   long limit, 
		   ProcessList runList)
   {
	   this.cli = cli;
	   this.fileName = fileName;
	   this.limit = limit;
	   this.runList = runList;
   }
   
   // Method to run the thread.
   public void run() {  
	   try {
		   runList.runStarted();
		   
		   // STUB:
		   Thread.sleep(Math.round(Math.random()*10000));
		   // END STUB
		   
		   // create and start new MaxTime thread
		   MaxTime mt = new MaxTime(this,limit);
		   File file = new File(fileName + ".bat");
		   PrintWriter writer = new PrintWriter(file.getCanonicalFile());
		   String str = "";
		   mt.start();
		   while(!runList.isEmpty()){
			   proc = runList.head();
			   this.setPriority(proc.getPriority());
			   proc.setStatus(Stati.RUNNING);
			   str += runList.deQueue().run(writer);
		   }
		   mt.interrupt();
		   writer.flush();
		   writer.close();
		   if (str == "")
				Kernel.cPrintln(System.out,"Batch Empty");
		   runList.runFinished(Stati.TERMINATED);
		   Kernel.cPrintln(System.out,"Batch terminated.");
		   cli.kernelT.interrupt();
	   }
	   catch (InterruptedException | InstantiationException | IllegalAccessException | IOException e) {
		   // set Process status ABORTED
		   while(!runList.isEmpty()){
				proc = runList.head();
				proc.setStatus(Stati.ABORTED);
				Kernel.cPrintln(System.out,proc.toString());
				runList.deQueue();
		   }
		   System.err.println("BT: run() interrupted");  // STUB
	   }
   }
}