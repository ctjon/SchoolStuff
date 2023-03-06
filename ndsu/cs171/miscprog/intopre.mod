(* It turns out I had this problem done already so here it is. *)
(* D. Bruce Erickson -- Winter Quarter 1988- 1989 *)
(* Example of syntax directed translation from infix to prefix *)
(* using recursion. *)
(* <infix> ::= <term> <IRest>
   <IRest> ::= + <term> <IRest>
             | - <term> <IRest>
             | <empty string>
   <term>  ::= <factor> <FRest>
   <FRest> ::= * <factor> <FRest>
             | / <factor> <FRest>
             | <empty string>
   <factor> ::= (<infix>)
              | <letter>
   <letter> ::= 'a'|..|'z'|'A'|..|'Z'
*)

MODULE InToPre;
FROM Strings IMPORT String,Concat;
FROM InOut IMPORT Write, WriteString, WriteLn, OpenInput, OpenOutput,
     CloseInput, CloseOutput;
FROM SkipWhiteSpace IMPORT GetNextChar;

TYPE
  CHARSET = SET OF CHAR;

VAR
  Terminator : CHAR;
  PrefixExpression : String;

  PROCEDURE CharToString(CH : CHAR; VAR S : String);
  BEGIN
    S := " ";
    S(:0:) := CH
  END CharToString;

  PROCEDURE Infix(VAR Expr : String; VAR NextCH : CHAR);
  VAR
    RightOperand : String;
    Operator : String;
  BEGIN
    Term(Expr, NextCH);
    WHILE NextCH IN CHARSET { '+', '-' } DO
      CharToString(NextCH, Operator);
      Term(RightOperand,NextCH);
      Concat(Operator, Expr, Expr);
      Concat(Expr, RightOperand, Expr)
    END;
  END Infix;

  PROCEDURE Term(VAR Expr : String; VAR NextCH : CHAR);
  VAR
    RightOperand : String;
    Operator : String;
  BEGIN
    Factor(Expr,NextCH);
    WHILE NextCH IN CHARSET { '*', '/' } DO
      CharToString(NextCH,Operator);
      Factor(RightOperand,NextCH);
      Concat(Operator, Expr, Expr);
      Concat(Expr, RightOperand, Expr)
    END;
  END Term;

  PROCEDURE Factor(VAR Expr : String; VAR NextCH : CHAR);
  VAR
    CH : CHAR;
  BEGIN
    CH := GetNextChar();
    Write(CH);
    IF CH = '(' THEN
      Infix(Expr, NextCH)              (* NextCH is ')' *)
    ELSE
      CharToString(CH,Expr);
    END;
      NextCH := GetNextChar();
      Write(NextCH)
  END Factor;

BEGIN
  OpenInput("");
  OpenOutput("");
  REPEAT
    WriteString("Input infix expression:  ");
    Infix(PrefixExpression,Terminator);
    WriteLn;
    WriteString("Yields the prefix expression:  ");
    WriteString(PrefixExpression);
    WriteLn;
  UNTIL Terminator = '.';
  CloseInput;
  CloseOutput
END InToPre.
