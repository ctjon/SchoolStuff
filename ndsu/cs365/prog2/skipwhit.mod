IMPLEMENTATION MODULE SkipWhiteSpace;
(* The Abstraction Function is: A(r) = c{Set of All Non-White Characters}
   The Rep Invariant is: True
*)
FROM InOut IMPORT Read,EOL;

PROCEDURE GetNextChar(): CHAR;
(* modifies - the standard input file
    effects  - Returns the next nonwhite space character from the
              standart input file if there is one.
              InOut.Done is FALSE if end of file is reached.
*)

VAR Ch : CHAR;
BEGIN
	Read(Ch);
	WHILE (Ch = " ") OR (Ch= EOL)  DO
		Read(Ch);
	END;
	RETURN Ch;
END GetNextChar;

END SkipWhiteSpace.

