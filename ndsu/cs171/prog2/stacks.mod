IMPLEMENTATION MODULE STACKS;

(***********************************************************************)
(*                                                                     *)
(*  IMPLEMENTATION MODULE STACKS                                       *)
(*                                                                     *)
(*  WRITTEN BY CHRISTOPHER C. TJON                                     *)
(*  FOR DR. ERICKSON'S CS171                                           *)
(*  17 DECEMBER 1989                                                   *)
(*                                                                     *)
(*  THIS MODULE IS AN ADAPTED IMPLEMENTATION OF THE STACKADT MODULE    *)
(*  ON PAGES 132 THRU 135 IN THE TEXT :                                *)
(*                                                                     *)
(*     A SECOND COURSE IN COMPUTER SCIENCE WITH MODULA-2               *)
(*                                                                     *)
(*     WRITTEN BY DANIEL D. MCCRACKEN AND WILLIAM I. SALMON            *)
(*                                                                     *)
(*     THIS MODULE CONTAINS THE FOLLOWING PROCEDURES:                  *)
(*                                                                     *)
(*       1. CREATE STACK          5. OVERFLOW ERROR                    *)
(*       2. MAKE STACK EMPTY      6. POP                               *)
(*       3. PUSH                  7. STACK IS EMPTY                    *)
(*       4. STACKTOP              8. STACK IS FULL                     *)
(*                                                                     *)
(***********************************************************************)

FROM InOut IMPORT WriteString, WriteLn;

FROM DATAITEM IMPORT DATATYPE;

FROM Storage IMPORT ALLOCATE, Available;

CONST MAXHEIGHT = 80; (* CAN BE AS DEEP YOU WOULD LIKE THE STACK TO GO *)

TYPE STACK = POINTER TO RECORD
             DATA : ARRAY [1..MAXHEIGHT] OF DATATYPE;
             TOP  : [0..MAXHEIGHT];
             END;

(***********************************************************************)
(*****< PROCEDURE CREATE STACK >****************************************)
(***********************************************************************)

PROCEDURE CREATESTACK( VAR S : STACK);

(***********************************************************************)
(* REQUIRES : NOTHING                                                  *)
(* MODIFIES : NOTHING                                                  *)
(* EFFECTS  : CREATES AND INITIALIZES AN EMPTY STACK                   *)
(***********************************************************************)

BEGIN
  IF (Available (SIZE(S@))) THEN
     ALLOCATE(S,SIZE(S@));
     S@.TOP := 0;
  ELSE
     WriteString("NOT ENOUGH MACHINE MEMORY AVAILABLE!  EXIT!");
  END; (* IF AVAILABLE *)
END CREATESTACK;


(***********************************************************************)
(*****< PROCEDURE MAKE STACK EMPTY >************************************)
(***********************************************************************)

PROCEDURE MAKESTACKEMPTY( VAR S : STACK);

(***********************************************************************)
(* REQUIRES : THAT STACK HAS BEEN CREATED                              *)
(* MODIFIES : NOTHING                                                  *)
(* EFFECTS  : MAKES AN EXISTING STACK EMPTY                            *)
(***********************************************************************)

BEGIN
  S@.TOP := 0;
END MAKESTACKEMPTY;


(***********************************************************************)
(*****< PROCEDURE PUSH >************************************************)
(***********************************************************************)

PROCEDURE PUSH(VAR S       : STACK;
                   NEWITEM : DATATYPE);

(***********************************************************************)
(* REQUIRES : STACK HAS BEEN INITIALIZED AND IS NOT FULL               *)
(* MODIFIES : NOTHING                                                  *)
(* EFFECTS  : PUSHES NEW ITEM ON TO THE TOP OF THE STACK               *)
(***********************************************************************)

BEGIN
  IF (S@.TOP = MAXHEIGHT) THEN
     OVERFLOWERROR;
  ELSE
     S@.TOP          := S@.TOP + 1;
     S@.DATA[S@.TOP] := NEWITEM;
  END; (* IF *)
END PUSH;


(***********************************************************************)
(*****< PROCEDURE OVERFLOWERROR >***************************************)
(***********************************************************************)

PROCEDURE OVERFLOWERROR;

(***********************************************************************)
(* REQUIRES : NOTHING                                                  *)
(* MODIFIES : NOTHING                                                  *)
(* EFFECTS  : DISPLAYS AN ERROR MESSAGE AND HALTS THE RUN              *)
(***********************************************************************)

BEGIN
  WriteLn;
  WriteString(" ATTEMPT TO PUSH DATAITEM ON TO A FULL STACK! ");
  WriteLn;
  WriteString(" RUN ABORTED! ");
  WriteLn;
  HALT;
END OVERFLOWERROR;


(***********************************************************************)
(*****< PROCEDURE UNDERFLOWERROR >**************************************)
(***********************************************************************)

PROCEDURE UNDERFLOWERROR;

(***********************************************************************)
(* REQUIRES : NOTHING                                                  *)
(* MODIFIES : NOTHING                                                  *)
(* EFFECTS  : DISPLAYS AN ERROR MESSAGE AND HALTS THE RUN              *)
(***********************************************************************)

BEGIN
  WriteLn;
  WriteString(" ATTEMPT TO POP DATAITEM FROM AN EMPTY STACK! ");
  WriteLn;
  WriteString(" RUN ABORTED! ");
  WriteLn;
  HALT;
END UNDERFLOWERROR;


(***********************************************************************)
(*****< PROCEDURE POP >*************************************************)
(***********************************************************************)

PROCEDURE POP( VAR S          : STACK;
               VAR STACKVALUE : DATATYPE );

(***********************************************************************)
(* REQUIRES : THAT STACK HAS BEEN INITIALIZED AND IS NOT EMPTY         *)
(* MODIFIES : THE STACK STRUCTURE                                      *)
(* EFFECTS  : COPIES TOP ELEMENT FROM STACK INTO STACKVALUE, THIS      *)
(*            EFFECTIVELY REMOVES IT FROM THE TOP OF THE STACK         *)
(***********************************************************************)

BEGIN
  IF (S@.TOP = 0) THEN
    UNDERFLOWERROR;
  ELSE
    STACKVALUE := S@.DATA[S@.TOP];
    S@.TOP     := S@.TOP - 1;
  END; (* IF *)
END POP;


(***********************************************************************)
(*****< FUNCTION PROCEDURE STACK IS EMPTY >*****************************)
(***********************************************************************)

PROCEDURE STACKISEMPTY(VAR S : STACK) : BOOLEAN;

(***********************************************************************)
(* REQUIRES : STACK HAS BEEN INITIALIZED                               *)
(* MODIFIES : NOTHING                                                  *)
(* EFFECTS  : RETURNS TRUE IF STACK IS EMPTY OTHERWISE FALSE           *)
(***********************************************************************)

BEGIN
  RETURN (S@.TOP = 0);
END STACKISEMPTY;


(***********************************************************************)
(*****< FUNCTION PROCEDURE STACK IS FULL >******************************)
(***********************************************************************)

PROCEDURE STACKISFULL(VAR S : STACK) : BOOLEAN;

(***********************************************************************)
(* REQUIRES : STACK HAS BEEN INITIALIZED                               *)
(* MODIFIES : NOTHING                                                  *)
(* EFFECTS  : RETURNS TRUE IF STACK IS FULL OTHERWISE FALSE            *)
(***********************************************************************)

BEGIN
  RETURN (S@.TOP = MAXHEIGHT);
END STACKISFULL;


(***********************************************************************)
(*****< FUNCTION PROCEDURE STACK TOP >**********************************)
(***********************************************************************)

PROCEDURE STACKTOP( VAR S : STACK ) : DATATYPE;

(***********************************************************************)
(* REQUIRES : STACK HAS BEEN INITIALIZED AND IS NOT EMPTY              *)
(* MODIFIES : NOTHING (STACK IS UNCHANGED)                             *)
(* EFFECTS  : RETURNS VALUE OF THE ITEM AT THE TOP OF THE STACK        *)
(***********************************************************************)

BEGIN
  RETURN S@.DATA[S@.TOP];
END STACKTOP;


END STACKS.
