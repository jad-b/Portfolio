package cs671.eval;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.util.*;

/**
 * Priority queue implementation with optimized serializability.
 */
public class SerialPrioQueue implements Serializable {
    private static final long serialVersionUID = 8382973928364L;
    /**Highest priority node*/
    public transient Node head;
    /**Size of the queue*/
    public transient int size;
    private transient PriorityQueue<Node> pq;
    private transient Map<Comparable,Comparable> keys;
    private transient Map<Object,Object> vals;

    /**
     * Builds a priority queue, initializing the underlying library data structure.
     */
    public SerialPrioQueue() {
        initialize();
    }

    /**
     * Sets up the key/value maps and underlying priority queue.
     */
    private void initialize(){
        pq = new PriorityQueue<>(20, new Comparator<Node>(){
            public int compare(Node n1, Node n2){
                return n2.priority.compareTo(n1.priority);
            }
        });
        keys = new TreeMap<>();
        vals = new TreeMap<>();
    }

    /**
     * Adds a {@link Node} to the priority queue.
     * @param p Priority of the data
     * @param v Data to be added
     */
    public void add(Comparable p, Object v){
        keys.put(p,p);
        vals.put(v,v);
        add(new Node(keys.get(p), vals.get(v)));
    }

    /**
     * Adds a {@link Node} to the priority queue
     * @param n Data and its priority encapsulated by a {@link Node}
     */
    private void add(Node n){
        pq.add(n);
        head = pq.peek();
        size = pq.size();
    }

    /**
     * Returns whether or not the priority queue is empty.
     * @return if the queue is empty.
     */
    public boolean isEmpty(){
        return pq.isEmpty();
    }

    /**
     * Provides a {@link Object} array of all the data values in the priority queue.
     * @return see above
     */
    public Object[] preOrder(){
        List<Object> list = new ArrayList<>();
        for( Node o : pq )
            list.add(o.val);
        return list.toArray();
    }

    /**
     * Removes and returns the highest priority value of the node
     * @return the highest priority node's value
     */
    public Object remove(){
        Node n = pq.poll();
        size = pq.size();
        head = pq.peek();
        return n.val;
    }

    /**
     * Returns size of the heap.
     * @return heap size
     */
    public int size(){
        return pq.size();
    }

    /**
     * String representation of the priority queue.
     * @return see above
     */
    @Override
    public String toString(){
        StringBuilder sb = new StringBuilder();
        for (Node aPq : pq) {
            sb.append(aPq.toString());
        }
        return sb.toString();
    }

    /**
     * Reads in Object from stream. Initializes new key/value maps for the incoming values,
     * and nulls the head. Uses the preceeding size to inform the number of incoming key/value
     * pairs.
     *
     * @param in Stream to be read from.
     * @throws IOException if I/O errors arise while reading.
     * @throws ClassNotFoundException if the Object being read in can not be attributed to a known class.
     */
    private void readObject(ObjectInputStream in) throws IOException, ClassNotFoundException{
        initialize();
        head = null;
        int n = in.readInt();
//        System.err.printf("Reading %d nodes%n", n);
        for( int i = 0; i < n; i++ ){
            add((Comparable)in.readObject(),in.readObject());
        }
//        System.err.printf("Read %d nodes%n",size);
    }

    /**
     * Serializes the objects by writing the size to the stream, followed by priority/value tuples.
     * @param out ObjectOutputStream to write this instance to .
     * @throws IOException if problems arise while writing across the socket.
     */
    private void writeObject(ObjectOutputStream out) throws IOException {
        out.writeInt(size);
        for( Node n : pq ){
            out.writeObject(n.priority);
            out.writeObject(n.val);
        }
    }

    /**
     * Encapsulating class for a value and it's priority in the heap.
     */
    public static class Node {
        /**Node priority*/
        public Comparable priority;
        /**Stored data*/
        public Object val;

        /**
         * Node constructor
         * @param p {@link Node#priority}
         * @param v {@link Node#val}
         */
        public Node(Comparable<?> p, Object v) {
            priority = p;
            val = v;
        }

        /**
         * Returns a string representation of this node as "(priority,val)"
         * @return see above
         */
        @Override
        public String toString() {
            return String.format("(%s,%s)", priority, val);
        }
    }

    /**
     * Used for class testing
     * @param args
     */
    public static void main(String[] args) {
        SerialPrioQueue spq = new SerialPrioQueue();
        String[] vals = new String[]{"gamma","beta","omega","alpha","tau","rho"};
        Integer[] keys = new Integer[]{3,2,24,1,19,17};
        System.out.println("Testing creation...");
        for( Alphabets.Greek g : Alphabets.Greek.values() ){
            spq.add(g.ordinal(),g);
        }
        System.out.println(spq);

        //System.out.println("Testing removal...");
    }
}
