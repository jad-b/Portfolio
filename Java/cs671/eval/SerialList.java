package cs671.eval;

import java.io.*;
import java.util.*;

/**
 * A serializable linked-list implementation, using key and value pairs.
 */
public class SerialList implements Serializable {
    private static final long serialVersionUID = 10239482391L;
    /**
     * Head of the list
     */
    public transient Node head;

    /*Instance Variables*/
    /**
     * Number of elements in the list.
     */
    public transient Node tail;
    /**
     * Tail of the list
     */
    public transient int size;
    private transient Map<Comparable,Comparable> keys;
    private transient Map<Object,Object> vals;

    /**
     * Creates a {@code SerialList} instance and explicitly nulls the
     * head, tail, and size.
     */
    public SerialList() {
        initialize();
    }

    /**
     * Sets instance variables to defaults (0,null) and creates the backbone Maps to track
     * keys and values.
     */
    private void initialize() {
        head = tail = null;
        size = 0;
        keys = new TreeMap<>();
        vals = new TreeMap<>();
    }

    /**
     * Merges two {@code SerialLists} by connecting the tail of the first list
     * to the head of the second.
     *
     * @param l1 The preceding list in the final merged list
     * @param l2 The proceeding list in the final merged list
     * @return A modified version of the first {@code SerialList} that incorporates
     *         the elements of the second.
     */
    public static SerialList merge(SerialList l1, SerialList l2) {
        try {
            l1.tail.next = l2.head;
            l1.tail = l2.tail;
            l1.size += l2.size;
            l2.head = l2.tail = null;
        } catch (NullPointerException e) {
            return null;
        }
        return l1;
    }

    /**
     * Used for class testing
     * @param args Command line arguments
     */
    public static void main(String[] args) {
        SerialList blankList, fullList;
        String[] keys = new String[]{"gamma", "beta", "omega", "alpha", "tau", "rho"};
        Integer[] vals = new Integer[]{3, 2, 24, 1, 19, 17};

        fullList = new SerialList();
        for (int i = 0; i < keys.length; i++) {
            fullList.add(keys[i], vals[i]);
        }
        System.out.printf("%s%n", fullList);

        System.out.println("Testing remove(index):...");
        System.out.printf("Removing %s%n", fullList.remove(3));
        System.out.printf("Removing %s%n", fullList.remove(1));
        System.out.println(fullList);

        System.out.println("Testing remove(key)");
        System.out.printf("Removing %s%n", fullList.remove("alpha"));
        System.out.println(fullList);

        System.out.println("Testing get(index):...");
        for (int i : new int[]{0, 1, 2}) {
            System.out.printf("%d: %s%n", i, fullList.get(i));
        }

        System.out.println("Testing get(key):...");
        for (String k : keys) {
            try {
                System.out.printf("%s: %s%n", k, fullList.get(k));
            } catch (NoSuchElementException e) {
                System.out.printf("%s not found in list%n", k);
            }
        }

        System.out.println("Testing merge:...");
        blankList = new SerialList();
        for (int i = 0; i < keys.length; i++) {
            blankList.add(keys[i], vals[i]);
        }
        System.out.printf("List 1: %s%n", fullList);
        System.out.printf("List 2: %s%n", blankList);
        SerialList mergedList = SerialList.merge(fullList, blankList);
        System.out.printf("Merged: %s%n", mergedList);

        System.out.println("Testing sort:...");
        mergedList.sort();
        System.out.println(mergedList);

        System.out.println("Testing Serialization:...");
        try {
            File file = new File("serialized.txt");
            ObjectOutputStream out = new ObjectOutputStream(new FileOutputStream(file));
            mergedList.writeObject(out);
            out.close();
            System.out.println("File size: " + file.length());

            ObjectInputStream in = new ObjectInputStream(new FileInputStream(file));
            SerialList l = (SerialList) in.readObject();
            in.close();
            System.out.printf("After serialization:%n%s%n", l);
        } catch (FileNotFoundException e) {
            System.err.printf("%s: %s%n", e, "");
            e.printStackTrace();
        } catch (IOException e) {
            System.err.printf("%s: %s%n", e, "");
            e.printStackTrace();
        } catch (ClassNotFoundException e) {
            System.err.printf("%s: %s%n", e, "");
            e.printStackTrace();
        }
    }

    /**
     * Adds a {@link SerialList.Node} to the head of the list.
     *
     * @param key the {@code Comparable} used to identify the value
     * @param val the value stored in the node
     */
    public void add(Comparable key, Object val) {
        keys.put(key, key);
        vals.put(val, val);
        Node tmp = head;
        head = new Node(keys.get(key),vals.get(val));
        head.next = tmp;
        if (tail == null)
            tail = head;
        size++;
    }

    /**
     * Adds a {@link SerialList.Node} to the tail of the list.
     *
     * @param key the {@code Comparable} used to identify the value
     * @param val the value stored in the node
     * @throws IllegalArgumentException if arguments are null
     */
    private void addLast(Comparable key, Object val) throws IllegalArgumentException {
        if( key == null || val == null )
            throw new IllegalArgumentException("Argument(s) were null");
        keys.put(key, key);
        vals.put(val, val);
//        System.out.printf("Adding (%s,%s)%n",key,val);
        Node n = new Node(keys.get(key),vals.get(val));
        //System.out.printf("Added %s%n",n);
        if (tail != null)
            tail.next = n;
        else
            head = tail = n;
        size++;
    }

    /**
     * Retrieves the Object at the given index.
     *
     * @param index index at which the value is stored
     * @return the found Object
     * @throws IndexOutOfBoundsException if the index is invalid for the list.
     */
    public Object get(int index) throws IndexOutOfBoundsException {
        if (index < 0 || index >= size)
            throw new IndexOutOfBoundsException("Invalid index " + index + " for list of size " + size);

        Node n = head;
        for (int i = 0; i < index && n != null; i++)
            n = n.next;

        assert (n != null);// Check final product is not null
        return n.val;
    }

    /**
     * Retrieves {@code Object} in list by the key. Takes first match.
     *
     * @param key {@code Comparable} object
     * @return matching object, if found.
     * @throws NoSuchElementException if Object does not exist in the list.
     */
    public Object get(Comparable key) throws NoSuchElementException {
        Node n = head;
        while (n != null && key.compareTo(n.key) != 0)
            n = n.next;

        if (n == null)
            throw new NoSuchElementException("Object not found in list");

        return n.val;
    }

    /**
     * Removes Object at given index.
     *
     * @param index index of {@link SerialList.Node} to be removed.
     * @return value of the {@code Node} removed.
     * @throws NoSuchElementException if the Object doesn't exist.
     */
    public Object remove(int index) throws NoSuchElementException {
        if (index < 0 || index >= size)
            throw new IndexOutOfBoundsException("Invalid index " + index + " for list of size " + size);

        Node n = head;
        if (size == 1) {
            head = tail = null;
        } else if (index == 0) {
            head = head.next;
        } else {
            Node prev = null;
            for (int i = 0; i < index; i++) {
                prev = n;
                n = n.next;
            }

            assert (n != null);
            if (index == size - 1) { //Removing from the tail of the list
                if (prev != null) {
                    prev.next = null;
                }
                tail = prev;
            } else { //middle of list
                if (prev != null) {
                    prev.next = n.next;
                }
            }
        }
        n.next = null;
        size--;
        return n.val;
    }

    /**
     * Removes element of the list matching the Comparable and returns the Object data value.
     *
     * @param key Comparable to match by
     * @return Object value.
     * @throws NoSuchElementException if the key isn't found in the list.
     */
    public Object remove(Comparable key) throws NoSuchElementException {
        Node prev = null;
        Node n = head;
        while (n != null && key.compareTo(n.key) != 0) {
            prev = n;
            n = n.next;
        }

        if (n == null)
            throw new NoSuchElementException("Key not found in list");

        if (size == 1) {
            assert (prev == null);
            head = tail = null;
        } else if (head.key.compareTo(key) == 0) { //Removing from the head of the list
            assert (prev == null);
            head = head.next;
        } else if (tail.key.compareTo(key) == 0) { //Removing from the tail of the list
            if (prev != null) {
                prev.next = null;
            }
            tail = prev;
        } else { //middle of list
            if (prev != null) {
                prev.next = n.next;
            }
        }
        n.next = null;
        size--;
        return n.val;
    }

    /**
     * Sorts the Serial List. Places all nodes into an ArrayList, then
     * uses the {@link java.util.Collections;} sort.
     */
    public void sort() {
        List<Node> list = new ArrayList<>();
        Node n = head;
        while (n != null) {
            list.add(n);
            n = n.next;
        }
        Collections.sort(list, new Comparator<Node>() {
            @Override
            public int compare(Node o1, Node o2) {
                return o1.key.compareTo(o2.key);
            }
        });
        // Re-connect list internally
        Node prev = null;
        for (int i = 0; i < list.size(); i++) {
            n = list.get(i);
            if (i == 0) // Head case
                head = n;
            if (i == list.size() - 1) { // Tail case
                tail = n;
                tail.next = null;
            }
            if (prev != null)
                prev.next = n;
            prev = n;
        }
    }

    /**
     * Prints a String representation of the list as:
     * Node 1, Node 2, Node 3,..., Node 4
     *
     * @return {code String} representation
     * @see cs671.eval.SerialList.Node#toString()
     */
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        Node n = head;
        while (n.next != null) {
            sb.append(n.pairPrint()).append(", ");
            n = n.next;
        }
        sb.append(n.pairPrint());
        return sb.toString();
    }

    /**
     * Tells if the list is empty
     *
     * @return whether or not the size of the list is zero
     */
    public boolean isEmpty() {
        return size == 0;
    }

    /**
     * Returns the size of the list.
     */
    public int size() {
        return size;
    }

    /**
     * Reads the entire list from {@code in} in as efficient a way as possible,
     * re-calculating any necessary values.
     *
     * @param in {@link ObjectInputStream} to be read from
     */
    private void readObject(ObjectInputStream in) throws IOException,
            ClassNotFoundException {
        initialize();
        int n = in.readInt();
//        int count = 0;
//        System.out.println("Reading in a list of size " + n);
        for (int i = 0; i < n; i++){
//            System.out.printf("Read %d nodes of %d%n", i,n);
            Comparable k = (Comparable) in.readObject();
            Object o = in.readObject();
            addLast(k,o);
        }
//        System.out.println("Done reading; list size = " + size);
    }

    /**
     * Outputs the size of the list, followed by key/value pairs.
     * @param out {@link ObjectOutputStream} to be written to.
     * @throws IOException if there is an I/O error while writing
     */
    private void writeObject(ObjectOutputStream out) throws IOException {
        out.writeInt(size);
//        int count = 0;
        for (Node n = head; n != null; n = n.next) {
            out.writeObject(n.key);
            out.writeObject(n.val);
//            count++;
        }
//        System.out.println(count +" nodes written");
    }

    /**
     * Inner node class to store data. Stores references to next node in the list.
     */
    public static class Node {
        /**
         * Key for this node
         */
        public Comparable key;
        /**
         * Next item in the list
         */
        public Node next;
        /**
         * Data for this node
         */
        public Object val;

        /**
         * Builds a Node.
         * @param c Key
         * @param v Value
         */
        public Node(Comparable c, Object v) {
            key = c;
            val = v;
            next = null;
        }

        /**
         * Prints the Node as (key,val)
         * @return String representation
         */
        private String pairPrint() {
            return String.format("(%s,%s)", key, val);
        }

        /**
         * Prints the data value
         * @return String representation
         */
        @Override
        public String toString() {
            return String.format("%s", val);
        }

    }


}
