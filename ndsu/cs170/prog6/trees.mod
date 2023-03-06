(***********************************************************************)
(*  IMPLEMENTATION MODULE TREES                                        *)
(*    WRITTEN BY CHRISTOPHER C. TJON                                   *)
(*    NAID: 110975-8                                                   *)
(*    5 NOV 1989                                                       *)
(*                                                                     *)
(*    THIS IMPLEMENTATION MODULE CONTAINS A NUMBER OF UTILITY          *)
(*    PROCEDURES FOR THE MANIPULATION OF TREES.                        *)
(*                                                                     *)
(*    THEY INCLUDE THE FOLLOWING:                                      *)
(*                                                                     *)
(*    1. CREATE TREE                6. IS IN TREE                      *)
(*    2. TREE IS EMPTY              7. INSERT WORD IN TREE             *)
(*    3. DATA                       8. WORD COUNT                      *)
(*    4. LEFTCHILD                  9. WRITE TREE                      *)
(*    5. RIGHTCHILD                 10. CREATE NEW NODE                *)
(*                                                                     *)
(*    THE GIVEN PROCEDURES ARE ADAPTATIONS AND ALTERATIONS OF          *)
(*    SIMILAR TREE PROCEDURES GIVEN IN THE BOOK:                       *)
(*                                                                     *)
(*       A SECOND COURSE IN COMPUTER SCIENCE WITH MODULA-2             *)
(*                                                                     *)
(*       WRITTEN BY: DANIEL D. MCCRACKEN AND WILLIAM I. SALMON         *)
(*                                                                     *)
(*       COPYRIGHT 1987, BY JOHN WILEY AND SONS, INC.                  *)
(*                                                                     *)
(*    THE SOURCE PROCEDURES CAN BE FOUND ON PAGES 273 THRU 283         *)
(*                                                                     *)
(*                                                                     *)
(***********************************************************************)
IMPLEMENTATION MODULE TREES;

FROM Storage IMPORT ALLOCATE;

FROM WORDS IMPORT MAXLENGTH;

FROM InOut IMPORT Write, WriteCard, WriteString, WriteLn;

FROM FInOut IMPORT FWrite, FWriteCard, FWriteString, FWriteLn, FILE;

FROM Strings IMPORT CompareStr;

TYPE TREE = POINTER TO TREENODE;

TREENODE = RECORD
           DATA : DATATYPE;
           LEFT : TREE;
           RIGHT : TREE;
           END;



(***********************************************************************)
(*** PROCEDURE : CREATE TREE *******************************************)
(***********************************************************************)

PROCEDURE CREATETREE (VAR T : TREE);
(* REQUIRES : NOTHING                                                  *)
(* MODIFIES : T                                                        *)
(* EFFECTS  : CREATES AN EMPTY TREE T                                  *)

BEGIN
  T := NIL;
END CREATETREE;


(***********************************************************************)
(*** PROCEDURE : TREE IS EMPTY *****************************************)
(***********************************************************************)

PROCEDURE TREEISEMPTY (T : TREE):BOOLEAN;
(* REQUIRES : T HAS BEEN INITIALIZED                                   *)
(* MODIFIES : NOTHING                                                  *)
(* EFFECTS  : RETURNS TRUE IF T IS EMPTY; FALSE OTHERWISE              *)

BEGIN
  RETURN (T = NIL)
END TREEISEMPTY;


(***********************************************************************)
(*** PRODEDURE : DATA **************************************************)
(***********************************************************************)

PROCEDURE DATA (T : TREE) : DATATYPE;
(* REQUIRES : T IS NOT EMPTY                                           *)
(* MODIFIES : NOTHING                                                  *)
(* EFFECTS  : RETURNS THE DATA ITEM AT THE ROOT NODE OF T              *)

BEGIN
  RETURN ( T@.DATA)
END DATA;


(***********************************************************************)
(*** PROCEDURE : LEFTCHILD *********************************************)
(***********************************************************************)

PROCEDURE LEFTCHILD (VAR T : TREE);
(* REQUIRES : T IS NOT EMPTY                                           *)
(* MODIFIES : T                                                        *)
(* EFFECTS  : MAKES T THE LEFT CHILD OF T                              *)

BEGIN
  T := T@.LEFT
END LEFTCHILD;


(***********************************************************************)
(*** PROCEDURE : RIGHTCHILD ********************************************)
(***********************************************************************)

PROCEDURE RIGHTCHILD (VAR T : TREE);
(* REQUIRES : T IS NOT EMPTY                                           *)
(* MODIFIES : T                                                        *)
(* EFFECTS  : MAKES T THE RIGHT CHILD OF T                             *)

BEGIN
  T := T@.RIGHT
END RIGHTCHILD;


(***********************************************************************)
(*** PROCEDURE : IS IN TREE ********************************************)
(***********************************************************************)

PROCEDURE ISINTREE (T    : TREE;
                    WORD : WORDTYPE) : BOOLEAN;
(* REQUIRES : T HAS BEEN INITIALIZED                                   *)
(* MODIFIES : NOTHING                                                  *)
(* EFFECTS  : RETURNS TRUE IF WORD IS IN T; OTHERWISE FALSE            *)

BEGIN
  IF T = NIL THEN
     RETURN ( FALSE )
  ELSIF (CompareStr(WORD,T@.DATA.WORD) = 0) THEN
     RETURN ( TRUE )
  ELSIF (CompareStr(WORD,T@.DATA.WORD) = -1) THEN
     RETURN ( ISINTREE (T@.LEFT, WORD))
  ELSE
     RETURN ( ISINTREE (T@.RIGHT, WORD))
  END; (* IF *)
END ISINTREE;


(***********************************************************************)
(*** PROCEDURE : INSERT WORD IN TREE ***********************************)
(***********************************************************************)

PROCEDURE INSERTWORDINTREE (VAR T       : TREE;
                                NEWWORD : WORDTYPE);
(* REQUIRES : T HAS BEEN INITIALIZED                                   *)
(* MODIFIES : T                                                        *)
(* EFFECTS  : IF NEWWORD IS ALREADY IN T, THEN INCREMENTS THE COUNT    *)
(*            FOR NEWWORD, OTHERWISE ADDS NEWWORD TO T AND INITIALIZES *)
(*            COUNT FOR THE NEW NEWWORD TO 1                           *)

BEGIN
  IF T = NIL THEN
     CREATENEWNODE (T, NEWWORD)
  ELSIF (CompareStr(NEWWORD,T@.DATA.WORD) = -1) THEN
     INSERTWORDINTREE (T@.LEFT, NEWWORD)
  ELSIF (CompareStr(NEWWORD,T@.DATA.WORD) = 1) THEN
     INSERTWORDINTREE (T@.RIGHT,NEWWORD)
  ELSE INC(T@.DATA.WCOUNT);
  END; (* IF *)
END INSERTWORDINTREE;


(***********************************************************************)
(*** PROCEDURE : WORD COUNT ********************************************)
(***********************************************************************)

PROCEDURE WORDCOUNT (T : TREE) : CARDINAL;
(* REQUIRES : T HAS BEEN INITIALIZED                                   *)
(* MODIFIES : NOTHING                                                  *)
(* EFFECTS  : RETURNS THE NUMBER OF WORDS IN T                         *)

BEGIN
  IF T = NIL THEN
     RETURN (0)
  ELSE
     RETURN (T@.DATA.WCOUNT + WORDCOUNT(T@.LEFT) + WORDCOUNT(T@.RIGHT))
  END; (* IF *)
END WORDCOUNT;


(***********************************************************************)
(*** PROCEDURE : WRITE TREE ********************************************)
(***********************************************************************)

PROCEDURE WRITETREE (T : TREE;F :FILE);
(* REQUIRES : T HAS BEEN INITIALIZED                                   *)
(* MODIFIES : NOTHING                                                  *)
(* EFFECTS  : DOES AN INORDER TRAVERSAL OF T, PRODUCING WORD AND       *)
(*            WORDCOUNT FOR EACH NODE OF T                             *)

VAR X   : CARDINAL;

BEGIN
  IF NOT TREEISEMPTY (T) THEN
     WRITETREE (T@.LEFT,F);

     WriteCard(T@.DATA.WCOUNT,4);     (*** WRITES TO SCREEN ***)
     WriteString('  ');
     WriteString(T@.DATA.WORD);
     WriteLn;

     FWriteCard(F,T@.DATA.WCOUNT,4);    (*** WRITES TO OUTPUT FILE ***)
     FWriteString(F,'  ');
     FWriteString(F,T@.DATA.WORD);
     FWriteLn(F);

     WRITETREE (T@.RIGHT,F)
  END; (* IF *)
END WRITETREE;


(***********************************************************************)
(*** PROCEDURE : CREATE NEW NODE ***************************************)
(***********************************************************************)

PROCEDURE CREATENEWNODE (VAR T   : TREE;
                         NEWWORD : WORDTYPE);
(* REQUIRES : T HAS BEEN INITIALIZED                                   *)
(* MODIFIES : NOTHING                                                  *)
(* EFFECTS  : CREATES A NEW NODE AND INITIALIZES WORD COUNT TO 1       *)

BEGIN
  ALLOCATE (T,SIZE(T@));
  T@.DATA.WORD := NEWWORD;
  T@.DATA.WCOUNT := 1;
  T@.LEFT := NIL;
  T@.RIGHT := NIL
END CREATENEWNODE;

END TREES.
