package dining;
 
import java.util.ArrayList;
import java.util.Random;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicInteger;
 
enum PhilosopherState { Get, Eat, Pon }
 
class Fork {
    public static final int ON_TABLE = -1;
    static int instances = 0;
    public int id;
    public AtomicInteger holder = new AtomicInteger(ON_TABLE);
 
    Fork() { id = instances++; }
}
 
class Philosopher implements Runnable {
    static final int maxWaitMs = 100;                          //  must be > 0
    static AtomicInteger token = new AtomicInteger(0);
    static int instances = 0;
    static Random rand = new Random();
    AtomicBoolean end = new AtomicBoolean(false);
    int id;
    PhilosopherState state = PhilosopherState.Get;
    Fork left;
    Fork right;
    int timesEaten = 0;
 
    Philosopher() {
        id = instances++;
        left = MainPhil.forks.get(id);
        right = MainPhil.forks.get((id+1)%MainPhil.philosopherCount);
    }
 
    void sleep() { try { Thread.sleep(rand.nextInt(maxWaitMs)); }
        catch (InterruptedException ex) {} }
 
    void waitForFork(Fork fork) {
        do {
            if (fork.holder.get() == Fork.ON_TABLE) {
                fork.holder.set(id);                //  my id shows I hold it
                return;
            } else {                                //  someone still holds it
                sleep();                            //  check again later
            }
        } while (true);
    }
 
    public void run() {
        do {
            if (state == PhilosopherState.Pon) {    //  all that pondering
                state = PhilosopherState.Get;       //  made me hungry
            } else { // ==PhilosopherState.Get
                if (token.get() == id) {            //  my turn now
                    waitForFork(left);
                    waitForFork(right);             //  Ah needs me some foahks!
                    token.set((id+2)% MainPhil.philosopherCount);
                    state = PhilosopherState.Eat;
                    timesEaten++;
                    sleep();                        //  eat for a while
                    left.holder.set(Fork.ON_TABLE);
                    right.holder.set(Fork.ON_TABLE);
                    state = PhilosopherState.Pon;   //  ponder for a while
                    sleep();
                } else {                    //  token.get() != id, so not my turn
                    sleep();
                }
            }
        } while (!end.get());
    }
}