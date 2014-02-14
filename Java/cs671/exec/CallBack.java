package cs671.exec;

public interface CallBack {
  /**
   * Callback. In general, there is no guarantees as to what thread initiates a
   * callback. Accordingly, this method should be designed in a thread-safe way.
   * 
   * @param errors
   *          failures associated with executed tasks.
   */
  void call(Throwable[] errors);
}
