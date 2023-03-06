MODULE NIM;
(*****************************************************************************)
(*                                                                           *)
(*      MODULE NIM                                                           *)
(*      WRITTEN BY CHRISTOPHER C. TJON                                       *)
(*      110975-8                                                             *)
(*      FOR DR. ERICKSON'S CS171                                             *)
(*      10 FEBRUARY 1990                                                     *)
(*                                                                           *)
(*      THIS MODULE IS THE GAME OF NIM.  IT IS DESIGNED FOR TWO PILES OF     *)
(*      M AND N CHIPS WHERE NEITHER M OR N IS LESS THAN 1.                   *)
(*                                                                           *)
(*****************************************************************************)


FROM InOut IMPORT    Write, WriteLn, WriteString, WriteCard, Read,
                     ReadCard, FlushLn,EOL, Peek, Done;

FROM Storage IMPORT  Available, ALLOCATE;

FROM Strings IMPORT  String, Assign;

FROM Terminal IMPORT ClearScreen;



TYPE TREE = POINTER TO NODE;
     NODE = RECORD
                STATUS : CARDINAL;
                M      : CARDINAL;
                N      : CARDINAL;
                LCHILD : TREE;
                RCHILD : TREE;
            END; (* RECORD *)



PROCEDURE SKIPWHITESPACES();
(*****************************************************************************)
(* REQUIRES : NOTHING                                                        *)
(* MODIFIES : NOTHING                                                        *)
(* EFFECTS  : SKIPS WHITE SPACE IN A FIELD OF INPUT                          *)
(*****************************************************************************)

VAR CH : CHAR;

BEGIN
    CH := ' ';
    Peek(CH);
    WHILE (((CH = ' ') OR (CH = EOL)) AND Done) DO
        Read(CH);
        Peek(CH);
    END; (* WHILE CH *)
END SKIPWHITESPACES;



PROCEDURE RANDOMNUMBER(VAR RANDOM : REAL) : CARDINAL;
(*****************************************************************************)
(* REQUIRES : INITIALIZATION OF THE GLOBAL VARIABLE RANDOM                   *)
(* MODIFIES : RANDOM                                                         *)
(* EFFECTS  : CREATES A SEMI-PSUEDO RANDOM NUMBER                            *)
(*****************************************************************************)

VAR RN : CARDINAL;

BEGIN
    RANDOM := (RANDOM * RANDOM);
    RANDOM := RANDOM - FLOAT(TRUNC(RANDOM));
    RANDOM := (8.0  * RANDOM) + 1.0;
    RN := TRUNC(RANDOM);
    RETURN(RN);
END RANDOMNUMBER;



PROCEDURE DISPLAY(M,N : CARDINAL);
(*****************************************************************************)
(* REQUIRES : M AND N HAVE BEEN INITIALIZED                                  *)
(* MODIFIES : NOTHING                                                        *)
(* EFFECTS  : DISPLAYS THE NUMBER OF CHIPS ON EACH STACK.  IF THESE NUMBERS  *)
(*            ARE LESS THAN 15 THEN A VIDEO DISPLAY OF THE STACKS IS SHOWN   *)
(*****************************************************************************)

VAR I, LOW, HIGH : CARDINAL;

BEGIN
    ClearScreen;
    IF ((M > 15) OR (N > 15)) THEN
        WriteLn;
        WriteLn;
        WriteLn;
        WriteLn;
        WriteString("CURRENT VALUE OF 'M' IS : ");
        WriteCard(M,5);
        WriteLn;
        WriteString("CURRENT VALUE OF 'N' IS : ");
        WriteCard(N,5);
        WriteLn;
        WriteLn;
        RETURN;
    END; (* IF M > 15 *)
    WriteLn;
    WriteString("           'M'                  'N'");
    WriteLn;
    WriteString("  ----------------------------------------------");
    WriteLn;
    IF (M > N) THEN
        HIGH := M;
        LOW := N;
    ELSE
        HIGH := N;
        LOW := M;
    END; (* IF M > N *)
    FOR I := 1 TO (15 - HIGH) DO
        WriteLn;
    END; (* FOR I *)
    FOR I :=  HIGH TO 1 BY -1 DO
        IF ((M > N) AND (N < I)) THEN
            WriteString("       ============");
        ELSIF ((M < N) AND (M < I)) THEN
            WriteString("                            ============");
        ELSE
            WriteString("       ============         ============");
        END; (* IF M > N *)
    WriteLn;
    END; (* FOR I *)
    WriteString("  <><><><><><><><><><><><><><><><><><><><><><><>");
    WriteLn;
    WriteLn;
END DISPLAY;




PROCEDURE BUILDTREE(M, N : CARDINAL; VAR T : TREE);
(*****************************************************************************)
(* REQUIRES : MEMORY IS AVAILABLE                                            *)
(* MODIFIES : NOTHING                                                        *)
(* EFFECTS  : CREATES T                                                      *)
(*****************************************************************************)

BEGIN
    IF (Available(SIZE(T@))) THEN
        ALLOCATE(T,SIZE(T@));
        T@.M := M;
        T@.N := N;
        T@.LCHILD := NIL;
        T@.RCHILD := NIL;
    ELSE
        WriteString("ERROR! NOT ENOUGH MEMORY AVAILABLE! RUN ABORTED!");
        WriteLn;
        HALT;
    END; (* IF AVAILABLE *)

    IF (M # 0) THEN
        BUILDTREE(M - 1, N, T@.LCHILD);
    END; (* IF M # 0 *)

    IF (N # 0) THEN
        BUILDTREE(M, N-1, T@.RCHILD);
    END; (* IF N # 0 *)
END BUILDTREE;




PROCEDURE PLAYERSTURN(VAR M, N : CARDINAL;
                              T : TREE     ) : TREE;
(****************************************************************)
(* REQUIRES : M, N, T HAVE BEEN INITALIZED                      *)
(* MODIFIES : NOTHING                                           *)
(* EFFECTS  : RETURNS POINTER TO THE NODE CORRESPONDING TO THE  *)
(*            PLAYERS CHOICE                                    *)
(****************************************************************)
BEGIN
    IF (T # NIL) THEN
        IF (M < T@.M) THEN
            RETURN(PLAYERSTURN(M,N,T@.LCHILD));
        ELSIF (N < T@.N) THEN
            RETURN(PLAYERSTURN(M,N,T@.RCHILD));
        ELSIF ((T@.M = M)  AND  (T@.N = N)) THEN
            RETURN(T);
        END; (* IF M < T@.M *)
    END; (* IF T = NIL *)
END PLAYERSTURN;




PROCEDURE NUMCHILDREN(T : TREE) : CARDINAL;
(*****************************************************************************)
(* REQUIRES : T HAS BEEN INITIALIZED                                         *)
(* MODIFIES : NOTHING                                                        *)
(* EFFECTS  : RETURNS THE NUMBER OF CHILDREN OF A SPECIFIC NODE              *)
(*****************************************************************************)
BEGIN
    IF (T = NIL) THEN
        RETURN(0);
    ELSE
        RETURN(1 + NUMCHILDREN(T@.LCHILD) + NUMCHILDREN(T@.RCHILD));
    END;
END NUMCHILDREN;



PROCEDURE ASSIGNMINMAX (T : TREE);
(*****************************************************************************)
(* REQUIRES : T HAS BEEN INITIALIZED                                         *)
(* MODIFIES : THE STATUS FIELD OF THE RECORD                                 *)
(* EFFECTS  : ASSIGNS VALUES TO EACH NODE BASED ITS NUMBER OF CHILDREN       *)
(*****************************************************************************)
BEGIN
    IF (T # NIL) THEN
        ASSIGNMINMAX(T@.LCHILD);
        T@.STATUS := NUMCHILDREN(T);
        ASSIGNMINMAX(T@.RCHILD);
    END; (* IF T = NIL *)
END ASSIGNMINMAX;




PROCEDURE ZEROONE (TR : TREE) : TREE;
(*****************************************************************************)
(* REQUIRES: TR HAS BEEN INITIALIZED                                         *)
(* MODIFIES: NOTHING                                                         *)
(* EFFECTS : RETURNS NIL IF NO 0,1 NODE EXISTS                               *)
(*****************************************************************************)

VAR T    : TREE;
    M, N : CARDINAL;

BEGIN
    IF (TR = NIL) THEN
        RETURN(NIL);
    ELSIF (((TR@.M=1) AND (TR@.N=0)) OR ((TR@.M=0) AND (TR@.N=1))) THEN
        M := 0;
        N := 0;
        RETURN(PLAYERSTURN(M,N,TR));
    ELSE
        T := TR;
        WHILE (T # NIL) DO
            IF (((T@.M = 1) AND (T@.N = 0)) OR ((T@.M = 0) AND (T@.N = 1))) THEN
                RETURN(T);
            ELSE
                T := T@.LCHILD;
            END; (* IF T@.M = 1 *)
        END; (* WHILE T # NIL *)
        T := TR;
        WHILE (T # NIL) DO
            IF (((T@.M = 1) AND (T@.N = 0)) OR ((T@.M = 0) AND (T@.N = 1))) THEN
                RETURN(T);
            ELSE
                T := T@.RCHILD;
            END; (* IF T@.M = 1 *)
        END; (* WHILE T # NIL *)
        RETURN(NIL);
    END; (* IF TR = NIL *)
END ZEROONE;




PROCEDURE EVENOUT (TR : TREE) : TREE;
(*****************************************************************************)
(* REQUIRES : TREE HAS BEEN INITIALIZED                                      *)
(* MODIFIES : NOTHING                                                        *)
(* EFFECTS  : RETURNS POINTER TO MOST LOGICAL COMPUTER MOVE                  *)
(*****************************************************************************)

VAR T, HIGHEST : TREE;

BEGIN
    IF (TR = NIL) THEN
        WriteString("ERROR: NIL VALUE ENCOUNTERED IN EVENOUT PROCEDURE");
        WriteLn;
        RETURN(NIL);
    ELSE
        T := TR@.LCHILD;       (* SCAN LEFT SIDE *)
        WHILE (T # NIL) DO
            IF (T@.M = T@.N ) THEN
                RETURN(T);
            ELSE
                T := T@.LCHILD;
            END; (* IF T@.M = T@.N *)
        END; (* WHILE T # NIL *)
        T := TR@.RCHILD;       (* SCAN RIGHT SIDE *)
        WHILE (T # NIL) DO
            IF (T@.M = T@.N ) THEN
                RETURN(T);
            ELSE
                T := T@.RCHILD;
            END; (* IF T@.M = T@.N *)
        END; (* WHILE T # NIL *)
        T := TR@.LCHILD;       (* NO EVEN SO TAKE OPTIMAL *)
        HIGHEST := T;
        WHILE (T # NIL) DO
            IF (T@.STATUS > HIGHEST@.STATUS) THEN
                HIGHEST := T;
            ELSE
                T := T@.LCHILD;
            END; (* IF T@.STATUS *)
        END; (* WHILE T # NIL *)
        T := TR@.RCHILD;
        IF (HIGHEST = NIL) THEN
            HIGHEST := TR@.RCHILD;
        END; (* IF HIGHEST = NIL *)
        WHILE (T # NIL) DO
            IF (T@.STATUS > HIGHEST@.STATUS) THEN
                HIGHEST := T;
            ELSE
                T := T@.RCHILD;
            END; (* IF T@.STATUS *)
        END; (* WHILE T # NIL *)
        RETURN(HIGHEST);
    END;
END EVENOUT;




PROCEDURE COMPTURN(T : TREE) : TREE;
(*****************************************************************************)
(* REQUIRES : T HAS BEEN INITIALIZED                                         *)
(* MODIFIES : NOTHING                                                        *)
(* EFFECTS  : RETURNS A POINTER TO THE NODE CORRESPONDING TO COMPUTER MOVE   *)
(*****************************************************************************)

VAR TEMP : TREE;

BEGIN
    TEMP := ZEROONE(T);
    IF (TEMP = NIL) THEN
        RETURN ( EVENOUT(T) );
    ELSE
        RETURN(TEMP);
    END;
END COMPTURN;




(*****************************************************************************)
(*****< MAIN MODULE >*********************************************************)
(*****************************************************************************)

VAR M, N, NUM, OPTION              : CARDINAL;
    NIMTREE, TURN                  : TREE;
    CH                             : CHAR;
    RANDOM                         : REAL;
    QUIT, ENDOFGAME, VALIDOPTION   : BOOLEAN;



BEGIN (* MAIN MODULE *)

RANDOM := 1.23456789;
QUIT := FALSE;
WHILE (NOT(QUIT)) DO
    NIMTREE := NIL;
    VALIDOPTION := FALSE;
    ENDOFGAME := FALSE;
    WHILE (NOT(VALIDOPTION)) DO
        WriteLn;
        WriteLn;
        WriteLn;
        WriteLn;
        WriteLn;
        WriteLn;
        WriteLn;
        WriteLn;
        WriteString("          NN   N  IIIII  MM   MM ");
        WriteLn;
        WriteString("          N N  N    I    M M M M ");
        WriteLn;
        WriteString("          N  N N    I    M  M  M ");
        WriteLn;
        WriteString("          N   NN  IIIII  M     M ");
        WriteLn;
        WriteLn;
        WriteString("WELCOME TO THE GAME OF NIM");
        WriteLn;
        WriteLn;
        WriteString("FOR PROFESSIONALS ONLY!");
        WriteLn;
        WriteLn;
        WriteLn;
        WriteString("IF YOU DON'T KNOW THE RULES TOO BAD");
        WriteLn;
        WriteLn;
        WriteLn;
        WriteString("WHICH VERSION WOULD YOU LIKE TO PLAY");
        WriteLn;
        WriteLn;
        WriteString("EIGHT CHIPS PER PILE MAXIMUM");
        WriteLn;
        WriteLn;
        WriteString("1) COMPUTER CHOSES M AND N, PLAYER GOES FIRST");
        WriteLn;
        WriteString("2) PLAYER CHOSES M AND N, COMPUTER GOES FIRST");
        WriteLn;
        WriteString("3) COMPUTER CHOSES M AND N AND GOES FIRST");
        WriteLn;
        WriteString("4) PLAYER CHOSES M AND N AND GOES FIRST");
        WriteLn;
        WriteString("5) EXIT");
        WriteLn;
        WriteLn;
        ReadCard(OPTION);
        WriteLn;
        WriteLn;
        IF ((OPTION < 1) OR (OPTION > 5)) THEN
            VALIDOPTION := FALSE;
        ELSE
            VALIDOPTION := TRUE;
        END; (* IF OPTION *)
    END; (* WHILE NOT VALID OPTION *)

    CASE OPTION OF

(*****************************************************************************)
(*****< OPTION 1 >************************************************************)
(*****************************************************************************)

    1:
        WHILE (NOT(ENDOFGAME)) DO
            ClearScreen;
            WriteString("CHOSING MY NUMBERS");
            WriteLn;
            M := RANDOMNUMBER(RANDOM);
            N := RANDOMNUMBER(RANDOM);
            BUILDTREE(M,N,NIMTREE);
            TURN := NIMTREE;
            ASSIGNMINMAX(TURN);
            WHILE ((M # 0) OR (N # 0)) DO
                DISPLAY(M,N);
                WriteString("FROM WHICH STACK WOULD YOU LIKE TO DRAW?");
                WriteLn;
                SKIPWHITESPACES();
                Read(CH);
                DISPLAY(M,N);
                WriteString("HOW MANY CHIPS WOULD YOU LIKE TO REMOVE ");
                WriteString("FROM THE '");
                Write(CAP(CH));
                WriteString("' STACK?");
                WriteLn;
                ReadCard(NUM);
                IF (CAP(CH) = 'M') THEN
                    M := M - NUM;
                ELSE
                    N := N - NUM;
                END; (* IF CAP(CH) = M *)
                Read(CH);
                IF ((M # 0) OR (N # 0)) THEN
                    TURN := PLAYERSTURN(M,N,TURN);
                END; (* IF M # 0 *)
                DISPLAY(M,N);
                IF ((M = 0) AND (N = 0)) THEN
                    ClearScreen;
                    WriteLn;
                    WriteLn;
                    WriteLn;
                    WriteLn;
                    WriteString("SORRY YOU LOSE!!!");
                    WriteLn;
                    WriteString("PRESS RETURN ...");
                    WriteLn;
                    REPEAT
                        Read(CH);
                    UNTIL (CH = EOL);
                    ClearScreen;
                    ENDOFGAME := TRUE;
                END; (* IF M = 0 AND N = 0 *)
                IF (NOT(ENDOFGAME)) THEN
                    WriteString("NOW IT IS MY TURN, PRESS RETURN ...");
                    WriteLn;
                    REPEAT
                        Read(CH);
                    UNTIL (CH = EOL);
                    IF ((M # 0) OR (N # 0)) THEN
                        TURN := COMPTURN(TURN);
                    M := TURN@.M;
                    N := TURN@.N;
                END; (* IF M # 0 *)
                    IF ((M = 0) AND (N = 0) AND (NOT(ENDOFGAME))) THEN
                        ClearScreen;
                        WriteLn;
                        WriteLn;
                        WriteLn;
                        WriteLn;
                        WriteString("CONGRATULATIONS! YOU WIN!");
                        WriteLn;
                        WriteString("PRESS RETURN ...");
                        WriteLn;
                        REPEAT
                            Read(CH);
                        UNTIL (CH = EOL);
                        ClearScreen;
                        ENDOFGAME := TRUE;
                    END; (* IF M = 0 AND N = 0 *)
                END; (* IF NOT END OF GAME *)
            END; (* WHILE M # 0 AND N # 0 *)
        END; (* WHILE NOT END OF GAME *)                   | (* END OPTION 1 *)

(*****************************************************************************)
(*****< OPTION 2 >************************************************************)
(*****************************************************************************)

    2 :
        ClearScreen;
        WriteLn;
        WriteLn;
        WriteString("HOW MANY CHIPS WOULD YOU LIKE IN THE M STACK ?");
        WriteLn;
        ReadCard(M);
        WriteLn;
        WriteLn;
        WriteString("HOW MANY CHIPS WOULD YOU LIKE IN THE N STACK ?");
        WriteLn;
        ReadCard(N);
        BUILDTREE(M,N,NIMTREE);
        TURN := NIMTREE;
        ASSIGNMINMAX(TURN);
        WHILE (NOT(ENDOFGAME)) DO
            WHILE ((M # 0) OR (N # 0)) DO
                IF (NOT(ENDOFGAME)) THEN
                    ClearScreen;
                    DISPLAY(M,N);
                    WriteString("IT IS MY TURN, PRESS RETURN ...");
                    WriteLn;
                    REPEAT
                        Read(CH);
                    UNTIL (CH = EOL);
                    CH := 'X';
                    REPEAT
                        Read(CH);
                    UNTIL (CH = EOL);
                    IF ((M # 0) OR (N # 0)) THEN
                        TURN := COMPTURN(TURN);
                        M := TURN@.M;
                        N := TURN@.N;
                        ClearScreen;
                        DISPLAY(M,N);
                    END; (* IF M # 0 *)
                    IF ((M = 0) AND (N = 0) AND (NOT(ENDOFGAME))) THEN
                        CH := 'X';
                        WriteString("PRESS RETURN...");
                        WriteLn;
                        REPEAT
                            Read(CH);
                        UNTIL (CH = EOL);
                        ClearScreen;
                        WriteLn;
                        WriteLn;
                        WriteLn;
                        WriteLn;
                        WriteString("CONGRATULATIONS! YOU WIN!");
                        WriteLn;
                        WriteString("PRESS RETURN ...");
                        WriteLn;
                        REPEAT
                            Read(CH);
                        UNTIL (CH = EOL);
                        ClearScreen;
                        ENDOFGAME := TRUE;
                    END; (* IF M = 0 AND N = 0 *)
                END; (* IF NOT END OF GAME *)
            IF (NOT(ENDOFGAME)) THEN
                WriteString("YOUR TURN! PRESS RETURN...");
                WriteLn;
                REPEAT
                    Read(CH);
                UNTIL (CH = EOL);
                DISPLAY(M,N);
                WriteString("FROM WHICH STACK WOULD YOU LIKE TO DRAW?");
                WriteLn;
                SKIPWHITESPACES();
                Read(CH);
                DISPLAY(M,N);
                WriteString("HOW MANY CHIPS WOULD YOU LIKE TO REMOVE ");
                WriteString("FROM THE '");
                Write(CAP(CH));
                WriteString("' STACK?");
                WriteLn;
                ReadCard(NUM);
                IF (CAP(CH) = 'M') THEN
                    M := M - NUM;
                ELSE
                    N := N - NUM;
                END; (* IF CAP(CH) = M *)
                Read(CH);
           IF ((M # 0) OR (N # 0)) THEN
                TURN := PLAYERSTURN(M,N,TURN);
           END; (* IF M # 0 *)
                DISPLAY(M,N);
                IF ((M = 0) AND (N = 0)) THEN
                    ClearScreen;
                    WriteLn;
                    WriteLn;
                    WriteLn;
                    WriteLn;
                    WriteString("SORRY YOU LOSE!!!");
                    WriteLn;
                    WriteString("PRESS RETURN ...");
                    WriteLn;
                    REPEAT
                        Read(CH);
                    UNTIL (CH = EOL);
                    ClearScreen;
                    ENDOFGAME := TRUE;
                END; (* IF M = 0 AND N = 0 *)
            END; (* WHILE M # 0 AND N # 0 *)
        END; (* IF NOT END OF GAME *)
        END; (* WHILE NOT END OF GAME *)                   | (* END OPTION 2 *)

(*****************************************************************************)
(*****< OPTION 3 >************************************************************)
(*****************************************************************************)

    3 :
        ClearScreen;
        WriteString("CHOSING MY NUMBERS");
        WriteLn;
        M := RANDOMNUMBER(RANDOM);
        N := RANDOMNUMBER(RANDOM);
        BUILDTREE(M,N,NIMTREE);
        TURN := NIMTREE;
        ASSIGNMINMAX(TURN);
        WHILE (NOT(ENDOFGAME)) DO
            WHILE ((M # 0) OR (N # 0)) DO
                IF (NOT(ENDOFGAME)) THEN
                    ClearScreen;
                    DISPLAY(M,N);
                    WriteString("IT IS MY TURN, PRESS RETURN ...")       ;
                    WriteLn;
                    REPEAT
                        Read(CH);
                    UNTIL (CH = EOL);
                    CH := 'X';
                    REPEAT
                        Read(CH);
                    UNTIL (CH = EOL);
                    IF ((M # 0) OR (N # 0)) THEN
                        TURN := COMPTURN(TURN);
                        M := TURN@.M;
                        N := TURN@.N;
                        ClearScreen;
                        DISPLAY(M,N);
                    END; (* IF M # 0 *)
                    IF ((M = 0) AND (N = 0) AND (NOT(ENDOFGAME))) THEN
                        CH := 'X';
                        WriteString("PRESS RETURN...");
                        WriteLn;
                        REPEAT
                            Read(CH);
                        UNTIL (CH = EOL);
                        ClearScreen;
                        WriteLn;
                        WriteLn;
                        WriteLn;
                        WriteLn;
                        WriteString("CONGRATULATIONS! YOU WIN!");
                        WriteLn;
                        WriteString("PRESS RETURN ...")                  ;
                        WriteLn;
                        REPEAT
                            Read(CH);
                        UNTIL (CH = EOL);
                        ClearScreen;
                        ENDOFGAME := TRUE;
                    END; (* IF M = 0 AND N = 0 *)
                END; (* IF NOT END OF GAME *)
                IF (NOT(ENDOFGAME)) THEN
                    WriteString("YOUR TURN! PRESS RETURN...");
                    WriteLn;
                    REPEAT
                        Read(CH);
                    UNTIL (CH = EOL);
                    DISPLAY(M,N);
                    WriteString("FROM WHICH STACK WOULD YOU LIKE TO DRAW?");
                    WriteLn;
                    SKIPWHITESPACES();
                    Read(CH);
                    DISPLAY(M,N);
                    WriteString("HOW MANY CHIPS WOULD YOU LIKE TO REMOVE ");
                    WriteString("FROM THE '");
                    Write(CAP(CH));
                    WriteString("' STACK?");
                    WriteLn;
                    ReadCard(NUM);
                    IF (CAP(CH) = 'M') THEN
                        M := M - NUM;
                    ELSE
                        N := N - NUM;
                    END; (* IF CAP(CH) = M *)
                    Read(CH);
                    IF ((M # 0) OR (N # 0)) THEN
                        TURN := PLAYERSTURN(M,N,TURN);
                    END; (* IF M # 0 *)
                    DISPLAY(M,N);
                    IF ((M = 0) AND (N = 0)) THEN
                        ClearScreen;
                        WriteLn;
                        WriteLn;
                        WriteLn;
                        WriteLn;
                        WriteString("SORRY YOU LOSE!!!");
                        WriteLn;
                        WriteString("PRESS RETURN ...");
                        WriteLn;
                        REPEAT
                        Read(CH);
                        UNTIL (CH = EOL);
                        ClearScreen;
                        ENDOFGAME := TRUE;
                    END; (* IF M = 0 AND N = 0 *)
                END; (* IF NOT END OF GAME *)
            END; (* WHILE M # 0 AND N # 0 *)
        END; (* WHILE NOT END OF GAME *)                   | (* END OPTION 3 *)

(*****************************************************************************)
(*****< OPTION 4 >************************************************************)
(*****************************************************************************)

    4 :
        WHILE (NOT(ENDOFGAME)) DO
            ClearScreen;
            WriteLn;
            WriteLn;
            WriteString("HOW MANY CHIPS WOULD YOU LIKE IN THE M STACK");
            WriteLn;
            ReadCard(M);
            WriteLn;
            WriteLn;
            WriteString("HOW MANY CHIPS WOULD YOU LIKE IN THE N STACK ");
            WriteLn;
            ReadCard(N);
            BUILDTREE(M,N,NIMTREE);
            TURN := NIMTREE;
            ASSIGNMINMAX(TURN);
            WHILE ((M # 0) OR (N # 0)) DO
                DISPLAY(M,N);
                WriteString("FROM WHICH STACK WOULD YOU LIKE TO DRAW?");
                WriteLn;
                SKIPWHITESPACES();
                Read(CH);
                DISPLAY(M,N);
                WriteString("HOW MANY CHIPS WOULD YOU LIKE TO REMOVE ");
                WriteString("FROM THE '");
                Write(CAP(CH));
                WriteString("' STACK?");
                WriteLn;
                ReadCard(NUM);
                IF (CAP(CH) = 'M') THEN
                    M := M - NUM;
                ELSE
                    N := N - NUM;
                END; (* IF CAP(CH) = M *)
                Read(CH);
                IF ((M # 0) OR (N # 0)) THEN
                    TURN := PLAYERSTURN(M,N,TURN);
                END; (* IF M # 0 *)
                DISPLAY(M,N);
                IF ((M = 0) AND (N = 0)) THEN
                    ClearScreen;
                    WriteLn;
                    WriteLn;
                    WriteLn;
                    WriteLn;
                    WriteString("SORRY YOU LOSE!!!");
                    WriteLn;
                    WriteString("PRESS RETURN ...");
                    WriteLn;
                    REPEAT
                        Read(CH);
                    UNTIL (CH = EOL);
                    ClearScreen;
                    ENDOFGAME := TRUE;
                END; (* IF M = 0 AND N = 0 *)
                IF (NOT(ENDOFGAME)) THEN
                    WriteString("NOW IT IS MY TURN, PRESS RETURN ...");
                    WriteLn;
                    REPEAT
                        Read(CH);
                    UNTIL (CH = EOL);
                    IF ((M # 0) OR (N # 0)) THEN
                        TURN := COMPTURN(TURN);
                        M := TURN@.M;
                        N := TURN@.N;
                    END; (* IF M # 0 *)
                    IF ((M = 0) AND (N = 0) AND (NOT(ENDOFGAME))) THEN
                        ClearScreen;
                        WriteLn;
                        WriteLn;
                        WriteLn;
                        WriteLn;
                        WriteString("CONGRATULATIONS! YOU WIN!");
                        WriteLn;
                        WriteString("PRESS RETURN ...");
                        WriteLn;
                        REPEAT
                            Read(CH);
                        UNTIL (CH = EOL);
                        ClearScreen;
                        ENDOFGAME := TRUE;
                    END; (* IF M = 0 AND N = 0 *)
                END; (* IF NOT END OF GAME *)
            END; (* WHILE M # 0 AND N # 0 *)
        END; (* WHILE NOT END OF GAME *)                   | (* END OPTION 4 *)

(*****************************************************************************)
(*****< OPTION 5 >************************************************************)
(*****************************************************************************)

    5:
        QUIT := TRUE;
        WriteString("THANKS FOR PLAYING NIM WITH ME!");
        WriteLn;
        WriteString("HAVE A NICE DAY!");
        WriteLn;                                             (* END OPTION 5 *)

    END; (* CASE *)

END; (* WHILE NOT QUIT *)

END NIM.
