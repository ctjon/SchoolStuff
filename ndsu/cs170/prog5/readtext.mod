MODULE READTEXT;
(*****************************************)
(*  PROGRAMMING ASSIGNMENT # 5           *)
(*  CHRISTOPHER C. TJON                  *)
(*  110975-8                             *)
(*  CS170                                *)
(*  25 OCT 1989                          *)
(*  DR.ERICKSON                          *)
(***********************************************************************)
(* THIS PROGRAM PERFORMS THE FOLLOWING FUNCTIONS AFTER READING A BLOCK *)
(*      OF TEXT:                                                       *)
(*                                                                     *)
(*              1. CALCULATION OF THE TOTAL NUMBER OF WORDS IN THE     *)
(*                 TEXT                                                *)
(*                                                                     *)
(*              2. AN ALPHABETICAL LIST OF ALL THE WORDS USED IN THE   *)
(*                 TEXT                                                *)
(*                                                                     *)
(*              3. THE NUMBER OF TIMES THAT EACH WORD WAS USED IN THE  *)
(*                 TEXT                                                *)
(*                                                                     *)
(***********************************************************************)

(* IMPORTS *)

FROM Strings IMPORT EOS, String,CompareStr,Pos;
FROM InOut IMPORT Read,Done,WriteString,WriteLn,EOL,
                  OpenInput, CloseInput, OpenOutput, CloseOutput,
                  WriteCard, FlushLn ;

(*** DECLARATIONS ******************************************************)

CONST MAXSIZE = 1000;
      MAXLENGTH = 20;
TYPE WORDTYPE = ARRAY[0..MAXLENGTH-1] OF CHAR;

     DATATYPE = RECORD
                WORD:WORDTYPE;
                WCOUNT:CARDINAL;
                END;

TABLETYPE = ARRAY[1..MAXSIZE] OF DATATYPE;
ENDSET = SET OF CHAR;

(*** DECLARE VARIABLES *************************************************)

VAR TABLE: TABLETYPE;
    CHECK : INTEGER;
    TABLESIZE,TCOUNT,I,J,R: CARDINAL;
    WORDDATA:DATATYPE;
    EOF : BOOLEAN;
    LOCATED : BOOLEAN ;
    CH : CHAR;
    VOIDCHAR : ENDSET;
    VALIDCHR : String;
    WORD:WORDTYPE;

(***********************************************************************)
(***********************************************************************)

PROCEDURE STORE(Word:WORDTYPE;VAR Table:TABLETYPE;
                VAR Tablesize:CARDINAL);
(* REQUIRES : INPUT OF THE WORD AND THE ARRAY                          *)
(* MODIFIES : THE ARRAY BY ADDING AN ELEMENT TO IT                     *)
(* EFFECTS :  CHANGES THE CONTENTS OF THE ARRAY DURING PROCESS         *)

    VAR X:CARDINAL;
        FOUND:BOOLEAN;
        WORDDATA:DATATYPE;
    BEGIN

    FOUND := FALSE;

    FOR X := 1 TO Tablesize BY 1 DO
        IF ( (CompareStr (Word,Table[X].WORD)) =0 ) THEN
            INC(Table[X].WCOUNT);
            FOUND := TRUE;
        END; (* IF *)
    END; (* FOR *)

    IF (NOT FOUND) THEN
       INC(Tablesize);
       WORDDATA.WORD := Word;
       WORDDATA.WCOUNT := 1;
       Table[Tablesize] := WORDDATA;
    END; (* IF *)
END STORE;

(***********************************************************************)
(***********************************************************************)

PROCEDURE SORT ( VAR INTABLE : TABLETYPE ; SIZE : CARDINAL) ;

(* REQUIRES : THE UNSORTED ARRAY AND ITS SIZE                          *)
(* MODIFIES : THE SEQUENCE OF ELEMENTS IN THE ARRAY                    *)
(* EFFECTS  : RETURNS THE ARRAY IN A ALPHABETICALLY SORTED STATE       *)

VAR L,K : CARDINAL ;
    TEMP: DATATYPE ;

BEGIN (*SORT*) ;

IF (SIZE > 1) THEN

FOR L := SIZE TO 2 BY -1 DO
   FOR K:= 1 TO (L-1) BY 1 DO
   IF ( CompareStr (INTABLE[K].WORD,INTABLE[K+1].WORD) = 1 ) THEN
     TEMP := INTABLE[K+1];
     INTABLE[K+1] := INTABLE[K] ;
     INTABLE[K] := TEMP ;
   END (*IF*);
    END (*FOR*);
END (*FOR*) ;
END (*IF*) ;

END SORT ;

(***********************************************************************)
(***********************************************************************)
(***********************************************************************)

BEGIN (* MAIN MODULE *)

OpenInput("");
OpenOutput("");

VOIDCHAR := ENDSET
           {'!','@','#','$','%','^','&','*','(',')','_','+','1','2','3',
            '4','5','6','7','8','9','0','-','=','[',']','`','{','}','~',
            ';','\',':','"','|','.','/','<','>','?',' ',' ',','};

           (* THIS IS BY NO MEANS A COMPLETE SET BY MORE CHARACTERS
              MAY BE ADDED *)

EOF := FALSE;         (*    INITIALIZE VARIABLES  *)
TABLESIZE := 0;
TCOUNT := 0;

WHILE (NOT EOF) DO
   I := 0;           (*INITIALIZE I TO ZERO *)

   (* INITIALIZE THE ARRAY TO BLANKS *)

   FOR J := 0 TO (MAXLENGTH-1) BY 1 DO
       WORD[J] := ' ';
   END;  (* FOR *)

   LOCATED := FALSE;     (* SET LOCATED FLAG TO FALSE *)

   WHILE ( NOT LOCATED ) DO

      Read (CH) ;
      CH := CAP(CH);
      IF (Done) THEN
         IF (CH = EOL) THEN
            FlushLn ;
            WORD[I] := EOS ;      (* IF CH = EOL THEN GO TO NEXT LINE *)
            LOCATED := TRUE ;
         ELSIF (CH IN VOIDCHAR) THEN
            WORD[I] := EOS ;     (* IF CH IS A VOID CHARACTER THEN END *)
            LOCATED := TRUE ;    (*     OF WORD IS FOUND               *)
         ELSE
            WORD[I] := CH ;      (* ELSE STORE CHARACTER AS AN ELEMENT *)
            INC (I) ;            (*     OF THE WORD                    *)
         END (*IF*) ;
      ELSE
         EOF := TRUE ;
         WORD[I] := EOS ;        (* SET CHARACTER = TO EOS AND LOCATED *)
         LOCATED := TRUE ;       (*     FLAG TO TRUE                   *)
      END (*IF*) ;
   END; (* WHILE NOT LOCATED *)

   IF ( I > 0 ) THEN
      (*** STORE WORD AND COUNT ***)

      STORE ( WORD, TABLE,TABLESIZE) ;

   END (*IF*) ;

   (*** GET TO START OF NEXT WORD ***)

END; (*WHILE NOT EOF *)

(*** SORT ***)

SORT ( TABLE ,TABLESIZE) ;

(*** ADD UP COUNTS ***)

FOR R := 1 TO TABLESIZE BY 1 DO
  TCOUNT := TCOUNT + TABLE[R].WCOUNT
END; (* FOR R *)

(*** PRINT OUT LIST OF WORDS AND COUNTS ***)

FOR I := 1 TO TABLESIZE DO
    WriteCard(TABLE[I].WCOUNT,5);
    WriteString("  ");
    WriteString(TABLE[I].WORD);
    WriteLn;
END; (* FOR *)

WriteLn;
WriteString(" THE TOTAL NUMBER OF WORDS = ");
WriteCard(TCOUNT,6);
WriteLn;


CloseInput;
CloseOutput;
END READTEXT.  (* END OF MAIN MODULE *)
