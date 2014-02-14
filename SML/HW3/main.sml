(* Jeremy DobbinsBucklad
 * CS671 Summer '13
 * HW3
 *)


(* Reworking of modulo operator *)
fun modulo (0,n) = 0
  | modulo (x,0) = x
  | modulo (x,1) = 0
  | modulo (x,n) = 
  let
  	val quotient = x div  n
  	val whole = quotient * n 
  in
  	x - whole
  end


(* Least Common Multiple *)
fun lcm (0,_) = 0
	| lcm (_,0) = 0
	| lcm (a,b) = 
	let 
		fun gcd x y = 
			if y <> 0 then 
				gcd y ( x mod y )
			else
				Int.abs(x)
	in
		Int.abs( (a*b) div (gcd a b) )
	end


(* Replacement for && operator *)
fun andEval (f1,f2) = 
	let 
		val x = f1 ()
		val y = f2 ()
	in
		if x andalso y then
			true
		else
			false
	end


(* Replacement for || operator *)
fun orEval (f1,f2) = 
	let 
		val x = f1 ()
		val y = f2 ()
	in
		if x orelse y then 
			true
		else
			false
	end


(* Returns the number of out-of-order elements in the list *)
fun nOutOfOrder comp list = 
	let 
		fun compare [] acc = acc
			| compare (x::nil) acc = acc
			| compare (x::y::l) acc = 
				if comp (x,y) then compare (y::l) acc 
				else compare (y::l) (acc+1)
	in 
		compare list 0
	end




(*The following recursive algorithm picks all of the k-element combinations from an ordered set:

o choose the first element i of your combination
o combine i with each of the combinations of k-1 elements chosen recursively 
	from the set of elements larger than i.
o Iterate the above for each i in the set.

It is essential that you pick the rest of the elements as larger than i, 
to avoid repetition. This way [3,5] will be picked only once, as [3] 
combined with [5], instead of twice (the condition eliminates [5] + [3]). 
Without this condition you get variations instead of combinations.*)
fun cmbs (0,_) = [[]]
	| cmbs (_,[]) = [[]]
	| cmbs (n,l) = 
		let 
			fun cmb nil = [[]]
				| cmb (x::t) = (List.map ((fn x=>fn y=>x::y) x) (cmb t))
		in cmb l end


(* fun maybe nil = [[]]
	| maybe x::t = List.map (fn q=> fn y=> (q::y) x) *)
 
(* fun layer nil ll = ll
 	| layer (x::t) ll =  *)


(*  val combinations; (int * 'a list) -> 'a list list *)
 fun combinations (0,_) = [[]]
	| combinations (_,[]) = [[]]
	| combinations (n,l) = 
	let
		(*Creates combinations using x as a seed
			val cmbxh : 'a list -> 'a list -> 'a list list -> 'a list list
		*)
		fun cmbxh front [] acc = []::acc
			| cmbxh front (x::nil) acc = front::acc (*Excluding last element x*)
			(*Build a combination excluding x, then call on the x+1 element*)
			| cmbxh front (x::tail) acc = cmbxh (front@[x]) tail ((front@tail)::acc)
		
		(*Calls for combinations of size n-1 to be made from every list 
			of size n in the containing 'a list list.
			val cmbx : 'a list list -> 'a list list -> 'a list list
		*)
		fun cmbx nil acc = acc@[]
			| cmbx (x::[]) acc = acc@(cmbxh [] x [])
			| cmbx (x::tail) acc = cmbx tail acc@(cmbxh [] x [])
		
		(*Reductively creates combinations of l of size n*)
		fun cmb n ll = 
			if List.length(hd ll) = n then ll
			else cmb n (cmbx ll [])
	in 
		cmb n [l]
	end


(*Creates a list of all permutations on l*)
fun permutations l =
	let 
		(*Calculates permutations by recursing down l
			val buildTuples : a' list -> a' list -> a' list list -> ('a list * 'a list) list
		*)
		fun buildTuples _ nil acc = acc
			| buildTuples front (x::tail) acc = buildTuples (front@[x]) tail (acc@[([x],(front@tail))])

		(* Takes a tuple and creates a list of permutations one level deeper.
			 front : stores the values appended so far
			 acc : accumulator for the created permutations
			 x : base list to be appended to
			 l : options of elements to append
 		*)
		fun aH front acc (x,[]) = acc
				| aH front acc (x,(y::t)) = aH (front@[y]) (acc@[( (x@[y]) , (front@t) )]) (x,t)

		fun assign [] = []
			| assign tplList = 
				let 
					val l = (List.concat (List.map (aH [] []) tplList))
					val headTuple = List.nth(l,0)
				in
					if List.null (#2(headTuple)) then (List.map (fn (x,y) => x) l) (*No more appendings; return l*)
					else assign l (*Reassign on tuple list*)
				end
		
	in
		case l of
			nil => [[]]
		| l => 
			let 
				val tplList = buildTuples [] l []
			in 
				assign tplList
			end
	end


fun commonFactors (n1,n2) = 
	let 
		fun findPrimeFactors num = 
			if num < 2 then [] else
				let 
					fun expDiv n dvr count = 
						let
							val qtt = n div dvr;
							val modulo = n mod dvr;
						in
							if modulo = 0 then
								expDiv qtt dvr (count+1)
							else
								(n,dvr,count)
						end

					fun factor n ftr acc = 
						let
							val (qtt,dvr,count) = expDiv n ftr 0			
						in
							if count > 0 then (*If it divides*) 
								if qtt > 1 then (*more to divide*)	
									factor qtt (ftr+1) ((ftr,count)::acc)
								else 
									((ftr,count)::acc)
							else 
								factor n (ftr+1) acc (*Does not factor*)
						end
				in
					List.rev (factor num 2 [])
				end

		fun findCommonFactors l1 l2 = 
			let 
				fun listLoop [] acc = acc
					| listLoop (x::t) acc = 
						let 
							val result = List.find ((fn (a,_)=>fn (b,_)=> a=b) x) l2
						in 
							case result of 
								SOME thing => listLoop t ( (#1(thing), Int.min( #2(x), #2(thing) ) )::acc)
							| NONE => listLoop t acc
						end
			in
				listLoop l1 []
			end 
		
		val n1_factors = findPrimeFactors n1
		val n2_factors = findPrimeFactors n2		
	in
		List.rev (findCommonFactors n1_factors n2_factors)
	end

(* Finds the best alignment between two strings 
   Stub method. *)
fun bestAlign "" _ = ("",0)
	| bestAlign _ "" = ("",0)
	| bestAlign s1 s2 = 
		if String.compare (s1,s2) = EQUAL then 
			(s1,0)
		else
		  (s2,0)

(* Outputs the string alignments with spaces placed where necessary *)
fun printAlign s1 s2 match shift = 
	let
		fun printSpaces x = 
			if x < 1 then () else (print " ";printSpaces (x-1))

	in
		if shift > 0 then
			 (printSpaces shift;
			 print (s1^"\n");
			 print (s2^"\n");
			 printSpaces (Int.abs shift);
			 print (match^"\n"))
		else
			(print (s1^"\n");
			printSpaces (Int.abs shift );
			print (s2^"\n");
			printSpaces (Int.abs shift);
			print (match^"\n"))
	end




