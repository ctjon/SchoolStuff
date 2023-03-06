MODULE TestNames;
(* Program to determine the names in a string
            J. M. Adams   January 1988 *)
FROM InOut IMPORT WriteString, WriteLn, ReadString;
FROM Strings IMPORT String, Copy, Pos, Length;

PROCEDURE SplitNames(FullName: String;
                     VAR FirstName, LastName: String);

VAR CommaPos: CARDINAL;

BEGIN;
  CommaPos := Pos(",", FullName);
  Copy(FullName, 0, CommaPos, LastName);
  Copy(FullName, CommaPos + 1,
       Length(FullName) - CommaPos - 1, FirstName);
END SplitNames;

VAR Full, First, Last: String;

BEGIN (* TestNames *)
  WriteString("Enter a name in the form: last name,first name");
  WriteLn;
  ReadString(Full); WriteLn;
  SplitNames(Full, First, Last);
  WriteString("The first name is: ");
  WriteString(First); WriteLn;
  WriteString("The last name is: ");
  WriteString(Last); WriteLn;
END TestNames.
