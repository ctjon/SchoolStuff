IMPLEMENTATION MODULE ATOMLIST;

(****************************************************************)
(*                                                              *)
(*     IMPLEMENTATION MODULE ATOM LIST                          *)
(*                                                              *)
(*     WRITTEN BY CHRISTOPHER C. TJON                           *)
(*     NAID #: 110975-8                                         *)
(*     DATE: 5 FEBRUARY 1990                                    *)
(*                                                              *)
(*     THIS MODULE CONTAINS A SERIES OF SPECIAL PROCEDURES      *)
(*     FOR USE WITH THE ATOMIC LIST MODULE WHICH WAS PROVIDED.  *)
(*                                                              *)
(****************************************************************)

FROM Storage IMPORT ALLOCATE, Available;

FROM InOut IMPORT WriteString, WriteLn;

TYPE GENERALLIST = POINTER TO NODE;
     GENERALLISTNODE = GENERALLIST;
     NODE = RECORD
            NEXTNODE : GENERALLIST;
     CASE ATOMIC : BOOLEAN OF
                 TRUE : A : CHAR |
                 FALSE : L : GENERALLIST
            END; (* CASE *)
     END; (* RECORD *)


(****************************************************************)
(*****< PROCEDURE GET LIST >*************************************)
(****************************************************************)

PROCEDURE GETLIST(N : GENERALLISTNODE) : GENERALLIST;
(****************************************************************)
(* REQUIRES : L HAS BEEN CREATED                                *)
(* MODIFIES : NOTHING                                           *)
(* EFFECTS  : RETURNS A LIST OF NODE N                          *)
(****************************************************************)

BEGIN
    RETURN N@.L;
END GETLIST;


(****************************************************************)
(*****< PROCEDURE CREATE LIST >**********************************)
(****************************************************************)

PROCEDURE CREATELIST(VAR L : GENERALLIST);
(****************************************************************)
(* REQUIRES : NOTHING                                           *)
(* MODIFIES : NOTHING                                           *)
(* EFFECTS  : CREATES THE LIST                                  *)
(****************************************************************)

BEGIN
    L := NIL;
END CREATELIST;


(****************************************************************)
(*****< PROCEDURE GET ATOM >*************************************)
(****************************************************************)

PROCEDURE GETATOM(L : GENERALLISTNODE) : CHAR;
(****************************************************************)
(* REQUIRES : LISTS HAVE BEEN INITIALIZED                       *)
(* MODIFIES : NOTHING                                           *)
(* EFFECTS  : RETURNS THE ATOM FROM ATOMIC NODE N               *)
(****************************************************************)

BEGIN
    RETURN L@.A;
END GETATOM;


(****************************************************************)
(*****< PROCEDURE CREATE ATOM NODE >*****************************)
(****************************************************************)

PROCEDURE CREATEATOMNODE(A : CHAR) : GENERALLISTNODE;
(****************************************************************)
(* REQUIRES : LIST HAS BEEN INITIALIZED                         *)
(* MODIFIES : NOTHING                                           *)
(* EFFECTS  : CREATES A NEW ATOM NODE CONTAINING A              *)
(****************************************************************)

VAR N : GENERALLISTNODE;

BEGIN
    IF (Available(SIZE(N@))) THEN
       ALLOCATE(N,SIZE(N@));
       N@.A := A;
       N@.ATOMIC := TRUE;
       RETURN(N);
    ELSE
       WriteString("NOT ENOUGH AVAILABLE MEMORY!  RUN ABORTED!");
       WriteLn;
       HALT;
    END; (* IF AVAILABLE *)
END CREATEATOMNODE;


(****************************************************************)
(*****< PROCEDURE CREATE LIST NODE >*****************************)
(****************************************************************)

PROCEDURE CREATELISTNODE(L : GENERALLIST) : GENERALLISTNODE;
(****************************************************************)
(* REQUIRES : LIST HAS BEEN INITIALIZED                         *)
(* MODIFIES : NOTHING                                           *)
(* EFFECTS  : RETURNS THE LIST L AS A NODE                      *)
(****************************************************************)

VAR N : GENERALLISTNODE;

BEGIN
    IF (Available(SIZE(N@))) THEN
       ALLOCATE(N,SIZE(N@));
       N@.L := L;
       N@.ATOMIC := FALSE;
       RETURN(N);
    ELSE
       WriteString("NOT ENOUGH MEMORY AVAILABLE!  RUN ABORTED!");
       WriteLn;
    END; (* IF AVAILABLE *)
END CREATELISTNODE;


(****************************************************************)
(*****< PROCEDURE LIST >*****************************************)
(****************************************************************)

PROCEDURE LIST(N : GENERALLISTNODE) : BOOLEAN;
(****************************************************************)
(* REQUIRES : LIST HAS BEEN INITIALIZED                         *)
(* MODIFIES : NOTHING                                           *)
(* EFFECTS  : RETUNS TRUE IF N IS A LIST NODE FALSE OTHERWISE   *)
(****************************************************************)

BEGIN
    RETURN(NOT(N@.ATOMIC));
END LIST;


(****************************************************************)
(*****< PROCEDURE LENGTH >***************************************)
(****************************************************************)

PROCEDURE LENGTH(L : GENERALLIST) : CARDINAL;
(****************************************************************)
(* REQUIRES : LIST HAS BEEN INITIALIZED                         *)
(* MODIFIES : NOTHING                                           *)
(* EFFECTS  : RETURNS THE LENGTH OF THE LIST                    *)
(****************************************************************)

BEGIN
    IF (L=NIL) THEN
        RETURN(0);
    ELSE
        RETURN (1 + LENGTH(L@.NEXTNODE));
    END; (* IF L = NIL *)
END LENGTH;


(****************************************************************)
(*****< PROCEDURE CAR >******************************************)
(****************************************************************)

PROCEDURE CAR(L : GENERALLIST) : GENERALLISTNODE;
(****************************************************************)
(* REQUIRES : LIST HAS BEEN INITIALIZED                         *)
(* MODIFIES : NOTHING                                           *)
(* EFFECTS  : RETURNS THE FIRST NODE OF THE LIST                *)
(****************************************************************)

BEGIN
    RETURN (L);
END CAR;


(****************************************************************)
(*****< PROCEDURE CDR >******************************************)
(****************************************************************)

PROCEDURE CDR(L : GENERALLIST) : GENERALLIST;
(****************************************************************)
(* REQUIRES : LIST HAS BEEN INITIALIZED                         *)
(* MODIFIES : NOTHING                                           *)
(* EFFECTS  : RETURNS THE LIST WITHOUT THE FIRST NODE           *)
(****************************************************************)

BEGIN
    RETURN(L@.NEXTNODE);
END CDR;


(****************************************************************)
(*****< PROCEDURE CONS >*****************************************)
(****************************************************************)

PROCEDURE CONS(N : GENERALLISTNODE; VAR L : GENERALLIST);
(****************************************************************)
(* REQUIRES : LIST HAS BEEN INITIALIZED                         *)
(* MODIFIES : NOTHING                                           *)
(* EFFECTS  : ADDS A NODE TO THE BEGINNING OF THE LIST L        *)
(****************************************************************)

VAR TEMPSAVE : GENERALLIST;

BEGIN
    TEMPSAVE := L;
    L := N;
    L@.NEXTNODE := TEMPSAVE;
END CONS;

END ATOMLIST.
