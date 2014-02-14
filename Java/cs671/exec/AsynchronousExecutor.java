package cs671.exec;

import java.util.Collection;

public interface AsynchronousExecutor {
  /**
   * Terminates the executor and frees resources. It is invalid to call this
   * method while the executor is running, even from the thread that started the
   * computation.
   * 
   * @throws IllegalStateException
   *           if the executor is currently running.
   */
  void dispose() throws IllegalStateException;

  /**
   * 
   * @param callback
   *          instance to be called when the execution of all the tasks has
   *          completed. The callback object is then passed an array of errors
   *          and exceptions that caused tasks to abort. These are in the same
   *          order as tasks were in the collection. For successful tasks, the
   *          array contains null.
   * @param tasks tasks to be executed.
   * @throws IllegalStateException
   *           if the executor has previously been terminated with dispose or if
   *           the executor is already running.
   * 
   */
  void executeAsynchronously(CallBack callback,
      Collection<? extends Runnable> tasks)throws IllegalStateException;

  /**
   * Executor status. This method can be used to check whether a background
   * computation is still running.
   * 
   * @return true if the computation started by the previous call to
   *         executeAsynchronously is still running. This does not include
   *         callbacks (isAsynchronouslyRunning() == false while running a
   *         callback unless a new call to executeAsynchronously has taken
   *         place).
   */
  boolean isAsynchronouslyRunning();
}
