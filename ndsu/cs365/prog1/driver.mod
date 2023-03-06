MODULE Driver;
(***********************************************************************)
(* Program 1                                                           *)
(* Written By: Chris Tjon                                              *)
(* NAID# 110975-8                                                      *)
(* 9 December 1991                                                     *)
(* For: Dr. Erickson's CS365                                           *)
(***********************************************************************)

FROM InOut IMPORT WriteLn, Write, WriteString, OpenInput, CloseInput,
                  OpenOutput, CloseOutput;
FROM SkipWhiteSpace IMPORT GetNextChar;
FROM Trees IMPORT Tree, Child, NullTree, Copy, Clear, Construct,
                  SwapChild, IsNull, ItemOf, ChildOf;
FROM Items IMPORT Item;
TYPE CharSet = SET OF CHAR;
CONST Operator = CharSet {"+","-","*","/"};
CONST Operand = CharSet {"a","b","c","d","e","f","g","h","i","j","k","l",
"m","n","o","p","q","r","s","t","u","v","w","x","y","z","A","B","C","D",
"E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V",
"W","X","Y","Z"};
VAR ExpressionTree : Tree;

PROCEDURE PostOrderTraversal(T : Tree );
(***********************************************************************)
(* Requires: The Tree has been initialized                             *)
(* Modifies: Nothing                                                   *)
(* Effects:  Performs a Post Order Traversal of a tree                 *)
(***********************************************************************)
VAR CH:Item;
BEGIN
  IF NOT IsNull( T ) THEN
    PostOrderTraversal(ChildOf(T,Left));
    PostOrderTraversal(ChildOf(T,Right));
    ItemOf(T,CH);
    Write(CH);
  END (* If Not IsNull *)
END PostOrderTraversal;

PROCEDURE StoreItem(VAR T:Tree);
(***********************************************************************)
(* Requires: That T is a valid tree                                    *)
(* Modifies: T                                                         *)
(* Effects:  The Item CH is stored in the Tree T                       *)
(***********************************************************************)
VAR CH : Item;
    LCH,RCH:Tree;

BEGIN
    CH := GetNextChar();
    IF (CH IN Operator) THEN StoreItem(T);
        Construct(CH,T,Left);
        StoreItem(RCH);
        SwapChild(Right,T,RCH);
    ELSIF (CH IN Operand) THEN
        T := NullTree();
        Construct(CH,T,Left);
    ELSE
        WriteString("Input Is Invalid --> ");
        Write(CH);
        WriteLn;
END;
END StoreItem;


PROCEDURE PreorderTraversal(T : Tree);
(***********************************************************************)
(* Requires: That T has been initialized                               *)
(* Modifies: Nothing                                                   *)
(* Effects : Prints A preorder Traversal Of the Tree T                 *)
(***********************************************************************)

VAR CH:Item;

BEGIN
    IF (NOT IsNull(T)) THEN
        ItemOf(T,CH);
        Write(CH);
        PreorderTraversal(ChildOf(T,Left));
        PreorderTraversal(ChildOf(T,Right));
    END;
END PreorderTraversal;

PROCEDURE Output(T : Tree);
(***********************************************************************)
(* Requires: Nothing                                                   *)
(* Modifies: Nothing                                                   *)
(* Effects: Prints Out The Output in the Format Specified              *)
(***********************************************************************)

BEGIN
    WriteString("The Prefix Expression --> ");
    PreorderTraversal(T);
    WriteLn;
    WriteString("Has The Postfix Expression --> ");
    PostOrderTraversal(T);
    WriteLn;
    WriteLn;
END Output;

PROCEDURE Input(VAR T: Tree);
(***********************************************************************)
(* Requires: T is a valid Tree                                         *)
(* Modifies: T                                                         *)
(* Effects:  Processes Prefex Expression                               *)
(***********************************************************************)
VAR CH: Item;
BEGIN
    StoreItem(T);
    Output(T);
    Clear(T);
    CH := GetNextChar();
LOOP
    IF (CH = ".") THEN
        EXIT
    END;
    StoreItem(T);
    Output(T);
    Clear(T);
    CH := GetNextChar();
END;
END Input;

PROCEDURE PrintOutputHeader;
(***********************************************************************)
(* Requires: Nothing                                                   *)
(* Modifies: Nothing                                                   *)
(* Effects:  Prints the Output Header To the screen                    *)
(***********************************************************************)

BEGIN
        WriteLn;
        WriteLn;
        WriteString("Prefix to Postfix Conversion Program");
        WriteLn;
        WriteLn;
        WriteString("  Written By: Christopher C. Tjon   ");
        WriteLn;
        WriteString("  For Dr. Erickson's CS365          ");
        WriteLn;
        WriteString("  9 December 1991                   ");
        WriteLn;
        WriteLn;
END PrintOutputHeader;


BEGIN
  OpenOutput("");
  OpenInput("");
  PrintOutputHeader;
  ExpressionTree := NullTree();
  Input(ExpressionTree);
  CloseInput;
  CloseOutput;
END Driver.
