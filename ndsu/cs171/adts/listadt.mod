IMPLEMENTATION MODULE LISTADT;

(***********************************************************************)
(*                                                                     *)
(*    IMPLEMENTATION MODULE LISTADT                                    *)
(*                                                                     *)
(*    WRITTEN BY :  CHRISTOPHER C. TJON                                *)
(*    FOR        :  DR. ERICKSON'S CS171                               *)
(*    NAID       :  110975-8                                           *)
(*    DATE DUE   :  19 JANUARY 1990                                    *)
(*                                                                     *)
(*    THIS IMPLEMENTATION MODULE IS A MODIFICATION OF THE LISTPOINTER  *)
(*    MODULE GIVEN ON PAGES 224 THRU 237 IN THE TEXT :                 *)
(*                                                                     *)
(*        A SECOND COURSE IN COMPUTER SCIENCE WITH MODULA-2            *)
(*                                                                     *)
(*        WRITTEN BY : DANIEL D. MCCRACKEN AND WILLIAM I. SALMON       *)
(*                                                                     *)
(***********************************************************************)

FROM InOut IMPORT Write, WriteLn, WriteString, WriteCard;
FROM Storage IMPORT ALLOCATE, DEALLOCATE, Available;
FROM Strings IMPORT String, CompareStr;

TYPE LIST = POINTER TO NODE;

NODE = RECORD
       ITEM : ITEMTYPE;
       NEXT : LIST;
       END; (* RECORD *)

(***********************************************************************)
(*****< PROCEDURE CREATE LIST >*****************************************)
(***********************************************************************)

PROCEDURE CREATELIST(VAR L : LIST );
(***********************************************************************)
(* REQUIRES : NOTHING                                                  *)
(* MODIFIES : NOTHING                                                  *)
(* EFFECTS  : INITIALIZES LINKED LIST                                  *)
(***********************************************************************)

BEGIN
   L := NIL;
END CREATELIST;


(***********************************************************************)
(*****< PROCEDURE ADD NODE >********************************************)
(***********************************************************************)

PROCEDURE ADDNODE ( VAR L   : LIST ;
                    NEWITEM : ITEMTYPE );

(***********************************************************************)
(* REQUIRES : THE LIST HAS BEEN INITIALIZED                            *)
(* MODIFIES : NOTHING                                                  *)
(* EFFECTS  : ADDS A NEW NODE TO THE LIST                              *)
(***********************************************************************)

VAR SAVE : LIST;

BEGIN
   SAVE := L;
   IF (Available (SIZE(L@))) THEN
      ALLOCATE(L,SIZE(L@));
      L@.ITEM := NEWITEM;
      L@.NEXT := SAVE;
   ELSE
      WriteString("NOT ENOUGH MEMORY AVAILABLE");
      WriteLn;
      WriteString("RUN ABORTED!");
      WriteLn;
      HALT;
   END; (* IF AVAILABLE *)
END ADDNODE;


(***********************************************************************)
(*****< PROCEDURE INSERT AT FRONT >*************************************)
(***********************************************************************)

PROCEDURE INSERTATFRONT(VAR   L : LIST;
                        NEWITEM : ITEMTYPE);

(***********************************************************************)
(* REQUIRES : THE LIST HAS BEEN INITIALIZED                            *)
(* MODIFIES : NOTHING                                                  *)
(* EFFECTS  : INSERTS A NODE AT THE FRONT OF THE LIST                  *)
(***********************************************************************)

BEGIN
   ADDNODE(L , NEWITEM);
END INSERTATFRONT;


(***********************************************************************)
(*****< PROCEDURE INSERT AT END >***************************************)
(***********************************************************************)

PROCEDURE INSERTATEND (VAR L   : LIST;
                       NEWITEM : ITEMTYPE);

(***********************************************************************)
(* REQUIRES : THE LIST HAS BEEN INITIALIZED                            *)
(* MODIFIES : NOTHING                                                  *)
(* EFFECTS  : INSERTS A NODE AT THE END OF THE LIST                    *)
(***********************************************************************)

BEGIN
  IF (L=NIL) THEN
     ADDNODE(L,NEWITEM)
  ELSE
     INSERTATEND(L@.NEXT, NEWITEM)
  END;  (* IF L = NIL *)
END INSERTATEND;


(***********************************************************************)
(*****< PROCEDURE INSERT AFTER Kth >************************************)
(***********************************************************************)

PROCEDURE INSERTAFTERKTH (VAR L       : LIST;
                              K       : CARDINAL;
                              NEWITEM : ITEMTYPE);

(***********************************************************************)
(* REQUIRES : THE LIST HAS BEEN INITIALIZED AND 0 < K <= LIST LENGTH   *)
(* MODIFIES : NOTHING                                                  *)
(* EFFECTS  : INSERTS A NODE AS THE Kth ELEMENT OF THE LIST            *)
(***********************************************************************)

BEGIN
  IF (K < 1) OR (L = NIL) THEN
     LISTERROR("AfterNoNode");
  ELSIF (K = 1) THEN
     ADDNODE(L@.NEXT,NEWITEM);
  ELSE
     INSERTAFTERKTH(L@.NEXT,K-1,NEWITEM)
  END; (* IF *)
END INSERTAFTERKTH;


(***********************************************************************)
(*****< PROCEDURE INSERT AFTER CONTENT >********************************)
(***********************************************************************)

PROCEDURE INSERTAFTERCONTENT (VAR L   : LIST;
                              CONTENT : ITEMTYPE;
                              NEWITEM : ITEMTYPE);

(***********************************************************************)
(* REQUIRES : THE LIST HAS BEEN INITIALIZED AND CONTENT IS IN LIST     *)
(* MODIFIES : NOTHING                                                  *)
(* EFFECTS  : INSERTS A NODE AFTER THE CONTENT SPECIFIED               *)
(***********************************************************************)

BEGIN
   IF (L=NIL) THEN
      LISTERROR("NotInList");
   ELSIF (L@.ITEM = CONTENT) THEN
      ADDNODE (L@.NEXT, NEWITEM);
   ELSE
      INSERTAFTERCONTENT(L@.NEXT,CONTENT,NEWITEM);
   END;
END INSERTAFTERCONTENT;


(***********************************************************************)
(*****< FUNCTION PROCEDURE IN LIST >************************************)
(***********************************************************************)

PROCEDURE INLIST (L          : LIST;
                  SEARCHITEM : ITEMTYPE) : BOOLEAN;

(***********************************************************************)
(* REQUIRES : THE LIST HAS BEEN INITIALIZED                            *)
(* MODIFIES : NOTHING                                                  *)
(* EFFECTS  : CHECKS TO SEE IF THE SPECIFIED ELEMENT IS IN THE LIST    *)
(***********************************************************************)

BEGIN
  IF (L=NIL) THEN
     RETURN (FALSE);
  ELSIF (L@.ITEM = SEARCHITEM) THEN
     RETURN (TRUE);
  ELSE RETURN (INLIST(L@.NEXT,SEARCHITEM))
  END; (* IF *)
END INLIST;


(***********************************************************************)
(*****< PROCEDURE DELETENODE >******************************************)
(***********************************************************************)

PROCEDURE DELETENODE (VAR L : LIST);

(***********************************************************************)
(* REQUIRES : THE LIST HAS BEEN INITIALIZED                            *)
(* MODIFIES : NOTHING                                                  *)
(* EFFECTS  : DELETES A SPECIFIED NODE FROM THE LIST                   *)
(***********************************************************************)

VAR SAVE : LIST;

BEGIN
  SAVE := L;
  L    := L@.NEXT;
  DEALLOCATE(SAVE,SIZE(L@));
END DELETENODE;


(***********************************************************************)
(*****< PROCEDURE DELETE Kth >******************************************)
(***********************************************************************)

PROCEDURE DELETEKTH (VAR L : LIST;
                         K : CARDINAL);

(***********************************************************************)
(* REQUIRES : THE LIST HAS BEEN INITIALIZED AND 0 < K <= LISTLENGTH    *)
(* MODIFIES : NOTHING                                                  *)
(* EFFECTS  : DELETES THE Kth NODE FROM THE LIST                       *)
(***********************************************************************)

BEGIN
  IF (L=NIL) THEN
     LISTERROR("NoneToDelete")
  ELSIF (K=1) THEN
    DELETENODE(L)
  ELSE DELETEKTH(L@.NEXT,K-1)
  END; (* IF *)
END DELETEKTH;


(***********************************************************************)
(*****< FUNCTION PROCCEDURE LIST IS EMPTY >*****************************)
(***********************************************************************)

PROCEDURE LISTISEMPTY (L : LIST) : BOOLEAN;

(***********************************************************************)
(* REQUIRES : THE LIST HAS BEEN INITIALIZED                            *)
(* MODIFIES : NOTHING                                                  *)
(* EFFECTS  : RETURNS TRUE IF THE LIST IS EMPTY OTHERWISE FALSE        *)
(***********************************************************************)

BEGIN
  RETURN (L=NIL)
END LISTISEMPTY;


(***********************************************************************)
(*****< FUNCTION PROCEDURE LIST LENGTH >********************************)
(***********************************************************************)

PROCEDURE LISTLENGTH (L : LIST) : CARDINAL;

(***********************************************************************)
(* REQUIRES : THE LIST HAS BEEN INITIALIZED                            *)
(* MODIFIES : NOTHING                                                  *)
(* EFFECTS  : RETURNS THE LENGTH OF THE LIST                           *)
(***********************************************************************)

BEGIN
  IF (L=NIL) THEN
     RETURN(0);
  ELSE
     RETURN(1 + LISTLENGTH (L@.NEXT))
  END; (* IF *)
END LISTLENGTH;


(***********************************************************************)
(*****< PROCEDURE MAKE LIST EMPTY >*************************************)
(***********************************************************************)

PROCEDURE MAKELISTEMPTY (VAR L : LIST);

(***********************************************************************)
(* REQUIRES : THE LIST HAS BEEN INITIALIZED                            *)
(* MODIFIES : NOTHING                                                  *)
(* EFFECTS  : MAKES THE LIST EMPTY                                     *)
(***********************************************************************)

BEGIN
  WHILE ( L<>NIL ) DO
    DELETENODE(L)
  END; (* WHILE *)
END MAKELISTEMPTY;


(***********************************************************************)
(*****< PROCEDURE COPY LIST >*******************************************)
(***********************************************************************)

PROCEDURE COPYLIST (OLDLIST     : LIST;
                    VAR NEWLIST : LIST);

(***********************************************************************)
(* REQUIRES : THE LIST HAS BEEN INITIALIZED                            *)
(* MODIFIES : NOTHING                                                  *)
(* EFFECTS  : COPIES THE LIST                                          *)
(***********************************************************************)

BEGIN
  IF (OLDLIST = NIL) THEN
     NEWLIST := NIL
  ELSE
     ADDNODE (NEWLIST,OLDLIST@.ITEM);
     COPYLIST (OLDLIST@.NEXT, NEWLIST@.NEXT);
   END; (* IF *)
END COPYLIST;


(***********************************************************************)
(*****< PROCEDURE CONCAT LIST >*****************************************)
(***********************************************************************)

PROCEDURE CONCATLIST(VAR LEFT  : LIST;
                         RIGHT : LIST);

(***********************************************************************)
(* REQUIRES : THE LISTS HAVE BEEN INITIALIZED                          *)
(* MODIFIES : NOTHING                                                  *)
(* EFFECTS  : CONCATS TWO LISTS TOGETHER                               *)
(***********************************************************************)

VAR P : LIST;

BEGIN
  IF (RIGHT=NIL) THEN
     (*** NOTHING TO DO ***)
  ELSIF (LEFT=NIL) THEN
     LEFT := RIGHT
  ELSE
     P := LEFT;
     WHILE (P@.NEXT <> NIL) DO
       P := P@.NEXT
     END; (* WHILE *)
  P@.NEXT := RIGHT
  END; (* IF *)
END CONCATLIST;


(***********************************************************************)
(*****< PROCEDURE WRITE LIST >******************************************)
(***********************************************************************)

PROCEDURE WRITELIST (L : LIST);

(***********************************************************************)
(* REQUIRES : THE LIST HAS BEEN INITIALIZED                            *)
(* MODIFIES : NOTHING                                                  *)
(* EFFECTS  : PRINTS OUT THE ELEMENTS IN THE LIST [TYPE = STRING]      *)
(***********************************************************************)

BEGIN
  WHILE (L <> NIL) DO
    WriteCard(L@.ITEM,4);
    L := L@.NEXT;
  END; (* WHILE *)
END WRITELIST;


(***********************************************************************)
(*****< PROCEDURE RETURN ITEM >*****************************************)
(***********************************************************************)

PROCEDURE RETURNITEM (L : LIST) : ITEMTYPE;

(***********************************************************************)
(* REQUIRES : THE LIST HAS BEEN INITIALIZED                            *)
(* MODIFIES : NOTHING                                                  *)
(* EFFECTS  : RETURNS THE ITEM FIELD OF THE NODE POINTED TO            *)
(***********************************************************************)

BEGIN
  RETURN (L@.ITEM);
END RETURNITEM;


(***********************************************************************)
(*****< PROCEDURE NEXTNODE >********************************************)
(***********************************************************************)

PROCEDURE NEXTNODE ( L : LIST ) : LIST;

(***********************************************************************)
(* REQUIRES : THE LIST HAS BEEN INITIALIZED                            *)
(* MODIFIES : NOTHING                                                  *)
(* EFFECTS  : RETURNS THE ITEM FIELD OF THE NEXT NODE                  *)
(***********************************************************************)

BEGIN
  RETURN (L@.NEXT);
END NEXTNODE;


(***********************************************************************)
(*****< PROCEDURE ADVANCE >*********************************************)
(***********************************************************************)

PROCEDURE ADVANCE ( VAR L : LIST );

(***********************************************************************)
(* REQUIRES : THE LIST HAS BEEN INITIALIZED                            *)
(* MODIFIES : NOTHING                                                  *)
(* EFFECTS  : MAKES L THE LIST BEGINNING AT THE NEXT NODE              *)
(***********************************************************************)

BEGIN
  L := L@.NEXT;
END ADVANCE;


(***********************************************************************)
(*****< PROCEDURE LIST ERROR >******************************************)
(***********************************************************************)

PROCEDURE LISTERROR(ERROR : String );

(***********************************************************************)
(* REQUIRES : NOTHING                                                  *)
(* MODIFIES : NOTHING                                                  *)
(* EFFECTS  : PRINTS OUT THE APPROPRIATE ERROR MESSAGE                 *)
(***********************************************************************)

BEGIN
  WriteString(ERROR);
  WriteLn;
END LISTERROR;

END LISTADT.
