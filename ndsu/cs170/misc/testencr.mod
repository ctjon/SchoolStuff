MODULE TestEncrypt;
(* Tests the Encrypt program from pg 230 of the text.  The missing
   string routines are provided.
   Implemented on CMS by D. Bruce Erickson 10/5/89 *)

FROM InOut IMPORT ReadString, WriteString, WriteLn;

FROM Strings IMPORT String, Length;

VAR
   TheString : String;

PROCEDURE FetchChar( S : ARRAY OF CHAR; I : CARDINAL) : CHAR;
(* REQUIRES -  I is between 0 and Length(S) - 1
   EFFECTS  -  returns the character in position I of the string S
               The "first" character of S is in position 0, the
               "second" character of S is in position 1, etc. *)
BEGIN
  RETURN S(:I:)
END FetchChar;

PROCEDURE AssignChar(CH : CHAR; VAR S : ARRAY OF CHAR; I : CARDINAL);
(* REQUIRES -  I is between 0 and Length(S) - 1
   MODIFIES -  S
   EFFECTS  -  replaces the character at position I of the string with
               CH *)
BEGIN
  S(:I:) := CH;
END AssignChar;

PROCEDURE Encrypt( VAR Str : String);
(* REQUIRES - Str is a valid initialized string.
   MODIFIES - Str
   EFFECTS  - Replaces Str by a simple encryption of Str:  each digit
              '0', through '8' is increased to the next value, '9' is
              changed to '0'.  So the input string '30291' is changed
              to '41302' *)

VAR  CharPos : CARDINAL;
     Ch      : CHAR;

BEGIN
  FOR CharPos := 0 TO Length(Str) - 1 DO
    Ch := FetchChar(Str, CharPos);              (* get character *)
    IF Ch = '9' THEN
       AssignChar('0', Str, CharPos);
    ELSE
       INC(Ch);                                 (* increment it *)
       AssignChar(Ch, Str, CharPos);            (* put it back  *)
    END;  (* IF *)
  END;  (* FOR *)
END Encrypt;

BEGIN
  WriteString("Enter a string of digits 0 - 9.");
  WriteLn;
  ReadString(TheString);
  WriteString(TheString);
  WriteString(" after encryption becomes:  ");
  WriteLn;
  Encrypt(TheString);
  WriteString(TheString);
  WriteLn;
END TestEncrypt.
