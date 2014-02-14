// $Id: Testable.java 14 2012-02-09 14:24:11Z cs671a $

package cs671.tester;

import java.lang.reflect.Method;

/** Testable classes.  Test methods are annotated with {@code Test}.
 *
 * @author  Michel Charpentier
 * @version 1.0, 02/08/12
 * @see Test
 */
public interface Testable {

  /** Executed before each test.  If this method fails or return
   * false, the corresponding test is not run.
   *
   * @param m the test method soon to be run
   */
  public boolean beforeMethod (Method m) throws Exception;

  /** Executed after each test.  This method runs after each test,
   * whether the test was successful or not.  It does not run if the
   * corresponding test was not run.
   *
   * @param m the test method that was just run
   */
  public void afterMethod (Method m) throws Exception;

}
