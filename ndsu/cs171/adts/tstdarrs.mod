MODULE TstDArrs;    (* Test Dynamic Real Arrays *)
                   (* D. Bruce Erickson        *)
                   (* 10/04/87                 *)
FROM DynamArr IMPORT
   DynamicRealArray, RCreate, RDestroy, RLow, RHigh, RAssign, RFetch,
   DynamicIntegerArray,ICreate,IDestroy,ILow,IHigh,IAssign,IFetch,
  DynamicCardinalArray,CACreate,CADestroy,CALow,CAHigh,CAAssign,CAFetch,
   DynamicBooleanArray,BCreate,BDestroy,BLow,BHigh,BAssign,BFetch,
   DynamicCharArray,CHCreate,CHDestroy,CHLow,CHHigh,CHAssign,CHFetch;
FROM RealInOut IMPORT
  WriteReal;
FROM InOut IMPORT
  ReadInt, FlushLn, Write, WriteInt, WriteLn, WriteString;
FROM MathLib0 IMPORT
  real, pi;

VAR
  low, high, i : INTEGER;
  A : DynamicRealArray;
  B : DynamicIntegerArray;
  C : DynamicCardinalArray;
  D : DynamicBooleanArray;
  E : DynamicCharArray;


BEGIN
  REPEAT
    WriteString('First test real arrays---');
    WriteLn;
    WriteString('What is the low bound for the array?');
    WriteLn;
    ReadInt(low);
    FlushLn;
    WriteString('What is the high bound for the array?');
    WriteLn;
    WriteString('Make it equal the low bound to indicate final run.');
    WriteLn;
    ReadInt(high);
    FlushLn;
    A := RCreate(low,high);
    WriteString("The low bound for the array is: ");
    WriteInt(RLow(A),0);
    WriteLn;
    WriteString("The high bound for the array is: ");
    WriteInt(RHigh(A),0);
    WriteLn;
    FOR i := low TO high
      DO
        RAssign(A,i,real(i)*pi);
      END;
    FOR i := low TO high
      DO
        WriteInt(i,3);
        WriteReal(RFetch(A,i),20);
        WriteReal(real(i)*pi,20);
        WriteLn;
      END;
    RDestroy(A)
  UNTIL low = high;
  REPEAT
    WriteString('Next test Integer arrays---');
    WriteLn;
    WriteString('What is the low bound for the array?');
    WriteLn;
    ReadInt(low);
    FlushLn;
    WriteString('What is the high bound for the array?');
    WriteLn;
    WriteString('Make it equal the low bound to indicate final run.');
    WriteLn;
    ReadInt(high);
    FlushLn;
    B := ICreate(low,high);
    WriteString("The low bound for the array is: ");
    WriteInt(ILow(B),0);
    WriteLn;
    WriteString("The high bound for the array is: ");
    WriteInt(IHigh(B),0);
    WriteLn;
    FOR i := low TO high
      DO
        IAssign(B,i,i);
      END;
    FOR i := low TO high
      DO
        WriteInt(i,3);
        WriteInt(IFetch(B,i),20);
        WriteInt(i,20);
        WriteLn;
      END;
    IDestroy(B)
  UNTIL low = high;
  REPEAT
    WriteString('Next test Cardinal arrays---');
    WriteLn;
    WriteString('What is the low bound for the array?');
    WriteLn;
    ReadInt(low);
    FlushLn;
    WriteString('What is the high bound for the array?');
    WriteLn;
    WriteString('Make it equal the low bound to indicate final run.');
    WriteLn;
    ReadInt(high);
    FlushLn;
    C := CACreate(low,high);
    WriteString("The low bound for the array is: ");
    WriteInt(CALow(C),0);
    WriteLn;
    WriteString("The high bound for the array is: ");
    WriteInt(CAHigh(C),0);
    WriteLn;
    FOR i := low TO high
      DO
        CAAssign(C,i,CARDINAL(ABS(i)));
      END;
    FOR i := low TO high
      DO
        WriteInt(i,3);
        WriteInt(CAFetch(C,i),20);
        WriteInt(i,20);
        WriteLn;
      END;
    CADestroy(C)
  UNTIL low = high;
  REPEAT
    WriteString('Next test Boolean arrays---');
    WriteLn;
    WriteString('What is the low bound for the array?');
    WriteLn;
    ReadInt(low);
    FlushLn;
    WriteString('What is the high bound for the array?');
    WriteLn;
    WriteString('Make it equal the low bound to indicate final run.');
    WriteLn;
    ReadInt(high);
    FlushLn;
    D := BCreate(low,high);
    WriteString("The low bound for the array is: ");
    WriteInt(BLow(D),0);
    WriteLn;
    WriteString("The high bound for the array is: ");
    WriteInt(BHigh(D),0);
    WriteLn;
    FOR i := low TO high
      DO
        BAssign(D,i,ODD(i));
      END;
    FOR i := low TO high
      DO
        WriteInt(i,3);
        IF BFetch(D,i)
           THEN
              WriteString(' TRUE ')
           ELSE
              WriteString(' FALSE ')
           END;
        IF ODD(i)
           THEN
              WriteString(' TRUE ')
           ELSE
              WriteString(' FALSE ')
           END;
        WriteLn;
      END;
    BDestroy(D)
  UNTIL low = high;
  REPEAT
    WriteString('Next test Char arrays---');
    WriteLn;
    WriteString('What is the low bound for the array?');
    WriteLn;
    ReadInt(low);
    FlushLn;
    WriteString('What is the high bound for the array?');
    WriteLn;
    WriteString('Make it equal the low bound to indicate final run.');
    WriteLn;
    ReadInt(high);
    FlushLn;
    E := CHCreate(low,high);
    WriteString("The low bound for the array is: ");
    WriteInt(CHLow(E),0);
    WriteLn;
    WriteString("The high bound for the array is: ");
    WriteInt(CHHigh(E),0);
    WriteLn;
    FOR i := low TO high
      DO
        CHAssign(E,i,CHR(CARDINAL(ABS(i MOD 256))));
      END;
    FOR i := low TO high
      DO
        WriteInt(i,3);
        WriteString('     ');
        Write( CHFetch(E,i) );
        WriteString('     ');
        Write(CHR(CARDINAL(ABS(i MOD 256))));
        WriteLn;
      END;
    CHDestroy(E)
  UNTIL low = high;
  WriteString("End of test.");
  WriteLn
END TstDArrs.
