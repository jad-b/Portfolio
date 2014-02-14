package cs671.eval;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.net.Socket;
import java.util.Random;

/**
 * A client to connect to the EvalServer. Receives serialized work from the server over a
 * socket in the form of a EvalTask. It should confirm that the method signatures given
 * are valid, call them, and then send the results back to the server. If the method has no
 * return value, the object upon which methods were called should be returned.
 *
 * @author Jeremy Dobbins-Bucklad
 */
public class EvalClient implements Runnable {
    private static final String ERROR = "ERROR";
    /**
     * Hostname/IP address of the server
     */
    public String address;
    /**
     * Object representing connection to server
     */
    public Socket connection;
    /**
     * Input stream to server
     */
    public ObjectInputStream in;
    /**
     * Output stream from server
     */
    public ObjectOutputStream out;
    /**
     * Port number of server
     */
    public int port;
    private boolean initialized = false;

    /**
     * Creates an EvalClient
     *
     * @param a hostname or ip address of the server to connect to; @see {@link EvalClient#address}
     * @param p port of the specified server to connect through; @see {@link EvalClient#port}
     */
    public EvalClient(String a, int p) {
        address = a;
        port = p;
    }

    /**
     * Main method for running the client from command line. Creates a new client using
     * hostname/address and port given at command line. Starts the client in a new Thread.
     *
     * @param args command-line arguments passed to the program
     */
    public static void main(String[] args) {
        if (args.length < 2) {
            usage();
            throw new IllegalArgumentException("Insufficient arguments");
        }

        try {
            int p = Integer.parseInt(args[1]);
            EvalClient client = new EvalClient(args[0], p);
            client.initialize();
            new Thread(client, "EvalClient_" + (new Random().nextInt())).start();
        } catch (NumberFormatException nfe) {
            System.err.printf("%s: %s%n", "Bad argument", args[2]);
        }
    }

    /**
     * Instructions for running the program.
     */
    private static void usage() {
        System.out.println("EvalClient:\n" +
                "Invoke via the following command:" +
                "java cs671.eval.EvalClient <server address>  <server port #>" +
                "Where\n" +
                "\tserver address: Hostname or IP address of the server" +
                "\tport #: Port for the server to listen on");
    }

    /**
     * Sets up server connection. Initializes data streams. All exceptions are checked,
     * with error messages printed.
     */
    public void initialize() {
        try {
//            System.err.println("Client's grabbing connection");
            connection = new Socket(address, port);
//            System.err.println("Client connection made");
            out = new ObjectOutputStream(connection.getOutputStream());
            in = new ObjectInputStream(connection.getInputStream());
            initialized = true;
//            System.err.println("Client initialized");
        } catch (IOException e) {
            System.err.printf("%s: %s%n", e, "Error initializing client");
            e.printStackTrace();
        }
    }

    /**
     * For the method name and set of arguments args, the client attempts to find a method
     * with that signature. If none is found, it returns an error String to notify the server
     * of the problem. If the method is found, the client invokes it and returns the result.
     * For methods with no return value, the target is returned, under the assumption that
     * the method likely altered it.
     *
     * @param c      Class to be searched for methods.
     * @param target Object to invoke the method upon
     * @param name   name of the method
     * @param args   method parameters to be used through reflection
     */
    public Object doTask(Class c, Object target, String name, Object[] args) {
        try {
//            System.err.printf("Client.doTask: Looking for method %s in %s%n", name, c);
            Method[] methods = c.getMethods();
            Method rightMethod = null;
            for (Method m : methods) {
                if (m.getName().equals(name) && checkMethod(name, m, args)){
                    rightMethod = m;
                    break;
                }
            }
            if (rightMethod == null)
                return String.format("No method found by name %s", name);
//            System.err.printf("Client: invoking %s%n", name);
            Object result = rightMethod.invoke(target, args);
            return (result == null) ? target : result;
        } catch (InvocationTargetException e) {
            System.err.printf("%s: %s%n", e, "Failed to invoke " + name);
        } catch (IllegalAccessException e) {
            System.err.printf("%s: %s%n", e, "Failed to access");
        }
        return ERROR;
    }

    /**
     * Searches the Method declaration through reflection, determining if it is valid
     * given the supplied arguments.
     *
     * @param name of the method to be checked
     * @param m    {@link java.lang.reflect.Method} to be inspected
     * @param args parameters to be inspected against.
     * @return boolean indicating if the method matches the name and arguments
     */
    public boolean checkMethod(String name, Method m, Object[] args) {
        /**Class notes
         * Check arguments as their class types (String.class) &
         * their String.TYPE for primitive types
         * Basically, check twice in case it's a primitive type
         * that the usual thing doesn't.
         *
         * if method's parameter type is primitive
         *  check whether arg has TYPE field
         *  check whether TYPE equals primitive type
         *
         *  use isAssignableFrom() for checking Class Types
         */
//        System.err.println("Client: checking method " + m.getName());
        // Retrieve parameters to this method
        Class[] paramTypes = m.getParameterTypes();
        if (args.length != paramTypes.length) {
//            System.err.printf("\tcheckMethod: Argument(%d) and parameter(%d) lists of different lengths%n",
//                    args.length, paramTypes.length);
            return false;
        }
        for (int i = 0; i < paramTypes.length; i++) {
            Class<?> pCls = paramTypes[i];
            Class<?> argClass = args[i].getClass();
//            System.err.printf("Comparing %s to %s%n", pCls, argClass);
            if (!pCls.isAssignableFrom(argClass)) { // Try normal
//                System.err.printf("Checking if %s is primitive%n",pCls);
                if (pCls.isPrimitive()) {
//                    System.err.println("\tHave primitive: " + pCls);
                    try {
                        Field primType = argClass.getField("TYPE");
                        primType.setAccessible(true);
                        Class<?> primClass = (Class) primType.get(null);
//                        System.err.println("primClass is " + primClass);
                        if (!pCls.equals(primClass))
                            return false;
                    } catch (NoSuchFieldException e) {
                        System.err.printf("%s: %s%n", e, "Error; no Field found by name TYPE");
                        return false;
                    } catch (SecurityException e) {
                        System.err.printf("%s: %s%n", e, "Java didn't like that");
                        return false;
                    } catch (IllegalAccessException e) {
                        System.err.printf("%s: %s%n", e, "");
                        return false;
                    }
                } else {
                    return false;
                }
            }
        }
        return true;
    }

    /**
     * Main loop of the client.
     * Uses the checkWork method to test whether there is more work to be done.
     * If there is more work, receives a serialized EvalTask from the server.
     * Uses doTask to invoke each method and sends the result or relevant error message
     * to the server.
     * When no work remains or the connection is closed, client exits.
     * Handles all exceptions gracefully, printing a descriptive error message, sending an error
     * message String notifying the server of the problem, and moving on to the next method or task.
     */
    @Override
    public void run() {
        if (!initialized)
            throw new IllegalStateException("Client not initialized");

        while (checkWork()) {
            try {
                EvalTask task = getWork();
                Class taskClass = task.target.getClass();
                for (int i = 0; i < task.methods.length; i++) {
                    String name = task.methods[i];
                    Object[] args = task.args[i];
                    try {
                        out.writeObject(doTask(taskClass, task.target, name, args));
                        out.flush();
//                        System.err.println("Client: Sent results to server");
                    } catch (IOException e) {
                        System.err.printf("%s: %s%n", e, "Failed to send to server");
                    }
                }
            } catch (Exception e) {
                System.err.printf("Error while running; %s%n", e.getCause());
                e.printStackTrace();
            }
        }
//        System.err.println(Thread.currentThread().getName() + " shutting down");
    }

    /**
     * Asks the server whether more work is available by sending the String "hasWork", and
     * receiving a Boolean value of either true or false. Handles ClassNotFoundException and
     * IOException gracefully, printing an error message. If an exception is encountered, the
     * method returns false.
     *
     * @return boolean indicating if the server has work to do.
     * @throws IllegalStateException if client has not been initialized
     */
    public boolean checkWork() {
        if (!initialized)
            throw new IllegalStateException("Client not initialized");

        boolean isWork = false;
        try {
            out.writeObject("hasWork");
//            System.err.println("Client: hasWork?");
            isWork = in.readBoolean();
//            System.err.printf("Client: Server says %b%n", isWork);
        } catch (IOException e) {
            System.err.printf("%s: %s%n", e, "CheckWork: Stream I/O failed");
            //e.printStackTrace();
        }
        return isWork;
    }

    /**
     * Receives new work from the server, confirms it is a valid EvalTask, and casts it in
     * order to return it. Handles ClassNotFoundException and IOException gracefully,
     * printing an error message.
     *
     * @return {@link cs671.eval.EvalTask} received from the server; @see EvalServer.
     */
    public EvalTask getWork() {
        try {
            //            System.err.println("Client: Read work from server");
            return (EvalTask) in.readObject();
        } catch (IOException e) {
            System.err.printf("%s: %s%n", e, "Client closed");
            e.printStackTrace();
        } catch (ClassNotFoundException e) {
            System.err.printf("%s: %s%n", e, "Unable to cast to EvalTask");
            e.printStackTrace();
        }
        return null;
    }
}
