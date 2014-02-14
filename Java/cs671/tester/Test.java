// $Id: Test.java 14 2012-02-09 14:24:11Z cs671a $

package cs671.tester;

import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.ElementType;
import java.lang.annotation.Target;
import java.lang.annotation.Retention;

/** Test annotation.  This is the only annotation used in the system.
 *
 * @author  Michel Charpentier
 * @version 1.0, 02/08/12
 */
@Retention(RetentionPolicy.RUNTIME)
@Target({ElementType.METHOD})
public @interface Test {

  /** The weight of this test.  Tests with negative weight are silently
   * ignored. */
  double weight () default 1;

  /** A description of the test. */
  String info () default "";
}