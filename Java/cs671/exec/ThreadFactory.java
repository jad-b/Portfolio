package cs671.exec;

public interface ThreadFactory {
  /**
   * Creates a new thread. When started, the thread will run the given behavior. 
   * @param behavior the purpose of the thread
   * @return thread to be run.
   */
  Thread newThread(Runnable behavior);

}
