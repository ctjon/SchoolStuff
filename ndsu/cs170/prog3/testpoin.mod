MODULE TestPoints;

(* MODULE TO TEST POINTS MODULES
   WRITTEN BY: CHRISTOPHER C. TJON
   NAID# 110975-8
   CS170 , 4 OCTOBER 1989
   DR. ERICKSON *)

FROM RealInOut IMPORT ReadReal,WriteReal;
FROM InOut IMPORT WriteLn,WriteString;
FROM Points IMPORT Point, DistanceToOrigin,AddPoints,SubtractPoints,
                   MultiplyPoints,DividePoints,ReflectOrigin;

VAR TestP1, TestP2, Result:Point;
    Distance : REAL;
    X : INTEGER;

PROCEDURE PrintPoints(P:Point);
(* REQUIRES : INPUT OF A POINT
   MODIFIES : NOTHING
   EFFECTS  : PRINTS OUT THE POINT IN THE FORM (X,Y) *)

BEGIN
  WriteString("(");
  WriteReal(P.X,4);
  WriteString(",");
  WriteReal(P.Y,4);
  WriteString(")");
  WriteLn;
END PrintPoints;


BEGIN (* TESTPOINTS MODULE *)
  FOR X:= 1 TO 5 DO    (* LOOP 5 TIMES FOR BETTER TEST *)

  WriteLn;

  (* GET INPUT FROM USER *)

  WriteString("PLEASE ENTER THE FIRST X - COORDINATE.");
  WriteLn;
  ReadReal(TestP1.X);

  WriteLn;
  WriteString("PLEASE ENTER THE FIRST Y - COORDINATE.");
  WriteLn;
  ReadReal(TestP1.Y);

  WriteLn;
  WriteString("PLEASE ENTER THE SECOND X - COORDINATE.");
  WriteLn;
  ReadReal(TestP2.X);

  WriteLn;
  WriteString("PLEASE ENTER THE SECOND Y - COORDINATE.");
  WriteLn;
  ReadReal(TestP2.Y);
  WriteLn;

  (* ECHO THE DATA *)

  WriteString("THE POINTS ARE  ");
  WriteLn;
  PrintPoints(TestP1);
  PrintPoints(TestP2);
  WriteLn;

  (* EXECUTE THE TEST PROCEDURES *)

  Distance := DistanceToOrigin(TestP1);
  WriteString("THE DISTANCE BETWEEN THE FIRST POINT AND ORIGIN IS ");
  WriteReal(Distance,6);
  WriteLn;

  Distance := DistanceToOrigin(TestP2);
  WriteString("THE DISTANCE BETWEEN THE SECOND POINT AND ORIGIN IS ");
  WriteReal(Distance,6);
  WriteLn;

  AddPoints(TestP1,TestP2,Result);
  WriteString("THE SUM OF THE POINTS IS  ");
  PrintPoints(Result);
  WriteLn;

  SubtractPoints(TestP1,TestP2,Result);
  WriteString("THE SUBTRACTION OF POINT 1 FROM POINT 2 YEILDS ");
  PrintPoints(Result);
  WriteLn;

  MultiplyPoints(TestP1,TestP2,Result);
  WriteString("THE PRODUCT OF THE POINTS IS ");
  PrintPoints(Result);
  WriteLn;

  DividePoints(TestP1,TestP2,Result);
  WriteString("THE DIVISION OF THE FIRST POINT BY THE SECOND YEILDS ");
  PrintPoints(Result);
  WriteLn;

  ReflectOrigin(TestP1);
  WriteString("THE REFLECTION OF POINT 1 ACCROSS THE ORIGIN IS ");
  PrintPoints(TestP1);
  WriteLn;
  ReflectOrigin(TestP2);
  WriteString("THE REFLECTION OF POINT 2 ACCROSS THE ORIGIN IS ");
  PrintPoints(TestP2);
  WriteLn;

  END; (* FOR *)
END TestPoints.
