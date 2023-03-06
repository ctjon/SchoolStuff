IMPLEMENTATION MODULE EXFAMILY;

(***********************************************************************)
(*  WRITTEN BY CHRISTOPHER C. TJON                                     *)
(*  FOR DR. ERICKSONS CS171                                            *)
(*  8 DEC 1989                                                         *)
(***********************************************************************)

FROM InOut IMPORT WriteLn, WriteString, ReadString, ReadCard, WriteCard,
                  FlushLn;
FROM Strings IMPORT String, CompareStr;
FROM Storage IMPORT ALLOCATE,Available;

CONST MAXFAMILY = 10;   (* THE MAXIMUM NUMBER OF FAMILIES ALLOWED      *)
      MAXCHILD  = 10;   (* THE MAXIMUM NUMBER OF CHILDREN PER FAMILY   *)

TYPE FAMILY = POINTER TO FAMILYDATA;

TYPE FAMILYUNITS = RECORD
                   LASTNAME   : NAME;
                   FATHER     : NAME;
                   MOTHER     : NAME;
                   NUMBERCH   : CARDINAL;
                   CHILDREN   : ARRAY [1..MAXCHILD] OF NAME;
                   END;

FAMILYDATA = ARRAY [1..MAXFAMILY] OF FAMILYUNITS;

TYPE STORAGE = ARRAY[1..MAXFAMILY] OF BOOLEAN;

VAR AVAILABLE : STORAGE;
          X,Y : CARDINAL;
            F : FAMILY;

(***********************************************************************)
(*****< INITIALIZE >****************************************************)
(***********************************************************************)

PROCEDURE INITIALIZE(VAR F : FAMILY);
BEGIN
   IF (Available(SIZE(F@))) THEN ALLOCATE(F,SIZE(F@));
   ELSE WriteString("NOT ENOUGH MACHINE MEMORY! EXIT!");
   WriteLn;
   END; (* IF *)
END INITIALIZE;




(***********************************************************************)
(*****< PROCEDURE ADD FAMILY >******************************************)
(***********************************************************************)

PROCEDURE ADDFAMILY(VAR F : FAMILY) : CARDINAL;
(* REQUIRES : STORAGE IS AVAILABLE FOR FAMILY AND FAMILY IS NOT        *)
(*            ALREADY IN BLOCK OF FAMILIES                             *)
(* MODIFIES : BLOCK OF FAMILIES                                        *)
(* EFFECTS  : ADDS A FAMILY TO THE BLOCK OF FAMILIES                   *)

VAR X,Y, NUMCHILD : CARDINAL;

BEGIN

   X := 1;
   WHILE ((NOT AVAILABLE[X]) AND (X <= MAXFAMILY)) DO
      INC(X);
   END; (* WHILE *)
   IF X > MAXFAMILY THEN
      WriteString("NO STORAGE AVAILABLE FOR FAMILY");
      WriteLn;
   ELSE
      AVAILABLE[X] := FALSE;
      WriteString("WHAT IS THE LAST NAME OF THE FAMILY?");
      WriteLn;
      ReadString(F@[X].LASTNAME);
      FlushLn;
      WriteString("WHAT IS THE FATHER'S NAME?");
      WriteLn;
      ReadString(F@[X].FATHER);
      FlushLn;
      WriteString("WHAT IS THE MOTHER'S NAME?");
      WriteLn;
      ReadString(F@[X].MOTHER);
      FlushLn;
      WriteString("HOW MANY CHILDREN DOES THE FAMILY HAVE?");
      WriteLn;
      ReadCard(NUMCHILD);
      FlushLn;
      F@[X].NUMBERCH := NUMCHILD;
      FOR Y := 1 TO NUMCHILD DO
         WriteString("PLEASE ENTER THE NAME OF CHILD NUMBER ");
         WriteCard(Y,2);
         WriteLn;
         ReadString(F@[X].CHILDREN[Y]);
         FlushLn;
      END; (* FOR Y *)
   END; (* IF *)
RETURN(NUMCHILD);
END ADDFAMILY;



(***********************************************************************)
(*****< PROCEDURE ARE THERE FAMILIES >**********************************)
(***********************************************************************)

PROCEDURE ARETHEREFAMILIES(F : FAMILY) : BOOLEAN;

(* REQUIRES : NOTHING                                                  *)
(* MODIFIES : NOTHING                                                  *)
(* EFFECTS  : RETURNS FALSE IF HAVE BEEN ENTERED. OTHERWISE TRUE       *)

VAR X : CARDINAL;

BEGIN

   FOR X := 1 TO MAXFAMILY DO
      IF NOT AVAILABLE[X] THEN
         RETURN(TRUE);
      END; (* IF *)
   END; (* FOR *)
   RETURN(FALSE);
END ARETHEREFAMILIES;



(***********************************************************************)
(*****< PROCEDURE ROOM FOR MORE FAMILIES >******************************)
(***********************************************************************)

PROCEDURE ROOMFORMOREFAMILIES(F : FAMILY) : BOOLEAN;

(* REQUIRES : NOTHING                                                  *)
(* MODIFIES : NOTHING                                                  *)
(* EFFECTS  : RETURNS TRUE IF THERE IS STORAGE AVAILABLE FOR FAMILY.   *)
(*            OTHERWISE FALSE                                          *)

VAR X     : CARDINAL;
    FOUND : BOOLEAN;

BEGIN
   FOUND := FALSE;
   FOR X := 1 TO MAXFAMILY DO
      IF AVAILABLE[X] THEN
         FOUND := TRUE;
      END;
   END; (* FOR *)
   RETURN(FOUND);
END ROOMFORMOREFAMILIES;



(***********************************************************************)
(*****< PROCEDURE REMOVE FAMILY >***************************************)
(***********************************************************************)

PROCEDURE REMOVEFAMILY(VAR F : FAMILY; LASTNAME:NAME);
(* REQUIRES : FAMILY TO BE REMOVED IS IN BLOCK OF FAMILIES             *)
(* MODIFIES : BLOCK OF FAMILIES                                        *)
(* EFFECTS  : REMOVES FAMILY FROM THE LIST                             *)

VAR X,Y : CARDINAL;

BEGIN

FOR X := 1 TO MAXFAMILY DO
   IF (AVAILABLE[X] = FALSE) THEN
   IF CompareStr(LASTNAME,F@[X].LASTNAME) = 0 THEN
      AVAILABLE[X] := TRUE;
      F@[X].LASTNAME := "  ";
      F@[X].FATHER := "  ";
      F@[X].MOTHER := "  ";
      FOR Y := 1 TO MAXCHILD DO
         F@[X].CHILDREN[Y] := "  ";
      END; (* FOR Y *)
   END; (* IF *)
   END; (* IF *)
END; (* FOR X *)
END REMOVEFAMILY;



(***********************************************************************)
(*****< PROCEDURE FATHER OF >*******************************************)
(***********************************************************************)

PROCEDURE FATHEROF(F : FAMILY; LASTNAME : NAME) : NAME;
(* REQUIRES : INPUT OF A VALID FAMILY NAME                             *)
(* MODIFIES : NOTHING                                                  *)
(* EFFECTS  : RETURNS THE FATHER OF THE FAMILY                         *)

VAR X : CARDINAL;

BEGIN
   X := 1;
   WHILE (CompareStr(F@[X].LASTNAME,LASTNAME) # 0) AND (X<=MAXFAMILY) DO
      INC(X);
   END; (* WHILE *)
   IF X > MAXFAMILY THEN
      WriteString("THE SPECIFIED FAMILY DOES NOT EXIST!");
      RETURN("  ");
   ELSE
      RETURN(F@[X].FATHER);
   END; (* IF *)
END FATHEROF;


(***********************************************************************)
(*****< PROCEDURE MOTHER OF >*******************************************)
(***********************************************************************)

PROCEDURE MOTHEROF(F : FAMILY; LASTNAME : NAME) : NAME;
(* REQUIRES : INPUT OF A VALID FAMILY NAME                             *)
(* MODIFIES : NOTHING                                                  *)
(* EFFECTS  : RETURNS THE MOTHER OF THE FAMILY                         *)

VAR X : CARDINAL;

BEGIN
   X := 1;
   WHILE (CompareStr(F@[X].LASTNAME,LASTNAME) # 0) AND (X<=MAXFAMILY) DO
      INC(X);
   END; (* WHILE *)
   IF X > MAXFAMILY THEN
      WriteString("THE SPECIFIED FAMILY DOES NOT EXIST!");
      RETURN("  ");
   ELSE
      RETURN(F@[X].MOTHER);
   END; (* IF *)
END MOTHEROF;


(***********************************************************************)
(*****< PROCEDURE CHILD OF >********************************************)
(***********************************************************************)

PROCEDURE CHILDOF(F : FAMILY; LASTNAME : NAME) ;
(* REQUIRES : INPUT OF A VALID FAMILY NAME                             *)
(* MODIFIES : NOTHING                                                  *)
(* EFFECTS  : WRITES OUT THE CHILDREN OF THE FAMILY                    *)

VAR X,Y : CARDINAL;

BEGIN
   X := 1;
   WHILE (CompareStr(F@[X].LASTNAME,LASTNAME) # 0) AND (X<=MAXFAMILY) DO
      INC(X);
   END; (* WHILE *)
   IF X > MAXFAMILY THEN
      WriteString("THE SPECIFIED FAMILY DOES NOT EXIST!");
   ELSE
      WriteString ( "CHILDREN OF THE " ) ;
      WriteString ( F@[X].LASTNAME ) ;
      WriteString ( " FAMILY:  " ) ; WriteLn ; WriteLn ;
      FOR Y := 1 TO F@[X].NUMBERCH DO
         WriteString(F@[X].CHILDREN[Y]);WriteLn ;
      END; (* IF Y *)
   END; (* IF X *)
END CHILDOF;


(***********************************************************************)
(*****< PROCEDURE IS IN FAMILY >****************************************)
(***********************************************************************)

PROCEDURE ISINFAMILY(F:FAMILY; VAR LASTNAME, FIRSTNAME : NAME) : BOOLEAN;
(* REQUIRES : THE NAME ENTERED IS VALID                                *)
(* MODIFIES : NOTHING                                                  *)
(* EFFECTS  : RETURNS TRUE IF THE PERSON IS IN THE FAMILY.  OTHERWISE  *)
(*            FALSE                                                    *)

VAR X,Y   : CARDINAL;
    FOUND : BOOLEAN;

BEGIN
   FOUND := FALSE;
   FOR X := 1 TO MAXFAMILY DO
   IF ( NOT ( AVAILABLE[X] ) ) THEN
     IF (CompareStr(F@[X].LASTNAME,LASTNAME) = 0) THEN
      IF CompareStr(FIRSTNAME,F@[X].FATHER) = 0 THEN
         FOUND := TRUE;
      ELSIF CompareStr(FIRSTNAME,F@[X].MOTHER) = 0 THEN
         FOUND := TRUE;
      END; (* IF *)
      FOR Y := 1 TO F@[X].NUMBERCH DO
         IF CompareStr(FIRSTNAME,F@[X].CHILDREN[Y]) = 0 THEN
         FOUND := TRUE;
         END; (* IF *)
      END; (* FOR Y *)
   END; (* IF COMPARE *)
   END; (*IF*)
   END; (* FOR X *)
   RETURN(FOUND);
END ISINFAMILY;


(***********************************************************************)
(*****< PROCEDURE DOES FAMILY HAVE CHILDREN >***************************)
(***********************************************************************)

PROCEDURE DOESFAMILYHAVECHILDREN(F : FAMILY;LASTNAME:NAME) : BOOLEAN;

(* REQUIRES : FAMILY SPECEFIED IS IN BLOCK OF FAMILIES                 *)
(* MODIFIES : NOTHING                                                  *)
(* EFFECTS  : RETURNS TRUE IF THERE ARE CHILDREN IN GIVEN FAMILY       *)

VAR ISTHERECHILD : BOOLEAN;
    X            : CARDINAL;

BEGIN
ISTHERECHILD := FALSE;
FOR X := 1 TO MAXFAMILY DO
   IF (CompareStr(F@[X].LASTNAME,LASTNAME)=0) THEN
      IF (CompareStr(F@[X].CHILDREN[1],"     ") = 0) THEN
         ISTHERECHILD := TRUE;
      END; (* IF *)
   END; (* IF *)
END; (* FOR X*)
RETURN(ISTHERECHILD);
END DOESFAMILYHAVECHILDREN;


(***********************************************************************)
(*****< PROCEDURE IS CHILD IN FAMILY >**********************************)
(***********************************************************************)

PROCEDURE ISCHILDINFAMILY(F:FAMILY;LASTNAME,FIRSTNAME : NAME) : BOOLEAN;
(* REQUIRES :                                                          *)
(* MODIFIES :                                                          *)
(* EFFECTS  :                                                          *)

VAR X,Y : CARDINAL;

BEGIN
   X := 1;
   WHILE (CompareStr(F@[X].LASTNAME,LASTNAME) # 0) AND (X<=MAXFAMILY) DO
      INC(X);
   END; (* WHILE *)
   IF X > MAXFAMILY THEN
      WriteString("THE SPECIFIED FAMILY DOES NOT EXIST!");
      RETURN(FALSE);
   ELSE
      FOR Y := 1 TO MAXCHILD DO
         IF (CompareStr(FIRSTNAME,F@[X].CHILDREN[Y]) = 0) THEN
            RETURN(TRUE);
         END; (* IF *)
      END; (* IF Y *)
   END; (* IF X *)
END ISCHILDINFAMILY;


(***********************************************************************)
(*****< PROCEDURE LIST FAMILIES >***************************************)
(***********************************************************************)

PROCEDURE LISTFAMILIES(F : FAMILY ; NUMCHILD : CARDINAL);
(* REQUIRES : THAT THERE ARE FAMILIES IN DATA BLOCK TO LIST            *)
(* MODIFIES : NOTHING                                                  *)
(* EFFECTS  : PRINTS FAMILIES STORED ON TO THE SCREEN                  *)

VAR X,Y : CARDINAL;

BEGIN

X := 1;
FOR X := 1 TO MAXFAMILY DO
IF (NOT (AVAILABLE[X])) THEN
   WriteLn ;
   WriteString ( "MEMBERS OF THE " ) ;
   WriteString ( F@[X].LASTNAME ) ;
   WriteString ( " FAMILY:  " ) ; WriteLn ;
   WriteLn;
   WriteString("THE FATHER IS : ");
   WriteString(F@[X].FATHER);
   WriteLn;
   WriteLn;
   WriteString("THE MOTHER IS : ");
   WriteString(F@[X].MOTHER);
   WriteLn;
   IF (F@[X].NUMBERCH = 0) THEN
      WriteString("THERE ARE NO CHILDREN");
      WriteLn;
   ELSE


      WriteLn;
      WriteString("THE CHILDREN ARE : ");
      WriteLn;
   END; (* IF *)
   WriteLn;
   FOR Y := 1 TO F@[X].NUMBERCH DO
      IF (CompareStr(F@[X].CHILDREN[Y],"     ") # 0) THEN
         WriteString(F@[X].CHILDREN[Y]);
         WriteLn;
      END;
   END; (* FOR Y *)
END; (* IF *)
END; (* FOR *)

END LISTFAMILIES;

BEGIN
  IF (Available(SIZE(FAMILYDATA))) THEN
     ALLOCATE(F,SIZE(F@));
  ELSE WriteString (" NOT ENOUGH MEMORY AVAILABLE ");
       WriteLn;
  END; (* IF *)
  FOR X := 1 TO MAXFAMILY DO
    AVAILABLE[X] := TRUE;
    F@[X].FATHER := "    ";
    F@[X].MOTHER := "    ";
    F@[X].NUMBERCH := 0;
    FOR Y := 1 TO MAXCHILD DO
       F@[X].CHILDREN[Y] := "     ";
    END; (* FOR Y *)

  END; (* FOR X *)
END EXFAMILY.
