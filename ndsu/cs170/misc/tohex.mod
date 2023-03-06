MODULE ToHex;
FROM InOut IMPORT WriteString, ReadCard, WriteCard, WriteHex, WriteLn;

VAR
  i : CARDINAL;
BEGIN
  REPEAT
    WriteString("Enter an cardinal between 0 and ");
    WriteCard(MAX(CARDINAL),10);WriteString(". Enter 0 to stop.");
    WriteLn;
    ReadCard(i);
    WriteLn;
    WriteString("The integer "); WriteCard(i,10);
    WriteString( "in hex is ");
    WriteHex(i,10); WriteLn;
  UNTIL i = 0
END ToHex.
