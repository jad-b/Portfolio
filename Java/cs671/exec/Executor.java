package cs671.exec;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import java.util.Random;

/**
 * Executors. These executors offer synchronous and asynchronous task execution.
 * They are not thread-safe. In particular, it is illegal to call an executor
 * method while the executor is running, except that isAsynchronouslyRunning can
 * be called by the same thread that previously called executeAsynchronously.
 *
 * @author jdb
 * @version 1.0
 * @since 27Feb2012
 */

public class Executor implements AsynchronousExecutor, SynchronousExecutor {
  /**
   * Creates a full executor from an asynchronous executor. All tasks are
   * executed by the underlying asynchronous executor. This method is optional.
   *
   * @param exec
   * @return
   * @throws UnsupportedOperationException
   */
  public static Executor completeExecutor(AsynchronousExecutor exec)
      throws UnsupportedOperationException {
    return null;
  }

  /**
   * Creates a full executor from a synchronous executor. All tasks are executed
   * by the underlying synchronous executor. This method is optional.
   *
   * @param exec
   * @return
   */
  public static Executor completeExecutor(SynchronousExecutor exec)
      throws UnsupportedOperationException {
    return null;
  }

  /**
   * Creates a new bounded parallel executor. With each call to execute or
   * executeAsynchronously, this executor creates at most bound threads from the
   * factory; these threads execute all the tasks in parallel and terminate.
   *
   * @param f
   * @return
   */
  public static Executor newBoundedExecutor(ThreadFactory f, int size) {
    return new BoundedExecutor(f, size);
  }

  /**
   *
   *
   * @param f
   *          the thread factory; null is a valid value (no factory is used in
   *          that case)
   * @return
   */
  public static Executor newParallelExecutor(ThreadFactory f) {
    return new ParallelExecutor(f);
  }

  /**
   * Creates a new pool parallel executor. This executor maintains a pool of at
   * most size threads created from the factory. Each call to execute or
   * executeAsynchronously reuses existing pool threads (and/or creates new
   * ones, up to size). The pool threads execute the tasks in parallel, after
   * which they return to the pool (they do not terminate). Pool threads are
   * terminated when dispose is called.
   *
   * @param f
   *          the thread factory; null is a valid value (no factory is used in
   *          that case)
   * @param the
   *          maximum number of threads used to execute the tasks; must be at
   *          least 1.
   * @return
   */
  public static Executor newPoolExecutor(ThreadFactory f, int poolSize) {
    return new PoolExecutor(f, poolSize);
  }

  /**
   * Creates a new sequential executor. With each call to execute or
   * executeAsynchronously, this executor creates 1 new thread from the factory;
   * this thread executes all the tasks sequentially (in the order of the
   * collection) and terminates.
   *
   * @param exec
   * @return
   * @throws UnsupportedOperationException
   */
  public static Executor newSequentialExecutor(final ThreadFactory f)
      throws UnsupportedOperationException {
    return new SequentialExecutor(f);
  }

  protected boolean disposed = false;
  protected boolean running = false;
  protected boolean asyncRunning = false;
  protected ThreadFactory tf;

  Executor(ThreadFactory f) {
    tf = f;
  }

  /**
   * Terminates the executor and frees resources.
   */
  public void dispose() {
    if (running || asyncRunning)
      throw new IllegalStateException();
    else
      disposed = false;
  }

  /**
   * Executes a collections of tasks. The call is synchronous: this method
   * returns when all the tasks have been executed.
   *
   * @param tasks
   * @return
   * @throws InterruptedException
   */
  public synchronized Throwable[] execute(Collection<? extends Runnable> tasks)
      throws InterruptedException {
    return null;
  }

  /**
   * Executes a collections of tasks. The call is asynchronous: this method
   * returns immediately and the tasks continue to run in the background.
   *
   * @param cb
   * @param tasks
   */
  public void executeAsynchronously(CallBack callback,
      Collection<? extends Runnable> tasks) throws IllegalStateException {
    return;
  }

  /**
   * Executor status. This method can be used to check whether a background
   * computation is still running.
   *
   * @return
   */
  public synchronized boolean isAsynchronouslyRunning() {
    return asyncRunning;
  }
}

/**
 * With each call to execute or executeAsynchronously, this executor creates at
 * most bound threads from the factory; these threads execute all the tasks in
 * parallel and terminate.
 *
 * @author jdb
 *
 */
class BoundedExecutor extends Executor {
  int maxThreads;

  BoundedExecutor(ThreadFactory f, int n) {
    super(f);
    maxThreads = n;
  }

  @Override
  public synchronized Throwable[] execute(Collection<? extends Runnable> tasks)
      throws InterruptedException {
    if (running || asyncRunning)
      throw new IllegalStateException("BoundedExecutor already running");
    if (disposed)
      throw new IllegalStateException("BoundedExecutor has been disposed.");

    running = true;

    int n = Math.min(maxThreads, tasks.size());// Get smaller of two values
    Throwable[] errors = new Throwable[tasks.size()];// error array
    Thread[] runners = new Thread[n];
    Dispatcher disp = new Dispatcher(tasks);

    for (int i = 0; i < n; i++) {
      if (tf != null)// use thread factory if available
        runners[i] = tf.newThread(new Runner(disp, errors));
      else
        runners[i] = new Thread(new Runner(disp, errors));
      runners[i].start();
    }

    for (Thread t : runners)
      t.join();

    running = false;
    return errors;
  }

  @Override
  public synchronized void executeAsynchronously(final CallBack callback,
      final Collection<? extends Runnable> tasks) throws IllegalStateException {
    if (running || asyncRunning)
      throw new IllegalStateException("BoundedExecutor already running");
    if (disposed)
      throw new IllegalStateException("BoundedExecutor has been disposed.");

    asyncRunning = true;

    new Thread("BoundedExecutor async monitor") {
      int n = Math.min(maxThreads, tasks.size());// Get smaller of two values
      Throwable[] errors = new Throwable[tasks.size()];// error array
      Thread[] runners = new Thread[n];
      Dispatcher disp = new Dispatcher(tasks);

      @Override
      public void run() {
        for (int i = 0; i < n; i++) {
          if (tf != null)// use thread factory if available
            runners[i] = tf.newThread(new Runner(disp, errors));
          else
            runners[i] = new Thread(new Runner(disp, errors));
          runners[i].start();
        }
        for (Thread t : runners)
          try {
            t.join();// wait for all threads to finish up.
          } catch (InterruptedException e) {
            System.err.println(t.getName() + " was interrupted on join(): "
                + e.getMessage());
          }
        asyncRunning = false;
        callback.call(errors);
      }
    }.start();
  }

  /**
   * Wraps thread functionality with a Dispatcher object for retrieval of new
   * tasks to execute.
   *
   * @author jdb
   *
   */
  class Runner implements Runnable {
    Dispatcher disp;
    Throwable[] errors;
    TaskWrap r;

    public Runner(Dispatcher disp, Throwable[] errors) {
      this.disp = disp;
      this.errors = errors;
    }

    public void run() {
      while (true) {// infinitely loop
        r = disp.getTask();
        if (r == null)// no more tasks to run
          break;// so exit
        try {
          // System.out.print(Thread.currentThread().getName() + ": ");
          r.run();
        } catch (Throwable e) {
          errors[r.getIndex()] = e;
        }
      }
    }
  }

  /**
   * Dispatcher model based off that which we did in class. Manages the tasks
   * passed to the BoundedExecutor, and evenly distributes them to requesting
   * threads. Once all tasks have been run, returns null.
   *
   * @author jdb
   *
   */
  class Dispatcher {
    Runnable[] tasks;
    int taskIndex;

    Dispatcher(Collection<? extends Runnable> tasks) {
      this.tasks = tasks.toArray(new Runnable[tasks.size()]);
    }

    synchronized public TaskWrap getTask() {
      if (taskIndex == tasks.length)
        return null;
      return new TaskWrap(tasks[taskIndex], taskIndex++);
    }
  }

  /**
   * Wraps the Runnable task so that it carries its index from the task list.
   *
   * @author jdb
   *
   */
  class TaskWrap implements Runnable {
    int index;
    Runnable r;

    public TaskWrap(Runnable r, int i) {
      index = i;
      this.r = r;
    }

    public void run() {
      r.run();
    }

    public int getIndex() {
      return index;
    }
  }
}

/**
 * Creates a new parallel executor. With each call to execute or
 * executeAsynchronously, this executor creates as many new threads from the
 * factory as there are tasks; these threads execute all the tasks in parallel
 * and terminate.
 *
 * @author jdb
 *
 */
class ParallelExecutor extends Executor {

  ParallelExecutor(ThreadFactory f) {
    super(f);
  }

  class TaskWrap implements Runnable {
    Runnable r;
    Throwable[] errors;
    int idx; // index into error array

    TaskWrap(Throwable[] t, Runnable rnr, int i) {
      errors = t;
      r = rnr;
      idx = i;
    }

    public void run() {
      try {
        r.run();
      } catch (Throwable e) {
        errors[idx] = e;
      }
    }
  }

  @Override
  public synchronized Throwable[] execute(Collection<? extends Runnable> tasks)
      throws InterruptedException {
    if (running || asyncRunning)
      throw new IllegalStateException("ParallelExecutor already running");
    if (disposed)
      throw new IllegalStateException("ParallelExecutor has been disposed.");

    Throwable[] errors = new Throwable[tasks.size()];
    Thread[] runners = new Thread[tasks.size()];
    Thread t;// Thread to join on

    int i = 0;
    for (Runnable r : tasks) {// assign each thread its task
      if (tf != null)
        t = runners[i] = tf.newThread(new TaskWrap(errors, r, i));
      else
        t = runners[i] = new Thread(new TaskWrap(errors, r, i));
      i++;
      t.start();
    }

    for (Thread x : runners)
      x.join();

    return errors;
  }

  @Override
  public synchronized void executeAsynchronously(final CallBack callback,
      final Collection<? extends Runnable> tasks) throws IllegalStateException {
    if (running || asyncRunning)
      throw new IllegalStateException("ParallelExecutor already running");
    if (disposed)
      throw new IllegalStateException("ParallelExecutor has been disposed.");

    asyncRunning = true;
    new Thread() {
      @Override
      public void run() {
        Throwable[] errors = new Throwable[tasks.size()];
        Thread[] runners = new Thread[tasks.size()];
        Thread t;

        int i = 0;
        for (Runnable r : tasks) {// assign each thread it's task
          if (tf != null)
            t = runners[i] = tf.newThread(new TaskWrap(errors, r, i));
          else
            t = runners[i] = new Thread(new TaskWrap(errors, r, i));
          i++;
          t.start();
        }

        for (Thread x : runners)
          try {
            x.join();
          } catch (InterruptedException e) {
            System.err.println(Thread.currentThread().getName()
                + " was interrupted: " + e.getMessage());
          }

        asyncRunning = false;
        callback.call(errors);
      }
    }.start();
  }
}

/**
 * This executor maintains a pool of at most size threads created from the
 * factory. Each call to execute or executeAsynchronously reuses existing pool
 * threads (and/or creates new ones, up to size). The pool threads execute the
 * tasks in parallel, after which they return to the pool (they do not
 * terminate). Pool threads are terminated when dispose is called.
 *
 * @author jdb
 *
 */
class PoolExecutor extends Executor {
  int poolSize;
  Thread[] runners;
  Throwable[] errors = null;
  Dispatcher disp = null;

  private class ThreadLock {
    private boolean active = false;
    private int activeThreads = 0;

    synchronized public void dec() {
      if (--activeThreads == 0)
        synchronized (mainLock) {
          mainLock.notify();// notify execute() supervisor thread
        }
    }

    synchronized public boolean isActive() {
      return active;
    }

    synchronized public void status(boolean a) {
      active = a;
    }
  }

  private class MainLock {}

  private final ThreadLock threadLock = new ThreadLock();
  private final MainLock mainLock = new MainLock();

  PoolExecutor(ThreadFactory f, int n) {
    super(f);
    if (n < 1)
      poolSize = 1;
    else
      poolSize = n;
    runners = new Thread[poolSize];

    for (int i = 0; i < poolSize; i++) {
      if (tf != null)
        runners[i] = tf.newThread(new Runner());
      else
        runners[i] = new Thread(new Runner());

      // System.out.println("Starting Thread " + i);
      runners[i].start();
    }// build and start all threads to 'wait' on disp
  }

  /**
   * Terminates the executor and frees resources.
   */
  @Override
  public void dispose() {
    // System.out.println("PoolExec.dispose() called");
    if (running || asyncRunning)
      throw new IllegalStateException();
    else
      synchronized (threadLock) {
        disposed = true;
        threadLock.notifyAll();
      }
  }

  class Runner implements Runnable {
    TaskWrap r;

    public void run() {
      while (!disposed) {

        synchronized (threadLock) {
          while (!threadLock.isActive() && !disposed)
            try {
              threadLock.wait();// wait until notified
            } catch (Throwable e) {
              System.err.printf("run.WARNING: PoolExec %s interrupted: %s%n",
                                Thread.currentThread().getName(),
                                e.getMessage());
            }
        }
        while ((r = disp.getTask()) != null)
          try {
            r.run();
            System.err.println(Thread.currentThread().getName()
                + " running task.");
          } catch (Throwable e) {
            if (errors == null)
              System.err.println(Thread.currentThread().getName()
                  + " has a null 'errors' array");
            errors[r.getIndex()] = e;
          }
      }
    }
  }

  /**
   * Dispatcher model based off that which we did in class. Manages the tasks
   * passed to the BoundedExecutor, and evenly distributes them to requesting
   * threads. Once all tasks have been run, returns null.
   *
   * @author jdb
   *
   */
  class Dispatcher {
    Runnable[] tasks;
    int taskIndex;
    int ThreadCount;

    Dispatcher(Collection<? extends Runnable> tasks) {
      this.tasks = tasks.toArray(new Runnable[tasks.size()]);
    }

    synchronized public TaskWrap getTask() {
      if (taskIndex == tasks.length) {
        threadLock.status(false);// 'wait' pool threads signal
        threadLock.dec();
        return null;
      }
      return new TaskWrap(tasks[taskIndex], taskIndex++);
    }

    synchronized public boolean hasTask() {
      return taskIndex < tasks.length;
    }
  }

  /**
   * Wraps the Runnable task so that it carries its index from the task list.
   *
   * @author jdb
   *
   */
  class TaskWrap implements Runnable {
    int index;
    Runnable r;

    public TaskWrap(Runnable r, int i) {
      index = i;
      this.r = r;
    }

    public void run() {
      r.run();
    }

    public int getIndex() {
      return index;
    }
  }

  @Override
  public synchronized Throwable[] execute(Collection<? extends Runnable> tasks)
      throws InterruptedException {
    if (running || asyncRunning)
      throw new IllegalStateException("PoolExecutor already running");
    if (disposed)
      throw new IllegalStateException("PoolExecutor has been disposed.");
    running = true;

    disp = new Dispatcher(tasks);
    errors = new Throwable[tasks.size()];
    threadLock.activeThreads = poolSize;

    synchronized (threadLock) {// Wake waiting pool threads
      threadLock.status(true);
      threadLock.notifyAll();
    }
    synchronized (mainLock) {// Wait on separate lock
      while (disp.hasTask() && threadLock.activeThreads != 0)
        // while tasks are available and threads are working
        mainLock.wait();
    }

    running = false;
    return errors;
  }

  @Override
  public synchronized void executeAsynchronously(final CallBack callback,
      final Collection<? extends Runnable> tasks) throws IllegalStateException {
    if (running || asyncRunning)
      throw new IllegalStateException("PoolExecutor already running.");
    if (disposed)
      throw new IllegalStateException("PoolExecutor has been disposed.");

    asyncRunning = true;

    new Thread("PoolExec Async Monitor") {
      @Override
      public void run() {
        disp = new Dispatcher(tasks);
        errors = new Throwable[tasks.size()];
        threadLock.activeThreads = poolSize;

        synchronized (threadLock) {// Wake waiting pool threads
          threadLock.status(true);
          threadLock.notifyAll();
        }
        synchronized (mainLock) {// Wait on separate lock
          try {
            mainLock.wait();
          } catch (InterruptedException e) {
            e.printStackTrace();
          }
        }

        asyncRunning = false;
        callback.call(errors);
      }
    }.start();
  }
}

/**
 * Creates a new sequential executor. With each call to execute or
 * executeAsynchronously, this executor creates 1 new thread from the factory;
 * this thread executes all the tasks sequentially (in the order of the
 * collection) and terminates.
 *
 * @author jdb
 *
 */
class SequentialExecutor extends Executor {

  /** Simple constructor */
  SequentialExecutor(ThreadFactory f) {
    super(f);
  }

  /** Provides a wrapper for Runnable tasks that adds error handling */
  class TaskWrap implements Runnable {// class for error handling
    Collection<? extends Runnable> tasks;
    Throwable[] errors;

    TaskWrap(Collection<? extends Runnable> t, Throwable[] e) {
      tasks = t;
      errors = e;
    }

    public void run() {
      int i = 0;
      for (Runnable r : tasks)
        try {
          r.run();// run the task
        } catch (Throwable e) {
          errors[i] = e;
        } finally {
          i++;
        }
    }
  }

  @Override
  public synchronized Throwable[] execute(Collection<? extends Runnable> tasks)
      throws InterruptedException {
    if (running || asyncRunning)
      throw new IllegalStateException("SequentialExecutor already running.");
    if (disposed)
      throw new IllegalStateException("SequentialExecutor has been disposed");
    running = true;

    Throwable[] errors = new Throwable[tasks.size()];// error array
    Thread t;// Single thread to be used

    if (tf != null)// use thread factory if available
      t = tf.newThread(new TaskWrap(tasks, errors));
    else
      t = new Thread(new TaskWrap(tasks, errors), "SeqThread");

    t.start();
    t.join();// Wait for thread to die.

    running = false;
    return errors;
  }

  @Override
  public synchronized void executeAsynchronously(final CallBack callback,
      final Collection<? extends Runnable> tasks) throws IllegalStateException {
    if (running || asyncRunning)
      throw new IllegalStateException("SequentialExecutor already running.");
    if (disposed)
      throw new IllegalStateException("SequentialExecutor has been disposed");
    asyncRunning = true;

    new Thread("SeqExec Async Monitor") {
      @Override
      public void run() {
        // Begin excerpt from execute()
        Throwable[] errors = new Throwable[tasks.size()];// error array
        Thread t;// Single thread to be used

        if (tf != null)// use thread factory if available
          t = tf.newThread(new TaskWrap(tasks, errors));
        else
          t = new Thread(new TaskWrap(tasks, errors));

        t.start();

        try {
          t.join();
        } catch (InterruptedException e) {
          System.err.println(Thread.currentThread().getName()
              + " interrupted on " + t.getName() + ".join(): " + e.getCause());
        }
        // End: excerpt from execute()
        asyncRunning = false;
        callback.call(errors);
      }
    }.start();
  }
}

class ExecTester {
  static long time;

  public static void main(String[] args) throws InterruptedException {
    class Factory implements ThreadFactory {
      // int max = 10;
      int count = 0;

      public Thread newThread(final Runnable r) {
        return new Thread(r, "Thread #" + (count++)) {
          @Override
          public void run() {
            // System.out.println(getName() + " running");
            r.run();

          }
        };
      }
    }

    class Task implements Runnable {
      int num;
      Random rand = new Random();

      public Task(int n) {
        // System.out.printf("Task.Task(): Task %d created%n", n);
        num = n;
      }

      public void run() {
        System.out.println(Thread.currentThread().getName() + ": " + num);
        if (num % 7 == 3)
          throw new Error("Did You Know: " + num + " % 7 has remainder 3.");
        try {
          int sleepTime = rand.nextInt(500);
          // System.out.println("Sleeping "+sleepTime);
          Thread.sleep(sleepTime);// sleep for a random time <= sleepTime
        } catch (InterruptedException e) {
          System.err.println(Thread.currentThread().getName()
              + " was awoken from " + "it's sleep: " + e.getMessage());
        }
      }
    }
    System.out.println("Running ExecTester");
    int testSize = 100;

    List<Runnable> tasks = new ArrayList<Runnable>(testSize);
    for (int i = 0; i < testSize; i++)
      tasks.add(new Task(i));

    CallBack cb = new CallBack() {
      public void call(Throwable[] errors) {
        time = System.nanoTime() - time;
        System.out.printf("time: %f ms%n", time / 1e9);
        System.out.printf("Callback%n");
        for (int i = 0; i < errors.length; i++)
          if (errors[i] != null)
            System.out.println(errors[i] + " at index " + i);
        System.out.println("*********************");
      }
    };
    /*
     * Executor exec = Executor.newSequentialExecutor(new Factory()); try {
     * Throwable[] errors = exec.execute(tasks); for (int i = 0; i <
     * errors.length; i++) if (errors[i] != null) System.out.println(errors[i] +
     * " at index " + i); System.out.println("Back ... to the main.");
     * System.out.println("*********************"); } catch (Throwable e) {
     * System.err.println("Error running seqExec execute(): "+e.getCause()); }
     *
     *
     * try { //exec.executeAsynchronously(cb,tasks);
     * System.out.println("Back ... to the main."); } catch (Throwable e) {
     * System
     * .err.println("Error running seqExec executeAsync(): "+e.getCause()); }
     */

    /*
     * Executor parExec = Executor.newParallelExecutor(new Factory()); //test
     * execute try { Throwable[] errors = parExec.execute(tasks); for (int i =
     * 0; i < errors.length; i++) if (errors[i] != null)
     * System.out.println(errors[i] + " at index " + i);
     * System.out.println("Back ... to the main.");
     * System.out.println("*********************"); } catch (Throwable e) {
     * System.err.println("Error running parExec execute(): "+e.getCause()); }
     * //test execAsync try { parExec.executeAsynchronously(cb,tasks);
     * System.out.println("Back ... to the main."); } catch (Throwable e) {
     * System
     * .err.println("Error running parExec executeAsync(): "+e.getCause()); }
     */
    /*
     * Executor bndExec = Executor.newBoundedExecutor(new Factory(),3); try {
     * time = System.nanoTime(); Throwable[] errors = bndExec.execute(tasks);
     * time = System.nanoTime() - time;
     * System.out.printf("time: %f ms%n",time/1e9); for (int i = 0; i <
     * errors.length; i++) if (errors[i] != null) System.out.println(errors[i] +
     * " at index " + i); System.out.println("Back ... to the main.");
     * System.out.println("*********************"); } catch (Throwable e) {
     * System.err.println("Error running bndExec execute(): "+e.getCause()); }
     * //test execAsync try { time = System.nanoTime();
     * bndExec.executeAsynchronously(cb,tasks);
     * System.out.println("Back ... to the main."); } catch (Throwable e) {
     * System
     * .err.println("Error running bndExec executeAsync(): "+e.getCause()); }
     */

    Executor poolExec = Executor.newPoolExecutor(new Factory(), 10);
    Thread.sleep(100);
    try {
      time = System.nanoTime();
      Throwable[] errors = poolExec.execute(tasks);
      time = System.nanoTime() - time;
      System.out.printf("time: %f ms%n", time / 1e9);
      for (int i = 0; i < errors.length; i++)
        if (errors[i] != null)
          System.out.println(errors[i] + " at index " + i);
      System.out.println("Back ... to the main.");
      System.out.println("*********************");
    } catch (Throwable e) {
      System.err.println("Error running poolExec execute(): " + e.getCause());
    }
    try {
      time = System.nanoTime();
      poolExec.executeAsynchronously(cb, tasks);
      System.out.println("Back ... to the main.");
    } catch (Throwable e) {
      System.err.println("Error running poolExec executeAsync(): "
          + e.getCause());
    }

  }
}
