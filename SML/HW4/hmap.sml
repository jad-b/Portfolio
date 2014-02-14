

val size = 1000;

fun hash x = x mod size;

fun h (x,y) = hash x;

fun insertList((a as (k,v)),nil) = [a] (*Adds to tail if no match*)
|   insertList((a as (k,v), (x,y)::ys)) =
        if k=x then a::ys (*Adds matches before*)
        else (x,y)::insertList(a,ys); 

fun insert (a as (k,v), A) =
    let
        val bucket = h(a); (*index into array*)
        val L = Array.sub (A, bucket) (*List at said index*)
    in
        Array.update(A,bucket,insertList(a,L)) (*Updates array *)
    end;

fun deleteList(x,nil) = nil
|   deleteList(x,y::ys) =
        if x=y then ys
        else y::deleteList(x,ys);

fun delete(x,A) =
    let
        val bucket = h(x);
        val L = Array.sub(A,bucket)
    in
        Array.update(A,bucket,deleteList(x,L))
    end;

fun lookupList(x,nil) = NONE
|   lookupList(x,(a,b)::ys) =
        if x=a then SOME b 
        else lookupList(x,ys);

fun lookup(x,A) = lookupList(x,Array.sub(A,hash(x)));

fun len A = Array.length A

fun hashMap () = Array.array(size, nil: (int * real) list)

