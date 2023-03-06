MODULE InfixToPrefix;

(***********************************************************************)
(*                                                                     *)
(*  MODULE TO CONVERT INFIX NOTATION TO PREFIX NOTATION                *)
(*                                                                     *)
(*  WRITTEN BY CHRISTOPHER C. TJON                                     *)
(*                                                                     *)
(*  FOR DR. ERICKSONS CS171                                            *)
(*                                                                     *)
(*  17 DECEMBER 1989                                                   *)
(*                                                                     *)
(*                                                                     *)
(*  THIS MODULE IS DESIGNED TO READ AN EXPRESSION IN INFIX FORM FROM   *)
(*  THE KEYBOARD AND PRODUCE THE EXPRESSION'S PREFIX EQUIVILENT.  SOME *)
(*  OF THE PROCEDURES SEEN HERE ARE MODIFICATIONS OF THOSE GIVEN ON    *)
(*  PAGES 142 THRU 145 IN THE TEXT:                                    *)
(*                                                                     *)
(*    A SECOND COURSE IN COMPUTER SCIENCE WITH MODULA-2                *)
(*                                                                     *)
(*    WRITTEN BY DANIEL D. MCCRACKEN AND WILLIAM I. SALMON             *)
(*                                                                     *)
(*  THE PROCEDURES INPREC AND STACKPREC ARE NOT ACTIVE COMPONENTS OF   *)
(*  THE CODE BUT I CHOSE TO LEAVE THEM HERE FOR POTENTIAL FUTURE       *)
(*  IMPLEMENTATION.                                                    *)
(*                                                                     *)
(***********************************************************************)
(*****< EXTERNAL MODULE IMPORTS >***************************************)
(***********************************************************************)

FROM STACKS IMPORT CREATESTACK, MAKESTACKEMPTY, PUSH, STACKTOP, STACK,
                   POP, STACKISEMPTY, STACKISFULL;

FROM SkipWhiteSpace IMPORT GetNextChar;  (***** THIS IS A FUNCTION *****)

FROM Strings        IMPORT String , Assign , Concat ;

FROM InOut IMPORT WriteString, WriteLn, WriteCard, Write, Read,
                  FlushLn, Done, OpenOutput, OpenInput, CloseOutput,
                  CloseInput;

(***********************************************************************)
(*****< VARIABLE DECLARATIONS >*****************************************)
(***********************************************************************)

VAR  OPERATORS : STACK   ;
     OPERANDS  : STACK   ;
     EOF       : BOOLEAN ;
     NEXTCHAR  : CHAR    ;
    STRINGCHAR : String  ;





(***********************************************************************)
(*****+------------------------+****************************************)
(*****| MAIN MODULE PROCEDURES |****************************************)
(*****+------------------------+****************************************)
(***********************************************************************)


(***********************************************************************)
(*****< FUNCTION PROCEDURE INPUT PRECEDENCE >***************************)
(***********************************************************************)

PROCEDURE INPREC( OPERATOR : CHAR ) : INTEGER;

(***********************************************************************)
(* REQUIRES : THAT THERE IS VALID INPUT                                *)
(* MODIFIES : NOTHING                                                  *)
(* EFFECTS  : RETURNS THE PRECEDENCE OF THE CHARACTER FROM INPUT       *)
(***********************************************************************)

BEGIN
  CASE OPERATOR OF

  ')'     : RETURN(0)|
  '+','-' : RETURN(1)|
  '*','/' : RETURN(3)|
  '('     : RETURN(5)

  END; (* CASE *)
END INPREC;


(***********************************************************************)
(*****< FUNCTION PROCEDURE STACK PRECEDENCE >***************************)
(***********************************************************************)

PROCEDURE STACKPREC( OPERATOR : CHAR ) : INTEGER;

(***********************************************************************)
(* REQUIRES : THAT THE STACK HAS HAD VALID DATA PUSHED ON TO IT        *)
(* MODIFIES : NOTHING                                                  *)
(* EFFECTS  : RETURNS THE PRECEDENCE OF AN OPERATOR IN THE OPERAND     *)
(*            STACK                                                    *)
(***********************************************************************)

BEGIN
  CASE OPERATOR OF

  '('     : RETURN(0)|
  '+','-' : RETURN(2)|
  '*','/' : RETURN(4)

  END; (* CASE *)
END STACKPREC;


(***********************************************************************)
(*****< FUNCTION PROCEDURE PRECEDENCE >*********************************)
(***********************************************************************)

PROCEDURE PRECEDENCE(ITEM : CHAR) : INTEGER ;

(***********************************************************************)
(* REQUIRES : A CHARACTER FROM THE SET { ( , * , / , + , - , ) }       *)
(* MODIFIES : NOTHING                                                  *)
(* EFFECTS  : RETURNS THE PRECEDENCE OF THAT CHARACTER AS A CARDINAL   *)
(***********************************************************************)

BEGIN
   CASE ITEM OF
      '('       : RETURN (0) ; |
      '*' , '/' : RETURN (1) ; |
      '+' , '-' : RETURN (2) ; |
      ')'       : RETURN (3) ;
   END (*CASE*) ;
END PRECEDENCE;

(***********************************************************************)
(*****< PROCEDURE PRINT OUTPUT HEADER >*********************************)
(***********************************************************************)

PROCEDURE PRINTOUTPUTHEADER;

(***********************************************************************)
(* REQUIRES : NOTHING                                                  *)
(* MODIFIES : NOTHING                                                  *)
(* EFFECTS  : PRINTS OUTPUT HEADER TO THE SCREEN                       *)
(***********************************************************************)

BEGIN
  WriteLn;
  WriteLn;
  WriteString("INFIX TO PREFIX CONVERSION PROGRAM");
  WriteLn;
  WriteLn;
  WriteString("  WRITTEN BY CHRISTOPHER C. TJON   ");
  WriteLn;
  WriteString("  FOR DR. ERICKSON'S CS171         ");
  WriteLn;
  WriteString("  17 DEC 1989                      ");
  WriteLn;
  WriteLn;
  WriteString("INFIX EXPRESSION:  ");
END PRINTOUTPUTHEADER;


(***********************************************************************)
(*****< PROCEDURE PARTIAL CONVERSION >**********************************)
(***********************************************************************)

PROCEDURE PARTIALCONVERSION(VAR OPERANDS : STACK ; STOPERANDS : String);

(***********************************************************************)
(* REQUIRES : A STACK OF OPERANDS AND AN OPERATOR                      *)
(* MODIFIES : THE STACK                                                *)
(* EFFECTS  : CONVERTS THE TOP TWO OPERANDS ON THE STACK AND THE       *)
(*            OPERATOR INTO A PREFIX EXPRESSION. THE EXPRESSION IS     *)
(*            THEN PUSHED BACK ON THE STACK. THEN STACK IS RETURNED    *)
(***********************************************************************)

VAR LVAR1 , LVAR2 , TSTRING1 , TSTRING2 : String;

BEGIN
   POP (OPERANDS , LVAR1);
   POP (OPERANDS , LVAR2);
   Concat (LVAR2 , LVAR1 , TSTRING1);
   Concat (STOPERANDS , TSTRING1 , TSTRING2);
   PUSH (OPERANDS , TSTRING2);
END PARTIALCONVERSION;


(***********************************************************************)
(*****< PROCEDURE PROCESS PARENTHESES >*********************************)
(***********************************************************************)

PROCEDURE PROCESSPARENTHESES (VAR OPERATORS , OPERANDS : STACK ;
                              NEXTCH : CHAR) ;

(***********************************************************************)
(* REQUIRES : A STACK OF OPERATORS, A STACK OF OPERANDS, AND A CHAR    *)
(* MODIFIES : BOTH STACKS                                              *)
(* EFFECTS  : WRITES THE CHARACTER, THEN FINISHES CONVERTING THE       *)
(*            DATA BETWEEN A SET OF PARENTHESES                        *)
(***********************************************************************)

VAR LOPERATOR : String ;
    COPERATOR : CHAR   ;

BEGIN
   WriteString(NEXTCH);
   POP (OPERATORS , LOPERATOR);
   Assign (LOPERATOR , COPERATOR);
   WHILE (PRECEDENCE (COPERATOR) # 0) DO
      PARTIALCONVERSION (OPERANDS , LOPERATOR);
      POP (OPERATORS , LOPERATOR);
      Assign (LOPERATOR , COPERATOR);
   END; (* WHILE *)
END PROCESSPARENTHESES;


(***********************************************************************)
(*****< PROCEDURE PROCESS ADD SUBTRACT >********************************)
(***********************************************************************)

PROCEDURE PROCESSADDSUBTRACT (VAR OPERATORS , OPERANDS : STACK;
                              NEXTCH : CHAR);

(***********************************************************************)
(* REQUIRES : A STACK OF OPERATORS, STACK OF OPERANDS, AND A CHARACTER *)
(* MODIFIES : BOTH STACKS                                              *)
(* EFFECTS  : WRITES THE CHARACTER, AND THEN PROCESSES IT ACCORDING    *)
(*            TO IT'S PRECEDENCE RELATIVE TO THE LAST OPERATOR         *)
(*            PROCESSED                                                *)
(***********************************************************************)

VAR STRINGCHAR , LASTOPERATOR : String ;
                 CHAROPERATOR : CHAR   ;

BEGIN
   WriteString (NEXTCH);
   IF (NOT STACKISEMPTY (OPERATORS)) THEN
      POP (OPERATORS , LASTOPERATOR);
      Assign (LASTOPERATOR , CHAROPERATOR);
      IF ((PRECEDENCE (CHAROPERATOR) = 1)
      OR (PRECEDENCE(CHAROPERATOR) = 2)) THEN
         PARTIALCONVERSION(OPERANDS , LASTOPERATOR);
      ELSE
         Assign (CHAROPERATOR , LASTOPERATOR);
         PUSH (OPERATORS , LASTOPERATOR);
      END; (* IF *)
   END; (* IF *)
   Assign (NEXTCH , STRINGCHAR);
   PUSH (OPERATORS , STRINGCHAR);
END PROCESSADDSUBTRACT;


(***********************************************************************)
(*****< PROCEDURE COMPLETE CONVERSION >*********************************)
(***********************************************************************)

PROCEDURE COMPLETECONVERSION (VAR OPERATORS , OPERANDS : STACK;
                              NEXTCH : CHAR);

(***********************************************************************)
(* REQUIRES : A STACK OF OPERATORS, STACK OF OPERANDS, AND A CHARACTER *)
(* MODIFIES : THE STACKS                                               *)
(* EFFECTS  : FINISHES WRITING OUT THE CURRENT INFIX EXPRESSION        *)
(*            FINISHES CONVERSION TO A PREFIX EXPRESSION               *)
(*            PROMPTS USER FOR THE NEXT INFIX EXPRESSION               *)
(***********************************************************************)

VAR PREFIXSTRING , LASTOPERATOR : String ;
                   CHAROPERATOR : CHAR   ;

BEGIN
   WriteLn; WriteLn;
   WHILE (NOT STACKISEMPTY (OPERATORS)) DO
      POP (OPERATORS , LASTOPERATOR);
      Assign (LASTOPERATOR , CHAROPERATOR);
      PARTIALCONVERSION(OPERANDS , LASTOPERATOR);
   END; (* WHILE *)
   POP (OPERANDS , PREFIXSTRING);
   WriteString ("PREFIX EXPRESSION:  ");
   WriteString (PREFIXSTRING); WriteLn;
   WriteLn;
   MAKESTACKEMPTY (OPERATORS);
   MAKESTACKEMPTY (OPERANDS);
   IF (NEXTCH = ';') THEN
      WriteString ("INFIX EXPRESSION:   ");
   ELSE
      WriteLn;
   END; (* IF *)
END COMPLETECONVERSION;


(***********************************************************************)
(*****+--------------+**************************************************)
(*****| MAIN PROGRAM |**************************************************)
(*****+--------------+**************************************************)
(***********************************************************************)

BEGIN
   OpenOutput("");
   PRINTOUTPUTHEADER;
   OpenInput("");
   EOF := FALSE;
   CREATESTACK (OPERATORS);
   CREATESTACK (OPERANDS);
   WHILE (NOT EOF) DO
      NEXTCHAR := GetNextChar();
      IF (NOT Done) THEN
         EOF := TRUE;
         CloseInput;
      ELSE
         CASE NEXTCHAR OF
            '(' , '*' , '/' : WriteString (NEXTCHAR);
                              Assign (NEXTCHAR , STRINGCHAR);
                              PUSH (OPERATORS , STRINGCHAR); |
            ')'             : PROCESSPARENTHESES(OPERATORS , OPERANDS ,
                                                 NEXTCHAR); |
            '+' , '-'       : PROCESSADDSUBTRACT (OPERATORS, OPERANDS ,
                                                  NEXTCHAR); |
            ';' , '.'       : COMPLETECONVERSION (OPERATORS , OPERANDS ,
                                                  NEXTCHAR)
         ELSE
            WriteString (NEXTCHAR);
            Assign (NEXTCHAR , STRINGCHAR);
            PUSH (OPERANDS , STRINGCHAR);
         END; (* CASE *)
      END; (* IF *)
   END; (* WHILE *)
   CloseOutput;
END InfixToPrefix.
