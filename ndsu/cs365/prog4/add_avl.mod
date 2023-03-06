(* From: "Algorithms & Data Structures" by: Niklaus Wirth
         pp. 218-224 ISBN 0-13-022005-1                       *)

PROCEDURE AVLInsert( VAR T : Tree;
                         s : Strings.String;
                 VAR ReBal : BOOLEAN );

    PROCEDURE LeftBal( VAR T : Tree );
      VAR T1, T2 : Tree;
      BEGIN
        T1 := T@.left;
        IF T1@.Fact = -1 THEN
          T@.left := T1@.right;
          T1@.right := T;
          T@.Fact := 0;
          T := T1;
        ELSE
          T2 := T1@.right;
          T1@.right := T2@.left;
          T2@.left := T1;
          T@.left := T2@.right;
          T2@.right := T;
          IF T2@.Fact = -1 THEN T@.Fact := 1 ELSE T@.Fact := 0 END;
          IF T2@.Fact = 1 THEN T@.Fact := -1 ELSE T@.Fact := 0 END;
          T := T2
        END;
        T@.Fact := 0;
      END LeftBal;

    PROCEDURE RightBal( VAR T : Tree );
      VAR T1, T2 : Tree;
      BEGIN
        T1 := T@.right;
        IF T1@.Fact = 1 THEN
          T@.right := T1@.left;
          T1@.left := T;
          T@.Fact := 0;
          T := T1;
        ELSE
          T2 := T1@.left;
          T1@.left := T2@.right;
          T2@.right := T1;
          T@.right := T2@.left;
          T2@.left := T;
          IF T2@.Fact = 1 THEN T@.Fact := -1 ELSE T@.Fact := 0 END;
          IF T2@.Fact = -1 THEN T@.Fact := 1 ELSE T@.Fact := 0 END;
          T := T2;
        END;
        T@.Fact := 0;
      END RightBal;

  BEGIN
    INC( LineNum );
    IF IsEmpty( T ) THEN ReBal := TRUE; AddNode( T, s )
    ELSIF Strings.CompareStr( s, T@.s ) = -1 THEN
      AVLInsert( T@.left, s, ReBal );
      IF ReBal THEN
        IF T@.Fact = 1 THEN
          T@.Fact := 0;
          ReBal := FALSE
        ELSIF T@.Fact = 0 THEN T@.Fact := -1
        ELSIF T@.Fact = 1 THEN LeftBal( T ); ReBal := FALSE
        END
      END
    ELSIF Strings.CompareStr( s, T@.s ) = 0 THEN
      (* allready in tree *)
    ELSIF Strings.CompareStr( s, T@.s ) = 1 THEN
      AVLInsert( T@.right, s, ReBal );
      IF ReBal THEN
        IF T@.Fact = 1 THEN T@.Fact := 0; ReBal := FALSE
        ELSIF T@.Fact = 0 THEN T@.Fact := 1
        ELSIF T@.Fact = 1 THEN RightBal( T ); ReBal := FALSE
        END
      END
    END
  END AVLInsert;
IMPLEMENTATION MODULE BST;

(*


*)
FROM Strings IMPORT
    Pos, Length, String, CompareStr;
FROM FInOut IMPORT
    FWrite, FILE, FWriteLn, FWriteString;
FROM InOut IMPORT
    Write, WriteString, WriteCard, WriteLn, ReadInt;
FROM Storage IMPORT
    ALLOCATE;
TYPE
   BST = POINTER TO TreeNode;

   TreeNode = RECORD;
               Item:String;
               Left, Right, Equal:BST;
            END;


PROCEDURE IsEqual(VAR A,B:String):BOOLEAN;
VAR P:INTEGER;
BEGIN
  P := 0;
   LOOP
      IF (A[P] = " ") AND (B[P]= " ") THEN;
         RETURN TRUE;
      ELSIF (A[P] # B[P]) THEN RETURN FALSE;
      END
   END;
END IsEqual;

PROCEDURE IsInBST(VAR T:BST;VAR Word:String):BOOLEAN;
(* Requires - An Initialized BST and an Initialized Word
   Modifies - Nothing
   Effects  - Returns True if Word is in BST, FALSE otherwise. *)
BEGIN

   IF T = NIL THEN;
      RETURN FALSE;
   ELSIF Pos(T@.Item, Word) < 5  THEN;
      RETURN TRUE;
   ELSIF CompareStr(Word, T@.Item) = -1 THEN;
      RETURN (IsInBST(T@.Left, Word));
   ELSE
      RETURN (IsInBST(T@.Right, Word));
   END;
END IsInBST;

PROCEDURE InitializeString(VAR A:String);
VAR I:INTEGER;
BEGIN
   FOR I := 0 TO 79 DO;
      A[I] := " ";
   END;
END InitializeString;

PROCEDURE CreateTree(VAR T:BST);
(* Requires - T of type BST.
   Modifies - T.
   Effects  - will initialized t. *)
BEGIN
   T := NIL;
END CreateTree;

PROCEDURE InsertBSTNode(VAR T:BST;VAR Word:String);
(* Requires - An initialized T, and a Non-empty Word
   Modifies - T.
   Effects  - Inserts Word into T, using the conventions of a binary
              search tree. *)
BEGIN
   IF T = NIL THEN;
      MakeTreeNode(T, Word);
   ELSIF CompareStr(Word, T@.Item) = -1 THEN;
      InsertBSTNode(T@.Left, Word);
   ELSIF CompareStr(Word, T@.Item) = 1 THEN;
      InsertBSTNode(T@.Right, Word);
   ELSE
      WriteString(" Tree Error Duplicate Node");WriteLn;
   END;
END InsertBSTNode;

PROCEDURE MakeTreeNode(VAR T:BST; Word:String);
(* Requires - an initialized Word.
   Modifies - T.
   Effects  - Allocates and initializes a new node T. *)
BEGIN
   ALLOCATE(T, SIZE(T@));
   T@.Item := Word;
   T@.Left := NIL;
   T@.Right := NIL;
   T@.Equal := NIL;
END MakeTreeNode;


PROCEDURE SaveInOrderTraverse(VAR F:FILE;VAR Memory:BST);
(* Requires - an open file f, and an initialized BST.
   Modifies - Nothing.
   Effects  - Does an inorder traversal of Memory but writes the output
              to an open file F. *)
VAR I:INTEGER;
BEGIN
   IF NOT TreeIsEmpty(Memory) THEN;
      SaveInOrderTraverse(F, Memory@.Left);
      FOR I := 0 TO 79 DO;

         FWrite(F, Memory@.Item[I]);
      END;
      FWriteLn(F);
      SavePrintEqual(F, Memory@.Equal);
      SaveInOrderTraverse(F, Memory@.Right);
   END;
END SaveInOrderTraverse;


PROCEDURE TreeIsEmpty(B:BST):BOOLEAN;
(* Requires - an initialized tree b.
   Modifies - nothing.
   Effects  - returns true of b is empty else it returns false. *)
BEGIN
   RETURN (B = NIL);
END TreeIsEmpty;

PROCEDURE InsertSpecialBSTNode(VAR Memory:BST; VAR Output, Word:String);
(* Requires - an initalized BST Memory, 2 strings output and word that ar
              initialized and non-empty.
   Modifies - Memory.
   Effects  - Inserts Output into Memory based upon a Key word which shou
              be stored alone in Word, as well as in column 40 of Output.
*)
VAR BSTWord:String; P, Q:INTEGER;
BEGIN
   InitializeString(BSTWord); (* BSTWord is used to get key word from
                                 other nodes in tree *)
   IF Memory = NIL THEN
      MakeTreeNode(Memory, Output);
   ELSE
      P := 40; Q := 0;
      LOOP               (* Get key word from current node *)
         BSTWord[Q] := Memory@.Item[P];
         P := P + 1;Q := Q + 1;
         IF Memory@.Item[P] = " " THEN EXIT END;
      END;
      IF CompareStr(Word, BSTWord) = -1 THEN;
         InsertSpecialBSTNode(Memory@.Left, Output, Word);
      ELSIF CompareStr(Word, BSTWord) = 1 THEN;
         InsertSpecialBSTNode(Memory@.Right, Output, Word);
      ELSE               (* Modifies so there's 3 children of BST Node*)
         InsertSpecialEqualBSTNode(Memory@.Equal, Output);
      END;
   END;
END InsertSpecialBSTNode;


PROCEDURE InsertSpecialEqualBSTNode(VAR B:BST; VAR Output:String);
(* Requires - An initialized B, and output.
   Modifies - B.
   Effects  - Inserts a output into a 3rd child which is set aside for
              equal nodes. *)
BEGIN
   IF B = NIL THEN;
      MakeTreeNode(B, Output);
   ELSE
      InsertSpecialEqualBSTNode(B@.Equal, Output);
   END;
END InsertSpecialEqualBSTNode;

PROCEDURE SavePrintEqual(VAR F:FILE;VAR B:BST);
(* Requires - An open file F, and an initalized B.
   Modifies - Nothing.
   Effects  - Prints out all equal nodes of a node into an open file f.
*)
VAR I:INTEGER;
BEGIN
   IF B = NIL THEN;
   ELSE
      FOR I := 0 TO 79 DO;
         FWrite(F, B@.Item[I]);
      END;
      FWriteLn(F);
      SavePrintEqual(F, B@.Equal);
   END;
END SavePrintEqual;

END BST.
