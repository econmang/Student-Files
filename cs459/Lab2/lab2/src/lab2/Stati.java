package lab2;

/*	
A Process' or ProcessList's Status initially is IDLE. 
It goes to RUNNING when it begins to execute. 
If it completes normally it goes to TERMINATED. 
If it completes abnormally, it goes to ABORTED. 
WAIT theoretically indicates a process that is blocked 
(however, we won’t actually use this status in our implementation)
*/
public enum Stati {
	RUNNING,
	WAIT,
	IDLE,
	TERMINATED,
	ABORTED
	
	/* Originally in the Process class as
	public static final int RUNNING    = 0;
	public static final int WAIT       = 1;
	public static final int IDLE       = 2;
	public static final int TERMINATED = 3;
	public static final int ABORTED    = 4;
	*/
}
