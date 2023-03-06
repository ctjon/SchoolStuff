MODULE Power;
FROM InOut IMPORT
 WriteString, WriteCard, ReadCard, WriteLn;

VAR
  A , B  : CARDINAL;
  J : REAL;
PROCEDURE Pow ( m,n : CARDINAL) : CARDINAL;
VAR
  TEMP : CARDINAL;
BEGIN
  WriteString("Just entered Pow with m,n: ");
  WriteCard(m,3);WriteCard(n,3);WriteLn;
  IF (n = 0) THEN
    WriteString("               RETURNING:  1");WriteLn;
    RETURN 1
  ELSIF ODD(n) THEN
    WriteString("     Found n was odd"); WriteLn;
    WriteString("     I'll compute "); WriteCard(m,3);
    WriteString(" * Pow(");WriteCard(m*m,3);WriteString(",");
    WriteCard((n-1) DIV 2,3);WriteString(")"); WriteLn;
    TEMP :=(m * Pow(m*m, (n-1) DIV 2));
    WriteString("               RETURNING:  ");WriteCard(TEMP,3);
    WriteLn;
    RETURN TEMP
  ELSE (* n is even and > 0 *)
    WriteString("     Found n was even"); WriteLn;
    WriteString("     I'll compute ");
    WriteString(" * Pow(");WriteCard(m*m,3);WriteString(",");
    WriteCard(n DIV 2,3);WriteString(")"); WriteLn;
    TEMP :=  ( Pow(m*m, n DIV 2) );
    WriteString("               RETURNING:  ");WriteCard(TEMP,3);
    WriteLn;
    RETURN TEMP
  END
END Pow;

BEGIN
  WriteString("What are the values of base and exponent?");
  WriteLn;
  ReadCard(A);ReadCard(B);
  WriteCard(A,3);
  WriteString(" to the power ");
  WriteCard(B,3);
  WriteString(" is:  "); WriteLn;
  WriteCard(Pow(A,B),3);
  WriteLn;
END Power.
