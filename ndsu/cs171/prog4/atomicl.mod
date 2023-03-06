MODULE ATOMICL;

(****************************************************************)
(* MODULE TO BREAK UP NESTED LISTS                              *)
(*                                                              *)
(* CHRISTOPHER C. TJON                                          *)
(* 110975-8                                                     *)
(* 5 FEB 1990                                                   *)
(*                                                              *)
(****************************************************************)

FROM ATOMLIST IMPORT GENERALLIST, GENERALLISTNODE, CREATELISTNODE,
                     GETLIST, CREATELIST, CREATEATOMNODE, GETATOM,
                     LIST, LENGTH, CAR, CDR, CONS;

FROM Strings IMPORT String;

FROM InOut IMPORT WriteLn, WriteString, Write, Read, Done, ReadLn,
                  OpenInput, OpenOutput;

VAR L : GENERALLIST;


(****************************************************************)
(*****< PROCEDURE PRINT LIST >***********************************)
(****************************************************************)

PROCEDURE PRINTLIST(L : GENERALLIST);
(****************************************************************)
(* REQUIRES : L HAS BEEN INITIALIZED                            *)
(* MODIFIES : NOTHING                                           *)
(* EFFECTS  : PRINTS THE NESTED LISTS IN L                      *)
(****************************************************************)

VAR N : GENERALLISTNODE;

BEGIN
    Write('(');
    WHILE LENGTH(L) # 0 DO
    N := CAR(L);
         IF (NOT(LIST(N))) THEN
             Write(GETATOM(N));
         ELSE
             PRINTLIST(GETLIST(N));
         END; (* IF *)
        IF LENGTH(L) > 1 THEN
            Write(',');
        END; (* IF *)
        L := CDR(L);
    END; (* WHILE *)
    Write(')');
END PRINTLIST;


(****************************************************************)
(*****< PROCEDURE READ LIST >************************************)
(****************************************************************)

PROCEDURE READLIST(VAR L : GENERALLIST);
(****************************************************************)
(* REQUIRES : L HAS BEEN INITIALIZED                            *)
(* MODIFIES : NOTHING                                           *)
(* EFFECTS  : READS THE NESTED LISTS IN L                       *)
(****************************************************************)

VAR CH     : CHAR;
    RESTOF : String;

    PROCEDURE INNERREAD(CH : CHAR; VAR L :GENERALLIST);
    (************************************************************)
    (* REQUIRES : L HAS BEEN INTIALIZED                         *)
    (* MODIFIES : L                                             *)
    (* EFFECTS  : RECURSIVELY READS AND STORES THE NESTED LISTS *)
    (************************************************************)

    VAR N  : GENERALLIST;
    NEXTCH : CHAR;

    BEGIN
        IF CH = ',' THEN
            Read(CH);
        END; (* IF *)
        IF CH = '(' THEN
            CREATELIST(N);
            Read(NEXTCH);
             INNERREAD(NEXTCH,N);
            Read(NEXTCH);
            INNERREAD(NEXTCH,L);
            CONS(CREATELISTNODE(N),L);
        ELSIF (CH = ')' ) THEN
            RETURN
        ELSE
            Read(NEXTCH);
            INNERREAD(NEXTCH,L);
            CONS(CREATEATOMNODE(CH),L);
        END; (* IF CH = ',' *)
      END INNERREAD;

BEGIN
    Read(CH);
    IF Done THEN
        Read(CH);
        INNERREAD(CH,L);
        ReadLn(RESTOF);
    END; (* IF *)
END READLIST;

(****************************************************************)
(*****< PROCEDURE BREAK UP >*************************************)
(****************************************************************)

PROCEDURE BREAKUP(L : GENERALLIST);
(****************************************************************)
(* REQUIRES : L HAS BEEN INITIALIZED                            *)
(* MODIFIES : L                                                 *)
(* EFFECTS  : BREAKS UP THE NESTED LISTS INTO COMPONENT PARTS   *)
(****************************************************************)

VAR N : GENERALLISTNODE;

BEGIN
    IF LENGTH(L) > 0 THEN
       N := CAR(L);
        IF (NOT(LIST(N))) THEN
            Write(GETATOM(N));
            WriteLn;
        ELSE
            PRINTLIST(GETLIST(N));
            WriteLn;
            BREAKUP(GETLIST(N));
        END; (* IF NOT LIST *)
        BREAKUP(CDR(L));
    END; (* IF LENGTH *)
END BREAKUP;


(****************************************************************)
(*****< MAIN PROGRAM >*******************************************)
(****************************************************************)

BEGIN
OpenInput('');
OpenOutput('');
LOOP
    CREATELIST(L);
    READLIST(L);
    IF NOT Done THEN
       EXIT
    END; (* IF *)
    WriteString('THE NEXT INPUT LIST IS : ');
    WriteLn;
    PRINTLIST(L);
    WriteLn;
    WriteString('BREAKING THE LIST UP INTO ITS COMPONENT PARTS YEILDS : ');
    WriteLn;
    BREAKUP(L);
    WriteLn;
    WriteLn;
END; (* LOOP *)

END ATOMICL.

