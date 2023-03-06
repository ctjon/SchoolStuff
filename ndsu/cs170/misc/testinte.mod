MODULE TestIntegrate;
(* Test numerical integration by trapezoidal rule procedure
               J. M. Adams   January 1988
               implemented on CMS in Waterloo Modula-2 by
               D. Bruce Erickson October 30 1989              *)
FROM InOut IMPORT WriteString, WriteLn;
FROM RealInOut IMPORT WriteReal;
FROM MathLib0 IMPORT exp, sin, pi;

TYPE Function = PROCEDURE(REAL):REAL;

PROCEDURE XSquared(X: REAL):REAL;
(* Test function for Integrate *)
BEGIN
  RETURN X * X;
END XSquared;

PROCEDURE Fx(X : REAL):REAL;
(* Test fuction for Integrate *)
CONST  TwoPi = 2.0 * pi;
BEGIN
  RETURN exp(-X) + sin(TwoPi * X);
END Fx;

PROCEDURE Integrate(f:Function; a,b: REAL; n: CARDINAL) :REAL;
(* Compute an approximation to the area under the graph of the
   function f, from x = a to x = b using the trapezoidal rule with
   n subdivisions *)
VAR Sum, h : REAL;
    I: CARDINAL;
BEGIN
  h := (b-a) / FLOAT(n);
  Sum := f(a);
  FOR I := 1 TO n-1 DO
    Sum := Sum + 2.0 * f(a+FLOAT(I) * h);
  END;   (* FOR *)
  Sum := Sum + f(b);
  RETURN (h/2.0) * Sum;
END Integrate;

BEGIN (* TestIntegrate *)
  WriteString("The area under x squared from x = 1 to x = 3");
  WriteString(" is approximately ");
  WriteLn;
  WriteReal(Integrate(XSquared, 1.0, 3.0, 10), 15);
  WriteLn;WriteLn;
  WriteString("The area under exp(-x) + sin(2 pi x) from x = 0 to ");
  WriteString("x = 64 is approximately ");
  WriteLn;
  WriteReal(Integrate(Fx, 0.0, 64.0, 150), 15); WriteLn;
END TestIntegrate.
