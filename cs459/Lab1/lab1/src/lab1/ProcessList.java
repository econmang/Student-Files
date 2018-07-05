/*
 * Evan Conley, Jacob Cromwell, Michael Coley
 * 4/23/2017
 * Lab One
 * 
 * */

package lab1;

//Class for maintaining a doubly linked list of processors.
public class ProcessList
{  
	private Process     head;
	private Process     tail;
	
	public ProcessList() {
		head = tail = null;
	}	
	// Change priority
	public Process setPriority(long id, int priority) {
		Process proc = find(id);
		if (proc == null)
			return null;
		else
			proc.setPriority(priority);
		return proc;
	}
	public String toString() {
		String batch = String.format("%-15s %-10s %-10s %-10s %-10s %-10s \n", "Name:", "ID:", "Status:",
				"RunTime:", "Priority:", "Arguments:");
		Process peek = head();
		if(peek == null){
			return batch;
		}
		while(peek != null){
			batch = batch + peek.toString() + "\n";
			peek = peek.next;
		}
		return batch;
	}
	// Check if queue is Empty.
	public boolean isEmpty() {
		if (head() == null){
			return true;
		}
		else{
			return false;
		}
	}     
	// Return the process at the head.
	public Process head() {
		return this.head;
	}        
	// Add process to the tail.
	public void enQueue(Process proc) {
		if (head == null)
			head = tail = proc;
		else {
			tail.next = proc;
			proc.previous = tail;
			tail = proc;
		}
	}
	// Remove 1st process in the list and return it
	public Process deQueue() {
		Process proc = head();
		head = head.next;
		return proc;
	}       
	// Remove process from the list and return it
	public Process remove(long id) {
		Process proc = find(id);
		if (proc != null) {
			if (proc == head()) {
				head = proc.next;
				return proc;
			} else if (proc == tail) {
				proc.previous = tail;
				proc.previous.next = null;
				return proc;
			} 
			else if(head.previous == null & head.next == null){
				head = tail = null;
				return proc;
			}
				else {
				proc.next.previous = proc.previous;
				proc.previous.next = proc.next;
				return proc;
			}
			
		} else
			return proc;
	} 
	// Find process in the queue and return it or null.
	public Process find(long id) {
		Process curr = head();
		if(curr != null){
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