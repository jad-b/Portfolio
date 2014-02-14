package cs671.eval;

import java.io.Serializable;

/**
 * A container for a "task" to be passed from an EvalServer to an EvalClient.
 * Stores the object to be used, names of parameters, and arguments to pass.
 *
 * @author Jeremy Dobbins-Bucklad
 */
public class EvalTask implements Serializable{
    /**Arguments to be passed to methods*/
    public Object[][] args;
    /**Names of methods to be called*/
    public String[] methods;
    /**Object to be the target of the methods called*/
    public Object target;

    /**
     * Creates an EvalTask
     * @param t
     * @param m
     * @param a
     */
    public EvalTask(Object t, String[] m, Object[][] a){
        target = t;
        methods = m;
        args = a;
    }

    /**
     * Prints out the finished product, in the same fashion as it is stored in file.
     * @return
     */
    @Override
    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append(target);
        sb.append("\n");
        for( int i = 0; i < methods.length; i++ ){
            sb.append(methods[i]).append(" ");
            for( Object o : args[i] )
                sb.append(o).append(" ");
            sb.append("\n");
        }
        return sb.toString();
    }
}
