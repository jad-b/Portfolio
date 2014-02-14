use "hmap.sml";

datatype 'a permutationSeq = Cons of 'a option * (unit -> 'a permutationSeq);

(**************************************************************************)
(*Integral
  Calculates integrals through the ol' drawing rectangles method*)
(* Helper function to get around small differences in real number
   equivalences *)
fun equiv x1 x2 = Real.<((Real.abs(Real.- (x1,x2)), 0.000001))

fun integral f x1 x2 = 
  let
      fun iH acc x = 
        if 
          equiv x x2 then acc
        else
          iH (Real.+ (acc,Real.*((f x),0.1))) (Real.+ (x,0.1))
  in
      iH 0.0 x1 
  end

(*Adds memoization to the calculation of integrals. 
  If any part of an integral calculation has been used before,
  a lookup is done in place of the calculation. *)
fun integralMem f = 
  let
      val m = hashMap ()
      fun g (x1:real) (x2:real) = 
        let
          fun gH acc x = 
            if equiv x x2 then acc
            else
              case lookup (Real.round x,m) of
                  SOME y => gH (Real.+(acc,y)) (Real.+ (x,0.1))
                | NONE => 
                  let val r = Real.*((f x),0.1)
                  in
                    insert ((Real.round x,r),m); 
                    gH (Real.+(acc,r)) (Real.+ (x,0.1))
                  end
        in
          gH 0.0 x1
        end
  in
    g
  end

(*Integral Tests*)
(*val test1 = integral (fn x => Math.pow(x,8.0)) 2.0 8.4*)
(**************************************************************************)

(**************************************************************************)
(*Permutations
  Creates permutations of a list. For a list of size n, 
  it keeps a binary counter of size n to track changes*)
fun printList l = 
  let fun pLh nil = ()
    | pLh (x::nil) = print x
    | pLh (x::t) = (print (x^",");pLh t)
  in print "["; pLh l; print"]\n" end

(*Shifts the head of the list by n positions*)
fun shift nil _ = raise Empty
  | shift l 0 = l
  | shift (x::nil) n = [x]
  | shift (x::y::t) n = y::(shift (x::t) (n-1))

fun shiftList nil _ = nil
  | shiftList _ nil = nil
  | shiftList (x::t) (y::z) = shift (x::(shiftList t z)) y

(*Increments a binary counter for shift positions*)
fun inc nil = nil
  | inc (l as x::t) = 
    let 
      val len = List.length l
      val max = len-1
    in 
      if x < max then 
        (x+1)::t
      else
        0::(inc t)
    end

fun incRef l = (l := (inc (!l)); (!l))

local
fun printIntList l = 
    let fun pLh nil = ()
      | pLh (x::nil) = print (Int.toString(x))
      | pLh (x::t) = (print ((Int.toString(x))^",");pLh t)
    in print "["; pLh l; print"]\n" end
in
fun permutation l =
  let
      local
        val binCtr = ref (List.tabulate (List.length l, (fn x => 0)))
        val origin = !binCtr (*Holds a blank counter for comparison*)
        val start = l
        fun nullPSeq l = Cons(NONE, fn () => nullPSeq l)
      in
      fun permH [] = Cons(SOME [], fn () => nullPSeq [])
        | permH l = 
          let
            val prm = shiftList start (!binCtr) (*Create permutation here*)
          in 
            incRef binCtr; (*Increment shift counter*)
            if origin = (!binCtr) then (*Check for completion of permutations*)
              Cons(SOME prm, fn () => nullPSeq prm)
            else  
              Cons(SOME prm, fn () => permH prm)
          end
      end
  in
      permH l
  end
end

(*Calls the function pointer nestled in the permutationSeq*)
fun rest (Cons(_,f)) = f ()

(*Returns the permutation list*)
fun next (Cons(NONE,f))   = NONE
  | next (Cons(SOME a,f)) = SOME a

fun printPermutations (Cons(NONE,f)) = ()
  | printPermutations (Cons(SOME a, f)) = (printList a; printPermutations (f ()))

(**)
fun find cmp (Cons(NONE,f)) = (NONE,f ())
  | find cmp (Cons(SOME x, f)) = 
    if cmp x then 
      (x,f ())
    else
      find cmp (f ()) 

(**************************************************************************)

(*Variables*)
(*val l = List.tabulate (4,fn x => x)
val binL = List.tabulate (List.length l, (fn x => 0))*)

(*Test*)
(*val shftd = shift l 3
val incd1 = inc binL
val incd2 = inc incd1
val incd4 = inc [3,2,0,0]
val incd5 = inc [3,2,1,0]
val binLref = ref binL
val binLref1 = incRef binLref
val shiftd = shiftList l [0,0,0,0]
val shiftd2 = shiftList l [3,2,1,0]
val perm1 = permutation l
val perm2 = permutation l*)