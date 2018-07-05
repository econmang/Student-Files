package lab3;
import java.util.*;
import java.io.*;
import console.*;

/**
 * Acts as the kernel of our batch operating system:
 * receives commands (system calls)
 * maintains lists of batches
 */
public class Kernel implements Runnable {
	// used to get commands
	private Cli cli;
	
	// active
	private  ProcessList runList;
	
	
	
	// List of ProcessLists -- max of 100 processes 
	// more than that and the system will burn down :)
	// if more are needed, the run command could extend this array.
	// I used an array, because 1) a vector caused a concurrency exception
	// to be thrown at run time, which probably could be ignored, and
	// 2) an array is faster.
	private ProcessList[] activeProcs = new ProcessList[100];
	private int activePCnt = 0;
	
	// list of Batches
	private  Hashtable<String, ProcessList> listOfBatches = new Hashtable<String, ProcessList>();
	
	// constructor
	public Kernel(Cli cli, OSConsole console) {
		this.cli = cli;
	}
	
	// KERNEL utilities:
	
	public static synchronized void cPrintln(PrintStream out, String s) {
		//console.write(s+"\n");
		if (out == System.out) {
			System.out.println(s);
			System.out.flush();
		}
		else {
			System.err.println(s);
			System.err.flush();
		}
	}
	
    // run loop: gets a command from the console

	public void run() {  
    	// set priority to max
		Thread.currentThread().setPriority(Thread.MAX_PRIORITY);
		
		// interrupt event loop
		while(true) {
			try {
				// bare wait() gives IllegalMonitorStateException.
    			synchronized(this) {wait();} 
    		}
    		catch(InterruptedException e){  
    			// find out who interrupted
    			// get local copy of the command for use by the dispatcher
    			String cmd;
    			if ((cmd = cli.atomicRWCmd(null)) != null)
    				dispatchCommand(cmd);
    				
				// walk active threads to see which of them interrupted
    			for (int i=0;i<activePCnt;i++)
    				if (activeProcs[i].isRunFinished()) {
    					cPrintln(System.out, ""+activeProcs[i].getName()+" finished - "+activeProcs[i].getStatus());
    					// place last process in this spot and decrement count
    					activeProcs[i]=activeProcs[--activePCnt];
    				}
    		}
		}
    }
	
	// Commands:
	
	/**
	 * Dispatches commands
	 */
	private void dispatchCommand(String cmd) {
		String[] argData = cmd.trim().split(" ");
		argData[0] = argData[0].substring(0,1).toUpperCase() + argData[0].substring(1).toLowerCase();
		String[] args = new String[argData.length - 1];
		System.arraycopy(argData, 1, args, 0, args.length);
		try{
			if(argData[0].contains("Logout")) {
				cmdLogout();
			}
			else if(argData[0].contains("Run")){
				if(args != null && args.length == 2)
					cmdRun(args[0],Integer.parseInt(args[1]));
				else
					Kernel.cPrintln(System.out, "Incorrect format for Run Command.");
			}
			else if(argData[0].contains("Priority")){
				if(args != null && args.length == 2)
					cmdPriority(args);
				else
					Kernel.cPrintln(System.out, "Incorrect Format for Priority Command.");
			}
			else if(argData[0].contains("List")){
				cmdList();
			}
			else if(argData[0].contains("New")){
				if(args != null && args.length == 1)
					cmdNew(args);
				else
					Kernel.cPrintln(System.out,"Could not creat new batch. Incorrect Format.");
			}
			else if(argData[0].contains("Remove")){
				if(args != null && args.length == 1)
					cmdRemove(args);
				else
					Kernel.cPrintln(System.out, "Incorrect Format for Remove.");
			}
			else if(argData[0].contains("Kill")){
				if(args!= null && args.length == 1)
					cmdKill(args);
				else
					Kernel.cPrintln(System.out, "Incorrect Format for Kill");
			}
			else if(argData[0].contains("Cat")){
				if(args != null && args.length == 1)
					cmdCat(args);
				else
					Kernel.cPrintln(System.out, "Incorrect Format for Cat Command.");
			}
			else if(argData[0].contains("Queue")){
				if(args.length > 0){
					cmdQueue(args);
				}
				else{
					Kernel.cPrintln(System.out, "Incorrect format for Queue");
				}
			}
			else if(argData[0].contains("Add")){
				if(args != null && args[0].equals("ReaderWriter") && args.length == 5){
					cmdAdd(args);
				}
				else if(args != null && args.length == 2)
					cmdAdd(args);
				else
					Kernel.cPrintln(System.out, "Incorrect Format for Add.");
			}
			else if(argData[0].contains("Switch")){
				if(args != null && args.length == 1)
					cmdSwitch(args);
				else
					Kernel.cPrintln(System.out, "Incorrect Format for Switch Command.");
			}
		}
		catch (Throwable t){
			if (t instanceof ClassNotFoundException) {
				cPrintln(System.out,"ClassNotFoundException for " + argData[0]);
			} else if (t instanceof IOException) {
				cPrintln(System.out,"IOException for " + argData[0]);
			} else if (t instanceof InstantiationException) {
				cPrintln(System.out,"InstantiationException for " + argData[0]);
			} else if (t instanceof IllegalAccessException) {
				cPrintln(System.out,"IllegalAccessException for " + argData[0]);
			} else {
				cPrintln(System.out,"Thrown Exception for " + argData[0]);
				t.printStackTrace();
			}
		}
	}
	
	/**
	 * Implements the new command
	 * @param args arguments to new
	 * @return 0 - success
	 */
	private void cmdNew(String[] bName) {
		// Add a Batch to the listOfBatches
		String name = bName[0];
		if(listOfBatches.get(name) != null){
			cPrintln(System.out,"Batch Already Exists.");
		}
		else{
			listOfBatches.put(name, new ProcessList(name));
			runList = listOfBatches.get(name);
			cPrintln(System.out,"Batch " + name + " initialized.");
		}
	}
	
	/**
	 * Implements the run command
	 * @param fOutName output file
	 * @param timeOut maximum time this process can run
	 * @return 0 - batch started
	 */
	public void cmdRun(String fOutName, int timeOut) {
		int timeRun = timeOut;
		if (timeRun < 0){
			cPrintln(System.out, "ERROR: Run time of process must be positive number.");
		}
		else if(timeRun == 0){
			timeRun = Integer.MAX_VALUE/1000;
			BatchThread bThread = new BatchThread(this.cli,fOutName,timeRun * 1000, runList);
			bThread.start();
			cPrintln(System.out, "Batch Started.");
		}
		else if(timeRun > 0){
			BatchThread bThread = new BatchThread(this.cli,fOutName,timeRun * 1000, runList);
			bThread.start();
			cPrintln(System.out, "Batch Started.");
		}
	}
	
	private void cmdPriority(String[] args)throws ClassNotFoundException, IOException,
	InstantiationException, IllegalAccessException{
			int newPriority = Integer.parseInt(args[1]);
			if (newPriority < Thread.MIN_PRIORITY || newPriority > Thread.MAX_PRIORITY-1){
				cPrintln(System.out, "ERROR: Priority must be between: " + Thread.MIN_PRIORITY + "-" + (Thread.MAX_PRIORITY-1));
			}
			else{
				runList.setPriority(Long.parseLong(args[0]), newPriority);
				cPrintln(System.out, runList.toString());
			}
	}
	
	private void cmdCat(String[] args){
		String strVar = null;
		StringBuffer strBuffer = new StringBuffer();
		try{
			File file = new File(args[0]);
			BufferedReader in = new BufferedReader(new FileReader(file.getCanonicalPath()));
			while((strVar = in.readLine())!= null){
				strBuffer.append(strVar);
				strBuffer.append("\n");
			}
			in.close();
		}catch(IOException ioe){
			cPrintln(System.out, "ERROR: File does not Exist!");
		}
		cPrintln(System.out, strBuffer.toString());
	}
	
	private void cmdLogout(){
		System.exit(0);
	}
	
	private void cmdRemove(String args[]){
		runList.remove(Long.parseLong(args[0]));
		cPrintln(System.out,"Process removed");
	}
	
	private void cmdList(){
		Enumeration<ProcessList> ep = listOfBatches.elements();
		String batchList = "List of Batches: \n";
		while(ep.hasMoreElements()){
			batchList += ep.nextElement().toString() + "\n";
		}
		cPrintln(System.out,batchList);
	}
	
	private void cmdQueue(String[] args){
		if(listOfBatches.get(args[0]) != null){
			runList = listOfBatches.get(args[0]);
			cPrintln(System.out,runList.toString());
		}
		else{
			cPrintln(System.out,"Batch does not exist.");
		}
	}
	
	private void cmdSwitch(String[] args){
		if(listOfBatches.get(args[0]) != null){
			runList = listOfBatches.get(args[0]);
			cPrintln(System.out, "" + args[0] + " now active.");
		}
		else{
			cPrintln(System.out,"Batch does not exist.");
		}
	}
	
	private void cmdKill(String[] args){
		if(args[0]==null){
			cPrintln(System.out,"Please enter the name of the batch");
		}
		if(listOfBatches.containsKey(args[0]))
		{
			listOfBatches.remove(args[0]);
			Enumeration<ProcessList> e = listOfBatches.elements();
			if(e.hasMoreElements()){
				runList = e.nextElement();
			}else{
				runList = null;
			}
			cPrintln(System.out, args[0] + " Killed");
		}else{
			cPrintln(System.out, args[0] + " not found");
		}
	}
	
	private void cmdAdd(String[] args) throws ClassNotFoundException, IOException,
	InstantiationException, IllegalAccessException, InterruptedException{
		long pid = System.currentTimeMillis() % 100000;
		Process process = new Process(args, Thread.NORM_PRIORITY, pid);
		runList.enQueue(process);
		cPrintln(System.out,"process " + process.getName() + " added to batch.\n");
	}


}