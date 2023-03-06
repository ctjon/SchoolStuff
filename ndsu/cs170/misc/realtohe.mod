MODULE RealToHex;
FROM InOut IMPORT WriteString, WriteLn;
FROM RealInOut IMPORT ReadReal, WriteReal, WriteRealHex;
VAR
  i : REAL;
BEGIN
  REPEAT
    WriteString("Enter a real number.");
    WriteString(". Enter 0.0 to stop.");
    WriteLn;
    ReadReal(i);
    WriteLn;
    WriteString("The real "); WriteReal(i,10);
    WriteString( "in hex is ");
    WriteRealHex(i); WriteLn;
  UNTIL i = 0.0
END RealToHex.
