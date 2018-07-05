package lab3;

import java.io.*;
import java.util.LinkedList;
import java.util.Random;

public class ReaderWriter extends Program {

	public DataLock dl[];
	public LinkedList<Thread> threads;
	public int records;
	public int numberWriters;
	public int numberReaders;
	public int numberIterations;

	private static final long serialVersionUID = 1L;

	public ReaderWriter() throws InterruptedException {
		super("Reader/Writer");
	}

	@Override
	public int run(PrintWriter out, String[] args) throws InterruptedException {
		numberWriters = Integer.parseInt(args[2]);
		numberReaders = Integer.parseInt(args[1]);
		numberIterations = Integer.parseInt(args[3]);
		records = Integer.parseInt(args[4]);
		dl = new DataLock[Integer.parseInt(system("size"))];
		for (int i = 0; i < dl.length; i++) {
			dl[i] = new DataLock();
		}
		threads = new LinkedList<>();
		for (int i = 0; i < numberReaders; i++) {
			threads.push(new Reader(dl, out, numberIterations, i));
		}
		for (int i = 0; i < numberWriters; i++) {
			threads.push(new Writer(dl, out, numberIterations, i));
		}
		for (Thread thread : threads) {
			thread.start();
		}
		for (Thread thread : threads) {
			try {
				thread.join();
			} catch (InterruptedException e) {
			}
		}
		return 0;
	}
	
	@Override
	public void terminate(){
		Kernel.cPrintln(System.out, "Process Aborted");
		Thread[] ts = new Thread[numberReaders + numberWriters];
		for(int i = 0; i < numberReaders; i++){
			ts[i] = threads.pop();
		}
		for(int i = numberReaders-1; i < numberWriters+numberReaders; i++){
			ts[i] = threads.pop();
		}
		for(Thread thread : ts){
			try {
				schedule();
				thread.join();
			} catch (InterruptedException e) {
				
			}
		}
	}

	class Reader extends Thread {
		private DataLock[] dl;
		private int iteration, readerID;
		private PrintWriter out;
		private Random rand;
		private int index;

		public Reader(DataLock[] dl, PrintWriter out, int iteration, int readerID) {
			this.dl = dl;
			this.out = out;
			this.iteration = iteration;
			this.readerID = readerID;
		}

		public void run() {

			for (int i = 0; i < iteration; i++) {

				rand = new Random();
				index = rand.nextInt(dl.length);
				int last = (index + records) % dl.length;
				for (int j = index; j != last; j = ((j + 1) % dl.length)) {
					try {
						dl[j].acquireRead();
					} catch (InterruptedException e) {
						// TODO Auto-generated catch block
						out.println("Thread Reader " + readerID + " interrupted on acquire.");
					}
					out.println("Thread Reader " + readerID + " locked record " + j + " for read");

				}

				for (int j = index; j != last; j = ((j + 1) % dl.length)) {
					out.println("Thread Reader " + readerID + " read " + j + " value = " + system("read " + j));
				}

				for (int j = index; j != last; j = ((j + 1) % dl.length)) {
					try {
						dl[j].releaseRead();
					} catch (InterruptedException e) {

						out.println("Thread Reader " + readerID + "Interrupted on release");
					}
					out.println("Thread Reader " + readerID + " released record " + j + " for read.");

				}

				try {
					schedule();
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}

			}
		}
	}

	class Writer extends Thread {
		private DataLock[] dl;
		private int iteration, writerID;
		private PrintWriter out;
		private Random random;
		private int index;

		public Writer(DataLock[] dl, PrintWriter out, int iteration, int writerID) {
			this.dl = dl;
			this.iteration = iteration;
			this.writerID = writerID;
			this.out = out;
		}

		public void run() {

			for (int i = 0; i < iteration; i++) {
				random = new Random();
				index = random.nextInt(dl.length);
				int last = (index + records) % dl.length;
				int randwrite = random.nextInt(dl.length);
				for (int j = index; j != last; j = ((j + 1) % dl.length)) {
					try {
						dl[j].acquireWrite();
					} catch (InterruptedException e) {
						// TODO Auto-generated catch block
						out.println("Thread Writer " + writerID + " interrupted on acquire.");
					}
					out.println("Thread Writer " + writerID + " locked record " + j + " for write");
				}
				for (int k = index; k != last; k = ((k + 1) % dl.length)) {
					system("write " + k + " " + randwrite);
					out.println("Thread Writer " + writerID + " wrote " + k + " value = " + randwrite);
				}

				for (int k = index; k != last; k = ((k + 1) % dl.length)) {

					try {
						dl[k].releaseWrite();
					} catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					out.println("Thread Writer " + writerID + " released record " + k + " for write.");
				}
				try {
					schedule();
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		}
	}
}