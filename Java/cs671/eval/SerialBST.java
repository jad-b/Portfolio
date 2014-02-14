package cs671.eval;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.util.*;

/**
 *
 */
public class SerialBST implements Serializable {
    private static final long serialVersionUID = 1019273928364L;
    /**
     * Root of the tree
     */
    public transient Node root;
    /**
     * Number of nodes in the tree
     */
    public transient int size;
    private transient Map<Comparable,Comparable> keys;
    private transient Map<Object,Object> vals;

    /**
     * Builds BST variables
     */
    public SerialBST() {
        initialize();
    }

    private void initialize() {
        root = null;
        size = 0;
        keys = new TreeMap<>();
        vals = new TreeMap<>();
    }

    private static List<Node> toList(List<Node> list, Node n) {
        if (n != null) {
            list.add(n);
            SerialBST.toList(list, n.left);
            SerialBST.toList(list, n.right);
        }
        return list;
    }

    /**
     * Testing for class methods
     * @param args
     */
    public static void main(String[] args) {
        SerialBST bst = new SerialBST();
        String[] vals = new String[]{"gamma", "beta", "omega", "alpha", "tau", "rho"};
        Integer[] keys = new Integer[]{3, 2, 24, 1, 19, 17};
        for (int i = 0; i < keys.length; i++) {
            bst.add(keys[i], vals[i]);
        }
        System.out.println("Testing creation...");
        System.out.println(bst);


        System.out.println("Testing removal...");
        for (Integer i : keys) {
            System.out.println("Removed " + bst.remove(i));
            System.out.println(bst);
        }

        System.out.println("Testing big tree now...");
        for (Alphabets.Greek g : Alphabets.Greek.values())
            bst.add(g.ordinal(), g);
        System.out.println(bst);

        System.out.println("Testing balance on big tree...");
        bst.balance();
        System.out.println(bst);


    }

    /**
     * Adds the node to the tree
     * @param key key to be attached to the Node
     * @param val value stored in the Node
     */
    public void add(Comparable key, Object val) {
        keys.put(key,key);
        vals.put(val,val);
        add(new Node(keys.get(key), vals.get(val)));
    }

    private void add(Node n) {
        n.parent = n.left = n.right = null;
        Node y = null;
        Node x = root;
        while (x != null) {
            y = x;
            if (n.key.compareTo(x.key) < 0)
                x = x.left;
            else
                x = x.right;
        }
        n.parent = y;
        if (y == null)
            root = n;
        else if (n.key.compareTo(y.key) < 0)
            y.left = n;
        else
            y.right = n;

        size++;
    }

    private void transplant(Node u, Node v) {
        if (u.parent == null)
            root = v;
        else if (u == u.parent.left) {
            u.parent.left = v;
        } else
            u.parent.right = v;
        if (v != null)
            v.parent = u.parent;
    }

    /**
     * Extracts the node with the given key from the tree. Takes the first node it finds
     * with that key.
     * @param k key to be matched upon
     * @return the matching node, if found
     * @throws NoSuchElementException if the node is not found in the tree
     */
    public Object remove(Comparable k) throws NoSuchElementException {
        Node n = (SerialBST.Node) find(k);

        if (n.left == null)
            transplant(n, n.right);
        else if (n.right == null)
            transplant(n, n.left);
        else {
            Node y = treeMinimum(n.right);
            if (y.parent != n) {
                transplant(y, y.right);
                y.right = n.right;
                y.right.parent = y;
            }
            transplant(n, y);
            y.left = n.left;
            y.left.parent = y;
        }

        n.parent = n.left = n.right = null;
        size--;
        return n.val;
    }

    /**
     * Follows the tree down the left-hand side to retrieve the left-most
     * descendant.
     *
     * @param start Node to start our voyage at
     * @return Node with the smallest value in this subtree
     */
    private Node treeMinimum(Node start) {
        while (start.left != null)
            start = start.left;
        return start;
    }

    /**
     * Balances the tree to the greatest degree possible,
     * reorganizing nodes so each node has as close to an equal number
     * of left and right descendants as possible.
     * <p/>
     * <p>
     * Now, how <i>I</i> do this is by dumping everything into a list,
     * sorting, and then inserting the middle (or closest to) as the root.
     * From there, all future additions will come out alright.
     * </p>
     */
    public void balance() {
        // Dump tree into a List
        List<Node> list = SerialBST.toList(new LinkedList<Node>(), this.root);
        for (Node n : list)
            n.parent = n.left = n.right = null;
        root = null;
        size = 0;
        // Sort the list by keys
        Collections.sort(list, new Comparator<Node>() {
            public int compare(Node n1, Node n2) {
                return n1.key.compareTo(n2.key);
            }
        });
        // Add middle node of sorted list as root
        addMiddle(list);
    }

    /**
     * Recursive method to continually add the middle node of a list undergoing
     * binary division in size. Used in conjunction with {@link SerialBST#balance}
     * @param list
     */
    private void addMiddle(List<Node> list) {
        if (list.isEmpty()) //  Empty list
            return;

        if(list.size() == 1) // One element list
            add(list.remove(0));
        else {  //Multiple element list
            int mid = list.size() / 2;
            add(list.remove(mid));
            addMiddle(new ArrayList<>(list.subList(0,mid)));
            addMiddle(new ArrayList<>(list.subList(mid,list.size())));
        }
    }

    /**
     * Retrieves the node by its key.
     * @param key Comparable to be searched upon.
     * @return the node if found
     * @throws NoSuchElementException if no node with that key exists in the tree
     */
    public Object find(Comparable key) throws NoSuchElementException {
        Node n = root;
        while (n != null && n.key.compareTo(key) != 0) {
//            System.out.printf("Find: %s vs. %s%n", n.key, key);
            if (key.compareTo(n.key) < 0)
                n = n.left;
            else
                n = n.right;
        }

        if (n == null)
            throw new NoSuchElementException("Item with key " + key + " not found");
//        System.out.printf("Found: %s vs. %s%n", n.key, key);
        return n;
    }

    /**
     * Checks if tree contains no nodes.
     * @return boolean indicating whether the tree has nodes.
     */
    public boolean isEmpty() {
        return size == 0 && root == null;
    }

    /**
     * Getter method for tree size.
     * @return tree size; number of nodes in the tree
     */
    public int size() {
        return size;
    }

    /**
     * Builds an in-order list of data values
     * @return
     */
    public Object[] inOrder() {
        ArrayList<Object> list = new ArrayList<>();
        inOrderHelper(list, root);
        return list.toArray();
    }

    private void inOrderHelper(ArrayList<Object> list, Node n) {
        if (n == null)
            return;
        inOrderHelper(list, n.left);
        list.add(n.val);
        inOrderHelper(list, n.right);
    }

    /**
     * Builds a pre-order list of data values
     * @return
     */
    public Object[] preOrder() {
        ArrayList<Object> list = new ArrayList<>();
        preOrderHelper(list, root);
        return list.toArray();
    }

    private void preOrderHelper(ArrayList<Object> list, Node n) {
        if (n == null)
            return;
        list.add(n.val);
        preOrderHelper(list, n.left);
        preOrderHelper(list, n.right);
    }

    /**
     * Returns a post-order list of data values
     * @return
     */
    public Object[] postOrder() {
        ArrayList<Object> list = new ArrayList<>();
        postOrderHelper(list, root);
        return list.toArray();
    }

    private void postOrderHelper(ArrayList<Object> list, Node n) {
        if (n == null)
            return;
        postOrderHelper(list, n.left);
        postOrderHelper(list, n.right);
        list.add(n.val);
    }

    /**
     * Builds an in-order String representation of the tree
     * @return
     */
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        return toStringHelper(sb, root).toString();
    }

    private StringBuilder toStringHelper(StringBuilder sb, Node n) {
        if (n != null) {
            sb.append(n.pairPrint());
            toStringHelper(sb, n.left);
            toStringHelper(sb, n.right);
        }
        return sb;
    }

    /**
     * @param in Stream to be read from
     * @throws IOException            if an I/O error occurs while reading
     * @throws ClassNotFoundException if the read object can not be translated
     */
    private void readObject(ObjectInputStream in) throws IOException, ClassNotFoundException {
        initialize();
        int n = in.readInt();
        for( int i = 0; i < n; i++ ){
            add((Comparable)in.readObject(),in.readObject());
        }
        System.out.printf("%d nodes read into SerialBST%n",size);
    }


    /**
     * @param out Stream to write to
     * @throws IOException if an I/O error occurs while writing
     */
    private void writeObject(ObjectOutputStream out) throws IOException {
        out.writeInt(size);
        int count = preOrderWrite(root, out, 0);
        System.out.printf("SerialBST: %d nodes written%n",count);
    }

    /**
     * Writes BST to {@code out} by pre-order traversal
     * @param n Parent node of tree to write
     * @param out Stream to write to
     * @throws IOException if an I/O error occurs while writing
     */
    private int preOrderWrite(Node n, ObjectOutputStream out, int count) throws IOException {
        if( n != null ){
            out.writeObject(n.key);
            out.writeObject(n.val);
            count++;
            count = preOrderWrite(n.left,out, count);
            count = preOrderWrite(n.right, out, count);
        }
        return count;
    }


    /**
     * Inner node class to store data
     */
    public static class Node {
        public Node parent;
        public Node left;
        public Node right;
        public Comparable key;
        public Object val;

        public Node(Comparable k, Object v) {
            key = k;
            val = v;
        }

        /**
         * Debugging method that prints (key,value) pairs.
         * @return see above
         */
        private String pairPrint() {
            return String.format("(%s,%s)", key, val);
        }

        /**
         * String representation of data value.
         * @return see above
         */
        @Override
        public String toString() {
            return val.toString();
        }
    }
}



