/*
 * Evan Conley, Jacob Cromwell, Michael Coley
 * 4/23/2017
 * Lab One
 * 
 * */

package lab3;

import java.io.PrintWriter;

public class Tower extends Program{
public Tower() { super("Tower of Hanoi"); }
	
	public final static long serialVersionUID = 1;
	
	@Override
	public int run(PrintWriter out, String[] args) 
			throws InterruptedException{
		
		long top = Long.parseLong(args[1]);
		if (top < 1){
			return(ILLEGAL_PARAMETER);
		}
		else{
			out.println("Tower of Hanoi Solution for: " + top + " disks");
			char from = 'A';
			char inter = 'B';
			char to = 'C';
			doTowers(out, top, from, inter, to);
			return 0;
		}
	}
	
	public void doTowers(PrintWriter out, long topN, char from, char inter, char to)
			throws InterruptedException {
	      if (topN == 1) {
	    	  this.schedule();
	          out.println("Disk 1 from " + from + " to " + to);
	      } else {
	    	  this.schedule();
	    	  doTowers(out, topN - 1, from, to, inter);
	    	  out.println("Disk " + topN + " from " + from + " to " + to);
	    	  doTowers(out, topN - 1, inter, from, to);
	      }
	   }
}