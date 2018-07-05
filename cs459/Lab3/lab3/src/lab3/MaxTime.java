package lab3;

public class MaxTime extends Thread {
	Thread thread;
	long timeLim;
	
	public MaxTime(Thread thread, long timeLim){
		this.thread = thread;
		this.timeLim = timeLim;
		this.setPriority(Thread.MAX_PRIORITY);
	}
	
	public void run(){
		try{
			if (timeLim > 0){
				Thread.sleep(this.timeLim);
				this.thread.interrupt();
				this.join(1000);
			}
			else if(timeLim == 0){
				;
			}
		}
		catch(InterruptedException ie){	
		}
	}
}
