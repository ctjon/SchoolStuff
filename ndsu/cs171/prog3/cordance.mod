MODULE CORDANCE;
(***********************************************************************)
(*  PROGRAMMING ASSIGNMENT # 3                                         *)
(*  CHRISTOPHER C. TJON                                                *)
(*  110975-8                                                           *)
(*  CS171                                                              *)
(*  19 JAN 1989                                                        *)
(*  DR.ERICKSON                                                        *)
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
(*              3. THE PAGES ON WHICH EACH WORD WAS USED               *)
(*                                                                     *)
(*                                                                     *)
(***********************************************************************)


(***********************************************************************)
(*** IMPORTS ***********************************************************)
(***********************************************************************)

FROM Strings IMPORT EOS, String,CompareStr,Pos;
FROM InOut IMPORT Read,Done,WriteString,WriteLn,EOL,
                  OpenInput, CloseInput, OpenOutput, CloseOutput,
                  WriteCard, FlushLn;
FROM WORDS IMPORT WORDTYPE;
FROM TREES IMPORT TREE,WRITETREE,INSERTWORDINTREE,CREATETREE,WORDCOUNT;
FROM FInOut IMPORT FOpenOutput, FWrite, FCloseOutput, FILE, FWriteLn,
                   FWriteString, FWriteCard;


(***********************************************************************)
(*** TYPE DECLARATIONS *************************************************)
(***********************************************************************)

TYPE ENDSET = SET OF CHAR;

(***********************************************************************)
(*** DECLARE VARIABLES *************************************************)
(***********************************************************************)

CONST PAGEFEED = CHR(12);

VAR EOF : BOOLEAN;
    LOCATED : BOOLEAN ;
    CH : CHAR;
    VOIDCHAR : ENDSET;
    WORD : WORDTYPE;
    TABLE : TREE;
    OUT : FILE;
    NUMWORD, I, PAGENUM : CARDINAL;


(***********************************************************************)
(*** MAIN MODULE *******************************************************)
(***********************************************************************)

BEGIN (* MAIN MODULE *)

CREATETREE(TABLE);
OpenInput("");
OpenOutput("");
WriteLn;

VOIDCHAR := ENDSET
           {'!','@','#','$','%','^','&','*','(',')','_','+','1','2','3',
            '4','5','6','7','8','9','0','-','=','[',']','`','{','}','~',
            ';','\',':','"','|','.','/','<','>','?',' ',' ',',',CHR(12),
            CHR(63),CHR(125),CHR(21)};

             (* THIS IS BY NO MEANS A COMPLETE SET BY MORE CHARACTERS  *)
             (* MAY BE ADDED                                           *)

EOF := FALSE;
PAGENUM := 1;                            (* INITIALIZE PAGENUM TO ZERO *)

WHILE (NOT EOF) DO
   I := 0;                                     (* INITIALIZE I TO ZERO *)

   LOCATED := FALSE;                      (* SET LOCATED FLAG TO FALSE *)

   WHILE ( NOT LOCATED ) DO

      Read (CH) ;
      CH := CAP(CH);
      IF (CH = PAGEFEED) THEN
         PAGENUM := PAGENUM + 1;
      END; (* IF *)
      IF (Done) THEN
         IF (CH = EOL) THEN
            FlushLn ;
            WORD[I] := EOS ;       (* IF CH = EOL THEN GO TO NEXT LINE *)
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

      INSERTWORDINTREE(TABLE,WORD,PAGENUM);  (* STORE THE WORD IN TREE *)

   END (* IF *) ;

END; (*WHILE NOT EOF *)

WRITETREE(TABLE);           (* WRITE THE TREE TO FILE AND SCREEN   *)

NUMWORD := WORDCOUNT(TABLE);    (* CALCULATE THE TOTAL NUMBER OF WORDS *)

WriteLn;
WriteString(" THE TOTAL NUMBER OF WORDS = ");   (* WRITE THE TOTAL     *)
WriteCard(NUMWORD,6);                           (* NUMBER OF WORDS     *)
WriteLn;                                        (* TO THE SCREEN       *)



CloseInput;
CloseOutput;
END CORDANCE.                                    (* END OF MAIN MODULE *)
