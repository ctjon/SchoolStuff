
MODULE cs171p2              ;

FROM SkipWhiteSpace IMPORT GetNextChar ;
FROM Strings        IMPORT String , Assign , Concat ;
FROM StackADT       IMPORT Stack , CreateStack , Push , Pop ,
                           StackIsEmpty , MakeStackEmpty ;
FROM InOut          IMPORT WriteString , WriteLn , OpenOutput ,
                           CloseOutput , OpenInput , CloseInput , Done ;

VAR Operators , Operands : Stack   ;
               EndOfFile : BOOLEAN ;
                NextChar : CHAR    ;
              StringChar : String  ;

PROCEDURE PrintOutputHeader ;

(*+----------------------------+
  |                            |
  |  PROCEDURE                 |
  |                            |
  |  prints my output header.  |
  |                            |
  +----------------------------+*)

BEGIN (*PrintOutputHeader*)
   WriteLn ;
   WriteLn ;
   WriteString ("***************************************") ; WriteLn ;
   WriteString ("***************************************") ; WriteLn ;
   WriteLn ;
   WriteLn ;
   WriteString ("INFIX EXPRESSION:   ") ;
END PrintOutputHeader ;

PROCEDURE Precedence (Item : CHAR) : INTEGER ;

(*+-------------------------------------------------------------------+
  |                                                                   |
  |  FUNCTION Precedence                                              |
  |                                                                   |
  |  requires a character from the set { ( , * , / , + , - , ) } and  |
  |  and returns the precedence of that character as an integer.      |
  |                                                                   |
  +-------------------------------------------------------------------+*)

BEGIN (*Precedence*)
   CASE Item OF
      '('       : RETURN (0) ; |
      '*' , '/' : RETURN (1) ; |
      '+' , '-' : RETURN (2) ; |
      ')'       : RETURN (3) ;
   END (*CASE*) ;
END Precedence ;

PROCEDURE PartialConversion (VAR Opnds : Stack ; StringOp : String) ;

(*+------------------------------------------------------------+
  |                                                            |
  |  PROCEDURE PartialConversion                               |
  |                                                            |
  |  requires a stack of operands and an operator.             |
  |  converts the top two operands on the stack and the        |
  |  operator into a prefix expression, pushes the expression  |
  |  back on the stack, and then returns the stack.            |
  |                                                            |
  +------------------------------------------------------------+*)

VAR LastVar1 , LastVar2 , TempString1 , TempString2 : String ;

BEGIN (*PartialConversion*)
   Pop (Opnds , LastVar1)                        ;
   Pop (Opnds , LastVar2)                        ;
   Concat (LastVar2 , LastVar1 , TempString1)    ;
   Concat (StringOp , TempString1 , TempString2) ;
   Push (Opnds , TempString2)                    ;
END PartialConversion ;

PROCEDURE ProcessParentheses (VAR Opators , Opands : Stack ;
                              NextCh : CHAR) ;

(*+-------------------------------------------------------------------+
  |                                                                   |
  |  PROCEDURE ProcessParentheses                                     |
  |                                                                   |
  |  requires a stack of operators, a stack of operands, and a char-  |
  |  acter.  writes the character, and then finishes converting the   |
  |  material between a set of parentheses.  modifies both stacks.    |
  |                                                                   |
  +-------------------------------------------------------------------+*)

VAR LastOperator : String ;
    CharOperator : CHAR   ;

BEGIN (*ProcessParentheses*)
   WriteString (NextCh)                         ;
   Pop (Opators , LastOperator)                 ;
   Assign (LastOperator , CharOperator)         ;
   WHILE (Precedence (CharOperator) # 0) DO
      PartialConversion (Opands , LastOperator) ;
      Pop (Opators , LastOperator)              ;
      Assign (LastOperator , CharOperator)      ;
   END (*WHILE*)                                ;
END ProcessParentheses ;

PROCEDURE ProcessAddSubtract (VAR Opators , Opands : Stack ;
                              NextCh : CHAR ) ;

(*+-------------------------------------------------------------------+
  |                                                                   |
  |  PROCEDURE ProcessAddSubtract                                     |
  |                                                                   |
  |  requires a stack of operators, a stack of operands, and a char-  |
  |  acter.  writes the character, and then processes it according    |
  |  to it's precedence relative to the last operator processed.      |
  |                                                                   |
  +-------------------------------------------------------------------+*)

VAR StringChar , LastOperator : String ;
                 CharOperator : CHAR   ;

BEGIN (*ProcessAddSubtract*)
   WriteString (NextCh)                           ;
   IF (NOT StackIsEmpty (Opators)) THEN
      Pop (Opators , LastOperator)                ;
      Assign (LastOperator , CharOperator)        ;
      IF ((Precedence (CharOperator) = 1) OR
                                  (Precedence(CharOperator) = 2)) THEN
         PartialConversion(Opands , LastOperator) ;
      ELSE
         Assign (CharOperator , LastOperator)     ;
         Push (Opators , LastOperator)            ;
      END (*IF*)                                  ;
   END (*IF*)                                     ;
   Assign (NextCh , StringChar)                   ;
   Push (Opators , StringChar)                    ;
END ProcessAddSubtract ;

PROCEDURE CompleteConversion (VAR Opators , Opands : Stack ;
                              NextCh : CHAR) ;

(*+-------------------------------------------------------------------+
  |                                                                   |
  |  PROCEDURE CompleteConversion                                     |
  |                                                                   |
  |  requires a stack of operators, a stack of operands, and a char-  |
  |  acter.  finishes writing out the current infix expression, fin-  |
  |  ishes converting it into a prefix expression, writes that out,   |
  |  and then prints a label for a new infix expression if necessary. |
                                                                      |
  +-------------------------------------------------------------------+*)

VAR PrefixString , LastOperator : String ;
                   CharOperator : CHAR   ;

BEGIN (*CompleteConversion*)
   WriteLn ; WriteLn                           ;
   WHILE (NOT StackIsEmpty (Opators)) DO
      Pop (Opators , LastOperator)             ;
      Assign (LastOperator , CharOperator)     ;
      PartialConversion(Opands , LastOperator) ;
   END (*WHILE*)                               ;
   Pop (Opands , PrefixString)                 ;
   WriteString ("PREFIX EXPRESSION:  ")        ;
   WriteString (PrefixString) ; WriteLn        ;
   WriteLn                                     ;
   MakeStackEmpty (Opators)                    ;
   MakeStackEmpty (Opands)                     ;
   IF (NextCh = ';') THEN
      WriteString ("INFIX EXPRESSION:   ")     ;
   ELSE
      WriteLn                                  ;
   END (*IF*)                                  ;
END CompleteConversion ;

BEGIN (*TranslateExpressions*)
   OpenOutput ("") ;
   PrintOutputHeader ;
   OpenInput ("") ;
   EndOfFile := FALSE ;
   CreateStack (Operators) ;
   CreateStack (Operands) ;
   WHILE (NOT EndOfFile) DO
      NextChar := GetNextChar () ;
      IF (NOT Done) THEN
         EndOfFile := TRUE ;
         CloseInput ;
      ELSE
         CASE NextChar OF
            '(' , '*' , '/' : WriteString (NextChar)         ;
                              Assign (NextChar , StringChar) ;
                              Push (Operators , StringChar)  ; |
            ')'             : ProcessParentheses(Operators , Operands ,
                                                 NextChar) ; |
            '+' , '-'       : ProcessAddSubtract (Operators, Operands ,
                                                  NextChar) ; |
            ';' , '.'       : CompleteConversion (Operators , Operands ,
                                                  NextChar) ;
         ELSE
            WriteString (NextChar)         ;
            Assign (NextChar , StringChar) ;
            Push (Operands , StringChar)   ;
         END (*CASE*) ;
      END (*IF*) ;
   END (*WHILE*) ;
   CloseOutput ;
END cs171p2 .
