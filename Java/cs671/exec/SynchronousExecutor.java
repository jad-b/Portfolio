package cs671.exec;

import java.util.Collection;

public interface SynchronousExecutor {
  /**
   * Terminates the executor and frees resources.
   */
  void dispose();

  /**
   * Executes a collections of tasks. The call is synchronous: this method
   * returns when all the tasks have been executed.
   * 
   * @param tasks
   * @return an array of errors and exceptions that caused tasks to abort. These
   *         are in the same order as tasks were in the collection. For
   *         successful tasks, the array contains null.
   * @throws InterruptedException
   * @throws IllegalStateException
   *           if the executor has previously been terminated with dispose.
   */
  Throwable[] execute(Collection<? extends Runnable> tasks)
      throws InterruptedException, IllegalStateException;
}
