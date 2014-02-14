package cs671.eval;

import java.io.*;
import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketTimeoutException;
import java.util.*;


/**
 * A server for remote computation. Listens on a given port for clients to connect and
 * creates new EvalConnection instances in new threads to communicate with each client.
 * When all work is done and no clients remain connected, the server shuts down.
 */
public class EvalServer implements Runnable {
    /**
     * Port the server's running on
     */
    public final int port;
    /**
     * Socket server's listening on
     */
    public ServerSocket serv;
    /**
     * List of clients connected to the server
     */
    public ArrayList<Thread> clients;
    /**
     * Results from clients' computations.
     */
    public ArrayList<Object> results;
    /**
     * List of work for clients
     */
    private LinkedList<EvalTask> work;
    /*Private Instance Variables*/
    private boolean initialized = false;


    /**
     * Builds an EvalServer instance.
     * Stores the {@code port} in its {@link EvalServer#port} field.
     * Port: Provided port to start on.
     */
    public EvalServer(int port) {
        if (port < 0 || port > 65535)
            throw new IllegalArgumentException("Invalid port number [0..65535].");
        this.port = port;
//        System.err.printf("Server's running on port %d%n", this.port);
    }

    /**
     * Prints out the command-line usage of the program
     */
    private static void usage() {
        System.out.printf("%s%n%s%n%s%n%s%n%s%n",
                "EvalServer",
                "Invoke via the following command:",
                "java cs671.eval.EvalServer <port #>  <work file>",
                "Where\n\tport #: Port for the server to listen on",
                "\twork file: Input file containing tasks");
    }

    /**
     * Main method for running the server from command line.
     * Creates a new server using the port and input file given at command line.
     * Reads the data structures and methods from the input file and adds them to the work list.
     * Starts the server in a new Thread.
     *
     * @param args command-line arguments passed to the program
     */
    public static void main(String[] args) {
        if (args.length < 2) {
            usage();
            throw new IllegalArgumentException("Insufficient arguments to program");
        }
        File workFile;
        try {
            // Setup server and open file
            EvalServer server = new EvalServer(Integer.parseInt(args[0]));
            server.initialize();
            workFile = new File(args[1]);

            readTasksFromFile(server.work, new FileInputStream(workFile));

            new Thread(server, "ServerThread").start();
        } catch (NumberFormatException e) {
            System.out.printf("%s%n", "Port number must be an integer");
        } catch (NullPointerException npx) {
            System.out.printf("%s not found%n", args[2]);
        } catch (FileNotFoundException e) {
            System.err.printf("%s: %s%n", e, "Could not locate file");
            e.printStackTrace();
        }
    }

    /**
     * Performs the complicated work of reading in tasks from files.
     *
     * @param work List to store instantiated EvalTasks to
     * @param in FileStream the tasks are read from.
     */
    private static void readTasksFromFile(LinkedList<EvalTask> work, FileInputStream in) {
        if (work == null || in == null)
            throw new IllegalArgumentException("null argument(s)");

        Scanner scan = new Scanner(in);
        while (scan.hasNext()) { // Task-level loop
            String line = scan.nextLine();
            String[] ds = line.split("\\s");
//            System.out.printf("Building %s<%s,%s>%n", ds[0], ds[1], ds[2]);
            try {
                String cName = "cs671.eval." + ds[0];
                //Build data structure
                Class<?> structType = Class.forName(cName);
                Object dStruct = structType.newInstance();
                //Get add method
                Method add = structType.getMethod("add",Comparable.class,Object.class);
                // Get key & val constructors
                Class<?> key = Class.forName("java.lang." + ds[1]);
                Constructor keyCtor = key.getConstructor(String.class);
                Class<?> val = Class.forName("java.lang." + ds[2]);
                Constructor valCtor = val.getConstructor(String.class);
                //Add nodes to data structure
                String nodeLine = scan.nextLine();
                String[] keyVals = nodeLine.split("&");
                assert( (keyVals.length & 0x1) == 0 ); // Should be an even number
                for( int i = 0; i < keyVals.length; i += 2 ){
//                    System.out.printf("Adding node <%s,%s>%n",keyVals[i],keyVals[i+1]);
                    add.invoke(dStruct,
                            keyCtor.newInstance(keyVals[i]),
                            valCtor.newInstance(keyVals[i+1]));
                }

                // Add methods and arguments
                List<String> methodNames = new ArrayList<>();
                List<List<Object>> methodArguments = new ArrayList<>();
                String methodLine;
                while( scan.hasNextLine() ){
                    methodLine = scan.nextLine();
                    if( methodLine.equals("") )
                        break;
                    String[] nameArgs = methodLine.split("\\s");
                    // Store method name
//                    System.out.printf("Adding method '%s'%n",nameArgs[0]);
                    methodNames.add(nameArgs[0]);
                    // Retrieve arguments
                    List<Object> arguments = new ArrayList<>();
                    methodArguments.add(arguments);
                    if( nameArgs.length < 2 ) // No-argument method
                        continue;
                    String[] args = nameArgs[1].split("&");
                    assert((args.length & 0x1) == 0); // Again, should be an even number
                    for( int i = 0; i < args.length; i += 2 ){
//                        System.out.printf("Adding argument (%s,%s)%n",args[i],args[i+1]);
                        Class c = Class.forName("java.lang."+args[i]);
                        Constructor<?> argCtor = c.getConstructor(String.class);
                        arguments.add(argCtor.newInstance(args[i+1]));
                    }
                }

                // Add everything into an EvalTask and then to our work list
                String[] mNames = methodNames.toArray(new String[methodNames.size()]);
                Object[][] args = new Object[methodArguments.size()][];
                for( int i = 0; i < args.length; i++ ){
                    List<Object> argArray = methodArguments.get(i);
                    args[i] = argArray.toArray(new Object[argArray.size()]);
                }
                EvalTask newTask = new EvalTask(dStruct, mNames, args);
                work.add(newTask);
//                System.out.printf("EvalTask created:%n%s%n",newTask);
            } catch (ClassNotFoundException e) {
                System.err.printf("%s: %s%n", "Could not locate class by name of", ds[0]);
            } catch (InstantiationException | IllegalAccessException | NoSuchMethodException e) {
                System.err.printf("%s: %s%n", e, "");
                e.printStackTrace();
            } catch (InvocationTargetException e) {
                System.err.printf("%s: %s%n", e, "Failed to add node to data structure");
                e.printStackTrace();
            }
        }
    }

    /**
     * Sets up the server for great things to come. Creates lists for tasks and clients,
     * and initializes the Socket. Finally, calls {@link EvalServer#run} to begin operations.
     *
     * @throws IllegalStateException if already initialized.
     */
    public void initialize() throws IllegalStateException {
        if (initialized)
            throw new IllegalStateException("Server already initialized");

        work = new LinkedList<>();
        clients = new ArrayList<>();
        results = new ArrayList<>();
        try {
            serv = new ServerSocket(port);
            serv.setSoTimeout(1000);
        } catch (IOException e) {
            System.err.printf("Could not open ServerSocket on %d%n", port);
            return;
        } catch (Exception e) {
            System.err.printf("Failed to open server socket: %s", e.toString());
            return;
        }

        initialized = true;
    }

    /**
     * Main loop of the server. While there is work to be done or clients are still connected,
     * it continues to listen for new clients. Listens for new connections in 10 second increments.
     * When a new client connects, creates a new EvalConnection and starts a new thread to run it.
     * Adds the thread to the clients list and continues to listen for new clients.
     *
     * @throws IllegalStateException if server hasn't been initialized
     */
    @Override
    public void run() throws IllegalStateException {
        if (!initialized)
            throw new IllegalStateException("run(): Server not initialized");

        while (!work.isEmpty() || clientsActive()) {
            try {
                Socket s = serv.accept();
                s.setKeepAlive(true);
                EvalConnection ec = new EvalConnection(s);
                ec.initialize();
                Thread t = new Thread( ec,"client " + clients.size());
                clients.add(t);
//                System.err.printf("%s connected%n",t.getName());
                t.start();
            } catch(SocketTimeoutException e){
//                System.err.println("Server timed out waiting for client to connect");
            }catch (IOException e) {
                System.err.println("I/O error while waiting");
                //e.printStackTrace();
            } catch( Exception e){
                System.err.println("Problem with a client.");
            }
        }
//        System.err.println("Server shutting down");
    }

    /**
     * Determines if the server has any active clients through use of the
     * {@code Thread} {@link Thread#isAlive()} method.Nonactive clients are
     * removed from the client list.
     *
     * @return true if <i>any</i> client threads on the server are alive.
     */
    public boolean clientsActive() {
        boolean isActive = false;
        Iterator<Thread> iter = clients.iterator();
        while (iter.hasNext()) {
            Thread client = iter.next();
            if (client.isAlive())
                isActive = true;
            else
                iter.remove();
        }
        return isActive;
    }

    /**
     * Adds EvalTask to the work list.
     *
     * @param et task to be added.
     * @throws IllegalStateException if server hasn't been initialized
     */
    synchronized public void addWork(EvalTask et) throws IllegalStateException {
        if (!initialized)
            throw new IllegalStateException();

        work.add(et);
    }

    /**
     * Retrieves work from the task list.
     *
     * @return {@link EvalTask} from the task list.
     * @throws IllegalStateException if server isn't initialized or task list is empty
     */
    synchronized public EvalTask getWork() throws IllegalStateException {
        if (!initialized)
            throw new IllegalStateException("Server not initialized");
        if (work.isEmpty())
            throw new IllegalStateException("No work available");

        return work.removeFirst();
    }

    /**
     * Returns whether the work list has tasks.
     *
     * @return true if work remains in the {@link EvalServer#work} list.
     * @throws IllegalStateException if server hasn't been initialized
     */
    synchronized public boolean hasWork() throws IllegalStateException {
        if (!initialized)
            throw new IllegalStateException();
        return !work.isEmpty();
    }

    /**
     * Inner class to handle communication with one specific client.
     * Communicates to clients whether work is remaining, sends serialized
     * EvalTask objects to be worked on, and receives results until a new
     * String object containing only "hasWork" is sent.
     */
    class EvalConnection implements Runnable {
        private final Socket s;
        /**
         * Input stream from the client
         */
        public ObjectInputStream in;
        /**
         * Output stream from the client
         */
        public ObjectOutputStream out;
        private boolean initialized = false;

        /**
         * Builds an EvalConnection, representing a client.
         *
         * @param s {@link Socket} connection to the client.
         */
        public EvalConnection(Socket s) {
            this.s = s;
        }

        /**
         * Main loop of the connection. First, attempts to receive the String "hasString"
         * from the client and sends true or false based on whether the server has remaining
         * work to send or not. Gets an EvalTask from the server and sends a serialized
         * version to the client over the socket. Then waits for result data to be sent
         * and adds it to the results list. Continues listening for results until the String
         * "hasWork" is sent again. If no work remains or the client disconnects, the method exits.
         *
         * @throws IllegalStateException if called before {@link EvalConnection#initialize}
         */
        @Override
        public void run() throws IllegalStateException {
            if (!initialized)
                throw new IllegalStateException("Connection not initialized");

            String workQuery = null;
            while (EvalServer.this.hasWork() || s.isConnected() ) {
                try {
                    // Receive client's hasWorkString
                    if( workQuery == null )
                        workQuery = (String) in.readObject();


                    //Send T/F depending on server's hasWork
                    if (!hasWork()){
                        out.writeBoolean(false);
                        out.flush(); // Connection can shut down before out gets a chance to write
//                        System.err.println("Server: false");
                        break;
                    }else {
                        out.writeBoolean(true);
//                        System.err.println("Server: true");
                        EvalTask task = EvalServer.this.getWork();
                        out.writeObject(task);
//                        System.err.println("Server: Sent work to client");

                        //Listen for results
                        while (true) {
                            Object result = in.readObject();
                            if (String.class.isAssignableFrom(result.getClass()) &&
                                    result.equals("hasWork")) {
//                                System.err.println("Server: Client asked hasWork");
                                workQuery = (String) result;
                                break;
                            }
//                            System.err.println("Server: Read result from client");
                            addResult(result);
                        }
                    }
                } catch (IOException e) {
                    System.err.println("Client disconnected");
                    break;
                } catch (ClassNotFoundException e) {
                    System.err.printf("%s: %s%n", e, e.getMessage());
                    e.printStackTrace();
                } catch (Exception e){
                    System.err.println("Problems with client(s): "+e.toString());
                    e.printStackTrace();
                }
            }
//            System.err.println(Thread.currentThread().getName()+" closed");
        }

        /**
         * Initializes input and output streams. Gracefully handles any
         * exceptions that arise when attempting to connect and set up streams,
         * printing error messages.
         */
        public void initialize() throws IllegalStateException {
            try {
                out = new ObjectOutputStream(s.getOutputStream());
                in = new ObjectInputStream(s.getInputStream());
                initialized = true;
            } catch (IOException e) {
                System.err.printf("%s: %s%n", e.getMessage(), "Error opening client's I/O streams");
                e.printStackTrace();
            } catch( Exception e){
                System.err.println("Problem setting up connection");
            }
        }

        /**
         * Adds an object to the results list in thread-safe manner.
         *
         * @throws IllegalStateException if called before {@code EvalConnection} is initialized.
         */
        public void addResult(Object o) {
            if (!initialized)
                throw new IllegalStateException("Server not initialized");
            synchronized (results) {
                results.add(o);
            }
        }
    }
}