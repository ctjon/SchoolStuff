MODULE TESTFAMILY;

(***********************************************************************)
(*  PROGRAM TO TEST EXFAMILY MODULE                                    *)
(*  WRITTEN BY CHRISTOPHER C. TJON                                     *)
(*  FOR DR. ERICKSONS CS171                                            *)
(*  8 DEC 1989                                                         *)
(***********************************************************************)

FROM InOut IMPORT WriteString, ReadString, WriteLn, Read, FlushLn;

FROM Strings IMPORT String;

FROM EXFAMILY IMPORT ARETHEREFAMILIES, ADDFAMILY, ROOMFORMOREFAMILIES,
                     REMOVEFAMILY, FATHEROF, MOTHEROF, CHILDOF,
                     ISINFAMILY, LISTFAMILIES, FAMILY,INITIALIZE,
                     ISCHILDINFAMILY;


VAR CHOICE : CHAR;
    TARGET : String;
    FNAME  : String;
    FATHER : String;
    MOTHER : String;
    CHILD  : String;
    ISCHILD: BOOLEAN;
    F      : FAMILY;
    JUNK   : CHAR; (* READS THE RETURN CHARACTER AFTER OTION SELECTION *)
    Z, NUMCHILD : CARDINAL;

BEGIN

INITIALIZE(F);



REPEAT
   WriteLn;
   WriteLn;
   WriteLn;
   WriteLn;
   WriteString("***< FAMILY OPTION MENU >***");
   WriteLn;
   WriteLn;
   WriteLn;

   WriteString("1.  ADD A FAMILY TO THE DATA BLOCK");
   WriteLn;
   WriteLn;

   WriteString("2.  DELETE A FAMILY FROM THE DATA BLOCK");
   WriteLn;
   WriteLn;
   WriteString("3.  DETERMINE THE FATHER OF A FAMILY");
   WriteLn;
   WriteLn;

   WriteString("4.  DETERMINE THE MOTHER OF A FAMILY");
   WriteLn;
   WriteLn;

   WriteString("5.  DETERMINE THE CHILDREN OF A FAMILY");
   WriteLn;
   WriteLn;

   WriteString("6.  DETERMINE IF A PERSON IS IN A FAMILY");
   WriteLn;
   WriteLn;

   WriteString("7.  LIST ALL FAMILIES TO THE SCREEN");
   WriteLn;
   WriteLn;

   WriteString("8.  EXIT");
   WriteLn;
   WriteLn;


   Read(CHOICE);
   Read(JUNK);
   FlushLn;

   CASE CHOICE OF

   '1' : IF (ROOMFORMOREFAMILIES(F)) THEN
           NUMCHILD := ADDFAMILY(F);
         ELSE
           WriteString("INSUFFICIENT SPACE TO ADD FAMILY ");
           WriteLn;
         END; (* IF *)

 | '2' : WriteString("ENTER VALID FAMILY TO BE DELETED");
         WriteLn;
         ReadString(TARGET);
         FlushLn ;
         IF (ARETHEREFAMILIES(F)) THEN
            REMOVEFAMILY(F,TARGET);
         ELSE
            WriteString("THERE ARE NO FAMILIES TO DELETE");
            WriteLn;
         END; (* IF *)

 | '3' : WriteString("PLEASE ENTER THE FAMILY NAME");
         WriteLn;
         ReadString(TARGET);
         FlushLn ;

         IF (ARETHEREFAMILIES(F)) THEN
            FATHER := FATHEROF(F,TARGET);
            WriteString("FATHER OF THE FAMILY : "); WriteString(FATHER);
            WriteLn;
         ELSE
            WriteString("THERE ARE NO FAMILIES TO SEARCH");
            WriteLn;
         END; (* IF *)

 | '4' : WriteString("PLEASE ENTER THE FAMILY NAME");
         WriteLn;
         ReadString(TARGET);
         FlushLn ;

         IF (ARETHEREFAMILIES(F)) THEN
            MOTHER := MOTHEROF(F,TARGET);
            WriteString("MOTHER OF THE FAMILY : "); WriteString(MOTHER);
            WriteLn;
         ELSE
            WriteString("THERE ARE NO FAMILIES TO SEARCH");
            WriteLn;
         END; (* IF *)


 | '5' : WriteString("PLEASE ENTER THE FAMILY NAME");
         WriteLn;
         ReadString(TARGET);
         FlushLn ;

         IF (ARETHEREFAMILIES(F)) THEN
            CHILDOF(F,TARGET);
         ELSE
            WriteString("THERE ARE NO FAMILIES TO SEARCH");
            WriteLn;
         END; (* IF *)

 | '6' : WriteString("PLEASE ENTER THE FAMILY NAME");
         WriteLn;
         ReadString(TARGET);
         FlushLn ;

         WriteString("PLEASE ENTER THE FIRST NAME");
         WriteLn;
         ReadString(FNAME);
         FlushLn ;
         IF (ARETHEREFAMILIES(F)) THEN
            IF (ISINFAMILY(F,TARGET,FNAME)) THEN
            WriteString("YES"); WriteLn;
            END; (* IF *)
         ELSE
            WriteString("THERE ARE NO FAMILIES TO SEARCH");
            WriteLn;
         END; (* IF *)

 | '7' : LISTFAMILIES(F , NUMCHILD);

 | '8' : (* DO NOTHING DUMMY CHOICE *);

   ELSE
      WriteString("--- INVALID CHOICE ---");
      WriteLn;
   END; (* CASE *)

UNTIL (CHOICE = '8');



END TESTFAMILY.
