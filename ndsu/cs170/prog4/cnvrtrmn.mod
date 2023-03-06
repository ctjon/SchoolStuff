MODULE CNVRTRMN;

(* CHRISTOPHER C. TJON *)
(* 110975-8            *)
(* CS 170              *)
(* PROGRAM 4           *)
(* 11 OCT 1989         *)
(* DR. ERICKSON        *)

(* PROBLEM: TO CONVERT CALENDER YEARS GIVEN IN THE FORM
            OF ROMAN NUMERALS TO ARABIC NUMBERS. IT IS
            IMPORTANT TO NOTE THAT ONLY FORMAL ROMAN SCRIPT
            IS ALLOWED. *)

(* ROMAN NUMERAL TABLE IS AS FOLLOWS :

  I = 1
  V = 5
  X = 10
  L = 50
  C = 100
  D = 500
  M = 1000                       *)

(* IMPORTS *)

FROM InOut IMPORT WriteString,WriteLn,ReadString,WriteCard,Read,Write,
     EOL,ReadCard,Done,OpenInput,CloseInput;
FROM Strings IMPORT String, Length;

CONST MAXSIZE = 12;

  (* MAXSIZE IS THE LARGEST PRINT FIELD FOR THE OUTPUT OF THE
     ROMAN NUMERALS TO THE SCREEN.  IF YOU NEED MORE ROOM, CHANGE
     THE VALUE OF THE CONSTANT MAXSIZE ACCORDING TO YOUR NEEDS.
     THE MAXIMUM LENGTH OF THE ROMAN NUMERAL INPUT IS 80 CHARACTERS *)

(* VARIABLE DECLARATIONS *)

VAR ROMAN : ARRAY[1..80] OF CHAR;
    Ch:CHAR;
    X:INTEGER;
    LEN,Z,SUM,A,NUMBER:CARDINAL;

PROCEDURE Precedence (Ch:CHAR):CARDINAL;

 (* PROCEDURE TO DETERMINE THE PRECEDENCE OF THE CHARACTER BEING
    EXAMINED RELATIVE TO THE ONE BEFORE IT. IE. 10 WILL HAVE A
    GREATER PRECEDENCE THAN 5.       *)

BEGIN
    CASE Ch OF
'i','I' : RETURN(1);|
'v','V' : RETURN(2);|
'x','X' : RETURN(3);|
'l','L' : RETURN(4);|
'c','C' : RETURN(5);|
'd','D' : RETURN(6);|
'm','M' : RETURN(7);|
    ELSE RETURN(0);
    END; (* CASE *)
END Precedence;

(* MAIN MODULE BEGINS HERE *)

BEGIN

OpenInput ("");

WriteLn;
WriteLn;
WriteString("********************************************************");
WriteLn;
WriteString("*  PROGRAM TO CONVERT ROMAN NUMBERS TO ARABIC NUMBERS  *");
WriteLn;
WriteString("*    WRITTEN BY CHRISTOPHER C. TJON  8 OCTOBER 1989    *");
WriteLn;
WriteString("********************************************************");
WriteLn;
WriteLn;
WriteLn;

  (* GET THE INPUT STRING OF ROMAN NUMERALS *)
  Ch := ' ';  (* INITIALIZE CH TO A BLANK *)

  Read(Ch);
  WHILE Done DO

  FOR X := 1 TO 80 DO
      ROMAN[X] := ' ';
  END; (*FOR*)

  X := 0;     (* REINITIALIZE X TO ZERO     *)

  (* LOAD THE STRING INTO THE ARRAY ONE CHARACTER AT A TIME
     BY READING THE ENTERED STRING ONE CHARACTER AT A TIME  *)

  REPEAT
    INC(X);
    ROMAN[X] := Ch;
    Read(Ch);
  UNTIL (Ch = EOL);
  (* REPEATS UNTIL THE STRING ENDS *** WARNING DO NOT ENTER
                                       MORE THAN 80 CHARACTERS***)

  (* DO THE CONVERSION BY GOING TO THE RIGHT END OF THE STRING
     AND WORKING BACKWARDS. IF THE CHARACTER DIRECTLY IN FRONT
     OF THE ONE BEING CHECKED IS SMALLER (IE. V < X) THEN SUBTRACT
     AND IF IT IS GREATER THAN OR EQUAL TO THEN ADD THEM *)

  (* INITIALIZE VARIABLES *)

  LEN := X;
  SUM := 0;

  (* CALCULATE THE SUM BY COMPARING THE PRECEDENCE OF THE CHARACTER
     AND ITS NEIGHBOR TO THE LEFT.  IF THE PRECEDENCE IS LESS THAN
     THEN SUBTRACT ITS VALUE FROM THE SUM. IF NOT THEN ADD ITS VALUE
     TO THE SUM. THIS PROCESS IS CONTINUED UNTIL THE WHOLE NUMBER
     IS CALCULATED   *)

  FOR Z := LEN TO 1 BY -1 DO

  CASE ROMAN[Z] OF

'i','I' : IF Precedence(ROMAN[Z]) < Precedence(ROMAN[Z+1]) THEN
          SUM := SUM -1;
          ELSE
          SUM := SUM + 1;
          END; (* IF *)|

'v','V' : IF Precedence(ROMAN[Z]) < Precedence(ROMAN[Z+1]) THEN
          SUM := SUM - 5;
          ELSE
          SUM := SUM + 5;
          END; (* IF *)|

'x','X' : IF Precedence(ROMAN[Z]) < Precedence(ROMAN[Z+1]) THEN
          SUM := SUM - 10;
          ELSE
          SUM := SUM + 10;
          END; (* IF *)|

'l','L' : IF Precedence(ROMAN[Z]) < Precedence(ROMAN[Z+1]) THEN
          SUM := SUM - 50;
          ELSE
          SUM := SUM + 50;
          END; (* IF *)|

'c','C' : IF Precedence(ROMAN[Z]) < Precedence(ROMAN[Z+1]) THEN
          SUM := SUM - 100;
          ELSE
          SUM := SUM + 100;
          END; (* IF *)|

'd','D' : IF Precedence(ROMAN[Z]) < Precedence(ROMAN[Z+1]) THEN
          SUM := SUM - 500;
          ELSE
          SUM := SUM + 500;
          END; (* IF *)|

'm','M' : IF Precedence(ROMAN[Z]) < Precedence(ROMAN[Z+1]) THEN
          SUM := SUM - 1000;
          ELSE
          SUM := SUM + 1000;
          END; (* IF *)|

     END;(*CASE*)
  END; (* FOR Z *)
  FOR Z := 1 TO MAXSIZE BY 1 DO
     Write (ROMAN[Z]) ;
  END; (*FOR*)
  WriteString ( "  =  " ) ;

  WriteCard(SUM,4);
  WriteLn;
  Read(Ch);
END; (* WHILE *)

CloseInput;
  WriteLn;
  WriteLn;
  WriteString("CONVERSION MODULE NOW TERMINIATED. THANK YOU.");
  WriteLn;
END CNVRTRMN.
