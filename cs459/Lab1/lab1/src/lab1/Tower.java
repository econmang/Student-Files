/*
 * Evan Conley, Jacob Cromwell, Michael Coley
 * 4/23/2017
 * Lab One
 * 
 * */

package lab1;

import java.io.PrintWriter;

public class Tower extends Program{
public Tower() { super("Tower of Hanoi"); }
	
	public final static long serialVersionUID = 1;
	
	@Override
	public int run(PrintWriter out, String[] args) {
		
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
	
	public void doTowers(PrintWriter out, long topN, char from, char inter, char to) {
	      if (topN == 1) {
	         out.println("Disk 1 from " + from + " to " + to);
	      } else {
	         doTowers(out, topN - 1, from, to, inter);
	         out.println("Disk " + topN + " from " + from + " to " + to);
	         doTowers(out, topN - 1, inter, from, to);
	      }
	   }
	
	public static void main(String[] args){
		Tower h = new Tower();
		String[] ha = {"Tower","4"};
		PrintWriter pw = new PrintWriter(System.out, true); // true => flush each output
		h.run(pw, ha);
	}
}