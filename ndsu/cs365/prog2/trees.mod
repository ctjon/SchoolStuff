IMPLEMENTATION MODULE Trees;
(* The Abstraction Mapping is
    A(r) = [] if r is nil
    A(r) = [t.stuf] || A(t.RightChild) || A(t.LeftChild)
    where t = value_some(r)
*)
(* The rep invariant for expression trees is:
   An expression tree has operators for its interior nodes and
   operands for its leaf nodes
*)

FROM Items 	IMPORT 	Item;
FROM InOut 	IMPORT 	WriteString, WriteLn;
FROM Storage 	IMPORT 	Available, ALLOCATE, DEALLOCATE;
TYPE
 Tree = POINTER TO Node;
  Node = RECORD
   Item : Item;
   LeftChild,RightChild :Tree;
   END;


PROCEDURE NullTree() : Tree;
(* effects - returns the Null Tree.  May be used to initialize a
             variable of type Tree
*)
BEGIN
	RETURN NIL;
END NullTree;


PROCEDURE MakeNode(VAR  T : Tree; Stuf : Item; LeftChild, RightChild : Tree);
(******************************************************************************)
(* Requires: T is a valid tree                                                *)
(* Modifies: T                                                                *)
(* Effects:  Creates a new tree with item as its root and LeftChild and       *)
(*           RightChild as its specified left and right child respectively    *)
(******************************************************************************)

 BEGIN
 	IF Available(SIZE(T@)) THEN
		ALLOCATE(T,SIZE(T@));
	ELSE
		WriteString("A Memory Allocation Error Has Occurred - Goodbye");
		WriteLn;
		HALT;
	END;
    T@.Item:= Stuf;
 	T@.LeftChild :=LeftChild;
 	T@.RightChild:=RightChild;
 END MakeNode;


PROCEDURE Copy (theTree : Tree) : Tree;
(* effects - Returns a copy of theTree
*)
VAR T : Tree;
BEGIN
 MakeNode(T, theTree@.Item,
  Copy(theTree@.LeftChild),
  Copy(theTree@.RightChild));
 RETURN T;
END Copy;


PROCEDURE Clear (VAR TheTree : Tree);
(* requires - TheTree has been initialized to a valid Tree
   modifies - TheTree
   effects  - Removes all nodes if any from TheTree and makes TheTree
              null.
*)

BEGIN
	IF NOT IsNull(TheTree) THEN
	Clear(TheTree@.LeftChild);
	Clear(TheTree@.RightChild);
	DEALLOCATE(TheTree, SIZE(TheTree@));
	TheTree := NullTree();
	END;
END Clear;


PROCEDURE Construct(TheItem     : Item;
                 VAR AndTheTree : Tree;
                    OnTheChild  : Child);
(* requires - AndTheTree must be a valid tree, possibly null.
   modifies - AndTheTree
   effects  - Adds TheItem at the root of AndTheTree;  the original
              tree (passed in AndTheTree) becomes the specified child
              of the new node and the
              other child of AndTheTree is made null.
*)
VAR T : Tree;

BEGIN
	T := AndTheTree;
	IF (OnTheChild = Left) THEN
		MakeNode(AndTheTree, TheItem, T, NullTree());
	ELSE
		MakeNode(AndTheTree, TheItem, NullTree(), T);
	END;
END Construct;


PROCEDURE SwapChild(TheChild  : Child;
               VAR OfTheTree  : Tree;
               VAR AndTheTree : Tree);
(* requires - OfTheTree and AndTheTree must have been initialized to
              valid trees.
   modifies - OfTheTree and AndTheTree
   effects  - Exchanges the specified child of OfTheTree with the entire
              tree AndTheTree.
*)
VAR T : Tree;

BEGIN
	IF (TheChild = Left) THEN
		T := ChildOf(OfTheTree, Left);
		OfTheTree@.LeftChild := AndTheTree;
		AndTheTree := T;
	ELSE
		T := ChildOf(OfTheTree, Right);
		OfTheTree@.RightChild := AndTheTree;
		AndTheTree := T;
	END;
END SwapChild;


PROCEDURE IsNull(TheTree: Tree):BOOLEAN;
(* requires - TheTree must have been initalized to a valid tree.
   effects  - Returns TRUE if TheTree is Null else returns FALSE.
*)
BEGIN
	IF (TheTree = NIL) THEN
		RETURN(TRUE);
	ELSE
		RETURN(FALSE);
	END;
END IsNull;


PROCEDURE ItemOf(TheTree : Tree;
             VAR TheItem : Item);
(* requires - TheTree is a non null tree.
   modifies - TheItem
   effects  - Sets TheItem to TheItem of the root node of TheTree
*)
BEGIN
	TheItem := TheTree@.Item;
END ItemOf;


PROCEDURE ChildOf(TheTree :  Tree;
                  TheChild : Child): Tree;
(* requires - TheTree must be a nun null tree
   effects  - Returns the specified child of the given tree.
*)
BEGIN
	IF (TheChild = Left) THEN
		RETURN TheTree@.LeftChild;
	ELSE
		RETURN TheTree@.RightChild;
	END;
END ChildOf;

END Trees.

