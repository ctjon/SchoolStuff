IMPLEMENTATION MODULE DynamArr; (* Dynamic Arrays      *)
                                (* D. Bruce Erickson   *)
                                (* 10/04/87            *)
(* Dynamic Arrays are represented as a block of contiguous
   storage.  The first 4 bytes is an integer value representing
   the low bound for the array.  The next 4 bytes is an integer
   value representing the high bound for the array.  If high >= low
   the remaining TSIZE(TYPE) * (high-low+1) bytes is used to store the
   array proper.  The location where A[i] is stored is:
   A + 2 * TSIZE(INTEGER) + (high-low+1) * TSIZE(TYPE)

   The rep invariant is TRUE;
*)
FROM Terminal IMPORT
  WriteLine, ClearScreen;

FROM SYSTEM IMPORT
   ADDRESS, TSIZE;

FROM Storage IMPORT
   Available, ALLOCATE, DEALLOCATE;

TYPE
   DynamicRealArray = ADDRESS;
   DynamicIntegerArray = ADDRESS;
   DynamicCardinalArray = ADDRESS;
   DynamicBooleanArray = ADDRESS;
   DynamicCharArray = ADDRESS;

PROCEDURE RCreate ( low,high: INTEGER ) : DynamicRealArray;
(* REQUIRES low <= high + 1
   EFFECTS creates a Dynamic Real Array indexed from low to high
*)
VAR
   space : CARDINAL;
   DRA : DynamicRealArray;
   temp : POINTER TO INTEGER;
BEGIN
  space := TSIZE(REAL) * CARDINAL(high - low + 1) +
           2 * TSIZE(INTEGER) ;
  IF Available(space)
     THEN
        ALLOCATE(DRA,space)
     ELSE
        WriteLine('Unable to allocate space for DynamicRealArray');
        HALT
     END;
  temp := DRA;
  temp@ := low;
  temp := DRA + TSIZE(INTEGER);
  temp@ := high;
  RETURN DRA
END RCreate;

PROCEDURE RDestroy ( A : DynamicRealArray );
(* REQUIRES A has been RCreated
   MODIFIES A
   EFFECTS Destroys A returning the space to the system.
*)
VAR
  space : CARDINAL;
  low   : POINTER TO INTEGER;
  high  : POINTER TO INTEGER;
BEGIN
  low := A;
  high :=  A + TSIZE(INTEGER);
  space := CARDINAL(high@ - low@ + 1) * TSIZE(REAL) +
           2 * TSIZE(INTEGER) ;
  DEALLOCATE(A,space)              (* space isn't used by Waterloo *)
END RDestroy;

PROCEDURE RLow( A : DynamicRealArray ) : INTEGER;
(* REQUIRES A has been RCreated
   EFFECTS returns the Low bound of A
*)
BEGIN
  RETURN INTEGER(A@)
END RLow;

PROCEDURE RHigh( A : DynamicRealArray ) : INTEGER;
(* REQUIRES A has been RCreated
   EFFECTS returns the High bound of A
*)
VAR
  location : POINTER TO INTEGER;

BEGIN
  location := A + TSIZE(INTEGER);
  RETURN location@
END RHigh;

PROCEDURE RAssign( A : DynamicRealArray;
                  i : INTEGER;
                  v : REAL );
(* REQUIRES A has been RCreated, and  RLow(A) <= i <= RHigh(A)
   MODIFIES A
   EFFECTS assigns v to position i in array A
*)
VAR
  location : POINTER TO REAL;

BEGIN                                 (* start after low and high *)
  location := A + 2 * TSIZE(INTEGER)
              + TSIZE(REAL) * CARDINAL(i - INTEGER(A@)) ;
  location@ := v
END RAssign;

PROCEDURE RFetch(A : DynamicRealArray; i : INTEGER): REAL;
(* REQUIRES A has been RCreated, position i has been assigned a value,
            and RLow(A) <= i <= RHigh(A)
   EFFECTS returns the value stored in position i of array A
*)
VAR
  location : POINTER TO REAL;

BEGIN                                 (* start after low and high *)
  location := A + 2 * TSIZE(INTEGER)
              + TSIZE(REAL) * CARDINAL(i - INTEGER(A@)) ;
  RETURN location@
END RFetch;

PROCEDURE ICreate ( low,high: INTEGER ) : DynamicIntegerArray;
(* REQUIRES low <= high + 1
   EFFECTS creates a Dynamic Integer Array indexed from low to high
*)
VAR
   space : CARDINAL;
   DRA : DynamicIntegerArray;
   temp : POINTER TO INTEGER;
BEGIN
  space := TSIZE(INTEGER) * CARDINAL(high - low + 1) +
           2 * TSIZE(INTEGER) ;
  IF Available(space)         (* get 7 extra bytes for allignment *)
     THEN
        ALLOCATE(DRA,space)
     ELSE
        WriteLine('Unable to allocate space for DynamicIntegerArray');
        HALT
     END;
  temp := DRA;
  temp@ := low;
  temp := DRA + TSIZE(INTEGER);
  temp@ := high;
  RETURN DRA
END ICreate;

PROCEDURE IDestroy ( A : DynamicIntegerArray );
(* REQUIRES A has been ICreated
   MODIFIES A
   EFFECTS Destroys A returning the space to the system.
*)
VAR
  space : CARDINAL;
  low   : POINTER TO INTEGER;
  high  : POINTER TO INTEGER;
BEGIN
  low := A;
  high :=  A + TSIZE(INTEGER);
  space := CARDINAL(high@ - low@ + 1) * TSIZE(INTEGER) +
           2 * TSIZE(INTEGER) ;
  DEALLOCATE(A,space)              (* space isn't used by Waterloo *)
END IDestroy;

PROCEDURE ILow( A : DynamicIntegerArray ) : INTEGER;
(* REQUIRES A has been ICreated
   EFFECTS returns the Low bound of A
*)
BEGIN
  RETURN INTEGER(A@)
END ILow;

PROCEDURE IHigh( A : DynamicIntegerArray ) : INTEGER;
(* REQUIRES A has been ICreated
   EFFECTS returns the High bound of A
*)
VAR
  location : POINTER TO INTEGER;

BEGIN
  location := A + TSIZE(INTEGER);
  RETURN location@
END IHigh;

PROCEDURE IAssign( A : DynamicIntegerArray;
                  i : INTEGER;
                  v : INTEGER );
(* REQUIRES A has been ICreated, and  ILow(A) <= i <= IHigh(A)
   MODIFIES A
   EFFECTS assigns v to position i in array A
*)
VAR
  location : POINTER TO INTEGER;

BEGIN                                 (* start after low and high *)
  location := A + 2 * TSIZE(INTEGER)
              + TSIZE(INTEGER) * ( CARDINAL(i - INTEGER(A@))) ;
  location@ := v
END IAssign;

PROCEDURE IFetch(A : DynamicIntegerArray; i : INTEGER): INTEGER;
(* REQUIRES A has been ICreated, position i has been assigned a value,
            and ILow(A) <= i <= IHigh(A)
   EFFECTS returns the value stored in position i of array A
*)
VAR
  location : POINTER TO INTEGER;

BEGIN                                 (* start after low and high *)
  location := A + 2 * TSIZE(INTEGER)
              + TSIZE(INTEGER) * ( CARDINAL(i - INTEGER(A@))) ;
  RETURN location@
END IFetch;

PROCEDURE CACreate ( low,high: INTEGER ) : DynamicCardinalArray;
(* REQUIRES low <= high + 1
   EFFECTS creates a Dynamic Cardinal Array indexed from low to high
*)
VAR
   space : CARDINAL;
   DRA : DynamicCardinalArray;
   temp : POINTER TO INTEGER;
BEGIN
  space := TSIZE(CARDINAL) * CARDINAL(high - low + 1) +
           2 * TSIZE(INTEGER) ;
  IF Available(space)         (* get 7 extra bytes for allignment *)
     THEN
        ALLOCATE(DRA,space)
     ELSE
        WriteLine('Unable to allocate space for DynamicCardinalArray');
        HALT
     END;
  temp := DRA;
  temp@ := low;
  temp := DRA + TSIZE(INTEGER);
  temp@ := high;
  RETURN DRA
END CACreate;

PROCEDURE CADestroy ( A : DynamicCardinalArray );
(* REQUIRES A has been CACreated
   MODIFIES A
   EFFECTS Destroys A returning the space to the system.
*)
VAR
  space : CARDINAL;
  low   : POINTER TO INTEGER;
  high  : POINTER TO INTEGER;
BEGIN
  low := A;
  high :=  A + TSIZE(INTEGER);
  space := CARDINAL(high@ - low@ + 1) * TSIZE(CARDINAL) +
           2 * TSIZE(INTEGER) ;
  DEALLOCATE(A,space)              (* space isn't used by Waterloo *)
END CADestroy;

PROCEDURE CALow( A : DynamicCardinalArray ) : INTEGER;
(* REQUIRES A has been CACreated
   EFFECTS returns the Low bound of A
*)
BEGIN
  RETURN INTEGER(A@)
END CALow;

PROCEDURE CAHigh( A : DynamicCardinalArray ) : INTEGER;
(* REQUIRES A has been CACreated
   EFFECTS returns the High bound of A
*)
VAR
  location : POINTER TO INTEGER;

BEGIN
  location := A + TSIZE(INTEGER);
  RETURN location@
END CAHigh;

PROCEDURE CAAssign( A : DynamicCardinalArray;
                  i : INTEGER;
                  v : CARDINAL );
(* REQUIRES A has been CACreated, and  CALow(A) <= i <= CAHigh(A)
   MODIFIES A
   EFFECTS assigns v to position i in array A
*)
VAR
  location : POINTER TO CARDINAL;

BEGIN                                 (* start after low and high *)
  location := A + 2 * TSIZE(INTEGER)
              + TSIZE(CARDINAL) * ( CARDINAL(i - INTEGER(A@))) ;
  location@ := v
END CAAssign;

PROCEDURE CAFetch(A : DynamicCardinalArray; i : INTEGER): CARDINAL;
(* REQUIRES A has been CACreated, position i has been assigned a value,
            and CALow(A) <= i <= CAHigh(A)
   EFFECTS returns the value stored in position i of array A
*)
VAR
  location : POINTER TO CARDINAL;

BEGIN                                 (* start after low and high *)
  location := A + 2 * TSIZE(INTEGER)
              + TSIZE(CARDINAL) * ( CARDINAL(i - INTEGER(A@))) ;
  RETURN location@
END CAFetch;

PROCEDURE BCreate ( low,high: INTEGER ) : DynamicBooleanArray;
(* REQUIRES low <= high + 1
   EFFECTS creates a Dynamic Boolean Array indexed from low to high
*)
VAR
   space : CARDINAL;
   DRA : DynamicBooleanArray;
   temp : POINTER TO INTEGER;
BEGIN
  space := TSIZE(BOOLEAN) * CARDINAL(high - low + 1) +
           2 * TSIZE(INTEGER) ;
  IF Available(space)         (* get 7 extra bytes for allignment *)
     THEN
        ALLOCATE(DRA,space)
     ELSE
        WriteLine('Unable to allocate space for DynamicBooleanArray');
        HALT
     END;
  temp := DRA;
  temp@ := low;
  temp := DRA + TSIZE(INTEGER);
  temp@ := high;
  RETURN DRA
END BCreate;

PROCEDURE BDestroy ( A : DynamicBooleanArray );
(* REQUIRES A has been BCreated
   MODIFIES A
   EFFECTS Destroys A returning the space to the system.
*)
VAR
  space : CARDINAL;
  low   : POINTER TO INTEGER;
  high  : POINTER TO INTEGER;
BEGIN
  low := A;
  high :=  A + TSIZE(INTEGER);
  space := CARDINAL(high@ - low@ + 1) * TSIZE(BOOLEAN) +
           2 * TSIZE(INTEGER) ;
  DEALLOCATE(A,space)              (* space isn't used by Waterloo *)
END BDestroy;

PROCEDURE BLow( A : DynamicBooleanArray ) : INTEGER;
(* REQUIRES A has been BCreated
   EFFECTS returns the Low bound of A
*)
BEGIN
  RETURN INTEGER(A@)
END BLow;

PROCEDURE BHigh( A : DynamicBooleanArray ) : INTEGER;
(* REQUIRES A has been BCreated
   EFFECTS returns the High bound of A
*)
VAR
  location : POINTER TO INTEGER;

BEGIN
  location := A + TSIZE(INTEGER);
  RETURN location@
END BHigh;

PROCEDURE BAssign( A : DynamicBooleanArray;
                  i : INTEGER;
                  v : BOOLEAN );
(* REQUIRES A has been BCreated, and  BLow(A) <= i <= BHigh(A)
   MODIFIES A
   EFFECTS assigns v to position i in array A
*)
VAR
  location : POINTER TO BOOLEAN;

BEGIN                                 (* start after low and high *)
  location := A + 2 * TSIZE(INTEGER)
              + TSIZE(BOOLEAN) * ( CARDINAL(i - INTEGER(A@))) ;
  location@ := v
END BAssign;

PROCEDURE BFetch(A : DynamicBooleanArray; i : INTEGER): BOOLEAN;
(* REQUIRES A has been BCreated, position i has been assigned a value,
            and BLow(A) <= i <= BHigh(A)
   EFFECTS returns the value stored in position i of array A
*)
VAR
  location : POINTER TO BOOLEAN;

BEGIN                                 (* start after low and high *)
  location := A + 2 * TSIZE(INTEGER)
              + TSIZE(BOOLEAN) * ( CARDINAL(i - INTEGER(A@))) ;
  RETURN location@
END BFetch;

PROCEDURE CHCreate ( low,high: INTEGER ) : DynamicCharArray;
(* REQUIRES low <= high + 1
   EFFECTS creates a Dynamic Char Array indexed from low to high
*)
VAR
   space : CARDINAL;
   DRA : DynamicCharArray;
   temp : POINTER TO INTEGER;
BEGIN
  space := TSIZE(CHAR) * CARDINAL(high - low + 1) +
           2 * TSIZE(INTEGER) ;
  IF Available(space)         (* get 7 extra bytes for allignment *)
     THEN
        ALLOCATE(DRA,space)
     ELSE
        WriteLine('Unable to allocate space for DynamicCharArray');
        HALT
     END;
  temp := DRA;
  temp@ := low;
  temp := DRA + TSIZE(INTEGER);
  temp@ := high;
  RETURN DRA
END CHCreate;

PROCEDURE CHDestroy ( A : DynamicCharArray );
(* REQUIRES A has been CHCreated
   MODIFIES A
   EFFECTS Destroys A returning the space to the system.
*)
VAR
  space : CARDINAL;
  low   : POINTER TO INTEGER;
  high  : POINTER TO INTEGER;
BEGIN
  low := A;
  high :=  A + TSIZE(INTEGER);
  space := CARDINAL(high@ - low@ + 1) * TSIZE(CHAR) +
           2 * TSIZE(INTEGER) ;
  DEALLOCATE(A,space)              (* space isn't used by Waterloo *)
END CHDestroy;

PROCEDURE CHLow( A : DynamicCharArray ) : INTEGER;
(* REQUIRES A has been CHCreated
   EFFECTS returns the Low bound of A
*)
BEGIN
  RETURN INTEGER(A@)
END CHLow;

PROCEDURE CHHigh( A : DynamicCharArray ) : INTEGER;
(* REQUIRES A has been CHCreated
   EFFECTS returns the High bound of A
*)
VAR
  location : POINTER TO INTEGER;

BEGIN
  location := A + TSIZE(INTEGER);
  RETURN location@
END CHHigh;

PROCEDURE CHAssign( A : DynamicCharArray;
                  i : INTEGER;
                  v : CHAR );
(* REQUIRES A has been CHCreated, and  CHLow(A) <= i <= CHHigh(A)
   MODIFIES A
   EFFECTS assigns v to position i in array A
*)
VAR
  location : POINTER TO CHAR;

BEGIN                                 (* start after low and high *)
  location := A + 2 * TSIZE(INTEGER)
              + TSIZE(CHAR) * ( CARDINAL(i - INTEGER(A@))) ;
  location@ := v
END CHAssign;

PROCEDURE CHFetch(A : DynamicCharArray; i : INTEGER): CHAR;
(* REQUIRES A has been CHCreated, position i has been assigned a value,
            and CHLow(A) <= i <= CHHigh(A)
   EFFECTS returns the value stored in position i of array A
*)
VAR
  location : POINTER TO CHAR;

BEGIN                                 (* start after low and high *)
  location := A + 2 * TSIZE(INTEGER)
              + TSIZE(CHAR) * ( CARDINAL(i - INTEGER(A@))) ;
  RETURN location@
END CHFetch;

END DynamArr.
