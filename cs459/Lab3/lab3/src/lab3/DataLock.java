package lab3;

import java.util.concurrent.Semaphore;

public class DataLock {
	private int readers;
	private Semaphore db, mutex;
	
	public DataLock(){
		readers = 0;
		mutex = new Semaphore(1);
		db = new Semaphore(1);
	}
	
	public void acquireRead() throws InterruptedException{
		mutex.acquire();
		if(++readers==1)
			db.acquire();
		mutex.release();
	}
	
	public void releaseRead() throws InterruptedException{
		mutex.acquire();
		if(--readers==0)
			db.release();
		mutex.release();
	}
	
	public void acquireWrite() throws InterruptedException{
		db.acquire();
	}
	
	public void releaseWrite() throws InterruptedException{
		db.release();
	}

}

