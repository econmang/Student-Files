package lab3;

//Class for maintaining a doubly linked list of processors.
public class ProcessList
{  
	private Process head;
	private Process tail;
	
	// status of this batch job
	// use Process.RUNNING, etc., but this status means
	// the status of the entire batch
	private Stati status;
		
	private String bName;  // name of this batch
	
	public ProcessList(String bName) {
		this.bName = bName;
		head = tail = null;
		status = Stati.IDLE;
	}
	// a batchthread has started running this PL
	public void runStarted() {
		status = Stati.RUNNING;
	}
	public boolean isRunFinished() {
		return status==Stati.TERMINATED ||
				status==Stati.ABORTED;
	}
	// a batchthread has finished running this PL
	public void runFinished(Stati status) {
		this.status = status;
	}
	public Stati getStatus() {
		return status;
	}
	// Change priority
	public Process setPriority(long id, int priority) {
		Process process = find(id);
		if(process == null){
			return null;
		}
		else{
			process.setPriority(priority);
		}
		return process;
	}
	// retrieve name of this batch
	public String getName() {
		return bName;
	}
	
	public String toString() {
		String header = String.format("%-15s %-15s","Batch Name: ", getName());
		String batch = String.format("%-15s %-10s %-10s %-10s %-10s %-10s \n", "Name:", "ID:", "Status:",
				"RunTime:", "Priority:", "Arguments:");

		Process topProc = head();
		if (topProc == null)
			return header + "\n" + batch;
		while (topProc != null) {
			batch = batch + topProc.toString() + "\n";
			topProc = topProc.next;
		}
		return header + "\n" + batch;
	}
	// Check if queue is Empty.
	public boolean isEmpty() {
		if(head() == null){
			return true;
		}
		else
			return false;
	}     
	// Return the process at the head.
	public Process head() {
		return this.head;
	}        
	// Add process to the tail.
	public void enQueue(Process p) {
		if(head == null){
			head = tail = p;
		}
		else{
			tail.next = p;
			p.previous = tail;
			tail = p;
		}
	}
	
	public Process deQueue() {
		Process proc = head();
		head = head.next;
		return proc;
	}
	
	// Remove process from the list and return it
	public Process remove(long id) {
		Process proc = find(id);
		if(proc != null){
			if(proc == head()){
				head = proc.next;
				return proc;
			}
			else if(proc == tail){
				tail = proc.previous;
				tail.next = null;
				return proc;
			}
			else if(head.previous == null & head.next == null){
				head = tail = null;
				return proc;
			}
			else{
				proc.next.previous = proc.previous;
				proc.previous.next = proc.next;
				return proc;
			}
		}
		else{
			return proc;
		}
	} 
	// Find process in the queue and return it or null.
	public Process find(long id) {
		Process curr = head();
		while(curr != null){
			if(curr.getId() == id){
				return curr;
			}
			else{
				curr = curr.next;
			}
		}
		return curr;
	} 
}
