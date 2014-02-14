package cs671.eval;

/**
 * A collection of enums representing alphabets
 */
public class Alphabets {
    public enum Greek{
        ALPHA,
        BETA,
        GAMMA,
        DELTA,
        EPSILON,
        ZETA,
        ETA,
        THETA,
        IOTA,
        KAPPA,
        LAMBDA,
        MU,
        NU,
        XI,
        OMICRON,
        PI,
        RHO,
        SIGMA,
        TAU,
        UPSILON,
        PHI,
        CHI,
        PSI,
        OMEGA
    }

    public static void main(String[] args) {
        Greek[] sample = new Greek[]{Greek.ALPHA,Greek.LAMBDA,Greek.TAU};
        for( Greek g : Greek.values() )
            System.out.printf("%s: %d%n",g,g.ordinal());

    }
}
