package cs671.tester;

import java.io.PrintWriter;
import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.lang.reflect.Modifier;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.Comparator;
import java.util.List;

public class Tester {

  // ------------------------fields------------------------//
  private Collection<Class<? extends Testable>> classColl;
  private List<TestResult> testList = new ArrayList<TestResult>();
  private PrintWriter out = new PrintWriter(System.err, true);
  private boolean outputFlag = false; // flag for output
  private boolean runFlag = false; // True if tests have been run
  private String className;

  /**
   * Creates a tester for the given classes. Converts the array created by the
   * variable arguments into a List.
   */
  public Tester(Class<? extends Testable>... s) {
    classColl = Arrays.asList(s);
  }

  /**
   * Creates a tester for the given classes. Stores them in a List<Class<?
   * extends Testable>> format.
   * 
   */
  public Tester(Collection<Class<? extends Testable>> classes) {
    classColl = classes;
  }

  /**
   * Starts a console-based application. Command line arguments are the names of
   * the classes to be tested. The application produces a summary output of
   * tests that succeeded and tests that failed.
   * 
   * @param args
   * @param Tester
   */
  public static void main(String[] args) {
    try {
      Tester t;
      if (verifyClasses(args)) {
        t = new Tester(toClassList(args));
        t.run();
      }
    } catch (ClassNotFoundException e) {
      System.err.println(e.getMessage());
    }
  }

  /**
   * Runs the tests. All the classes are processed in the order in which they
   * were given. For each class, all the tests are run on the same instance in
   * order of the method names. If no instance can be created, the class is
   * skipped with an error message. If method beforeMethod fails or returns
   * false, the corresponding test is skipped with a warning message. After each
   * test, method afterMethod is run and a warning is displayed if it fails.
   * </p> In general, no-argument methods are valid test methods if they are
   * annotated, even when they are non-public or non-void. Inherited methods,
   * abstract methods, static method and methods that require arguments are
   * ignored. A warning is displayed if they are test-annotated.
   */
  public void run() throws IllegalStateException {
    if (runFlag)
      throw new IllegalStateException("run() has already been called.");
    runFlag = true;
    for (Class<? extends Testable> cTest : classColl)
      try {
        className = cTest.getName();
        Constructor<? extends Testable> conT = cTest.getDeclaredConstructor();
        conT.setAccessible(true);
        Testable t = conT.newInstance();
        Method[] tMethods = cTest.getDeclaredMethods();
        Arrays.sort(tMethods, new MethodComparator());
        Method.setAccessible(tMethods, true);
        for (Method m : tMethods)
          if (checkMethod(m))
            testMethod(m, t);
        if (outputFlag)
          output();
      }  catch(NullPointerException e) {
        System.err.println("ERROR: NullPointerException. " + className
                    + " " + e.getCause());
      }catch (IllegalArgumentException e) {      
        out.println("ERROR: IllegalArgumentException. " + className
            + " " + e.getCause());
      } catch (InstantiationException e) {
        out.println("ERROR: caught InstantiationException. " + className
            + " can not be opened: " + e.getCause());
      } catch (IllegalAccessException e) {
        out.println("ERROR: caught IllegalAccessException. " + className
            + " can not be opened: " + e.getCause());
      } catch (SecurityException e) {
        out.println("ERROR: run(): SetAccesssible request denied. "
            + e.getMessage());
      } catch (NoSuchMethodException e) {
        out.println("ERROR: caught NoSuchMethodException. " + className
            + " threw " + e.getCause());
      } catch (InvocationTargetException e) {
        out.println("ERROR: caught InvocationTargetException. "
            + className + " threw " + e.getCause());
      } catch (Throwable e) {// Catch-all
        out.println("ERROR: " + className + " threw " + e.getCause());
      }
  }

  /**
   * Sets the tester output. By default, the output is System.err. It is valid
   * to set the output to null, in which case the tester is completely silent.
   * 
   * @param w
   *          - the output for tester info; can be null
   */
  public void setPrintWriter(PrintWriter w) {
    out = w;
  }

  /**
   * Test results. This method returns a list that contains a TestResult object
   * for each test that was run (in the order the test method were actually
   * run). The returned list can be modified and modifications will affect
   * subsequent calls to getResults (i.e., this method does not make copies of
   * the list).
   */
  public List<TestResult> getResults() throws IllegalStateException {
    if (!runFlag)
      throw new IllegalStateException("run() has not been called.");
    else
      return testList;
  }

  // ================================================================//
  // =========================Helper Methods=========================//
  // ================================================================//
  /**
   * Verifies all classes passed through are valid for testing. Checks for both
   * ability to be loaded and that they are Testable. Returns true if all
   * classes passed are good.
   * 
   * @throws ClassNotFoundException
   */
  private static boolean verifyClasses(String... args)
      throws ClassNotFoundException {
    for (String s : args)
      try {
        Class<?> c = Class.forName(s);
        if (!Testable.class.isAssignableFrom(c)) {
          System.err.println("Class '" + s + "' is not Testable");
          return false;
        }
        // System.out.println(s + " is a class.");
      } catch (ClassNotFoundException e) {
        throw new ClassNotFoundException("class '" + s + "' is not loadable");
      }
    return true;
  }

  /**
   * Builds a Collection of Class objects from an array of class names. Strings
   * should've been previously verified loadable and Testable by
   * verifyClasses().
   * 
   * @param args
   *          The string array of class names.
   * @return A collection of Class(? extends Testable> objects, built from the
   *         passed string
   */
  private static Collection<Class<? extends Testable>> toClassList(
      String... args) {
    Collection<Class<? extends Testable>> list = new ArrayList<Class<? extends Testable>>();
    for (String s : args) {
      Class<?> c;
      try {
        c = Class.forName(s);
        Class<? extends Testable> cT = c.asSubclass(Testable.class);
        list.add(cT);
      } catch (ClassNotFoundException e) {
        System.err.println("toClassList: Class " + s + " could not be found"
            + ", but should've been verified by verifyClasses()");
      }
    }
    return list;
  }

  /**
   * Tests method for appropriate Test annotation and modifiers. Specifically,
   * must be non-static with no arguments.
   */
  private boolean checkMethod(Method m) {
    Class<?>[] arr = m.getParameterTypes();
    int mods = m.getModifiers();
    Test a = m.getAnnotation(Test.class);
    if (a == null)
      return false;
    else if (a.weight() < 0)
      return false;
    else if (arr.length != 0) {
      out.println("WARNING: " + m.getName() + " has parameters; ignored.");
      return false;
    }
    else if (Modifier.isStatic(mods)) {
      out.println("WARNING: " + m.getName() + " is static; ignored.");
      return false;
    }
    else if (Modifier.isAbstract(mods)) {
      out.println("WARNING: " + m.getName() + " is abstract; ignored.");
      return false;
    }
    else
      return true;
  }

  /**
   * Runs the test upon the method. If beforeMethod() fails or returns false,
   * the test is not run, and a warning is issued stating such. Saves the
   * results in the testList
   * 
   * @param m
   *          - the method to be tested.
   * @param t
   *          - the testable class object containing the method
   */
  private void testMethod(Method m, Testable t) {
    try {
      if (!t.beforeMethod(m)) {
        out.println("WARNING: " + m.getName()
            + " failed to initialize; ignored.");
        outputFlag = true;
        return;
      }
    } catch (Exception e) {
      out.println("WARNING: " + m.getName() + " failed to initialize;"
          + " ignoring.");
      return;
    }
    Result result = new Result();
    testList.add(result);
    // out.println(m.getName());

    Test a = m.getAnnotation(Test.class);
    if (a != null) {// Get annotation information
      result.setWeight(a.weight());
      result.setInfo(m.getName(), a.info());
    }

    long startTime = System.nanoTime();
    long endTime;

    try {
      m.invoke(t, new Object[0]);
      endTime = System.nanoTime();
    } catch (Throwable e) {
      endTime = System.nanoTime();
      result.saveError(e.getCause());
      result.setSuccess(false);
      outputFlag = true;
      // out.println("InvocationTargetException caught");
      // out.println("\tsuccess = false.");
    }

    long duration = endTime - startTime;
    result.setDuration(duration);
    // out.printf("\tduration = %d ns%n%n", duration);

    try {
      t.afterMethod(m);
    } catch (Exception e) {
      System.err.printf("Tester.testMethod(): Exception thrown by "
          + "%s.afterMethod(%s)%n", className, m.getName());
    }
  }

  /**
   * Outputs the test results, as per assignment 2's specifications. Outputs
   * successful tests, followed by failed tests, and produces a score.
   */
  private void output() {
    double good, all;
    good = all = 0;
    List<TestResult> bad = new ArrayList<TestResult>();

    out.println("SUCCESSFUL TESTS:");
    for (TestResult r : testList) {
      if (r.success()) {
        out.println(r);
        good += r.getWeight();
      }
      else
        bad.add(r);
      all += r.getWeight();
    }
    out.println("FAILED TESTS:");
    for (TestResult r : bad)
      out.println(r);
    // System.out.printf("Good = %f%nTotal = %f%n",good, all );
    out.printf("SCORE = %%%.2f%n", ((good / all) * 100));
  }

  // ================================================================//
  // =========================Inner Classes==========================//
  // ================================================================//
  /**
   * Encapsulating class for TestResult objects. Implements the set() methods to
   * complement the TestResult interface's get() methods. Also overrides
   * toString() to produce output().
   * 
   * @author jdb
   */
  class Result implements TestResult {

    private Throwable error = null;
    private double weight;
    private String info;
    private long time;
    private boolean success = true; // true by default

    /**
     * Sets error message.
     * 
     * @param e
     *          saved error/exception for message output
     */
    public void saveError(Throwable e) {
      error = e;
    }

    /**
     * Sets weight. Ignores negative weight by setting them to 0.
     * 
     * @param w
     *          - the weight of the test
     */
    public void setWeight(double w) {
      if (w < 0)
        weight = 0;
      else
        weight = w;
    }

    /**
     * Sets string info. Needs to be passed the method's full name and the value
     * of Test annotation info field.
     * 
     * @param mName
     *          - name of the method
     * @param aVal
     *          - additional info contained in the
     * @Test annotation
     */
    public void setInfo(String mName, String aVal) {
      info = className.concat("." + mName);
      if (!aVal.equals(""))
        info = info.concat(": " + aVal);
    }

    /**
     * Saves the duration of the test.
     * 
     * @param t
     *          - the length of the test. Measured from just before the invoke()
     *          call, and just after either an exception is thrown or successful
     *          exiting of the try/catch block
     */
    public void setDuration(long t) {
      time = t;
    }

    /**
     * Sets the success/failure flag
     * 
     * @param tf
     *          - boolean value for success flag
     */
    public void setSuccess(boolean tf) {
      success = tf;
    }

    /**
     * Outputs the testResult
     * 
     * @return String containing properly formatted Result for output.
     */
    public String output() {
      String s;
      if (success)
        s = String.format("  " + info + " (" + weight + ") in %f milliseconds",
                          (double) time / 1000000);
      else
        s = String.format("  " + info + " (" + weight + ") from " + error + "");
      return s;
    }

    /**
     * Override of toString(). Does not contain output() code to keep
     * flexibility
     * 
     * @return
     * @see Tester#output
     */
    @Override
    public String toString() {
      return output();
    }

    /**
     * Test failure.
     * 
     * @return the cause of test failure, or {@code null} if the test was
     *         successful
     */
    public Throwable error() {
      return error;
    }

    /**
     * Test duration. This is the duration of the test, in seconds, till
     * completion or up to the point of failure. It does not include time spent
     * inside {@code beforeMethod} and {@code afterMethod}.
     * 
     * @see Testable#beforeMethod
     * @see Testable#afterMethod
     */
    public double getDuration() {
      return (double) time / 1000000000f;
    }

    /**
     * Test info. If the info argument of the {@code Test} annotation of the
     * corresponding test method is not empty, then this is
     * {@code full-method-name + ": " + info}; otherwise, it is
     * {@code full-method-name}.
     * 
     * @see Test#info
     */
    public String getInfo() {
      return info;
    }

    /**
     * Test weight. This is the weight associated with the {@code Test}
     * annotation of the corresponding test method.
     * 
     * @see Test#weight
     */
    public double getWeight() {
      return weight;
    }

    /**
     * Test status.
     * 
     * @return true if the test was successful, false otherwise
     */
    public boolean success() {
      return success;
    }
  }

  /**
   * Comparator for Methods. Used by Arrays.sort in Tester.run().
   * 
   * @author jdb
   * @see Tester#run
   */
  class MethodComparator implements Comparator<Method> {
    @Override
    public int compare(Method m1, Method m2) {
      String s1 = m1.getName();
      String s2 = m2.getName();
      return s1.compareTo(s2);
    }
  }
}
